#include "timer.h"
#include "sys.h" //��Ϊ�����ж����ȼ���Ҫ����sys.c�еĺ���
extern u8 use1,use2,use3; 
extern u16 t1,t2,t3; 
u8 times;
extern u8 door;
void PWM_Init(u16 arr,u16 psc)
{
	RCC->APB2ENR|=1<<3;    //ʹ��PORTBʱ��
	RCC->APB1ENR|=1<<2;	//TIM4ʱ��ʹ��    
	GPIOB->CRH&=0XFFFFFFF0;	//PB8���֮ǰ������
	GPIOB->CRH|=0X0000000B;	//���ù������
	TIM4->ARR=arr;             //�趨�������Զ���װֵ 
	TIM4->PSC=psc;             //Ԥ��Ƶ����Ƶ
	TIM4->CCMR2|=6<<4;         //CH3 PWM1ģʽ		 
	TIM4->CCMR2|=1<<3;         //CH3Ԥװ��ʹ��	    
	TIM4->CCER|=1<<8;          //CH3���ʹ��	
	TIM4->CR1=0x0080;          //ARPEʹ�� 
	TIM4->CR1|=0x01;          //ʹ�ܶ�ʱ��3	
}
//��ʱ��3�жϷ������	 
void TIM3_IRQHandler(void)
{ 		    		  			    
	if(TIM3->SR&0X0001)//����ж�
	{
		if(use1==1)
		{
			t1++;
		}
		if(use2==1)
		{
			t2++;
		}
		if(use3==1)
		{
			t3++;
		}
		if(door==1)
		{
			times++;
			PWM=15;    //����5s
			if(times>=5)
			{
			times=0;
			PWM=5; 	
			door=0;
			}
			
		}
	}				   
	TIM3->SR&=~(1<<0);//����жϱ�־λ 	    
}
void TIM3_Int_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<1;	//TIM3ʱ��ʹ��    
 	TIM3->ARR=arr;  	//�趨�������Զ���װֵ//�պ�1ms    
	TIM3->PSC=psc;  	//Ԥ��Ƶ��7200,�õ�10Khz�ļ���ʱ��		  
	TIM3->DIER|=1<<0;   //��������ж�	  
	TIM3->CR1|=0x01;    //ʹ�ܶ�ʱ��3
  	MY_NVIC_Init(1,3,TIM3_IRQn,2);//��ռ1�������ȼ�3����2									 
}

