#ifndef TARGET_H
#define TARGET_H 1
  #include "lcd.h"
  #include "key.h"
  #ifndef TARGET_GLOBAL
    #define TARGET_EXT extern
  #else
    #define TARGET_EXT
  #endif
//------------------键值映射---------------------------
  #define KEY_ONE    1
  #define KEY_TWO    2
  #define KEY_THREE  3
  #define KEY_FOUR   4
  #define KEY_FIVE   5
  #define KEY_SIX    6
  #define KEY_SEVEN  7
  #define KEY_EIGHT  8
  #define KEY_NINE   9
  #define KEY_ZERO   10
  #define KEY_TRUE   11
  #define KEY_CLEAR  12
  #define KEY_SET    13
  #define KEY_UP     14
  #define KEY_DOWN   15
//---------------------------------------------------------------------
  TARGET_EXT void target_init(void);
  TARGET_EXT void displayFramOne(void);           //第一个界面显示 
  TARGET_EXT void displayFramTwo(bit posBit);     //第二个界面显示 
  TARGET_EXT void displayFramThree(void);         //第三个界面显示 
  TARGET_EXT void displayFramFour(void);          //第四个界面显示 
  TARGET_EXT void displayFramFive(void);          //第五个界面显示 
  TARGET_EXT void displayMima(uchar *s,uchar len,uchar mode);//显示密码输入 
#endif