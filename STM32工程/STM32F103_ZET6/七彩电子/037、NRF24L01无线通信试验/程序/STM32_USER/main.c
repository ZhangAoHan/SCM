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



u8 nrf_buf[32]={0};




int main(void)
{
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
		delay_ms(2);
		
		if(NRF24L01_RxPacket(nrf_buf)==0){//���յ�����
			LED_TOGGLE(LED1);
			printf("���յ�����: ");
			printf("%s\r\n",nrf_buf);
		}
		
		switch(Key_Scan(0)){//����ɨ��
			case KEY0_PRES:{//--------------KEY0������
				LED_TOGGLE(LED0);
				printf("KEY0 Press!");
				memcpy(nrf_buf,"KEY0 Press!",strlen("KEY0 Press!")+1);
				NRF24L01_Set_Mode(NRF_MODEL_TX);//�л�������ģʽ
				if(NRF24L01_TxPacket(nrf_buf)==TX_OK){
					printf("   ���ͳɹ�!\r\n");
				}
				else{
					printf("   ����ʧ��!\r\n");
				}
				NRF24L01_Set_Mode(NRF_MODEL_RX);//�������,�л�������ģʽ
				break;
			}
			case KEY1_PRES:{//--------------KEY1������
				LED_TOGGLE(LED0);
				printf("KEY1 Press!");
				memcpy(nrf_buf,"KEY1 Press!",strlen("KEY1 Press!")+1);
				NRF24L01_Set_Mode(NRF_MODEL_TX);//�л�������ģʽ
				if(NRF24L01_TxPacket(nrf_buf)==TX_OK){
					printf("   ���ͳɹ�!\r\n");
				}
				else{
					printf("   ����ʧ��!\r\n");
				}
				NRF24L01_Set_Mode(NRF_MODEL_RX);//�������,�л�������ģʽ
				break;
			}
			case KEY2_PRES:{//--------------KEY2������
				LED_TOGGLE(LED0);
				printf("KEY2 Press!");
				memcpy(nrf_buf,"KEY2 Press!",strlen("KEY2 Press!")+1);
				NRF24L01_Set_Mode(NRF_MODEL_TX);//�л�������ģʽ
				if(NRF24L01_TxPacket(nrf_buf)==TX_OK){
					printf("   ���ͳɹ�!\r\n");
				}
				else{
					printf("   ����ʧ��!\r\n");
				}
				NRF24L01_Set_Mode(NRF_MODEL_RX);//�������,�л�������ģʽ
				break;
			}
			case WKUP_PRES:{////--------------KEY3������
				LED_TOGGLE(LED0);
				printf("KEY3 Press!");
				memcpy(nrf_buf,"KEY3 Press!",strlen("KEY3 Press!")+1);
				NRF24L01_Set_Mode(NRF_MODEL_TX);//�л�������ģʽ
				if(NRF24L01_TxPacket(nrf_buf)==TX_OK){
					printf("   ���ͳɹ�!\r\n");
				}
				else{
					printf("   ����ʧ��!\r\n");
				}
				NRF24L01_Set_Mode(NRF_MODEL_RX);//�������,�л�������ģʽ
				break;
			}
		}
	}
}




