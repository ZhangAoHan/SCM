#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"   
#include "lcd.h"   
#include "mouse.h"   
//ALIENTEK Mini STM32�����巶������25
//PS2���ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾ 

//��ʾ��������ֵ
//x,y:��LCD����ʾ������λ��
//pos:����ֵ
void Mouse_Show_Pos(u16 x,u16 y,short pos)
{
	if(pos<0)
	{			  
		LCD_ShowChar(x,y,'-',16,0);		//��ʾ����
		pos=-pos;						//תΪ����
	}else LCD_ShowChar(x,y,' ',16,0);	//ȥ������
	LCD_ShowNum(x+8,y,pos,5,16);		//��ʾֵ				  
}
 	    		   						   	 
int main(void)
{			  
	u8 t;
	u8 errcnt=0;	 
 	Stm32_Clock_Init(9);	//ϵͳʱ������
	uart_init(72,9600);	 	//���ڳ�ʼ��Ϊ9600
	delay_init(72);	   	 	//��ʱ��ʼ�� 
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
	LCD_Init();			   	//��ʼ��LCD   
 	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(60,50,200,16,16,"Mini STM32");	
	LCD_ShowString(60,70,200,16,16,"Mouse TEST");	
	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,200,16,16,"2014/3/12");		  
 	while(Init_Mouse())	//�������Ƿ���λ.	
	{
		LCD_ShowString(60,130,200,16,16,"Mouse Error");
		delay_ms(400);
		LCD_Fill(60,130,239,130+16,WHITE);	 
		delay_ms(100);
	}								   
	LCD_ShowString(60,130,200,16,16,"Mouse OK");
 	LCD_ShowString(60,150,200,16,16,"Mouse ID:");
 	LCD_ShowNum(132,150,MOUSE_ID,3,16);//���ģʽ

	POINT_COLOR=BLUE;
 	LCD_ShowString(30,170,200,16,16,"BUF[0]:");
	LCD_ShowString(30,186,200,16,16,"BUF[1]:");
	LCD_ShowString(30,202,200,16,16,"BUF[2]:"); 
	if(MOUSE_ID==3)LCD_ShowString(30,218,200,16,16,"BUF[3]:"); 

	LCD_ShowString(90+30,170,200,16,16,"X  POS:");
	LCD_ShowString(90+30,186,200,16,16,"Y  POS:");
	LCD_ShowString(90+30,202,200,16,16,"Z  POS:"); 
	if(MOUSE_ID==3)LCD_ShowString(90+30,218,200,16,16,"BUTTON:"); 
	t=0;
	while(1)
	{
		if(PS2_Status&0x80)//�õ���һ������
		{		  
			LCD_ShowNum(56+30,170,PS2_DATA_BUF[0],3,16);//���ģʽ
			LCD_ShowNum(56+30,186,PS2_DATA_BUF[1],3,16);//���ģʽ
			LCD_ShowNum(56+30,202,PS2_DATA_BUF[2],3,16);//���ģʽ
			if(MOUSE_ID==3)LCD_ShowNum(56+30,218,PS2_DATA_BUF[3],3,16);//���ģʽ

			Mouse_Data_Pro();//��������

			Mouse_Show_Pos(146+30,170,MouseX.x_pos);				//X����
			Mouse_Show_Pos(146+30,186,MouseX.y_pos);				//Y����
			if(MOUSE_ID==3)Mouse_Show_Pos(146+30,202,MouseX.z_pos);	//����λ��

		    if(MouseX.bt_mask&0x01)LCD_ShowString(146+30,218,200,16,16,"LEFT"); 
			else LCD_ShowString(146+30,218,200,16,16,"    "); 
		    if(MouseX.bt_mask&0x02)LCD_ShowString(146+30,234,200,16,16,"RIGHT"); 
			else LCD_ShowString(146+30,234,200,16,16,"     "); 				    
			if(MouseX.bt_mask&0x04)LCD_ShowString(146+30,250,200,16,16,"MIDDLE"); 
			else LCD_ShowString(146+30,250,200,16,16,"      ");   		 
			PS2_Status=MOUSE;
			PS2_En_Data_Report();//ʹ�����ݱ���
		}else if(PS2_Status&0x40)
		{
			errcnt++;
			PS2_Status=MOUSE;
			LCD_ShowNum(86+30,234,errcnt,3,16);//���ģʽ
		}
		t++;
		delay_ms(1);
		if(t==200)
		{
			t=0;
			LED0=!LED0;
		}
	} 
}

















