/*  main.c  */

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "LcdBsp.h"
#include "LcdApi.h"
#include "image.h"
#include "key.h"
#include "beep.h"



/***********************************************************************/
//此程序适用于七彩光子太极M3—STM32F103开发板及部分兼容的STM32系统，
//只供学习使用，未经作者许可，不得用于其它任何用途！
/***********************************************************************/
 
 
 
 
/*
说明:
    按键为独立按键,本例程支持按键同时按下,
		按下KEY2之后再按KEY0会改变蜂鸣器状态
*/
 


int main(void)
{
	//u32 i=0;
	delay_init();	    //延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	LED_Init();
	USART1_Init(115200);//串口1初始化
	Key_Init();
	LCD_Init();	
	Beep_Init();
	POINT_COLOR = RED;
	LCD_ShowString(20,20,220,16,16,"STM32 Key Test !");//显示字符串

	while(1)
	{
		switch(Key_Scan(0)){
			case KEY0_PRES:{
				if(Key_GetSta(KEY2)){//按键同时按下测试,按住KEY2 再按KEY0
					printf("KEY0 Press!");
					BEEP_TOGGLE();
				}
				else{
					LCD_ShowString(20,50,220,16,16,"KEY0_PRES");//显示字符串
					printf("KEY2 & KEY0 Press!");
					LED_TOGGLE(LED0);
				}
				break;
			}
			case KEY1_PRES:{
				LCD_ShowString(20,50,220,16,16,"KEY1_PRES");//显示字符串
				printf("KEY1 Press!");
				LED_TOGGLE(LED1);
				break;
			}
			case KEY2_PRES:{
				LCD_ShowString(20,50,220,16,16,"KEY2_PRES");//显示字符串
				printf("KEY2 Press!");
				LED_TOGGLE(LED0);
				LED_TOGGLE(LED1);
				break;
			}
			case WKUP_PRES:{//关闭所有LED
				LCD_ShowString(20,50,220,16,16,"KEY3_PRES");//显示字符串
				printf("KEY3 Press!");
				LED_OFF(LED0);
				LED_OFF(LED1);
				break;
			}
		}
	}
}




