/*****************************************************
* �ļ����ƣ�12864LCD.h							   
* ���ܣ�LCD��������
* ��ǰ�汾��1.0
* ���ߣ�YuanDong
* ������ڣ�2009��7��18��
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
* �������ƣ�unsigned char lcd_readcmd(void)
* ��    �ܣ���æ
* ��ڲ�������
* ���ڲ�������
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
* �������ƣ�void lcd_writecmd(unsigned char lcddata)
* ��    �ܣ�дָ��
* ��ڲ�����unsigned char lcddata
* ���ڲ�������
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
    for (i=0;i<5;i++)//дǰ��λ1
    {
     L_SCK = HIGH;L_SCK = LOW;
    }
    L_SI = LOW;   //д�����λ0
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
* �������ƣ�void lcd_writedata(unsigned char lcddata)
* ��    �ܣ�д����
* ��ڲ�����unsigned char lcddata
* ���ڲ�������
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
    //    11111 010,д����
    L_SI = HIGH;
    for (i=0;i<5;i++){L_SCK = HIGH;L_SCK = LOW;}
    L_SI = LOW;
    L_SCK = HIGH;L_SCK = LOW;
    L_SI = HIGH;
    L_SCK = HIGH;L_SCK = LOW;
    L_SI = LOW;
    L_SCK = HIGH;L_SCK = LOW;
    //    HHHH0000,д����λ
    temp = (lcddata)&0xf0;
    for (i=0;i<8;i++)
    {
        L_SI = (temp&0x80)?HIGH:LOW;
        temp <<=1;
        L_SCK = HIGH;L_SCK = LOW;
    }
    //    LLLL0000,д����λ
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
    }while (lcdopt&0x80); //�ж�æ
    EA=1;
}
 
/*********************************************************
* �������ƣ�void lcd_cmd(unsigned char cmd,unsigned char opt)
* ��    �ܣ�LCDдָ��
* ��ڲ�����unsigned char cmd,unsigned char opt
* ���ڲ�������
*********************************************************/
void lcd_cmd(unsigned char cmd,unsigned char opt)
{
 switch (cmd)
 {
  //����ָ��     //��չָ��
  case 0:lcd_writecmd(0x01);break;                //���                 //����ģʽ
  case 1:lcd_writecmd(0x02);break;                //λַ��λ             //��λַ��RAMλַѡ��
  case 2:opt&=0x03;lcd_writecmd(0x04|opt);break;  //������趨           //����ѡ��
  case 3:opt&=0x07;lcd_writecmd(0x08|opt);break;  //��ʾ״̬             //˯��ģʽ
  case 4:opt&=0x0f;lcd_writecmd(0x10|opt);break;  //�α����ʾ��λ����   //���书���趨
  case 5:opt&=0x1f;lcd_writecmd(0x20|opt);break;  //�����趨             //�趨ICONRAMλַ���λַ
  case 6:opt&=0x3f;lcd_writecmd(0x40|opt);break;  //CGRAMλַ            //�趨��ͼRAMλַ
  case 7:opt&=0x3f;lcd_writecmd(0x80|opt);break;  //DDRAMλַ
    }
}
	
/*********************************************************
* �������ƣ�void lcd_home(void)
* ��    �ܣ�LCD����
* ��ڲ�������
* ���ڲ�������
*********************************************************/
void lcd_home(void)
{
    lcd_cmd(1,0);
    lcd_cmd(2,0x02);
//    os_wait2(K_TMO,1);
}
	
/*********************************************************
* �������ƣ�void lcd_init(void)
* ��    �ܣ�LCD��ʼ��
* ��ڲ�������
* ���ڲ�������
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
* �������ƣ�void lcd_writestr(unsigned char l_line,unsigned char l_site,unsigned char * words)
* ��    �ܣ�д���ַ���
* ��ڲ�����unsigned char l_line,unsigned char l_site,unsigned char * words
* ���ڲ�������
*********************************************************/
void lcd_writestr(unsigned char l_line,unsigned char l_site,unsigned char * words)
{
//    l_line:��0-3; l_site:�� 0-7; words:��Ӣ�ַ�
 unsigned char c;
 c = 0; 
 l_site = l_site % 8;                  //ʹ����0-7��Χ
 if(l_line>1)                          //����=2,3
 {
  l_line = l_line % 2;                 //2�б�0��,3�б�1��
  l_site = l_site + 8;                 //�м�8
 }
 l_site = (l_line<<4) + l_site;        //��*16+��
 lcd_cmd(7,l_site);                    //DDRAM��ַ
 
 while(*words != 0)                    //д�ַ�
 {
  unsigned char tempdata;
  tempdata = *words;
  lcd_writedata(tempdata);
  words++;
  l_site++;
  c++;
 }
 if (c%2)                              //д������,�����һ���ַ��к��������򲹿ո�
 {
 lcd_writedata(0x20);
 }
}
 
/*********************************************************
* �������ƣ�void lcd_writechar(unsigned char words1,uchar words2,uchar words3,uchar words4)
* ��    �ܣ�д�뵥���ַ�
* ��ڲ�����unsigned char words1,uchar words2,uchar words3,uchar words4
* ���ڲ�������
*********************************************************/
void lcd_writechar(unsigned char words1,uchar words2,uchar words3,uchar words4)
{
//    l_line:��0-3; l_site:�� 0-7; words:��Ӣ�ַ�
 /*unsigned char tempdata;
 l_site = l_site % 8;                  //ʹ����0-7��Χ
 if(l_line>1)                          //����=2,3(����3,4��)
 {
  l_line = l_line % 2;                 //3�б�1��,4�б�2��
  l_site = l_site + 8;                 //�м�8
 }
 l_site = (l_line<<4) + l_site;    */    //��*16+��
 lcd_cmd(7,0x1a);                    //DDRAM��ַ
 
  lcd_writedata(words1);
  lcd_writedata(words2);
  lcd_writedata(words3);
  lcd_writedata(words4);

}
 
/*********************************************************
* �������ƣ�void delay(void)
* ��    �ܣ���ʱ
* ��ڲ�������
* ���ڲ�������
*********************************************************/
void delay(void)
{
  unsigned char a,b;
  for(a=250;a>0;a--)
   for(b=250;b>0;b--);
}