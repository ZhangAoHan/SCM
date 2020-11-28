#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 		 	 
#include "lcd.h"  
#include "key.h"   
#include "timer.h"
#include "exti.h"   
#include "ov7725.h"

//ALIENTEK战舰STM32开发板 实验35
//摄像头实验 实验 
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司 

u8 key;
u8 key1;
//传感器名字宏定义
#define  OV7725 1
u8 flag=0;
//由于OV7725传感器安装方式原因,OV7725_WINDOW_WIDTH相当于LCD的高度，OV7725_WINDOW_HEIGHT相当于LCD的宽度
//图像数据输出方式相对LCD的顺序为D2U_L2R（从下到上,从左到右）
//注意：此宏定义只对OV7725有效
#define  OV7725_WINDOW_WIDTH		320 // <=320,部分尺寸图像有问题
#define  OV7725_WINDOW_HEIGHT		240 // <=240,部分尺寸图像有问题
u16 color1;

const u8*LMODE_TBL[6]={"Auto","Sunny","Cloudy","Office","Home","Night"};//6种光照模式	    
const u8*EFFECTS_TBL[7]={"Normal","Negative","B&W","Redish","Greenish","Bluish","Antique"};	//7种特效 
extern u8 ov_sta;	//在exit.c里 面定义
extern u8 ov_frame;	//在timer.c里面定义

 //数据采集矩阵
u32 Array[60] ={
	 /*采集像素点矩阵【（16,150），（19,154）】 320列*/
	5270,5271,5272,5273,5274,    //46*320+150=14870
	5590,5591,5592,5593,5594,
	5770,5771,5772,5773,5774,
	6090,6091,6092,6093,6094,
	 /*采集像素点矩阵【（100,10），（104,13）】 320列*/
	32010,32011,32012,32013,			 
	32330,32331,32332,32333,
	32650,32651,32652,32653,
	32970,32971,32972,32973,
	33290,33291,33292,33293,
	/*采集像素点矩阵【（205,150），（208,154）】 320列  */
	65750,65751,65752,65753,65754,		 
	66070,66071,66072,66073,66074,
	66390,66391,66392,66393,66394,
	66710,66711,66712,66713,66714,

};

//更新LCD显示(OV7725)
void OV7725_camera_refresh(void)
{
	u32 i,j;
	u8 whitepoint = 0;
	u8 leftblackpoint  = 0;
	u8 rightblackpoint = 0;
 	u16 color;	 
	flag=0;
	if(ov_sta)//有帧中断更新
	{
		LCD_Scan_Dir(U2D_L2R);		//从上到下,从左到右  
		LCD_Set_Window((lcddev.width-OV7725_WINDOW_WIDTH)/2,(lcddev.height-OV7725_WINDOW_HEIGHT)/2,OV7725_WINDOW_WIDTH,OV7725_WINDOW_HEIGHT);//将显示区域设置到屏幕中央
		if(lcddev.id==0X1963)LCD_Set_Window((lcddev.width-OV7725_WINDOW_WIDTH)/2,(lcddev.height-OV7725_WINDOW_HEIGHT)/2,OV7725_WINDOW_HEIGHT,OV7725_WINDOW_WIDTH);//将显示区域设置到屏幕中央
		LCD_WriteRAM_Prepare();     //开始写入GRAM	
		OV7725_RRST=0;				//开始复位读指针 
		OV7725_RCK_L;
		OV7725_RCK_H;
		OV7725_RCK_L;
		OV7725_RRST=1;				//复位读指针结束 
		OV7725_RCK_H; 
		for(i=0;i<OV7725_WINDOW_HEIGHT*OV7725_WINDOW_WIDTH;i++)
		{
				OV7725_RCK_L;
				color=GPIOC->IDR&0XFF;	//读数据（&0xff  是为了保证本次数据不受上次数据的干扰）
				OV7725_RCK_H; 
				color<<=8;  
				OV7725_RCK_L;
				color|=GPIOC->IDR&0XFF;	//读数据   一共读取2B数据  （采用RGB565格式）
				OV7725_RCK_H;  
				LCD->LCD_RAM=color; 				
				if(i== Array[j]&&(j<=60))//init(k) = 0									  -=
			{
//				if(j < 20)
//				{
//					   
//					 if(!(color&0x8000))  //测得白点
//						leftblackpoint++;
//						
//				}
//				else if(j < 40)
//				{
//					if(color&0x8000)
//					whitepoint++;		//测得黑点
//					
//				}
//				else if(j < 60)
//				{
//						if(!(color&0x8000))  //检测底片  黑，如果bit15为0，则黑点
//						rightblackpoint++;
//					
//				}
           if(j==45)	
		   {
			   color=color1;
		   }			   
//				if(j < 20)
//				{
//					   
//					 if(!(color&0x8000))  //测得黑
//						leftblackpoint++;
//						
//				}
//				else if(j < 40)
//				{
//					if(color&0x4000)
//					whitepoint++;		//测得白点
//					
//				}
//				else if(j < 60)
//				{
//						if(!(color&0x8000))  //检测底片  黑，如果bit15为0，则黑点
//						rightblackpoint++;
//					
//				}	
			j++;
			} 

			
			
		}
		
//		if(whitepoint<=20)	    //中间端未检测到黑色则停止
//	{
//		flag = 2;// stop
//	}
//	else
//		flag=1;
//	else 
//	{

//		if((whitepoint>13)&&(leftblackpoint>13)&&(rightblackpoint>13))//左端块白色  中端块黑色 右端块白色 
//		{
//			flag = 1;       
//		}
//	
//		if(leftblackpoint <= 13 && rightblackpoint >13)	//左端黑色 右端白色 则向往左
//		{
//			flag = 2;  //goleft
//		}

//		if(leftblackpoint > 13 && rightblackpoint <= 13)	//右端黑色 左端白色 则向往右
//		{
//			flag = 3;  //goright
//		}
//    }	
 		ov_sta=0;					//清零帧中断标记
		ov_frame++; 
		LCD_Scan_Dir(DFT_SCAN_DIR);	//恢复默认扫描方向 
	} 
}



