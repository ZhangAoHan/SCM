#include "timer.h"
#include "usart.h" 
extern u8 key;
//��ʱ��3�жϷ������	 
void TIM3_IRQHandler(void)
{ 		    		  			    
	if(TIM3->SR&0X0001)//����ж�
	{
	}				   
	TIM3->SR&=~(1<<0);//����жϱ�־λ 	    
}
//ͨ�ö�ʱ��3�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
void TIM3_Int_Init(u16 arr,u16 psc)  //����LED���𣬱�ʾ������������
{
	RCC->APB1ENR|=1<<1;	//TIM3ʱ��ʹ��    
 	TIM3->ARR=arr;  	//�趨�������Զ���װֵ//�պ�1ms    
	TIM3->PSC=psc;  	//Ԥ��Ƶ��7200,�õ�10Khz�ļ���ʱ��		  
	TIM3->DIER|=1<<0;   //��������ж�	  
	TIM3->CR1|=0x01;    //ʹ�ܶ�ʱ��3
  	MY_NVIC_Init(1,3,TIM3_IRQn,2);//��ռ1�������ȼ�3����2									 
}
//TIM3 PWM���ֳ�ʼ�� 
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM3_PWM_Init(u16 arr,u16 psc)  //���PWM����LED���ĳ̶�    ������û��
{		 					 
	RCC->APB2ENR|=1<<2;    //ʹ��PORTAʱ��
	RCC->APB1ENR|=1<<1;	//TIM3ʱ��ʹ��    
	GPIOA->CRL&=0XF0FFFFFF;	//PA6���֮ǰ������
	GPIOA->CRL|=0X0B000000;	//���ù������
	TIM3->ARR=arr;             //�趨�������Զ���װֵ 
	TIM3->PSC=psc;             //Ԥ��Ƶ����Ƶ
	TIM3->CCMR1|=6<<4;         //CH1 PWM1ģʽ		 
	TIM3->CCMR1|=1<<3;         //CH1Ԥװ��ʹ��	    
	TIM3->CCER|=1<<0;          //CH1���ʹ��	
	TIM3->CR1=0x0080;          //ARPEʹ�� 
	TIM3->CR1|=0x01;          //ʹ�ܶ�ʱ��3												  
}  	 

u8 ov_frame; 	//ͳ��֡��
//��ʱ��6�жϷ������	 
void TIM6_IRQHandler(void)
{ 		    		  			    
	if(TIM6->SR&0X0001)//����ж�
	{				    
//		printf("frame:%dfps\r\n",ov_frame);	//��ӡ֡��
		ov_frame=0;	
		key++;	
	if(key>=4) key=0;		
	}				   
	TIM6->SR&=~(1<<0);//����жϱ�־λ 	    
}
//������ʱ��6�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
void TIM6_Int_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<4;//TIM6ʱ��ʹ��    
 	TIM6->ARR=arr;  	//�趨�������Զ���װֵ//�պ�1ms    
	TIM6->PSC=psc;  	//Ԥ��Ƶ��7200,�õ�10Khz�ļ���ʱ��	  
	TIM6->DIER|=1<<0;   //��������ж�	 
	TIM6->CR1|=0x01;    //ʹ�ܶ�ʱ��3
  	MY_NVIC_Init(1,3,TIM6_IRQn,2);//��ռ1�������ȼ�3����2									 
}















