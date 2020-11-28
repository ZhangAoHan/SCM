
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
	
	//说明!!!
	//说明!!!
	//说明!!!
	//因为串口1不能同时接到RS232接口USB转串口电路,
	//在使用RS232接口时需要调节纽扣电池上方的跳线帽,调节方式如下:
	//
	//            PA9
	//             |
	// CH340_RX ■ ■-■ RS232_RX
	// CH340_TX ■ ■-■ RS232_TX
	//             |
	//            PA10
	//通过将两个横向的跳线帽接到右侧来将STM32的串口1连接到232接口,
	//此时串口1也和ch340断开了连接,即USB转串口被断开
	
	//另外说明:
	//这个例程本质上也是串口通信,只是要通过跳线选择RS232接口而已,与之前的串口例程并无其他差异,
	//单独作为例程只是给是不很熟悉这方面知识的朋友提供个方便
	
	
	while(1)
	{
		delay_ms(1000);
		delay_ms(1000);
		LED_TOGGLE(LED0);
		printf("太极M3 STM32开发板RS232串口测试程序，第%d次发送。\r\n\r\n",count++);
		USART_SendString(USART1,"提示:\r\n    开发板接收到数据会原样返回！支持串口1、2、3、4、5");
		USART_SendByte(USART1,'\r');
		USART_SendByte(USART1,'\n');
		USART_SendBuf(USART1,"\r\n",2);
	}
}




