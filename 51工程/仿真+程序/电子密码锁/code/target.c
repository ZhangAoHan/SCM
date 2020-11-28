#define TARGET_GLOBAL 1
#include "target.h"
#include "dot.h"
void target_init(void)
{
  Lcd_Initial(); //lcd初始化
  key_init();	 //按键扫描初始化
}
/**********************************
*程序名称：displayFramOne(void)
*程序功能：显示第一个操作界面
*程序入口：无
*程序出口：无
*说明：显示“欢迎使用”
**********************************/
void displayFramOne(void)
{
  Lcd_Clear();
  Lcd_Character_16X16(1,2,32,fram_one[0]);
  Lcd_Character_16X16(1,2,48,fram_one[1]);
  Lcd_Character_16X16(1,2,64,fram_one[2]);
  Lcd_Character_16X16(1,2,80,fram_one[3]);
}
/**********************************
*程序名称：displayFramTwo(bit posBit)
*程序功能：显示第二个操作界面
*程序入口：posBit,光标所在位置
*程序出口：无
*说明：posbit=0,第一行黑白显示
	   posbit=1,第二行黑白显示
	   显示“A:进入系统”
	       “B:设置密码”
**********************************/           
void displayFramTwo(bit posBit)
{
  uchar i;
  uchar temp;
  Lcd_Clear();
  Lcd_Character_16X8(1,8,0,other_dot[0]);
  Lcd_Character_16X8(1,8,8,other_dot[2]);
  Lcd_Character_16X8(1,60,0,other_dot[1]);
  Lcd_Character_16X8(1,60,8,other_dot[2]);
  temp=16;
  for(i=0;i<4;i++)
  {
    if(posBit==0)
       Lcd_Character_16X16(0,8,temp,fram_two[i]);
	else
	   Lcd_Character_16X16(1,8,temp,fram_two[i]);
	temp+=16;
  }
  temp=16;
  for(i=0;i<4;i++)
  {
    if(posBit==1)
       Lcd_Character_16X16(0,60,temp,fram_two[i+4]);
	else
	   Lcd_Character_16X16(1,60,temp,fram_two[i+4]);
	temp+=16;
  } 
}
/**********************************
*程序名称：displayFramThree(void)
*程序功能：显示第三个操作界面
*程序入口：无
*程序出口：无
*说明：显示“请输入密码”
**********************************/           
void displayFramThree(void)
{
  uchar temp,i;
  temp=0;
  Lcd_Clear();
  for(i=0;i<5;i++)
  {
    Lcd_Character_16X16(1,10,temp,fram_three[i]);
	temp+=16;
  }
  Lcd_Character_16X8(1,10,80,other_dot[2]); 
  
}
/**********************************
*程序名称：displayFramFour(void)
*程序功能：显示第四个操作界面
*程序入口：无
*程序出口：无
*说明：显示“请设置密码”
**********************************/      
void displayFramFour(void)
{
  uchar temp,i;
  Lcd_Clear();
  Lcd_Character_16X16(1,10,0,fram_three[0]);
  temp=16;
  for(i=0;i<4;i++)
  {
    Lcd_Character_16X16(1,10,temp,fram_two[i+4]);
    temp+=16;
  }
  Lcd_Character_16X8(1,10,80,other_dot[2]);
}
/**********************************
*程序名称：displayFramFour(void)
*程序功能：显示第五个操作界面
*程序入口：无
*程序出口：无
*说明：显示“恭喜你,答对了”
**********************************/
void displayFramFive(void)
{
  uchar i,temp;
  Lcd_Clear();
  temp=0;
  for(i=0;i<3;i++)
  {
    Lcd_Character_16X16(1,10,temp,fram_five[i]);
	temp+=16;
  }
  Lcd_Character_16X8(1,10,temp,other_dot[4]);
  temp+=8;
  for(i=0;i<3;i++)
  {
    Lcd_Character_16X16(1,10,temp,fram_five[i+3]);
	temp+=16;
  }

}
/****************************************************
*程序名称：displayMima(uchar *s,uchar len,uchar mode)
*程序功能：显示密码输入
*程序入口：s-密码数组指针;len-已输密码长度;mode-为要
显密码的类型,0x01为解密输入,0x02为密码设置输入
*程序出口：无
*****************************************************/           
void displayMima(uchar *s,uchar len,uchar mode)
{
  uchar temp,i;
  if(mode==0x01)   //解密输入,此时从10行,88列开始显示len个*
  {
    temp=88;
    for(i=0;i<len;i++)
	{
	  Lcd_Character_16X8(1,10,temp,other_dot[3]);
	  temp+=8;
	}
	 
  }
  else           //密码设置,此时从10行,88列开始显示s[0]~s[len]
  {
    temp=88;
    for(i=0;i<len;i++)
	{
	  Lcd_Character_16X8(1,10,temp,digital_dot[s[i]]);
	  temp+=8;
	}
  }
}