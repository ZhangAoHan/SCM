#include "led.h"

void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PA,PD�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_12|GPIO_Pin_14|GPIO_Pin_15;				 //LED0-->PA.8 �˿����ã�ʹ�õ���A8�ţ�
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.8(�����Ѿ����������趨�ŵGPIO_InitStructure�������ˣ�����ֱ�ӵ��ã����������ʼ��GPIODʱ��Ҳ����ֱ�ӵ���)
 GPIO_SetBits(GPIOB,GPIO_Pin_13|GPIO_Pin_12|GPIO_Pin_14|GPIO_Pin_15);						 //PA.8 �����(ResetBits������͵�ƽ)
						 
}
 
