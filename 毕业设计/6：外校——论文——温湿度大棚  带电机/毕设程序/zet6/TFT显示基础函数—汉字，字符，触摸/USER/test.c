#include "sys.h"
#include "usart.h"		
#include "delay.h"	 
#include "lcd.h"
#include "touch.h"  
#include "w25q128.h"  
#include "text.h"	
#include "24l01.h" 

u8 mode=0;

int main(void)
{				 
	u8 tmp_buf[33];	  
	Stm32_Clock_Init(9);	//系统时钟设置
	delay_init(72);	  		//延时初始化
	uart_init(72,115200); 	//串口初始化为115200
	LCD_Init();
	W25QXX_Init();				//初始化W25Q128 和SPI2
	tp_dev.init();			//触摸屏初始化 
	NRF24L01_Init();  
	while(font_init()) 			//检查字库
	{;}  
	while(NRF24L01_Check())
	{
 		delay_ms(200);
	}
  	while(1)
	{
		if(mode==0)
		{
			NRF24L01_RX_Mode();	
			if(NRF24L01_RxPacket(tmp_buf)==0)//一旦接收到信息,则显示出来.
			{
				if(tmp_buf[0]==' '&&tmp_buf[5]=='!')
				{
					LCD_ShowxNum(20,20,tmp_buf[1],4,16,0);
					LCD_ShowxNum(20,50,tmp_buf[2],4,16,0);
					LCD_ShowxNum(20,80,tmp_buf[3],4,16,0);
					LCD_ShowxNum(20,110,tmp_buf[4],4,16,0);
					tmp_buf[0]=tmp_buf[1]=tmp_buf[2]=tmp_buf[3]=tmp_buf[4]=tmp_buf[5]=0;
				}
			}
		}
//		if(mode==1)
//		{
//			
//		}
	}	 
} 






