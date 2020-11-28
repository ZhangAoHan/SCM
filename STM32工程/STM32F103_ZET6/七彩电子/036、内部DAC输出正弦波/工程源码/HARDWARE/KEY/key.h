/*  key.h  */

#ifndef __KEY_H
#define __KEY_H
#include "sys.h"

/***********************************************************************/
//�˳����������߲ʹ���̫��M3��STM32F103�����弰���ּ��ݵ�STM32ϵͳ��
//ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;��
/***********************************************************************/

//��������
#define KEY0  0
#define KEY1  1
#define KEY2  2
#define KEY3  3

//key0 PE4
//key1 PE3
//key2 PE2
//key3/key_up PA0 


/********************* ��������GPIO�ں궨�� ***************************/
#define KEY0_GPIO GPIOE
#define KEY1_GPIO GPIOE
#define KEY2_GPIO GPIOE
#define KEY3_GPIO GPIOA

#define KEY0_PIN GPIO_Pin_4
#define KEY1_PIN GPIO_Pin_3
#define KEY2_PIN GPIO_Pin_2
#define KEY3_PIN GPIO_Pin_0
/****************************** end *********************************/


/********************* ��������GPIO��ʱ�Ӻ궨�� *********************/
#define KEY0_RCC_CLK  RCC_APB2Periph_GPIOE
#define KEY1_RCC_CLK  RCC_APB2Periph_GPIOE
#define KEY2_RCC_CLK  RCC_APB2Periph_GPIOE
#define KEY3_RCC_CLK  RCC_APB2Periph_GPIOA
/****************************** end *********************************/



/********************* ����Ӳ��״̬��ȡ�궨�� ***********************/
#define KEY0_HARD_STA  ((KEY0_GPIO->IDR & (uint16_t)KEY0_PIN)==0)
#define KEY1_HARD_STA  ((KEY1_GPIO->IDR & (uint16_t)KEY1_PIN)==0)
#define KEY2_HARD_STA  ((KEY2_GPIO->IDR & (uint16_t)KEY2_PIN)==0)
#define KEY3_HARD_STA  ((KEY3_GPIO->IDR & (uint16_t)KEY3_PIN)!=0)//��������Ǹߵ�ƽ��Ч
/****************************** end *********************************/

 
 
/********************* �������·���ֵ�궨�� *************************/
#define KEY0_PRES 	1	//KEY0����
#define KEY1_PRES  	2	//KEY1����
#define KEY2_PRES 	3	//KEY2����
#define WKUP_PRES   4	//KEY_UP����(��WK_UP/KEY_UP)
/****************************** end *********************************/



/********************* ������������ *********************************/

void Key_Init(void);   //IO��ʼ��
u8 Key_Scan(u8);  	   //����ɨ�躯��
u8 Key_GetSta(u8 key); //������ǰ״̬��ȡ  1:�ѱ�����  0:δ������


/****************************** end *********************************/











#endif











