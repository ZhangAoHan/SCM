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
uint32_t date0, date1,date2, date3;
uint32_t fre0, fre1,fre2, fre3;
uint32_t fre0_init_min,fre0_init_max, fre1_init_min,fre1_init_max,fre2_init_min,fre2_init_max, fre3_init_min,fre3_init_max;  //检测10000个数 找到最大值和最小值
uint32_t ch0_middle,ch0_wave,ch1_middle,ch1_wave,ch2_middle,ch2_wave,ch3_middle,ch3_wave; //中值和波动区间
uint32_t by2,bb2,sy2,sb2,jy2,jb2,by3,bb3,sy3,sb3,jy3,jb3;  //使系统具有存储功能
//触摸按键选择
u8 ch_selsct=0,mode_selsct=0;   //通道选择
//算术平均滤波
uint32_t result0,result1,result2,result3;
//一阶滤波
uint32_t fre2_last, fre3_last;

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
    FDC2214_GetChannelData(FDC2214_Channel_3, &date3);
	fre2 = FDC2214_CalculateFrequency(FDC2214_Channel_2, date2);    
    fre3 = FDC2214_CalculateFrequency(FDC2214_Channel_3, date3);	
	fre2_last=fre2;	
	fre3_last=fre3;	
	LCD_Clear(WHITE);
	POINT_COLOR=BLUE;
	LCD_DrawRectangle(10,60 ,230 ,310);   //画矩形
	Show_Str(11,61,131,24,"电容返回值",24,0);
	POINT_COLOR=RED;   //默认选择通道2
	Show_Str(11,90,84,24,"通道2：",24,0);
	POINT_COLOR=BLUE;
	Show_Str(11,120,84,24,"通道3：",24,0);
	POINT_COLOR=BLUE;	
	Show_Str(60,150,48,24,"阈值",24,0);
	Show_Str(120,150,96,24,"波动范围",24,0);	
	Show_Str(11,180,48,24,"石头",24,0);
	POINT_COLOR=BLUE;
	Show_Str(11,210,48,24,"剪刀",24,0);
	Show_Str(11,240,48,24,"布",24,0);
		while(1)
	{
		if(bb2!=0&&by2!=0&&sy2!=0&&sb2!=0&&jy2!=0&&jb2!=0)  //通道2学习完成  &&bb3!=0&&by3!=0&&sy3!=0&&sb3!=0&&jy3!=0&&jb3!=0
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
        FDC2214_GetChannelData(FDC2214_Channel_3, &date3);
	    fre2 = FDC2214_CalculateFrequency(FDC2214_Channel_2, date2);    
        fre3 = FDC2214_CalculateFrequency(FDC2214_Channel_3, date3);
//	//限幅滤波   限制峰峰值
//			if(fre0>ch0&&fre0-ch0>200000) fre0=ch0;
//			if(fre0<ch0&&ch0-fre0>200000) fre0=ch0;
//			if(fre1>ch1&&fre1-ch1>200000) fre1=ch1;
//			if(fre1<ch1&&ch1-fre1>200000) fre1=ch1;
	//算术平均滤波
		result2	=result2+fre2;
		result3	=result3+fre3;
		i++;
	}
	fre2=result2/30;
	fre3=result3/30;
	fre2=result2/30*0.8+fre2_last*0.2;
	fre3=result3/30*0.8+fre3_last*0.2;
	fre2_last=fre2;
	fre3_last=fre3;
	result2=0;
	result3=0;
