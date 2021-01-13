/*************************************************************
                      平面旋转LED程序
单片机 STC12C5A32S2  
运用无线供电方法 旋转起来非常安静
字模软件用的PC2002
实现功能：1、平面显示字
		  2、平面显示数字时钟 年月日 星期 如果带了DS18B20 还能显示温度 （时钟可调 时钟芯片用DS1302 带后备电池 掉电时钟继续走时）
		  3、平面显示模拟表盘时钟 12、3、6、9显示 指针带箭头（如果初次上电表盘会自适应旋转速度，当感觉表盘稳定时 按下按键TEST 以保存参数，
		  	 不再自适应调整，节省CPU运算时间，如果表盘有轻微抖动可以通过遥控器的“快进键“和“快退键”对单列时间进行调整，调整后保存到DS1302RAM中）
		  4、表轮时钟模式，显示时分秒 以及显示表轮
		  5、图片显示模式 共8张 可通过红外遥控按键 “+”或者“-” 来切换
		  6、动画效果（由上位机软件制作动画）
		  
程序编写：Fucp 
年月日：13-8-29

套件出售：http://59tiaoba.taobao.com
博客地址：http://hi.baidu.com/fcping/blog/item/71aaa1ec9c3743f2cf1b3eaa.html?timeStamp=1323178049250
***************************************************************/
//#include "NEW_8051.H"
#include "task.h"

#include <stddef.h>

#define ucNumRows 108 //定义一周显示字个数 一个字16列 108/16=8个字



uchar Delay=1 ;
bit BIT_timeout=0;
//bit Scan_bit=0;
uint uitime=0;
uint S=0;
uint uiicount=0;
uint uiCountFontNumber;
uchar ucMode=1;
data uint uiicountTwo=0;

uchar ucPCA0_TimeCount;
bit Time0_flag=0;	//定时器T0中断标志位

uint addr;
uchar OffsetAdder=0;//图片地址；
bit AutoSwitch=1;
uchar DelayTimeCount=0;
uchar  Row=0;
uint S0,T,D;		//计数用的变量
uchar DISP_LINE=0;
uchar DISP_LINEE=0;
uchar k;
void delay_200ms(void) ;
uchar code liushui[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};	// 方便移位 流水测试

/***************模拟表盘变量**************/
// uint DISP_LINE=0;
 uchar DISP_LINE_ADJ=0;
 uchar DISP_TIME_ADJ=0;
 uchar Time0_count=0;
 uchar ucAdder=0;

 uchar code TAB_12369[]=
 {

	0xFF,0x03,0xFF,0xB3,0x6B,0x6B,0x9B,0xFF,		
	0x8F,0x77,0x7F,0x8F,0x7F,0x77,0x8F,0xFF,//3
	0xFF,0xFF,0x9F,0x6D,0x6D,0x6B,0x87,0xFF,//6	
	0x9F,0xEF,0xF7,0x87,0x77,0x77,0x8F,0xFF,///9


 };
/*********延时子程序**********/
void delay(unsigned char n)	//每列显示的时间
{
	unsigned char a,b;
	for(;n>0;n--)
	{    	
		for(b=100;b>0;b--)
        for(a=2;a>0;a--);
	}
}

