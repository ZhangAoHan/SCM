#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 		 	 
#include "lcd.h"  
#include "joypad.h"  
//ALIENTEKս��STM32������ ʵ��29
//��Ϸ�ֱ� ʵ�� 
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾ 

const u8*JOYPAD_SYMBOL_TBL[8]=
{"Right","Left","Down","Up","Start","Select","A","B"};//�ֱ��������Ŷ���
int main(void)
{		
	u8 key;
	u8 t=0,i=0;		 
 	Stm32_Clock_Init(9);	//ϵͳʱ������
	uart_init(72,115200);	//���ڳ�ʼ��Ϊ115200
	delay_init(72);	   	 	//��ʱ��ʼ�� 
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
	LCD_Init();			   	//��ʼ��LCD 	
	JOYPAD_Init();			//�ֱ���ʼ��
 	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(30,50,200,16,16,"WarShip STM32");	
	LCD_ShowString(30,70,200,16,16,"JOYPAD TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2015/1/16");
   	LCD_ShowString(30,130,200,16,16,"KEYVAL:");	      
    LCD_ShowString(30,150,200,16,16,"SYMBOL:");	      
 	POINT_COLOR=BLUE;//��������Ϊ��ɫ 
	while(1)
	{
		key=JOYPAD_Read();
		if(key)
		{
			LCD_ShowNum(116,130,key,3,16);//��ʾ��ֵ
			for(i=0;i<8;i++)
			{
				if(key&(0X80>>i))
				{
					LCD_Fill(30+56,150,30+56+48,150+16,WHITE);//���֮ǰ����ʾ
					LCD_ShowString(30+56,150,200,16,16,(u8*)JOYPAD_SYMBOL_TBL[i]);//��ʾ����
				}		
			}		    
		}
	 	delay_ms(10);
		t++;
		if(t==20)
		{
			t=0;
			LED0=!LED0;
		}
	}
}












