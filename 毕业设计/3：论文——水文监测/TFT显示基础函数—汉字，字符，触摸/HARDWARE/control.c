#include "control.h"
#include "text.h"
#include "24l01.h"
#include "lcd.h"
#include "rc522.h"
#include "w25q128.h" 
#include "at24c02.h" 

extern u8 tmp_buf[33];
extern unsigned char SN[4]; //卡号
extern unsigned char NEW_SN[4]; //卡号
extern unsigned char OLD_SN[4]; //卡号
u8 wd=0;
u8 sd=0;
u16 tds=0;
u16 distend_1;
u8 distend_0;
extern u8 door;
u16 temperature;
void Nrf_communicate(void)
{
	u8 t;
		if(NRF24L01_RxPacket(tmp_buf)==0)//一旦接收到信息,则显示出来.
	{
		for(t=1;t<31;t++)
		{
			tmp_buf[t]=tmp_buf[t]-48;
		}
		wd=tmp_buf[1]*10+tmp_buf[2];
		sd=tmp_buf[3]*10+tmp_buf[4];
		tds=tmp_buf[5]*100+tmp_buf[6]*10+tmp_buf[7];
//		temperature=tmp_buf[8]*100+tmp_buf[9]*10+tmp_buf[10];
		distend_1=tmp_buf[11]*10+tmp_buf[12];
		distend_0=tmp_buf[13];
		SN[0]=tmp_buf[17]*100+tmp_buf[18]*10+tmp_buf[19];
		SN[1]=tmp_buf[20]*100+tmp_buf[21]*10+tmp_buf[22];
		SN[2]=tmp_buf[23]*100+tmp_buf[24]*10+tmp_buf[25];
		SN[3]=tmp_buf[26]*100+tmp_buf[27]*10+tmp_buf[28];
	}	 			    	
}

void use_control(void)
{
//	u8 t;
	Nrf_communicate();
	if(tmp_buf[0]=='D')
	{
	POINT_COLOR=BLUE;
	Show_Str(72,5,120,24,"收到数据",24,0);
	display();
	}
	else
	{
	POINT_COLOR=BLUE;
	Show_Str(72,5,120,24,"没有数据",24,0);
	}
}

void display(void)
{
	u8 t;
	POINT_COLOR=BLUE;
	Show_Str(5,30,168,24,"本次检验员ID：",24,0);
	Show_Str(5,80,168,24,"上次检验员ID：",24,0);
	POINT_COLOR=RED;
	Show_Str(5,130,120,24,"水质TDS：",24,0);
	Show_Str(5,160,120,24,"环境温度：",24,0);
	Show_Str(5,190,120,24,"环境湿度：",24,0);
	Show_Str(5,220,120,24,"液位高度：",24,0);
	
	LCD_ShowString(180,220,24,24,24,"CM");
	Show_Str(5,250,120,24,"水体温度：",24,0);
	
	Show_Str(5,280,120,24,"下雨预警：",24,0);
	POINT_COLOR=BLACK;
	LCD_DrawRectangle(4,29,236,129);
	LCD_DrawRectangle(3,29,237,129);
	LCD_DrawLine(4,79,236,79);
	id_scan();

	
	for(t=0;t<4;t++)
	{
		LCD_ShowxNum(20+50*t,55,NEW_SN[t],3,24,0);
	}
		for(t=0;t<4;t++)
	{
		LCD_ShowxNum(20+50*t,105,OLD_SN[t],3,24,0);
	}
	LCD_ShowxNum(125,130,tds,3,24,0);
	POINT_COLOR=BLUE;
	if(tds<200)
	{
		Show_Str(165,135,75,16,"可以饮用",16,0);
	}
		else 
	{
		Show_Str(165,135,75,16,"不可饮用",16,0);
	}
	POINT_COLOR=BLACK;
	LCD_ShowChar(150,220,'.',24,0);
	LCD_ShowChar(150,250,'.',24,0);
	LCD_ShowxNum(125,160,wd,2,24,0);
	LCD_ShowxNum(125,190,sd,2,24,0);
	LCD_ShowxNum(125,220,distend_1,2,24,0);
	LCD_ShowxNum(165,220,distend_0,1,24,0);
	
	LCD_ShowxNum(125,250,tmp_buf[8]*10+tmp_buf[9],2,24,0);
	LCD_ShowxNum(165,250,tmp_buf[10],1,24,0);
	if(tmp_buf[14]==1)
	{
		Show_Str(150,280,120,24,"有雨",24,0);
	}
	else
	{
		Show_Str(150,280,120,24,"无雨",24,0);
	}
	
}

void Key_init(void)
{
	RCC->APB2ENR|=1<<2;    //使能PORTa时钟
	GPIOA->CRH&=0XFFF0FFFF; 
	GPIOA->CRH|=0X00080000;   	 
	GPIOA->ODR|=1<<12;      //PB.5 输出高	
}
void id_scan(void)
{
	u8 t;
		old_id_read();	
	if(SN[0]!=0&&SN[1]!=0)  //确定有人刷卡了
	{
		if(SN[0]!=NEW_SN[0]||SN[1]!=NEW_SN[1]||SN[2]!=NEW_SN[2]||SN[3]!=NEW_SN[3])   //这次卡号和上次的不一样  则将上次卡号存储  并将这次卡号传递给中间卡号
		{
			if(NEW_SN[0]!=0&&NEW_SN[1]!=0)
			{
										AT24CXX_WriteOneByte(60,NEW_SN[0]/100);
			AT24CXX_WriteOneByte(61,(NEW_SN[0]%100)/10);
			AT24CXX_WriteOneByte(62,NEW_SN[0]%10);
						AT24CXX_WriteOneByte(63,NEW_SN[1]/100);
			AT24CXX_WriteOneByte(64,(NEW_SN[1]%100)/10);
			AT24CXX_WriteOneByte(65,NEW_SN[1]%10);
						AT24CXX_WriteOneByte(66,NEW_SN[2]/100);
			AT24CXX_WriteOneByte(67,(NEW_SN[2]%100)/10);
			AT24CXX_WriteOneByte(68,NEW_SN[2]%10);
						AT24CXX_WriteOneByte(69,NEW_SN[3]/100);
			AT24CXX_WriteOneByte(70,(NEW_SN[3]%100)/10);
			AT24CXX_WriteOneByte(71,NEW_SN[3]%10);
			}
			for(t=0;t<4;t++)    //保持完数据后 传递数据
		{
			NEW_SN[t]=SN[t];
		}
		}


	}
	
}
void old_id_read(void)
{
	OLD_SN[0]=AT24CXX_ReadOneByte(60)*100+AT24CXX_ReadOneByte(61)*10+AT24CXX_ReadOneByte(62);
	OLD_SN[1]=AT24CXX_ReadOneByte(63)*100+AT24CXX_ReadOneByte(64)*10+AT24CXX_ReadOneByte(65);
	OLD_SN[2]=AT24CXX_ReadOneByte(66)*100+AT24CXX_ReadOneByte(67)*10+AT24CXX_ReadOneByte(68);
	OLD_SN[3]=AT24CXX_ReadOneByte(69)*100+AT24CXX_ReadOneByte(70)*10+AT24CXX_ReadOneByte(71);
}



