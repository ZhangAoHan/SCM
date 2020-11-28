/*******************************************************************************
* �ļ����ƣ�LM041L.h                          
* ˵�������ļ�ΪLCDͷ�ļ�
* ���ܣ�1. LCD�˿ڶ���
2. LCD�õ��ĺ���˵��
* �޸ģ� 
* �汾��1.0.0
* ���ߣ�YuanDong
* ʱ�䣺2009.5.11 
*******************************************************************************/

#ifndef LM041L_H
  #define LM041L_H 1
  #include "Include.h"
  #ifndef   LCD_GLOBAL
    #define LCD_EXT extern 
  #else
    #define LCD_EXT     
  #endif 
/***********�˿ڶ���************/
  #define LCD_DATA   P0	 
  sbit RS = P2^0;
  sbit RW = P2^1;
  sbit EN = P2^2;
 // uchar x_pos = 0,y_pos = 0;
  
/***********�˿ڶ���************/
  enum SEND_DATA_TYPE{DATA=0x01,COMM=0x00};  //���͸�LCD������Ϊcomm����data
LCD_EXT void delay(uint n);
LCD_EXT void recom(void);                   //��lcd״ָ̬�� 
LCD_EXT void busytest(void);		        //�����Ƿ�æ
LCD_EXT void wrlcd(uchar mode,uchar n);     //дlcdָ�������,DATA����COMM
LCD_EXT void clrscr(void);	                //����
LCD_EXT void initlcd(void);			        //��ʼ��lcd
LCD_EXT void setpos(uchar x,uchar y);       //���ù��λ��
LCD_EXT void wrstrdat(uchar x,uchar y,uchar *s,uint length);//д�ַ�������
#endif