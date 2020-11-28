/*  main.c  */

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "ezio.h"
#include "key.h"

#include "LcdApi.h"
#include "LcdBsp.h"
#include "touch.h"
#include "adc.h"
#include "dac.h"

#include "TimerPWM.h"




/*************************** �ļ�˵�� *******************************/
//�˳����������߲ʹ���̫��M3��STM32F103�����弰���ּ��ݵ�STM32ϵͳ��
//�Ա�����"�߲ʹ��� ̫��M3 STM32������"���򳬸��Լ۱ȿ�������ȡ��������
//ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;��
/********************************************************************/ 


//u8 lcd_buf[50]={0};//������ʱ�洢LCD��ʾ���ַ���





int main(void)
{
	
	delay_init();	    //��ʱ������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	USART1_Init(115200);//����1��ʼ��
	LCD_Init(); //LCD��ʼ��
	
	
	TIM3_PWM_Init(1000-1,72-1);//72��Ƶ��������1000������Ϊ1ms����ӦƵ��1KHz
	TIM_SetCompare2(TIM3,499);//����ռ�ձ�Ϊ500us����50%ռ�ձ�
	
	while(1)
	{
		
	}
}




