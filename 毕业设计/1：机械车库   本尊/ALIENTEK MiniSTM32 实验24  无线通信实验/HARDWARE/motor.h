#ifndef __MOTOR_H
#define __MOTOR_H
#include <sys.h>	 

#define PWMA   TIM1->CCR1  //PA8
//#define PWMB   TIM3->CCR2   //����A9
#define AIN2   PBout(15)   //����
#define AIN1   PBout(14)
//#define BIN1   PAout(8)   //����
//#define BIN2   PAout(9)
//#define PWMB   TIM1->CCR4  //PA11
void PWM_Init(u16 arr,u16 psc);  
void TIM3_PWM_Init(u16 arr,u16 psc);
void state_scan(void);
void motor_STOP(void);
//void use_motor(void);
#endif

/*  
AIN1=1 AIN2=0; ->���� ���� ǰ��
BIN1=1 BIN2=0; ->���� ���� ����
PWMԽ��ת��Խ��
*/
