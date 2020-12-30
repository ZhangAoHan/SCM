#include "sys.h"
#include "usart.h"		
#include "delay.h"	 
#include "rcf24l01.h"
#include "date.h"

u16 adcx;
u8 temperature;  	    
u8 humidity;  	
u8 settle;
void date_read(u8 set);
int main(void)
{				 
	u8 mode=0;        //0:����ģʽ   1����ģʽ
	u8 tmp_buf[33]; 
	Stm32_Clock_Init(9);	//ϵͳʱ������
	delay_init(72);	  		//��ʱ��ʼ��
	uart_init(72,9600); 	//���ڳ�ʼ��Ϊ9600
	Io_In_Out();
	while(DHT11_Init())	//DHT11��ʼ��	
	{;}
	NRF24L01_Init(); 
	Adc_Init();
	 while(NRF24L01_Check())	//���NRF24L01�Ƿ���λ.	
	{
 		delay_ms(400);
	}
  	while(1)
	{
		if(mode==0)       //fs
		{
			date_read(settle);
			NRF24L01_TX_Mode();
			tmp_buf[0]=' ';
			tmp_buf[1]=temperature;
			tmp_buf[2]=humidity;
			tmp_buf[3]=adcx/256;
			tmp_buf[4]=adcx%256;
		if(NRF24L01_TxPacket(tmp_buf)==TX_OK)
			{
				tmp_buf[5]='!';//�����ַ���������  
				mode=1;
			}else delay_us(100);		
			
		}
		else
		{
			NRF24L01_RX_Mode();		
			if(NRF24L01_RxPacket(tmp_buf)==0)
			{
				if(tmp_buf[0]==' '&&tmp_buf[2]=='!')
				{
					if(tmp_buf[1]==0)
					{
						settle=0;
					}
					else if(tmp_buf[1]==1)
					{
						settle=1;
					}
				}
			}
		}
		if(settle==0) date_read(0);
		else if(settle==1) date_read(1);
	}	 
} 


void date_read(u8 set)
{
	if(set==0)
	{
		JDQ=1;
	}
	if(set==1)
	{
		JDQ=0;
	}
	DHT11_Read_Data(&temperature,&humidity);
	adcx=Get_Adc_Average(ADC_CH1,5);
}



