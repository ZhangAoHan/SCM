#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 
#include "timer.h" 
//ALIENTEK战舰STM32开发板实验10
//输入捕获 实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司 

extern u8  TIM5CH1_CAPTURE_STA;		//输入捕获状态		    				
extern u16	TIM5CH1_CAPTURE_VAL;	//输入捕获值
int main(void)
{					   
	u32 temp=0;  	
	Stm32_Clock_Init(9);	//系统时钟设置
	uart_init(72,115200);	//串口初始化为115200
	delay_init(72);	   	 	//延时初始化 
	LED_Init();		  		//初始化与LED连接的硬件接口
  	TIM3_PWM_Init(899,0);	//不分频。PWM频率=72000/(899+1)=80Khz
 	TIM5_Cap_Init(0XFFFF,72-1);	//以1Mhz的频率计数 
   	while(1)
	{
 		delay_ms(10);
		LED0_PWM_VAL++;
		if(LED0_PWM_VAL==300)LED0_PWM_VAL=0;	 		 
 		if(TIM5CH1_CAPTURE_STA&0X80)//成功捕获到了一次高电平
		{
			temp=TIM5CH1_CAPTURE_STA&0X3F;
			temp*=65536;					//溢出时间总和
			temp+=TIM5CH1_CAPTURE_VAL;		//得到总的高电平时间
			printf("HIGH:%d us\r\n",temp);	//打印总的高点平时间
			TIM5CH1_CAPTURE_STA=0;			//开启下一次捕获
		}
	}
}


