#include "control.h"
#include "date_control.h"
#include "text.h"	
#include "lcd.h"
#include "touch.h"  
#include "delay.h"	 
#include "date_control.h"
#include "24l01.h"
#include "motor_control.h"
#include "led.h"
#include "motor.h"

extern u16 ValidN;//ģ������Чָ�Ƹ���
 const  u8* kbd_menu1[15]={"ɾָ��"," : ","¼ָ��","1","2","3","4","5","6","7","8","9","DEL","0","Enter",};//������
 const  u8* kbd_delFR1[15]={"����"," : ","���ָ��","1","2","3","4","5","6","7","8","9","DEL","0","Enter",};//������
extern u8 tmp_buf[33]; 
extern u8 page;
extern char *str1;
extern u8 ste;  
extern u8 use_start;   //����������׼��
 extern u8 dl_success;   //���ڽ���ͣ�������ı�׼��
 extern u8 people_car;
 extern u8 people_id;
 extern u16 car_id[4];      //ʹ��ͣ��λ���û�ID
 extern u8 use_error; 
 extern u8 use1,use2,use3,use4; 
 
void use_control(void)   //����ҳ�����ն����Ȼع���ҳ�棬�ٴ���ҳ���������ҳ��  
{
	if(page==0)        //��ʾ��ҳ��  ��¼����  һֱɨ��ָ��ģ�飬���Ƿ����˵�¼�����ҵó��û��Ƿ���ȡ��
	{
		DL_Display();
		use_as608_scan();		
	}
	else if(page==1)   //���泵
	{
		save_car_display();
	}
	else if(page==2)   //��ȡ�����߲鿴��Ϣ
	{
		qu_car_display();
	}
	else if(page==3)   //����Ա��¼����
	{
//		LCD_Clear(WHITE); 
//		delay_ms(100);
		
		Show_Str_Mid(0,10,"����Ա��¼�ɹ�",24,240);
		Show_Str_Mid(100,290,"����",24,240);
		LCD_ShowNum(10,50,car_id[0],1,24);
		LCD_ShowNum(10,80,car_id[1],1,24);
		LCD_ShowNum(10,110,car_id[2],1,24);
		LCD_ShowNum(10,140,car_id[3],1,24);
		gly_scan();	
//		use_error=1;
//		LCD_Clear(WHITE); 
//		delay_ms(100);	
//		Show_Str_Mid(0,150,"����Ա��¼�ɹ�",24,240);
//		while(use_error)
//		{;}
//		LCD_Clear(WHITE); 
//		delay_ms(100);
//		page=0;
	}
	
//	display_main();
//	use_touch();
//	use_motor_control(ste);
//	LCD_ShowNum(10,20,ste,1,24);
//	LCD_ShowNum(50,20,use_start,1,24);
//	if(page==0)
//	{
//		display_main();
//		use_touch();
//	}
//	else if(page==1)
//	{
//		if(set==1)
//		{
//			AS_Control(0);
//		}
//		else if(set==2)
//		{
//			
//			AS_Control(1);
//		}
//		else
//		{
//			page=0;
//			delay_ms(100);
//			LCD_Clear(WHITE);  
//		}
//	}

}

