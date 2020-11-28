#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 		 	 
#include "lcd.h" 
#include "adc.h" 
//ALIENTEK战舰STM32开发板 实验17
//ADC 实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司  

int main(void)
{		 	
	u16 adcx;
	float temp;   			    
  	Stm32_Clock_Init(9);	//系统时钟设置
	uart_init(72,115200);	//串口初始化为115200
	delay_init(72);	   	 	//延时初始化 
	LED_Init();		  		//初始化与LED连接的硬件接口
  	LCD_Init();				//初始化LCD
 	Adc_Init();		  		//ADC初始化	    
	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(30,50,200,16,16,"WarShip STM32");	
	LCD_ShowString(30,70,200,16,16,"ADC TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2015/1/14");	
	//显示提示信息
	POINT_COLOR=BLUE;//设置字体为蓝色
	LCD_ShowString(30,130,200,16,16,"ADC_CH0_VAL:");	      
	LCD_ShowString(30,150,200,16,16,"ADC_CH0_VOL:0.000V");	      
	while(1)
	{
		adcx=Get_Adc_Average(ADC_CH1,10);
		LCD_ShowxNum(126,130,adcx,4,16,0);//显示ADC的值
		temp=(float)adcx*(3.3/4096);
		adcx=temp;
		LCD_ShowxNum(126,150,adcx,1,16,0);//显示电压值
		temp-=adcx;
		temp*=1000;
		LCD_ShowxNum(142,150,temp,3,16,0X80);
		LED0=!LED0;
		delay_ms(250);	
	}
}


