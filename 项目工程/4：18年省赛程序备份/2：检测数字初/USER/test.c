#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "lcd.h"
#include "touch.h"  
#include "w25qxx.h"  
#include "text.h"	 
#include "fdc2214.h"
#include "IIC.h"
#include "timer.h"    
uint32_t date2;
uint32_t fre2;
uint32_t fre2_init_min,fre2_init_max;  //检测 找到最大值和最小值
uint32_t ch2_middle,ch2_wave; //中值和波动区间
uint32_t y1,b1,y2,b2,y3,b3,y4,b4,y5,b5;  //使系统具有存储功能
//触摸按键选择
u8 mode_selsct=0;   //通道选择
//算术平均滤波
uint32_t result2;
//一阶滤波
uint32_t fre2_last;

void FDC2214read(void);
void Display(void);
void Scan_sjb(void);  //检测石头剪刀布函数
void Feedback(void);    //反馈显示函数

int main(void)
{		
//	u8 j;	
	Stm32_Clock_Init(9);	//系统时钟设置
	delay_init(72);	  		//延时初始化
	uart_init(72,115200); 	//串口初始化为115200
	TIM3_Int_Init(999,7199);//10Khz的计数频率，计数5K次为100ms  
	LCD_Init();
	W25QXX_Init();				//初始化W25Q128 和SPI2
	tp_dev.init();			//触摸屏初始化 
	IIC_Init1();
	FDC2214_Init();  //检测2214
	while(font_init()) 			//检查字库
	{;}  
    FDC2214_GetChannelData(FDC2214_Channel_2, &date2);
	fre2 = FDC2214_CalculateFrequency(FDC2214_Channel_2, date2);    
	fre2_last=fre2;	
	LCD_Clear(WHITE);
	POINT_COLOR=BLUE;
	LCD_DrawRectangle(10,60 ,230 ,310);   //画矩形
	Show_Str(11,61,131,24,"电容返回值",24,0);
	POINT_COLOR=RED;   
	Show_Str(11,90,84,24,"通道2：",24,0);
	POINT_COLOR=BLUE;	
	Show_Str(60,120,48,24,"阈值",24,0);
	Show_Str(120,120,96,24,"波动范围",24,0);	
	Show_Str(11,150,48,24,"测1",24,0);
	Show_Str(11,180,48,24,"测2",24,0);
	Show_Str(11,210,48,24,"测3",24,0);
	Show_Str(11,240,48,24,"测4",24,0);
	Show_Str(11,270,48,24,"测5",24,0);
		while(1)
	{
		if(y1!=0&&b1!=0&&y2!=0&&b2!=0&&y3!=0&&b3!=0&&y4!=0&&b4!=0&&y5!=0&&b5!=0)  //通道2学习完成  
		{
			Show_Str(11,1,96,24,"学习完成",24,0);
			Feedback();
		}
		else
		{
			Show_Str(11,1,96,24,"请先学习",24,0);
		}
	FDC2214read();
	Display();	
	}
} 
void FDC2214read(void)
{
	u8 i;
	for(i=0;i<30;i++)
	{
        FDC2214_GetChannelData(FDC2214_Channel_2, &date2);
	    fre2 = FDC2214_CalculateFrequency(FDC2214_Channel_2, date2);    
	//算术平均滤波
		result2	=result2+fre2;
		i++;
	}
	fre2=result2/30;
	fre2=result2/30*0.8+fre2_last*0.2;
	fre2_last=fre2;
	result2=0;
}
void Display(void)
{
	u8 i;
	POINT_COLOR=RED;        //红色字体
	Show_Str(11,90,84,24,"通道2：",24,0);
	if(mode_selsct==1)   //测试1
	{      
	POINT_COLOR=RED;
	Show_Str(11,150,60,24,"测1",24,0);
	FDC2214read();
	fre2_init_min=fre2_init_max=fre2;   //赋初值
		for(i=0;i<100;i++)
		{
			Scan_sjb();     //学习阈值		
			POINT_COLOR=BLACK;
			LCD_ShowxNum(96,94,fre2,8,16,0);	
			LCD_ShowxNum(60,154,ch2_middle,8,16,0);	   //显示阈值
			LCD_ShowxNum(130,154,ch2_wave,5,16,0);    //显示波动范围
		}
	y1=ch2_middle;
	b1=ch2_wave;
	POINT_COLOR=BLUE;  
	Show_Str(11,150,48,24,"测1",24,0);
	mode_selsct=0;
	}
	if(mode_selsct==2)   //测2
	{      
	POINT_COLOR=RED;
	Show_Str(11,180,48,24,"测2",24,0);
	FDC2214read();
	fre2_init_min=fre2_init_max=fre2;   //赋初值
		for(i=0;i<100;i++)
		{
			Scan_sjb();     //学习阈值		
			POINT_COLOR=BLACK;
			LCD_ShowxNum(96,94,fre2,8,16,0);	
			LCD_ShowxNum(60,184,ch2_middle,8,16,0);	   //显示阈值
			LCD_ShowxNum(130,184,ch2_wave,5,16,0);    //显示波动范围
		}
	y2=ch2_middle;
	b2=ch2_wave;
	POINT_COLOR=BLUE;  
	Show_Str(11,180,48,24,"测2",24,0);
	mode_selsct=0;
	}
	if(mode_selsct==3)   //测试3
	{      
	POINT_COLOR=RED;
	Show_Str(11,210,48,24,"测3",24,0);
	FDC2214read();
	fre2_init_min=fre2_init_max=fre2;   //赋初值
		for(i=0;i<100;i++)
		{
			Scan_sjb();     //学习阈值		
			POINT_COLOR=BLACK;
			LCD_ShowxNum(96,94,fre2,8,16,0);	
			LCD_ShowxNum(60,214,ch2_middle,8,16,0);	   //显示阈值
			LCD_ShowxNum(130,214,ch2_wave,5,16,0);    //显示波动范围
		}
	y3=ch2_middle;
	b3=ch2_wave;
	POINT_COLOR=BLUE;  
	Show_Str(11,210,48,24,"测3",24,0);
	mode_selsct=0;
	}
		if(mode_selsct==4)   //测试4
	{      
	POINT_COLOR=RED;
	Show_Str(11,240,48,24,"测4",24,0);
	FDC2214read();
	fre2_init_min=fre2_init_max=fre2;   //赋初值
		for(i=0;i<100;i++)
		{
			Scan_sjb();     //学习阈值		
			POINT_COLOR=BLACK;
			LCD_ShowxNum(96,94,fre2,8,16,0);	
			LCD_ShowxNum(60,244,ch2_middle,8,16,0);	   //显示阈值
			LCD_ShowxNum(130,244,ch2_wave,5,16,0);    //显示波动范围
		}
	y4=ch2_middle;
	b4=ch2_wave;
	POINT_COLOR=BLUE;  
	Show_Str(11,240,48,24,"测4",24,0);
	mode_selsct=0;
	}
		if(mode_selsct==5)   //测试5
	{      
	POINT_COLOR=RED;
	Show_Str(11,270,48,24,"测5",24,0);
	FDC2214read();
	fre2_init_min=fre2_init_max=fre2;   //赋初值
		for(i=0;i<100;i++)
		{
			Scan_sjb();     //学习阈值		
			POINT_COLOR=BLACK;
			LCD_ShowxNum(96,94,fre2,8,16,0);	
			LCD_ShowxNum(60,274,ch2_middle,8,16,0);	   //显示阈值
			LCD_ShowxNum(130,274,ch2_wave,5,16,0);    //显示波动范围
		}
	y5=ch2_middle;
	b5=ch2_wave;
	POINT_COLOR=BLUE;  
	Show_Str(11,270,48,24,"测5",24,0);
	mode_selsct=0;
	}
	//显示测的值  ，使系统具有存储功能
			POINT_COLOR=BLACK;
			LCD_ShowxNum(60,154,y1,8,16,0);	   //显示阈值
			LCD_ShowxNum(130,154,b1,5,16,0);    //显示波动范围
			LCD_ShowxNum(60,184,y2,8,16,0);	   //显示阈值
			LCD_ShowxNum(130,184,b2,5,16,0);    //显示波动范围
			LCD_ShowxNum(60,214,y3,8,16,0);	   //显示阈值
			LCD_ShowxNum(130,214,b3,5,16,0);    //显示波动范围
			LCD_ShowxNum(60,244,y4,8,16,0);	   //显示阈值
			LCD_ShowxNum(130,244,b4,5,16,0);    //显示波动范围
			LCD_ShowxNum(60,274,y5,8,16,0);	   //显示阈值
			LCD_ShowxNum(130,274,b5,5,16,0);    //显示波动范围
	
	
	POINT_COLOR=BLACK;
	LCD_ShowxNum(96,94,fre2,8,16,0);	
}

