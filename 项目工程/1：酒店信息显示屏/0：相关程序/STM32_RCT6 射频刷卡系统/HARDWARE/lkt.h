#ifndef __LKT_H
#define __LKT_H	 
#include "sys.h"

//LED�˿ڶ���
#define LED0 PAout(8)// PA8
#define LED1 PDout(2)// PD2	

void LED_Init(void);//��ʼ��		

#define KEY0 PAin(13)   //PA13
#define KEY1 PAin(15)	//PA15 
#define KEY2 PAin(0)	//PA0  WK_UP
	 
void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(void);  //����ɨ�躯��	

//ͨ���ı�TIM3->CCR2��ֵ���ı�ռ�ձȣ��Ӷ�����LED0������
#define LED0_PWM_VAL TIM3->CCR2 

void Timerx_Init(u16 arr,u16 psc);
void PWM_Init(u16 arr,u16 psc);
#endif
