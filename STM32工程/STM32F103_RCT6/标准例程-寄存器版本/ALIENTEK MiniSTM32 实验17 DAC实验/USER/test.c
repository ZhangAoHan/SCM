#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"   
#include "lcd.h"  
#include "adc.h" 
#include "key.h" 
#include "usmart.h" 
#include "dac.h" 
//ALIENTEK Mini STM32开发板范例代码17
//DAC实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司
   	
int main(void)
{			   
	u16 adcx;
	float temp;
 	u8 t=0;	 
	u16 dacval=0;
	u8 key;
 	Stm32_Clock_Init(9);	//系统时钟设置
	uart_init(72,9600);	 	//串口初始化为9600
	delay_init(72);	   	 	//延时初始化 
	LED_Init();		  		//初始化与LED连接的硬件接口
 	LCD_Init();			   	//初始化LCD 		
	KEY_Init();				//按键初始化		 	
 	Adc_Init();		  		//ADC初始化
	Dac1_Init();		 	//DAC通道1初始化	
	usmart_dev.init(72);	//USMART初始化
	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(60,50,200,16,16,"Mini STM32");	
	LCD_ShowString(60,70,200,16,16,"DAC TEST");	
	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,200,16,16,"2014/3/9");	
	LCD_ShowString(60,130,200,16,16,"WK_UP:+  KEY0:-");	
	//显示提示信息											      
	POINT_COLOR=BLUE;//设置字体为蓝色
	LCD_ShowString(60,150,200,16,16,"DAC VAL:");	      
	LCD_ShowString(60,170,200,16,16,"DAC VOL:0.000V");	      
	LCD_ShowString(60,190,200,16,16,"ADC VOL:0.000V");	    
	DAC->DHR12R1=dacval;//初始值为0	    	      
	while(1)
	{
		t++;
		key=KEY_Scan(0);			  
		if(key==WKUP_PRES)
		{		 
			if(dacval<4000)dacval+=200;
			DAC->DHR12R1=dacval;		//输出	
		}else if(key==KEY0_PRES)	
		{
			if(dacval>200)dacval-=200;
			else dacval=0;
			DAC->DHR12R1=dacval; 		//输出
		}	 
		if(t==10||key==KEY0_PRES||key==WKUP_PRES) 	//WKUP/KEY1按下了,或者定时时间到了
		{	  
 			adcx=DAC->DHR12R1;
			LCD_ShowxNum(124,150,adcx,4,16,0);     	//显示DAC寄存器值
			temp=(float)adcx*(3.3/4096);			//得到DAC电压值
			adcx=temp;
 			LCD_ShowxNum(124,170,temp,1,16,0);     	//显示电压值整数部分
 			temp-=adcx;
			temp*=1000;
			LCD_ShowxNum(140,170,temp,3,16,0X80); 	//显示电压值的小数部分
 			adcx=Get_Adc_Average(ADC_CH1,10);		//得到ADC转换值	  
			temp=(float)adcx*(3.3/4096);			//得到ADC电压值
			adcx=temp;
 			LCD_ShowxNum(124,190,temp,1,16,0);     	//显示电压值整数部分
 			temp-=adcx;
			temp*=1000;
			LCD_ShowxNum(140,190,temp,3,16,0X80); 	//显示电压值的小数部分
			LED0=!LED0;	   
			t=0;
		}	    
		delay_ms(10);	
	}										    
}	









