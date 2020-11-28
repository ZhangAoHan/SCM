#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"   
#include "lcd.h"   
#include "key.h" 
#include "usmart.h" 
#include "malloc.h" 
#include "mmc_sd.h" 
#include "flash.h"	
#include "mass_mal.h"
#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h"
#include "memory.h"	    
#include "usb_bot.h"  
//ALIENTEK Mini STM32�����巶������34
//USB������ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾ 
 
int main(void)
{						  
	u8 offline_cnt=0;
	u8 tct=0;
	u8 USB_STA;
	u8 Divece_STA; 
	
   	Stm32_Clock_Init(9);//ϵͳʱ������
	delay_init(72);		//��ʱ��ʼ��
	uart_init(72,9600); //����1��ʼ��  	  
	LCD_Init();			//��ʼ��Һ�� 
	LED_Init();         //LED��ʼ��	 
	KEY_Init();			//������ʼ��	   
	
 	POINT_COLOR=RED;	//��������Ϊ��ɫ	   
	LCD_ShowString(60,50,200,16,16,"Mini STM32");	
	LCD_ShowString(60,70,200,16,16,"USB Card Reader TEST");	
	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,200,16,16,"2014/3/15");	
 	SPI_Flash_Init();
	if(SD_Initialize())LCD_ShowString(60,130,200,16,16,"SD Card Error!");	//���SD������
	else //SD ������
	{   															  
		LCD_ShowString(60,130,200,16,16,"SD Card Size:     MB");
 	    Mass_Memory_Size[0]=(long long)SD_GetSectorCount()*512;//�õ�SD���������ֽڣ�����SD����������4G��ʱ��,��Ҫ�õ�����u32����ʾ
	    Mass_Block_Size[0] =512;//��Ϊ������Init����������SD���Ĳ����ֽ�Ϊ512��,��������һ����512���ֽ�.
	    Mass_Block_Count[0]=Mass_Memory_Size[0]/Mass_Block_Size[0];
 		LCD_ShowNum(164,130,Mass_Memory_Size[0]>>20,5,16);	//��ʾSD������
 	}
	if(SPI_FLASH_TYPE!=W25Q64)LCD_ShowString(60,130,200,16,16,"W25Q64 Error!");	//���SD������
	else //SPI FLASH ����
	{   															  
 	   	Mass_Memory_Size[1]=4916*1024;//ǰ4.8M�ֽ�
	    Mass_Block_Size[1] =512;//��Ϊ������Init����������SD���Ĳ����ֽ�Ϊ512��,��������һ����512���ֽ�.
	    Mass_Block_Count[1]=Mass_Memory_Size[1]/Mass_Block_Size[1];
		LCD_ShowString(60,150,200,16,16,"SPI FLASH Size:4916KB");	 
	}
  	delay_ms(1800);
 	USB_Port_Set(0); 	//USB�ȶϿ�
	delay_ms(300);
   	USB_Port_Set(1);	//USB�ٴ�����   
 	LCD_ShowString(60,170,200,16,16,"USB Connecting...");//��ʾSD���Ѿ�׼����	
	Data_Buffer=mymalloc(BULK_MAX_PACKET_SIZE*2*4);	//ΪUSB���ݻ����������ڴ�
	Bulk_Data_Buff=mymalloc(BULK_MAX_PACKET_SIZE);	//�����ڴ�
 	//USB����
 	USB_Interrupts_Config();    
 	Set_USBClock();   
 	USB_Init();	    
	delay_ms(1800);	   	    
	while(1)
	{	
		delay_ms(1);				  
		if(USB_STA!=USB_STATUS_REG)//״̬�ı��� 
		{	 						   
			LCD_Fill(60,190,240,190+16,WHITE);//�����ʾ			  	   
			if(USB_STATUS_REG&0x01)//����д		  
			{
				LCD_ShowString(60,190,200,16,16,"USB Writing...");//��ʾUSB����д������	 
			}
			if(USB_STATUS_REG&0x02)//���ڶ�
			{
				LCD_ShowString(60,190,200,16,16,"USB Reading...");//��ʾUSB���ڶ�������  		 
			}	 										  
			if(USB_STATUS_REG&0x04)LCD_ShowString(60,210,200,16,16,"USB Write Err ");//��ʾд�����
			else LCD_Fill(60,210,240,210+16,WHITE);//�����ʾ	  
			if(USB_STATUS_REG&0x08)LCD_ShowString(60,230,200,16,16,"USB Read  Err ");//��ʾ��������
			else LCD_Fill(60,230,240,230+16,WHITE);//�����ʾ    
			USB_STA=USB_STATUS_REG;//��¼����״̬
		}
		if(Divece_STA!=bDeviceState) 
		{
			if(bDeviceState==CONFIGURED)LCD_ShowString(60,170,200,16,16,"USB Connected    ");//��ʾUSB�����Ѿ�����
			else LCD_ShowString(60,170,200,16,16,"USB DisConnected ");//��ʾUSB���γ���
			Divece_STA=bDeviceState;
		}
		tct++;
		if(tct==200)
		{
			tct=0;
			LED0=!LED0;//��ʾϵͳ������
			if(USB_STATUS_REG&0x10)
			{
				offline_cnt=0;//USB������,�����offline������
				bDeviceState=CONFIGURED;
			}else//û�еõ���ѯ 
			{
				offline_cnt++;  
				if(offline_cnt>10)bDeviceState=UNCONNECTED;//2s��û�յ����߱��,����USB���γ���
			}
			USB_STATUS_REG=0;
		}
	};  										    			    
}












