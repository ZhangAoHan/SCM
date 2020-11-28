#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"   
#include "lcd.h"  
#include "key.h"  
#include "24cxx.h" 
#include "usmart.h" 
//ALIENTEK Mini STM32�����巶������19
//IICʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾
   	
//Ҫд�뵽24c02���ַ�������
const u8 TEXT_Buffer[]={"MiniSTM32 IIC TEST"};
#define SIZE sizeof(TEXT_Buffer)	 
int main(void)
{		
	u8 key;
	u16 i=0;
	u8 datatemp[SIZE];
 	Stm32_Clock_Init(9);	//ϵͳʱ������
	uart_init(72,9600);	 	//���ڳ�ʼ��Ϊ9600
	delay_init(72);	   	 	//��ʱ��ʼ�� 
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
 	LCD_Init();			   	//��ʼ��LCD
	usmart_dev.init(72);	//��ʼ��USMART		
	KEY_Init();				//������ʼ��		 	
	AT24CXX_Init();			//IIC��ʼ�� 

 	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(60,50,200,16,16,"Mini STM32");	
	LCD_ShowString(60,70,200,16,16,"IIC TEST");	
	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,200,16,16,"2014/3/9");	
	LCD_ShowString(60,130,200,16,16,"WK_UP:Write  KEY0:Read");	//��ʾ��ʾ��Ϣ		
 	while(AT24CXX_Check())//��ⲻ��24c02
	{
		LCD_ShowString(60,150,200,16,16,"24C02 Check Failed!");
		delay_ms(500);
		LCD_ShowString(60,150,200,16,16,"Please Check!      ");
		delay_ms(500);
		LED0=!LED0;//DS0��˸
	}
	LCD_ShowString(60,150,200,16,16,"24C02 Ready!");    
 	POINT_COLOR=BLUE;//��������Ϊ��ɫ	  
	while(1)
	{
		key=KEY_Scan(0);
		if(key==WKUP_PRES)//WK_UP ����,д��24C02
		{
			LCD_Fill(0,170,239,319,WHITE);//�������    
 			LCD_ShowString(60,170,200,16,16,"Start Write 24C02....");
			AT24CXX_Write(0,(u8*)TEXT_Buffer,SIZE);
			LCD_ShowString(60,170,200,16,16,"24C02 Write Finished!");//��ʾ�������
		}
		if(key==KEY0_PRES)//KEY0 ����,��ȡ�ַ�������ʾ
		{
 			LCD_ShowString(60,170,200,16,16,"Start Read 24C02.... ");
			AT24CXX_Read(0,datatemp,SIZE);
			LCD_ShowString(60,170,200,16,16,"The Data Readed Is:  ");//��ʾ�������
			LCD_ShowString(60,190,200,16,16,datatemp);//��ʾ�������ַ���
		}
		i++;
		delay_ms(10);
		if(i==20)
		{
			LED0=!LED0;//��ʾϵͳ��������	
			i=0;
		}		   
	}
}







