#include "FAT.h"
#include "usart.h"
	 
 

//ȫ�ֱ�������
DWORD FirstDirClust;    //��Ŀ¼�غ�
DWORD FirstDataSector;	//�������ĵ�һ������
WORD BytesPerSector;	//ÿ�����ֽ���
DWORD FATsectors;		//FAT����ռ������
WORD SectorsPerClust;	//ÿ��������
DWORD FirstFATSector;	//��һ��FAT��(FAT1)��������
DWORD FirstDirSector;	//��һ��Ŀ¼���� fat32
DWORD RootDirSectors;	//��Ŀ¼��ռ�õ�������
DWORD RootDirCount;		//��Ŀ¼��Ŀ¼����
BYTE FAT32_Enable;		//FAT32�ļ�ϵͳ��־
	    
DWORD Cur_Dir_Cluster;//��ǰĿ¼�غ�
//DWORD Fat_Dir_Cluster;//��Ŀ¼�غ� ��FAT�ļ�������CopyDirentruyItem�������޸�!
	
FAT_TABLE FAT_TAB;//TINY FAT��		 

//�ļ���Ϣ������		   		    															   
FileInfoStruct F_Info[3];
//�ⲿȫ�ֱ���

//FAT ���ݻ�����
u8 fat_buffer[512];//���ڴ洢FAT����
u8 LongNameBuffer[MAX_LONG_NAME_SIZE];//���ļ����Ļ�����
BOOL LongNameFlag = 0;//�Ƿ���ڳ��ļ����ı�־


