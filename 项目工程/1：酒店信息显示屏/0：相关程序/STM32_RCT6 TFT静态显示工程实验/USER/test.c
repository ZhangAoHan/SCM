#include "sys.h"
#include "usart.h"		
#include "delay.h"	   
#include "TFT.h"   


int main(void)
{
//	u8 lcd_id[12]; //存放 LCD ID 字符串
	u8 t;
//	u8 value;
	u8 temp[3];
	Stm32_Clock_Init(9); //系统时钟设置
	uart_init(72,9600); //串口初始化为 115200
	delay_init(72); //延时初始化
	LCD_Init();
	
	//sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//将 LCD ID 打印到 lcd_id 数组。
	LCD_Clear(WHITE);
	while(1)
	{
//		POINT_COLOR=BLACK;
//		LCD_ShowString(30,30,150,54,24,"STM32");   //X,Y,区域大小（字号*字符数） 字号  字符
//		LCD_Fill(17,56,47,86,RED);
//		POINT_COLOR=BLUE;
//		LCD_Draw_Circle(32,71,15);
//		LCD_DrawRectangle(16,55,48,87);
				if(USART_RX_STA)
		{					   

			for(t=0;t<3;t++)
			{
			temp[t]=USART_RX_BUF[t];
			USART1->DR=temp[t];	  //将数据发送给上位机
			while((USART1->SR&0X40)==0) { ; }
			temp[t]=temp[t]-48;
			printf("U%d %d",t,temp[t]);
//			printf("U%d %d",t,USART_RX_BUF[t]);
//			printf("\r\n\r\n");//插入换行	
			}
//			value=temp[0]*100+temp[1]*10+temp[2];
			LCD_ShowNum(15,15,temp[0],1,24);
			LCD_ShowNum(27,15,temp[1],1,24);
			LCD_ShowNum(39,15,temp[2],1,24);

			
		
		
//			printf("\r\n\r\n");//插入换行
			
			USART_RX_STA=0;

		}
			


		
		


		
	}
}


