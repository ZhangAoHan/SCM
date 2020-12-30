#include "display.h"
#include "lcd.h"
#include "touch.h"  
#include "delay.h"	
#include "text.h"	
#include "as608.h"
#include "as608_control.h"
#include "motor_control.h"

//��ҪΪ �ǹ���Ա�����Լ��ǲ����������������ʾ����
extern u16 car_id[4];      //ʹ��ͣ��λ���û�ID
extern u16 t1,t2,t3,t4;     //��ʱ
extern u8 use1,use2,use3,use4;   
extern u8 people_car;   //�û�ѡ����ͣ��λ��  ���ڴ���ѡ���¥����Ϣ  Ϊ����һ���ĵ������
extern u8 set;     //�Զ�¼�����Աָ�Ʊ�׼��
extern u16 now_people_id;
extern u16 now_people_mark;  
extern u8 page;
 extern u8 dl_success;   //���ڽ���ͣ�������ı�׼��  1���ڽ���  0�������  Ϊ����ʾ ����ͣ������������ʾ����ȡ������
 
 /*
	�泵��ʾ�����麯��                   ���ֱ�ӵ���save_car_display����
 */
void save_car_display(void)  //�泵��ʾ����    �û�ˢָ�� ����֮ǰû��ˢ��  page=2
{	
	
	POINT_COLOR=BLACK;
	Show_Str(10,0,120,24,"ʹ����ID��",24,0);
	Show_Str(10,30,120,24,"���ε÷֣�",24,0);
	LCD_ShowNum(130,4,now_people_id,3,16);  
	LCD_ShowNum(130,34,now_people_mark,3,16);  
	car_settle();                //ͣ��λ��ʾ��ѡ�����
	set=1;
	while(set)
	{
		use1_touch();
		if(dl_success)         //ѡ����ͣ��λ  �����û��ѡ�� ��һֱ�ڸ�ҳ����ʾ ���ߵ㷵�أ�
		{
			if(people_car==1||people_car==2)   //һ¥
			{
				cl_display(1,1);
			}
			else if(people_car==3||people_car==4)   //��¥
			{
				cl_display(2,1);
			}
			//�泵�����Լ����  ������ҳ��  �������ֱ�׼������
				now_people_id=300;
				now_people_mark=0;
				people_car=0;
				dl_success=0;
				LCD_Clear(WHITE);    //������� ������ҳ��
				delay_ms(100);
				page=0;
				set=0;
		}
	}

		
}



void car_settle(void)   //ͣ��λѡ����  �Դ�����ɨ��
{
		LCD_DrawRectangle(10,60,110,160);
	LCD_DrawRectangle(9,59,111,161);
		LCD_DrawRectangle(130,60,230,160);
	LCD_DrawRectangle(129,59,231,161);
		LCD_DrawRectangle(10,180,110,280);
	LCD_DrawRectangle(9,179,111,281);
		LCD_DrawRectangle(130,180,230,280);
	LCD_DrawRectangle(129,179,231,281);
		if(car_id[0]==300)
	{
		LCD_Fill(15,65,105,105,GREEN);
		POINT_COLOR=BLACK;
		Show_Str_Mid(15,72,"��λ����",16,90);
	}
	else
	{
		LCD_Fill(15,65,105,105,BLUE);
		POINT_COLOR=BLACK;
		Show_Str_Mid(15,72,"��λ��ռ",16,90);
	}
		if(car_id[1]==300)
	{
		LCD_Fill(135,65,225,105,GREEN);
		POINT_COLOR=BLACK;
		Show_Str_Mid(135,72,"��λ����",16,90);
	}
	else
	{
		LCD_Fill(135,65,225,105,BLUE);
		POINT_COLOR=BLACK;
		Show_Str_Mid(135,72,"��λ��ռ",16,90);
	}
		if(car_id[2]==300)
	{
		LCD_Fill(15,185,105,225,GREEN);
		POINT_COLOR=BLACK;
		Show_Str_Mid(15,192,"��λ����",16,90);
	}
	else
	{
		LCD_Fill(15,185,105,225,BLUE);
		POINT_COLOR=BLACK;
		Show_Str_Mid(15,192,"��λ��ռ",16,90);
	}
		if(car_id[3]==300)
	{
		LCD_Fill(135,185,225,225,GREEN);
		POINT_COLOR=BLACK;
		Show_Str_Mid(135,192,"��λ����",16,90);
	}
	else
	{
		LCD_Fill(135,185,225,225,BLUE);
		POINT_COLOR=BLACK;
		Show_Str_Mid(135,192,"��λ��ռ",16,90);
	}
	Show_Str(100,290,48,24,"����",24,0);
}

