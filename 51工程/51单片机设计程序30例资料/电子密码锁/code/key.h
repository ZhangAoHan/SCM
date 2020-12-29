/*******************************************************************************
驱动名称：矩阵式键盘扫描   
说明：本驱动适用4X4矩阵式键盘,采用反转式扫描,不支持组合键
功能：1.对键盘进行重新定义和存放
      2.行列定义在同一个单片机口
修改：针对protues中的测试
版本：0.0.2
作者：kxm
时间：2009.5.10 
*******************************************************************************/

#ifndef KEY_H
  #define KEY_H
  #include "Include.h"
  #ifndef KEY_GLOBAL
    #define KEY_EXT extern
  #else
    #define KEY_EXT
  #endif
  //-------用户使用设置-------------------
  #define key_line_L1	P1_0     //第一行所接的端口
  #define key_line_L2   P1_1	 //第二行所接的端口
  #define key_line_L3   P1_2	 //第三行所接的端口
  #define key_line_L4   P1_3	 //第四行所接的端口
  #define key_row_R1    P1_4	 //第一列所接的端口
  #define key_row_R2    P1_5	 //第二列所接的端口
  #define key_row_R3    P1_6	 //第三列所接的端口
  #define key_row_R4    P1_7	 //第四列所接的端口
  //------键盘端口定义-----------------------
  #define CAN_REPEAT      0           //是否允许重复按键: 允许为1;不允许为0 
  #define REPEAT_MODE     1           //重复模式: 先长后短为1;相同间隔为0 
  #define FIRST_TIMES     6000        //重复按下时,第一次间隔时间
  #define OTHER_TIMES     900         //第二次后间隔时间(如果重复模式为0时此值无效)
 //-----------------------------------------
  KEY_EXT void  key_init(void); 	  //矩阵式键盘参量初始化
  KEY_EXT uchar get_key_value(void);  //返回0~16键值
#endif