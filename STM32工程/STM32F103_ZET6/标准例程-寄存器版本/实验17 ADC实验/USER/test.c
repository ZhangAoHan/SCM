#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 		 	 
#include "lcd.h" 
#include "adc.h" 
//ALIENTEKս��STM32������ ʵ��17
//ADC ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾  

int main(void)
{		 	
	u16 adcx;
	float temp;   			    
  	Stm32_Clock_Init(9);	//ϵͳʱ������
	uart_init(72,115200);	//���ڳ�ʼ��Ϊ115200
	delay_init(72);	   	 	//��ʱ��ʼ�� 
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
  	LCD_Init();				//��ʼ��LCD
 	Adc_Init();		  		//ADC��ʼ��	    
	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(30,50,200,16,16,"WarShip STM32");	
	LCD_ShowString(30,70,200,16,16,"ADC TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2015/1/14");	
	//��ʾ��ʾ��Ϣ
	POINT_COLOR=BLUE;//��������Ϊ��ɫ
	LCD_ShowString(30,130,200,16,16,"ADC_CH0_VAL:");	      
	LCD_ShowString(30,150,200,16,16,"ADC_CH0_VOL:0.000V");	      
	while(1)
	{
		adcx=Get_Adc_Average(ADC_CH1,10);
		LCD_ShowxNum(126,130,adcx,4,16,0);//��ʾADC��ֵ
		temp=(float)adcx*(3.3/4096);
		adcx=temp;
		LCD_ShowxNum(126,150,adcx,1,16,0);//��ʾ��ѹֵ
		temp-=adcx;
		temp*=1000;
		LCD_ShowxNum(142,150,temp,3,16,0X80);
		LED0=!LED0;
		delay_ms(250);	
	}
}


