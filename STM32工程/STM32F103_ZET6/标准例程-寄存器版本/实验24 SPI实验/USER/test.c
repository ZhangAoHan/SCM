#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 		 	 
#include "lcd.h" 
#include "key.h" 
#include "w25qxx.h" 
#include "usmart.h" 
//ALIENTEKս��STM32������ ʵ��24
//SPI ʵ�� 
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾  

//Ҫд�뵽W25Q128���ַ�������
const u8 TEXT_Buffer[]={"WarShip STM32F1 SPI TEST"};
#define SIZE sizeof(TEXT_Buffer)	 

int main(void)
{	
	u8 key;
	u16 i=0;
	u8 datatemp[SIZE];
	u32 FLASH_SIZE; 
 	Stm32_Clock_Init(9);	//ϵͳʱ������
	uart_init(72,115200);	//���ڳ�ʼ��Ϊ115200
	delay_init(72);	   	 	//��ʱ��ʼ�� 
	usmart_dev.init(72);	//��ʼ��USMART		
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
	LCD_Init();			   	//��ʼ��LCD 	
	KEY_Init();				//������ʼ��		 	 	
	W25QXX_Init();			//W25QXX��ʼ��

 	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(30,50,200,16,16,"WarShip STM32");	
	LCD_ShowString(30,70,200,16,16,"SPI TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2015/1/15");	
	LCD_ShowString(30,130,200,16,16,"KEY1:Write  KEY0:Read");	//��ʾ��ʾ��Ϣ		
	while(W25QXX_ReadID()!=W25Q128)								//��ⲻ��W25Q128
	{
		LCD_ShowString(30,150,200,16,16,"W25Q128 Check Failed!");
		delay_ms(500);
		LCD_ShowString(30,150,200,16,16,"Please Check!        ");
		delay_ms(500);
		LED0=!LED0;//DS0��˸
	}
	LCD_ShowString(30,150,200,16,16,"W25Q128 Ready!");    
	FLASH_SIZE=128*1024*1024;	//FLASH ��СΪ16M�ֽ�
 	POINT_COLOR=BLUE;//��������Ϊ��ɫ	  
	while(1)
	{
		key=KEY_Scan(0);
		if(key==KEY1_PRES)	//KEY1����,д��W25QXX
		{
			LCD_Fill(0,170,239,319,WHITE);//�������    
 			LCD_ShowString(30,170,200,16,16,"Start Write W25Q128...."); 
			W25QXX_Write((u8*)TEXT_Buffer,FLASH_SIZE-100,SIZE);			//�ӵ�����100����ַ����ʼ,д��SIZE���ȵ�����
			LCD_ShowString(30,170,200,16,16,"W25Q128 Write Finished!");	//��ʾ�������
		}
		if(key==KEY0_PRES)	//KEY0����,��ȡ�ַ�������ʾ
		{
 			LCD_ShowString(30,170,200,16,16,"Start Read W25Q128.... ");
			W25QXX_Read(datatemp,FLASH_SIZE-100,SIZE);					//�ӵ�����100����ַ����ʼ,����SIZE���ֽ�
			LCD_ShowString(30,170,200,16,16,"The Data Readed Is:  ");	//��ʾ�������
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





















