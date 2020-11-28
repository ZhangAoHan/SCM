
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"


/***********************************************************************/
//此程序适用于七彩光子太极M3—STM32F103开发板及部分兼容的STM32系统，
//只供学习使用，未经作者许可，不得用于其它任何用途！
/***********************************************************************/
 
 
u32 count=0;


int main(void)
{
	delay_init();	    //延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	LED_Init();
	
	USART1_Init(115200);//串口1初始化
	USART2_Init(115200);//串口2初始化
	USART3_Init(115200);//串口3初始化
	UART4_Init (115200);//串口4初始化
	UART5_Init (115200);//串口5初始化
	
	
	while(1)
	{
		delay_ms(1000);
		delay_ms(1000);
		LED_TOGGLE(LED0);
		printf("太极M3 STM32开发板串口测试程序，第%d次发送。\r\n\r\n",count++);
		USART_SendString(USART1,"提示:\r\n    开发板接收到数据会原样返回！支持串口1、2、3、4、5");
		USART_SendByte(USART1,'\r');
		USART_SendByte(USART1,'\n');
		USART_SendBuf(USART1,"\r\n",2);
	}
}




