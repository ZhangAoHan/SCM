#include "sys.h"


int main(void)
{ 
Stm32_Clock_Init(9);  //ϵͳʱ������
delay_init(72); //��ʱ��ʼ��
uart_init(72,9600);
IIC_Init();                     //ģ��IIC��ʼ��
MPU6050_initialize();           //=====MPU6050��ʼ��	
DMP_Init();                     //��ʼ��DMP 
while(1)
	{
		 Read_DMP();
	} 
}
























