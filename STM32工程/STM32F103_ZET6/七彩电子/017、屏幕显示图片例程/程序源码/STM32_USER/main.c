/*  main.c  */

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "LcdBsp.h"
#include "LcdApi.h"
#include "image.h"


/***********************************************************************/
//此程序适用于七彩光子太极M3—STM32F103开发板及部分兼容的STM32系统，
//只供学习使用，未经作者许可，不得用于其它任何用途！
/***********************************************************************/
 
 


int main(void)
{
	//u32 i=0;
	delay_init();	    //延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	LED_Init();
	USART1_Init(115200);//串口1初始化
	
	LCD_Init();	
	POINT_COLOR = RED;
	LCD_ShowString(20,150,220,24,24,"STM32 LCD Test !");//显示字符串
	
	Show_Str(20,20,220,12,"七彩光子 太极M3开发板",12,0);//覆盖显示
	Show_Str(20,40,220,16,"七彩光子 太极M3开发板",16,0);//覆盖显示
	Show_Str(20,65,220,24,"七彩光子 太极M3开发板",24,0);//覆盖显示
	
	delay_ms(1000);
	delay_ms(1000);
	
	//LCD_Fill(20,150,20+220,150+24,WHITE);
	
	LCD_Color_Fill(0,0,240-1,320-1,(u16*)&gImage_image[0]);//将数组强制转化为u16*,注意图像大小不能超区域,否则可能会跑飞
	
	
	
	while(1)
	{
		LED_TOGGLE(LED0);
		delay_ms(500);

	}
}




