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
//ALIENTEK Mini STM32开发板范例代码34
//USB读卡器实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司 
 
int main(void)
{						  
	u8 offline_cnt=0;
	u8 tct=0;
	u8 USB_STA;
	u8 Divece_STA; 
	
   	Stm32_Clock_Init(9);//系统时钟设置
	delay_init(72);		//延时初始化
	uart_init(72,9600); //串口1初始化  	  
	LCD_Init();			//初始化液晶 
	LED_Init();         //LED初始化	 
	KEY_Init();			//按键初始化	   
	
 	POINT_COLOR=RED;	//设置字体为红色	   
	LCD_ShowString(60,50,200,16,16,"Mini STM32");	
	LCD_ShowString(60,70,200,16,16,"USB Card Reader TEST");	
	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,200,16,16,"2014/3/15");	
 	SPI_Flash_Init();
	if(SD_Initialize())LCD_ShowString(60,130,200,16,16,"SD Card Error!");	//检测SD卡错误
	else //SD 卡正常
	{   															  
		LCD_ShowString(60,130,200,16,16,"SD Card Size:     MB");
 	    Mass_Memory_Size[0]=(long long)SD_GetSectorCount()*512;//得到SD卡容量（字节），当SD卡容量超过4G的时候,需要用到两个u32来表示
	    Mass_Block_Size[0] =512;//因为我们在Init里面设置了SD卡的操作字节为512个,所以这里一定是512个字节.
	    Mass_Block_Count[0]=Mass_Memory_Size[0]/Mass_Block_Size[0];
 		LCD_ShowNum(164,130,Mass_Memory_Size[0]>>20,5,16);	//显示SD卡容量
 	}
	if(SPI_FLASH_TYPE!=W25Q64)LCD_ShowString(60,130,200,16,16,"W25Q64 Error!");	//检测SD卡错误
	else //SPI FLASH 正常
	{   															  
 	   	Mass_Memory_Size[1]=4916*1024;//前4.8M字节
	    Mass_Block_Size[1] =512;//因为我们在Init里面设置了SD卡的操作字节为512个,所以这里一定是512个字节.
	    Mass_Block_Count[1]=Mass_Memory_Size[1]/Mass_Block_Size[1];
		LCD_ShowString(60,150,200,16,16,"SPI FLASH Size:4916KB");	 
	}
  	delay_ms(1800);
 	USB_Port_Set(0); 	//USB先断开
	delay_ms(300);
   	USB_Port_Set(1);	//USB再次连接   
 	LCD_ShowString(60,170,200,16,16,"USB Connecting...");//提示SD卡已经准备了	
	Data_Buffer=mymalloc(BULK_MAX_PACKET_SIZE*2*4);	//为USB数据缓存区申请内存
	Bulk_Data_Buff=mymalloc(BULK_MAX_PACKET_SIZE);	//申请内存
 	//USB配置
 	USB_Interrupts_Config();    
 	Set_USBClock();   
 	USB_Init();	    
	delay_ms(1800);	   	    
	while(1)
	{	
		delay_ms(1);				  
		if(USB_STA!=USB_STATUS_REG)//状态改变了 
		{	 						   
			LCD_Fill(60,190,240,190+16,WHITE);//清除显示			  	   
			if(USB_STATUS_REG&0x01)//正在写		  
			{
				LCD_ShowString(60,190,200,16,16,"USB Writing...");//提示USB正在写入数据	 
			}
			if(USB_STATUS_REG&0x02)//正在读
			{
				LCD_ShowString(60,190,200,16,16,"USB Reading...");//提示USB正在读出数据  		 
			}	 										  
			if(USB_STATUS_REG&0x04)LCD_ShowString(60,210,200,16,16,"USB Write Err ");//提示写入错误
			else LCD_Fill(60,210,240,210+16,WHITE);//清除显示	  
			if(USB_STATUS_REG&0x08)LCD_ShowString(60,230,200,16,16,"USB Read  Err ");//提示读出错误
			else LCD_Fill(60,230,240,230+16,WHITE);//清除显示    
			USB_STA=USB_STATUS_REG;//记录最后的状态
		}
		if(Divece_STA!=bDeviceState) 
		{
			if(bDeviceState==CONFIGURED)LCD_ShowString(60,170,200,16,16,"USB Connected    ");//提示USB连接已经建立
			else LCD_ShowString(60,170,200,16,16,"USB DisConnected ");//提示USB被拔出了
			Divece_STA=bDeviceState;
		}
		tct++;
		if(tct==200)
		{
			tct=0;
			LED0=!LED0;//提示系统在运行
			if(USB_STATUS_REG&0x10)
			{
				offline_cnt=0;//USB连接了,则清除offline计数器
				bDeviceState=CONFIGURED;
			}else//没有得到轮询 
			{
				offline_cnt++;  
				if(offline_cnt>10)bDeviceState=UNCONNECTED;//2s内没收到在线标记,代表USB被拔出了
			}
			USB_STATUS_REG=0;
		}
	};  										    			    
}












