#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"




/*************************** �ļ�˵�� *******************************/
//�˳����������߲ʹ���̫��M3��STM32F103�����弰���ּ��ݵ�STM32ϵͳ��
//�Ա�����"�߲ʹ��� ̫��M3 STM32������"���򳬸��Լ۱ȿ�������ȡ��������
//ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;��
/********************************************************************/ 








#define TIM1_IRQHandler TIM1_UP_IRQHandler
#define TIM8_IRQHandler TIM8_UP_IRQHandler






void TIM_SetInterval(u8 TIM_Index,u32 nus);
void TIM_Init(u8 TIM_Index,u16 Prescaler,u16 Period);







#endif
