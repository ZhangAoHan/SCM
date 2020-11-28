#include "control.h"   
u8 x;
void TFT_S_Display(void)
{
	POINT_COLOR=RED;       		  
	Show_Str(48,5,144,24,"距离测量系统",24,0);
	POINT_COLOR=BLACK;	
	Show_Str(10,50,108,24,"十位数据：",24,0);	
	Show_Str(10,80,108,24,"个位数据：",24,0);	
	Show_Str(10,110,108,24,"运算结果：",24,0);
	Show_Str(64,240,72,24,"指示灯",24,0);
}

void TFT_Display(void)
{
	u8 i=0;
	u8 j=0;
	for(j=0;j<30;j++)
	{
	Read_Distane();	     
	m1+=Distance/10;
	m2+=Distance%10;	
	}
	m1=m1/30;
	m2=m2/30;
	if(m1<10&&m1>5) i=1;
	if(m1>=11) i=0;
	if(m1<5) i=2;
	if(m1<25&&m1>5)
	{
		Clear_ss(140,200,240,230);
	}
	if(m1<5)
	{
		m1=m2=0;
		Show_Str(140,200,100,24,"距离过低",12,0);
	}
		if(m1>25) 
	{
		m1=m2=0;
		Show_Str(140,200,100,24,"安全距离",12,0);
	}
	POINT_COLOR=BLUE;	
	gui_fill_circle	(15,279,15,BLUE);
	LCD_DrawLine(0,279,240,279);
	gui_fill_circle	(125,279,5,RED);
	gui_fill_circle	(235,279,5,BRRED);
	LCD_ShowString(125,286,48,12,12,"10cm");
	LCD_ShowString(192,286,48,12,12,"20cm");
	LCD_ShowxNum(120,50,m1,4,24,0);
	LCD_ShowxNum(120,80,m2,4,24,0);
	LCD_ShowxNum(120,110,m1,3,24,0);
	LCD_ShowChar(156,110,'.',24,0);	
	LCD_ShowxNum(168,110,m2,1,24,0);
	LCD_ShowString(182,110,24,24,24,"cm");
	x=((m2/10+m1)/20)*240+5;
	if(i==0) gui_fill_circle	(100,200,30,GREEN);
	if(i==1) gui_fill_circle	(100,200,30,RED);
	if(i==2) gui_fill_circle	(100,200,30,GRAY);
}

void Clear_ss(u8 x,u16 y,u8 x1,u16 y1)
{
	LCD_Fill(x,y,x1,y1,WHITE);
}
