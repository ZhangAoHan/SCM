#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"   
#include "lcd.h"  
#include "key.h"  
#include "24cxx.h"  
#include "touch.h"  
#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h" 
//ALIENTEK Mini STM32�����巶������33
//����USB���ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾  
 
//װ�ػ�ͼ����						
void Load_Draw_Dialog(void)
{
	LCD_Clear(WHITE);//����   
 	POINT_COLOR=BLUE;//��������Ϊ��ɫ 
	LCD_ShowString(lcddev.width-24,0,200,16,16,"RST");//��ʾ��������
  	POINT_COLOR=RED;//���û�����ɫ 
}	  
//����x1,x2�ľ���ֵ
u32 usb_abs(u32 x1,u32 x2)
{
	if(x1>x2)return x1-x2;
	else return x2-x1;
} 	  
int main(void)
{		
	u8 key;
	u8 i=0;
 	s8 x0;		 	//���͵����Զ˵�����ֵ
	s8 y0;
	u8 keysta;		//[0]:0,����ɿ�;1,�������;
					//[1]:0,�Ҽ��ɿ�;1,�Ҽ�����
					//[2]:0,�м��ɿ�;1,�м�����
	u8 tpsta=0;		//0,��������һ�ΰ���;1,����������	   
	short xlast; 	//���һ�ΰ��µ�����ֵ
	short ylast;			   
   	Stm32_Clock_Init(9);//ϵͳʱ������
	delay_init(72);		//��ʱ��ʼ��
	uart_init(72,9600); //����1��ʼ��  	  
	LCD_Init();			//��ʼ��Һ�� 
	LED_Init();         //LED��ʼ��	 
	KEY_Init();			//������ʼ��	  													    
	TP_Init();			//��ʼ��������  
	POINT_COLOR=RED;      						    	   
	LCD_ShowString(60,50,200,16,16,"Mini STM32");	
	LCD_ShowString(60,70,200,16,16,"USB Mouse TEST");	
	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,200,16,16,"2014/3/15");	
	LCD_ShowString(60,130,200,16,16,"KEY_UP:SCROLL +");		 
	LCD_ShowString(60,150,200,16,16,"KEY1:RIGHT BTN");	
	LCD_ShowString(60,170,200,16,16,"KEY0:LEFT BTN");	
  	delay_ms(1800);
 	USB_Port_Set(0); 	//USB�ȶϿ�
	delay_ms(300);
   	USB_Port_Set(1);	//USB�ٴ�����
	//USB����
 	USB_Interrupts_Config();    
 	Set_USBClock();   
 	USB_Init();	        
	Load_Draw_Dialog();    
 	while(1)
	{	  
		key=KEY_Scan(1);//֧������
		if(key)
		{								    	 
			if(key==3)Joystick_Send(0,0,0,1); 		//���͹������ݵ�����    
			else 
			{
				if(key==1)keysta|=0X01;		 		//����������    
				if(key==2)keysta|=0X02;		   		//��������Ҽ�
				Joystick_Send(keysta,0,0,0);		//���͸�����
			}			    	 
		}else if(keysta)//֮ǰ�а���
		{
			keysta=0;
			Joystick_Send(0,0,0,0); //�����ɿ����������
		} 
		tp_dev.scan(0); 		 
		if(tp_dev.sta&TP_PRES_DOWN)	//������������
		{
			//�����ƶ�5����λ,���㻬��
  			if(((usb_abs(tp_dev.x[0],xlast)>4)||(usb_abs(tp_dev.y[0],ylast)>4))&&tpsta==0)//�ȴ�����
			{
				xlast=tp_dev.x[0];		//��¼�հ��µ����� 
				ylast=tp_dev.y[0];
	 			tpsta=1;
			}
 			if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
			{	
				if(tp_dev.x[0]>(lcddev.width-24)&&tp_dev.y[0]<16)Load_Draw_Dialog();//���
				else TP_Draw_Big_Point(tp_dev.x[0],tp_dev.y[0],RED);		//��ͼ	  
				if(bDeviceState==CONFIGURED)
				{   
					if(tpsta)//����
					{
						x0=(xlast-tp_dev.x[0])*3;	//�ϴ�����ֵ��õ�������ֵ֮��,����2��
						y0=(ylast-tp_dev.y[0])*3;
						xlast=tp_dev.x[0];			//��¼�հ��µ����� 
						ylast=tp_dev.y[0];
						Joystick_Send(keysta,-x0,-y0,0); //�������ݵ�����  
						delay_ms(5);	   
					}       
				}				   
			}
		}else 
		{	
			tpsta=0;	//��� 
 			delay_ms(1);
		}
		if(bDeviceState==CONFIGURED)LED1=0;//��USB���óɹ��ˣ�LED1����������
		else LED1=1;    
		i++;
		if(i==200)
		{
			i=0;
			LED0=!LED0;
		}
	}	   										    			    
}


