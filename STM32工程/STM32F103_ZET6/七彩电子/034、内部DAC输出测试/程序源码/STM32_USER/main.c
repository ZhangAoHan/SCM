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

/*************************** �ļ�˵�� *******************************/
//�˳����������߲ʹ���̫��M3��STM32F103�����弰���ּ��ݵ�STM32ϵͳ��
//�Ա�����"�߲ʹ��� ̫��M3 STM32������"���򳬸��Լ۱ȿ�������ȡ��������
//ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;��
/********************************************************************/ 






int main(void)
{
	u16 temp=0;
	delay_init();	    //��ʱ������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	USART1_Init(115200);//����1��ʼ��
	
	LCD_Init();    //LCD��ʼ��
	Dac1_Init();
	
	//ͨ��PA4�����ѹ
	//�����ѹ����,���Ч����Ŀ¼����Ƭ
	while(1)
	{
		DAC_SetChannel1Data(DAC_Align_12b_R,temp);//12λ�Ҷ������ݸ�ʽ����DACֵ
		delay_ms(500);//��ʱ
		temp+=255;
		if(temp>4095){
			temp=0;
		}
	}
}




