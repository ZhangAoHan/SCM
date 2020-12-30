#include "sys.h"
#include "usart.h"		
#include "delay.h"	 
#include "lcd.h"
#include "touch.h"  
#include "w25q128.h"  
#include "text.h"	
#include "motor_control.h"
#include "motor.h"
#include "led.h"
#include "timer.h"
#include "usart2.h"
#include "AS608.h" 
#include "malloc.h"	  
#include "as608_control.h"
#include "display.h"

#define usart2_baund  57600//����2�����ʣ�����ָ��ģ�鲨���ʸ���



u8 use_start=0;   //����������׼��
u8 dl_success=0;   //��ʼ����ͣ�������ı�־��
u8 set=0;     //��������while��1���ı�׼��
u16 now_people_id=300;           //Ԥ��ֵ����299  ����û��id
u16 now_people_mark=0;         //ƥ��÷�   �����û�ˢָ�Ƴɹ���ĵ�¼����
u8 page=0;
u8 gly_page=0;
u16 car_id[4]={300,300,300,300};      //ʹ��ͣ��λ���û�ID
u16 t1=0,t2=0,t3=0,t4=0;     //��ʱ
u8 use1=0,use2=0,use3=0,use4=0;   
u8 people_car=0;    //�û�ѡ����ͣ��λ��  ���ڴ���ѡ���¥����Ϣ  Ϊ����һ���ĵ������
int main(void)
{				 

	Stm32_Clock_Init(9);	//ϵͳʱ������
	delay_init(72);	  		//��ʱ��ʼ��
	uart_init(72,115200); 	//���ڳ�ʼ��Ϊ115200
	usart2_init(36,usart2_baund);		//��ʼ������2 
	LCD_Init();
	W25QXX_Init();				//��ʼ��W25Q128 ��SPI2
	tp_dev.init();			//��������ʼ�� 
	my_mem_init(SRAMIN);		//��ʼ���ڲ��ڴ��
//	exfuns_init();				//Ϊfatfs��ر��������ڴ�  
// 	f_mount(fs[1],"1:",1); 		//����FLASH.
	while(font_init()) 			//����ֿ�
	{;}  
	Key_init();
	PWM_Init(999,71);   //pwm��ֵ=7200��Ƶ��=10K
	DJ_PWM_Init(200,7199);       //���ƶ��
	TIM3_Int_Init(9999,7199);	
	while(motor_rest())    //���ݸ�λ
	{
		Show_Str(30,140,120,24,"���ݸ�λ��",24,0);
	}
	as608_use_init();
	LCD_Clear(WHITE);
	delay_ms(100);

  	while(1)
	{
		if(page==0)
		{
			page_0();
		}
		else if(page==1)   //����Ա����
		{
			if(gly_page==0)
			{
				gly_page_0();
			}
			else if(gly_page==1)
			{
				gly_page_1();
			}
			else if(gly_page==2)
			{
				gly_page_2();
			}
			else if(gly_page==3)
			{
				gly_page_3();
			}
		}
		else if(page==2)
		{
			save_car_display();
		}
		else if(page==3)
		{
			qu_car_display();
		}
	}	 
} 

//		cl_display(1,1);
//		delay_ms(50);
//		LCD_Clear(WHITE); 
//		Show_Str_Mid(0,150,"�����ͣ2¥",24,240);
//		delay_ms(3000);
//		cl_display(2,1);
//		delay_ms(50);
//		LCD_Clear(WHITE); 
//		delay_ms(50);
//		Show_Str_Mid(0,150,"�������",24,240);




