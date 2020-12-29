#ifndef _8255_H
#define _8255_H
  #define CHOOSE8255()  {P2_5=0;P2_6=1;P2_7=0;}   //选择8255
  #define PA_ADDRESS        0x00    //片选8255时，PA端口地址 
  #define PB_ADDRESS	      0x01    //片选8255时，PB端口地址
  #define PC_ADDRESS		  0x02    //片选8255时，PC端口地址
  #define COMMAND_ADDRESS   0x03    //片选8255时，控制端口地址
#endif