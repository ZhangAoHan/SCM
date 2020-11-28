/*  main.c  */

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "w25qxx.h"
#include "string.h"
#include "24l01.h"
#include "ezio.h"
#include "key.h"
#include "string.h"


/***********************************************************************/
//此程序适用于七彩光子太极M3—STM32F103开发板及部分兼容的STM32系统，
//只供学习使用，未经作者许可，不得用于其它任何用途！
/***********************************************************************/
 
 
// 注意  !!!!!!!!!!!!!!!!!!!!
// 此处SPI2的时序设置与W25Q64的时序有所改变,固不能与W25Q64的时序混用



u8 nrf_buf[32]={0};




int main(void)
{
	delay_init();	    //延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	LED_Init();
	USART1_Init(115200);//串口1初始化
	Pin_ModeSet(PB12,OUTPUT_PP|OUT_H);//禁用W25Q64 SPI 接口,防止干扰24L01
	Key_Init();
	
	NRF24L01_Init();
	while(NRF24L01_Check()!=0){
		printf("请插入检查NRF24L01模块是否已正确插入!\r\n");
		delay_ms(500);
		LED_TOGGLE(LED0);
	}
	NRF24L01_Init();
	
	printf("NRF24L01 初始化成功!\r\n");
	while(1)
	{
		delay_ms(2);
		
		if(NRF24L01_RxPacket(nrf_buf)==0){//接收到数据
			LED_TOGGLE(LED1);
			printf("接收到数据: ");
			printf("%s\r\n",nrf_buf);
		}
		
		switch(Key_Scan(0)){//安检扫描
			case KEY0_PRES:{//--------------KEY0被按下
				LED_TOGGLE(LED0);
				printf("KEY0 Press!");
				memcpy(nrf_buf,"KEY0 Press!",strlen("KEY0 Press!")+1);
				NRF24L01_Set_Mode(NRF_MODEL_TX);//切换到发送模式
				if(NRF24L01_TxPacket(nrf_buf)==TX_OK){
					printf("   发送成功!\r\n");
				}
				else{
					printf("   发送失败!\r\n");
				}
				NRF24L01_Set_Mode(NRF_MODEL_RX);//发送完毕,切换到接收模式
				break;
			}
			case KEY1_PRES:{//--------------KEY1被按下
				LED_TOGGLE(LED0);
				printf("KEY1 Press!");
				memcpy(nrf_buf,"KEY1 Press!",strlen("KEY1 Press!")+1);
				NRF24L01_Set_Mode(NRF_MODEL_TX);//切换到发送模式
				if(NRF24L01_TxPacket(nrf_buf)==TX_OK){
					printf("   发送成功!\r\n");
				}
				else{
					printf("   发送失败!\r\n");
				}
				NRF24L01_Set_Mode(NRF_MODEL_RX);//发送完毕,切换到接收模式
				break;
			}
			case KEY2_PRES:{//--------------KEY2被按下
				LED_TOGGLE(LED0);
				printf("KEY2 Press!");
				memcpy(nrf_buf,"KEY2 Press!",strlen("KEY2 Press!")+1);
				NRF24L01_Set_Mode(NRF_MODEL_TX);//切换到发送模式
				if(NRF24L01_TxPacket(nrf_buf)==TX_OK){
					printf("   发送成功!\r\n");
				}
				else{
					printf("   发送失败!\r\n");
				}
				NRF24L01_Set_Mode(NRF_MODEL_RX);//发送完毕,切换到接收模式
				break;
			}
			case WKUP_PRES:{////--------------KEY3被按下
				LED_TOGGLE(LED0);
				printf("KEY3 Press!");
				memcpy(nrf_buf,"KEY3 Press!",strlen("KEY3 Press!")+1);
				NRF24L01_Set_Mode(NRF_MODEL_TX);//切换到发送模式
				if(NRF24L01_TxPacket(nrf_buf)==TX_OK){
					printf("   发送成功!\r\n");
				}
				else{
					printf("   发送失败!\r\n");
				}
				NRF24L01_Set_Mode(NRF_MODEL_RX);//发送完毕,切换到接收模式
				break;
			}
		}
	}
}




