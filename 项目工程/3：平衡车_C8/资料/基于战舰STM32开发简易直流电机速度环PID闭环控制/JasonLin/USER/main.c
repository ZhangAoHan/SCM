/***********************************************************************************
Author     :JasonLin
version	   :V1.1
Date       :2014/8/2
Description:Based on the STM32 Micro Control Unit design simple movement controller  
************************************************************************************/

#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "UserConfiguration.h"
#include "UserFunction.h"
#include "UserDelay.h"
#include "lcd.h" 
#include "led.h"

extern s32 CNT2,CNT3,CNT4,CNT5,V2,V3,V4,V5,rcnt2,rcnt3,rcnt4,rcnt5;

int main(void)
{	
  	SystemInit();

	UserNVIC_Configuration();

	UserTIM_Configuration();   

	UserLed_Configuration();

	UserDelay_Configuration();

	while(1)
	{								
	   delay_ms(200);LED1=!LED1;delay_ms(200);//LED1提示系统正常运行
	}	
	
	
	 
}








