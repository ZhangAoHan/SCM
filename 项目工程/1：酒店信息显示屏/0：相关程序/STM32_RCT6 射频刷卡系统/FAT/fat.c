#include "FAT.h"
#include "usart.h"
	 
 

//全局变量区域
DWORD FirstDirClust;    //根目录簇号
DWORD FirstDataSector;	//数据区的第一个扇区
WORD BytesPerSector;	//每扇区字节数
DWORD FATsectors;		//FAT表所占扇区数
WORD SectorsPerClust;	//每簇扇区数
DWORD FirstFATSector;	//第一个FAT表(FAT1)所在扇区
DWORD FirstDirSector;	//第一个目录扇区 fat32
DWORD RootDirSectors;	//根目录所占用的扇区数
DWORD RootDirCount;		//根目录下目录项数
BYTE FAT32_Enable;		//FAT32文件系统标志
	    
DWORD Cur_Dir_Cluster;//当前目录簇号
//DWORD Fat_Dir_Cluster;//父目录簇号 在FAT文件夹里面CopyDirentruyItem函数中修改!
	
FAT_TABLE FAT_TAB;//TINY FAT表		 

//文件信息缓存区		   		    															   
FileInfoStruct F_Info[3];
//外部全局变量

//FAT 数据缓存区
u8 fat_buffer[512];//用于存储FAT数据
u8 LongNameBuffer[MAX_LONG_NAME_SIZE];//长文件名的缓存区
BOOL LongNameFlag = 0;//是否存在长文件名的标志


