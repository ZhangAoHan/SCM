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


/*************************** 文件说明 *******************************/
//此程序适用于七彩光子太极M3—STM32F103开发板及部分兼容的STM32系统，
//淘宝搜索"七彩光子 太极M3 STM32开发板"购买超高性价比开发板或获取更多资料
//只供学习使用，未经作者许可，不得用于其它任何用途！
/********************************************************************/ 





u8 lcd_buf[50]={0};//用于临时存储LCD显示的字符串

int main(void)
{
	u16 value=0;
	float voltage=0;
	
	delay_init();	    //延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	USART1_Init(115200);//串口1初始化
	
	LCD_Init();    //LCD初始化
	ADC1_Init();
	
	while(1)
	{
		//通过ADC通道1采集并显示外部电压
		//电压由PA1输入
		
		//注意! 所采集电压不得高于3.3V!!!!
		//注意! 所采集电压不得高于3.3V!!!!
		//注意! 所采集电压不得高于3.3V!!!!
		
		value=Get_Adc_Average(1,10);//采集10次取平均值
		voltage=(float)value/4095.0*3.3;//计算出电压
		
		//串口发送结果
		printf("ADC Value : %5d  | ",value);
		printf("voltage : %6.3f V\r\n",voltage);
		
		//彩屏显示结果(没有屏幕不会影响程序运行)
		sprintf((char*)lcd_buf,"ADC Value:%5d ",value);
		Show_Str(10,20,220,24,lcd_buf,16,0);
		sprintf((char*)lcd_buf,"voltage:%6.3fV",voltage);
		Show_Str(10,50,220,24,lcd_buf,16,0);
		
		//延时
		delay_ms(600);
	}
}




