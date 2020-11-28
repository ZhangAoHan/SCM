#include "delay.h"
#include "sys.h"
#include "oled.h"
#include "bmp.h"
#include "led.h"
#include "key.h"

u8 KEY=0;
u8 MM[3]={0,0,0};
u8 mm[3]={0,0,0};
//u8 flag=0;
u8 Flag=0;

void Display(u8 x);
void MiMa(void) ;
void mima(void) ;
void Led_Init(u8 x);

 int main(void)
 {	
	
	 delay_init();	    	 //延时函数初始化	 
	 OLED_Init();			//初始化OLED  
	 OLED_Clear(); 
	 led_init();
	  beep=0;
	 key_init();
	 Display(0);
	 Led_Init(3);
	 delay_ms(2000);

	while(1) 
	{		
		if(Flag==0)
		{
		Display(1);
        MiMa();
		OLED_Clear();
		}
   if(Flag==1)
   {
	   Display(2);
	    mima();   
	 if(mm[0]==MM[0]&&mm[1]==MM[1]&&mm[2]==MM[2]) 
		{
		Led_Init(3);
		OLED_Clear();
		Display(3);
		delay_ms(1000);
		Display(5);
	while(KEY==0) Key_Scan();//等待按键按下
		if(KEY==11) {OLED_Clear();Flag=0;KEY=0;}  //确认修改密码
		if(KEY==12) {OLED_Clear();Flag=1;KEY=0;}
			
		}   //密码输入正确
    else {Led_Init(3);OLED_Clear();Display(4);beep=1;delay_ms(1000);beep=0;}   //密码输入错误
   }	   
	}	  
	
}
void Display(u8 x)
{
	switch(x)
	{
	case 0:
	OLED_ShowCHinese(16,2,0);
	OLED_ShowCHinese(32,2,1);
	OLED_ShowCHinese(48,2,2);
	OLED_ShowCHinese(64,2,3);
	OLED_ShowCHinese(80,2,4);
	break;  //电子密码锁
	case 1:
	OLED_ShowCHinese(16,2,5);
	OLED_ShowCHinese(32,2,6);
	OLED_ShowCHinese(48,2,7);
	OLED_ShowCHinese(64,2,8);
	OLED_ShowCHinese(80,2,9);
	
	OLED_ShowCHinese(0,4,8);
	OLED_ShowCHinese(16,4,9);
	OLED_ShowChar(32,4,':');
	break; //请设置密码
	case 2:
	OLED_ShowCHinese(16,2,5);
	OLED_ShowCHinese(32,2,10);
	OLED_ShowCHinese(48,2,11);
	OLED_ShowCHinese(64,2,8);
	OLED_ShowCHinese(80,2,9);
	
	OLED_ShowCHinese(0,4,8);
	OLED_ShowCHinese(16,4,9);
	OLED_ShowChar(32,4,':');
	break; //请输入密码
		case 3:
	OLED_ShowCHinese(0,6,8);
	OLED_ShowCHinese(16,6,9);
	OLED_ShowCHinese(32,6,12);
	OLED_ShowCHinese(48,6,13);
	break; //密码正确
			case 4:
	OLED_ShowCHinese(0,6,8);
	OLED_ShowCHinese(16,6,9);
	OLED_ShowCHinese(32,6,14);
	OLED_ShowCHinese(48,6,15);
	break; //密码错误		
	case 5:
	OLED_ShowCHinese(0,0,17);	
	OLED_ShowCHinese(16,0,8);
	OLED_ShowCHinese(32,0,9);
	OLED_ShowCHinese(48,0,18);
	OLED_ShowChar(64,0,':');
	OLED_ShowString(72,0,"KEY0");
	OLED_ShowCHinese(0,2,19);
	OLED_ShowCHinese(16,2,20);
	OLED_ShowCHinese(32,2,18);
	OLED_ShowChar(48,2,':');
	OLED_ShowString(56,2,"KEY1");
	break; //修改密码
			
	}
}
void MiMa(void)  //取密码
{
	u8 i;
	for(i=0;i<3;i++)
	{
	while(KEY==0) Key_Scan();//等待按键按下
	MM[i]=KEY-1;
	OLED_ShowNum(40+i*8,4,KEY-1,1,16);
	KEY=0;
    delay_ms(300);	
		
}
		Flag=1;   //取密码完成
}
void mima(void)  //输入密码
{
	u8 i;
	for(i=0;i<3;i++)
	{
	while(KEY==0) Key_Scan();//等待按键按下
	mm[i]=KEY-1;
	OLED_ShowNum(40+i*8,4,KEY-1,1,16);
	Led_Init(i);
	KEY=0;
    delay_ms(300);						
}		
}
void Led_Init(u8 x)
{
	switch(x)
	{
		case 0:led0=0;break;
		case 1:led1=0;break;
		case 2:led2=0;break;
		case 3:led0=1;led1=1;led2=1;break;
	}
}

