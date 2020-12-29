/*********************************************************
*�ļ����ƣ�lcdMain.c
*�ļ����ܣ�����ʵ�����lcd��ʾģ��,��lcdΪ�����ֿ��12864
*�汾��	   V0.0.1
*���ߣ�	   yd
*ʱ�䣺	   09.07.22
*˵������lcd��ʾ�������ݶ˿���ͨ��8255��չ�ģ��˴����Գ���
��8255�Ķ˿�ȫѡ���ڷ�ʽ0�������������ݴ���
*********************************************************/
#include <AT89X52.h>
#include <absacc.h>
#include <intrins.h>
#define uchar unsigned char
#define uint  unsigned int
//--------------------8255�˿ڲ�������---------------------
#define CHOOSE8255()  {P2_5=0;P2_6=1;P2_7=0;}   //ѡ��8255
#define PA_ADDRESS        0x00    //Ƭѡ8255ʱ��PA�˿ڵ�ַ 
#define PB_ADDRESS	      0x01    //Ƭѡ8255ʱ��PB�˿ڵ�ַ
#define PC_ADDRESS		  0x02    //Ƭѡ8255ʱ��PC�˿ڵ�ַ
#define COMMAND_ADDRESS   0x03    //Ƭѡ8255ʱ�����ƶ˿ڵ�ַ
//--------------------lcd���ƶ˿ڶ���----------------------
#define LCD_RS   P1_0  
#define LCD_RW   P1_1
#define LCD_E    P1_2
//---------------------------------------------------------
	/*��ĻXY�ᶨ��*/
	#define Line1	 0x80
	#define Line2	 0x90
	#define Line3	 0x88
	#define Line4	 0x98
	#define Y		 0x80

enum SEND_DATA_TYPE{DAT=0x00,COMM=0x01};
enum COMM_TYPE{COMM_BASE_FUN = 0x30, COMM_RE_FUN = 0x34, 			/*ͨ������*/
			COMM_CLR = 0x01, COMM_CURSOR = 0x06, COMM_ON_DISPLAY = 0x0C,
			COMM_DRAW_ON = 0x36 };
void chk_busy (void);
void wr_lcd(uchar mode,uchar sendData);
void display_one_8X4(uchar x, uchar y, uchar cH, uchar cL);
void init_lcd (void);
/**********************************************************
*�������ƣ�chk_busy (void)
*�������ܣ��ж�lcd�Ƿ�æ
*��ڲ�������
*���ڲ�������
**********************************************************/
void chk_busy (void)
{
  CHOOSE8255();  //Ƭѡ8255
  XBYTE[COMMAND_ADDRESS] =0x00;  //8255,PB�ڶ���Ϊ��ʽ0�����ģʽ
  XBYTE[PB_ADDRESS]	=0xff;
  //P1=0xff;
  //rs=0;
  //rw=1;
  //e =1;
  LCD_RS =0;
  LCD_RW =1;
  LCD_E  =1;
  XBYTE[COMMAND_ADDRESS] =0x02;    //8255,PB�ڶ���Ϊ��ʽ0������ģʽ
  while((XBYTE[PB_ADDRESS])&0x80); //�ȴ�lcdæ����
  //while(busy==1);
  //e =0;
  LCD_E =0;
}
/**********************************************************
*�������ƣ�wr_lcd(uchar mode,uchar sendData)
*�������ܣ���lcdд���ݻ�������
*��ڲ�����mode,���ݲ���ģʽѡ��sendData,����������
*���ڲ�������
**********************************************************/
void wr_lcd(uchar mode,uchar sendData)
{
   chk_busy ();
   if(mode==DAT)
   {
    //rs=1;   
    //rw=0;   
	 LCD_RS =1; //����
	 LCD_RW =0; //д
   }
   else 
   {
    //rs=0;   
    //rw=0;   
	 LCD_RS =0; //����
	 LCD_RW =0; //д
   }
   XBYTE[COMMAND_ADDRESS] =0x00;  //8255,PB�ڶ���Ϊ��ʽ0�����ģʽ
   XBYTE[PB_ADDRESS]	=sendData;
   //P1=content;   //output data or comm
   //e=1;
   LCD_E =1;
   _nop_();
   LCD_E =0;
   //e=0;
}
/**********************************************************
*�������ƣ�init_lcd (void)
*�������ܣ�lcd��ʼ��
*��ڲ�������
*���ڲ�������
**********************************************************/
void init_lcd (void)
{
  wr_lcd (COMM,0x30);  /*30---����ָ���*/   
  wr_lcd (COMM,0x01);  /*��������ַָ��ָ��00H*/
  wr_lcd (COMM,0x06);  /*�����ƶ�����*/
  wr_lcd (COMM,0x0c);  /*����ʾ�����α�*/
}
/**********************************************************
*����:ָ��λ����ʾһ���ַ�(16λ)
*λ��:  ���Ͻ�(0,0)��X�� (0,7)
		       ��
			  Y��(3,0)

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
���ܣ������ַ���ʾ
������x,�������ꣻy,��������;str[],�ַ�����;doubleNum,�ַ�����
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
  display_string(0,0,"abcd",4); //��ʾ�ַ�
  while(1);
}
