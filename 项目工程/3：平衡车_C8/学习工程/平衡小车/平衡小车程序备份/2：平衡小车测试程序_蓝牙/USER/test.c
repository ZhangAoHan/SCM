#include "sys.h" 
#include "iic.h"
#include "timer.h"
	u8 res;
	
void Bluetooth(void);	
int main(void)
{		
//	u16 led0pwmval=0;    
//	u8 dir=1;
//		u8 t;

//	u8 len;	
//	u16 times=0;  
	Stm32_Clock_Init(9);	//ϵͳʱ������
	delay_init(72);	  		//��ʱ��ʼ��
	uart_init(72,9600); 	//���ڳ�ʼ��Ϊ9600


//	IIC_Init();                  //6050_iic��ʼ��	
//	DMP_Init();                  //6050_DMP��ʼ��
//	MPU6050_initialize();        //6050_��ʼ��
//	iIC_Init(); 

//	Timer_init(899,0);   //����Ƶ��pwmƵ��Ϊ72M/900=80K hz  ��pwm��������Ϊ900����ʱ��3�ڲ�����ȽϼĴ���װ��ֵ��900�Ƚ�
//    LED_init();		
  	while(1)
	{
//		Read_DMP();
//			if(USART_RX_STA&0x8000)
//		{					   
//			len=USART_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
//			printf("\r\n�����͵���ϢΪ:\r\n");
//			for(t=0;t<len;t++)
//			{
//				USART1->DR=USART_RX_BUF[t];
//				while((USART1->SR&0X40)==0);//�ȴ����ͽ���
//			}
//			printf("\r\n\r\n");//���뻻��
//			USART_RX_STA=0;
//		}else
//		{
//			times++;
//			if(times%200==0)
//			{
//				printf("\r\nALIENTEK MiniSTM32������ ����ʵ��\r\n");
//				printf("����ԭ��@ALIENTEK\r\n\r\n\r\n");
//			}
//			if(times%200==0)printf("����������,�Իس�������\r\n");  
//			if(times%30==0)               //��˸LED,��ʾϵͳ��������.
//			delay_ms(10);   
//		}
         Bluetooth();
	}	 
} 


void Bluetooth()
{
	switch(res)
	{
		case 0x00:  led=0;   break;
		case 0x01:  led=1;   break;
	}
}






