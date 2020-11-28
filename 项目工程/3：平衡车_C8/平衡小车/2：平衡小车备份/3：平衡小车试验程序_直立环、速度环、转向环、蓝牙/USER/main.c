#include "sys.h"
#include "Motor.h" 
#include "Oled.h"	
#include "Timer.h"
#include "Control.h"
#include "Motor.h"   
u8 res;           //�������ձ���
int 	Motor=0x00;
float Angle_Balance,Gyro_Balance,Gyro_Turn;
int left,right;
int Moto1,Moto2; 
int Flag_Left=0,Flag_Right=0;
void OLED_Display(int x,int y);
void BlueTooth(void);
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
	OLED_Display(left,right);
	BlueTooth();
	}
 }

void OLED_Display(int x,int y)
{	
	if(x>0) x=x;
	if(x<0) x=-x;
	if(y>0) y=y;
	if(y<0) y=-y;
	OLED_ShowString(0,0,"L",16);
	OLED_ShowChar(8,0,':',16);
	OLED_ShowNum(16,0,x,14,16);
	
	OLED_ShowString(0,2,"R",16);
	OLED_ShowChar(8,2,':',16);
	OLED_ShowNum(16,2,y,14,16);
}

void BlueTooth()
{
	switch(res)
	{
		case 0x00:Flag_Left=0;Flag_Right=0;Motor=0;Motor_Control();   break;
		case 0x01:Flag_Left=0;Flag_Right=0;Motor=20;Motor_Control();  break;
		case 0x02:Flag_Left=0;Flag_Right=0;Motor=-20;Motor_Control(); break;
		case 0x03:Flag_Left=1;Flag_Right=0;Motor=0;Motor_Control(); break;
		case 0x04:Flag_Left=0;Flag_Right=1;Motor=0;Motor_Control(); break;

		
	}
}
