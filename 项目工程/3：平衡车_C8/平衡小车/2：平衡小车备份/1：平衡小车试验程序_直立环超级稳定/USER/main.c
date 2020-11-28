#include "sys.h"
#include "Motor.h" 
#include "Oled.h"	
#include "Timer.h"
#include "Control.h"

u8 res;           //�������ձ���
float Angle_Balance,Gyro_Balance;
int left,right;
int Moto1,Moto2; 
void OLED_Display(float x,float y);
 int main(void)
 {	
	/* ϵͳ������ʼ�� */
	Stm32_Clock_Init(9);	//ϵͳʱ������
	delay_init(72);	  		//��ʱ��ʼ��
	uart_init(72,9600); 	//���ڳ�ʼ��Ϊ9600
	 
    /* ������ƺ�����ʼ�� */	 
	PWM_Init(7199,0);   //pwm��ֵ=7200��Ƶ��=10K
	Motor_Init();  
	Encoder_Init_TIM4();
	Encoder_Init_TIM2();
	 
	/* Oled��ʾ��ʼ������ */
	OLED_Init();
	OLED_Clear();
	 
	 /* MPU6050��ʼ������ */
	IIC_Init();
	MPU6050_initialize();
	DMP_Init();
	 
	 /* ���ƺ�����ʼ�� */
	 TIME3_init();
	 
	 
	while(1)
	{
		Motor_Control();
	}
 }

void OLED_Display(float x,float y)
{	
	OLED_ShowString(0,0,"L",16);
	OLED_ShowChar(8,0,':',16);
	OLED_ShowNum(16,0,x,14,16);
	
	OLED_ShowString(0,2,"R",16);
	OLED_ShowChar(8,2,':',16);
	OLED_ShowNum(16,2,y,14,16);
	
	

}


