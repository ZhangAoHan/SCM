
#include "sys.h"
#include "delay.h"

/***********************************************************************/
//此程序适用于七彩光子太极M3—STM32F103开发板及部分兼容的STM32系统，
//只供学习使用，未经作者许可，不得用于其它任何用途！
/***********************************************************************/
 
#define LED0_GPIO  GPIOB
#define LED1_GPIO  GPIOE

#define LED0_PIN   GPIO_Pin_5
#define LED1_PIN   GPIO_Pin_5


int main(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	delay_init();	    //延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE, ENABLE);	 //使能PB,PE端口时钟

	GPIO_InitStructure.GPIO_Pin = LED0_PIN;				       //LED0端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(LED0_GPIO, &GPIO_InitStructure);					   //根据设定参数初始化LED0
	GPIO_SetBits(LED0_GPIO,LED0_PIN);						         //LED0输出高

	GPIO_InitStructure.GPIO_Pin = LED1_PIN;	    		     //LED1端口配置, 推挽输出
	GPIO_Init(LED1_GPIO, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GPIO_SetBits(LED1_GPIO,LED1_PIN); 						         //LED1输出高 
	
	
	while(1)
	{
		GPIO_ResetBits(LED0_GPIO,LED0_PIN); 
		delay_ms(500);
		GPIO_SetBits(LED0_GPIO,LED0_PIN);
		GPIO_ResetBits(LED1_GPIO,LED1_PIN); 
		delay_ms(500);
		GPIO_SetBits(LED1_GPIO,LED1_PIN);
	}
}




