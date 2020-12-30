#include "sys.h"
#include "usart.h"		
#include "delay.h"	 
#include "lcd.h"
#include "touch.h"  
#include "w25q128.h"  
#include "text.h"
#include "ds18b20.h"   
#include "memory.h" 
#include "rc522.h"

/*全局变量*/
unsigned char CT[2];//卡类型
unsigned char SN[4]; //卡号
unsigned char RFID[16];			//存放RFID 
unsigned char lxl_bit=0;
unsigned char card1_bit=0;
unsigned char card2_bit=0;
unsigned char card3_bit=0;
unsigned char card4_bit=0;
unsigned char total=0;
unsigned char lxl[4]={6,109,250,186};
unsigned char card_1[4]={66,193,88,0};
unsigned char card_2[4]={66,191,104,0};
unsigned char card_3[4]={62,84,28,11};
unsigned char card_4[4]={126,252,248,12};
u8 KEY[6]={0xff,0xff,0xff,0xff,0xff,0xff};
unsigned char RFID1[16]={0x01,0x00,0x00,0x00,0x00,0x00,0xff,0x07,0x80,0x29,0xff,0xff,0xff,0xff,0xff,0xff};

//void rtp_test(void);
//void Load_Drow_Dialog(void);
//void gui_fill_circle(u16 x0,u16 y0,u16 r,u16 color);
//u16 my_abs(u16 x1,u16 x2);
//void lcd_draw_bline(u16 x1, u16 y1, u16 x2, u16 y2,u8 size,u16 color);
//void test_touch(void)
//{
//	tp_dev.scan(0); 
//if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
//{
//	if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
//	{
//		if(tp_dev.x[0]>11&&tp_dev.x[0]<150&&tp_dev.y[0]>10&&tp_dev.y[0]<80)
//		{
//			Show_Str(50,200,24,24,"对",24,0);
//		}
//		else if(tp_dev.x[0]>11&&tp_dev.x[0]<150&&tp_dev.y[0]>100&&tp_dev.y[0]<170)
//		{
//			Show_Str(50,200,24,24,"错",24,0);
//		}
//		else if(tp_dev.x[0]>150&&tp_dev.x[0]<200&&tp_dev.y[0]>200&&tp_dev.y[0]<230)
//		{
//			TP_Adjust();
//		}
//		else
//		{
//			Show_Str(50,200,24,24,"无",24,0);
//			LCD_ShowxNum(10,240,tp_dev.x[0],9,16,0);
//			LCD_ShowxNum(10,280,tp_dev.y[0],9,16,0);

//		}
//	}
//}	
//	else Show_Str(50,200,24,24,"浪",24,0);
//}
//清空屏幕并在右上角显示"RST"
//void Load_Drow_Dialog(void)
//{
//	LCD_Clear(WHITE);	//清屏   
// 	POINT_COLOR=BLUE;	//设置字体为蓝色 
//	LCD_ShowString(lcddev.width-24,0,200,16,16,"RST");//显示清屏区域
//  	POINT_COLOR=RED;	//设置画笔蓝色 
//}

// //5个触控点的颜色												 
//const u16 POINT_COLOR_TBL[CT_MAX_TOUCH]={RED,GREEN,BLUE,BROWN,GRED};  
////电阻触摸屏测试函数
//void rtp_test(void)
//{  
//	while(1)
//	{
//		tp_dev.scan(0); 		 
//		if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
//		{	
//		 	if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
//			{	
//				if(tp_dev.x[0]>(lcddev.width-24)&&tp_dev.y[0]<16)Load_Drow_Dialog();//清除
//				else TP_Draw_Big_Point(tp_dev.x[0],tp_dev.y[0],RED);		//画图	  			   
//			}
//		}else delay_ms(10);	//没有按键按下的时候 	    
//	}
//}

int main(void)
{		
	unsigned char status;
	unsigned char s=7;
	u8 t;
	Stm32_Clock_Init(9);	//系统时钟设置
	delay_init(72);	  		//延时初始化
	uart_init(72,115200); 	//串口初始化为115200
	LCD_Init();
	W25QXX_Init();				//初始化W25Q128 和SPI2
	tp_dev.init();			//触摸屏初始化 
	while(font_init()) 			//检查字库
	{;}  
	InitRc522();
	Show_Str(150,200,48,24,"校准",24,0);
//	while(DS18B20_Init())	//DS18B20初始化	
//	{
//		LCD_ShowString(60,130,200,16,16,"DS18B20 Error");
//		delay_ms(200);
//		LCD_Fill(60,130,239,130+16,WHITE);
// 		delay_ms(200);
//	}
//	Show_Str(5,5,132,24,"第一次数据：",24,0);
//	Show_Str(5,35,132,24,"第二次数据：",24,0);
//	Show_Str(5,65,108,24,"温度数据：",24,0);
//		LCD_DrawRectangle(10,10,150,80);
//		LCD_ShowString(11,11,80,16,16,"right");
//		LCD_DrawRectangle(10,100,150,170);
//		LCD_ShowString(11,101,64,16,16,"left");
//		Show_Str(150,200,48,24,"校准",24,0);
		
  	while(1)
	{
////		test_touch();
//		rtp_test(); 	
//LCD_ShowChar(60+40,150,' ',16,0);			//去掉负号
//			LCD_ShowNum(60+40+8,150,temperature/10,2,16);	//显示正数部分	    
//   			LCD_ShowNum(60+40+32,150,temperature%10,1,16);	//显示小数部分 	
//		temp_memory();
 	while(1)
	{	
		status = PcdRequest(PICC_REQALL,CT);/*尋卡*/
		if(status==MI_OK)//尋卡成功
		{
			 status=MI_ERR;
			 status = PcdAnticoll(SN);/*防冲撞*/
		}	
		if(status==MI_OK)
		{
			status=MI_ERR;
			status =PcdSelect(SN);
		}

		if(status==MI_OK)//選卡成功
		{
			 status=MI_ERR;
			 status =PcdAuthState(0x61,0x06,KEY,SN);
		 }
	
		 if(status==MI_OK)//驗證成功
		 {
			  status=MI_ERR;
			  for(t=0;t<4;t++)
			  {
					LCD_ShowNum(0,116+t*16,SN[t],3,16);
			  }	  
		  }
//	 if(status==MI_OK)//驗證成功
//		 {
//			status=MI_ERR;
////			LCD_ShowNum(0,116+t*16,SN[t],3,16);
//			 date1=SN[0];
//			 date2=SN[1];
//			 date3=SN[2];
//			 date4=SN[3];
//			LCD_ShowNum(5,5,date1,3,16);	//显示小数部分 
//			LCD_ShowNum(5,25,date2,3,16);	//显示小数部分 
//			LCD_ShowNum(5,45,date3,3,16);	//显示小数部分 
//			LCD_ShowNum(5,65,date4,3,16);	//显示小数部分  

//			  }	 
	}
}
	}	 







