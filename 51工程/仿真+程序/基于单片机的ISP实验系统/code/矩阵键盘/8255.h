#ifndef _8255_H
#define _8255_H
  #define CHOOSE8255()  {P2_5=0;P2_6=1;P2_7=0;}   //ѡ��8255
  #define PA_ADDRESS        0x00    //Ƭѡ8255ʱ��PA�˿ڵ�ַ 
  #define PB_ADDRESS	      0x01    //Ƭѡ8255ʱ��PB�˿ڵ�ַ
  #define PC_ADDRESS		  0x02    //Ƭѡ8255ʱ��PC�˿ڵ�ַ
  #define COMMAND_ADDRESS   0x03    //Ƭѡ8255ʱ�����ƶ˿ڵ�ַ
#endif