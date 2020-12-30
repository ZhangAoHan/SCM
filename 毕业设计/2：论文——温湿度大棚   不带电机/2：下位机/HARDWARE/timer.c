#include "timer.h"
#include "sys.h" //��Ϊ�����ж����ȼ���Ҫ����sys.c�еĺ���
#include "adc.h"
#include "dht11.h"
#include "led.h"
#include "control.h"

	extern u16 adcx;    //tr
	extern u16 adcx1;    //����
	extern u16 adcx2;    //MQ3
	extern	u8 temperature;  	    
	extern u8 humidity;
	extern u8 door;
	u8 i,di,si;
	extern u8 set;
	extern u8 settle;
//��ʱ��3�жϷ������	 
void TIM3_IRQHandler(void)
{ 		    		  			    
	if(TIM3->SR&0X0001)//����ж�
	{
		i++;
//		adcx1=Get_Adc_Average(ADC_CH1,10);
//		adcx=Get_Adc_Average(ADC_CH2,10);	
//		adcx2=Get_Adc_Average(ADC_CH3,10);
//		DHT11_Read_Data(&temperature,&humidity);	//��ȡ��ʪ��ֵ	
		Rc522_read();
		if(set==1)
		{
			si++;
			if(si==25)
			{
				set=0;
				si=0;
			}
		}
		if(i==50)
		{
			i=0;
			DHT11_JDQ=!DHT11_JDQ;
			TRSD_JDQ=!TRSD_JDQ;
			
	//FS_JDQ=!FS_JDQ
			settle=!settle;
		}
		if(door==1)
		{
			di++;
			PWM=10;    //����5s
			if(di>=30)
			{
				di=0;
				door=0;
				PWM=20; 	
			}
		}
	}				   
	TIM3->SR&=~(1<<0);//����жϱ�־λ 	    
}
void TIM1_PWM_Init(u16 arr,u16 psc)
{		 					 
	//�˲������ֶ��޸�IO������
	RCC->APB2ENR|=1<<11; 	//TIM1ʱ��ʹ��    
	GPIOA->CRH&=0XFFFFFFF0;	//PA8���֮ǰ������
	GPIOA->CRH|=0X0000000B;	//���ù������ 
	
	TIM1->ARR=arr;			//�趨�������Զ���װֵ 
	TIM1->PSC=psc;			//Ԥ��Ƶ������
  
	TIM1->CCMR1|=7<<4;  	//CH1 PWM2ģʽ		 
	TIM1->CCMR1|=1<<3; 		//CH1Ԥװ��ʹ��	 
 	TIM1->CCER|=1<<0;   	//OC1 ���ʹ��	   
	TIM1->BDTR|=1<<15;   	//MOE �����ʹ��	   

	TIM1->CR1=0x0080;   	//ARPEʹ�� 
	TIM1->CR1|=0x01;    	//ʹ�ܶ�ʱ��1 										  
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