//文件类型
//3gp,3g2,m4a,mp4也是支持的.
//返回值:对应的类型   
//0,mp1;1,mp2;2,mp3;3,mp4;4,m4a;5,3gp;6,3g2;7,ogg;8,acc;9,wma;10,wav;11,midi;12,flac;
//13,lrc;14,txt;15,c;16,h;17,file;18,FON;19,SYS;20,bmp;21,jpg;22,jpeg;   
const unsigned char *filetype[23]=
{
"MP1","MP2","MP3","MP4","M4A","3GP","3G2","OGG","ACC","WMA","WAV","MID","FLA",
"LRC","TXT","C  ","H  ","   ","FON","SYS","BMP","JPG","JPE"
};
//返回扩展名类型
//输入:exName 文件扩展名
//返回值:文件的类型,目前支持20种文件类型,最大支持32种文件类型
u32 FileType_Tell(u8 * exName)
{
    u8 i;
    u8 t;   
    for(i=0;i<20;i++)
    { 
        for(t=0;t<3;t++)if(exName[t]!=filetype[i][t])break; 
        if(t==3)break;
    } 
    return 1<<i;//返回文件类型
}  
//FAT初始化，不含SD的初始化，用之前应先调用sd的初始化
//返回值:0,初始化成功
//    其他,初始化失败   
unsigned char FAT_Init(void)//Initialize of FAT  need initialize SD first
{  		   
	bootsector710 *bs  = 0;       //定义DBR结构体，包含BPB部分（12~90字节是BPB）
	bpb710        *bpb = 0;       //定义BPB结构体     
	partrecord    *pr  = 0;       //定义硬盘信息　结构休      （16字节）
	DWORD hidsec=0;             //隐藏的扇区数即为DBR在物理扇区的偏移量
	long long Capacity;   
	Capacity =(long long)SD_GetSectorCount()*512;   //得到SD容量，单位为字节            
	if(Capacity<0xff)return 1;       
	
	if(SD_ReadDisk(fat_buffer,0,1))return 2; //读物理扇区0。即MBR（其中MBR内的硬盘分区表中有DBR的地址信息），如没有MBR，则为DBR。经测试，我的SD卡是有MBR的
	if(fat_buffer[0]!=0XEB&&fat_buffer[0]!=0XE9)  //如物理0扇区第一字节不为0XEB或0XE9,则存在MBR，否则不存在
		{   				  
		//printf("此SD卡的物理扇区0为MBR\n");
		pr = (partrecord *)((partsector *)fat_buffer)->psPart;//first partition       第一分区
		hidsec=pr->prStartLBA;   //隐藏的扇区 即DBR的物理扇区偏移
		//printf("此SD卡的DBR的物理扇区为=%d\n",hidsec) ;
	}
	else 
	{
		hidsec=0;      //无MBR，物理扇区0即为DBR
		//printf("此SD卡不存在MBR，物理扇区0即为DBR，物理扇区0即为逻辑扇区0.\n"); 
 	} 
	if(SD_ReadDisk(fat_buffer,hidsec,1))return 3;
	//printf("DBR物理扇区偏移量：%d \n",hidsec);
	bs = (bootsector710 *)fat_buffer;
	bpb = (bpb710 *)bs->bsBPB;
	if(bpb->bpbFATsecs)//detemine thd FAT type  do not support FAT12
	{
		FAT32_Enable=0;   					//FAT16
		FATsectors     = bpb->bpbFATsecs;	//FAT表占用的扇区数 
		FirstDirClust = 2;
	}
	else
	{
		FAT32_Enable=1;   					//FAT32
		FATsectors     = bpb->bpbBigFATsecs;//FAT占用的扇区数 
		FirstDirClust = bpb->bpbRootClust;
	}   
	BytesPerSector   = bpb->bpbBytesPerSec;      				//每扇区字节数
	SectorsPerClust   = (BYTE)bpb->bpbSecPerClust;				//每簇扇区数
	FirstFATSector   = bpb->bpbResSectors+hidsec;				//第一个FAT表扇区
	RootDirCount   = bpb->bpbRootDirEnts;      					//根目录项数
	RootDirSectors   = (RootDirCount*32)>>9;      				//根目录占用的扇区数
	FirstDirSector   = FirstFATSector+bpb->bpbFATs*FATsectors;	//第一个目录扇区
	FirstDataSector   = FirstDirSector+RootDirSectors;			//第一个数据扇区
	//printf("每扇区字节数：%d \n",BytesPerSector);
	//printf("每簇扇区数：%d \n",SectorsPerClust);
	//printf("第一个FAT表扇区：%d \n",FirstFATSector);
	//printf("根目录项数：%d \n",RootDirCount);
	//printf("根目录占用的扇区数：%d \n",RootDirSectors);
	return 0; 	 
}   
//将FAT表,从头到尾COPY过来,如果没COPY完,则Fat_Over=0,否则为1   
//cluster:文件的首簇
void Copy_Fat_Table(unsigned long cluster)
{
	u32 bcluster; 
	u8 fat_base;//0~Fat_Table_Size	 
	FAT_TAB.Fat_Over=0;	   
    for(fat_base=0;fat_base<Fat_Table_Size;fat_base++)
	{
		FAT_TAB.Fat_Base_Tab[fat_base]=0;
		FAT_TAB.Fat_Base_Len[fat_base]=0;//全部清空
	}
	fat_base=0;
	bcluster=cluster;//起始簇,不能丢失的.
	FAT_TAB.Fat_Base_Tab[fat_base]=bcluster;
	FAT_TAB.Fat_Base_Len[fat_base]=1;//有1个数据了,就是最新的bcluster	  
	while(1)
	{
	    bcluster=FAT_NextCluster(bcluster);	   
		if((FAT32_Enable==0&&bcluster==0xffff)||bcluster==0x0ffffff8||bcluster==0x0fffffff)//文件结束 
		{
			FAT_TAB.Fat_Over=1;//文件COPY结束
			break; 
		} 	 		
		if(bcluster-FAT_TAB.Fat_Base_Tab[fat_base]-FAT_TAB.Fat_Base_Len[fat_base]!=0)//是否满足偏移条件
		{
			fat_base++;//启用下一个BASE
			if(fat_base>=Fat_Table_Size)//超出了缓冲区范围,文件太大了/磁盘太零散了!!!
			{
				FAT_TAB.Fat_Over=0;//文件COPY结束
				break; 
			}
			FAT_TAB.Fat_Base_Tab[fat_base]=bcluster;
			FAT_TAB.Fat_Base_Len[fat_base]=1;//有1个数据了,就是最新的bcluster				
		}else FAT_TAB.Fat_Base_Len[fat_base]++;//基址偏移量增加	   
	}
	//监控用
	//printf("Fat_Over:%d\n",FAT_TAB.Fat_Over);
	//printf("Fat_Head_Pos:%d\n",FAT_TAB.Fat_Head_Pos);
	//printf("Fat_Base_Tab[0]:%d\n",FAT_TAB.Fat_Base_Tab[0]);
	//printf("Fat_Base_Tab[1]:%d\n",FAT_TAB.Fat_Base_Tab[1]);
	//printf("Fat_Base_Tab[2]:%d\n",FAT_TAB.Fat_Base_Tab[2]);		 
}	    							    
//在TINY FAT表里面查找cluster的上一个簇号
//cluster:当前簇号
//返回值:cluster,表示不能再向上了
//	      其他值,cluster的上一个簇	   
u32 FatTab_Prev_Cluster(unsigned long cluster)
{
	u8 t;	 
	u32 tempclust;
RSTP:
	for(t=0;t<Fat_Table_Size;t++)
	{
		if(cluster<=(FAT_TAB.Fat_Base_Tab[t]+FAT_TAB.Fat_Base_Len[t]-1)&&cluster>=FAT_TAB.Fat_Base_Tab[t])break;//在这个BASE内
	}	  
	if(cluster==FAT_TAB.Fat_Base_Tab[t])//是在BASE,但是是第一个
	{		 
		if(t==0)//这份FAT表 全部找完还没找到
		{					 									    
			if(FAT_TAB.Fat_Head_Pos>0)//不超过范围
			{
				FAT_TAB.Fat_Head_Pos--;
				tempclust=FAT_TAB.Fat_Base_Head[FAT_TAB.Fat_Head_Pos];//拷贝上一个tinyFAT表的表头
			}else return cluster;   //无法继续向上
			Copy_Fat_Table(tempclust);//COPY 上一个tinyFAT表
			goto RSTP;
			//return FAT_TAB.Fat_Base_Tab[Fat_Table_Size-1]+FAT_TAB.Fat_Base_Len[Fat_Table_Size-1]-1;//返回上一个簇号		 
		} 																 
		return FAT_TAB.Fat_Base_Tab[t-1]+FAT_TAB.Fat_Base_Len[t-1]-1;//上一个簇号
	}else return --cluster;//返回上一个簇   
}	 
//在TINY FAT表里面查找cluster的下一个簇号
//cluster:当前簇号
//返回值:0x0ffffff8,表示没有后续簇了
//	   		 其他值,对应簇号
u32 FatTab_Next_Cluster(unsigned long cluster)
{
	u8 t;	 
RESN:
	for(t=0;t<Fat_Table_Size;t++)
	{
		if(cluster<=(FAT_TAB.Fat_Base_Tab[t]+FAT_TAB.Fat_Base_Len[t]-1)&&cluster>=FAT_TAB.Fat_Base_Tab[t])break;//在这个BASE内
	}	  
	if(cluster==FAT_TAB.Fat_Base_Tab[t]+FAT_TAB.Fat_Base_Len[t]-1)//是在BASE,但是是最后一个了
	{		 
		if((t+1)==Fat_Table_Size)//全部找完还没找到
		{														  
			if(FAT_TAB.Fat_Over)return 0x0ffffff8;//文件结束了	 
			if(FAT_TAB.Fat_Head_Pos<Fat_Head_Size-1)//不超过范围
			{		  
				FAT_TAB.Fat_Base_Head[FAT_TAB.Fat_Head_Pos]=FAT_TAB.Fat_Base_Tab[0];//拷贝当前tinyFAT表的第一个簇
				FAT_TAB.Fat_Head_Pos++;
			}
			Copy_Fat_Table(cluster);//COPY 余下的FAT表
			goto RESN;
		} 
		if(FAT_TAB.Fat_Base_Len[t+1]==0)return 0x0ffffff8;//没有后续簇了
		return FAT_TAB.Fat_Base_Tab[t+1];//下一个簇号
	}else return ++cluster;//返回下一个簇   
}	  
//在SD卡上的FAT表中查找下一簇号
//cluster:当前簇号
//返回值:0x0ffffff8,表示没有后续簇了
//	   		 其他值,下一簇号				   		    
unsigned long FAT_NextCluster(unsigned long cluster)
{
	DWORD sector;
	DWORD offset;  

	if(FAT32_Enable)offset = cluster/128;//FAT32的FAT表中,用四个字节表示一个簇地址.512/4=128
	else offset = cluster/256;			 //FAT16的FAT表中,用两个字节表示一个簇地址.512/2=256
	if(cluster<2)return 0x0ffffff8;		 //簇0,1不能用于存放
	sector=FirstFATSector+offset;//计算该簇实际所在扇区

	if(SD_ReadDisk(fat_buffer,sector,1))return 0x0ffffff8;//读取FAT表,发生错误是返回0x0ffffff8
	if(FAT32_Enable)
	{
		offset=cluster%128;//计算在扇区内的偏移
		sector=((unsigned long *)fat_buffer)[offset];//u32	
	}
	else
	{
		offset=cluster%256;//计算在扇区内的偏移
		sector=((unsigned short *)fat_buffer)[offset];//u16
	}			   
	return (unsigned long)sector;//return the cluste number
}	  
//将簇号转变为扇区号
//cluster:要变为扇区的簇号
//返回值:cluster对应的扇区号
u32 fatClustToSect(u32 cluster)
{
	return FirstDataSector+(DWORD)(cluster-2)*(DWORD)SectorsPerClust;	 
}	 
//复制记录项信息
//将Source的相关内容复制到Desti里面
void CopyDirentruyItem(FileInfoStruct *Desti,direntry *Source)
{
	u8 i;
	u8 t;
	for(i=0;i<8;i++)Desti->F_ShortName[i]=Source->deName[i];//复制短文件名
	Desti->F_Type         = FileType_Tell(Source->deExtension);
	Desti->F_StartCluster = Source->deStartCluster + (((unsigned long)Source->deHighClust)<<16);//不用管
	Desti->F_Size         = Source->deFileSize;
	Desti->F_Attr         = Source->deAttributes;
	Desti->F_CurClust     = 0;//扇区...
	Desti->F_Offset       = 0;//偏移0 	

	//FAT的簇号不能是0(更目录簇号)
	if(FAT32_Enable&&Desti->F_StartCluster==0)  
	{																  
		Desti->F_StartCluster=FirstDirClust;//改变这个簇号.使其等于根目录所在簇号!!
	}   
	if(LongNameFlag)//存在长文件名
	{
		LongNameBuffer[MAX_LONG_NAME_SIZE-1] = 0;
		LongNameBuffer[MAX_LONG_NAME_SIZE-2] = 0;
		//UniToGB(LongNameBuffer);  //把Unicode代码转换为ASICII码
		for(i=0;i<80;i++)Desti->F_Name[i] = LongNameBuffer[i];//复制长文件名
	}else //短文件名
	{	//2E:当前目录所在簇.2E 2E:父目录所在簇.
		if(Source->deName[0]==0x2e)//得到一个父目录(修改为:":\")
		{	
			//保存父目录簇号   
			//Fat_Dir_Cluster=Desti->F_StartCluster; 	 
			Desti->F_Name[0]=':';
			Desti->F_Name[1]=0x5c;//'\'
			Desti->F_Name[2]='\0';//加入结束符
		}else	    			  //普通文件
		{
			t=7;//从最后一个短文件名开始,找空格,并丢掉
			while(t>0)
			{
				if(Source->deName[t]!=' ')break;
				t--;
			}   			   
			for(i=0;i<t+1;i++)Desti->F_Name[i] = Source->deName[i];//复制短文件名 
			if(Desti->F_Attr==0X20&&(Source->deExtension[0]!=0x20))//归档文件且文件后缀不为空
			{ 	   
				Desti->F_Name[i++]='.';//加入"."
				for(t=0;t<3;t++)Desti->F_Name[i+t] = Source->deExtension[t];//复制后缀	  
				Desti->F_Name[i+t]='\0';//加入结束符
			}else Desti->F_Name[i]='\0';//加入结束符
		}
	} 															   	  								  
	return ;
}		 
//浏览目标文件夹下面的一个文件类
//dir_clust:当前目录所在簇号
//FileInfo :目标文件的实体对象(FileInfoStruct体)
//type     :要查找的文件类型:1<<0,mp1;1<<1,mp2;1<<2,mp3;1<<3,mp4;1<<4,m4a;1<<5,3gp;
//                           1<<6,3g2;1<<7,ogg;1<<8,acc;1<<9,wma;1<<10,wav;1<<11,mid;
//							 1<<12,flac;1<<13,lrc;1<<14,txt;1<<15,c;1<<16,h;1<<17,file;
//                           1<<18,fon;1<<19,sys;1<<20,bmp;1<<21,jpg;1<<22,jpeg; 
//count    :0,返回当前目录下,该类型文件的个数;不为零时,返回第count个文件的详细信息
//返回值   :1,操作成功.0,操作失败
u8 Get_File_Info(u32 dir_clust,FileInfoStruct *FileInfo,u32 type,u16 *count)
{ 			  	   
	DWORD sector;
	DWORD cluster=dir_clust;
	DWORD tempclust;
	unsigned char cnt;
	unsigned int offset;		 
	unsigned short cont=0;//文件索引标志 <65536
	unsigned char j; //long name fat_buffer offset;
	unsigned char *p;//long name fat_buffer pointer
	direntry *item = 0;
	winentry *we =0;	  
	cont=0;
	LongNameFlag = 0;//清空长文件名标志

	//SD_Init();//初始化SD卡，在意外拔出之后可以正常使用
	//goto SD;
	if(cluster==0 && FAT32_Enable==0)//FAT16根目录读取
	{			 
		for(cnt=0;cnt<RootDirSectors;cnt++)
		{
			if(SD_ReadDisk(fat_buffer,FirstDirSector+cnt,1))return 0;//读数错误    	   
			for(offset=0;offset<512;offset+=32)
			{
				item=(direntry *)(&fat_buffer[offset]);//指针转换
				//找到一个可用的文件
				if((item->deName[0]!=0x2E)&&(item->deName[0]!=0x00)&&(item->deName[0]!=0xe5)
				||((item->deName[0]==0x2E)&&(item->deName[1]==0x2E)))//找到一个合法文件.忽略".",使用".."
				{		   
					if(item->deAttributes == 0x0f)//找到一个长文件名
					{
						we = (winentry *)(&fat_buffer[offset]);
						j = 26 *( (we->weCnt-1) & WIN_CNT);//长文件名的长度
                        if(j<MAX_LONG_NAME_SIZE-25)
						{
							p = &LongNameBuffer[j];//偏移到目标地址
							for (j=0;j<10;j++)	*p++ = we->wePart1[j];			
							for (j=0;j<12;j++)	*p++ = we->wePart2[j];
							for (j=0;j<4;j++)	*p++ = we->wePart3[j];	
							if (we->weCnt & 0x40) (*(unsigned int *)p) = 0;  				
							if ((we->weCnt & WIN_CNT) == 1) LongNameFlag = 1;//最后一个长文件项找到了	
						}	    
					}else 
					{  	 										 									 
						if(type&FileType_Tell(item->deExtension))//找到一个目标文件
						{
							cont++;//文件索引增加
						 }
						 //查找该目录下,type类型的文件个数
						if(*count&&cont==*count)
						{
							////printf("\ncount:%d",*count);
							CopyDirentruyItem(FileInfo,item);//复制目录项,提取详细信息 
							return 1;//找到目标文件成功	 
						}
						LongNameFlag=0;//清空长文件名
					}
				}
			}
		}  				 
	}
	else//其他文件夹/FAT32系统
	{
		tempclust=cluster;
		while(1)
		{
			sector=fatClustToSect(tempclust);
			for(cnt=0;cnt<SectorsPerClust;cnt++)
			{
				if(SD_ReadDisk(fat_buffer,sector+cnt,1))return 0;
				for(offset=0;offset<512;offset+=32)
				{
					item=(direntry *)(&fat_buffer[offset]);
					if((item->deName[0]!=0x2E)&&(item->deName[0]!=0x00)&&(item->deName[0]!=0xe5)
					||((item->deName[0]==0x2E)&&(item->deName[1]==0x2E)))//找到一个合法文件.忽略".",使用".."
					{				
						if(item->deAttributes == 0x0f) //得到一个长文件名
						{
							we = (winentry *)(&fat_buffer[offset]);
							j = 26 *( (we->weCnt-1) & WIN_CNT);
							if(j<MAX_LONG_NAME_SIZE-25)
							{
								p = &LongNameBuffer[j];//p指向长文件名的存放地址
								for (j=0;j<10;j++)	*p++ = we->wePart1[j];			
								for (j=0;j<12;j++)	*p++ = we->wePart2[j];
								for (j=0;j<4;j++)	*p++ = we->wePart3[j];	
								if (we->weCnt & 0x40) (*(unsigned int *)p) = 0;				
								if ((we->weCnt & WIN_CNT) == 1) LongNameFlag = 1;	
							}										    			 
						}	  
						else 
						{
							if(type&FileType_Tell(item->deExtension))//找到一个目标文件
							{
								cont++;//文件索引增加
							 }
							 //查找该目录下,type类型的文件个数
							if(*count&&cont==*count)
							{
								CopyDirentruyItem(FileInfo,item);//复制目录项,提取详细信息  
								return 1;//找到目标文件成功	 
							}
							LongNameFlag=0;//清空长文件名
						}
					}
				}
			}						  
			tempclust=FAT_NextCluster(tempclust);//查找下一个簇号
			if(tempclust==0x0fffffff||tempclust==0x0ffffff8 ||(FAT32_Enable==0&&tempclust==0xffff))break;
		}  
	}
	if(*count==0)
	{
		*count=cont;//得到总共文件数目
		return 1;   //操作成功,找到cont个符合条件的文件了
	}else return 0; //操作失败,没找到文件,或者出错
}
//打开文件
//FileInfo:文件信息
void F_Open(FileInfoStruct *FileInfo)
{
	FileInfo->F_CurClust=FileInfo->F_StartCluster;//当前簇为首簇
	FileInfo->F_Offset=0;//偏移扇区为0
}
//读取512个字节
//FileInfo:要读取的文件
//buf     :数据缓存区
//返回值  :0,操作失败,1,操作成功
unsigned char F_Read(FileInfoStruct *FileInfo,u8 *buf)
{	
	DWORD sector;			   		  
	sector=fatClustToSect(FileInfo->F_CurClust);//得到当前簇号对应的扇区号	   	 		    
	if(SD_ReadDisk(buf,sector+FileInfo->F_Offset,1))return 0;//读数错误   
	FileInfo->F_Offset++;
	if(FileInfo->F_Offset==SectorsPerClust)	//簇的尽头,换簇
	{
		FileInfo->F_Offset=0;		    
		FileInfo->F_CurClust=FAT_NextCluster(FileInfo->F_CurClust);//读取下一个簇号
		if((FAT32_Enable==0&&FileInfo->F_CurClust==0xffff) \
		||FileInfo->F_CurClust==0x0ffffff8||FileInfo->F_CurClust == 0x0fffffff)return 0;//error	    
	} 
	return 1;//读取成功
} 

