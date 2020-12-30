#include "display.h"
#include "rc522.h"
#include "lcd.h"
#include "text.h"
#include "dht11.h"
#include "adc.h"
#include "usart.h"	
extern u8 user;
extern int ID[12];  
unsigned char card_1[4]={224,147,168,112}; //����
unsigned char card_2[4]={213,196,112,34}; //����
unsigned char card_3[4]={50,70,216,26}; //����
extern unsigned char CT[2];//������
extern unsigned char SN[4]; //����
extern unsigned char RFID[16];			//���RFID 
extern unsigned char RFID1[16];
extern u8 KEY[6];
extern u8 temperature;  	    
extern u8 humidity;  	  
 u16 adcx;
 u16 adcx2;
extern u8 page;
u8 times;
extern int dt[4];         //  ������۳���⡢�����⡢��Դ��⣨1����   0�쳣��

void RFID_read(void)
{

		unsigned char status;
		status = PcdRequest(PICC_REQALL,CT);/*����*/
		if(status==MI_OK)//�����ɹ�
		{
			 status=MI_ERR;
			 status = PcdAnticoll(SN);/*����ײ*/
		}	
		if(status==MI_OK)
		{
			status=MI_ERR;
			status =PcdSelect(SN);
		}

		if(status==MI_OK)//�x���ɹ�
		{
			 status=MI_ERR;
			 status =PcdAuthState(0x61,0x06,KEY,SN);
		 }
	
		 if(status==MI_OK)//��C�ɹ�
		 {
			 status=MI_ERR;
			
			if(card_1[0]==SN[0]&&card_1[1]==SN[1]&&card_1[2]==SN[2]&&card_1[3]==SN[3]&&user!=21)	 user=1;
			else if(card_2[0]==SN[0]&&card_2[1]==SN[1]&&card_2[2]==SN[2]&&card_2[3]==SN[3]&&user!=22)	 user=2;
			 else if(card_3[0]==SN[0]&&card_3[1]==SN[1]&&card_3[2]==SN[2]&&card_3[3]==SN[3]&&user!=23)	 user=3;
				
			 
//			 user=!user;
						ID[0]=SN[0]/100;
			 ID[1]=(SN[0]%100)/10;
			 ID[2]=SN[0]%10;
			 			 ID[3]=SN[1]/100;
			 ID[4]=(SN[1]%100)/10;
			 ID[5]=SN[1]%10;
			 			 ID[6]=SN[2]/100;
			 ID[7]=(SN[2]%100)/10;
			 ID[8]=SN[2]%10;
			 			 ID[9]=SN[3]/100;
			 ID[10]=(SN[3]%100)/10;
			 ID[11]=SN[3]%10;
			
			door=1;
		  } 
}




void LED_Init(void)
{
	RCC->APB2ENR|=1<<4;    //ʹ��PORTcʱ��	   	 
	   	 
	GPIOC->CRL&=0X00000000; 
	GPIOC->CRL|=0X88333333;   
	GPIOC->ODR|=1<<3;      //P8,9 �����	
  

											
}

void control(void)
{
	RFID_read();
	adcx=Get_Adc_Average(ADC_CH1,5);   //�۳�
	adcx2=Get_Adc_Average(ADC_CH2,5);	//����
	if(adcx>=2000)  //�쳣
	{
		dt[1]=0;
		dt[0]=0;
		FS=0;  
	}
	else
	{
		dt[1]=1;
	}
	if(adcx2>4000)   //����
	{
		dt[2]=1;
	}
	else
	{
		dt[2]=0;
	}
	if(HY==0)
	{
		dt[3]=0;
		dt[0]=0;          //��������
		FS=0;  
	}
	else
	{
		dt[3]=1;      
	}
	if(HY==1&&adcx<2000)
	{  
		dt[0]=1;          //�رշ���
		FS=1;
	}
	
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
//��ʱ��3�жϷ������	 
void TIM3_IRQHandler(void)
{ 		    		  			    
	if(TIM3->SR&0X0001)//����ж�
	{
		if(door==1)
		{
			times++;
			PWM=20;    //����5s
			if(times>=5)
			{
			times=0;
			PWM=10; 	
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


