/*  key.h  */

#ifndef __KEY_H
#define __KEY_H
#include "sys.h"

/***********************************************************************/
//此程序适用于七彩光子太极M3—STM32F103开发板及部分兼容的STM32系统，
//只供学习使用，未经作者许可，不得用于其它任何用途！
/***********************************************************************/

//按键定义
#define KEY0  0
#define KEY1  1
#define KEY2  2
#define KEY3  3

//key0 PE4
//key1 PE3
//key2 PE2
//key3/key_up PA0 


/********************* 按键所在GPIO口宏定义 ***************************/
#define KEY0_GPIO GPIOE
#define KEY1_GPIO GPIOE
#define KEY2_GPIO GPIOE
#define KEY3_GPIO GPIOA

#define KEY0_PIN GPIO_Pin_4
#define KEY1_PIN GPIO_Pin_3
#define KEY2_PIN GPIO_Pin_2
#define KEY3_PIN GPIO_Pin_0
/****************************** end *********************************/


/********************* 按键所在GPIO口时钟宏定义 *********************/
#define KEY0_RCC_CLK  RCC_APB2Periph_GPIOE
#define KEY1_RCC_CLK  RCC_APB2Periph_GPIOE
#define KEY2_RCC_CLK  RCC_APB2Periph_GPIOE
#define KEY3_RCC_CLK  RCC_APB2Periph_GPIOA
/****************************** end *********************************/



/********************* 按键硬件状态获取宏定义 ***********************/
#define KEY0_HARD_STA  ((KEY0_GPIO->IDR & (uint16_t)KEY0_PIN)==0)
#define KEY1_HARD_STA  ((KEY1_GPIO->IDR & (uint16_t)KEY1_PIN)==0)
#define KEY2_HARD_STA  ((KEY2_GPIO->IDR & (uint16_t)KEY2_PIN)==0)
#define KEY3_HARD_STA  ((KEY3_GPIO->IDR & (uint16_t)KEY3_PIN)!=0)//这个按键是高电平有效
/****************************** end *********************************/

 
 
/********************* 按键按下返回值宏定义 *************************/
#define KEY0_PRES 	1	//KEY0按下
#define KEY1_PRES  	2	//KEY1按下
#define KEY2_PRES 	3	//KEY2按下
#define WKUP_PRES   4	//KEY_UP按下(即WK_UP/KEY_UP)
/****************************** end *********************************/



/********************* 按键函数声明 *********************************/

void Key_Init(void);   //IO初始化
u8 Key_Scan(u8);  	   //按键扫描函数
u8 Key_GetSta(u8 key); //按键当前状态获取  1:已被按下  0:未被按下


/****************************** end *********************************/











#endif