/*********PCA中断子程序**********/
void PCA() interrupt 7	//PCA定时器	调时闪烁
{
    if( CCF0 )
	{
		CCF0 = 0;
		CL = 0;
    	CH = 0;
		ucPCA0_TimeCount++;
		if(ucPCA0_TimeCount>12)
		{
			ucPCA0_TimeCount=0;	//调时闪烁
			if(ucMode==2)
			 {
			 	flag=~flag;
			 }
			 
		}
	}
}
/************************************/
void Timer0Interrupt(void) interrupt 1
{			 
    Time0_flag=1;	           //定时中断标志位置1;
	TH0=-Pt/256;TL0=-Pt%256;   //设置定时器T0的初设值
	DISP_LINE++; 
	DISP_LINEE++;                   //计数

}
/************************************************************/
//图片切换以及模拟表盘显示函数
void display_pic()
{
	uchar date1,date2,date3,date4;
	if(DISP_LINE<180)
	{
		if(Time0_flag)
		{
		 	Time0_flag=0;
			OEA=OEB=OEC=1;
			P2=0XFF;
			LED=0;
			if(ucMode==4)
			{
					 if(DISP_LINEE==180)
					 DISP_LINEE=0;
					if((DISP_LINEE>=0)&&DISP_LINEE<8)	//分 个位
					{
						Send_data_C(shuzi[Cent%10][DISP_LINEE]);	
						OEC=0;	
					}
					else if(DISP_LINEE>7&&DISP_LINEE<16)	//两点
					{
						Send_data_C(shuzi[10][DISP_LINEE-8]);	
						OEC=0;	
					}
					else if(DISP_LINEE>15&&DISP_LINEE<24)	//秒 十位
					{
						Send_data_C(shuzi[Sec/10][DISP_LINEE-16]);	
						OEC=0;	
					}
					else if(DISP_LINEE>23&&DISP_LINEE<32)	//秒 个位
					{
						Send_data_C(shuzi[Sec%10][DISP_LINEE-24]);	
						OEC=0;	
					}
					else if((DISP_LINEE>147)&&(DISP_LINEE<156))
					{
						ucAdder=DISP_LINEE-148;
						Send_data_C(shuzi[Hour/10][ucAdder]);//时 十位	
						OEC=0;
					}
					else if((DISP_LINEE>155)&&(DISP_LINEE<164))	
					{
						ucAdder=DISP_LINEE-156;
						Send_data_C(shuzi[Hour%10][ucAdder]);//时 个位	
						OEC=0;	
					}
					else if((DISP_LINEE>163)&&(DISP_LINEE<172))	//两点
					{
						ucAdder=DISP_LINEE-164;
						Send_data_C(shuzi[10][ucAdder]);	
						OEC=0;	
					}
					else if(DISP_LINEE>171&&DISP_LINEE<180)	//分 十位
					{
						ucAdder=DISP_LINEE-172;
						Send_data_C(shuzi[Cent/10][ucAdder]);	
						OEC=0;	
					}
					Round_table(DISP_LINEE,Hour,Cent,Sec);
			}
			if(ucMode==3)
			{
				  //DISP_LINEE=DISP_LINEE-1;
				      //标整点,以及显示数字12,3,6,9
					  if(DISP_LINEE==180)
					 DISP_LINEE=0;
			      if ( (DISP_LINEE >= 175) || (DISP_LINEE <= 3))  //12点
			      {
			       ucAdder=DISP_LINEE+4 ;
			       if ( ucAdder>=180) ucAdder=ucAdder-180 ;
			      }
			      else if ( (DISP_LINEE >= 41) && (DISP_LINEE <= 48)) //3点
			      {
			       ucAdder=DISP_LINEE-41+8*1 ;
			      }
			      else if ( (DISP_LINEE >= 86) && (DISP_LINEE <= 93)) //6点
			      {
			       ucAdder=DISP_LINEE-86+8*2 ;
			      }
			      else if ( (DISP_LINEE >= 131) && (DISP_LINEE <= 138)) //9点
			      {
			       ucAdder=DISP_LINEE-131+8*3 ;
			      }
				  else
				  {
					 ucAdder=250;
					/*************形成表盘*******************/
				   switch (DISP_LINEE)    
			       {
				        case 180*1/12 :    //1点
				        case 180*2/12 :    //2点
				        case 180*4/12 :    //4点
				        case 180*5/12 :    //5点
				        case 180*7/12 :    //6点
				        case 180*8/12 :    //7点
				        case 180*10/12 :   //10点
				        case 180*11/12 :   //11点
				          //LED=0;
						  Send_data_C(0X0F);
						  OEC=0;
				         break;
			       }
				   }
				   if ( ucAdder < 32 )
				    {
						Send_data_C(TAB_12369[ucAdder]) ; //查表显示12,3,6,9
						OEC=0;
					}
			   /****************************************/   
			   	  //显示指针"时"
			//	   i = Hour ;
			//       j = Hour ;
			//      if ( ++i > 179 ) i=0 ;    //i+1,结果>179,则清零
			//      if ( --j > 179 ) i=179 ;   //j-1,结果为负,则重新赋值179
				if(( (Hour-2)<=DISP_LINEE)&&((Hour+2)>=DISP_LINEE) )
				{
					if(((Hour-1)==DISP_LINEE)||((Hour+1)==DISP_LINEE))
					{
						P2=0XFF;
						Send_data_A(0XBF);
						OEA=0;
					}
					else if(((Hour-2)==DISP_LINEE)||((Hour+2)==DISP_LINEE))
					{
						P2=0XFF;
						Send_data_A(0XDF);
						OEA=0;
					}	
				}
			   	if(Hour==DISP_LINEE)//||(DISP_LINEE==i)||(DISP_LINEE==j
			    {
			        
			        P2=0X80 ;
					Send_data_A(0X00);
					OEA=0;
			
			
			    }    
			    //显示指针"分"
				if(( (Cent-2)<=DISP_LINEE)&&((Cent+2)>=DISP_LINEE) )
				{
					if(((Cent-1)==DISP_LINEE)||((Cent+1)==DISP_LINEE))
					{
						Send_data_A(0XFF);
						Send_data_B(0XFB);
						P2=0XFF;
						OEA=OEB=0;
					}	
					else if(((Cent-2)==DISP_LINEE)||((Cent+2)==DISP_LINEE))
					{
						Send_data_A(0XFF);
						Send_data_B(0XFD);
						P2=0XFF;
						OEA=OEB=0;
					}
					
				}
				if(Cent==DISP_LINEE)
			    {
			        //Send_data_B(0X00);
					Send_data_A(0X00);
					Send_data_B(0XF0);
					P2=0X80;
					OEA=OEB=0;
			       	
			    }
				//显示指针"秒"
				if(( (Sec-2)<=DISP_LINEE)&&((Sec+2)>=DISP_LINEE) )
				{
					if(((Sec-1)==DISP_LINEE)||((Sec+1)==DISP_LINEE))
					{
						Send_data_B(0XBF);
						Send_data_A(0XFF);
						P2=0XFF;
						OEA=OEB=0;
					}
					else if(((Sec-2)==DISP_LINEE)||((Sec+2)==DISP_LINEE))
					{
						Send_data_B(0XDF);
						Send_data_A(0XFF);
						P2=0XFF;
						OEA=OEB=0;
					}
						
				}
			    if(Sec==DISP_LINEE)
			    {
			        Send_data_B(0X00);
					Send_data_A(0X00);
					P2=0X80;
					OEA=OEB=0;
			       
			    }
				//DISP_LINEE=DISP_LINEE+1;
		
			}
			else if(ucMode==5)//11张图片显示
				{
					   
					date1=byte_read(OffsetAdder*720+0x3A02+DISP_LINE*4);
					date2=byte_read(OffsetAdder*720+0x3A03+DISP_LINE*4);
					date3=byte_read(OffsetAdder*720+0x3A04+DISP_LINE*4);
					date4=byte_read(OffsetAdder*720+0x3A05+DISP_LINE*4);	
					dis_picture(date3,date4,date1,date2);
					//	DISP_LINE=DISP_LINE+1;
				}
				else if(ucMode==6)//动画
				{
						//DISP_LINE=DISP_LINE+2;
//						date1=two_heart[DISP_LINE+OffsetAdder*180][0];
//						date2=two_heart[DISP_LINE+OffsetAdder*180][1];
//						date3=two_heart[DISP_LINE+OffsetAdder*180][2];
//						date4=two_heart[DISP_LINE+OffsetAdder*180][3];
//						dis_picture(date1,date2,date3,date4);
						//DISP_LINE=DISP_LINE-2;
					date1=byte_read(OffsetAdder*720+0x5202+DISP_LINE*4);
					date2=byte_read(OffsetAdder*720+0x5203+DISP_LINE*4);
					date3=byte_read(OffsetAdder*720+0x5204+DISP_LINE*4);
					date4=byte_read(OffsetAdder*720+0x5205+DISP_LINE*4);	
					dis_picture(date1,date2,date3,date4);
				}
//				else if(ucMode==7)//蝴蝶
//				{
//						//DISP_LINE=DISP_LINE+2;
//						date1=hudie[DISP_LINE+OffsetAdder*180][0];
//						date2=hudie[DISP_LINE+OffsetAdder*180][1];
//						date3=hudie[DISP_LINE+OffsetAdder*180][2];
//						date4=hudie[DISP_LINE+OffsetAdder*180][3];
//						dis_picture(date1,date2,date3,date4);
//						//DISP_LINE=DISP_LINE-2;
//				}
		}		
	}
	else 	
	{
			OEA=OEB=OEC=1;
			P2=0XFF;
			LED=0;

	}
}

