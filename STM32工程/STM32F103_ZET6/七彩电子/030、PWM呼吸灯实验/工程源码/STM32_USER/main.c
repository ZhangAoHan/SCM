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

#include "TimerPWM.h"




/*************************** 文件说明 *******************************/
//此程序适用于七彩光子太极M3—STM32F103开发板及部分兼容的STM32系统，
//淘宝搜索"七彩光子 太极M3 STM32开发板"购买超高性价比开发板或获取更多资料
//只供学习使用，未经作者许可，不得用于其它任何用途！
/********************************************************************/ 


//u8 lcd_buf[50]={0};//用于临时存储LCD显示的字符串





int main(void)
{
	u8 flag=0;//方向标志
	u16 t=0;//临时占空比
	delay_init();	    //延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	USART1_Init(115200);//串口1初始化
	LCD_Init(); //LCD初始化
	
	
	TIM3_PWM_Init(1000-1,72-1);//72分频，计数到1000，周期为1ms，对应频率1KHz
	TIM_SetCompare2(TIM3,0);//设置占空比为0us，即0%占空比
	
	while(1)
	{
		if(flag==0){//暗-->亮
			t+=10;
			if(t>=1000){
				flag=1;
			}
			else{
				TIM_SetCompare2(TIM3,t);
			}
		}
		else{//亮-->暗
			if(t>10){
				t-=10;
				TIM_SetCompare2(TIM3,t);
			}
			else{
				t=0;
				flag=0;
				TIM_SetCompare2(TIM3,t);
				delay_ms(1000);//延时1.5s,模拟呼吸的感觉
				delay_ms(500);
			}
		}
		delay_ms(10);
	}
}




