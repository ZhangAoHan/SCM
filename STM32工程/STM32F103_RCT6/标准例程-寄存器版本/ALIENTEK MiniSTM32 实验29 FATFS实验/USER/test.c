#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"   
#include "lcd.h"   
#include "key.h" 
#include "usmart.h" 
#include "malloc.h"  
#include "MMC_SD.h" 
#include "ff.h"  
#include "exfuns.h"
//ALIENTEK Mini STM32�����巶������29
//FATFS ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾  
    							   	 
int main(void)
{		 
 	u32 total,free;
	u8 t=0;		   	    
  	Stm32_Clock_Init(9);//ϵͳʱ������
	delay_init(72);		//��ʱ��ʼ��
	uart_init(72,9600); //����1��ʼ��  	  
 	exfuns_init();		//Ϊfatfs��ر��������ڴ�				 
	LCD_Init();			//��ʼ��Һ�� 
	LED_Init();         //LED��ʼ��	 													    
	usmart_dev.init(72);	
 	mem_init();			//��ʼ���ڴ��	

 	POINT_COLOR=RED;//��������Ϊ��ɫ	   
	LCD_ShowString(60,50,200,16,16,"Mini STM32");	
	LCD_ShowString(60,70,200,16,16,"FATFS TEST");	
	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,200,16,16,"Use USMART for test");	  
	LCD_ShowString(60,130,200,16,16,"2014/3/14");	  

	while(SD_Initialize())					//���SD��
	{
		LCD_ShowString(60,150,200,16,16,"SD Card Error!");
		delay_ms(200);
		LCD_Fill(60,150,240,150+16,WHITE);//�����ʾ			  
		delay_ms(200);
		LED0=!LED0;//DS0��˸
	}								   	
 	exfuns_init();							//Ϊfatfs��ر��������ڴ�				 
  	f_mount(fs[0],"0:",1); 					//����SD�� 
 	f_mount(fs[1],"1:",1); 					//����FLASH.	  
	while(exf_getfree("0",&total,&free))	//�õ�SD������������ʣ������
	{
		LCD_ShowString(60,150,200,16,16,"Fatfs Error!");
		delay_ms(200);
		LCD_Fill(60,150,240,150+16,WHITE);//�����ʾ			  
		delay_ms(200);
		LED0=!LED0;//DS0��˸
	}													 
 	POINT_COLOR=BLUE;//��������Ϊ��ɫ	   
	LCD_ShowString(60,150,200,16,16,"FATFS OK!");	 
	LCD_ShowString(60,170,200,16,16,"SD Total Size:     MB");	 
	LCD_ShowString(60,190,200,16,16,"SD  Free Size:     MB"); 	    
 	LCD_ShowNum(172,170,total>>10,5,16);					//��ʾSD�������� MB
 	LCD_ShowNum(172,190,free>>10,5,16);						//��ʾSD��ʣ������ MB			    
	while(1)
	{
		t++;
		delay_ms(200);		 			   
		LED0=!LED0;
	} 
}













