/*******************************************************************************
* 文件名称：mg_card.c	                        
* 说明：本文件为银行卡读卡程序。
* 功能：实现对银行卡的识别
* 修改：无
* 版本：1.0.0
* 作者：YuanDong
* 时间：2009.7.26
*******************************************************************************/	
#include <51reg.h>
#include <string.h>
#include <stdio.h>      /*标准输入输出定义*/


#define	FORWARD	     0x01			//磁卡正向刷卡
#define	BACK		   	 0x02			//磁卡反向刷卡
#define	NO_TRACK2		 0x04			//返回2轨错误
#define NO_TRACK3		 0x08			//返回3轨错误

#define  OK			     0x05
#define  STATE		   0x00

#define  SIZE1_DATA_TRK2       	300		//轨2原始数据BIT长度，协议上最长300
#define  SIZE2_DATA_TRK3       	1000	//轨3原始数据BIT长度，协议上最长1000
#define  SIZE3_CARD_NUM2       	50		//卡数据(由BIT位按标准转换后的数据字符）长度
#define  SIZE4_CARD_NUM3       	120		//卡数据(由BIT位按标准转换后的数据字符）长度

sbit B_CLK1=P3^2;  
sbit B_CLK2=P3^3;
sbit B_DATA1=P2^5;
sbit B_DATA2=P2^6;


struct mgcd_dev    //磁卡数据结构体
{
	unsigned char	data_trk2[SIZE1_DATA_TRK2];  //轨2 原始数据    第2磁道数据编码最大记录长度为40个字符40*5=200
	unsigned char	data_trk3[SIZE2_DATA_TRK3];  //轨3 原始数据    第3磁道数据编码最大记录长度为107个字符107*5=535
  char card_num2[SIZE3_CARD_NUM2];           //经过处理的轨2数据存储到card_num2[50]
  char card_num3[SIZE4_CARD_NUM3];         //经过处理的轨3数据存储到card_num3[50]  
  int  track2_num;       		       				//记录的是轨2数据记录占用的空间长度  (处理之后的长度)
	int  track3_num;	      		    				//记录的是轨3数据记录占用的空间长度（处理之后的长度)
	unsigned char  result_value;    			  //记录状态为FORWARD 或BACK 或 NO_TRACK2 或 NO_TRACK3 
}g_BrushCard;


static char direction_check(void);   
static unsigned char convert_track(void);
static int convert_forward(char *data, int len, int track);
static int convert_back(char *data,int len, int track);
static char ChangeData(char data);
static void ShowTrack2(char *back_track);
static void ShowTrack3(char *back_track);
static char check(char data);

/*****************************************************************************************
*函数名称：convert_track(void)
*函数功能：原始数据处理
*入口函数：无
*出口函数：g_BrushCard->result_value
*****************************************************************************************/
static unsigned char convert_track(void)  //对原始数据进行处理 此函数不需要改
{
	int i,trk2;
	unsigned char tmp[300];        //数据存放的临时数组
	memcpy(tmp,g_BrushCard->data_trk2,300);
	char direction;
	direction = direction_check();				 //对刷卡方向进行判断
	trk2=g_BrushCard->track2_num;

	if(direction == FORWARD)
	{
		if(g_BrushCard->track2_num = convert_forward((char *)g_BrushCard->data_trk2, g_BrushCard->track2_num,TRACK2))
			goto justice;
		for(i=0 ;i < trk2+1 ; i++)
		{
			memcpy(g_BrushCard->data_trk2+i,tmp+trk2-1-i,sizeof(unsigned char));
		}	

		if(!(g_BrushCard->track2_num = convert_forward((char *)g_BrushCard->data_trk2, trk2,TRACK2)))
				g_BrushCard->result_value |= NO_TRACK2;
		if(!(g_BrushCard->track3_num = convert_forward((char *)g_BrushCard->data_trk3, g_BrushCard->track3_num,TRACK3)))
			g_BrushCard->result_value |= NO_TRACK3;
	}
	else if(direction == BACK)
	{
		if(!(g_BrushCard->track2_num = convert_back((char *)g_BrushCard->data_trk2, g_BrushCard->track2_num,TRACK2)))
			g_BrushCard->result_value |= NO_TRACK2;

		if(!(g_BrushCard->track3_num = convert_back((char *)g_BrushCard->data_trk3, g_BrushCard->track3_num,TRACK3)))
			g_BrushCard->result_value |= NO_TRACK3;
	}
justice:	if((g_BrushCard->track2_num == 0 && g_BrushCard->track3_num == 0)
	|| g_BrushCard->track2_num > 0x28 || g_BrushCard->track2_num < 0x10
	|| g_BrushCard->track3_num > 0x6B || g_BrushCard->track2_num < 0x12)	//轨2数据16－40 ,轨3数据18－107 
	{
		g_BrushCard->state = STATE;		//数据组合错误返回

		return 0;
	}
	else							//数据组合正确返回
	{
		g_BrushCard->state = OK;
		ShowTrack2(g_BrushCard->card_num2);
    ShowTrack3(g_BrushCard->card_num3);
	}

	g_BrushCard->result_value |= direction;

	return g_BrushCard->result_value;
}

