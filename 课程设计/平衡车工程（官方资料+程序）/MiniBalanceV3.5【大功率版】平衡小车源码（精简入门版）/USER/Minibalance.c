#include "sys.h"
  /**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/
int Encoder_Left,Encoder_Right;             //���ұ��������������
int Moto1,Moto2;                            //���PWM���� Ӧ��Motor�� ��Moto�¾�	
float Angle_Balance,Gyro_Balance;           //ƽ����� ƽ�������� ת��������
int main(void)
{ 
	Stm32_Clock_Init(9);            //=====ϵͳʱ������
	delay_init(72);                 //=====��ʱ��ʼ��
//	JTAG_Set(JTAG_SWD_DISABLE);     //=====�ر�JTAG�ӿ�
//	JTAG_Set(SWD_ENABLE); 	//=====��SWD�ӿ� �������������SWD�ӿڵ���
	JTAG_Set(JTAG_SWD_ENABLE);
	LED_Init();                     //=====��ʼ���� LED ���ӵ�Ӳ���ӿ�
	OLED_Init();                    //=====OLED��ʼ��
	uart_init(72,128000);           //=====��ʼ������1
  MiniBalance_PWM_Init(7199,0);   //=====��ʼ��PWM 10KHZ������������� �����ʼ������ӿ� ��ΪMiniBalance_PWM_Init(9999,35) 200HZ
	Encoder_Init_TIM2();            //=====�������ӿ�
	Encoder_Init_TIM4();            //=====��ʼ��������2 
	IIC_Init();                     //=====ģ��IIC��ʼ��
  MPU6050_initialize();           //=====MPU6050��ʼ��	
  DMP_Init();                     //=====��ʼ��DMP     
	EXTI_Init();                    //=====MPU6050 5ms��ʱ�жϳ�ʼ��
	while(1)
		{     
					oled_show();            //===��ʾ����
				  printf("ƽ�� ���  %f \r\n���ֱ�����%d \r\n���ֱ�����%d \r\n",Angle_Balance,Encoder_Left,Encoder_Right);//�򴮿ڵ������ַ�������
		} 
}
