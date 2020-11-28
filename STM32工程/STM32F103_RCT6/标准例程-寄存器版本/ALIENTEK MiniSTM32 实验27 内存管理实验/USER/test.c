#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"   
#include "lcd.h"   
#include "key.h" 
#include "usmart.h" 
#include "malloc.h"   
//ALIENTEK Mini STM32�����巶������27
//�ڴ����ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾ 

int main(void)
{		
	u8 key;		 
 	u8 i=0;	    
	u8 *p=0;
	u8 *tp=0;
	u8 paddr[18];			//���P Addr:+p��ַ��ASCIIֵ  
 	Stm32_Clock_Init(9);	//ϵͳʱ������
	uart_init(72,9600);	 	//���ڳ�ʼ��Ϊ9600
	delay_init(72);	   	 	//��ʱ��ʼ�� 
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
	LCD_Init();			   	//��ʼ��LCD
	usmart_dev.init(72);	//��ʼ��USMART		
 	KEY_Init();				//������ʼ��   
	mem_init();				//��ʼ���ڴ��
			    
 	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(60,50,200,16,16,"Mini STM32");	
	LCD_ShowString(60,70,200,16,16,"MALLOC TEST");	
	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,200,16,16,"2014/3/12");  
	LCD_ShowString(60,130,200,16,16,"KEY0:Malloc");
	LCD_ShowString(60,150,200,16,16,"KEY1:Write Data");
	LCD_ShowString(60,170,200,16,16,"WK_UP:Free");

 	POINT_COLOR=BLUE;//��������Ϊ��ɫ  
	LCD_ShowString(60,190,200,16,16,"SRAM USED:   %");  
  	while(1)
	{	
		key=KEY_Scan(0);//��֧������	
		switch(key)
		{
			case 0:		//û�а�������	
				break;
			case 1:		//KEY0����
				p=mymalloc(2048);	//����2K�ֽ�
				if(p!=NULL)sprintf((char*)p,"Memory Malloc Test%03d",i);//��pд��һЩ����
				break;
			case 2:		//KEY1����	   
				if(p!=NULL)
				{
					sprintf((char*)p,"Memory Malloc Test%03d",i);//������ʾ���� 	 
					LCD_ShowString(60,250,200,16,16,p);			 //��ʾP������
				}
				break;
			case 3:		//WK_UP����	  
				myfree(p);	//�ͷ��ڴ�
				p=0;		//ָ��յ�ַ
				break; 
		}
		if(tp!=p)
		{
			tp=p;
			sprintf((char*)paddr,"P Addr:0X%08X",(u32)tp);
			LCD_ShowString(60,230,200,16,16,paddr);	//��ʾp�ĵ�ַ
			if(p)LCD_ShowString(60,250,200,16,16,p);//��ʾP������
		    else LCD_Fill(60,250,239,266,WHITE);	//p=0,�����ʾ
		}
		delay_ms(10);   
		i++;
		if((i%20)==0)//DS0��˸.
		{
			LCD_ShowNum(60+80,190,mem_perused(),3,16);//��ʾ�ڴ�ʹ����
 			LED0=!LED0;
 		}
	}	 	   
}











