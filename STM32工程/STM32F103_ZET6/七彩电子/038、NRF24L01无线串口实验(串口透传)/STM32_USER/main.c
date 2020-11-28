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



// 注意,本例程每次只能发送小于31个字节,可根据需要自行加入循环发送功能





#define UART_RX_MAX_LEN 31   //每一帧串口数据的最大长度,不能大于31 !!!!!


u8 nrf_buf[32]={0};



u8 Uart_RxCnt=0;
u8 Uart_RxBuf[UART_RX_MAX_LEN+1]={0};



int main(void)
{
	u8 t=0;
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
		
		if(NRF24L01_RxPacket(nrf_buf)==0){//接收到数据
			LED_TOGGLE(LED1);
			USART_SendBuf(USART1,nrf_buf,nrf_buf[31]);
		}
		
		
		t=Uart_RxCnt;
		delay_ms(2);//延时2ms,看是否有新的数据接收到
		if((t!=0)&&(t==Uart_RxCnt)){//接收到了数据,且接收完成了
			LED_TOGGLE(LED0);
			Uart_RxBuf[31]=(u8)t;
			NRF24L01_Set_Mode(NRF_MODEL_TX);//切换到发送模式
			if(NRF24L01_TxPacket(Uart_RxBuf)==TX_OK){
				//发送成功
			}
			NRF24L01_Set_Mode(NRF_MODEL_RX);//发送完毕,切换到接收模式
			Uart_RxCnt=0;
			t=0;
		}
		
	}
}


//串口1中断函数
void USART1_IRQHandler(void)                	//串口1中断服务程序
{
	u8 res;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		res =USART_ReceiveData(USART1);	//读取接收到的数据
		//USART_SendData(USART1,res); 
		if(Uart_RxCnt<UART_RX_MAX_LEN){
			Uart_RxBuf[Uart_RxCnt++]=res;
		}
	}
}

















