#include "sys.h"
#include "usart.h"		
#include "delay.h"	   
#include "TFT.h"   
#include "ff.h"  
#include "exfuns.h"
#include "fontupd.h"
#include "text.h"	
#include "malloc.h" 
#include "MMC_SD.h" 
#include "AT24c02.h"  
#include "touch.h"  

int main(void)
{
	u8 key;
	
	Stm32_Clock_Init(9); //ϵͳʱ������
	uart_init(72,115200); //���ڳ�ʼ��Ϊ 115200
	delay_init(72); //��ʱ��ʼ��
	LCD_Init();
 	mem_init();				//��ʼ���ڴ��
	exfuns_init();			//Ϊfatfs��ر��������ڴ�  
		tp_dev.init();			//��������ʼ��
	while(font_init()) 	//����ֿ�
	{  
		key=update_font(20,110,16);//�����ֿ�
		while(key)//����ʧ��		
		{			 		  
			LCD_ShowString(60,110,200,16,16,"Font Update Failed!");
			delay_ms(200);
			LCD_Fill(20,110,200+20,110+16,WHITE);
			delay_ms(200);		       
		} 		  
		LCD_ShowString(60,110,200,16,16,"Font Update Success!");
		delay_ms(1500);	
		LCD_Clear(RED);//����	       
	}
	LCD_Clear(WHITE);
		
	while(1)
	{


			
		
	
	}
}


