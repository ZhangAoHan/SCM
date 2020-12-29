/*****************************************************
*文件名称：target.h
*文件功能：包含在target.c和主文件中，实现特定任务函数
的实现和应用
*作者：yd
*时间：09.06.20
*****************************************************/
#ifndef TARGET_H
#define TARGET_H 1
  #include "Include.h"
  #ifndef TARGET_GLOBAL
    #define TARGET_EXT extern
  #else
    #define TARGET_EXT
  #endif
/**********定义时间各位在时间数组中的位置**********/
  #define MIN_H 0   //分钟计数十位在时间数组第0位
  #define MIN_L 1	//分钟计数各位在时间数组第1位
  #define S_H   3	//秒计数十位在时间数组第三位
  #define S_L   4	//秒计数各位在时间数组第四位
  #define MS_H   6	//毫秒计数十位在时间数组第六位
  #define MS_L   7	//毫秒计数各位在时间数组第七位
/*************************************************/
  #define CLEAR_KEY  P3_6   //秒表清零按键端口映射
  TARGET_EXT void target_init(void);
  TARGET_EXT void timer0_init(void);       //timer0初始化
  TARGET_EXT void int0_init(void);	       //int0初始化
  TARGET_EXT void int1_init(void);	       //int1初始化
  TARGET_EXT void ms_to_s(uchar *clockS);     //两位毫秒溢出,秒级进位
  TARGET_EXT void s_to_min(uchar *clockMin);  //秒级向分钟级进位
#endif