#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 		 	 
#include "lcd.h" 
#include "key.h" 
#include "can.h" 
#include "usmart.h" 
//ALIENTEKս��STM32������ ʵ��26
//CANͨ�� ʵ�� 
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾  

int main(void)
{	
	u8 key;
	u8 i=0,t=0;
	u8 cnt=0;
	u8 canbuf[8];
	u8 res;
	u8 mode=1;				//CAN����ģʽ;0,��ͨģʽ;1,����ģʽ

 	Stm32_Clock_Init(9);	//ϵͳʱ������
	uart_init(72,115200);	//���ڳ�ʼ��Ϊ115200
	delay_init(72);	   	 	//��ʱ��ʼ�� 
	usmart_dev.init(72);	//��ʼ��USMART		
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
	LCD_Init();			   	//��ʼ��LCD 	
	KEY_Init();				//������ʼ��		 	 
 	CAN_Mode_Init(1,8,9,4,mode);//CAN��ʼ��,������500Kbps    

 	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(30,50,200,16,16,"WarShip STM32");	
	LCD_ShowString(30,70,200,16,16,"CAN TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2015/1/15");
	LCD_ShowString(30,130,200,16,16,"LoopBack Mode");	 
	LCD_ShowString(30,150,200,16,16,"KEY0:Send KEK_UP:Mode");//��ʾ��ʾ��Ϣ		
  	POINT_COLOR=BLUE;//��������Ϊ��ɫ	  
	LCD_ShowString(30,170,200,16,16,"Count:");			//��ʾ��ǰ����ֵ	
	LCD_ShowString(30,190,200,16,16,"Send Data:");		//��ʾ���͵�����	
	LCD_ShowString(30,250,200,16,16,"Receive Data:");	//��ʾ���յ�������		
 	while(1)
	{
		key=KEY_Scan(0);
		if(key==KEY0_PRES)				//KEY0����,����һ������
		{
			for(i=0;i<8;i++)
			{
				canbuf[i]=cnt+i;		//��䷢�ͻ�����
				if(i<4)LCD_ShowxNum(30+i*32,210,canbuf[i],3,16,0X80);	//��ʾ����
				else LCD_ShowxNum(30+(i-4)*32,230,canbuf[i],3,16,0X80);	//��ʾ����
 			}
			res=CAN_Send_Msg(canbuf,8);//����8���ֽ� 
			if(res)LCD_ShowString(30+80,190,200,16,16,"Failed");		//��ʾ����ʧ��
			else LCD_ShowString(30+80,190,200,16,16,"OK    ");	 		//��ʾ���ͳɹ�								   
		}else if(key==WKUP_PRES)		//WK_UP���£��ı�CAN�Ĺ���ģʽ
		{	   
			mode=!mode;
			CAN_Mode_Init(1,8,9,4,mode);//CAN��ͨģʽ��ʼ��,��ͨģʽ,������500Kbps
  			POINT_COLOR=RED;			//��������Ϊ��ɫ 
			if(mode==0)					//��ͨģʽ����Ҫ2��������
			{
				LCD_ShowString(30,130,200,16,16,"Nnormal Mode ");	    
			}else 						//�ػ�ģʽ,һ��������Ϳ��Բ�����.
			{
 				LCD_ShowString(30,130,200,16,16,"LoopBack Mode");
			}
 			POINT_COLOR=BLUE;			//��������Ϊ��ɫ 
		}		 
		key=CAN_Receive_Msg(canbuf);
		if(key)//���յ�������
		{			
			LCD_Fill(30,270,130,310,WHITE);//���֮ǰ����ʾ
 			for(i=0;i<key;i++)
			{									    
				if(i<4)LCD_ShowxNum(30+i*32,270,canbuf[i],3,16,0X80);	//��ʾ����
				else LCD_ShowxNum(30+(i-4)*32,290,canbuf[i],3,16,0X80);	//��ʾ����
 			}
		}
		t++; 
		delay_ms(10);
		if(t==20)
		{
			LED0=!LED0;//��ʾϵͳ��������	
			t=0;
			cnt++;
			LCD_ShowxNum(30+48,170,cnt,3,16,0X80);	//��ʾ����
		}		   
	}
}





















