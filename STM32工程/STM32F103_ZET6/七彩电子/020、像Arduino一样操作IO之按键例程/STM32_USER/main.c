/*  main.c  */

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "ezio.h"


/*************************** �ļ�˵�� *******************************/
//ezio ��Ƭ��IO��������������װ,������������д�߳��Ľṹ��,һ�������㶨
//��Arduinoһ������IO
//�˳����������߲ʹ���̫��M3��STM32F103�����弰���ּ��ݵ�STM32ϵͳ��
//�Ա�����"�߲ʹ��� ̫��M3 STM32������"���򳬸��Լ۱ȿ�������ȡ��������
//ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;��
/********************************************************************/ 


#define LED0 PB5
#define LED1 PE5 


//key0 PE4
//key1 PE3
//key2 PE2
//key3/key_up PA0 



int main(void)
{
	delay_init();	    //��ʱ������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	USART1_Init(115200);//����1��ʼ��

	Pin_ModeSet(LED0,OUTPUT|OUT_H);//LED0��ʼ��
	Pin_ModeSet(LED1,OUTPUT|OUT_H);//LED1��ʼ��

	Pin_ModeSet(PE4,INPUT);//KEY0 ����
	Pin_ModeSet(PE3,INPUT);//KEY1 ����
	Pin_ModeSet(PE2,INPUT);//KEY2 ����
	Pin_ModeSet(PA0,INPUT_PD);////KEY3�ߵ�ƽ��Ч,ƽʱ����
	
	while(1)
	{
		//KEY0
		if(Pin_Read(PE4)==0){
			delay_ms(10);
			if(Pin_Read(PE4)==0){
				Pin_Toggle(LED1);
				while(Pin_Read(PE4)==0);
			}
		}
		//KEY1
		if(Pin_Read(PE3)==0){
			delay_ms(10);
			if(Pin_Read(PE3)==0){
				Pin_Toggle(LED1);
				while(Pin_Read(PE3)==0);
			}
		}
		//KEY2
		if(Pin_Read(PE2)==0){
			delay_ms(10);
			if(Pin_Read(PE2)==0){
				Pin_Toggle(LED1);
				while(Pin_Read(PE2)==0);
			}
		}
		//KEY3
		if(Pin_Read(PA0)==1){
			delay_ms(10);
			if(Pin_Read(PA0)==1){
				Pin_Toggle(LED1);
				while(Pin_Read(PA0)==1);
			}
		}
	}
}