//�ļ�����
//3gp,3g2,m4a,mp4Ҳ��֧�ֵ�.
//����ֵ:��Ӧ������   
//0,mp1;1,mp2;2,mp3;3,mp4;4,m4a;5,3gp;6,3g2;7,ogg;8,acc;9,wma;10,wav;11,midi;12,flac;
//13,lrc;14,txt;15,c;16,h;17,file;18,FON;19,SYS;20,bmp;21,jpg;22,jpeg;   
const unsigned char *filetype[23]=
{
"MP1","MP2","MP3","MP4","M4A","3GP","3G2","OGG","ACC","WMA","WAV","MID","FLA",
"LRC","TXT","C  ","H  ","   ","FON","SYS","BMP","JPG","JPE"
};
//������չ������
//����:exName �ļ���չ��
//����ֵ:�ļ�������,Ŀǰ֧��20���ļ�����,���֧��32���ļ�����
u32 FileType_Tell(u8 * exName)
{
    u8 i;
    u8 t;   
    for(i=0;i<20;i++)
    { 
        for(t=0;t<3;t++)if(exName[t]!=filetype[i][t])break; 
        if(t==3)break;
    } 
    return 1<<i;//�����ļ�����
}  
//FAT��ʼ��������SD�ĳ�ʼ������֮ǰӦ�ȵ���sd�ĳ�ʼ��
//����ֵ:0,��ʼ���ɹ�
//    ����,��ʼ��ʧ��   
unsigned char FAT_Init(void)//Initialize of FAT  need initialize SD first
{  		   
	bootsector710 *bs  = 0;       //����DBR�ṹ�壬����BPB���֣�12~90�ֽ���BPB��
	bpb710        *bpb = 0;       //����BPB�ṹ��     
	partrecord    *pr  = 0;       //����Ӳ����Ϣ���ṹ��      ��16�ֽڣ�
	DWORD hidsec=0;             //���ص���������ΪDBR������������ƫ����
	long long Capacity;   
	Capacity =(long long)SD_GetSectorCount()*512;   //�õ�SD��������λΪ�ֽ�            
	if(Capacity<0xff)return 1;       
	
	if(SD_ReadDisk(fat_buffer,0,1))return 2; //����������0����MBR������MBR�ڵ�Ӳ�̷���������DBR�ĵ�ַ��Ϣ������û��MBR����ΪDBR�������ԣ��ҵ�SD������MBR��
	if(fat_buffer[0]!=0XEB&&fat_buffer[0]!=0XE9)  //������0������һ�ֽڲ�Ϊ0XEB��0XE9,�����MBR�����򲻴���
		{   				  
		//printf("��SD������������0ΪMBR\n");
		pr = (partrecord *)((partsector *)fat_buffer)->psPart;//first partition       ��һ����
		hidsec=pr->prStartLBA;   //���ص����� ��DBR����������ƫ��
		//printf("��SD����DBR����������Ϊ=%d\n",hidsec) ;
	}
	else 
	{
		hidsec=0;      //��MBR����������0��ΪDBR
		//printf("��SD��������MBR����������0��ΪDBR����������0��Ϊ�߼�����0.\n"); 
 	} 
	if(SD_ReadDisk(fat_buffer,hidsec,1))return 3;
	//printf("DBR��������ƫ������%d \n",hidsec);
	bs = (bootsector710 *)fat_buffer;
	bpb = (bpb710 *)bs->bsBPB;
	if(bpb->bpbFATsecs)//detemine thd FAT type  do not support FAT12
	{
		FAT32_Enable=0;   					//FAT16
		FATsectors     = bpb->bpbFATsecs;	//FAT��ռ�õ������� 
		FirstDirClust = 2;
	}
	else
	{
		FAT32_Enable=1;   					//FAT32
		FATsectors     = bpb->bpbBigFATsecs;//FATռ�õ������� 
		FirstDirClust = bpb->bpbRootClust;
	}   
	BytesPerSector   = bpb->bpbBytesPerSec;      				//ÿ�����ֽ���
	SectorsPerClust   = (BYTE)bpb->bpbSecPerClust;				//ÿ��������
	FirstFATSector   = bpb->bpbResSectors+hidsec;				//��һ��FAT������
	RootDirCount   = bpb->bpbRootDirEnts;      					//��Ŀ¼����
	RootDirSectors   = (RootDirCount*32)>>9;      				//��Ŀ¼ռ�õ�������
	FirstDirSector   = FirstFATSector+bpb->bpbFATs*FATsectors;	//��һ��Ŀ¼����
	FirstDataSector   = FirstDirSector+RootDirSectors;			//��һ����������
	//printf("ÿ�����ֽ�����%d \n",BytesPerSector);
	//printf("ÿ����������%d \n",SectorsPerClust);
	//printf("��һ��FAT��������%d \n",FirstFATSector);
	//printf("��Ŀ¼������%d \n",RootDirCount);
	//printf("��Ŀ¼ռ�õ���������%d \n",RootDirSectors);
	return 0; 	 
}   
//��FAT��,��ͷ��βCOPY����,���ûCOPY��,��Fat_Over=0,����Ϊ1   
//cluster:�ļ����״�
void Copy_Fat_Table(unsigned long cluster)
{
	u32 bcluster; 
	u8 fat_base;//0~Fat_Table_Size	 
	FAT_TAB.Fat_Over=0;	   
    for(fat_base=0;fat_base<Fat_Table_Size;fat_base++)
	{
		FAT_TAB.Fat_Base_Tab[fat_base]=0;
		FAT_TAB.Fat_Base_Len[fat_base]=0;//ȫ�����
	}
	fat_base=0;
	bcluster=cluster;//��ʼ��,���ܶ�ʧ��.
	FAT_TAB.Fat_Base_Tab[fat_base]=bcluster;
	FAT_TAB.Fat_Base_Len[fat_base]=1;//��1��������,�������µ�bcluster	  
	while(1)
	{
	    bcluster=FAT_NextCluster(bcluster);	   
		if((FAT32_Enable==0&&bcluster==0xffff)||bcluster==0x0ffffff8||bcluster==0x0fffffff)//�ļ����� 
		{
			FAT_TAB.Fat_Over=1;//�ļ�COPY����
			break; 
		} 	 		
		if(bcluster-FAT_TAB.Fat_Base_Tab[fat_base]-FAT_TAB.Fat_Base_Len[fat_base]!=0)//�Ƿ�����ƫ������
		{
			fat_base++;//������һ��BASE
			if(fat_base>=Fat_Table_Size)//�����˻�������Χ,�ļ�̫����/����̫��ɢ��!!!
			{
				FAT_TAB.Fat_Over=0;//�ļ�COPY����
				break; 
			}
			FAT_TAB.Fat_Base_Tab[fat_base]=bcluster;
			FAT_TAB.Fat_Base_Len[fat_base]=1;//��1��������,�������µ�bcluster				
		}else FAT_TAB.Fat_Base_Len[fat_base]++;//��ַƫ��������	   
	}
	//�����
	//printf("Fat_Over:%d\n",FAT_TAB.Fat_Over);
	//printf("Fat_Head_Pos:%d\n",FAT_TAB.Fat_Head_Pos);
	//printf("Fat_Base_Tab[0]:%d\n",FAT_TAB.Fat_Base_Tab[0]);
	//printf("Fat_Base_Tab[1]:%d\n",FAT_TAB.Fat_Base_Tab[1]);
	//printf("Fat_Base_Tab[2]:%d\n",FAT_TAB.Fat_Base_Tab[2]);		 
}	    							    
//��TINY FAT���������cluster����һ���غ�
//cluster:��ǰ�غ�
//����ֵ:cluster,��ʾ������������
//	      ����ֵ,cluster����һ����	   
u32 FatTab_Prev_Cluster(unsigned long cluster)
{
	u8 t;	 
	u32 tempclust;
RSTP:
	for(t=0;t<Fat_Table_Size;t++)
	{
		if(cluster<=(FAT_TAB.Fat_Base_Tab[t]+FAT_TAB.Fat_Base_Len[t]-1)&&cluster>=FAT_TAB.Fat_Base_Tab[t])break;//�����BASE��
	}	  
	if(cluster==FAT_TAB.Fat_Base_Tab[t])//����BASE,�����ǵ�һ��
	{		 
		if(t==0)//���FAT�� ȫ�����껹û�ҵ�
		{					 									    
			if(FAT_TAB.Fat_Head_Pos>0)//��������Χ
			{
				FAT_TAB.Fat_Head_Pos--;
				tempclust=FAT_TAB.Fat_Base_Head[FAT_TAB.Fat_Head_Pos];//������һ��tinyFAT��ı�ͷ
			}else return cluster;   //�޷���������
			Copy_Fat_Table(tempclust);//COPY ��һ��tinyFAT��
			goto RSTP;
			//return FAT_TAB.Fat_Base_Tab[Fat_Table_Size-1]+FAT_TAB.Fat_Base_Len[Fat_Table_Size-1]-1;//������һ���غ�		 
		} 																 
		return FAT_TAB.Fat_Base_Tab[t-1]+FAT_TAB.Fat_Base_Len[t-1]-1;//��һ���غ�
	}else return --cluster;//������һ����   
}	 
//��TINY FAT���������cluster����һ���غ�
//cluster:��ǰ�غ�
//����ֵ:0x0ffffff8,��ʾû�к�������
//	   		 ����ֵ,��Ӧ�غ�
u32 FatTab_Next_Cluster(unsigned long cluster)
{
	u8 t;	 
RESN:
	for(t=0;t<Fat_Table_Size;t++)
	{
		if(cluster<=(FAT_TAB.Fat_Base_Tab[t]+FAT_TAB.Fat_Base_Len[t]-1)&&cluster>=FAT_TAB.Fat_Base_Tab[t])break;//�����BASE��
	}	  
	if(cluster==FAT_TAB.Fat_Base_Tab[t]+FAT_TAB.Fat_Base_Len[t]-1)//����BASE,���������һ����
	{		 
		if((t+1)==Fat_Table_Size)//ȫ�����껹û�ҵ�
		{														  
			if(FAT_TAB.Fat_Over)return 0x0ffffff8;//�ļ�������	 
			if(FAT_TAB.Fat_Head_Pos<Fat_Head_Size-1)//��������Χ
			{		  
				FAT_TAB.Fat_Base_Head[FAT_TAB.Fat_Head_Pos]=FAT_TAB.Fat_Base_Tab[0];//������ǰtinyFAT��ĵ�һ����
				FAT_TAB.Fat_Head_Pos++;
			}
			Copy_Fat_Table(cluster);//COPY ���µ�FAT��
			goto RESN;
		} 
		if(FAT_TAB.Fat_Base_Len[t+1]==0)return 0x0ffffff8;//û�к�������
		return FAT_TAB.Fat_Base_Tab[t+1];//��һ���غ�
	}else return ++cluster;//������һ����   
}	  
//��SD���ϵ�FAT���в�����һ�غ�
//cluster:��ǰ�غ�
//����ֵ:0x0ffffff8,��ʾû�к�������
//	   		 ����ֵ,��һ�غ�				   		    
unsigned long FAT_NextCluster(unsigned long cluster)
{
	DWORD sector;
	DWORD offset;  

	if(FAT32_Enable)offset = cluster/128;//FAT32��FAT����,���ĸ��ֽڱ�ʾһ���ص�ַ.512/4=128
	else offset = cluster/256;			 //FAT16��FAT����,�������ֽڱ�ʾһ���ص�ַ.512/2=256
	if(cluster<2)return 0x0ffffff8;		 //��0,1�������ڴ��
	sector=FirstFATSector+offset;//����ô�ʵ����������

	if(SD_ReadDisk(fat_buffer,sector,1))return 0x0ffffff8;//��ȡFAT��,���������Ƿ���0x0ffffff8
	if(FAT32_Enable)
	{
		offset=cluster%128;//�����������ڵ�ƫ��
		sector=((unsigned long *)fat_buffer)[offset];//u32	
	}
	else
	{
		offset=cluster%256;//�����������ڵ�ƫ��
		sector=((unsigned short *)fat_buffer)[offset];//u16
	}			   
	return (unsigned long)sector;//return the cluste number
}	  
//���غ�ת��Ϊ������
//cluster:Ҫ��Ϊ�����Ĵغ�
//����ֵ:cluster��Ӧ��������
u32 fatClustToSect(u32 cluster)
{
	return FirstDataSector+(DWORD)(cluster-2)*(DWORD)SectorsPerClust;	 
}	 
//���Ƽ�¼����Ϣ
//��Source��������ݸ��Ƶ�Desti����
void CopyDirentruyItem(FileInfoStruct *Desti,direntry *Source)
{
	u8 i;
	u8 t;
	for(i=0;i<8;i++)Desti->F_ShortName[i]=Source->deName[i];//���ƶ��ļ���
	Desti->F_Type         = FileType_Tell(Source->deExtension);
	Desti->F_StartCluster = Source->deStartCluster + (((unsigned long)Source->deHighClust)<<16);//���ù�
	Desti->F_Size         = Source->deFileSize;
	Desti->F_Attr         = Source->deAttributes;
	Desti->F_CurClust     = 0;//����...
	Desti->F_Offset       = 0;//ƫ��0 	

	//FAT�ĴغŲ�����0(��Ŀ¼�غ�)
	if(FAT32_Enable&&Desti->F_StartCluster==0)  
	{																  
		Desti->F_StartCluster=FirstDirClust;//�ı�����غ�.ʹ����ڸ�Ŀ¼���ڴغ�!!
	}   
	if(LongNameFlag)//���ڳ��ļ���
	{
		LongNameBuffer[MAX_LONG_NAME_SIZE-1] = 0;
		LongNameBuffer[MAX_LONG_NAME_SIZE-2] = 0;
		//UniToGB(LongNameBuffer);  //��Unicode����ת��ΪASICII��
		for(i=0;i<80;i++)Desti->F_Name[i] = LongNameBuffer[i];//���Ƴ��ļ���
	}else //���ļ���
	{	//2E:��ǰĿ¼���ڴ�.2E 2E:��Ŀ¼���ڴ�.
		if(Source->deName[0]==0x2e)//�õ�һ����Ŀ¼(�޸�Ϊ:":\")
		{	
			//���游Ŀ¼�غ�   
			//Fat_Dir_Cluster=Desti->F_StartCluster; 	 
			Desti->F_Name[0]=':';
			Desti->F_Name[1]=0x5c;//'\'
			Desti->F_Name[2]='\0';//���������
		}else	    			  //��ͨ�ļ�
		{
			t=7;//�����һ�����ļ�����ʼ,�ҿո�,������
			while(t>0)
			{
				if(Source->deName[t]!=' ')break;
				t--;
			}   			   
			for(i=0;i<t+1;i++)Desti->F_Name[i] = Source->deName[i];//���ƶ��ļ��� 
			if(Desti->F_Attr==0X20&&(Source->deExtension[0]!=0x20))//�鵵�ļ����ļ���׺��Ϊ��
			{ 	   
				Desti->F_Name[i++]='.';//����"."
				for(t=0;t<3;t++)Desti->F_Name[i+t] = Source->deExtension[t];//���ƺ�׺	  
				Desti->F_Name[i+t]='\0';//���������
			}else Desti->F_Name[i]='\0';//���������
		}
	} 															   	  								  
	return ;
}		 
//���Ŀ���ļ��������һ���ļ���
//dir_clust:��ǰĿ¼���ڴغ�
//FileInfo :Ŀ���ļ���ʵ�����(FileInfoStruct��)
//type     :Ҫ���ҵ��ļ�����:1<<0,mp1;1<<1,mp2;1<<2,mp3;1<<3,mp4;1<<4,m4a;1<<5,3gp;
//                           1<<6,3g2;1<<7,ogg;1<<8,acc;1<<9,wma;1<<10,wav;1<<11,mid;
//							 1<<12,flac;1<<13,lrc;1<<14,txt;1<<15,c;1<<16,h;1<<17,file;
//                           1<<18,fon;1<<19,sys;1<<20,bmp;1<<21,jpg;1<<22,jpeg; 
//count    :0,���ص�ǰĿ¼��,�������ļ��ĸ���;��Ϊ��ʱ,���ص�count���ļ�����ϸ��Ϣ
//����ֵ   :1,�����ɹ�.0,����ʧ��
u8 Get_File_Info(u32 dir_clust,FileInfoStruct *FileInfo,u32 type,u16 *count)
{ 			  	   
	DWORD sector;
	DWORD cluster=dir_clust;
	DWORD tempclust;
	unsigned char cnt;
	unsigned int offset;		 
	unsigned short cont=0;//�ļ�������־ <65536
	unsigned char j; //long name fat_buffer offset;
	unsigned char *p;//long name fat_buffer pointer
	direntry *item = 0;
	winentry *we =0;	  
	cont=0;
	LongNameFlag = 0;//��ճ��ļ�����־

	//SD_Init();//��ʼ��SD����������γ�֮���������ʹ��
	//goto SD;
	if(cluster==0 && FAT32_Enable==0)//FAT16��Ŀ¼��ȡ
	{			 
		for(cnt=0;cnt<RootDirSectors;cnt++)
		{
			if(SD_ReadDisk(fat_buffer,FirstDirSector+cnt,1))return 0;//��������    	   
			for(offset=0;offset<512;offset+=32)
			{
				item=(direntry *)(&fat_buffer[offset]);//ָ��ת��
				//�ҵ�һ�����õ��ļ�
				if((item->deName[0]!=0x2E)&&(item->deName[0]!=0x00)&&(item->deName[0]!=0xe5)
				||((item->deName[0]==0x2E)&&(item->deName[1]==0x2E)))//�ҵ�һ���Ϸ��ļ�.����".",ʹ��".."
				{		   
					if(item->deAttributes == 0x0f)//�ҵ�һ�����ļ���
					{
						we = (winentry *)(&fat_buffer[offset]);
						j = 26 *( (we->weCnt-1) & WIN_CNT);//���ļ����ĳ���
                        if(j<MAX_LONG_NAME_SIZE-25)
						{
							p = &LongNameBuffer[j];//ƫ�Ƶ�Ŀ���ַ
							for (j=0;j<10;j++)	*p++ = we->wePart1[j];			
							for (j=0;j<12;j++)	*p++ = we->wePart2[j];
							for (j=0;j<4;j++)	*p++ = we->wePart3[j];	
							if (we->weCnt & 0x40) (*(unsigned int *)p) = 0;  				
							if ((we->weCnt & WIN_CNT) == 1) LongNameFlag = 1;//���һ�����ļ����ҵ���	
						}	    
					}else 
					{  	 										 									 
						if(type&FileType_Tell(item->deExtension))//�ҵ�һ��Ŀ���ļ�
						{
							cont++;//�ļ���������
						 }
						 //���Ҹ�Ŀ¼��,type���͵��ļ�����
						if(*count&&cont==*count)
						{
							////printf("\ncount:%d",*count);
							CopyDirentruyItem(FileInfo,item);//����Ŀ¼��,��ȡ��ϸ��Ϣ 
							return 1;//�ҵ�Ŀ���ļ��ɹ�	 
						}
						LongNameFlag=0;//��ճ��ļ���
					}
				}
			}
		}  				 
	}
	else//�����ļ���/FAT32ϵͳ
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
					||((item->deName[0]==0x2E)&&(item->deName[1]==0x2E)))//�ҵ�һ���Ϸ��ļ�.����".",ʹ��".."
					{				
						if(item->deAttributes == 0x0f) //�õ�һ�����ļ���
						{
							we = (winentry *)(&fat_buffer[offset]);
							j = 26 *( (we->weCnt-1) & WIN_CNT);
							if(j<MAX_LONG_NAME_SIZE-25)
							{
								p = &LongNameBuffer[j];//pָ���ļ����Ĵ�ŵ�ַ
								for (j=0;j<10;j++)	*p++ = we->wePart1[j];			
								for (j=0;j<12;j++)	*p++ = we->wePart2[j];
								for (j=0;j<4;j++)	*p++ = we->wePart3[j];	
								if (we->weCnt & 0x40) (*(unsigned int *)p) = 0;				
								if ((we->weCnt & WIN_CNT) == 1) LongNameFlag = 1;	
							}										    			 
						}	  
						else 
						{
							if(type&FileType_Tell(item->deExtension))//�ҵ�һ��Ŀ���ļ�
							{
								cont++;//�ļ���������
							 }
							 //���Ҹ�Ŀ¼��,type���͵��ļ�����
							if(*count&&cont==*count)
							{
								CopyDirentruyItem(FileInfo,item);//����Ŀ¼��,��ȡ��ϸ��Ϣ  
								return 1;//�ҵ�Ŀ���ļ��ɹ�	 
							}
							LongNameFlag=0;//��ճ��ļ���
						}
					}
				}
			}						  
			tempclust=FAT_NextCluster(tempclust);//������һ���غ�
			if(tempclust==0x0fffffff||tempclust==0x0ffffff8 ||(FAT32_Enable==0&&tempclust==0xffff))break;
		}  
	}
	if(*count==0)
	{
		*count=cont;//�õ��ܹ��ļ���Ŀ
		return 1;   //�����ɹ�,�ҵ�cont�������������ļ���
	}else return 0; //����ʧ��,û�ҵ��ļ�,���߳���
}
//���ļ�
//FileInfo:�ļ���Ϣ
void F_Open(FileInfoStruct *FileInfo)
{
	FileInfo->F_CurClust=FileInfo->F_StartCluster;//��ǰ��Ϊ�״�
	FileInfo->F_Offset=0;//ƫ������Ϊ0
}
//��ȡ512���ֽ�
//FileInfo:Ҫ��ȡ���ļ�
//buf     :���ݻ�����
//����ֵ  :0,����ʧ��,1,�����ɹ�
unsigned char F_Read(FileInfoStruct *FileInfo,u8 *buf)
{	
	DWORD sector;			   		  
	sector=fatClustToSect(FileInfo->F_CurClust);//�õ���ǰ�غŶ�Ӧ��������	   	 		    
	if(SD_ReadDisk(buf,sector+FileInfo->F_Offset,1))return 0;//��������   
	FileInfo->F_Offset++;
	if(FileInfo->F_Offset==SectorsPerClust)	//�صľ�ͷ,����
	{
		FileInfo->F_Offset=0;		    
		FileInfo->F_CurClust=FAT_NextCluster(FileInfo->F_CurClust);//��ȡ��һ���غ�
		if((FAT32_Enable==0&&FileInfo->F_CurClust==0xffff) \
		||FileInfo->F_CurClust==0x0ffffff8||FileInfo->F_CurClust == 0x0fffffff)return 0;//error	    
	} 
	return 1;//��ȡ�ɹ�
} 

