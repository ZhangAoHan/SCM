#include "timer.h"
#include "sys.h" //��Ϊ�����ж����ȼ���Ҫ����sys.c�еĺ���
#include "rc522.h"
#include "lcd.h"
#include "text.h"
#include "memory.h" 
#include "delay.h"	 
#include "led.h"
u8 t;
u8 nn=0;
extern u16 SL;
//��ʱ��3�жϷ������	 
void TIM2_IRQHandler(void)
{ 		    		  			    
	if(TIM2->SR&0X0001)//����ж�
	{

		
		t++;
		if(nn==0)
		{
		SL=TIM3->CNT;
		TIM3->CNT=0;
		}

		if(t>=5)
		{
			t=0;	
			tempin_memory();
			tempout_memory();
		}

	}				   
	TIM2->SR&=~(1<<0);//����жϱ�־λ 	    
}
void TIM2_Int_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<0;	//TIM3ʱ��ʹ��    
 	TIM2->ARR=arr;  	//�趨�������Զ���װֵ//�պ�1ms    
	TIM2->PSC=psc;  	//Ԥ��Ƶ��7200,�õ�10Khz�ļ���ʱ��		  
	TIM2->DIER|=1<<0;   //��������ж�	  
	TIM2->CR1|=0x01;    //ʹ�ܶ�ʱ��3
  	MY_NVIC_Init(1,3,TIM2_IRQn,2);//��ռ1�������ȼ�3����2									 
}



//ͨ�ö�ʱ��3 �����ⲿ������ ��ʼ��
//arr�������Զ���װֵ��

	void TIM3_Int(u16 arr)

	{

	RCC->APB2ENR|=1<<5;//����GPIOD�˿�ʱ��

	GPIOD->CRL &= 0xfffff0ff;

	GPIOD->CRL |= 0x00000400;//PD.2 �������� 



	RCC->APB1ENR |= 1<<1;//ʹ��TIM3ʱ��



	TIM3->ARR=arr;  //�趨�������Զ���װֵ

	TIM3->PSC=0; //����Ƶ


	TIM3->SMCR &= ~(0xf<<8);//���˲�

	TIM3->SMCR &= ~(3<<12);//�ر�Ԥ��Ƶ

	TIM3->SMCR |= 1<<15;//ETR�����࣬�͵�ƽ���½�����Ч

	TIM3->SMCR |= 1<<14;//ʹ���ⲿʱ��ģʽ2



	TIM3->DIER |= 1<<0;//��������ж�

	TIM3->DIER |= 1<<6;//�������ж�



	MY_NVIC_Init(1,3,TIM3_IRQn,2);//��ռ1�������ȼ�3����2 



	TIM3->CNT = 0x0;//���������

	TIM3->CR1 |= 1<<0;//ʹ�ܶ�ʱ��������������

	}




//��ʱ��3�жϷ������ ?

	void TIM3_IRQHandler(void)

	{ 

	if(TIM3->SR&0X0001)//����ж�

	{
		TIM3->CNT = 65535;//���������
	 
	} 
	TIM3->SR&=~(1<<0);//����жϱ�־λ ?

	}



