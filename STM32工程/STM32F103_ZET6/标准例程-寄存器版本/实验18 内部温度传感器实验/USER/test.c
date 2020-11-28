#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 		 	 
#include "lcd.h" 
#include "adc.h" 
//ALIENTEKս��STM32������ ʵ��18
//�ڲ��¶ȴ����� ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾  

int main(void)
{		 	
	short temp;  
  	Stm32_Clock_Init(9);	//ϵͳʱ������
	uart_init(72,115200);	//���ڳ�ʼ��Ϊ115200
	delay_init(72);	   	 	//��ʱ��ʼ�� 
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
  	LCD_Init();				//��ʼ��LCD
 	Adc_Init();		  		//ADC��ʼ��	    
	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(30,50,200,16,16,"WarShip STM32");	
	LCD_ShowString(30,70,200,16,16,"Temperature TEST");	 	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2015/1/14");	  
	POINT_COLOR=BLUE;//��������Ϊ��ɫ      
	LCD_ShowString(30,140,200,16,16,"TEMPERATE: 00.00C");	      
	while(1)
	{
		temp=Get_Temprate();	//�õ��¶�ֵ 
		if(temp<0)
		{
			temp=-temp;
			LCD_ShowString(30+10*8,140,16,16,16,"-");	//��ʾ����
		}else LCD_ShowString(30+10*8,140,16,16,16," ");	//�޷���		
		LCD_ShowxNum(30+11*8,140,temp/100,2,16,0);		//��ʾ��������
		LCD_ShowxNum(30+14*8,140,temp%100,2,16, 0X80);	//��ʾС������
		LED0=!LED0;
		delay_ms(250);	
	} 
}


