/*     iwdg.c    */

#ifndef __IWDG_H_
#define __IWDG_H_

#include "sys.h"





/*************************** 文件说明 *******************************/
//作者:七彩光子
//此程序适用于七彩光子太极M3—STM32F103开发板及部分兼容的STM32系统，
//淘宝搜索"七彩光子 太极M3 STM32开发板"购买超高性价比开发板或获取更多资料
//只供学习使用，未经作者许可，不得用于其它任何用途！
/********************************************************************/ 




//初始化看门狗并设置看门狗时间为10ms
void IWDG_Init_10ms(void);
//初始化看门狗并设置看门狗时间为50ms
void IWDG_Init_50ms(void);
//初始化看门狗并设置看门狗时间为200ms
void IWDG_Init_200ms(void);
//初始化看门狗并设置看门狗时间为500ms
void IWDG_Init_500ms(void);
//初始化看门狗并设置看门狗时间为1s
void IWDG_Init_1s(void);
//初始化看门狗并设置看门狗时间为2s
void IWDG_Init_2s(void);
//初始化看门狗并设置看门狗时间为4s
void IWDG_Init_4s(void);
//初始化看门狗并设置看门狗时间为8s
void IWDG_Init_8s(void);
//初始化看门狗并设置看门狗时间为16s
void IWDG_Init_16s(void);


//根据分频系数和装载值初始化看门狗,可按照需求自定义复位时间
void IWDG_Init(u8 prer,u16 rlr);
void IWDG_Feed(void);//喂狗

#endif