void qu_car_display(void)   //�û�ȡ�����߲鿴��Ϣ
{ 
		Show_Str(15,30,40,24,"ID��",16,1);    
		LCD_ShowNum(45,30,people_id,3,16);      //��ʾID
		if(people_id==car_id[0]) Show_Str_Mid(0,80,"ͣ��λ1",24,240);
		if(people_id==car_id[1]) Show_Str_Mid(0,80,"ͣ��λ2",24,240);
		if(people_id==car_id[2]) Show_Str_Mid(0,80,"ͣ��λ3",24,240);
		if(people_id==car_id[3]) Show_Str_Mid(0,80,"ͣ��λ4",24,240);
		Show_Str_Mid(0,150,"ֹͣʹ�ñ�ͣ��λ",24,240);	
		Show_Str_Mid(0,180,"����",24,240);	
		use_xx_scan();
		if(dl_success==1)
		{
			LCD_Clear(WHITE); 
			delay_ms(100);
			Show_Str_Mid(0,150,"�û����ڽ���",24,240);
			Show_Str_Mid(0,180,"ȡ������",24,240);	
			while(dl_success)
			{
				if(people_id==car_id[0]||people_id==car_id[1])
				{
					use_motor_control(1);
				}
				else if(people_id==car_id[2]||people_id==car_id[3])
				{
					use_motor_control(2);
				}
			}	
			//ȡ����ɺ�������й��ڸ�ͣ��λ����Ϣ   car_id   use
			if(people_id==car_id[0]) 
			{
				car_id[0]=0;
				use1=0;
				people_car=0;
				page=0;
				LCD_Clear(WHITE);    //������� ������ҳ��
				delay_ms(200);
				
			}
			else if(people_id==car_id[1]) 
			{
				car_id[1]=0;
				use2=0;
				people_car=0;
				page=0;
				LCD_Clear(WHITE);    //������� ������ҳ��
				delay_ms(200);
			
			}
			else if(people_id==car_id[2]) 
			{
				car_id[2]=0;
				use3=0;
				people_car=0;
				page=0;
							LCD_Clear(WHITE);    //������� ������ҳ��
			delay_ms(200);
			
			}
			else if(people_id==car_id[3]) 
			{
				car_id[3]=0;
				use4=0;
				people_car=0;
				page=0;
				LCD_Clear(WHITE);    //������� ������ҳ��
				delay_ms(200);
			
			}
		}
}
void save_car_display(void)  //�泵��ʾ����
{
		car_settle();                //ͣ��λ��ʾ����
		use1_touch();            //ѡ��ͣ��λ�İ������   ѡ��ͣ��λ������ͣ������
		if(dl_success==1)
		{
			LCD_Clear(WHITE); 
			use_start=0;
			delay_ms(200);
			Show_Str_Mid(0,150,"�û����ڽ���",24,240);
			Show_Str_Mid(0,180,"ͣ������",24,240);	
			while(dl_success)     //��ʼ����ͣ����������
			{
				if(people_car==1||people_car==2)   //һ¥
				{
					use_motor_control(1);
				}
				else if(people_car==3||people_car==4)   //��¥
				{
					use_motor_control(2);
				}
				
			}
			people_car=0;
			LCD_Clear(WHITE);    //������� ������ҳ��
			delay_ms(100);
			page=0;			
				
		}

}
void use_touch_scan(void)     // use_start=0  ��û��ʼ  use_start=1 ��ʼ  use_start=2  ���� 
{
	if(KEY_TOUCH==1&&use_start==0)
	{
		use_start=1;
	}
	else if(KEY_TOUCH==1&&use_start==1)
	{
		use_start=2;    //������־
	}
}
void use_motor_control(u8 lc)             //ͣ����������ɱ�׼Ϊdl_success=1
{
	if(lc==1)
	{
		if(KEY_DOWN==0&&use_start==1)   //�泵����ȡ��
		{
			PWM=8;    //����
		}
		else if(KEY_DOWN==0&&use_start==2)   //�泵��ɻ���ȡ�����
		{
			PWM=18;   
			use_start=0;
			dl_success=0;
		}
		
	}
	else if(lc==2)
	{
		if(KEY_UP==1&&use_start==1)  //����  ����û��2¥   //��ʱKEY_DOWN=0
		{
			motor_up();
		}
		else if(KEY_UP==0&&use_start==1)  //������  Ҳ����2¥    
		{
			motor_stop();
			PWM=8; 
		}
		else if(KEY_DOWN==1&&use_start==2)    //�ٰ�һ�� ��ʼ�½�  ֱ�����µĴ�����������Ϊֹ
		{
			PWM=18;   
			motor_down();
		}
		else if(KEY_DOWN==0&&use_start==2)   //�������
		{
			motor_stop();
			dl_success=0;
			use_start=0;

		}
		else  //�������  ��Ϊ�Ƿ�����  ֹͣ
		{
			motor_stop();
		}

	}
}
u8 motor_rest(void)           //���ݸ�λ
{
	if(KEY_DOWN==1)
	{
		motor_down();
		return 1;
	}
	else 
	{
		motor_stop();
		PWM=18;  
		return 0;
	}
}
void motor_up(void)
{
		PWMA=500;
		AIN1=1;
		AIN2=0;
}
void motor_down(void)
{
	PWMA=500;
	AIN1=0;
	AIN2=1;
}
void motor_stop(void)
{
	AIN1=0;
	AIN2=0;
}
void DL_Display(void)       //��¼����   page==0
{
	POINT_COLOR=BLUE;
	Show_Str_Mid(0,50,"��е����ϵͳ",16,240);
	POINT_COLOR=BLACK;
	Show_Str(48,100,144,24,"��ˢָ�Ƶ�¼",24,0);
}
void Error_0_display(void)   //�û�û��¼��ָ�ƣ��������   ��ʾ5��
{
	POINT_COLOR=BLUE;
	Show_Str_Mid(0,50,"û������ָ����Ϣ",24,240);
	POINT_COLOR=BLACK;
	Show_Str_Mid(0,100,"����ϵ����Ա¼ָ����Ϣ",16,240);
}
void Success_0_display(void)   //�û��泵�ȴ�����   ��ʾ5��
{
	POINT_COLOR=BLACK;
	Show_Str_Mid(0,50,"���ڽ��д泵����",16,240);
}
void display_main(void)         //�û���ҳ�� �û��泵ȡ�� ���漰�ӿڣ��û��Ѿ���¼��ɣ�Ҫôȡ����Ҫô�泵��
{
	
}

