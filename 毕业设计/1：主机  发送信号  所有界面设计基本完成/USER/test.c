#include "sys.h"
#include "usart.h"		
#include "delay.h"	 
#include "lcd.h"
#include "touch.h"  
#include "w25q128.h"  
#include "text.h"	
#include "usart2.h"
#include "AS608.h" 
#include "malloc.h"	  
#include "date_control.h"
#include "control.h"
#include "timer.h"
#include "led.h"
#include "motor.h"
#include "motor_control.h"

#define usart2_baund  57600//����2�����ʣ�����ָ��ģ�鲨���ʸ���
u8 tmp_buf[33]; 
u8 page=0;
char *str1;
u16 t1,t2,t3,t4; 
u8 use1=0,use2=0,use3=0,use4=0; 
u8 use_start=0;
u8 ste;
u8 use_error=0;   //�û����� ������Ϣ��ʾʱ�����
//u8 car[4]={0,0,0,0,};      //��4��ͣ��λ�ɹ�ѡ��
u16 car_id[4]={0,0,0,0};      //ʹ��ͣ��λ���û�ID
u8 dl_success=0;   //��ʼ����ͣ�������ı�־��
u8 people_car=0; 
u16 people_id;
u16 gly_id=0;
u8 gly_page=0;
u8 dessce=0; 
int main(void)
{				 

	Stm32_Clock_Init(9);	//ϵͳʱ������
	delay_init(72);	  		//��ʱ��ʼ��
	uart_init(72,115200); 	//���ڳ�ʼ��Ϊ115200
	LCD_Init();
	W25QXX_Init();				//��ʼ��W25Q128 ��SPI2
	tp_dev.init();			//��������ʼ�� 
	usart2_init(36,usart2_baund);		//��ʼ������2 
	LED_Init();
	Key_init();
	PWM_Init(999,71);   //pwm��ֵ=7200��Ƶ��=10K
	DJ_PWM_Init(200,7199);       //���ƶ��
	TIM3_Int_Init(9999,7199);
	while(font_init()) 			//����ֿ�
	{;}  
	//	
	  
		while(PS_HandShake(&AS608Addr))//��AS608ģ������
	{
		delay_ms(400);
		LCD_Fill(0,40,240,80,WHITE);
		Show_Str_Mid(0,40,"δ��⵽ģ��!!!",16,240);
		delay_ms(800);
		LCD_Fill(0,40,240,80,WHITE);
		Show_Str_Mid(0,40,"��������ģ��...",16,240);		  
	}
	LCD_Clear(WHITE);
	AS_Init();
	gly_id_save();
	while(motor_rest())    //���ݸ�λ
	{
		Show_Str(30,140,120,24,"���ݸ�λ��",24,0);
	}
	LCD_Clear(WHITE);
	delay_ms(100);

  	while(1)
	{
//		use_control();
		motor_up();
	}	 
} 








