/*  main.c  */

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "w25qxx.h"
#include "string.h"
#include "24cxx.h"



/***********************************************************************/
//此程序适用于七彩光子太极M3—STM32F103开发板及部分兼容的STM32系统，
//只供学习使用，未经作者许可，不得用于其它任何用途！
/***********************************************************************/
 
 
 
 
u32 count=0;
const char str[]={"EEPROM 数据读写测试 !"};
u8 temp[100];
u16 i=0;


int main(void)
{
	delay_init();	    //延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	LED_Init();
	USART1_Init(115200);//串口1初始化
	AT24CXX_Init();			//IIC初始化 
	
	while(AT24CXX_Check())//检测不到24c02
	{
		delay_ms(500);
		delay_ms(500);
		printf("24C02 Check Failed!\r\n");
	}
	
	printf("24C02 Check OK !\r\n");
	
	AT24CXX_Write(0,(u8*)str,strlen(str));
	printf("数据写入完毕！\r\n");
	for(i=0;i<100;i++){
		temp[i]=0;
	}
	
	AT24CXX_Read(0,temp,strlen(str));
	printf("\r\n读取到如下数据:\r\n%s\r\n",temp);
	
	while(1)
	{
		delay_ms(1000);
		LED_TOGGLE(LED0);
	}
}




