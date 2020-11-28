/*******************************************************************************
                           矩阵式键盘驱动
说明：本驱动使用4X4矩阵式键盘
功能：1.对键盘进行重新定义和存放
      2.行列定义在同一个单片机口
修改：采用翻转方式读取按下键值,仅支持单键按下
版本：0.0.2
作者：kxm
时间：2009.5.10 
*******************************************************************************/
#ifndef KEY_H
#define KEY_H  1
  #ifndef KEY_GLOBAL
    #define KEY_EXT extern
  #else
    #define KEY_EXT
  #endif
  #include "Include.h"
  //-------------用户使用设置-----------------------------
  //-------------键盘端口定义-----------------------------
  #define key_line_L1	P1_0       //键盘的第一行端口定义  
  #define key_line_L2   P1_1	   //键盘的第二行端口定义
  #define key_line_L3   P1_2	   //键盘的第三行端口定义
  #define key_line_L4   P1_3	   //键盘的第四行端口定义
  #define key_row_R1    P1_4	   //键盘的第一列端口定义
  #define key_row_R2    P1_5	   //键盘的第二列端口定义
  #define key_row_R3    P1_6	   //键盘的第三列端口定义
  #define key_row_R4    P1_7	   //键盘的第四列端口定义
  //-------------------------------------------------------
  #define CAN_REPEAT      0        //是否允许重复按键: 允许为1;不允许为0
  #define REPEAT_MODE     1        //重复模式: 先长后短为1;相同间隔为0
  #define FIRST_TIMES     6000     //重复按下时,第一次间隔时间
  #define OTHER_TIMES     900      //第二次后间隔时间(如果重复模式为0时此值无效)
 //-------------------------------------------------------
  KEY_EXT void  key_init(void);
  KEY_EXT uchar get_key_value();
  KEY_EXT void  keyDelay_us(uint us); //毫秒级延时
#endif