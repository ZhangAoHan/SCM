/*  main.c  */

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "string.h"
#include "sdio_sdcard.h"




/***********************************************************************/
//�˳����������߲ʹ���̫��M3��STM32F103�����弰���ּ��ݵ�STM32ϵͳ��
//ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;��
/***********************************************************************/
 


u8 test_buf[512];



int main(void)
{
	u8 t=0;
	u32 i=0;
	delay_init();	    //��ʱ������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	LED_Init();
	//Beep_Init();
	USART1_Init(115200);//����1��ʼ��
	
	//��ʱ1��
	delay_ms(1000);
	
	printf("̫��M3-STM32F103������SD��ʵ�鿪ʼ !\r\n");
	delay_ms(1000);
	
	//��ʼ��ʼ��SD��
	while( SD_OK != SD_Init() ){
		delay_ms(30);
		t++;
		if(t%10==0){
			//BEEP_TOGGLE();
			LED_TOGGLE(LED1);
		}
		if(t>30){
			t=0;
			printf("SD ����ʼ��ʧ�� !\r\n");
		}
	}
	//BEEP_OFF();
	printf("\r\nSD ����ʼ���ɹ� !\r\n");
	printf("SD������: %dM\r\n",(u32)SDCardInfo.CardCapacity/1024/1024);
	
	delay_ms(1000);
	
	//��ȡ0��������
	if(SD_ReadDisk(test_buf,0,1)==0){		//��ȡ0����������
		printf("\r\n��ȡ�ɹ� !��ȡ���������ݣ�\r\n");
		for(i=0;i<512;i++)printf("%02X ", test_buf[i]);//��ӡ0��������    	   
		printf("\r\n\r\n");
	}
	delay_ms(1000);
	//�������
	printf("\r\n\r\n������� !\r\n");
	while(1)
	{
		delay_ms(500);
		LED_TOGGLE(LED0);
	}
}