int main(void)
{		
	u8 sensor=0;
	
 	u8 i=0;	    
	u8 lightmode=0,effect=1;
	s8 saturation=0,brightness=0,contrast=0;
	
 	Stm32_Clock_Init(9);		//系统时钟设置
	uart_init(72,115200);		//串口初始化为115200
	delay_init(72);	   	 		//延时初始化 	
 	LED_Init();		  			//初始化与LED连接的硬件接口
	KEY_Init();					//初始化按键
	LCD_Init();			   		//初始化LCD   
 	POINT_COLOR=RED;			//设置字体为红色 
	LCD_ShowString(30,50,200,16,16,"WarShip STM32");	
	LCD_ShowString(30,70,200,16,16,"OV7725_OV7670 TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2017/11/1"); 
	LCD_ShowString(30,130,200,16,16,"KEY0:Light Mode");
	LCD_ShowString(30,150,200,16,16,"KEY1:Saturation");
	LCD_ShowString(30,170,200,16,16,"KEY2:Brightness");
	LCD_ShowString(30,190,200,16,16,"KEY_UP:Contrast");
	LCD_ShowString(30,210,200,16,16,"TPAD:Effects");	 
  	LCD_ShowString(30,230,200,16,16,"OV7725_OV7670 Init...");	  
	while(1)//等待7725初始化成功
	{
		if(OV7725_Init()==0)   
		{
			sensor=OV7725;
			LCD_ShowString(30,230,200,16,16,"OV7725 Init OK       ");
			while(1)   //等待选择模式
			{
				key=KEY_Scan(0);
				if(key==KEY0_PRES)
				{
					OV7725_Window_Set(OV7725_WINDOW_WIDTH,OV7725_WINDOW_HEIGHT,0);//QVGA模式输出
					i=0;
					break;
				}else if(key==KEY1_PRES)
				{
					OV7725_Window_Set(OV7725_WINDOW_WIDTH,OV7725_WINDOW_HEIGHT,1);//VGA模式输出
					i=0;
					break;
				}
				i++;
				if(i==100)LCD_ShowString(30,250,210,16,16,"KEY0:QVGA  KEY1:VGA"); //闪烁显示提示信息
				if(i==200)
				{	
					LCD_Fill(30,250,210,250+16,WHITE);
					i=0; 
				}
				delay_ms(5);
			}				
			OV7725_Light_Mode(lightmode);
			OV7725_Color_Saturation(saturation);
			OV7725_Brightness(brightness);
			OV7725_Contrast(contrast);
			OV7725_Special_Effects(effect);
			OV7725_CS=0;
			break;   
		}
		else
		{
			LCD_ShowString(30,230,200,16,16,"OV7725_OV7670 Error!!");
			delay_ms(200);
			LCD_Fill(30,230,239,246,WHITE);
			delay_ms(200);
		}
	}

	TIM6_Int_Init(10000,7199);			//10Khz计数频率,1秒钟中断									  
	EXTI8_Init();						//使能外部中断8,捕获帧中断			
	LCD_Clear(WHITE);
	delay_ms(200);
	POINT_COLOR=RED;
	LCD_DrawRectangle(16,150,19,154);
	LCD_DrawRectangle(100,10,104,13);
	LCD_DrawRectangle(205,150,208,154);
 	while(1)
	{	
		
		if(sensor==OV7725) OV7725_camera_refresh();		//更新显示
//		switch(flag)
//		{
//			case 2:LCD_ShowString(1,1,40,16,16,"BLACK");break;
//			case 1:LCD_ShowString(1,1,40,16,16,"WHITE");break;
////			case 2:LCD_ShowString(1,1,40,16,16,"LEFT");break;
////			case 3:LCD_ShowString(1,1,40,16,16,"RIGHT");break;
//		}
			LCD_DrawRectangle(16,150,19,154);
	LCD_DrawRectangle(100,10,104,13);
	LCD_DrawRectangle(205,150,208,154);
				LCD_ShowNum(10,300,color1&0x80,1,16);
				LCD_ShowNum(18,300,color1&0x40,1,16);	
				LCD_ShowNum(26,300,color1&0x20,1,16);	
				LCD_ShowNum(34,300,color1&0x10,1,16);	
				LCD_ShowNum(42,300,color1&0x08,1,16);	
				LCD_ShowNum(50,300,color1&0x04,1,16);	
				LCD_ShowNum(58,300,color1&0x02,1,16);	
				LCD_ShowNum(64,300,color1&0x01,1,16);
	}	   
}











