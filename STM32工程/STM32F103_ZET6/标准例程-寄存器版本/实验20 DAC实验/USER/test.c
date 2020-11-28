#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 		 	 
#include "lcd.h" 
#include "key.h"
#include "adc.h"
#include "dac.h" 
#include "usmart.h" 	 
//ALIENTEK战舰STM32开发板 实验20
//DAC 实验 
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
	uart_init(72,115200);	//串口初始化为115200
	delay_init(72);	   	 	//延时初始化 
	usmart_dev.init(72);	//初始化USMART	
	LED_Init();		  		//初始化与LED连接的硬件接口
 	KEY_Init();				//按键初始化		 	
 	LCD_Init();				//初始化LCD
	Adc_Init(); 			//adc初始化	
	Dac1_Init();		 	//DAC通道1初始化	   
	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(30,50,200,16,16,"WarShip STM32");	
	LCD_ShowString(30,70,200,16,16,"DAC TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2015/1/15");	
	LCD_ShowString(30,130,200,16,16,"KEY_UP:+  KEY1:-");	
	//显示提示信息											      
	POINT_COLOR=BLUE;//设置字体为蓝色
	LCD_ShowString(30,150,200,16,16,"DAC VAL:");	      
	LCD_ShowString(30,170,200,16,16,"DAC VOL:0.000V");	      
	LCD_ShowString(30,190,200,16,16,"ADC VOL:0.000V");	    
	DAC->DHR12R1=dacval;//初始值为0	    	      
	while(1)
	{
		t++;
		key=KEY_Scan(0);			  
		if(key==WKUP_PRES)
		{		 
			if(dacval<4000)dacval+=200;
			DAC->DHR12R1=dacval;		//输出	
		}else if(key==KEY1_PRES)	
		{
			if(dacval>200)dacval-=200;
			else dacval=0;
			DAC->DHR12R1=dacval; 		//输出
		}	 
		if(t==10||key==KEY1_PRES||key==WKUP_PRES) 	//WKUP/KEY1按下了,或者定时时间到了
		{	  
 			adcx=DAC->DHR12R1;
			LCD_ShowxNum(94,150,adcx,4,16,0);     	//显示DAC寄存器值
			temp=(float)adcx*(3.3/4096);			//得到DAC电压值
			adcx=temp;
 			LCD_ShowxNum(94,170,temp,1,16,0);     	//显示电压值整数部分
 			temp-=adcx;
			temp*=1000;
			LCD_ShowxNum(110,170,temp,3,16,0X80); 	//显示电压值的小数部分
 			adcx=Get_Adc_Average(ADC_CH1,10);		//得到ADC转换值	  
			temp=(float)adcx*(3.3/4096);			//得到ADC电压值
			adcx=temp;
 			LCD_ShowxNum(94,190,temp,1,16,0);     	//显示电压值整数部分
 			temp-=adcx;
			temp*=1000;
			LCD_ShowxNum(110,190,temp,3,16,0X80); 	//显示电压值的小数部分
			LED0=!LED0;	   
			t=0;
		}	    
		delay_ms(10);	

	}
}


