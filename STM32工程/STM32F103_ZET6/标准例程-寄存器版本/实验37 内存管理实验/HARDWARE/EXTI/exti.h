#ifndef __EXTI_H
#define __EXIT_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板V3
//外部中断 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2015/1/10
//版本：V1.1
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved		
//********************************************************************************
//V1.1 20150118
//1,增加EXTI8_Init函数。
//2,增加EXTI9_5_IRQHandler函数											  
//////////////////////////////////////////////////////////////////////////////////  

void EXTIX_Init(void);	//外部中断初始化	
void EXTI8_Init(void);	
#endif

























