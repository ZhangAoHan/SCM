#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 		 	 
#include "lcd.h"  
#include "key.h"  
#include "stmflash.h"  
#include "usmart.h" 
//ALIENTEKս��STM32������ ʵ��34
//FLASHģ��EEPROM ʵ�� 
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾ 

//Ҫд�뵽STM32 FLASH���ַ�������
const u8 TEXT_Buffer[]={"STM32F103 FLASH TEST"};
#define SIZE sizeof(TEXT_Buffer)		//���鳤��
#define FLASH_SAVE_ADDR  0X08070000		//����FLASH �����ַ(����Ϊż��������ֵҪ���ڱ�������ռ��FLASH�Ĵ�С+0X08000000)

int main(void)
{		
	u8 key=0;
	u16 i=0;
	u8 datatemp[SIZE];	   
 	Stm32_Clock_Init(9);		//ϵͳʱ������
	uart_init(72,115200);		//���ڳ�ʼ��Ϊ115200
	delay_init(72);	   	 		//��ʱ��ʼ�� 
	usmart_dev.init(72);		//��ʼ��USMART		
 	LED_Init();		  			//��ʼ����LED���ӵ�Ӳ���ӿ�
	KEY_Init();					//��ʼ������
	LCD_Init();			   		//��ʼ��LCD  
 	POINT_COLOR=RED;			//��������Ϊ��ɫ 
	LCD_ShowString(30,50,200,16,16,"WarShip STM32");	
	LCD_ShowString(30,70,200,16,16,"FLASH EEPROM TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2015/1/18"); 
	LCD_ShowString(30,130,200,16,16,"KEY1:Write  KEY0:Read");
	while(1)
	{
		key=KEY_Scan(0);
		if(key==KEY1_PRES)	//KEY1����,д��STM32 FLASH
		{
			LCD_Fill(0,170,239,319,WHITE);//�������    
 			LCD_ShowString(30,170,200,16,16,"Start Write FLASH....");
			STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)TEXT_Buffer,SIZE);
			LCD_ShowString(30,170,200,16,16,"FLASH Write Finished!");//��ʾ�������
		}
		if(key==KEY0_PRES)	//KEY0����,��ȡ�ַ�������ʾ
		{
 			LCD_ShowString(30,170,200,16,16,"Start Read FLASH.... ");
			STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)datatemp,SIZE);
			LCD_ShowString(30,170,200,16,16,"The Data Readed Is:  ");//��ʾ�������
			LCD_ShowString(30,190,200,16,16,datatemp);//��ʾ�������ַ���
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










