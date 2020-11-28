#ifndef __LKT_H
#define __LKT_H	 
#include "sys.h"

//LED端口定义
#define LED0 PAout(8)// PA8
#define LED1 PDout(2)// PD2	

void LED_Init(void);//初始化		

#define KEY0 PAin(13)   //PA13
#define KEY1 PAin(15)	//PA15 
#define KEY2 PAin(0)	//PA0  WK_UP
	 
void KEY_Init(void);//IO初始化
u8 KEY_Scan(void);  //按键扫描函数	

//通过改变TIM3->CCR2的值来改变占空比，从而控制LED0的亮度
#define LED0_PWM_VAL TIM3->CCR2 

void Timerx_Init(u16 arr,u16 psc);
void PWM_Init(u16 arr,u16 psc);
#endif
