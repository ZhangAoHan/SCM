#ifndef __MOTOR_H
#define __MOTOR_H
#include <sys.h>	 

#define PWMA   TIM1->CCR1  //PA8
#define AIN2   PBout(15)   //右轮
#define AIN1   PBout(14)
#define BIN1   PBout(13)   //左轮
#define BIN2   PBout(12)
#define PWMB   TIM1->CCR4  //PA11
void PWM_Init(u16 arr,u16 psc);  
void Motor_Init(void);            //输出pwm函数

void Encoder_Init_TIM2(void);     //读编码器函数
void Encoder_Init_TIM4(void);
int Read_Encoder(u8 TIMX);   
void TIM4_IRQHandler(void);
void TIM2_IRQHandler(void);

#endif

/*  
AIN1=1 AIN2=0; ->方向 右轮 顺时针转
BIN1=1 BIN2=0; ->方向 左轮 顺时针转
PWM越大，转的越快
*/
