#include "sys.h"
#include "usart.h"		
#include "delay.h"	 
#include "lcd.h"
#include "touch.h"  
#include "w25q128.h"  
#include "text.h"
#include "ds18b20.h"
#include "ds18b202.h"
#include "memory.h" 
#include "rc522.h"
#include "timer.h"
#include "adc.h"
#include "led.h"
#include "control.h"
#include "at24c02.h"  
u8 tim=0;        //ˮ�ÿ�����׼��
u8 tempdate1,date1,tempdate2,date2,tempdate3,date3,tempdate4,date4,tempdate5,date5;
u8 tempoutdate1,outdate1,tempoutdate2,outdate2,tempoutdate3,outdate3,tempoutdate4,outdate4,tempoutdate5,outdate5;
u16 SL;
u8 page=1;
int main(void)
{		
	
	Stm32_Clock_Init(9);	//ϵͳʱ������
	delay_init(72);	  		//��ʱ��ʼ��
	uart_init(72,115200); 	//���ڳ�ʼ��Ϊ115200
	LCD_Init();
	W25QXX_Init();				//��ʼ��W25Q128 ��SPI2
	tp_dev.init();			//��������ʼ�� 
	InitRc522();
	Adc_Init();		  		//ADC��ʼ��
	Adc2_Init();	    	
	LED_Init();	
	tempdate1=AT24CXX_ReadOneByte(60);    //��ȡ��5������
	date1=AT24CXX_ReadOneByte(61);
		tempdate2=AT24CXX_ReadOneByte(62);
	date2=AT24CXX_ReadOneByte(63);
		tempdate3=AT24CXX_ReadOneByte(64);
	date3=AT24CXX_ReadOneByte(65);
		tempdate4=AT24CXX_ReadOneByte(66);
	date4=AT24CXX_ReadOneByte(67);
		tempdate5=AT24CXX_ReadOneByte(68);
	date5=AT24CXX_ReadOneByte(69);
			tempoutdate1=AT24CXX_ReadOneByte(70);    //��ȡ��5������
	outdate1=AT24CXX_ReadOneByte(71);
		tempoutdate2=AT24CXX_ReadOneByte(72);
	outdate2=AT24CXX_ReadOneByte(73);
		tempoutdate3=AT24CXX_ReadOneByte(74);
	outdate3=AT24CXX_ReadOneByte(75);
		tempoutdate4=AT24CXX_ReadOneByte(76);
	outdate4=AT24CXX_ReadOneByte(77);
		tempoutdate5=AT24CXX_ReadOneByte(78);
	outdate5=AT24CXX_ReadOneByte(79);
		init_display();
		TIM2_Int_Init(1999,7199);//10Khz�ļ���Ƶ�ʣ�200ms
		TIM3_Int(65535);
		tim=0;
		SB=1;
		
 	while(1)
	{	

			control();

			  
	}

	}	 





