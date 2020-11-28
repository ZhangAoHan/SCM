
/*  key.c  */


#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"

/***********************************************************************/
//此程序适用于七彩光子太极M3—STM32F103开发板及部分兼容的STM32系统，
//只供学习使用，未经作者许可，不得用于其它任何用途！
/***********************************************************************/


u8 Key_Sta[4]={0};//按键的状态


//按键初始化函数
void Key_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(KEY0_RCC_CLK|KEY1_RCC_CLK|KEY2_RCC_CLK|KEY3_RCC_CLK,ENABLE);//使能PORTA,PORTE时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;//KEY0-KEY2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIOE2,3,4

	//初始化 WK_UP-->GPIOA.0	  下拉输入
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0设置成输入，默认下拉	  
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.0

}


//独立按键按键处理函数
//返回按键值
//0，没有任何按键按下
//1，KEY0按下
//2，KEY1按下
//3，KEY2按下 
//4，KEY3按下 WK_UP
//注意此函数支持多按键同时按下检测,
//但同时按下时有响应优先级,KEY0>KEY1>KEY2>KEY3!!
//mode  保留,随便传入一个值就OK
//
u8 Key_Scan(u8 mode)
{
	//key0
	if(Key_Sta[0]==0){
		if(KEY0_HARD_STA){
			delay_ms(10);
			if(KEY0_HARD_STA){
				Key_Sta[0]=1;
				return KEY0_PRES;
			}
		}
	}
	else{
		if(!(KEY0_HARD_STA)){
			Key_Sta[0]=0;
		}
	}
//KEY1
	if(Key_Sta[1]==0){
		if(KEY1_HARD_STA){
			delay_ms(10);
			if(KEY1_HARD_STA){
				Key_Sta[1]=1;
				return KEY1_PRES;
			}
		}
	}
	else{
		if(!(KEY1_HARD_STA)){
			Key_Sta[1]=0;
		}
	}	
	//Key2
	if(Key_Sta[2]==0){
		if(KEY2_HARD_STA){
			delay_ms(10);
			if(KEY2_HARD_STA){
				Key_Sta[2]=1;
				return KEY2_PRES;
			}
		}
	}
	else{
		if(!(KEY2_HARD_STA)){
			Key_Sta[2]=0;
		}
	}	
	
	//KEY3
	if(Key_Sta[3]==0){
		if(KEY3_HARD_STA){
			delay_ms(10);
			if(KEY3_HARD_STA){
				Key_Sta[3]=1;
				return WKUP_PRES;
			}
		}
	}
	else{
		if(!(KEY3_HARD_STA)){
			Key_Sta[3]=0;
		}
	}	
	
 	return 0;// 无按键按下
}

//获取按键的当前状态
u8 Key_GetSta(u8 key){
	if(key<=3){
		return Key_Sta[key];
	}
	return 0;
}























