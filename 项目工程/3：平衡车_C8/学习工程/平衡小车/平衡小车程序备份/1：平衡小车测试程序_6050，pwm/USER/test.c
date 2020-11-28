#include "sys.h" 
#include "iic.h"
#include "timer.h"

int main(void)
{		
	Stm32_Clock_Init(9);	//系统时钟设置
	delay_init(72);	  		//延时初始化
	uart_init(72,9600); 	//串口初始化为9600


//	IIC_Init();                  //6050_iic初始化	
//	DMP_Init();                  //6050_DMP初始化
//	MPU6050_initialize();        //6050_初始化
//	iIC_Init(); 
	
	Timer_init(899,0);   //不分频，pwm频率为72M/900=80K hz  ，pwm计数总数为900，定时器3内部输出比较寄存器装载值与900比较
    LED_init();		
  	while(1)
	{
//		Read_DMP();
		TIM3_oc1_pwm=200;
		TIM3_oc2_pwm=400;
		TIM3_oc3_pwm=600;
		TIM3_oc4_pwm=800;
	}	 
} 







