#include "sys.h"


int main(void)
{ 
Stm32_Clock_Init(9);  //系统时钟设置
delay_init(72); //延时初始化
uart_init(72,9600);
IIC_Init();                     //模拟IIC初始化
MPU6050_initialize();           //=====MPU6050初始化	
DMP_Init();                     //初始化DMP 
while(1)
	{
		 Read_DMP();
	} 
}
