void Scan_sjb(void)  //检测石头剪刀布函数
{
		FDC2214read();
		if(fre2<fre2_init_min) fre2_init_min=fre2;
		if(fre2>fre2_init_max) fre2_init_max=fre2;

		ch2_middle=(fre2_init_min+fre2_init_max)/2;
		ch2_wave=((ch2_middle-fre2_init_min)+(fre2_init_max-ch2_middle))/2;
			
}


void Feedback(void)    //反馈显示函数
{	
	if(fre2>y1&&(fre2-y1)<(b1*0.8))   Show_Str(11,30,48,24,"1",24,0);   

	else if(fre2<y1&&(y1-fre2)<(b1*0.8))   Show_Str(11,30,48,24,"1",24,0);  

	
	else if(fre2>y2&&(fre2-y2)<(b2*0.8))   Show_Str(11,30,48,24,"2",24,0);   

	else if(fre2<y2&&(y2-fre2)<(b2*0.8))   Show_Str(11,30,48,24,"2",24,0);  

	else if(fre2>y3&&(fre2-y3)<(b3*0.8))   Show_Str(11,30,48,24,"3",24,0);  

	else if(fre2<y3&&(y3-fre2)<(b3*0.8))   Show_Str(11,30,48,24,"3",24,0);
	
	else if(fre2>y4&&(fre2-y4)<(b4*0.8))   Show_Str(11,30,48,24,"4",24,0);  

	else if(fre2<y4&&(y4-fre2)<(b4*0.8))   Show_Str(11,30,48,24,"4",24,0); 
	
	else if(fre2>y5&&(fre2-y5)<(b5*0.8))   Show_Str(11,30,48,24,"5",24,0);  

	else if(fre2<y5&&(y5-fre2)<(b5*0.8))   Show_Str(11,30,48,24,"5",24,0); 	

	else Show_Str(11,30,240,24,"0",24,0); 
	
}

