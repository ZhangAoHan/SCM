/*  main.c  */

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "w25qxx.h"
#include "string.h"

/***********************************************************************/
//�˳����������߲ʹ���̫��M3��STM32F103�����弰���ּ��ݵ�STM32ϵͳ��
//ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;��
/***********************************************************************/
 
 
 
 
u32 count=0;
const char str[]={"SPI FLASH ���ݶ�д���� !"};
u8 temp[100];
u16 i=0;


int main(void)
{
	delay_init();	    //��ʱ������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	LED_Init();
	USART1_Init(115200);//����1��ʼ��
	W25QXX_Init();
	
	//�жϲ���ӡflash����
	printf("\r\n\r\nFlash���� : ");
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
	printf("����д����ϣ�\r\n");
	for(i=0;i<100;i++){
		temp[i]=0;
	}
	W25QXX_Read(temp,0,strlen(str));
	printf("\r\n��ȡ����������:\r\n%s\r\n",temp);
	
	while(1)
	{
		delay_ms(1000);
		LED_TOGGLE(LED0);
	}
}




