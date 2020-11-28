
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"


/***********************************************************************/
//作者:七彩光子
//此程序适用于七彩光子太极M3—STM32F103开发板及部分兼容的STM32系统，
//淘宝搜索"七彩光子 太极M3 STM32开发板"购买超高性价比开发板或获取更多资料
//只供学习使用，未经作者许可，不得用于其它任何用途！
/***********************************************************************/
 

//程序功能:
    //printf函数功能实现,可配置串口1~5任意一个串口为printf输出口
    //修改usart.c中的 PRINTF_COM 宏定义可改变输出串口




int i=0;
float f=0;



u32 count=0;


int main(void)
{
	delay_init();	    //延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	LED_Init();
	
	
	//串口初始化 ,需要使用哪一个则初始化哪一个,注意在usart.c中修改printf的对应串口
	USART1_Init(115200);//串口1初始化
//	USART2_Init(115200);//串口2初始化
//	USART3_Init(115200);//串口3初始化
//	UART4_Init (115200);//串口4初始化
//	UART5_Init (115200);//串口5初始化
	
	
	while(1)
	{
		delay_ms(1000);
		LED_TOGGLE(LED0);
		printf("-------------------我是分割线--------------------\r\n\r\n");
		printf("串口printf测试程序，第%d次发送。\r\n",count++);
		printf("printf字符串测试1\r\n");
		printf("%s\r\n","printf字符串测试2");
		printf("printf整数发送测试:%d\r\n",i);
		i++;
		printf("printf浮点数发送测试:%f\r\n",f);
		f += 0.000001;
		printf("\r\n\r\n");
		
	}
}