//        printf("%d,%d,%d,%d\r\n", fre0, fre1, fre2, fre3);
}
void Display(void)
{
	u8 i;
		if(ch_selsct==0)   //选择通道二
	{
	POINT_COLOR=RED;        //红色字体
	Show_Str(11,90,84,24,"通道2：",24,0);
	POINT_COLOR=BLUE;
	Show_Str(11,120,84,24,"通道3：",24,0);
	if(mode_selsct==1)   //选择石头进行学习阈值
	{      
	POINT_COLOR=RED;
	Show_Str(11,180,48,24,"石头",24,0);
	FDC2214read();
	fre2_init_min=fre2_init_max=fre2;   //赋初值
		for(i=0;i<100;i++)
		{
			Scan_sjb();     //学习阈值		
			POINT_COLOR=BLACK;
			LCD_ShowxNum(96,94,fre2,8,16,0);	
			LCD_ShowxNum(96,124,fre3,8,16,0);
			LCD_ShowxNum(60,184,ch2_middle,8,16,0);	   //显示阈值
			LCD_ShowxNum(130,184,ch2_wave,5,16,0);    //显示波动范围
		}
	sy2=ch2_middle;
	sb2=ch2_wave;
	POINT_COLOR=BLUE;  
	Show_Str(11,180,48,24,"石头",24,0);
	mode_selsct=0;
	}
	if(mode_selsct==2)   //选择剪刀
	{      
	POINT_COLOR=RED;
	Show_Str(11,210,48,24,"剪刀",24,0);
	FDC2214read();
	fre2_init_min=fre2_init_max=fre2;   //赋初值
		for(i=0;i<100;i++)
		{
			Scan_sjb();     //学习阈值		
			POINT_COLOR=BLACK;
			LCD_ShowxNum(96,94,fre2,8,16,0);	
			LCD_ShowxNum(96,124,fre3,8,16,0);
			LCD_ShowxNum(60,214,ch2_middle,8,16,0);	   //显示阈值
			LCD_ShowxNum(130,214,ch2_wave,5,16,0);    //显示波动范围
		}
	jy2=ch2_middle;
	jb2=ch2_wave;
	POINT_COLOR=BLUE;  
	Show_Str(11,210,48,24,"剪刀",24,0);
	mode_selsct=0;
	}
	if(mode_selsct==3)   //选择布
	{      
	POINT_COLOR=RED;
	Show_Str(11,240,48,24,"布",24,0);
	FDC2214read();
	fre2_init_min=fre2_init_max=fre2;   //赋初值
		for(i=0;i<100;i++)
		{
			Scan_sjb();     //学习阈值		
			POINT_COLOR=BLACK;
			LCD_ShowxNum(96,94,fre2,8,16,0);	
			LCD_ShowxNum(96,124,fre3,8,16,0);
			LCD_ShowxNum(60,244,ch2_middle,8,16,0);	   //显示阈值
			LCD_ShowxNum(130,244,ch2_wave,5,16,0);    //显示波动范围
		}
	by2=ch2_middle;
	bb2=ch2_wave;
	POINT_COLOR=BLUE;  
	Show_Str(11,240,48,24,"布",24,0);
	mode_selsct=0;
	}
	//显示测的值  ，使系统具有存储功能
			POINT_COLOR=BLACK;
			LCD_ShowxNum(60,184,sy2,8,16,0);	   //显示阈值
			LCD_ShowxNum(130,184,sb2,5,16,0);    //显示波动范围
			LCD_ShowxNum(60,214,jy2,8,16,0);	   //显示阈值
			LCD_ShowxNum(130,214,jb2,5,16,0);    //显示波动范围
			LCD_ShowxNum(60,244,by2,8,16,0);	   //显示阈值
			LCD_ShowxNum(130,244,bb2,5,16,0);    //显示波动范围
	}
	
	
		if(ch_selsct==1)   //选择通道三
	{
	POINT_COLOR=BLUE;       
	Show_Str(11,90,84,24,"通道2：",24,0);
	POINT_COLOR=RED;
	Show_Str(11,120,84,24,"通道3：",24,0);
	if(mode_selsct==1)   //选择石头进行学习阈值
	{      
	POINT_COLOR=RED;
	Show_Str(11,180,48,24,"石头",24,0);
	FDC2214read();
	fre3_init_min=fre3_init_max=fre3;
		for(i=0;i<100;i++)
		{
			Scan_sjb();     //学习阈值		
			POINT_COLOR=BLACK;
			LCD_ShowxNum(96,94,fre2,8,16,0);	
			LCD_ShowxNum(96,124,fre3,8,16,0);
			LCD_ShowxNum(60,184,ch3_middle,8,16,0);	   //显示阈值
			LCD_ShowxNum(130,184,ch3_wave,5,16,0);    //显示波动范围
		}
		sy3=ch3_middle;
		sb3=ch3_wave;
	POINT_COLOR=BLUE;  
	Show_Str(11,180,48,24,"石头",24,0);
	mode_selsct=0;
	}
		if(mode_selsct==2)   //选择剪刀
	{      
	POINT_COLOR=RED;
	Show_Str(11,210,48,24,"剪刀",24,0);
	FDC2214read();
	fre3_init_min=fre3_init_max=fre3;
		for(i=0;i<100;i++)
		{
			Scan_sjb();     //学习阈值		
			POINT_COLOR=BLACK;
			LCD_ShowxNum(96,94,fre2,8,16,0);	
			LCD_ShowxNum(96,124,fre3,8,16,0);
			LCD_ShowxNum(60,214,ch3_middle,8,16,0);	   //显示阈值
			LCD_ShowxNum(130,214,ch3_wave,5,16,0);    //显示波动范围
		}
		jy3=ch3_middle;
		jb3=ch3_wave;
	POINT_COLOR=BLUE;  
	Show_Str(11,210,48,24,"剪刀",24,0);
	mode_selsct=0;
	}
		if(mode_selsct==3)   //选择布
	{      
	POINT_COLOR=RED;
	Show_Str(11,240,48,24,"布",24,0);
	FDC2214read();
	fre3_init_min=fre3_init_max=fre3;
		for(i=0;i<100;i++)
		{
			Scan_sjb();     //学习阈值		
			POINT_COLOR=BLACK;
			LCD_ShowxNum(96,94,fre2,8,16,0);	
			LCD_ShowxNum(96,124,fre3,8,16,0);
			LCD_ShowxNum(60,244,ch3_middle,8,16,0);	   //显示阈值
			LCD_ShowxNum(130,244,ch3_wave,5,16,0);    //显示波动范围
		}
		by3=ch3_middle;
		bb3=ch3_wave;
	POINT_COLOR=BLUE;  
	Show_Str(11,240,48,24,"布",24,0);
	mode_selsct=0;
	}
			POINT_COLOR=BLACK;
			LCD_ShowxNum(60,184,sy3,8,16,0);	   //显示阈值
			LCD_ShowxNum(130,184,sb3,5,16,0);    //显示波动范围
			LCD_ShowxNum(60,214,jy3,8,16,0);	   //显示阈值
			LCD_ShowxNum(130,214,jb3,5,16,0);    //显示波动范围
			LCD_ShowxNum(60,244,by3,8,16,0);	   //显示阈值
			LCD_ShowxNum(130,244,bb3,5,16,0);    //显示波动范围
	}
	
	POINT_COLOR=BLACK;
	LCD_ShowxNum(96,94,fre2,8,16,0);	
	LCD_ShowxNum(96,124,fre3,8,16,0);


}

