#include "sys.h"
#include "usart.h"		
#include "delay.h"	 
#include "lcd.h"
#include "touch.h"  
#include "w25q128.h"  
#include "text.h"	
#include "24l01.h" 

u8 mode=0;

int main(void)
{				 
	u8 tmp_buf[33];	  
	Stm32_Clock_Init(9);	//ϵͳʱ������
	delay_init(72);	  		//��ʱ��ʼ��
	uart_init(72,115200); 	//���ڳ�ʼ��Ϊ115200
	LCD_Init();
	W25QXX_Init();				//��ʼ��W25Q128 ��SPI2
	tp_dev.init();			//��������ʼ�� 
	NRF24L01_Init();  
	while(font_init()) 			//����ֿ�
	{;}  
	while(NRF24L01_Check())
	{
 		delay_ms(200);
	}
  	while(1)
	{
		if(mode==0)
		{
			NRF24L01_RX_Mode();	
			if(NRF24L01_RxPacket(tmp_buf)==0)//һ�����յ���Ϣ,����ʾ����.
			{
				if(tmp_buf[0]==' '&&tmp_buf[5]=='!')
				{
					LCD_ShowxNum(20,20,tmp_buf[1],4,16,0);
					LCD_ShowxNum(20,50,tmp_buf[2],4,16,0);
					LCD_ShowxNum(20,80,tmp_buf[3],4,16,0);
					LCD_ShowxNum(20,110,tmp_buf[4],4,16,0);
					tmp_buf[0]=tmp_buf[1]=tmp_buf[2]=tmp_buf[3]=tmp_buf[4]=tmp_buf[5]=0;
				}
			}
		}
//		if(mode==1)
//		{
//			
//		}
	}	 
} 






