#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 		 	 
#include "lcd.h" 
#include "key.h" 
#include "rs485.h" 
#include "usmart.h" 
//ALIENTEKս��STM32������ ʵ��25
//RS485 ʵ�� 
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾  

int main(void)
{	
	u8 key;
	u8 i=0,t=0;
	u8 cnt=0;
	u8 rs485buf[5]; 
 	Stm32_Clock_Init(9);	//ϵͳʱ������
	uart_init(72,115200);	//���ڳ�ʼ��Ϊ115200
	delay_init(72);	   	 	//��ʱ��ʼ�� 
	usmart_dev.init(72);	//��ʼ��USMART		
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
	LCD_Init();			   	//��ʼ��LCD 	
	KEY_Init();				//������ʼ��		 	 
	RS485_Init(36,9600);	//��ʼ��RS485
 	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(30,50,200,16,16,"WarShip STM32");
	LCD_ShowString(30,70,200,16,16,"RS485 TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2015/1/15");	
	LCD_ShowString(30,130,200,16,16,"KEY0:Send");	//��ʾ��ʾ��Ϣ		
 
 	POINT_COLOR=BLUE;//��������Ϊ��ɫ	  
	LCD_ShowString(30,150,200,16,16,"Count:");			//��ʾ��ǰ����ֵ	
	LCD_ShowString(30,170,200,16,16,"Send Data:");		//��ʾ���͵�����	
	LCD_ShowString(30,210,200,16,16,"Receive Data:");	//��ʾ���յ�������		
 									  
	while(1)
	{
		key=KEY_Scan(0);
		if(key==KEY0_PRES)//KEY0����,����һ������
		{
			for(i=0;i<5;i++)
			{
				rs485buf[i]=cnt+i;//��䷢�ͻ�����
				LCD_ShowxNum(30+i*32,190,rs485buf[i],3,16,0X80);	//��ʾ����
 			}
			RS485_Send_Data(rs485buf,5);//����5���ֽ� 									   
		}		 
		RS485_Receive_Data(rs485buf,&key);
		if(key)//���յ�������
		{
			if(key>5)key=5;//�����5������.
 			for(i=0;i<key;i++)LCD_ShowxNum(30+i*32,230,rs485buf[i],3,16,0X80);	//��ʾ����
 		}
		t++; 
		delay_ms(10);
		if(t==20)
		{
			LED0=!LED0;//��ʾϵͳ��������	
			t=0;
			cnt++;
			LCD_ShowxNum(30+48,150,cnt,3,16,0X80);	//��ʾ����
		}		   
	} 
}





















