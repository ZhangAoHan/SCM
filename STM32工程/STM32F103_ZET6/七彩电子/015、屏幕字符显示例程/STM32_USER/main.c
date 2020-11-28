/*  main.c  */

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "LcdBsp.h"




/***********************************************************************/
//此程序适用于七彩光子太极M3—STM32F103开发板及部分兼容的STM32系统，
//只供学习使用，未经作者许可，不得用于其它任何用途！
/***********************************************************************/
 
 



int main(void)
{
	u32 i=0;
	delay_init();	    //延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	LED_Init();
	USART1_Init(115200);//串口1初始化
	
	LCD_Init();	
	POINT_COLOR = RED;
	LCD_ShowString(20,150,220,24,24,"STM32 LCD Test !");//显示字符串
	delay_ms(1000);
	delay_ms(1000);
	LCD_Fill(20,150,20+220,150+24,WHITE);
	while(1)
	{
		LED_TOGGLE(LED0);
		for(i=100;i>0;i--){
			LCD_ShowString(20,i*3,220,24,24,"STM32 LCD Test !");//显示字符串
			delay_ms(20);
			LCD_Fill(20,i*3,20+220,i*3+24,WHITE);
		}
	}
}