/*****************************************************************************************
*函数名称：direction_check(void)
*函数功能：刷卡方向判别
*入口函数：无
*出口函数：FORWARD
*****************************************************************************************/
static char direction_check(void)  //此函数不需要改
{    
	int i = 0,num = 0;
	char ascii_data = 0x00; 
	while(1)
	{
		if(g_BrushCard->data_trk2[num] == 0x00)								//去除前面的引导串
		{
			for(i = 0; i < 5;i++)
			{
				if(g_BrushCard->data_trk2[num++] & TRACK2)  					
					ascii_data |= (0x00<<i); 										
				else
					ascii_data |= (0x01<<i);					 					
			}
			if(ascii_data == 0x0b)  											
				return FORWARD;    
			else
			{
				break;
			}
		}
		num++;																		
	}
	
	num = g_BrushCard->track2_num - 1;  				 //反刷
	ascii_data=0x00;
	
	while(1)
	{
		if(g_BrushCard->data_trk2[num] == 0x00)		//去除前面的引导串
		{
			for(i = 0;i < 5;i++)
			{
				if(g_BrushCard->data_trk2[num--] & TRACK2)
					ascii_data |= (0x00<<i);
				else
					ascii_data |= (0x01<<i);
			}
			if(ascii_data == 0x0b)
				return BACK;        
			else
			{
				printf("\nRead card number error!\n");
				break;
			}
		}
		num--;
	}
}

/*****************************************************************************************
*函数名称：convert_forward(char *data, int len, int track)
*函数功能：正向数据组合
*入口函数：data  len  track
*出口函数：i
*****************************************************************************************/
static int convert_forward(char *data, int len, int track) //正向数据组合（原始数据，长度，轨道号）此函数不需要改
{ 
	int i = 0,now_postion = 0,real_num = 0;
	char *temp;																			   //记录当前指向的字符
	char ascii_data = 0x00, tmp_data[107], track_data;
	
	track_data = track;
	temp = data;
	
	while(1)
	{
		if(*temp&track_data)															//去除前面的引导串
		{
			temp ++;
			now_postion ++;
			if(now_postion > len)
				return 0;
		}
		else
		{
			while(ascii_data != 0x1f)												//前一次数据不为结束符就继续读取
			{				
				ascii_data = 0x00;

				for(i = 0;i < 5;i++)
				{
					if(*temp & track_data)
						ascii_data |= (0x00<<i);
					else
						ascii_data |= (0x01<<i);

					temp ++;
				}
				if(ascii_data == 0x00)
					break;

				if(check(ascii_data))
					tmp_data[real_num] = ascii_data;
				else
					return 0;

				real_num ++;
			}
			memset(data,0x00,len);
			if(real_num < 0x10)
				return 0;
			i = 0;
			do	{
					*(data + i) = tmp_data[i];
				}while((tmp_data[i++] != 0x1f)&&(i<120));
          
			return i;
		}
	}
}


/*****************************************************************************************
*函数名称：convert_back(char *data,int len, int track)
*函数功能：反向数据组合
*入口函数：data  len  track
*出口函数：i
*****************************************************************************************/
static int convert_back(char *data,int len, int track) //反向数据组合 此函数不需要改
{
	int i = 0,now_postion = 0,real_num = 0;
	char *temp;																		      //记录当前指向的字符
	char ascii_data = 0x00, tmp_data[107], track_data;

	track_data = track;
	temp = data + len - 1;
	
	while(1)
	{
		if(*temp&track_data)															//去除前面的引导串
		{
			temp --;
			now_postion ++;
			if(now_postion > len)
				return 0;
		}
		else
		{
			while(ascii_data != 0x1f)
			{				
				ascii_data = 0x00;
				for(i = 0; i < 5; i++)
				{
					if(*temp & track_data)
						ascii_data |= (0x00<<i);
					else
						ascii_data |= (0x01<<i);

					temp --;
				}

				if(ascii_data == 0x00)
					break;

				if(check(ascii_data))
					tmp_data[real_num] = ascii_data;
				else
					return 0;

				real_num ++;
			}
			memset(data,0x00,len);

			if(real_num < 0x10)
				return 0;

			i = 0;
			do{
				*(data + i) = tmp_data[i];
			}while((tmp_data[i++] != 0x1f)&&(i<120));

			return i;

		}
	}
}

