#ifndef _12864_
#define _12864_
#include "reg51.h"
#include "intrins.h"
sbit LCD12864_RS=P2^5;
sbit LCD12864_RW=P2^6;
sbit LCD12864_E =P2^7;
sbit LCD12864_PSB=P2^4;
sfr  LCD12864_DB=0x80;
sfr  P0M1=0x93;
sfr  P0M0=0x94;
sfr  P2M1=0x95;
sfr  P2M0=0x96;
void lcdwait();
void lcdwritecmd(unsigned char cmd);
void lcdwritedata(unsigned char dat);
void lcdinit();
void lcdsetcursor(unsigned char x, unsigned char y);
void lcdshowstr(unsigned char x, unsigned char y,
	              unsigned char *str);
void drawpoint(unsigned char y[]);
#endif