#ifndef __MOTOR
#define __MOTOR

#include "timer.h"
/*******************************************************************
�����궨��
*******************************************************************/

/*
*����������
*/ 
#define MT_LFT_A1 GPIO_Pin_3  
#define MT_LFT_A2 GPIO_Pin_6
#define MT_LFT_B1 GPIO_Pin_7
#define MT_LFT_B2 GPIO_Pin_8
/*
*�ҵ��������
*/
#define MT_RGT_A1 GPIO_Pin_13
#define MT_RGT_A2 GPIO_Pin_11  
#define MT_RGT_B1 GPIO_Pin_12
#define MT_RGT_B2 GPIO_Pin_1


/*
*���������궨��
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
*�ҵ��ʱ��궨��
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
���״̬�궨��
*******************************************************************/

#define MOTOR_STOP 0   /* ���ֹͣ */
#define MOTOR_RUN  1	 /* ������� */

/******************************************************************
�����궨��-������з���
******************************************************************/
#define MOTOR_GOAHEAD  0		/* ���ǰ�� */
#define MOTOR_GOBACK   1     /* ������� */
/*******************************************************************
�ṹ�嶨��
*******************************************************************/

struct motor{
					
volatile    char 	cState;			/* �������״̬ */
volatile	char 	cDir;			/* ������з��� */
volatile	unsigned long int ulPulse;		/* �����Ҫת���Ĳ��� */
volatile	unsigned long int ulPulseCtr;		/* ����Ѿ�ת���Ĳ��� */
volatile	long int  lSpeed;		/* ���ת�����ٶ� */
};
typedef struct motor MOTOR;
extern MOTOR GmLeft;
extern MOTOR GmRight;
	

/*******************************************************************
*��������
*******************************************************************/
void Motor_Init(void);
void StepRight(void);
void StepLeft(void);
void Motor_GORight(void);
void Motor_GOStraight(void);
void Motor_GOLeft(void);
void Motor_Stop(void);
#endif

