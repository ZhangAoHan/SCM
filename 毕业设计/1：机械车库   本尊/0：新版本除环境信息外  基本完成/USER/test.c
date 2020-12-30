#include "sys.h"
#include "usart.h"		
#include "delay.h"	 
#include "lcd.h"
#include "touch.h"  
#include "w25q128.h"  
#include "text.h"	
#include "motor_control.h"
#include "motor.h"
#include "led.h"
#include "timer.h"
#include "usart2.h"
#include "AS608.h" 
#include "malloc.h"	  
#include "as608_control.h"
#include "display.h"

#define usart2_baund  57600//串口2波特率，根据指纹模块波特率更改



u8 use_start=0;   //按键启动标准量
u8 dl_success=0;   //开始进行停车操作的标志量
u8 set=0;     //用于跳出while（1）的标准量
u16 now_people_id=300;           //预设值大于299  表面没有id
u16 now_people_mark=0;         //匹配得分   用于用户刷指纹成功后的登录界面
u8 page=0;
u8 gly_page=0;
u16 car_id[4]={300,300,300,300};      //使用停车位的用户ID
u16 t1=0,t2=0,t3=0,t4=0;     //计时
u8 use1=0,use2=0,use3=0,use4=0;   
u8 people_car=0;    //用户选择完停车位后  用于传递选择的楼层信息  为了下一步的电机控制
int main(void)
{				 

	Stm32_Clock_Init(9);	//系统时钟设置
	delay_init(72);	  		//延时初始化
	uart_init(72,115200); 	//串口初始化为115200
	usart2_init(36,usart2_baund);		//初始化串口2 
	LCD_Init();
	W25QXX_Init();				//初始化W25Q128 和SPI2
	tp_dev.init();			//触摸屏初始化 
	my_mem_init(SRAMIN);		//初始化内部内存池
//	exfuns_init();				//为fatfs相关变量申请内存  
// 	f_mount(fs[1],"1:",1); 		//挂载FLASH.
	while(font_init()) 			//检查字库
	{;}  
	Key_init();
	PWM_Init(999,71);   //pwm满值=7200，频率=10K
	DJ_PWM_Init(200,7199);       //控制舵机
	TIM3_Int_Init(9999,7199);	
	while(motor_rest())    //电梯复位
	{
		Show_Str(30,140,120,24,"电梯复位中",24,0);
	}
	as608_use_init();
	LCD_Clear(WHITE);
	delay_ms(100);

  	while(1)
	{
		if(page==0)
		{
			page_0();
		}
		else if(page==1)   //管理员界面
		{
			if(gly_page==0)
			{
				gly_page_0();
			}
			else if(gly_page==1)
			{
				gly_page_1();
			}
			else if(gly_page==2)
			{
				gly_page_2();
			}
			else if(gly_page==3)
			{
				gly_page_3();
			}
		}
		else if(page==2)
		{
			save_car_display();
		}
		else if(page==3)
		{
			qu_car_display();
		}
	}	 
} 

//		cl_display(1,1);
//		delay_ms(50);
//		LCD_Clear(WHITE); 
//		Show_Str_Mid(0,150,"请继续停2楼",24,240);
//		delay_ms(3000);
//		cl_display(2,1);
//		delay_ms(50);
//		LCD_Clear(WHITE); 
//		delay_ms(50);
//		Show_Str_Mid(0,150,"操作完成",24,240);




