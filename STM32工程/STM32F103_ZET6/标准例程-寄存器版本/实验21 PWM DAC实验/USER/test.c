#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 		 	 
#include "lcd.h" 
#include "key.h"
#include "adc.h"
#include "timer.h" 
#include "usmart.h" 	 
//ALIENTEKս��STM32������ ʵ��21
//PWM DAC ʵ�� 
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾  

//���������ѹ
//vol:0~330,����0~3.3V
void PWM_DAC_Set(u16 vol)
{
	float temp=vol;
	temp/=100;
	temp=temp*256/3.3;
	PWM_DAC_VAL=temp;	   
}	
int main(void)
{		 	
	u16 adcx;
	float temp;
 	u8 t=0;	 
	u16 pwmval=0;
	u8 key;
  	Stm32_Clock_Init(9);	//ϵͳʱ������
	uart_init(72,115200);	//���ڳ�ʼ��Ϊ115200
	delay_init(72);	   	 	//��ʱ��ʼ�� 
	usmart_dev.init(72);	//��ʼ��USMART	
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
 	KEY_Init();				//������ʼ��		 	
 	LCD_Init();				//��ʼ��LCD
	Adc_Init(); 			//adc��ʼ��	
	TIM1_PWM_Init(255,0);	//TIM1 PWM��ʼ��, Fpwm=72M/256=281.25Khz.				   
 	POINT_COLOR=RED;		//��������Ϊ��ɫ 
	LCD_ShowString(30,50,200,16,16,"WarShip STM32");	
	LCD_ShowString(30,70,200,16,16,"PWM DAC TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2015/1/15");	
	LCD_ShowString(30,130,200,16,16,"KEY_UP:+  KEY1:-");	
	//��ʾ��ʾ��Ϣ											      
	POINT_COLOR=BLUE;//��������Ϊ��ɫ
	LCD_ShowString(30,150,200,16,16,"PWM VAL:");	      
	LCD_ShowString(30,170,200,16,16,"DAC VOL:0.000V");	      
	LCD_ShowString(30,190,200,16,16,"ADC VOL:0.000V");		 
	PWM_DAC_VAL=pwmval;//��ʼֵΪ0	    	      
	while(1)
	{
		t++;
		key=KEY_Scan(0);			  
		if(key==WKUP_PRES)
		{		 
			if(pwmval<250)pwmval+=10;
			PWM_DAC_VAL=pwmval;		//���	
		}else if(key==KEY1_PRES)	
		{
			if(pwmval>10)pwmval-=10;
			else pwmval=0;
			PWM_DAC_VAL=pwmval; 		//���
		}	 
		if(t==10||key==KEY1_PRES||key==WKUP_PRES)	//WKUP/KEY1������,���߶�ʱʱ�䵽��
		{	  
 			adcx=PWM_DAC_VAL;
			LCD_ShowxNum(94,150,adcx,3,16,0);     	//��ʾDAC�Ĵ���ֵ
			temp=(float)adcx*(3.3/256);				//�õ�DAC��ѹֵ
			adcx=temp;
 			LCD_ShowxNum(94,170,temp,1,16,0);     	//��ʾ��ѹֵ��������
 			temp-=adcx;
			temp*=1000;
			LCD_ShowxNum(110,170,temp,3,16,0x80); 	//��ʾ��ѹֵ��С������
 			adcx=Get_Adc_Average(ADC_CH1,20);  		//�õ�ADCת��ֵ	  
			temp=(float)adcx*(3.3/4096);			//�õ�ADC��ѹֵ
			adcx=temp;
 			LCD_ShowxNum(94,190,temp,1,16,0);     	//��ʾ��ѹֵ��������
 			temp-=adcx;
			temp*=1000;
			LCD_ShowxNum(110,190,temp,3,16,0x80); 	//��ʾ��ѹֵ��С������
			t=0;
			LED0=!LED0;	   
		}	    
		delay_ms(10); 
	}
}


