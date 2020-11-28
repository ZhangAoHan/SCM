#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 		 	 
#include "lcd.h"  
#include "key.h"     
#include "usmart.h" 
#include "sram.h"
#include "malloc.h"
#include "string.h"
#include "timer.h"
#include "adc.h"
#include "beep.h"
#include "rtc.h"
#include "dm9000.h"
#include "lwip/netif.h"
#include "lwip_comm.h"
#include "lwipopts.h"
#include "udp_demo.h"
#include "tcp_client_demo.h"
#include "tcp_server_demo.h"
#include "httpd.h"
//ALIENTEKս��STM32������ ʵ��50
//����ͨ�� ʵ�� 
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾ 

extern u8 udp_demo_flag;  //UDP ����ȫ��״̬��Ǳ���
//����UI
//mode:
//bit0:0,������;1,����ǰ�벿��UI
//bit1:0,������;1,���غ�벿��UI
void lwip_test_ui(u8 mode)
{
	u8 speed;
	u8 buf[30]; 
	POINT_COLOR=RED;
	if(mode&1<<0)
	{
		LCD_Fill(30,30,lcddev.width,110,WHITE);	//�����ʾ
		LCD_ShowString(30,30,200,16,16,"WarShip STM32");
		LCD_ShowString(30,50,200,16,16,"Ethernet lwIP Test");
		LCD_ShowString(30,70,200,16,16,"ATOM@ALIENTEK");
		LCD_ShowString(30,90,200,16,16,"2015/3/21"); 	
	}
	if(mode&1<<1)
	{
		LCD_Fill(30,110,lcddev.width,lcddev.height,WHITE);	//�����ʾ
		LCD_ShowString(30,110,200,16,16,"lwIP Init Successed");
		if(lwipdev.dhcpstatus==2)sprintf((char*)buf,"DHCP IP:%d.%d.%d.%d",lwipdev.ip[0],lwipdev.ip[1],lwipdev.ip[2],lwipdev.ip[3]);//��ӡ��̬IP��ַ
		else sprintf((char*)buf,"Static IP:%d.%d.%d.%d",lwipdev.ip[0],lwipdev.ip[1],lwipdev.ip[2],lwipdev.ip[3]);//��ӡ��̬IP��ַ
		LCD_ShowString(30,130,210,16,16,buf); 
		speed=DM9000_Get_SpeedAndDuplex();//�õ�����
		if(speed&1<<1)LCD_ShowString(30,150,200,16,16,"Ethernet Speed:10M");
		else LCD_ShowString(30,150,200,16,16,"Ethernet Speed:100M");
		LCD_ShowString(30,170,200,16,16,"KEY0:TCP Server Test");
		LCD_ShowString(30,190,200,16,16,"KEY1:TCP Client Test");
		LCD_ShowString(30,210,200,16,16,"KEY2:UDP Test");
	}
}

int main(void)
{		
	u8 t;
	u8 key;
 	Stm32_Clock_Init(9);		//ϵͳʱ������
	uart_init(72,115200);		//���ڳ�ʼ��Ϊ115200
	delay_init(72);	   	 		//��ʱ��ʼ�� 
 	usmart_dev.init(72);		//��ʼ��USMART		
 	TIM3_Int_Init(1000,719);	//��ʱ��3Ƶ��Ϊ100hz
	LED_Init();		  			//��ʼ����LED���ӵ�Ӳ���ӿ�
	KEY_Init();					//��ʼ������
	LCD_Init();			   		//��ʼ��LCD   
	Adc_Init();					//ADC��ʼ��
	BEEP_Init();				//��������ʼ��
	RTC_Init();					//��ʼ��RTC
	my_mem_init(SRAMIN);		//��ʼ���ڲ��ڴ��
	POINT_COLOR=RED;			//��������Ϊ��ɫ 
	lwip_test_ui(1);			//����ǰ�벿��UI		    
	while(lwip_comm_init()) 	//lwip��ʼ��
	{
		LCD_ShowString(30,110,200,20,16,"LWIP Init Falied!");
		delay_ms(1200);
		LCD_Fill(30,110,230,130,WHITE); //�����ʾ
		LCD_ShowString(30,110,200,16,16,"Retrying...");  
	}
	LCD_ShowString(30,110,200,20,16,"LWIP Init Success!");
 	LCD_ShowString(30,130,200,16,16,"DHCP IP configing...");
	//�ȴ�DHCP��ȡ 
	while((lwipdev.dhcpstatus!=2)&&(lwipdev.dhcpstatus!=0XFF))//�ȴ�DHCP��ȡ�ɹ�/��ʱ���
	{
		lwip_periodic_handle();	//LWIP�ں���Ҫ��ʱ����ĺ���
		lwip_pkt_handle();
	} 
	lwip_test_ui(2);			//���غ�벿��UI 
	httpd_init();  				//Web Serverģʽ
  	while(1)
	{	
		key=KEY_Scan(0);
		switch(key)
		{
			case KEY0_PRES:		//TCP Serverģʽ
				tcp_server_test();
				lwip_test_ui(3);//���¼���UI
				break;
			case KEY1_PRES:		//TCP Clientģʽ
				tcp_client_test();
				lwip_test_ui(3);//���¼���UI
				break; 
			case KEY2_PRES:		//UDPģʽ
				udp_demo_test();
				lwip_test_ui(3);//���¼���UI
				break; 
		}
		lwip_periodic_handle();
		lwip_pkt_handle();
		delay_ms(2);
		t++;
		if(t==100)LCD_ShowString(30,230,200,16,16,"Please choose a mode!");
		if(t==200)
		{ 
			t=0;
			LCD_Fill(30,230,230,230+16,WHITE);//�����ʾ
			LED0=!LED0;
		} 
	}
}




