/*****************************************************
* 文件名称：12864LCD.h							   
* 功能：LCD驱动函数
* 当前版本：1.0
* 作者：YuanDong
* 完成日期：2009年7月18日
******************************************************/
#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int

sbit L_SCK =P1^1;
sbit L_SI =P1^2;
sbit L_EN =P1^0;
sbit L_PS= P1^3;
//#define L_RST T1

#define LOW 0 
#define HIGH 1 

/*********************************************************
* 函数名称：unsigned char lcd_readcmd(void)
* 功    能：读忙
* 入口参数：无
* 出口参数：无
*********************************************************/
unsigned char lcd_readcmd(void)
{
    register unsigned char i;
    register unsigned char temp;
    L_EN = LOW;
    L_SI = LOW;
    L_SCK = LOW;
    L_EN = HIGH;

    //    11111 100
    L_SI = HIGH;
    for (i=0;i<5;i++){L_SCK = HIGH;L_SCK = LOW;}
    L_SI = HIGH;
    L_SCK = HIGH;L_SCK = LOW;
    L_SI = LOW;
    L_SCK = HIGH;L_SCK = LOW;
    L_SI = LOW;           
    L_SCK = HIGH;L_SCK = LOW;

    temp = 0;
    for (i=0;i<8;i++)
    {
        L_SCK = HIGH;
        temp <<=1;
        temp |= L_SI;
        L_SCK = LOW;
    }
    temp >>= 4;
    for (i=0;i<4;i++)
    {
        L_SCK = HIGH;
        temp <<=1;
        temp |= L_SI;
        L_SCK = LOW;
    }
    for (i=0;i<4;i++)
    {
        L_SCK = HIGH;L_SCK = LOW;
    }

    L_EN = LOW;
    L_SI = LOW;
    L_SCK = LOW;
    return temp;
}

/*********************************************************
* 函数名称：void lcd_writecmd(unsigned char lcddata)
* 功    能：写指令
* 入口参数：unsigned char lcddata
* 出口参数：无
*********************************************************/
void lcd_writecmd(unsigned char lcddata)
{
    unsigned char lcdopt;
    register unsigned char i;
    register unsigned char temp;
    EA=0;
    L_EN = LOW;
    L_SI = LOW;
    L_SCK = LOW;
    L_EN = HIGH;
    //    11111 000
    L_SI = HIGH;
    for (i=0;i<5;i++)//写前五位1
    {
     L_SCK = HIGH;L_SCK = LOW;
    }
    L_SI = LOW;   //写如后三位0
    L_SCK = HIGH;
    L_SCK = LOW;
    L_SI = LOW;
    L_SCK = HIGH;
    L_SCK = LOW;
    L_SI = LOW;
    L_SCK = HIGH;
    L_SCK = LOW;
    //    HHHH000
    temp = lcddata&0xf0;
    for (i=0;i<8;i++)
    {
     L_SI = (temp&0x80)?HIGH:LOW;
     temp <<=1;
     L_SCK = HIGH;
     L_SCK = LOW;
    }
    //    LLLL0000
    temp = (lcddata<<4)&0xf0;
    for (i=0;i<8;i++)
    {
     L_SI = (temp&0x80)?HIGH:LOW;
     temp <<=1;
     L_SCK = HIGH;L_SCK = LOW;
    }
    L_EN = LOW;
    L_SI = LOW;
    L_SCK = LOW;
    lcdopt = 0;
    do
    {
     lcdopt = lcd_readcmd();
    }while (lcdopt&0x80);
    EA=1;
}

/*********************************************************
* 函数名称：void lcd_writedata(unsigned char lcddata)
* 功    能：写数据
* 入口参数：unsigned char lcddata
* 出口参数：无
*********************************************************/
void lcd_writedata(unsigned char lcddata)
{
    register unsigned char temp;
    register unsigned char i;
    unsigned char lcdopt;
    EA=0;
    L_EN = LOW;
    L_SI = LOW;
    L_SCK = LOW;
    L_EN = HIGH;
    //    11111 010,写数据
    L_SI = HIGH;
    for (i=0;i<5;i++){L_SCK = HIGH;L_SCK = LOW;}
    L_SI = LOW;
    L_SCK = HIGH;L_SCK = LOW;
    L_SI = HIGH;
    L_SCK = HIGH;L_SCK = LOW;
    L_SI = LOW;
    L_SCK = HIGH;L_SCK = LOW;
    //    HHHH0000,写高四位
    temp = (lcddata)&0xf0;
    for (i=0;i<8;i++)
    {
        L_SI = (temp&0x80)?HIGH:LOW;
        temp <<=1;
        L_SCK = HIGH;L_SCK = LOW;
    }
    //    LLLL0000,写低四位
    temp = ((lcddata)<<4)&0xf0;
    for (i=0;i<8;i++)
    {
        L_SI = (temp&0x80)?HIGH:LOW;
        temp <<=1;
        L_SCK = HIGH;L_SCK = LOW;
    }
    L_EN = LOW;
    L_SI = LOW;
    L_SCK = LOW;
    lcdopt = 0;
    do
    {
        lcdopt = lcd_readcmd();
    }while (lcdopt&0x80); //判断忙
    EA=1;
}
 
