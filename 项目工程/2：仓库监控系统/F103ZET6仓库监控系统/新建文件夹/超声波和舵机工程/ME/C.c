#include "C.h"  //����������TIM2ͨ��3��4��Ϊ��������
#include "delay.h"	
u16 TIM2CH3_CAPTURE_STA,TIM2CH3_CAPTURE_VAL;

void TIM2_Init(u16 arr,u16 psc)	     //��ʱ��2��ʼ��
{	 
	RCC->APB1ENR|=1<<0;     	//TIM2ʱ��ʹ��     
	RCC->APB2ENR|=1<<2;    		//ʹ��PORTAʱ��   	 
	GPIOA->CRL&=0XFFFF00FF; 	
	GPIOA->CRL|=0X00002800;		//  	PA.2 ���� PA.3���
	
	TIM2->ARR=arr;  		//�趨�������Զ���װֵ   
	TIM2->PSC=psc;  		//Ԥ��Ƶ�� 
	TIM2->CCMR2|=1<<0;	//ͨ��3 ѡ������� 
 	TIM2->CCMR2|=0<<4; 	// ���������˲��� ���˲�
 	TIM2->CCMR2|=0<<2; 	//���������Ƶ,����Ƶ 

	TIM2->CCER|=0<<9; 	//�����ز���
	TIM2->CCER|=1<<8; 	//�������������ֵ������Ĵ�����

	TIM2->DIER|=1<<3;   //�������ж�				
	TIM2->DIER|=1<<0;   //��������ж�	
	TIM2->CR1|=0x01;    //ʹ�ܶ�ʱ��3
	MY_NVIC_Init(1,3,TIM2_IRQn,1);
}
void Read_Distane(void)
{   
	 PAout(3)=1;
	 delay_us(15);  
	 PAout(3)=0;	
			if(TIM2CH3_CAPTURE_STA&0X80)//�ɹ�������һ�θߵ�ƽ
		{
			Distance=TIM2CH3_CAPTURE_STA&0X3F;
			Distance*=65536;					        //���ʱ���ܺ�
			Distance+=TIM2CH3_CAPTURE_VAL;		//�õ��ܵĸߵ�ƽʱ��
			Distance=Distance*170/1000;
		//	printf("%d \r\n",Distance);
			TIM2CH3_CAPTURE_STA=0;			//������һ�β���
		}				
}
void TIM2_IRQHandler(void)
{ 		    		  			    
	u16 tsr;
	tsr=TIM2->SR;
	if((TIM2CH3_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
				{
								if(tsr&0X01)//���
								{	    
										if(TIM2CH3_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
										{
											if((TIM2CH3_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
											{
												TIM2CH3_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
												TIM2CH3_CAPTURE_VAL=0XFFFF;
											}else TIM2CH3_CAPTURE_STA++;
										}	 
								}
						   	if(tsr&0x08)//����3���������¼�
				    	{	
											if(TIM2CH3_CAPTURE_STA&0X40)		//����һ���½��� 		
											{	  			
											TIM2CH3_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����
											TIM2CH3_CAPTURE_VAL=TIM3->CCR3;	//��ȡ��ǰ�Ĳ���ֵ.
											TIM2->CCER&=~(1<<9);			//CC1P=0 ����Ϊ�����ز���
									  	}else  								//��δ��ʼ,��һ�β���������
				   	{
											TIM2CH3_CAPTURE_STA=0;			//���
											TIM2CH3_CAPTURE_VAL=0;
											TIM2CH3_CAPTURE_STA|=0X40;		//��ǲ�����������
											TIM2->CNT=0;					//���������
											TIM2->CCER|=1<<9; 				//CC1P=1 ����Ϊ�½��ز���
							}		    
					    	}			     	    					   
		   }
			 TIM2->SR=0;//����жϱ�־λ 	     
}
