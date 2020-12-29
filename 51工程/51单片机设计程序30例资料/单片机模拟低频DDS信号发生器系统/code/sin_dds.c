#include "sin_dds.h"

uchar i,j;
uint counter,step;

/**************定时器0初始化**********************************/
void Init_Timer0(void)
{
   TMOD = (TMOD & 0XF0) | 0X01; 	//定时器0，方式1
   TH0 = 0xff;						//定时器初值
   TL0 = 0xff; 
   TR0 =1; 							//启动定时器0
   ET0 =1;							//开定时器0中断
}

/*************************主函数*********************************/
main()
{
   Init_Timer0();				    //定时器0初始化
   step=2;							//数值采样步数初始化
   EA = 1;							//CPU开中断
 	while(1)						
	{
		if(key_up == 0) if(step<4096) step++;	 //数值采样步数加1，采样频率变高 ，正弦波周期变小
		if(key_dw == 0) if(step>1) step--;		 //数值采样步数减1，采样频率变低 ，正弦波周期变大
		while((!key_up)||(!key_dw));			     //若有一个键按下去，则正弦波周期始终保持不变
 	}
}
/******************系统OS定时中断服务***************************/
void OS_Timer0(void) interrupt 1 using 2
{													   
   TH0 = 0xff;									  //重装定时器初值
   TL0 = 0xff; 									  
   counter = counter + step;					  //counter以step的步数递增
   dac1=type[(unsigned int)counter>>8];			  //当counter加满(256/step)次时，dac1的采样值变化一次
}
