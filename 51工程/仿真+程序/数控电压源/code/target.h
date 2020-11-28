#ifndef TARGET_H
#define TARGET_H 1
  #include "Include.h"
  #ifndef TARGET_GLOBAL
    #define TARGET_EXT extern
  #else
    #define TARGET_EXT
  #endif 
  #define UP   P3^2;
  #define DONW P3^3;
  #define ADIN XBYTE[0x7FFF]
  TARGET_EXT void key_init(void);  /*按键初始化,及对外部中断进行初始化*/
#endif