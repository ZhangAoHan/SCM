#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"   
#include "lcd.h"  
#include "adc.h" 
//ALIENTEK Mini STM32�����巶������16
//�ڲ��¶ȴ�����ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾
   	
int main(void)
{			   
	u16 adcx;
	float temp;
	float temperate;	 
  	Stm32_Clock_Init(9);	//ϵͳʱ������
	uart_init(72,9600);	 	//���ڳ�ʼ��Ϊ9600
	delay_init(72);	   	 	//��ʱ��ʼ�� 
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
 	LCD_Init();			   	//��ʼ��LCD 			 	
 	Adc_Init();		  		//ADC��ʼ��	    
	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(60,50,200,16,16,"Mini STM32");	
	LCD_ShowString(60,70,200,16,16,"Temperature TEST");	
	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,200,16,16,"2014/3/9");	
	//��ʾ��ʾ��Ϣ											      
	POINT_COLOR=BLUE;//��������Ϊ��ɫ
	LCD_ShowString(60,130,200,16,16,"TEMP_VAL:");	      
	LCD_ShowString(60,150,200,16,16,"TEMP_VOL:0.000V");	      
	LCD_ShowString(60,170,200,16,16,"TEMPERATE:00.00C");	  
	while(1)
	{
		adcx=Get_Adc_Average(ADC_CH_TEMP,10);
		LCD_ShowxNum(132,130,adcx,4,16,0);//��ʾADC��ֵ
		temp=(float)adcx*(3.3/4096);
		temperate=temp;//�����¶ȴ������ĵ�ѹֵ
		adcx=temp;
		LCD_ShowxNum(132,150,adcx,1,16,0);     		//��ʾ��ѹֵ��������
		temp-=(u8)temp;				    			//������������		  
		LCD_ShowxNum(148,150,temp*1000,3,16,0X80);	//��ʾ��ѹС������
 		temperate=(1.43-temperate)/0.0043+25;		//�������ǰ�¶�ֵ	 
		LCD_ShowxNum(140,170,(u8)temperate,2,16,0); //��ʾ�¶���������
		temperate-=(u8)temperate;	  
		LCD_ShowxNum(164,170,temperate*100,2,16,0X80);//��ʾ�¶�С������
		LED0=!LED0;
		delay_ms(250);
	}										    
}	









