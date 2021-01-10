#include "sys.h"
#include "usart.h"		
#include "delay.h"	 
#include "dht11.h"
u8 temperature;
u8 humidity;
u8 dh[4];
u8 receivedate[64];

int receive(void);
	u8 t=0; 
	u8 len;
int main(void)
{				 

	Stm32_Clock_Init(9);	//ϵͳʱ������
	delay_init(72);	  		//��ʱ��ʼ��
	uart_init(72,9600); 	//���ڳ�ʼ��Ϊ9600
  	while(1)
	{
		DHT11_Read_Data(&temperature,&humidity);
			dh[0]=temperature/10;
			dh[1]=temperature%10;
			dh[2]=humidity/10;
			dh[3]=humidity%10;
	//	while(receive()==0) { receive(); } //�ȴ���λ�������ź�		
//		USART1->DR=48+1;  //��ʾ��λ��׼������ʪ���ź�
//		while((USART1->SR&0X40)==0) { ; } //�ȴ����ͽ���	
				for(t=0;t<2;t++)
			{
				USART1->DR=48+dh[t];   
				while((USART1->SR&0X40)==0) { ; }//�ȴ����ͽ���
			}
		       delay_ms(1000);
		
			//while(receive()==0) { receive(); } //�ȴ���λ�������ź�

//		USART1->DR=48+2;  //��ʾ��λ��׼������ʪ���ź�
//		while((USART1->SR&0X40)==0) { ; } //�ȴ����ͽ���
				for(t=0;t<2;t++)
			{
				USART1->DR=48+dh[t+2];   
				while((USART1->SR&0X40)==0) { ; }//�ȴ����ͽ���
			}
			delay_ms(1000);
		
			
	}	 
} 
int receive(void)
{
	if(USART_RX_STA&0x80)  
			{
				len=USART_RX_STA&0x3f;//�õ��˴ν��յ������ݳ���
				for(t=0;t<len;t++)
			{
				receivedate[t]=USART_RX_BUF[t];
			}
			USART_RX_STA=0;
			if(receivedate[0]-48==9) //��λ���Ѿ���������
				return 1;	
				}	
			else
			{
				
				return 0;
			}
}