/*****************************************************************************************
*函数名称：ChangeData(char data)
*函数功能：数据转换
*入口函数：data  
*出口函数：data
*****************************************************************************************/
static char ChangeData(char data)  //数据转换	
{  
	data &= (~0x10);
	data = data + 0x30;
	return data;
}

/*****************************************************************************************
*函数名称：ShowTrack2(char *back_track)
*函数功能：将轨2中间数据进行组合转换
*入口函数：back_track
*出口函数：无
*****************************************************************************************/
static void ShowTrack2(char *back_track)			//将中间数据进行组合转换
{
	int i = 0;
	
	if(g_BrushCard->data_trk2[0] != 0x0b)
		return;

	for(i = 0; i<g_BrushCard->track2_num; i++)	
	{
		*(back_track + i ) = ChangeData(g_BrushCard->data_trk2[i]);
	}

	*(back_track + i) = '\0';  //加字符串的结束符
   
}		
/*****************************************************************************************
*函数名称：ShowTrack3(char *back_track)
*函数功能：将轨3中间数据进行组合转换
*入口函数：back_track
*出口函数：无
*****************************************************************************************/	
static void ShowTrack3(char *back_track)
{
 	int i;
	
	if(g_BrushCard->data_trk3[0] != 0x0b)
		return;

	for(i = 0; i<g_BrushCard->track3_num; i++)
	{
		*(back_track + i ) = ChangeData(g_BrushCard->data_trk3[i]);
	}

	*(back_track + i) = '\0';
}
/*****************************************************************************************
*函数名称：check(char data)
*函数功能：检查奇偶校验正否正确
*入口函数：data  
*出口函数：OK/0
*****************************************************************************************/											
static char check(char data)		//检查奇偶校验正否正确 5位为一个组合，第一位校验后四位
{
	int num = 0,i = 0;
	
	for(i= 0; i < 8; i++)
	{
		if(data&(0x01 << i))
		num ++;
	}

	if(num%2)
		return OK;
	else
		return 0;
}	

/*****************************************************************************************
*函数名称：mgcddata_init(void) 
*函数功能：卡数据结构体初始化
*入口函数：无  
*出口函数：无
*****************************************************************************************/
static void mgcddata_init(void)  
{
  uint i;
  for(i=0;i<SIZE1_DATA_TRK2;i++)
     	g_BrushCard->data_trk2[i]=0;   //轨二原始数据初始化
  for(i=0;i<SIZE1_DATA_TRK3;i++)
     	g_BrushCard->data_trk3[i]=0;   //轨三原始数据初始化
  for(i=0;i<SIZE3_CARD_NUM2 ;i++)  	
      g_BrushCard->card_num2[i]=0;   //轨二数据初始化
  for(i=0;i<SIZE3_CARD_NUM2 ;i++)  	
      g_BrushCard->card_num2[i]=0;   //轨三数据初始化
      
  g_BrushCard->track2_num = 0;
	g_BrushCard->track3_num = 0;
	g_BrushCard->result_value = 0;
	g_BrushCard->state = 0;
            
}
/*****************************************************************************************
*函数名称：mgcd_data2()
*函数功能：轨道2数据中断处理
*入口函数：无
*出口函数：无
*****************************************************************************************/
static mgcd_data2() interrupt 0 using 2  //中断0处理函数,使用第二组寄存器  
{

  EX0=0; //关中断0
	
	if(g_BrushCard->track2_num < SIZE1_DATA_TRK2)     //还未读满300个长度
	{ 
		g_BrushCard->data_trk2[g_BrushCard->track2_num++] = B_DATA2;	 //将数据口的数据读出来暂存
	}
  
  EX0=1; //开中断0
}
/*****************************************************************************************
*函数名称：mgcd_data3()
*函数功能：轨道3数据中断处理
*入口函数：无
*出口函数：无
*****************************************************************************************/
static mgcd_data3() interrupt 2 using 1  //中断1处理函数,使用第二组寄存器  
{

  EX1=0; //关中断1
	
	if(g_BrushCard->track3_num < SIZE1_DATA_TRK3)     //还未读满1000个长度
	{ 
		g_BrushCard->data_trk3[g_BrushCard->track3_num++] = B_DATA3;	 //将数据口的数据读出来暂存
	}
  
  EX1=1; //开中断1
}

/*****************************************************************************************
*函数名称：main(void) 
*函数功能：端口初始化
*入口函数：无  
*出口函数：无
*****************************************************************************************/
void main(void)     
{
	EA=0;   //关CPU中断
	 
  B_DATA1=0;
  B_DATA2=0;

  IT0=0;  //轨一低电平触发中断
  EX0=1;  //外部中断0允许 
  
  IT1=0;  //轨二低电平触发中断
  EX1=1;  //外部中断1允许 
 
  mgcddata_init(void);  

  EA=1;   //开CPU中断
	return;
}