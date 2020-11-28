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
	delay_init();	    //延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	LED_Init();
	USART1_Init(115200);//串口1初始化
	
	LCD_Init();	
	
	while(1)
	{
		LED_TOGGLE(LED0);
		LCD_Clear(BLUE);
		LCD_DrawRectangle(50,50,100,100);//画矩形
		delay_ms(500);
		LED_TOGGLE(LED1);
		LCD_Clear(RED);
		LCD_DrawLine(20,20,200,200);
		delay_ms(500);
		LED_TOGGLE(LED0);
		LCD_Clear(YELLOW);
		LCD_Draw_Circle(100,100,90);
		delay_ms(500);
	}
}




