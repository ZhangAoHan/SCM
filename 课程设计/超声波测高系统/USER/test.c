#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "lcd.h"
#include "touch.h"  
#include "w25qxx.h"  
#include "text.h"	 
#include "csb.h"   
#include "control.h"   
u32 Distance;  
float m1,m2;
int main(void)
{				 
	Stm32_Clock_Init(9);	//ϵͳʱ������
	delay_init(72);	  		//��ʱ��ʼ��
	uart_init(72,115200); 	//���ڳ�ʼ��Ϊ115200
	LCD_Init();
	W25QXX_Init();				//��ʼ��W25Q128 ��SPI2
	POINT_COLOR=RED;
	tp_dev.init();			//��������ʼ�� 
	TIM2_Cap_Init(0XFFFF,72-1);	
	TIM3_Int_Init(999,7199);//ʱ������0.1ms��
	while(font_init()) 			//����ֿ�
	{ 	
		LCD_Clear(WHITE);		   	//����
 		POINT_COLOR=RED;			//��������Ϊ��ɫ	   	   	  
		LCD_ShowString(30,50,200,16,16,"WarShip STM32");								 						    
		LCD_ShowString(30,90,200,16,16,"Font Updating...");	  
		LCD_ShowString(30,110,200,16,16,"Font Update Success!   ");
		delay_ms(1500);	
		LCD_Clear(WHITE);//����	       
	}  
			TFT_S_Display();
		while(1)
	{
		 
		TFT_Display();
	}
} 



//		printf("t:%d\r\n",t);


