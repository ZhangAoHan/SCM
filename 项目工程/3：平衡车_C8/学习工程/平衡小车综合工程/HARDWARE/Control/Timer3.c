#include "Timer3.h"
#include "sys.h" //因为设置中断优先级需要调用sys.c中的函数
u8 a=0;
void TIME3_init(void)  //计数频率=10k  每5ms中断一次
{
	RCC->APB1ENR |=1<<1; //使能定时器3
	TIM3->CR1 |=1<<0;  //使能计数器、定时器初始时钟为72M、计数器向上计数
	TIM3->PSC =7199;  //将定时器初始时钟（72M）分频7200，即此时定时器时钟=72M/7200=10000.（每记一个数耗时1/10000s）
	TIM3->ARR =49;  //每记50个数溢出一次（即每5ms产生一次中断）
	TIM3->DIER |=1<<0;  //允许中断更新
	TIM3->DIER |=1<<6;  //使能触发中断
	MY_NVIC_Init(1,2,TIM3_IRQn,2);  //使能定时器3中断线、并设置优先级分组为2组、并设置抢占优先级1、响应优先级1
}

void TIM3_IRQHandler(void)
{
	
	if(TIM3->SR&0x0001)    //SR是一个16位寄存器，每次中断发生，SR的最低位就置1，以此来判断中断是否发生
	{
		a++;
		Read_DMP();
		Angle_Balance=Pitch;             //===更新平衡倾角
		Gyro_Balance=gyro[1];            //===更新平衡角速度
		if(a==2)             //10ms
		{
		left=Read_Encoder(2);
	    right=Read_Encoder(4);
		a=0;
		}
		Motor_Control();
	}
	TIM3->SR&=~(1<<0);//清除中断标志位 
}


