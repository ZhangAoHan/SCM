#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"   
#include "lcd.h"  
#include "adc.h" 
//ALIENTEK Mini STM32开发板范例代码16
//内部温度传感器实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司
   	
int main(void)
{			   
	u16 adcx;
	float temp;
	float temperate;	 
  	Stm32_Clock_Init(9);	//系统时钟设置
	uart_init(72,9600);	 	//串口初始化为9600
	delay_init(72);	   	 	//延时初始化 
	LED_Init();		  		//初始化与LED连接的硬件接口
 	LCD_Init();			   	//初始化LCD 			 	
 	Adc_Init();		  		//ADC初始化	    
	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(60,50,200,16,16,"Mini STM32");	
	LCD_ShowString(60,70,200,16,16,"Temperature TEST");	
	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,200,16,16,"2014/3/9");	
	//显示提示信息											      
	POINT_COLOR=BLUE;//设置字体为蓝色
	LCD_ShowString(60,130,200,16,16,"TEMP_VAL:");	      
	LCD_ShowString(60,150,200,16,16,"TEMP_VOL:0.000V");	      
	LCD_ShowString(60,170,200,16,16,"TEMPERATE:00.00C");	  
	while(1)
	{
		adcx=Get_Adc_Average(ADC_CH_TEMP,10);
		LCD_ShowxNum(132,130,adcx,4,16,0);//显示ADC的值
		temp=(float)adcx*(3.3/4096);
		temperate=temp;//保存温度传感器的电压值
		adcx=temp;
		LCD_ShowxNum(132,150,adcx,1,16,0);     		//显示电压值整数部分
		temp-=(u8)temp;				    			//减掉整数部分		  
		LCD_ShowxNum(148,150,temp*1000,3,16,0X80);	//显示电压小数部分
 		temperate=(1.43-temperate)/0.0043+25;		//计算出当前温度值	 
		LCD_ShowxNum(140,170,(u8)temperate,2,16,0); //显示温度整数部分
		temperate-=(u8)temperate;	  
		LCD_ShowxNum(164,170,temperate*100,2,16,0X80);//显示温度小数部分
		LED0=!LED0;
		delay_ms(250);
	}										    
}	









