/*  main.c  */

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "w25qxx.h"
#include "string.h"
#include "24cxx.h"



/***********************************************************************/
//�˳����������߲ʹ���̫��M3��STM32F103�����弰���ּ��ݵ�STM32ϵͳ��
//ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;��
/***********************************************************************/
 
 
 
 
u32 count=0;
const char str[]={"EEPROM ���ݶ�д���� !"};
u8 temp[100];
u16 i=0;


int main(void)
{
	delay_init();	    //��ʱ������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	LED_Init();
	USART1_Init(115200);//����1��ʼ��
	AT24CXX_Init();			//IIC��ʼ�� 
	
	while(AT24CXX_Check())//��ⲻ��24c02
	{
		delay_ms(500);
		delay_ms(500);
		printf("24C02 Check Failed!\r\n");
	}
	
	printf("24C02 Check OK !\r\n");
	
	AT24CXX_Write(0,(u8*)str,strlen(str));
	printf("����д����ϣ�\r\n");
	for(i=0;i<100;i++){
		temp[i]=0;
	}
	
	AT24CXX_Read(0,temp,strlen(str));
	printf("\r\n��ȡ����������:\r\n%s\r\n",temp);
	
	while(1)
	{
		delay_ms(1000);
		LED_TOGGLE(LED0);
	}
}




