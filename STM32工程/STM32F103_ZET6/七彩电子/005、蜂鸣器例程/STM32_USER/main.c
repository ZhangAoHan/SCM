
#include "sys.h"
#include "delay.h"
#include "beep.h"

/***********************************************************************/
//此程序适用于七彩光子太极M3—STM32F103开发板及部分兼容的STM32系统，
//只供学习使用，未经作者许可，不得用于其它任何用途！
/***********************************************************************/
 



int main(void)
{
	delay_init();	    //延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	Beep_Init();
	while(1)
	{
		BEEP_ON();
		delay_ms(100);
		BEEP_TOGGLE();
		delay_ms(200);
		BEEP_TOGGLE();
		delay_ms(100);
		BEEP_TOGGLE();
		delay_ms(100);
		BEEP_TOGGLE();
		delay_ms(200);
		BEEP_OFF();
		delay_ms(1000);
	}
}