/*********************************************************
* 函数名称：void lcd_cmd(unsigned char cmd,unsigned char opt)
* 功    能：LCD写指令
* 入口参数：unsigned char cmd,unsigned char opt
* 出口参数：无
*********************************************************/
void lcd_cmd(unsigned char cmd,unsigned char opt)
{
 switch (cmd)
 {
  //基本指令     //扩展指令
  case 0:lcd_writecmd(0x01);break;                //清除                 //待命模式
  case 1:lcd_writecmd(0x02);break;                //位址归位             //卷动位址或RAM位址选择
  case 2:opt&=0x03;lcd_writecmd(0x04|opt);break;  //进入点设定           //反白选择
  case 3:opt&=0x07;lcd_writecmd(0x08|opt);break;  //显示状态             //睡眠模式
  case 4:opt&=0x0f;lcd_writecmd(0x10|opt);break;  //游标或显示移位控制   //扩充功能设定
  case 5:opt&=0x1f;lcd_writecmd(0x20|opt);break;  //功能设定             //设定ICONRAM位址或卷动位址
  case 6:opt&=0x3f;lcd_writecmd(0x40|opt);break;  //CGRAM位址            //设定绘图RAM位址
  case 7:opt&=0x3f;lcd_writecmd(0x80|opt);break;  //DDRAM位址
    }
}
	
/*********************************************************
* 函数名称：void lcd_home(void)
* 功    能：LCD清屏
* 入口参数：无
* 出口参数：无
*********************************************************/
void lcd_home(void)
{
    lcd_cmd(1,0);
    lcd_cmd(2,0x02);
//    os_wait2(K_TMO,1);
}
	
/*********************************************************
* 函数名称：void lcd_init(void)
* 功    能：LCD初始化
* 入口参数：无
* 出口参数：无
*********************************************************/
void lcd_init(void)
{
 L_PS = 0;
 lcd_cmd(5,0x10);
 lcd_cmd(5,0x10);
 lcd_cmd(3,0x04);
 lcd_cmd(2,0x02);
 lcd_cmd(0,0);
//    os_wait2(K_TMO,1);
}  
/*********************************************************
* 函数名称：void lcd_writestr(unsigned char l_line,unsigned char l_site,unsigned char * words)
* 功    能：写入字符串
* 入口参数：unsigned char l_line,unsigned char l_site,unsigned char * words
* 出口参数：无
*********************************************************/
void lcd_writestr(unsigned char l_line,unsigned char l_site,unsigned char * words)
{
//    l_line:行0-3; l_site:列 0-7; words:中英字符
 unsigned char c;
 c = 0; 
 l_site = l_site % 8;                  //使列在0-7范围
 if(l_line>1)                          //若行=2,3
 {
  l_line = l_line % 2;                 //2行变0行,3行变1行
  l_site = l_site + 8;                 //列加8
 }
 l_site = (l_line<<4) + l_site;        //行*16+列
 lcd_cmd(7,l_site);                    //DDRAM地址
 
 while(*words != 0)                    //写字符
 {
  unsigned char tempdata;
  tempdata = *words;
  lcd_writedata(tempdata);
  words++;
  l_site++;
  c++;
 }
 if (c%2)                              //写完数据,若最后一个字符列号是奇数则补空格
 {
 lcd_writedata(0x20);
 }
}
 
/*********************************************************
* 函数名称：void lcd_writechar(unsigned char words1,uchar words2,uchar words3,uchar words4)
* 功    能：写入单个字符
* 入口参数：unsigned char words1,uchar words2,uchar words3,uchar words4
* 出口参数：无
*********************************************************/
void lcd_writechar(unsigned char words1,uchar words2,uchar words3,uchar words4)
{
//    l_line:行0-3; l_site:列 0-7; words:中英字符
 /*unsigned char tempdata;
 l_site = l_site % 8;                  //使列在0-7范围
 if(l_line>1)                          //若行=2,3(即在3,4行)
 {
  l_line = l_line % 2;                 //3行变1行,4行变2行
  l_site = l_site + 8;                 //列加8
 }
 l_site = (l_line<<4) + l_site;    */    //行*16+列
 lcd_cmd(7,0x1a);                    //DDRAM地址
 
  lcd_writedata(words1);
  lcd_writedata(words2);
  lcd_writedata(words3);
  lcd_writedata(words4);

}
 
/*********************************************************
* 函数名称：void delay(void)
* 功    能：延时
* 入口参数：无
* 出口参数：无
*********************************************************/
void delay(void)
{
  unsigned char a,b;
  for(a=250;a>0;a--)
   for(b=250;b>0;b--);
}