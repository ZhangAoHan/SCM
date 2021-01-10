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

	Stm32_Clock_Init(9);	//系统时钟设置
	delay_init(72);	  		//延时初始化
	uart_init(72,9600); 	//串口初始化为9600
  	while(1)
	{
		DHT11_Read_Data(&temperature,&humidity);
			dh[0]=temperature/10;
			dh[1]=temperature%10;
			dh[2]=humidity/10;
			dh[3]=humidity%10;
	//	while(receive()==0) { receive(); } //等待上位机返回信号		
//		USART1->DR=48+1;  //提示上位机准备接收湿度信号
//		while((USART1->SR&0X40)==0) { ; } //等待发送结束	
				for(t=0;t<2;t++)
			{
				USART1->DR=48+dh[t];   
				while((USART1->SR&0X40)==0) { ; }//等待发送结束
			}
		       delay_ms(1000);
		
			//while(receive()==0) { receive(); } //等待上位机返回信号

//		USART1->DR=48+2;  //提示上位机准备接收湿度信号
//		while((USART1->SR&0X40)==0) { ; } //等待发送结束
				for(t=0;t<2;t++)
			{
				USART1->DR=48+dh[t+2];   
				while((USART1->SR&0X40)==0) { ; }//等待发送结束
			}
			delay_ms(1000);
		
			
	}	 
} 
int receive(void)
{
	if(USART_RX_STA&0x80)  
			{
				len=USART_RX_STA&0x3f;//得到此次接收到的数据长度
				for(t=0;t<len;t++)
			{
				receivedate[t]=USART_RX_BUF[t];
			}
			USART_RX_STA=0;
			if(receivedate[0]-48==9) //上位机已经正常接收
				return 1;	
				}	
			else
			{
				
				return 0;
			}
}





