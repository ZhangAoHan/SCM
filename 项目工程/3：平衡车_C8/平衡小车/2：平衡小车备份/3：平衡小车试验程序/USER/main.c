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
void OLED_Display_Init(void);
void BlueTooth(void);

 int main(void)
 {	
	/* ϵͳ������ʼ�� */
	Stm32_Clock_Init(9);	//ϵͳʱ������
	delay_init(72);	  		//��ʱ��ʼ��
	uart_init(72,9600); 	//���ڳ�ʼ��Ϊ9600
	 
	 /* Oled��ʾ��ʼ������ */
	OLED_Init();
	OLED_Clear();
	OLED_Display_Init();
	 delay_ms(2000);
    /* ������ƺ�����ʼ�� */	 
	PWM_Init(7199,0);   //pwm��ֵ=7200��Ƶ��=10K
	Motor_Init();  
	Encoder_Init_TIM4();
	Encoder_Init_TIM2();
	 
	 /* MPU6050��ʼ������ */
	IIC_Init();
	MPU6050_initialize();
	DMP_Init();
	 
	 /* ���ƺ�����ʼ�� */
	 TIME3_init();
	 
	 OLED_Clear();   //����
	 
	while(1)
	{
	BlueTooth();
	}
 }
void OLED_Display_Init()     //��ʼ����ʾ  Team of flame
{	
   OLED_ShowString(8,2,"Team Of Flame",16);
}
void OLED_Display(int x,int y)     //ֹͣ
{	
	if(x>0) x=x;
	if(x<0) x=-x;
	if(y>0) y=y;
	if(y<0) y=-y;
	OLED_ShowString(0,2,"L",16);
	OLED_ShowChar(8,2,':',16);
	OLED_ShowNum(16,2,x,4,16);
	
	OLED_ShowString(0,4,"R",16);
	OLED_ShowChar(8,4,':',16);
	OLED_ShowNum(16,4,y,4,16);
}
void BlueTooth()
{
	switch(res)
	{
		case 0x00: OLED_ShowString(0,0,"Stop",16);OLED_Display(left,right);Flag_Left=0;Flag_Right=0;Motor=0;  Motor_Control();   break;   //ֹͣ
		case 0x01: OLED_ShowString(0,0,"Fall Back",16);OLED_Display(left,right);Flag_Left=0;Flag_Right=0;Motor=20; Motor_Control();   break;   //����
		case 0x02: OLED_ShowString(0,0,"Go Forward",16);OLED_Display(left,right);Flag_Left=0;Flag_Right=0;Motor=-20;Motor_Control();   break;   //ǰ��
		case 0x03: OLED_ShowString(0,0,"Left",16);OLED_Display(left,right);Flag_Left=1;Flag_Right=0;Motor=0;  Motor_Control();   break;   //��ת
		case 0x04: OLED_ShowString(0,0,"Right",16);OLED_Display(left,right);Flag_Left=0;Flag_Right=1;Motor=0;  Motor_Control();   break;   //��ת

		
	}
}