/*********中断子程序**********/
void int0() interrupt 0	//使用外部中断0
{
	if((ucMode==0x01)||(ucMode==0x02))
	{
		BIT_timeout=1;
	}
	else
	{		
		if(Auto==1)
		{
			D+=(DISP_LINE-178);   //修正值
	   		Pt=600+D; 
		}      //得到定时器T0的初设值
		TH0=-Pt/256;
		TL0=-Pt%256;   //设置定时器T0的初设值
		DISP_LINE=0;   //计数器清零，将重新计数
		DISP_LINEE=128;	
		switch (ucMode)
		{
			case 0x06:
					if(++Row>=2)
					{
					   Row=0;
						OffsetAdder=OffsetAdder+1;
					   if(OffsetAdder>uiFontNumber_D)
						  OffsetAdder=0;
					}
				break;
			case 0x05:
				if(++Row>=100)
				{
				   Row=0;
				   if(AutoSwitch==1)
				   {
				   		OffsetAdder=OffsetAdder+1;
				   		if(OffsetAdder>uiFontNumber_P)
					 	OffsetAdder=0;
					}
				}	 
				break;
			case 0x03:
				du1302();//获取时间
				Sec=Sec/16*10+Sec%16 ;
        	    Cent=Cent/16*10+Cent%16 ;
        		Hour=Hour/16*10+Hour%16 ;
				if(Hour>11)
				{
					Hour=Hour-12;	
				}
			//	Hour=12-Hour;
				Sec=Sec*3;//秒针定位="秒"*3
				Hour=(Hour*15)+(Cent/4);//时针定位="时"*15+"分"/4
				Cent=Cent*3;//分针定位="分"*3	
				break;
			case 0x04:
				du1302();//获取时间
				Sec=Sec/16*10+Sec%16 ;
        	    Cent=Cent/16*10+Cent%16 ;
        		Hour=Hour/16*10+Hour%16 ;
				if(Hour>12)
				{
					Hour=Hour-12;	
				}
				break;
			default:
				break;
		}
		
	}		
}
/********************************/

