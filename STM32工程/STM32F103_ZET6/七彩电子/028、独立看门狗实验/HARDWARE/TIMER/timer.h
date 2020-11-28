#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"




/*************************** 文件说明 *******************************/
//此程序适用于七彩光子太极M3—STM32F103开发板及部分兼容的STM32系统，
//淘宝搜索"七彩光子 太极M3 STM32开发板"购买超高性价比开发板或获取更多资料
//只供学习使用，未经作者许可，不得用于其它任何用途！
/********************************************************************/ 








#define TIM1_IRQHandler TIM1_UP_IRQHandler
#define TIM8_IRQHandler TIM8_UP_IRQHandler






void TIM_SetInterval(u8 TIM_Index,u32 nus);
void TIM_Init(u8 TIM_Index,u16 Prescaler,u16 Period);







#endif