void Nrf_communicate(void)          //��Ҫ��������
{
	
//		if(NRF24L01_TxPacket(tmp_buf)==TX_OK)
//		{
//				if(set==1)
//				{
//					tmp_buf[0]='S';
//					tmp_buf[1]=48+1;
//					tmp_buf[32]=0; 
//				}
//				else if(set==2)
//				{
//					tmp_buf[0]='S';
//					tmp_buf[1]=48+2;
//					tmp_buf[32]=0; 
//				}
//				else if(set==0)				
//				{
//					tmp_buf[0]='N';
//					tmp_buf[32]=0; 
//				}
//		}
	
	
	
	
}



void use_touch(void)
{
	
	tp_dev.scan(0); 
	if(tp_dev.sta&TP_PRES_DOWN)			//������������
	{
		if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
		{
			if(tp_dev.x[0]>0&&tp_dev.x[0]<240&&tp_dev.y[0]>50&&tp_dev.y[0]<80) 
			{
				 ste=1;
			}
			if(tp_dev.x[0]>0&&tp_dev.x[0]<240&&tp_dev.y[0]>150&&tp_dev.y[0]<180) 
			{
				 ste=2;
			}
//			if(page==0)   //��ҳ��
//			{
//				if(tp_dev.x[0]>30&&tp_dev.x[0]<130&&tp_dev.y[0]>100&&tp_dev.y[0]<130)    //�û���¼
//				{
//					set=1;
//					page=1;
//					delay_ms(100);
//					LCD_Clear(WHITE);  
//					
//				}
//				if(tp_dev.x[0]>30&&tp_dev.x[0]<130&&tp_dev.y[0]>140&&tp_dev.y[0]<170)   //����Ա��¼
//				{
//					set=2;
//					page=1;
//					delay_ms(100);
//					LCD_Clear(WHITE);  
//					AS608_load_keyboard(0,170,(u8**)kbd_menu);  // ����Ա��������������
//					Show_Str(0,80,240,16,(u8*)str1,16,0);
//				}
//			}
			
		}
	}
}
















