#include "sys.h"
#include "usart.h"		
#include "delay.h"	 
#include "ds18b20.h"
#include "ds.h"
u8 Candela;
int dh[4];
int dh1[4];
u8 receivedate[64];
int temp;
short a=0,b=0;
u8 t;
void Temp(void);
int main(void)
{				 

	Stm32_Clock_Init(9);	//ϵͳʱ������
	delay_init(72);	  		//��ʱ��ʼ��
	uart_init(72,115200); 	//���ڳ�ʼ��Ϊ9600
//	DS18B20_Init();
//	Adc_Init(); 
  	while(1)
	{
			Temp();	
//		printf("%d",temp);
//		printf("\r\n");
//		printf("%d",Candela);
//		printf("\r\n");
				for(t=0;t<4;t++)
			{
				
				USART1->DR=48+dh[t];   
				while((USART1->SR&0X40)==0) { ; }//�ȴ����ͽ���
			}
		       delay_ms(100);
			
//				for(t=0;t<4;t++)
//			{
//				USART1->DR=48+dh1[t];   
//				while((USART1->SR&0X40)==0) { ; }//�ȴ����ͽ���
//			}

		       delay_ms(100);
		
//			//while(receive()==0) { receive(); } //�ȴ���λ�������ź�

////		USART1->DR=48+2;  //��ʾ��λ��׼������ʪ���ź�
////		while((USART1->SR&0X40)==0) { ; } //�ȴ����ͽ���
////		USART1->DR=0XF2;   
////		while((USART1->SR&0X40)==0) { ; }//�ȴ����ͽ���
//				for(t=0;t<2;t++)
//			{
//				USART1->DR=48+dh[t+2];   
//				while((USART1->SR&0X40)==0) { ; }//�ȴ����ͽ���
//			}
//			delay_ms(100);
		
			
	}	 
} 

void Temp(void)
{
//	temp=DS18B20_Get_Temp();	
	a=56;
	b=7;
	dh[0]=a/10;
	dh[1]=a%10;
	dh[2]=-2;
	dh[3]=b;
	
//	Candela=Get_Adc_Average(ADC_CH1,10);
//	Candela=4096-Candela/4;
//	dh1[0]=Candela/1000;
//	dh1[1]=(Candela%1000)/100;
//	dh1[2]=(Candela%100)/10;
//	dh1[3]=Candela%10;
}





