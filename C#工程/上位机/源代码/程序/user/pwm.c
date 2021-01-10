/*---------------------------------------
			PWM���ó���
 ˵��: ����������ͨ����A7��PWM������ӳ��
 	   ��PB5�˿���ʵ��PWM����LED��������
	   ����,���ù��̾��вο�����,ʹ�ü�
	   ֵ��,���������·�װ���µĺ���,ʹ
	   ��PWM�����ú�ʹ�ø��ӱ��ֱ�ۡ�
 ʱ��: 2013��7��26�� BoX��д
----------------------------------------*/
#include "pwm.h"
#include "stm32f10x.h"
/*---------------------------------------
 ��������: ��ʱ��3ͨ��2����PWM��ʱ��
 ��������: �Զ���װֵAuto_Reload 0-65535
 		   Ԥ��Ƶ Clock_Div 0-65535
----------------------------------------*/
void PWM_TIM2_CH2_Config(uint16_t Auto_Reload,uint16_t Clock_Div)
{	
	GPIO_InitTypeDef IO_Init;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);	 //ʹ�ܶ�ʱ��3ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	 //ʹ��AFIOʱ��
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOD , ENABLE);	
 	
	IO_Init.GPIO_Pin = GPIO_Pin_5;				    
  	IO_Init.GPIO_Mode = GPIO_Mode_AF_PP;				 //PB5�����������
  	IO_Init.GPIO_Speed = GPIO_Speed_50MHz;	
  	GPIO_Init(GPIOB, &IO_Init);

	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);	 //TIM3������ӳ�� TIM3_CH2->PB5

	TIM_TimeBaseStructure.TIM_Prescaler =  Clock_Div; 			//ʱ��Ԥ��Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode =  TIM_CounterMode_Up;//���ϼ���
	TIM_TimeBaseStructure.TIM_Period = Auto_Reload;				//�Զ���װֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;	    //ʱ�ӷ�Ƶ1
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);

	TIM_OCInitStructure.TIM_OCMode =  TIM_OCMode_PWM2;   //ѡ��ʱ��ģʽ:PWM2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OC2Init(TIM3,&TIM_OCInitStructure);				 //����ָ���Ĳ�����ʼ������TIM3 OC2
	
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable); //ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���
}
/*---------------------------------------
 ��������: ��ʱ��3ͨ��2��ʼ��
 ��������: �Զ���װֵAuto_Reload 0-65535
 ����ʾ��: PWM_TIM3_CH2_Init(8000) 
----------------------------------------*/
void PWM_TIM3_CH2_Init(unsigned short int Auto_Reload)
{
	PWM_TIM3_CH2_Config( (7200000/Auto_Reload)-1 , 0);		
	TIM_Cmd(TIM3,ENABLE);	//ʹ��TIM3
}
/*-------------------------------------------
 ��������: �趨��ʱ��3ͨ��2��PWMƵ�ʺ�ռ�ձ�
 ��������: PWMƵ��freq 0-65535 Hz
 		   ռ�ձ� duty 0-65536 Hz
		   ռ�ձ�Ƶ�� < PWMƵ��
 ����ʾ��: PWM_TIM3_CH2_Set_FreqAndDuty(8000,4000); 
--------------------------------------------*/
void PWM_TIM3_CH2_Set_FreqAndDuty(unsigned short int freq,unsigned short int duty)
{
	PWM_TIM3_CH2_Init(freq);
	TIM_SetCompare2(TIM3,(720000/duty)-1);
}

	
