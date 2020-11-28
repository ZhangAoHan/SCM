#include "lkt.h"
#include "delay.h"
void LED_Init(void)
{
	RCC->APB2ENR|=1<<2;    //ʹ��PORTAʱ��	   	 
	RCC->APB2ENR|=1<<5;    //ʹ��PORTDʱ��	
	   	 
	GPIOA->CRH&=0XFFFFFFF0; 
	GPIOA->CRH|=0X00000003;//PA8 �������   	 
  GPIOA->ODR|=1<<8;      //PA8 �����
											  
	GPIOD->CRL&=0XFFFFF0FF;
	GPIOD->CRL|=0X00000300;//PD.2�������
	GPIOD->ODR|=1<<2;      //PD.2����� 
}
void KEY_Init(void)
{
	RCC->APB2ENR|=1<<2;     //ʹ��PORTAʱ��
	GPIOA->CRL&=0XFFFFFFF0;//PA0���ó�����	  
	GPIOA->CRL|=0X00000008;   
	GPIOA->CRH&=0X0F0FFFFF;//PA13,15���ó�����	  
	GPIOA->CRH|=0X80800000; 				   
	GPIOA->ODR|=1<<13;	   //PA13����,PA0Ĭ������
	GPIOA->ODR|=1<<15;	   //PA15����
} 
//����������
//���ذ���ֵ
//0��û���κΰ�������
//1��KEY0����
//2��KEY1����
//3��KEY2���� WK_UP
//ע��˺�������Ӧ���ȼ�,KEY0>KEY1>KEY2!!
u8 KEY_Scan(void)
{	 
	static u8 key_up=1;//�������ɿ���־	
	JTAG_Set(JTAG_SWD_DISABLE);
	if(key_up&&(KEY0==0||KEY1==0||KEY2==1))
	{
		delay_ms(10);//ȥ���� 
		key_up=0;
		if(KEY0==0)
		{
			JTAG_Set(SWD_ENABLE);
			return 1;
		}
		else if(KEY1==0)
		{
			JTAG_Set(SWD_ENABLE);
			return 2;
		}
		else if(KEY2==1)
		{
			JTAG_Set(SWD_ENABLE);
			return 3;
		}
	}else if(KEY0==1&&KEY1==1&&KEY2==0)key_up=1; 	    
	JTAG_Set(SWD_ENABLE);
	return 0;// �ް�������
}
//��ʱ��3�жϷ������	 
void TIM3_IRQHandler(void)
{ 		    		  			    
	if(TIM3->SR&0X0001)//����ж�
	{
		LED1=!LED1;		
	}				   
	TIM3->SR&=~(1<<0);//����жϱ�־λ 	    
}
//ͨ�ö�ʱ���жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
void Timerx_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<1;//TIM3ʱ��ʹ��    
 	TIM3->ARR=arr;  //�趨�������Զ���װֵ//�պ�1ms    
	TIM3->PSC=psc;  //Ԥ��Ƶ��7200,�õ�10Khz�ļ���ʱ��
	//����������Ҫͬʱ���òſ���ʹ���ж�
	TIM3->DIER|=1<<0;   //��������ж�				
	TIM3->DIER|=1<<6;   //�������ж�
		  							    
	TIM3->CR1|=0x01;    //ʹ�ܶ�ʱ��3
  MY_NVIC_Init(1,3,TIM3_IRQChannel,2);//��ռ1�������ȼ�3����2									 
}

//TIM3 PWM����
//����ԭ��@ALIENTEK
//2010/6/2	 

//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void PWM_Init(u16 arr,u16 psc)
{		 					 
	//�˲������ֶ��޸�IO������
	RCC->APB1ENR|=1<<1;       //TIM3ʱ��ʹ��    

	GPIOA->CRH&=0XFFFFFFF0;//PA8���
	GPIOA->CRH|=0X00000004;//��������
	  	
	GPIOA->CRL&=0X0FFFFFFF;//PA7���
	GPIOA->CRL|=0XB0000000;//���ù������ 	  
	GPIOA->ODR|=1<<7;//PA7����	

	TIM3->ARR=arr;//�趨�������Զ���װֵ 
	TIM3->PSC=psc;//Ԥ��Ƶ������Ƶ
	
	TIM3->CCMR1|=7<<12;  //CH2 PWM2ģʽ		 
	TIM3->CCMR1|=1<<11; //CH2Ԥװ��ʹ��	   

	TIM3->CCER|=1<<4;   //OC2 ���ʹ��	   

	TIM3->CR1=0x8000;   //ARPEʹ�� 
	TIM3->CR1|=0x01;    //ʹ�ܶ�ʱ��3 										  
}  	 