void Scan_sjb(void)  //检测石头剪刀布函数
{
		FDC2214read();
		if(fre2<fre2_init_min) fre2_init_min=fre2;
		if(fre2>fre2_init_max) fre2_init_max=fre2;
		if(fre3<fre3_init_min) fre3_init_min=fre3;
		if(fre3>fre3_init_max) fre3_init_max=fre3;
		ch2_middle=(fre2_init_min+fre2_init_max)/2;
		ch2_wave=((ch2_middle-fre2_init_min)+(fre2_init_max-ch2_middle))/2;
		ch3_middle=(fre3_init_min+fre3_init_max)/2;
		ch3_wave=((ch3_middle-fre3_init_min)+(fre3_init_max-ch3_middle))/2;				
}


void Feedback(void)    //反馈显示函数
{
	if(fre2>sy2&&(fre2-sy2)<(sb2*0.8)) Show_Str(11,30,48,24,"石头",24,0);     //检测到石头
	else if(fre2<sy2&&(sy2-fre2)<(sb2*0.8)) Show_Str(11,30,48,24,"石头",24,0);     //检测到石头
	
	else if(fre2>jy2&&(fre2-jy2)<(jb2*0.8)) Show_Str(11,30,48,24,"剪刀",24,0);     //检测到剪刀
	else if(fre2<jy2&&(jy2-fre2)<(jb2*0.8)) Show_Str(11,30,48,24,"剪刀",24,0);     //检测到剪刀
	
	else if(fre2>by2&&(fre2-by2)<(bb2*0.8)) Show_Str(11,30,48,24,"  布",24,0);     //检测到布
	else if(fre2<by2&&(by2-fre2)<(bb2*0.8)) Show_Str(11,30,48,24,"  布",24,0);     //检测到布
	else Show_Str(1,30,240,24,"          ",24,0); 
	
}

