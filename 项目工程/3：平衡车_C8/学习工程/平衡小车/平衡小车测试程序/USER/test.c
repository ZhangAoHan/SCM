#include "sys.h" 
//#include "timer.h"
#include "olcd.h"
//#include "motor.h"
	u8 res;
	
void Bluetooth(void);	
int main(void)
{		
//	u16 led0pwmval=0;    
//	u8 dir=1;
//		u8 t;

//	u8 len;	
//	u16 times=0;  
	Stm32_Clock_Init(9);	//ϵͳʱ������
	delay_init(72);	  		//��ʱ��ʼ��
	uart_init(72,9600); 	//���ڳ�ʼ��Ϊ9600


//	IIC_Init();                  //6050_iic��ʼ��	
//	DMP_Init();                  //6050_DMP��ʼ��
//	MPU6050_initialize();        //6050_��ʼ��
//	iIC_Init(); 

//	Timer_init(7199,0);   //����Ƶ��pwmƵ��Ϊ72M/7200=10K hz  ��pwm��������Ϊ7200����ʱ��3�ڲ�����ȽϼĴ���װ��ֵ��900�Ƚ�
//    MOTO_PWM_init();
//	Mortor_init();
	
		OLED_Init();			//��ʼ��OLED  
		OLED_Clear() ; 
  	while(1)
	{
//		Read_DMP();
//		Bluetooth();
//		Motor_PWM(6900,6900) ;      //PWM����Ϊ6900.��ֵԽ��Խ����

		OLED_ShowCHinese(0,0,0);//��
		OLED_ShowCHinese(18,0,1);//��
		OLED_ShowCHinese(36,0,2);//԰
		OLED_ShowCHinese(54,0,3);//��
		OLED_ShowCHinese(72,0,4);//��
		OLED_ShowCHinese(90,0,5);//��
		OLED_ShowCHinese(108,0,6);//��
				delay_ms(8000);
	}	 
} 


void Bluetooth()
{
	switch(res)
	{
		case 0x00:  led=0;   break;
		case 0x01:  led=1;   break;
	}
}






