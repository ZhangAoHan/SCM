#include "sys.h" 
#include "iic.h"
#include "timer.h"

int main(void)
{		
	Stm32_Clock_Init(9);	//ϵͳʱ������
	delay_init(72);	  		//��ʱ��ʼ��
	uart_init(72,9600); 	//���ڳ�ʼ��Ϊ9600


//	IIC_Init();                  //6050_iic��ʼ��	
//	DMP_Init();                  //6050_DMP��ʼ��
//	MPU6050_initialize();        //6050_��ʼ��
//	iIC_Init(); 
	
	Timer_init(899,0);   //����Ƶ��pwmƵ��Ϊ72M/900=80K hz  ��pwm��������Ϊ900����ʱ��3�ڲ�����ȽϼĴ���װ��ֵ��900�Ƚ�
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







