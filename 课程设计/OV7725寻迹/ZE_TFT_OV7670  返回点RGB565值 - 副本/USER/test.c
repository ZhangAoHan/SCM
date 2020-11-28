#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "lcd.h"
#include "touch.h"  
#include "w25qxx.h"  
#include "text.h"	
#include "timer.h"	
#include "exit.h"   
#include "sccb.h" 
#include "ov7670.h" 


#define  OV7670 2
const u8*LMODE_TBL[6]={"Auto","Sunny","Cloudy","Office","Home","Night"};//6种光照模式	    
const u8*EFFECTS_TBL[7]={"Normal","Negative","B&W","Redish","Greenish","Bluish","Antique"};	//7种特效 
extern u8 ov_sta;	//在exit.c里 面定义
extern u8 ov_frame;	//在timer.c里面定义

u16 color1;


//更新LCD显示(OV7670)
void OV7670_camera_refresh(void)
{
	u32 j;
 	u16 color;	 
	if(ov_sta)//有帧中断更新
	{
		LCD_Scan_Dir(U2D_L2R);		//从上到下,从左到右  
		if(lcddev.id==0X1963)LCD_Set_Window((lcddev.width-240)/2,(lcddev.height-320)/2,240,320);//将显示区域设置到屏幕中央
		LCD_WriteRAM_Prepare();     //开始写入GRAM	
		OV7670_RRST=0;				//开始复位读指针 
		OV7670_RCK_L;
		OV7670_RCK_H;
		OV7670_RCK_L;
		OV7670_RRST=1;				//复位读指针结束 
		OV7670_RCK_H;
		for(j=0;j<76800;j++)
		{
			OV7670_RCK_L;
			color=GPIOC->IDR&0XFF;	//读数据
			OV7670_RCK_H; 
			color<<=8;  
			OV7670_RCK_L;
			color|=GPIOC->IDR&0XFF;	//读数据
			OV7670_RCK_H; 
			LCD->LCD_RAM=color;   
			if(j==38560)            //点120,160
			{
				color1=color;
			}
		}   							  
 		ov_sta=0;					//清零帧中断标记
		ov_frame++; 
		LCD_Scan_Dir(DFT_SCAN_DIR);	//恢复默认扫描方向 
	}
}	   



int main(void)
{		
	u8 sensor=0;
	u8 lightmode=0,effect=0;
	s8 saturation=0,brightness=0,contrast=0;	
		u8 r,g,b;
	Stm32_Clock_Init(9);	//系统时钟设置
	delay_init(72);	  		//延时初始化
	uart_init(72,115200); 	//串口初始化为115200
	LCD_Init();
	W25QXX_Init();				//初始化W25Q128 和SPI2
	POINT_COLOR=RED;
	tp_dev.init();			//触摸屏初始化 
	while(font_init()) 			//检查字库
	{;}  
	POINT_COLOR=RED;			//设置字体为红色 
	LCD_ShowString(30,50,200,16,16,"ELITE STM32F103 ^_^");	
	LCD_ShowString(30,70,200,16,16,"OV7670_OV7725 TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2017/11/1"); 
	LCD_ShowString(30,130,200,16,16,"KEY0:Light Mode");
	LCD_ShowString(30,150,200,16,16,"KEY1:Saturation");
	LCD_ShowString(30,170,200,16,16,"KEY_UP:Contrast");
	LCD_ShowString(30,190,200,16,16,"TPAD:Effects");	 
  	LCD_ShowString(30,210,200,16,16,"OV7670 Init...");
//	POINT_COLOR=RED;       
//	Show_Str(30,50,200,16,"战舰STM32F103开发板",16,0);	
	while(1)//初始化OV7725_OV7670
	{
		if(OV7670_Init()==0)
		{
			sensor=OV7670;
			LCD_ShowString(30,210,200,16,16,"OV7670 Init OK       ");
			delay_ms(1500);	 	   
			OV7670_Light_Mode(lightmode);
			OV7670_Color_Saturation(saturation);
			OV7670_Brightness(brightness);
			OV7670_Contrast(contrast);
			OV7670_Special_Effects(effect);
			OV7670_Window_Set(12,176,240,320);//设置窗口
			OV7670_CS=0;
			break;
		}else
		{
			LCD_ShowString(30,210,200,16,16,"OV7670 Error!!");
			delay_ms(200);
			LCD_Fill(30,210,239,246,WHITE);
			delay_ms(200);
		}
	}

	TIM6_Int_Init(10000,7199);			//10Khz计数频率,1秒钟中断									  
	EXTI8_Init();						//使能外部中断8,捕获帧中断			
	LCD_Clear(BLACK);		
//	color1=0xffff;     //满值  
		while(1)
	{
		if(sensor==OV7670)OV7670_camera_refresh();	//更新显示
		Show_Str(30,260,168,12,"中点颜色值为:",12,0);	
		r=(color1&0xf800)>>8;
		g=(color1&0x07e0)>>3;
		b=(color1&0x001f)<<3;
		LCD_ShowNum(30,290,r,3,16);   //满值 r=248 g=252  b=248
		LCD_ShowNum(80,290,g,3,16);
		LCD_ShowNum(130,290,b,3,16);		
	}
} 



//		printf("t:%d\r\n",t);

