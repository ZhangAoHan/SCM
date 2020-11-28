/*  main.c  */

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "string.h"
#include "sdio_sdcard.h"




/***********************************************************************/
//此程序适用于七彩光子太极M3—STM32F103开发板及部分兼容的STM32系统，
//只供学习使用，未经作者许可，不得用于其它任何用途！
/***********************************************************************/
 


u8 test_buf[512];



int main(void)
{
	u8 t=0;
	u32 i=0;
	delay_init();	    //延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	LED_Init();
	//Beep_Init();
	USART1_Init(115200);//串口1初始化
	
	//延时1秒
	delay_ms(1000);
	
	printf("太极M3-STM32F103开发板SD卡实验开始 !\r\n");
	delay_ms(1000);
	
	//开始初始化SD卡
	while( SD_OK != SD_Init() ){
		delay_ms(30);
		t++;
		if(t%10==0){
			//BEEP_TOGGLE();
			LED_TOGGLE(LED1);
		}
		if(t>30){
			t=0;
			printf("SD 卡初始化失败 !\r\n");
		}
	}
	//BEEP_OFF();
	printf("\r\nSD 卡初始化成功 !\r\n");
	printf("SD卡容量: %dM\r\n",(u32)SDCardInfo.CardCapacity/1024/1024);
	
	delay_ms(1000);
	
	//读取0扇区数据
	if(SD_ReadDisk(test_buf,0,1)==0){		//读取0扇区的内容
		printf("\r\n读取成功 !读取到如下数据：\r\n");
		for(i=0;i<512;i++)printf("%02X ", test_buf[i]);//打印0扇区数据    	   
		printf("\r\n\r\n");
	}
	delay_ms(1000);
	//测试完成
	printf("\r\n\r\n测试完成 !\r\n");
	while(1)
	{
		delay_ms(500);
		LED_TOGGLE(LED0);
	}
}




