/*----------------------------------------------
		STM32 SSD1963彩屏配套字库
 说明: 通过这个自建字库可以学习到一种数据结构的
       思路,就是通过建立索引来进行字库的查找.
       如需增加字库则按照既定规则进行添加即可,
	   请记得修改WORD_NUMBER,索引公式
	   if((GBKSmall[i].InnerCode[0]==chn[0]) && (GBKSmall[i].InnerCode[1]==chn[1]))
 时间: 2013年8月18日       BoX编写
----------------------------------------------*/
#ifndef __GBK_SMALL_H
#define __GBK_SMALL_H

/*使用小字库*/
#define SMALL_CHN_LIB	 

/*本字库有多少个字*/
#define WORD_NUMBER 16

typedef struct         //汉字字模数据结构 
{
   unsigned char  InnerCode[2]; //汉字内码索引	
   unsigned char  ArrayCode[32];//点阵码数据 
}GBK_Small;

GBK_Small GBKSmall[] = 
{

/*--  文字:  吴  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
"吴",0x00,0x00,0x1F,0xF0,0x10,0x10,0x10,0x10,0x1F,0xF0,0x00,0x00,0x00,0x00,0x3F,0xF8,
0x01,0x00,0x01,0x00,0xFF,0xFE,0x02,0x80,0x04,0x40,0x08,0x20,0x30,0x18,0xC0,0x06,

/*--  文字:  思  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
"思",0x00,0x00,0x3F,0xF8,0x21,0x08,0x21,0x08,0x3F,0xF8,0x21,0x08,0x21,0x08,0x3F,0xF8,
0x20,0x08,0x01,0x00,0x08,0x88,0x48,0x84,0x48,0x12,0x48,0x12,0x87,0xF0,0x00,0x00,

/*--  文字:  远  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
"远",0x00,0x00,0x23,0xF8,0x10,0x00,0x10,0x00,0x00,0x00,0x07,0xFC,0xF1,0x20,0x11,0x20,
0x11,0x20,0x11,0x20,0x11,0x24,0x12,0x24,0x12,0x24,0x14,0x1C,0x28,0x00,0x47,0xFE,
/*--  文字:  初  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
"初",0x20,0x00,0x10,0x00,0x01,0xFC,0xFC,0x44,0x08,0x44,0x10,0x44,0x10,0x44,0x34,0x44,
0x58,0x44,0x94,0x44,0x14,0x44,0x10,0x84,0x10,0x84,0x11,0x04,0x12,0x28,0x14,0x10,

/*--  文字:  始  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
"始",0x10,0x20,0x10,0x20,0x10,0x20,0x10,0x40,0xFC,0x48,0x24,0x84,0x25,0xFE,0x24,0x82,
0x24,0x00,0x48,0xFC,0x28,0x84,0x10,0x84,0x28,0x84,0x44,0x84,0x80,0xFC,0x00,0x84,

/*--  文字:  化  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
"化",0x08,0x80,0x08,0x80,0x08,0x84,0x10,0x88,0x10,0x90,0x30,0xA0,0x30,0xC0,0x50,0x80,
0x91,0x80,0x12,0x80,0x14,0x80,0x10,0x82,0x10,0x82,0x10,0x82,0x10,0x7E,0x10,0x00,

/*--  文字:  成  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
"成",0x00,0x50,0x00,0x48,0x00,0x40,0x3F,0xFE,0x20,0x40,0x20,0x40,0x20,0x44,0x3E,0x44,
0x22,0x44,0x22,0x28,0x22,0x28,0x22,0x12,0x2A,0x32,0x44,0x4A,0x40,0x86,0x81,0x02,

/*--  文字:  功  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
"功",0x00,0x40,0x00,0x40,0x00,0x40,0xFE,0x40,0x11,0xFC,0x10,0x44,0x10,0x44,0x10,0x44,
0x10,0x44,0x10,0x84,0x10,0x84,0x1E,0x84,0xF1,0x04,0x41,0x04,0x02,0x28,0x04,0x10,
/*--  文字:  液  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
"液",0x00,0x80,0x20,0x40,0x17,0xFE,0x11,0x20,0x81,0x20,0x42,0x3C,0x42,0x44,0x16,0x64,
0x12,0x94,0x23,0x48,0xE2,0x48,0x22,0x30,0x22,0x20,0x22,0x50,0x22,0x88,0x03,0x06,

/*--  文字:  晶  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
"晶",0x0F,0xE0,0x08,0x20,0x08,0x20,0x0F,0xE0,0x08,0x20,0x08,0x20,0x0F,0xE0,0x00,0x00,
0x7E,0xFC,0x42,0x84,0x42,0x84,0x7E,0xFC,0x42,0x84,0x42,0x84,0x7E,0xFC,0x42,0x84




};

#endif
