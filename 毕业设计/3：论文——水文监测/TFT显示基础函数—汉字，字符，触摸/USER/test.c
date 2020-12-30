#include "sys.h"
#include "usart.h"		
#include "delay.h"	 
#include "lcd.h"
#include "touch.h"  
#include "w25q128.h"  
#include "text.h"	
#include "24l01.h"
#include "control.h"
#include "timer.h"

u8 tmp_buf[33];
u8 door=0;
u8 times=0;
unsigned char SN[4]={0,0,0,0}; //����
unsigned char NEW_SN[4]={0,0,0,0}; //����
unsigned char OLD_SN[4]={0,0,0,0}; //����
int main(void)
{				 

	Stm32_Clock_Init(9);	//ϵͳʱ������
	delay_init(72);	  		//��ʱ��ʼ��
	uart_init(72,115200); 	//���ڳ�ʼ��Ϊ115200
	LCD_Init();
	W25QXX_Init();				//��ʼ��W25Q128 ��SPI2
	tp_dev.init();			//��������ʼ�� 
	NRF24L01_Init();    		//��ʼ��NRF24L01 
	Key_init();
	
	while(font_init()) 			//����ֿ�
	{;}  
	while(NRF24L01_Check())
	{
		LCD_ShowString(30,130,200,16,16,"NRF24L01 Error");
		delay_ms(200);
		LCD_Fill(30,130,239,130+16,WHITE);
 		delay_ms(200);
	}
	old_id_read();
		NRF24L01_RX_Mode();	
	LCD_Clear(WHITE);	
  	while(1)
	{

		use_control();
	}	 
} 






