#ifndef __MOTOR
#define __MOTOR

#include "timer.h"
/*******************************************************************
常量宏定义
*******************************************************************/

/*
*左电机四引脚
*/ 
#define MT_LFT_A1 GPIO_Pin_3  
#define MT_LFT_A2 GPIO_Pin_6
#define MT_LFT_B1 GPIO_Pin_7
#define MT_LFT_B2 GPIO_Pin_8
/*
*右电机四引脚
*/
#define MT_RGT_A1 GPIO_Pin_13
#define MT_RGT_A2 GPIO_Pin_11  
#define MT_RGT_B1 GPIO_Pin_12
#define MT_RGT_B2 GPIO_Pin_1


/*
*左电机拍数宏定义
*/
#define MT_LFT_OFF() GPIO_ResetBits(GPIOA,MT_LFT_A1|MT_LFT_A2|MT_LFT_B1|MT_LFT_B2)

#define MT_LFT_STEP1_SET() GPIO_ResetBits(GPIOA,MT_LFT_A1|MT_LFT_A2|MT_LFT_B1|MT_LFT_B2); \
                           GPIO_SetBits(GPIOA,MT_LFT_A1)
													 
#define MT_LFT_STEP2_SET() GPIO_ResetBits(GPIOA,MT_LFT_A1|MT_LFT_A2|MT_LFT_B1|MT_LFT_B2); \
                           GPIO_SetBits(GPIOA,MT_LFT_A1|MT_LFT_B1)
													 
#define MT_LFT_STEP3_SET() GPIO_ResetBits(GPIOA,MT_LFT_A1|MT_LFT_A2|MT_LFT_B1|MT_LFT_B2); \
                           GPIO_SetBits(GPIOA,MT_LFT_B1)
													 
#define MT_LFT_STEP4_SET() GPIO_ResetBits(GPIOA,MT_LFT_A1|MT_LFT_A2|MT_LFT_B1|MT_LFT_B2); \
                           GPIO_SetBits(GPIOA,MT_LFT_A2|MT_LFT_B1)
													 
#define MT_LFT_STEP5_SET() GPIO_ResetBits(GPIOA,MT_LFT_A1|MT_LFT_A2|MT_LFT_B1|MT_LFT_B2); \
                           GPIO_SetBits(GPIOA,MT_LFT_A2)
													 
#define MT_LFT_STEP6_SET() GPIO_ResetBits(GPIOA,MT_LFT_A1|MT_LFT_A2|MT_LFT_B1|MT_LFT_B2); \
                           GPIO_SetBits(GPIOA,MT_LFT_A2|MT_LFT_B2)
													 
#define MT_LFT_STEP7_SET() GPIO_ResetBits(GPIOA,MT_LFT_A1|MT_LFT_A2|MT_LFT_B1|MT_LFT_B2); \
                           GPIO_SetBits(GPIOA,MT_LFT_B2)
													 
#define MT_LFT_STEP8_SET() GPIO_ResetBits(GPIOA,MT_LFT_A1|MT_LFT_A2|MT_LFT_B1|MT_LFT_B2); \
                           GPIO_SetBits(GPIOA,MT_LFT_A1|MT_LFT_B2)
	
/*
*右电机时序宏定义
*/
#define MT_RGT_OFF() GPIO_ResetBits(GPIOC,MT_RGT_A1|MT_RGT_A2|MT_RGT_B1|MT_RGT_B2)

#define MT_RGT_STEP1_SET() GPIO_ResetBits(GPIOC,MT_RGT_A1|MT_RGT_A2|MT_RGT_B1|MT_RGT_B2); \
                           GPIO_SetBits(GPIOC,MT_RGT_A1)
													 
#define MT_RGT_STEP2_SET() GPIO_ResetBits(GPIOC,MT_RGT_A1|MT_RGT_A2|MT_RGT_B1|MT_RGT_B2); \
                           GPIO_SetBits(GPIOC,MT_RGT_A1|MT_RGT_B1)
													 
#define MT_RGT_STEP3_SET() GPIO_ResetBits(GPIOC,MT_RGT_A1|MT_RGT_A2|MT_RGT_B1|MT_RGT_B2); \
                           GPIO_SetBits(GPIOC,MT_RGT_B1)
													 
#define MT_RGT_STEP4_SET() GPIO_ResetBits(GPIOC,MT_RGT_A1|MT_RGT_A2|MT_RGT_B1|MT_RGT_B2); \
                           GPIO_SetBits(GPIOC,MT_RGT_A2|MT_RGT_B1)
													 
#define MT_RGT_STEP5_SET() GPIO_ResetBits(GPIOC,MT_RGT_A1|MT_RGT_A2|MT_RGT_B1|MT_RGT_B2); \
                           GPIO_SetBits(GPIOC,MT_RGT_A2)
													 
#define MT_RGT_STEP6_SET() GPIO_ResetBits(GPIOC,MT_RGT_A1|MT_RGT_A2|MT_RGT_B1|MT_RGT_B2); \
                           GPIO_SetBits(GPIOC,MT_RGT_A2|MT_RGT_B2)
													 
#define MT_RGT_STEP7_SET() GPIO_ResetBits(GPIOC,MT_RGT_A1|MT_RGT_A2|MT_RGT_B1|MT_RGT_B2); \
                           GPIO_SetBits(GPIOC,MT_RGT_B2)
													 
#define MT_RGT_STEP8_SET() GPIO_ResetBits(GPIOC,MT_RGT_A1|MT_RGT_A2|MT_RGT_B1|MT_RGT_B2); \
                           GPIO_SetBits(GPIOC,MT_RGT_A1|MT_RGT_B2)

/*******************************************************************
电机状态宏定义
*******************************************************************/

#define MOTOR_STOP 0   /* 电机停止 */
#define MOTOR_RUN  1	 /* 电机运行 */

/******************************************************************
常量宏定义-电机运行方向
******************************************************************/
#define MOTOR_GOAHEAD  0		/* 电机前进 */
#define MOTOR_GOBACK   1     /* 电机后退 */
/*******************************************************************
结构体定义
*******************************************************************/

struct motor{
					
volatile    char 	cState;			/* 电机运行状态 */
volatile	char 	cDir;			/* 电机运行方向 */
volatile	unsigned long int ulPulse;		/* 电机需要转动的步数 */
volatile	unsigned long int ulPulseCtr;		/* 电机已经转动的步数 */
volatile	long int  lSpeed;		/* 电机转动的速度 */
};
typedef struct motor MOTOR;
extern MOTOR GmLeft;
extern MOTOR GmRight;
	

/*******************************************************************
*函数声明
*******************************************************************/
void Motor_Init(void);
void StepRight(void);
void StepLeft(void);
void Motor_GORight(void);
void Motor_GOStraight(void);
void Motor_GOLeft(void);
void Motor_Stop(void);
#endif



