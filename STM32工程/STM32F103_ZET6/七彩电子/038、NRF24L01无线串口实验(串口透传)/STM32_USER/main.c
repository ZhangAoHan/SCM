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
//�˳����������߲ʹ���̫��M3��STM32F103�����弰���ּ��ݵ�STM32ϵͳ��
//ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;��
/***********************************************************************/
 
 
// ע��  !!!!!!!!!!!!!!!!!!!!
// �˴�SPI2��ʱ��������W25Q64��ʱ�������ı�,�̲�����W25Q64��ʱ�����



// ע��,������ÿ��ֻ�ܷ���С��31���ֽ�,�ɸ�����Ҫ���м���ѭ�����͹���





#define UART_RX_MAX_LEN 31   //ÿһ֡�������ݵ���󳤶�,���ܴ���31 !!!!!


u8 nrf_buf[32]={0};



u8 Uart_RxCnt=0;
u8 Uart_RxBuf[UART_RX_MAX_LEN+1]={0};



int main(void)
{
	u8 t=0;
	delay_init();	    //��ʱ������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	LED_Init();
	USART1_Init(115200);//����1��ʼ��
	Pin_ModeSet(PB12,OUTPUT_PP|OUT_H);//����W25Q64 SPI �ӿ�,��ֹ����24L01
	Key_Init();
	
	NRF24L01_Init();
	while(NRF24L01_Check()!=0){
		printf("�������NRF24L01ģ���Ƿ�����ȷ����!\r\n");
		delay_ms(500);
		LED_TOGGLE(LED0);
	}
	NRF24L01_Init();
	
	printf("NRF24L01 ��ʼ���ɹ�!\r\n");
	while(1)
	{
		
		if(NRF24L01_RxPacket(nrf_buf)==0){//���յ�����
			LED_TOGGLE(LED1);
			USART_SendBuf(USART1,nrf_buf,nrf_buf[31]);
		}
		
		
		t=Uart_RxCnt;
		delay_ms(2);//��ʱ2ms,���Ƿ����µ����ݽ��յ�
		if((t!=0)&&(t==Uart_RxCnt)){//���յ�������,�ҽ��������
			LED_TOGGLE(LED0);
			Uart_RxBuf[31]=(u8)t;
			NRF24L01_Set_Mode(NRF_MODEL_TX);//�л�������ģʽ
			if(NRF24L01_TxPacket(Uart_RxBuf)==TX_OK){
				//���ͳɹ�
			}
			NRF24L01_Set_Mode(NRF_MODEL_RX);//�������,�л�������ģʽ
			Uart_RxCnt=0;
			t=0;
		}
		
	}
}


//����1�жϺ���
void USART1_IRQHandler(void)                	//����1�жϷ������
{
	u8 res;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		res =USART_ReceiveData(USART1);	//��ȡ���յ�������
		//USART_SendData(USART1,res); 
		if(Uart_RxCnt<UART_RX_MAX_LEN){
			Uart_RxBuf[Uart_RxCnt++]=res;
		}
	}
}

