void use1_touch(void)  //ѡ��ͣ��λ�ĸ�����������
{
	tp_dev.scan(0); 
	if(tp_dev.sta&TP_PRES_DOWN)			//������������
	{
		if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
		{
			if(tp_dev.x[0]>15&&tp_dev.x[0]<105&&tp_dev.y[0]>60&&tp_dev.y[0]<100&&car_id[0]==300)
			{
				car_id[0]=now_people_id;
				use1=1;      //������ʱ
				people_car=1;
				dl_success=1;
				LCD_Clear(WHITE); 
				delay_ms(100);
			}
			else if(tp_dev.x[0]>135&&tp_dev.x[0]<225&&tp_dev.y[0]>60&&tp_dev.y[0]<100&&car_id[1]==300)
			{
				car_id[1]=now_people_id;
				use2=1;
				people_car=2;
				dl_success=1;
				LCD_Clear(WHITE); 
				delay_ms(100);
			}
			else if(tp_dev.x[0]>15&&tp_dev.x[0]<105&&tp_dev.y[0]>185&&tp_dev.y[0]<225&&car_id[2]==300)
			{
				car_id[2]=now_people_id;
				use3=1;
				people_car=3;
				dl_success=1;
				LCD_Clear(WHITE); 
				delay_ms(100);
			}
			else if(tp_dev.x[0]>135&&tp_dev.x[0]<225&&tp_dev.y[0]>185&&tp_dev.y[0]<225&&car_id[3]==300)
			{
				car_id[3]=now_people_id;
				use4=1;
				people_car=4;
				dl_success=1;
				LCD_Clear(WHITE); 
				delay_ms(100);
			}
			else if(tp_dev.x[0]>100&&tp_dev.x[0]<150&&tp_dev.y[0]>290&&tp_dev.y[0]<320)
			{
					LCD_Clear(WHITE);    //�����ж� ������ҳ��  �ò�����ɺ���Ҫ������ε�¼��ID��Ϣ���÷���Ϣ
					now_people_id=300;
					now_people_mark=0;
					people_car=0;
					dl_success=0;
					delay_ms(100);
					page=0;
					set=0;
			}
		}
	}
}

/*
	ȡ�����߲鿴��Ϣ�麯��
*/

