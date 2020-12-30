#include "sys.h"
#include "usart.h"		
#include "delay.h"	 
#include "lcd.h"
#include "touch.h"  
#include "w25q128.h"  
#include "text.h"	
#include "24l01.h"
#include "usart2.h"
#include "AS608.h" 
#include "malloc.h"	  
#include "date_control.h"
#include "control.h"
#include "timer.h"
#include "led.h"
#include "motor.h"
#include "motor_control.h"

#define usart2_baund  57600//串口2波特率，根据指纹模块波特率更改
u8 tmp_buf[33]; 
u8 page=0;
char *str1;
u16 t1,t2,t3,t4; 
u8 use1=0,use2=0,use3=0,use4=0; 
u8 use_start=0;
u8 ste;
u8 use_error=0;   //用户出错 警告信息显示时间变量
//u8 car[4]={0,0,0,0,};      //共4个停车位可供选择
u16 car_id[4]={0,0,0,0};      //使用停车位的用户ID
u8 dl_success=0;   //开始进行停车操作的标志量
u8 people_car=0; 
u16 people_id;
u16 gly_id=0;
int main(void)
{				 

	Stm32_Clock_Init(9);	//系统时钟设置
	delay_init(72);	  		//延时初始化
	uart_init(72,115200); 	//串口初始化为115200
	LCD_Init();
	W25QXX_Init();				//初始化W25Q128 和SPI2
	tp_dev.init();			//触摸屏初始化 
	usart2_init(36,usart2_baund);		//初始化串口2 
	LED_Init();
	Key_init();
	PWM_Init(999,71);   //pwm满值=7200，频率=10K
	DJ_PWM_Init(200,7199);       //控制舵机
	TIM3_Int_Init(9999,7199);
	while(font_init()) 			//检查字库
	{;}  
//		NRF24L01_Init();    		//初始化NRF24L01 
//				while(NRF24L01_Check())
//	{
//		LCD_ShowString(30,130,200,16,16,"NRF24L01 Error");
//		delay_ms(200);
//		LCD_Fill(30,130,239,130+16,WHITE);
// 		delay_ms(200);
//	}
//	NRF24L01_TX_Mode();	  
		while(PS_HandShake(&AS608Addr))//与AS608模块握手
	{
		delay_ms(400);
		LCD_Fill(0,40,240,80,WHITE);
		Show_Str_Mid(0,40,"未检测到模块!!!",16,240);
		delay_ms(800);
		LCD_Fill(0,40,240,80,WHITE);
		Show_Str_Mid(0,40,"尝试连接模块...",16,240);		  
	}
	LCD_Clear(WHITE);
	AS_Init();
	gly_id_save();
	while(motor_rest())    //电梯复位
	{
		Show_Str(30,140,120,24,"电梯复位中",24,0);
	}
	LCD_Clear(WHITE);
	delay_ms(100);

  	while(1)
	{
//		date_read();

		use_control();
//		if(KEY_UP==0||KEY_DOWN==0)
//		{
////		PWMA=500;
//		AIN1=0;
//		AIN2=0;
//		}
//		else
//		{
//		PWMA=500;
//		AIN1=0;  //下降
//		AIN2=1;
//		}
//		if(KEY_TOUCH==1)
//		{
//			Show_Str(30,140,96,24,"成功",24,0);
//		}
//		else
//		{
//			Show_Str(30,140,96,24,"失败",24,0);
//		}

	}	 
} 








