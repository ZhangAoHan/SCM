
#include "task.h"
bit flag;
uchar id;
uchar Tem=32;
/*********延时子程序**********/
void delay1(void)//18.432M 180us
{
	uchar a,b;
     for(b=115;b>0;b--)
        for(a=5;a>0;a--);
}
/*********************************************/
void OE_open(void)
{
	OEB=OEC=0;	
}
void OE_close(void)
{
	OEB=OEC=1;	
}
/**********************************************************/
void display(void)	
{	
	uchar i; 
/******************显示时分秒数据**************************/
/**************************************************/   	 
	if((flag==1)&&(id==1))    //实现调时 的闪烁位 （以下同） 
	{
		for(i=0;i<8;i++) 	  //这里用16个LED实现时间显示（以下同）
		{	 
			OE_close(); //关闭显示	//时的十位不显示（亮灭的结合就实现了闪烁）
				 
			delay1();	 	
		}	 
	
	  //if(BIT_timeout)return;
		for(i=0;i<8;i++) 
		{ 
			OE_close(); //关闭显示		//时的个位不显示	 	
			delay1();	 	
		}
	
		 //if(BIT_timeout)return;
	}
	else
	{
		for(i=0;i<8;i++) 			//这里用8个LED实现时间显示
		{	 
			Send_data_C(tab[Hour/16][i*2]);		//时的十位
			Send_data_B(tab[Hour/16][i*2+1]);
			Send_data_A(_8X8Number[tvalue/100][i]); //显示温度十位
			//Send_data_A(_8X8Number[Tem%10][i]); //显示温度个位
			//595下降沿锁存
			
			OE_open();//打开显示
			OEA=0;		 	 
			delay1();	 	
		}
		OE_close(); //关闭显示
		OEA=1;	 
	   //if(BIT_timeout)return;
		for(i=0;i<8;i++) 
		{ 
			Send_data_C(tab[Hour%16][i*2]);	//时的	个位
			Send_data_B(tab[Hour%16][i*2+1]);
			Send_data_A(_8X8Number[tvalue%100/10][i]); //显示温度个位	
			
			//595下降沿锁存
			
			OE_open();//打开显示
			OEA=0;		 
			delay1();	 	
		}	
		OE_close(); //关闭显示
		OEA=1;
		//if(BIT_timeout)return;
	}
/***********************************************************/	
	
	for(i=0;i<8;i++) 
	{ 
		Send_data_C(tab[10][i*2]);			//显示两点
		Send_data_B(tab[10][i*2+1]);
		Send_data_A(_8X8Number[12][i]); //显示小数点
		OEA=0;
		OE_open();//打开显示	 
		delay1();	 
	}
	OE_close(); //关闭显示
	OEA=1;
	//if(BIT_timeout)
	//return;
/**************************************************/ 
	if((flag==1)&&(id==2))      
	{
		for(i=0;i<8;i++) 
		{ 
			OE_close(); //关闭显示		 //分的十位不显示	
			delay1();
		}
		
		if(BIT_timeout)return;
		for(i=0;i<8;i++) 
		{ 
			OE_close(); //关闭显示		//分的个位不显示								 	 
			delay1();	 
		}
	
		//if(BIT_timeout)return;
	}
	else
	{	
		for(i=0;i<8;i++) 
		{ 
			Send_data_C(tab[Cent/16][i*2]);		//分的 十位
			Send_data_B(tab[Cent/16][i*2+1]);
			//Send_data_A(_8X8Number[11][i]); //显示.
			Send_data_A(_8X8Number[tvalue%10][i]); //显示温度小数位
			
			//
			//595下降沿锁存
			
			OE_open();//打开显示
			OEA=0;
			delay1();	 	
		}
		OE_close(); //关闭显示
		OEA=1;
		//if(BIT_timeout)return;
		for(i=0;i<8;i++) 
		{ 
			Send_data_C(tab[Cent%16][i*2]);		 //分的个位
			Send_data_B(tab[Cent%16][i*2+1]);
			Send_data_A(_8X8Number[11][i]); //显示.//
			
			
			OE_open();//打开显示
			OEA=0;						 	
			delay1();	 
		}
		OE_close(); //关闭显示
		OEA=1;
		//if(BIT_timeout)return;

	}
	for(i=0;i<8;i++) 		 //显示两点 
	{ 
		Send_data_C(tab[10][i*2]);
		Send_data_B(tab[10][i*2+1]);
		//Send_data_A(_8X8Number[12][i]); //显示m
		Send_data_A(_8X8Number[10][i]); //显示C
		//595下降沿锁存
		
		OE_open();//打开显示
		OEA=0;		
		delay1();	 
	}
	OE_close(); //关闭显示
	OEA=1;
	//if(BIT_timeout)return;
	for(i=0;i<8;i++) 
	{ 
		Send_data_C(tab[Sec/16][i*2]);	   //秒的十位
		Send_data_B(tab[Sec/16][i*2+1]);
		
		//595下降沿锁存
		
		OE_open();//打开显示	
		delay1();	 	 
	}
	OE_close(); //关闭显示
   //if(BIT_timeout)return;
	for(i=0;i<8;i++) 
	{ 
		Send_data_C(tab[Sec%16][i*2]);		 //秒的	个位
		Send_data_B(tab[Sec%16][i*2+1]);
		
		//595下降沿锁存
		
		OE_open();//打开显示 
		delay1();	 	 
	}
	OE_close(); //关闭显示
	//OEA=1;
	//if(BIT_timeout)return;
	/*********************显示月日数据***************************/
	delay1();	 //这里延时的作用是 把日期与时间拉开距离
		delay1();
			delay1();
				delay1();
					delay1();
						delay1();
							delay1();
								delay1();
			delay1();
				delay1();
					delay1();
						delay1();
							delay1();
								delay1();
				delay1();
				delay1();
					delay1();
						delay1();
							delay1();
								delay1();
									delay1();
										delay1();
											delay1();
	/****************************************************/
/****************************************************/
	for(i=7;i>0;i--) 
	{ 
		Send_data_C(tab1[11][i*2]);					//日字符
		Send_data_B(tab1[11][i*2+1]);
			
		//595下降沿锁存
		
		OE_open();//打开显示		 
		delay1();	 	 
	}
	OE_close(); //关闭显示
	//if(BIT_timeout)return;
	if((flag==1)&&(id==4)) 
	{
		for(i=8;i>0;i--) 
		{ 
			OE_close(); //关闭显示		//日期个位不显示	 
			delay1();	 
		}
		  if(BIT_timeout)return;
		for(i=8;i>0;i--) 
		{ 
			OE_close(); //关闭显示		//日期十位不显示
			delay1();		 
		}
		if(BIT_timeout)return;
	}
	else
	{
		for(i=8;i>0;i--) 
		{ 
			Send_data_C(tab1[Day%16][i*2]);				//日期个位
			Send_data_B(tab1[Day%16][i*2+1]);	
			
			//595下降沿锁存
			
			OE_open();//打开显示
			delay1();	 
		}
		OE_close(); //关闭显示
		for(i=8;i>0;i--) 
		{ 
			Send_data_C(tab1[Day/16][i*2]);				 //日期十位
			Send_data_B(tab1[Day/16][i*2+1]);
				
			//595下降沿锁存
			
			OE_open();//打开显示
			delay1();	 
		}	
	}
OE_close(); //关闭显示
	if(BIT_timeout)return;
/******************************************/

/************************************************************/
	for(i=8;i>0;i--)  
	{ 
		Send_data_C(tab1[10][i*2]);				   //月字符
		Send_data_B(tab1[10][i*2+1]);	
		
		//595下降沿锁存
		
		OE_open();//打开显示
		delay1();	 
	}
	OE_close(); //关闭显示
	if(BIT_timeout)return;
    if((flag==1)&&(id==3))      
	{
		for(i=8;i>0;i--) 
		{   
			OE_close(); //关闭显示		   //月的个位不显示	 
			delay1();	 
		}
	
	   if(BIT_timeout)return;
		for(i=8;i>0;i--)
		{ 
			OE_close(); //关闭显示			 //月的十位不显示	
			delay1();	 	 
		}
		if(BIT_timeout)return;
	}
	else
	{	
		for(i=8;i>0;i--) 
		{ 
			Send_data_C(tab1[Month%16][i*2]);		   //月的 个位
			Send_data_B(tab1[Month%16][i*2+1]);
			
			//595下降沿锁存
			
			OE_open();//打开显示			
			delay1();	 	 
		}
		OE_close(); //关闭显示
		if(BIT_timeout)return;	
		for(i=8;i>0;i--) 
		{ 
			Send_data_C(tab1[Month/16][i*2]);			 //月的	 十位
			Send_data_B(tab1[Month/16][i*2+1]);
			
			//595下降沿锁存
			
			OE_open();//打开显示
			delay1();		 
		}
		
	}
		OE_close(); //关闭显示
		//OEA=1;
	    //if(BIT_timeout)return;
/***********************************/


/******************显示星期数据******************************/
	
//	if((flag==1)&&(id==5))
//	{
//	for(i=8;i>0;i--)
//	{ 
//		OE_close(); //关闭显示	   //星期值不显示
//		delay1();	 
//	}
//	if(BIT_timeout)return;
//	} 
//	else
//	{
//		for(i=8;i>0;i--) 
//		{ 
//			Send_data_C(tab1[Week][i*2]);	   //星期值
//			Send_data_B(tab1[Week][i*2+1]);
//				
//			//595下降沿锁存
//			
//			OE_open();//打开显示	 
//			delay1();	 
//		}		
//	}
//	OE_close(); //关闭显示
//	if(BIT_timeout)return;
}
/*********************************************************************************/
/*************************************************************************************
************************************************************************************
***********************                                     ***************************
***********************    http://59tiaoba.taobao.com       ***************************
***********************                                     ***************************
*******************************程序编写：Fucp***************************************
**********************************************************************************/