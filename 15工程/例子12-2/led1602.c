#include "led1602.h"
void lcdwait()
{
	LCD1602_DB=0xFF;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	LCD1602_RS=0;
	LCD1602_RW=1;
	LCD1602_E=1;
	while(LCD1602_DB & 0x80);
  LCD1602_E=0;
}

void lcdwritecmd(unsigned char cmd)
{
	lcdwait();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	LCD1602_RS=0;
	LCD1602_RW=0;
	LCD1602_DB=cmd;
	LCD1602_E=1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	LCD1602_E=0;
}

void lcdwritedata(unsigned char dat)
{
	lcdwait();
  _nop_();
	_nop_();
	_nop_();
	_nop_();
	LCD1602_RS=1;
	LCD1602_RW=0;
	LCD1602_DB=dat;
	LCD1602_E=1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	LCD1602_E=0;
}

void lcdinit()
{
	lcdwritecmd(0x38);
	lcdwritecmd(0x0c);
	lcdwritecmd(0x06);
	lcdwritecmd(0x01);
}

void lcdsetcursor(unsigned char x, unsigned char y)
{
	unsigned char address;
	if(y==0)
		address=0x00+x;
	else
		address=0x40+x;
	lcdwritecmd(address|0x80);
}

void lcdshowstr(unsigned char x, unsigned char y,
	              unsigned char *str)
{
	lcdsetcursor(x,y);
	while((*str)!='\0') 
	{
		 lcdwritedata(*str);
		 str++;
	}
}									