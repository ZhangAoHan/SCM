
#include "sys.h"
#include "delay.h"
#include "led.h"

/***********************************************************************/
//此程序适用于七彩光子太极M3—STM32F103开发板及部分兼容的STM32系统，
//只供学习使用，未经作者许可，不得用于其它任何用途！
/***********************************************************************/
 



int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	delay_init();	    //延时函数初始化
	LED_Init();
	while(1)
	{
		LED_ON(LED0);
		delay_ms(500);
		LED_OFF(LED0);
		LED_ON(LED1);
		delay_ms(500);
		LED_OFF(LED1);
	}
}




