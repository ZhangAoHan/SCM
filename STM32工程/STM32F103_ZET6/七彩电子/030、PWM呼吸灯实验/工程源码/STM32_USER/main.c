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
	u8 flag=0;//�����־
	u16 t=0;//��ʱռ�ձ�
	delay_init();	    //��ʱ������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	USART1_Init(115200);//����1��ʼ��
	LCD_Init(); //LCD��ʼ��
	
	
	TIM3_PWM_Init(1000-1,72-1);//72��Ƶ��������1000������Ϊ1ms����ӦƵ��1KHz
	TIM_SetCompare2(TIM3,0);//����ռ�ձ�Ϊ0us����0%ռ�ձ�
	
	while(1)
	{
		if(flag==0){//��-->��
			t+=10;
			if(t>=1000){
				flag=1;
			}
			else{
				TIM_SetCompare2(TIM3,t);
			}
		}
		else{//��-->��
			if(t>10){
				t-=10;
				TIM_SetCompare2(TIM3,t);
			}
			else{
				t=0;
				flag=0;
				TIM_SetCompare2(TIM3,t);
				delay_ms(1000);//��ʱ1.5s,ģ������ĸо�
				delay_ms(500);
			}
		}
		delay_ms(10);
	}
}




