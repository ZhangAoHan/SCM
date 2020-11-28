#include "timer.h"
#include "sys.h"


//��ʱ��3��������2·PWM
void Timer_init(u16 arr,u16 psc)
{
	RCC->APB1ENR |=1<<1;       //ʹ�ܶ�ʱ��3
	TIM3->CR1 |=1<<0;          //ʹ�ܼ���������ʱ����ʼʱ��Ϊ72M�����������ϼ���
	TIM3->CR1 |=0X0080;
  	TIM3->PSC =psc;  
	TIM3->ARR =arr; 
	
	TIM3->CCMR1 |=7<<4;        //ͨ��1����
	TIM3->CCMR1 |=1<<3;
	TIM3->CCER  |=1<<0;        //ͨ��1��Ч��ƽ�������ã�TIM3->CCER=1��pwmΪ�͵�ƽ��Ч��=3��pwmΪ�ߵ�ƽ��Ч��
	
	TIM3->CCMR1 |=7<<12;       //ͨ��2����
	TIM3->CCMR1 |=1<<11;
	TIM3->CCER  |=1<<4;
}

void MOTO_PWM_init(void)
{
	
	RCC->APB2ENR|=1<<2;        //ʹ��GPIOA
	GPIOA->CRL&=0X00FFFFFF;    //ͨ��1 GPIOA6,�����������������ٶ�50M
	GPIOA->CRL|=0XBB000000;    //ͨ��2 GPIOA7,�����������������ٶ�50M
	GPIOA->ODR|=1<<6;          //����GPIOA6Ϊ���ģʽ
	GPIOA->ODR|=1<<7;          //����GPIOA7Ϊ���ģʽ
}

//��ʱ��2 ����2��������ٶ�
void TIM2_init(u16 arr)
{
	RCC->APB1ENR|=1<<0;     //TIM2ʱ��ʹ��
	RCC->APB2ENR|=1<<2;    //ʹ��PORTAʱ��
	GPIOA->CRL&=0XFFFFFF00;//PA0 PA1
	GPIOA->CRL|=0X00000044;//��������
	TIM2->DIER|=1<<0;   //��������ж�				
	TIM2->DIER|=1<<6;   //�������ж�
	MY_NVIC_Init(1,3,TIM2_IRQn,1);  //65536��arr��/72M=910us  ���Ƶ��
	TIM2->PSC = 0x0;//Ԥ��Ƶ��
	TIM2->ARR = arr;//�趨�������Զ���װֵ 
	TIM2->CR1 &=~(3<<8);// ѡ��ʱ�ӷ�Ƶ������Ƶ
	TIM2->CR1 &=~(3<<5);// ѡ�����ģʽ:���ض���ģʽ
		
	TIM2->CCMR1 |= 1<<0; //CC1S='01' IC1FP1ӳ�䵽TI1
	TIM2->CCMR1 |= 1<<8; //CC2S='01' IC2FP2ӳ�䵽TI2
	TIM2->CCER &= ~(1<<1);	 //CC1P='0'	 IC1FP1�����࣬IC1FP1=TI1
	TIM2->CCER &= ~(1<<5);	 //CC2P='0'	 IC2FP2�����࣬IC2FP2=TI2
	TIM2->CCMR1 |= 3<<4; //	IC1F='1000' ���벶��1�˲���
	TIM2->SMCR |= 3<<0;	 //SMS='011' ���е�������������غ��½�����Ч
	TIM2->CR1 |= 0x01;    //CEN=1��ʹ�ܶ�ʱ��
}

void TIM4_init(u16 arr)
{
	RCC->APB1ENR|=1<<2;     //TIM4ʱ��ʹ��
	RCC->APB2ENR|=1<<3;     //ʹ��PORTBʱ��
	GPIOB->CRL&=0X00FFFFFF; //PB6 PB7
	GPIOB->CRL|=0X44000000; //��������
	TIM4->DIER|=1<<0;   //��������ж�				
	TIM4->DIER|=1<<6;   //�������ж�
	MY_NVIC_Init(1,3,TIM4_IRQn,1);
	TIM4->PSC = 0x0;//Ԥ��Ƶ��
	TIM4->ARR = arr;//�趨�������Զ���װֵ 
	TIM4->CR1 &=~(3<<8);// ѡ��ʱ�ӷ�Ƶ������Ƶ
	TIM4->CR1 &=~(3<<5);// ѡ�����ģʽ:���ض���ģʽ
		
	TIM4->CCMR1 |= 1<<0; //CC1S='01' IC1FP1ӳ�䵽TI1
	TIM4->CCMR1 |= 1<<8; //CC2S='01' IC2FP2ӳ�䵽TI2
	TIM4->CCER &= ~(1<<1);	 //CC1P='0'	 IC1FP1�����࣬IC1FP1=TI1
	TIM4->CCER &= ~(1<<5);	 //CC2P='0'	 IC2FP2�����࣬IC2FP2=TI2
	TIM4->CCMR1 |= 3<<4; //	IC1F='1000' ���벶��1�˲���
	TIM4->SMCR |= 3<<0;	 //SMS='011' ���е�������������غ��½�����Ч
	TIM4->CR1 |= 0x01;    //CEN=1��ʹ�ܶ�ʱ��
}
void TIM2_IRQHandler(void)
{ 		    		  			    
	if(TIM2->SR&0X0001)//����ж�
	{    				   				     	    	
	}				   
	TIM2->SR&=~(1<<0);//����жϱ�־λ 	    
}
void TIM4_IRQHandler(void)
{ 		    		  			    
	if(TIM4->SR&0X0001)//����ж�
	{    				   				     	    	
	}				   
	TIM4->SR&=~(1<<0);//����жϱ�־λ 	    
}
int Read_val(u8 TIMX)     //��ȡ���������ص��ٶ�ֵ
{
    int Encoder_TIM;    
   switch(TIMX)
	 {
	   case 2:  Encoder_TIM= (short)TIM2 -> CNT;  TIM2 -> CNT=0;break;	
	   case 4:  Encoder_TIM= (short)TIM4 -> CNT;  TIM4 -> CNT=0;break;	
		 default:  Encoder_TIM=0;
	 }
		return Encoder_TIM;
}