//比较两个字符串相等不
//相等,返回1,不相等,返回0;
u8 mystrcmp(u8*s1,u8*s2)
{
	u8 len1,len2;
	len1=len2=0;
	while(*s1!='\0')
	{
		len1++;s1++;
	}
	while(*s2!='\0')
	{
		len2++;s2++;
	}
	if(len1!=len2)return 0;//不相等 
	s1-=len1;s2-=len1;
	while(*s1!='\0')
	{
		if(*s1!=*s2)return 0;//不相等 
		s1++;s2++;
	}
	return 1;
}  
	 
//查找系统文件
//在指定目录下,找寻一个指定类型的指定名字的文件
//cluster:文件夹的簇号!!!
//Name   :文件的名字
//type   :文件类型
//返回值 :该文件的详细信息/如果 FileInfo.F_StartCluster=0 则说明此次寻找失败
FileInfoStruct F_Search(u32 cluster,unsigned char *Name,u32 type)
{
	DWORD sector;			 
	DWORD tempclust;
	unsigned char cnt;
	unsigned int offset; 	    
	direntry *item = 0;	  
	FileInfoStruct FileInfo;    			    
	if(cluster==0 && FAT32_Enable==0)//FAT16根目录读取
	{			 
		for(cnt=0;cnt<RootDirSectors;cnt++)
		{
			if(SD_ReadDisk(fat_buffer,FirstDirSector+cnt,1))
			{
				FileInfo.F_StartCluster=0;//读数错误 
				return FileInfo;   
			}
			for(offset=0;offset<512;offset+=32)
			{
				item=(direntry *)(&fat_buffer[offset]);//指针转换
				//找到一个可用的文件
				if((item->deName[0] != 0x00) && (item->deName[0] != 0xe5))//找到一个合法文件
				{		   
					if(item->deAttributes != AM_LFN)//忽略长文件名	 
					{  	 				 
						CopyDirentruyItem(&FileInfo,item);//复制目录项,提取详细信息	   
						if(FileInfo.F_Type&type)//找到一个合适的类型了
						{
						   // //printf("File Name:%s\n",FileInfo.F_Name);
	
							//找到了文件,返回这个文件的首簇
							if(mystrcmp(Name,FileInfo.F_Name))
							{						    
								return FileInfo; 
							}
						} 	  
						LongNameFlag=0;//清空长文件名
					}
				}
			}
		}  				 
	}else//其他文件夹/FAT32系统
	{
		tempclust=cluster;
		while(1)
		{
			sector=fatClustToSect(tempclust);
			for(cnt=0;cnt<SectorsPerClust;cnt++)
			{
				if(SD_ReadDisk(fat_buffer,sector+cnt,1))
				{
					FileInfo.F_StartCluster=0;//读数错误 
					return FileInfo;   
				}
				for(offset=0;offset<512;offset+=32)
				{
					item=(direntry *)(&fat_buffer[offset]);
					if((item->deName[0] != 0x00) && (item->deName[0] != 0xe5))
					{				
						if(item->deAttributes != AM_LFN) //忽略长文件名		    
						{  	 				 
							CopyDirentruyItem(&FileInfo,item);//复制目录项,提取详细信息	  

							if(FileInfo.F_Type&type)//找到一个合适的类型了
							{	/*										   
								//printf("F_Info->F_Name:%s\n",FileInfo.F_Name);
								//printf("F_Info->F_Type:%d\n",FileInfo.F_Type);
								//printf("F_Info->F_Size:%d\n",FileInfo.F_Size);
								//printf("F_Info->F_StartClusterH:%x\n",FileInfo.F_StartCluster>>8); 	
								//printf("F_Info->F_StartClusterL:%x\n\n",FileInfo.F_StartCluster&0xff); */
								//找到了文件,返回这个文件的首簇
								if(mystrcmp(Name,FileInfo.F_Name))
								{						 
									return FileInfo; 
								}
							} 	  
							LongNameFlag=0;//清空长文件名
						}
					}
				}
			}						  
			tempclust=FAT_NextCluster(tempclust);//查找下一个簇号
			if(tempclust==0x0fffffff||tempclust==0x0ffffff8 ||(FAT32_Enable==0&&tempclust==0xffff))break;
		}  
	}		   
	FileInfo.F_StartCluster=0;//读数错误 
	return FileInfo;   					    
}	 	 	 						  

	 	 	 						  

