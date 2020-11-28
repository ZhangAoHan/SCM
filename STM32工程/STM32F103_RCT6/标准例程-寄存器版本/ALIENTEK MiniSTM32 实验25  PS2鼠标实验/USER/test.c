#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"   
#include "lcd.h"   
#include "mouse.h"   
//ALIENTEK Mini STM32开发板范例代码25
//PS2鼠标实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司 

//显示鼠标的坐标值
//x,y:在LCD上显示的坐标位置
//pos:坐标值
void Mouse_Show_Pos(u16 x,u16 y,short pos)
{
	if(pos<0)
	{			  
		LCD_ShowChar(x,y,'-',16,0);		//显示负号
		pos=-pos;						//转为正数
	}else LCD_ShowChar(x,y,' ',16,0);	//去掉负号
	LCD_ShowNum(x+8,y,pos,5,16);		//显示值				  
}
 	    		   						   	 
int main(void)
{			  
	u8 t;
	u8 errcnt=0;	 
 	Stm32_Clock_Init(9);	//系统时钟设置
	uart_init(72,9600);	 	//串口初始化为9600
	delay_init(72);	   	 	//延时初始化 
	LED_Init();		  		//初始化与LED连接的硬件接口
	LCD_Init();			   	//初始化LCD   
 	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(60,50,200,16,16,"Mini STM32");	
	LCD_ShowString(60,70,200,16,16,"Mouse TEST");	
	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,200,16,16,"2014/3/12");		  
 	while(Init_Mouse())	//检查鼠标是否在位.	
	{
		LCD_ShowString(60,130,200,16,16,"Mouse Error");
		delay_ms(400);
		LCD_Fill(60,130,239,130+16,WHITE);	 
		delay_ms(100);
	}								   
	LCD_ShowString(60,130,200,16,16,"Mouse OK");
 	LCD_ShowString(60,150,200,16,16,"Mouse ID:");
 	LCD_ShowNum(132,150,MOUSE_ID,3,16);//填充模式

	POINT_COLOR=BLUE;
 	LCD_ShowString(30,170,200,16,16,"BUF[0]:");
	LCD_ShowString(30,186,200,16,16,"BUF[1]:");
	LCD_ShowString(30,202,200,16,16,"BUF[2]:"); 
	if(MOUSE_ID==3)LCD_ShowString(30,218,200,16,16,"BUF[3]:"); 

	LCD_ShowString(90+30,170,200,16,16,"X  POS:");
	LCD_ShowString(90+30,186,200,16,16,"Y  POS:");
	LCD_ShowString(90+30,202,200,16,16,"Z  POS:"); 
	if(MOUSE_ID==3)LCD_ShowString(90+30,218,200,16,16,"BUTTON:"); 
	t=0;
	while(1)
	{
		if(PS2_Status&0x80)//得到了一次数据
		{		  
			LCD_ShowNum(56+30,170,PS2_DATA_BUF[0],3,16);//填充模式
			LCD_ShowNum(56+30,186,PS2_DATA_BUF[1],3,16);//填充模式
			LCD_ShowNum(56+30,202,PS2_DATA_BUF[2],3,16);//填充模式
			if(MOUSE_ID==3)LCD_ShowNum(56+30,218,PS2_DATA_BUF[3],3,16);//填充模式

			Mouse_Data_Pro();//处理数据

			Mouse_Show_Pos(146+30,170,MouseX.x_pos);				//X坐标
			Mouse_Show_Pos(146+30,186,MouseX.y_pos);				//Y坐标
			if(MOUSE_ID==3)Mouse_Show_Pos(146+30,202,MouseX.z_pos);	//滚轮位置

		    if(MouseX.bt_mask&0x01)LCD_ShowString(146+30,218,200,16,16,"LEFT"); 
			else LCD_ShowString(146+30,218,200,16,16,"    "); 
		    if(MouseX.bt_mask&0x02)LCD_ShowString(146+30,234,200,16,16,"RIGHT"); 
			else LCD_ShowString(146+30,234,200,16,16,"     "); 				    
			if(MouseX.bt_mask&0x04)LCD_ShowString(146+30,250,200,16,16,"MIDDLE"); 
			else LCD_ShowString(146+30,250,200,16,16,"      ");   		 
			PS2_Status=MOUSE;
			PS2_En_Data_Report();//使能数据报告
		}else if(PS2_Status&0x40)
		{
			errcnt++;
			PS2_Status=MOUSE;
			LCD_ShowNum(86+30,234,errcnt,3,16);//填充模式
		}
		t++;
		delay_ms(1);
		if(t==200)
		{
			t=0;
			LED0=!LED0;
		}
	} 
}

















