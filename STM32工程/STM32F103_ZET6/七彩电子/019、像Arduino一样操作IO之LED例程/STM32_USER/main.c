/*  main.c  */

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "ezio.h"


/*************************** �ļ�˵�� *******************************/
//ezio ��Ƭ��IO��������������װ,������������д�߳��Ľṹ��,һ�������㶨
//��Arduinoһ������IO
//����:�߲ʹ���
//�˳����������߲ʹ���̫��M3��STM32F103�����弰���ּ��ݵ�STM32ϵͳ��
//�Ա�����"�߲ʹ��� ̫��M3 STM32������"���򳬸��Լ۱ȿ�������ȡ��������
//ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;��
/********************************************************************/ 


#define LED0 PB5
#define LED1 PE5 


int main(void)
{
	delay_init();	    //��ʱ������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	USART1_Init(115200);//����1��ʼ��

	Pin_ModeSet(LED0,OUTPUT);//LED0��ʼ��
	Pin_ModeSet(PE5,OUTPUT);//LED1��ʼ��

	while(1)
	{
		Pin_Write(LED0,0);//�͵�ƽ����
		Pin_Write(LED1,1);//�ߵ�ƽϨ��
		delay_ms(500);
		Pin_Write(PB5,1);//�ߵ�ƽϨ��
		Pin_Write(PE5,0);//�͵�ƽ����
		delay_ms(500);
		Pin_Toggle(PB5);
		Pin_Toggle(PE5);
		delay_ms(500);
		Pin_WriteHigh(PB5);
		Pin_WriteLow(PE5);
		delay_ms(500);
	}
}