void qu_car_display(void)   //�û�ȡ�����߲鿴��Ϣ  page=3
{

	POINT_COLOR=BLACK;
	Show_Str(10,0,120,24,"ʹ����ID��",24,0);
	Show_Str(10,30,120,24,"���ε÷֣�",24,0);
	LCD_ShowNum(130,4,now_people_id,3,16);  
	LCD_ShowNum(130,34,now_people_mark,3,16); 
	Show_Str(0,80,120,24,"ʹ�ó�λ��",24,0); 
	Show_Str(0,120,120,24,"ʹ��ʱ�䣺",24,0); 
	LCD_ShowChar(155,124,'H',16,0);         //��ʾʹ��ʱ��
	LCD_ShowChar(190,124,'M',16,0);
	LCD_ShowChar(225,124,'S',16,0);
	POINT_COLOR=RED;
	Show_Str_Mid(0,150,"ֹͣʹ�ñ�ͣ��λ",24,240);	
	Show_Str_Mid(0,290,"����",24,240);	
	POINT_COLOR=BLACK;
			    //��ʾ��Ϣ
		set=1;
	while(set)
	{
		
		if(now_people_id==car_id[0]) 
		{ 
			people_car=1;   //�ṩȡ��¥��
			Show_Str(120,80,96,24,"ͣ��λ1",24,0); 
			LCD_ShowNum(135,124,(t1/60)/24,2,16); 
			LCD_ShowNum(170,124,(t1/60)%24,2,16); 
			LCD_ShowNum(205,124,t1%60,2,16);
		} 
		if(now_people_id==car_id[1]) 
		{
			people_car=2;
			use2=0;
			Show_Str(120,80,96,24,"ͣ��λ2",24,0); 
			LCD_ShowNum(135,124,(t2/60)/24,2,16); 
			LCD_ShowNum(170,124,(t2/60)%24,2,16); 
			LCD_ShowNum(205,124,t2%60,2,16);
		}
		if(now_people_id==car_id[2])
		{
			people_car=3;
			use3=0;
			Show_Str(120,80,96,24,"ͣ��λ3",24,0); 
			LCD_ShowNum(135,124,(t3/60)/24,2,16); 
			LCD_ShowNum(170,124,(t3/60)%24,2,16); 
			LCD_ShowNum(205,124,t3%60,2,16);
		}	
		if(now_people_id==car_id[3])
		{
			people_car=4;
			use4=0;
			Show_Str(120,80,96,24,"ͣ��λ4",24,0); 
			LCD_ShowNum(135,124,(t4/60)/24,2,16); 
			LCD_ShowNum(170,124,(t4/60)%24,2,16); 
			LCD_ShowNum(205,124,t4%60,2,16);
		}
		use_qc_scan();               //���ⰴ��ɨ�躯��
		if(dl_success)
		{
			if(people_car==1||people_car==2)   //һ¥
			{
				cl_display(1,2);
			}
			else if(people_car==3||people_car==4)   //��¥
			{
				cl_display(2,2);
			}
			//�泵�����Լ����  ������ҳ��  �������ֱ�׼������
			now_people_id=300;
			now_people_mark=0;
			people_car=0;
			dl_success=0;
			LCD_Clear(WHITE);    //������� ������ҳ��
			delay_ms(100);
			page=0;	
			set=0;
		}
		
			
	}
		
		
}

void use_qc_scan(void)
{
		tp_dev.scan(0); 
	if(tp_dev.sta&TP_PRES_DOWN)			//������������
	{
		if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
		{
			if(tp_dev.x[0]>0&&tp_dev.x[0]<240&&tp_dev.y[0]>150&&tp_dev.y[0]<175)   //ȡ��
			{
					dl_success=1;
				if(now_people_id==car_id[0]) car_id[0]=300,use1=0,t1=0;   //ֹͣ��ʱ
				if(now_people_id==car_id[1]) car_id[1]=300,use2=0,t2=0;   //ֹͣ��ʱ
				if(now_people_id==car_id[2]) car_id[2]=300,use3=0,t3=0;   //ֹͣ��ʱ
				if(now_people_id==car_id[3]) car_id[3]=300,use4=0,t4=0;   //ֹͣ��ʱ
					LCD_Clear(WHITE); 
					delay_ms(100);
					
			}
			if(tp_dev.x[0]>0&&tp_dev.x[0]<240&&tp_dev.y[0]>290&&tp_dev.y[0]<320)   //�鿴��Ϣ  ����
			{
					now_people_id=300;
					now_people_mark=0;
					people_car=0;
					dl_success=0;
					LCD_Clear(WHITE); 
					delay_ms(100);
					page=0;
					set=0;
			}
		}
	}
}


















