/*  main.c  */

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "w25qxx.h"
#include "string.h"

/***********************************************************************/
//此程序适用于七彩光子太极M3—STM32F103开发板及部分兼容的STM32系统，
//只供学习使用，未经作者许可，不得用于其它任何用途！
/***********************************************************************/
 
 
 
 
u32 count=0;
const char str[]={"SPI FLASH 数据读写测试 !"};
u8 temp[100];
u16 i=0;


int main(void)
{
	delay_init();	    //延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	LED_Init();
	USART1_Init(115200);//串口1初始化
	W25QXX_Init();
	
	//判断并打印flash类型
	printf("\r\n\r\nFlash类型 : ");
	switch(W25QXX_TYPE){
		case W25Q80:
			printf("W25Q80");
		break;
		case W25Q16:
			printf("W25Q16");
		break;
		case W25Q32:
			printf("W25Q32");
		break;
		case W25Q64:
			printf("W25Q64");
		break;
		case W25Q128:
			printf("W25Q128");
		break;
	}
	printf("\r\n");
	
	W25QXX_Write((u8*)str,0,strlen(str));
	printf("数据写入完毕！\r\n");
	for(i=0;i<100;i++){
		temp[i]=0;
	}
	W25QXX_Read(temp,0,strlen(str));
	printf("\r\n读取到如下数据:\r\n%s\r\n",temp);
	
	while(1)
	{
		delay_ms(1000);
		LED_TOGGLE(LED0);
	}
}




