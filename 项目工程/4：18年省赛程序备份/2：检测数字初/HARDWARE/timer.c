#include "timer.h"
#include "touch.h" 
#include "lcd.h"
extern u8 ch_selsct,mode_selsct;
//��ʱ��3�жϷ������	 ��ʱ����Ƿ��д������� 
void TIM3_IRQHandler(void)
{ 		    		  			    
	if(TIM3->SR&0X0001)//����ж�
	{
	Rtp_Scan();	    				   				     	    	
	}				   
	TIM3->SR&=~(1<<0);//����жϱ�־λ 	    
}
//ͨ�ö�ʱ��3�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<1;	//TIM3ʱ��ʹ��    
 	TIM3->ARR=arr;  	//�趨�������Զ���װֵ//�պ�1ms    
	TIM3->PSC=psc;  	//Ԥ��Ƶ��7200,�õ�10Khz�ļ���ʱ��		  
	TIM3->DIER|=1<<0;   //��������ж�	  
	TIM3->CR1|=0x01;    //ʹ�ܶ�ʱ��3
  	MY_NVIC_Init(1,3,TIM3_IRQn,2);//��ռ1�������ȼ�3����2									 
}
void Rtp_Scan(void)   //����������⺯��
{
			tp_dev.scan(0); 		 
		if(tp_dev.sta&TP_PRES_DOWN)			//������������
		{	
		 	if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
			{				
				if(tp_dev.x[0]>11&&tp_dev.x[0]<75&&tp_dev.y[0]>150&&tp_dev.y[0]<175)//����1
				{
					mode_selsct=1;
				}
				if(tp_dev.x[0]>11&&tp_dev.x[0]<75&&tp_dev.y[0]>180&&tp_dev.y[0]<205)//����2
				{
					mode_selsct=2;
				}
				if(tp_dev.x[0]>11&&tp_dev.x[0]<75&&tp_dev.y[0]>210&&tp_dev.y[0]<235)//����3
				{
					mode_selsct=3;
				}
			   	if(tp_dev.x[0]>11&&tp_dev.x[0]<75&&tp_dev.y[0]>240&&tp_dev.y[0]<265)//����4
				{
					mode_selsct=4;
				}
				if(tp_dev.x[0]>11&&tp_dev.x[0]<75&&tp_dev.y[0]>270&&tp_dev.y[0]<295)//����5
				{
					mode_selsct=5;
				}
			}
}
		}