/***************************************/
void OS_ALLRun(void)
{	
		if( new_code ) //有红外按键
		{
			//Send_data(key_code);
			new_code=0;
			switch( key_code ) //根据不同的按键值执行不同的动作
			{
				
				case 0x44:   //第2行第一个
					Auto=~Auto;
					if(Auto==0)
					{
						write_1302Data(DISP_TIME_adder_L,Pt);//写入DS1302 RAM中保存
						write_1302Data(DISP_TIME_adder_H,Pt>>8);//写入DS1302 RAM中保存
						write_1302Data(Auto_adder,1);//写入DS1302 RAM中保存	
					}

				break;
				case 0x07://第三行第一个
				
				 if((ucMode==3)||(ucMode==4)||(ucMode==5))
				 {				 	
					Pt++;
					write_1302Data(DISP_TIME_adder_L,Pt);//写入DS1302 RAM中保存
					write_1302Data(DISP_TIME_adder_H,Pt>>8);//写入DS1302 RAM中保存

				 }
				 else
				 {
				 	DelayTimeCount++;
				 }
				break;
	
				case 0x09:
				
				 if((ucMode==3)||(ucMode==4)||(ucMode==5))
				 {
				 	
					Pt--;
					write_1302Data(DISP_TIME_adder_L,Pt);//写入DS1302 RAM中保存
					write_1302Data(DISP_TIME_adder_H,Pt>>8);//写入DS1302 RAM中保存
				
				 }
				 else
				 {
				 	if(DelayTimeCount>0)
					{
						DelayTimeCount--;
						
					}
				 }
					
				break;
			   /*********************************/
				case 0x0C:
					ucMode=0x01;//平面显示字模式
					CR=0;
					TR0=0;
					P2=0XFF;
					OEA=1;
				break;

				case 0x18:
					TR0=0;
					CR=0;
					ucMode=0x02;//数字钟模式
					P2=0XFF;
				break;

				case 0x5E:
			
					//Pt=DISP_TIME_SET=R1302(DISP_TIME_adder+1);//读取单列显示时间

					ucMode=0x03;//指针时钟模式
					TR0=1;
			 		//CR=1;				 
					
				break;
				case 0x08:
					ucMode=0x04;//圆盘时钟模式
					TR0=1;
			 		//CR=1;
					
				break;
				case 0x1C:
//					DISP_TIME_SET=R1302(DISP_TIME_adder+1);//读取单列显示时间
//					if((DISP_TIME_SET>200)||(DISP_TIME_SET<50)) //防止值过大	过小
//					{
//						DISP_TIME_SET=80;	
//					}
					ucMode=0x05;//图片显示模式
					OffsetAdder=0;//偏移地址为0
					TR0=1;
			 		CR=0;
				break;
				/********************************************************/
				case 0x5A:
//					DISP_TIME_SET=R1302(DISP_TIME_adder+1);//读取单列显示时间
//					if((DISP_TIME_SET>200)||(DISP_TIME_SET<50)) //防止值过大	过小
//					{
//						DISP_TIME_SET=80;	
//					}
					
					OffsetAdder=0;//偏移地址为0
					TR0=1;
			 		CR=0;
					ucMode=0x06;//简单动画显示模式
				break;
					/********************************************************/
				case 0x42:
					OffsetAdder=0;//偏移地址为0
					TR0=1;
			 		CR=0;
					ucMode=0x07;//简单动画显示模式
				break;
				/*********************************/
				case 0x40:	 //调时加
				    if(ucMode==5)
					{
						if(OffsetAdder<uiFontNumber_P)//最多8张图
						OffsetAdder=OffsetAdder+1;
					}
					else if(ucMode==2)
					Set(id,1);
				break;

				case 0x19: //调时减
					 if(ucMode==5)
					{
						if(OffsetAdder>0)//8张图
							OffsetAdder=OffsetAdder-1;
						
					}
					else if(ucMode==2)
					Set(id,0); 
				break;
				
				case 0x15://调时切换
						if(ucMode==5)
						{
							AutoSwitch=~AutoSwitch;
						}
						else
						{
							id++;						
							//CCAPM0 = 0x49; //开PCA0中断
							//CCAPM1 = 0x00; //关PCA1中断
							CR=1;//启动PCA计数
	   						if(id>4)
							{
	    						id=0;
								CR=0;//关闭PCA计数
							//	CCAPM0 = 0x00;//关PCA0中断
							}
						}
				break;
					case 0x4A://时钟初始化
						Set1302(starts_time);    //初始化 
						W1302(0x8e,0x00); //控制命令,WP=0,写操作                
						W1302(0x90,0xa5); //打涞二级�  一个二级管串联一个2K玷 
//						write_1302Data(DISP_TIME_adder,130);
				break;

				default: break;
			}
		}
	if((ucMode==3)||(ucMode==4)||(ucMode==5)||(ucMode==6)||(ucMode==7))
	{
		display_pic();
	}
	else if(BIT_timeout)//起始点
 	{			  
		BIT_timeout=0;
		Scan_bit=1;
		//DelayTime=TimeCount/(ucNumRows+60);	
		//TimeCount=0;	//延时周期计数清零
		switch (ucMode)
		{
			case 0x01://平面显示字模式
				//uiCountFontNumber++; 	
					P2=0XFF;
				Send_data_A(0xFF);				           
            	if( ++uiCountFontNumber >uiFontNumber) //uiFontNumber
	            {
	                
					uiCountFontNumber = 0;
					
	            }            
	            for( uiicount = uiCountFontNumber;uiicount<ucNumRows+uiCountFontNumber;uiicount++ )
	            {                               
	                				
					//Send_data_C(zimo_num1[uiicount*2]);//读取数组里的字幕数据
	                //Send_data_B(zimo_num1[uiicount*2+1]);
					Send_data_C(byte_read(2+uiicount*2));	//读取内部EEPROM字幕数据 数据在2地址后 所以要加上2
					Send_data_B(byte_read(2+uiicount*2+1));
					
					OEB=OEC=0;
					delay(2);
					OEB=OEC=1;
	               if(BIT_timeout)
				   {
				   	  
					  break;
				   }
				}
				break;
			case 0x02:	//数字时钟模式
				du1302();
				read_temp();
				display();
				break;
			/*********************/
		
			default: break;
		}
		   
	}

//	if(Scan_bit==0)	//如果红外对管有问题（起点检测不到） 旋转起来只有流水灯现象	 流水灯可以检测灯焊接的是否有问题
//	{
//			OEA=OEB=OEC=0;				
//			for(k=0;k<8;k++)
//			{				
//				ES=0;
//				Send_data_A(~liushui[k]);
//				P3=0X0F;
//				Send_data_B(~liushui[k]);
//				Send_data_C(~liushui[k]);
//				ES=1;
//				P2=~0x80>>k;			
//			    delay_200ms();

//			}				
//		
//	}
}
/*********************************************************/
void delay_200ms(void)
{
    unsigned char a,b,c;
    for(c=164;c>0;c--)
        for(b=212;b>0;b--)
            for(a=25;a>0;a--);
}
/*********************************************************************************/
/*************************************************************************************
************************************************************************************
***********************                                     ***************************
***********************    http://59tiaoba.taobao.com       ***************************
***********************                                     ***************************
**************************程序编写：Fucp ******************************
**********************************************************************************/