//�Ƚ������ַ�����Ȳ�
//���,����1,�����,����0;
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
	if(len1!=len2)return 0;//����� 
	s1-=len1;s2-=len1;
	while(*s1!='\0')
	{
		if(*s1!=*s2)return 0;//����� 
		s1++;s2++;
	}
	return 1;
}  
	 
//����ϵͳ�ļ�
//��ָ��Ŀ¼��,��Ѱһ��ָ�����͵�ָ�����ֵ��ļ�
//cluster:�ļ��еĴغ�!!!
//Name   :�ļ�������
//type   :�ļ�����
//����ֵ :���ļ�����ϸ��Ϣ/��� FileInfo.F_StartCluster=0 ��˵���˴�Ѱ��ʧ��
FileInfoStruct F_Search(u32 cluster,unsigned char *Name,u32 type)
{
	DWORD sector;			 
	DWORD tempclust;
	unsigned char cnt;
	unsigned int offset; 	    
	direntry *item = 0;	  
	FileInfoStruct FileInfo;    			    
	if(cluster==0 && FAT32_Enable==0)//FAT16��Ŀ¼��ȡ
	{			 
		for(cnt=0;cnt<RootDirSectors;cnt++)
		{
			if(SD_ReadDisk(fat_buffer,FirstDirSector+cnt,1))
			{
				FileInfo.F_StartCluster=0;//�������� 
				return FileInfo;   
			}
			for(offset=0;offset<512;offset+=32)
			{
				item=(direntry *)(&fat_buffer[offset]);//ָ��ת��
				//�ҵ�һ�����õ��ļ�
				if((item->deName[0] != 0x00) && (item->deName[0] != 0xe5))//�ҵ�һ���Ϸ��ļ�
				{		   
					if(item->deAttributes != AM_LFN)//���Գ��ļ���	 
					{  	 				 
						CopyDirentruyItem(&FileInfo,item);//����Ŀ¼��,��ȡ��ϸ��Ϣ	   
						if(FileInfo.F_Type&type)//�ҵ�һ�����ʵ�������
						{
						   // //printf("File Name:%s\n",FileInfo.F_Name);
	
							//�ҵ����ļ�,��������ļ����״�
							if(mystrcmp(Name,FileInfo.F_Name))
							{						    
								return FileInfo; 
							}
						} 	  
						LongNameFlag=0;//��ճ��ļ���
					}
				}
			}
		}  				 
	}else//�����ļ���/FAT32ϵͳ
	{
		tempclust=cluster;
		while(1)
		{
			sector=fatClustToSect(tempclust);
			for(cnt=0;cnt<SectorsPerClust;cnt++)
			{
				if(SD_ReadDisk(fat_buffer,sector+cnt,1))
				{
					FileInfo.F_StartCluster=0;//�������� 
					return FileInfo;   
				}
				for(offset=0;offset<512;offset+=32)
				{
					item=(direntry *)(&fat_buffer[offset]);
					if((item->deName[0] != 0x00) && (item->deName[0] != 0xe5))
					{				
						if(item->deAttributes != AM_LFN) //���Գ��ļ���		    
						{  	 				 
							CopyDirentruyItem(&FileInfo,item);//����Ŀ¼��,��ȡ��ϸ��Ϣ	  

							if(FileInfo.F_Type&type)//�ҵ�һ�����ʵ�������
							{	/*										   
								//printf("F_Info->F_Name:%s\n",FileInfo.F_Name);
								//printf("F_Info->F_Type:%d\n",FileInfo.F_Type);
								//printf("F_Info->F_Size:%d\n",FileInfo.F_Size);
								//printf("F_Info->F_StartClusterH:%x\n",FileInfo.F_StartCluster>>8); 	
								//printf("F_Info->F_StartClusterL:%x\n\n",FileInfo.F_StartCluster&0xff); */
								//�ҵ����ļ�,��������ļ����״�
								if(mystrcmp(Name,FileInfo.F_Name))
								{						 
									return FileInfo; 
								}
							} 	  
							LongNameFlag=0;//��ճ��ļ���
						}
					}
				}
			}						  
			tempclust=FAT_NextCluster(tempclust);//������һ���غ�
			if(tempclust==0x0fffffff||tempclust==0x0ffffff8 ||(FAT32_Enable==0&&tempclust==0xffff))break;
		}  
	}		   
	FileInfo.F_StartCluster=0;//�������� 
	return FileInfo;   					    
}	 	 	 						  

	 	 	 						  

