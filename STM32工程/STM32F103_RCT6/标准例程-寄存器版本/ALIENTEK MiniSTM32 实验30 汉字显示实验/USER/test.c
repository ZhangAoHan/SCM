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
#include "fontupd.h"
#include "text.h"	
//ALIENTEK Mini STM32�����巶������30
//������ʾ ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾  
    							   	 
int main(void)
{		 
	u32 fontcnt;		  
	u8 i,j;
	u8 fontx[2];//gbk��
	u8 key,t;			
   	Stm32_Clock_Init(9);	//ϵͳʱ������
	delay_init(72);			//��ʱ��ʼ��
	uart_init(72,9600); 	//����1��ʼ��  	  
	LCD_Init();				//��ʼ��Һ�� 
	LED_Init();         	//LED��ʼ��	 
	KEY_Init();				//������ʼ��	  													    
	usmart_dev.init(72);	//usmart��ʼ��	
 	mem_init();				//��ʼ���ڴ��	    
 	exfuns_init();			//Ϊfatfs��ر��������ڴ�  
  	f_mount(fs[0],"0:",1); 	//����SD�� 
 	f_mount(fs[1],"1:",1); 	//����FLASH.
	while(font_init()) 	//����ֿ�
	{
UPD:    
		LCD_Clear(WHITE);		   	//����
 		POINT_COLOR=RED;			//��������Ϊ��ɫ	   	   	  
		LCD_ShowString(60,50,200,16,16,"Mini STM32");
		while(SD_Initialize())		//���SD��
		{
			LCD_ShowString(60,70,200,16,16,"SD Card Failed!");
			delay_ms(200);
			LCD_Fill(60,70,200+60,70+16,WHITE);
			delay_ms(200);		    
		}								 						    
		LCD_ShowString(60,70,200,16,16,"SD Card OK");
		LCD_ShowString(60,90,200,16,16,"Font Updating...");
		key=update_font(20,110,16);//�����ֿ�
		while(key)//����ʧ��		
		{			 		  
			LCD_ShowString(60,110,200,16,16,"Font Update Failed!");
			delay_ms(200);
			LCD_Fill(20,110,200+20,110+16,WHITE);
			delay_ms(200);		       
		} 		  
		LCD_ShowString(60,110,200,16,16,"Font Update Success!");
		delay_ms(1500);	
		LCD_Clear(WHITE);//����	       
	}  
	POINT_COLOR=RED;       
	Show_Str(60,50,200,16,"Mini STM32������",16,0);				    	 
	Show_Str(60,70,200,16,"GBK�ֿ���Գ���",16,0);				    	 
	Show_Str(60,90,200,16,"����ԭ��@ALIENTEK",16,0);				    	 
	Show_Str(60,110,200,16,"2014��3��14��",16,0);
	Show_Str(60,130,200,16,"��KEY0,�����ֿ�",16,0);
 	POINT_COLOR=BLUE;  
	Show_Str(60,150,200,16,"������ֽ�:",16,0);				    	 
	Show_Str(60,170,200,16,"������ֽ�:",16,0);				    	 
	Show_Str(60,190,200,16,"���ּ�����:",16,0);

	Show_Str(60,220,200,24,"��Ӧ����Ϊ:",24,0); 
	Show_Str(60,244,200,16,"��Ӧ����(16*16)Ϊ:",16,0);			 
	Show_Str(60,260,200,12,"��Ӧ����(12*12)Ϊ:",12,0);			 
	while(1)
	{
		fontcnt=0;
		for(i=0x81;i<0xff;i++)
		{		
			fontx[0]=i;
			LCD_ShowNum(148,150,i,3,16);		//��ʾ������ֽ�    
			for(j=0x40;j<0xfe;j++)
			{
				if(j==0x7f)continue;
				fontcnt++;
				LCD_ShowNum(148,170,j,3,16);	//��ʾ������ֽ�	 
				LCD_ShowNum(148,190,fontcnt,5,16);//���ּ�����ʾ	 
			 	fontx[1]=j;
				Show_Font(60+132,220,fontx,24,0);	  
				Show_Font(60+144,244,fontx,16,0);	  		 		 
				Show_Font(60+108,260,fontx,12,0);	  		 		 
				t=200;
				while(t--)//��ʱ,ͬʱɨ�谴��
				{
					delay_ms(1);
					key=KEY_Scan(0);
					if(key==KEY0_PRES)goto UPD;
				}
				LED0=!LED0;
			}   
		}	
	} 
}













