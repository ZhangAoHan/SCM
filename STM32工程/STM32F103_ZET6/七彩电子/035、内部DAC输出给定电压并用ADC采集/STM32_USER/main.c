/*  main.c  */

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "ezio.h"
#include "key.h"

#include "LcdApi.h"
#include "LcdBsp.h"
#include "touch.h"
#include "adc.h"
#include "dac.h"



/*************************** 文件说明 *******************************/
//此程序适用于七彩光子太极M3—STM32F103开发板及部分兼容的STM32系统，
//淘宝搜索"七彩光子 太极M3 STM32开发板"购买超高性价比开发板或获取更多资料
//只供学习使用，未经作者许可，不得用于其它任何用途！
/********************************************************************/ 


u8 lcd_buf[50]={0};//用于临时存储LCD显示的字符串



int main(void)
{
	u16 adc_value=0;
	float voltage=0;
	float adc_voltage=0;
	delay_init();	    //延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	USART1_Init(115200);//串口1初始化
	
	LCD_Init(); //LCD初始化
	Dac1_Init();
	ADC1_Init();
	
	while(1)
	{
		//说明!!!
		//说明!!!
		//说明!!!
		//DAC通过PA4输出电压,ADC通过PA1采集,
		//用杜邦线连接PA1和PA4可实现同步输出和采集
		
		Dac1_Set_Vol((u32)(voltage*1000.0));//电压输出
		
		printf("DAC OUT:%3.1fV  |  ",voltage);
		//彩屏显示(没有屏幕不会影响程序运行)
		sprintf((char*)lcd_buf,"DAC OUT:%3.1fV ",voltage);
		Show_Str(10,20,220,24,lcd_buf,16,0);
		
		delay_ms(10);//延时
		
		adc_value=Get_Adc_Average(1,10);//ADC 采集10次取平均值
		adc_voltage=(float)adc_value/4095.0*3.3;//计算出电压
		
		printf("ADC IN:%3.1fV \r\n",adc_voltage);
		//彩屏显示(没有屏幕不会影响程序运行)
		sprintf((char*)lcd_buf,"ADC IN:%3.1fV ",adc_voltage);
		Show_Str(10,50,220,24,lcd_buf,16,0);
		
		voltage+=0.1;//电压递增0.1V
		if(voltage>3.3){
			voltage=0.0;
		}
		
		delay_ms(1000);//延时
	}
}




