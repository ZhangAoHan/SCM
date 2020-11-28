#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include <stdio.h>
#include "KEY.H"
#include "led.h"

extern float CH_Data[4];  //通道值
extern int Init_flag;//FDC2214复位标志
extern unsigned int Mode_flag;
extern unsigned int Mode3_Gesture_cnt;     //记录模式3,4手势个数
extern unsigned int Mode4_Gesture_cnt;     //记录模式3,4手势个数

float trani_ch0[200],trani_ch1[200],trani_ch2[200];//训练数组


void KEY_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能PE端口时钟（GPIO外设是挂载在APB2总线上的）
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;		 //设置要用的GPIO口为PE5,PE6
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPU;			 //设置为上拉输入（因为外部没有上下拉电阻，只能将低电平有效的按键IO口设置为上拉输入）
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //初始化GPIOE5,6
}

u8 KEY_Scan(void)
{
	static u8 key_up_mode=1;//模式按键弹起标志
	static u8 key_up_train=1;//模式按键弹起标志
	static u8 reset=1;//模式按键弹起标志
	unsigned int i;
		
	 if(key_up_mode&&(KEY_mode==KEY_PRESSED) )			//模式确认按键
	{
		delay_ms(10);
		key_up_mode=0;
		if(Mode_flag>=5) //4种模式
		{
			Mode_flag=0;
			USART_SendData(USART1,0x10);//模式0标志
			while((USART1->SR&0X40)==0);
		}
		LED0=0;
		delay_ms(100);
		LED0=1;
	}
	else if(KEY_mode==1) key_up_mode=1;
/*-----------------------------------------------------*/	
	if(key_up_train&&(KEY_train==KEY_PRESSED) )			//训练手势计数按键
	{
		delay_ms(10);
		key_up_train=0;
		
	}
	else if(KEY_train==1) key_up_train=1;
	/*-----------------------------------------------------*/
//	if(reset&&(FDC2214_reset==KEY_PRESSED) )			//训练手势计数按键
//	{
//		delay_ms(10);
//		reset=0;
//		Init_flag=1;
//	}
//	else if(FDC2214_reset==1) reset=1;
}
//选择排序
void Sort_chooes(float *arr)
{
	int i,j;
	float temp;
	
	for(i=0;i<199;i++)
	{
		for(j=i+1;j<200;j++)
		{
			if(arr[i]>arr[j])
			{
				temp=arr[i];
				arr[i]=arr[j];
				arr[j]=temp;
			}
		}
	}
	
}
