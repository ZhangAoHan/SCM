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

#include "math.h"




/*************************** 文件说明 *******************************/
//此程序适用于七彩光子太极M3—STM32F103开发板及部分兼容的STM32系统，
//淘宝搜索"七彩光子 太极M3 STM32开发板"购买超高性价比开发板或获取更多资料
//只供学习使用，未经作者许可，不得用于其它任何用途！
/********************************************************************/ 


//u8 lcd_buf[50]={0};//用于临时存储LCD显示的字符串



float  angle = 0;//角度值
float  rad = 0;//弧度制
float  amplitude =3.3;//波形的峰峰值

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
	
	while(1)
	{
		//说明!!!
		//说明!!!
		//说明!!!
		//这里输出的正弦波并非真正的正弦波,因为无法输出负压,所以输出的是向上偏移二分之一幅值的正弦波
		//DAC通过PA4输出电压,通过示波器可观察波形
		
		
		rad=angle*3.1415926/180.0;//角度值转换为弧度制
		voltage=sin(rad)*(amplitude/2.0)+(amplitude/2.0);//计算出电压
		Dac1_Set_Vol((u32)(voltage*1000.0));//电压输出
		
		delay_us(50);//延时
		
		angle+=0.1;//步进0.1度,每个周期输出360÷0.1=3600次
		if(angle>360){//完成一个周期,重新开始
			angle=0;
		}
		
	}
}




