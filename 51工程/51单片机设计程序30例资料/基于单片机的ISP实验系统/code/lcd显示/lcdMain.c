/*********************************************************
*文件名称：lcdMain.c
*文件功能：测试实验板上lcd显示模块,此lcd为带汉字库的12864
*版本：	   V0.0.1
*作者：	   yd
*时间：	   09.07.22
*说明：该lcd显示屏的数据端口是通过8255扩展的，此处测试程序
把8255的端口全选择在方式0，即无条件数据传送
*********************************************************/
#include <AT89X52.h>
#include <absacc.h>
#include <intrins.h>
#define uchar unsigned char
#define uint  unsigned int
//--------------------8255端口操作定义---------------------
#define CHOOSE8255()  {P2_5=0;P2_6=1;P2_7=0;}   //选择8255
#define PA_ADDRESS        0x00    //片选8255时，PA端口地址 
#define PB_ADDRESS	      0x01    //片选8255时，PB端口地址
#define PC_ADDRESS		  0x02    //片选8255时，PC端口地址
#define COMMAND_ADDRESS   0x03    //片选8255时，控制端口地址
//--------------------lcd控制端口定义----------------------
#define LCD_RS   P1_0  
#define LCD_RW   P1_1
#define LCD_E    P1_2
//---------------------------------------------------------
	/*屏幕XY轴定义*/
	#define Line1	 0x80
	#define Line2	 0x90
	#define Line3	 0x88
	#define Line4	 0x98
	#define Y		 0x80

enum SEND_DATA_TYPE{DAT=0x00,COMM=0x01};
enum COMM_TYPE{COMM_BASE_FUN = 0x30, COMM_RE_FUN = 0x34, 			/*通信命令*/
			COMM_CLR = 0x01, COMM_CURSOR = 0x06, COMM_ON_DISPLAY = 0x0C,
			COMM_DRAW_ON = 0x36 };
void chk_busy (void);
void wr_lcd(uchar mode,uchar sendData);
void display_one_8X4(uchar x, uchar y, uchar cH, uchar cL);
void init_lcd (void);
/**********************************************************
*函数名称：chk_busy (void)
*函数功能：判断lcd是否忙
*入口参数：无
*出口参数：无
**********************************************************/
void chk_busy (void)
{
  CHOOSE8255();  //片选8255
  XBYTE[COMMAND_ADDRESS] =0x00;  //8255,PB口定义为方式0，输出模式
  XBYTE[PB_ADDRESS]	=0xff;
  //P1=0xff;
  //rs=0;
  //rw=1;
  //e =1;
  LCD_RS =0;
  LCD_RW =1;
  LCD_E  =1;
  XBYTE[COMMAND_ADDRESS] =0x02;    //8255,PB口定义为方式0，输入模式
  while((XBYTE[PB_ADDRESS])&0x80); //等待lcd忙结束
  //while(busy==1);
  //e =0;
  LCD_E =0;
}
/**********************************************************
*函数名称：wr_lcd(uchar mode,uchar sendData)
*函数功能：向lcd写数据或者命令
*入口参数：mode,数据操作模式选择；sendData,操作的数据
*出口参数：无
**********************************************************/
void wr_lcd(uchar mode,uchar sendData)
{
   chk_busy ();
   if(mode==DAT)
   {
    //rs=1;   
    //rw=0;   
	 LCD_RS =1; //数据
	 LCD_RW =0; //写
   }
   else 
   {
    //rs=0;   
    //rw=0;   
	 LCD_RS =0; //命令
	 LCD_RW =0; //写
   }
   XBYTE[COMMAND_ADDRESS] =0x00;  //8255,PB口定义为方式0，输出模式
   XBYTE[PB_ADDRESS]	=sendData;
   //P1=content;   //output data or comm
   //e=1;
   LCD_E =1;
   _nop_();
   LCD_E =0;
   //e=0;
}
/**********************************************************
*函数名称：init_lcd (void)
*函数功能：lcd初始化
*入口参数：无
*出口参数：无
**********************************************************/
void init_lcd (void)
{
  wr_lcd (COMM,0x30);  /*30---基本指令动作*/   
  wr_lcd (COMM,0x01);  /*清屏，地址指针指向00H*/
  wr_lcd (COMM,0x06);  /*光标的移动方向*/
  wr_lcd (COMM,0x0c);  /*开显示，关游标*/
}
/**********************************************************
*功能:指定位置显示一个字符(16位)
*位置:  左上角(0,0)→X轴 (0,7)
		       ↓
			  Y轴(3,0)

***********************************************************/
void display_one_8X4(uchar x, uchar y, uchar cH, uchar cL)
{
	uchar pos = 0;
	if( (x < 8) && (y < 4) )
	{
		//change the postion
        switch(y)
        {
            case 0:
                pos = Line1;
                break;
            case 1:
                pos = Line2;
                break;
            case 2:
                pos = Line3;
                break;
            case 3:
                pos = Line4;
                break;
        }
		pos = pos+x;

		//display
		wr_lcd (COMM,COMM_BASE_FUN);
		wr_lcd (COMM,pos);
        
		wr_lcd (DAT, cH );
		wr_lcd (DAT, cL );
	}
}
/*************************************************************
功能：进行字符显示
参数：x,横轴坐标；y,纵轴坐标;str[],字符坐标;doubleNum,字符数量
**************************************************************/
void display_string(uchar x,uchar y,const uchar str[], uchar doubleNum)
{
    register uchar i;
    for(i = 0; i < doubleNum; i ++)
    {
        display_one_8X4(x+i,y,str[(i<<1)],str[(i<<1)+1]);
    }
}
void main()
{
  init_lcd();
  display_string(0,0,"abcd",4); //显示字符
  while(1);
}
