#ifndef TARGET_H
#define TARGET_H 1
  #include "lcd.h"
  #include "key.h"
  #ifndef TARGET_GLOBAL
    #define TARGET_EXT extern
  #else
    #define TARGET_EXT
  #endif
//------------------��ֵӳ��---------------------------
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
  TARGET_EXT void displayFramOne(void);           //��һ��������ʾ 
  TARGET_EXT void displayFramTwo(bit posBit);     //�ڶ���������ʾ 
  TARGET_EXT void displayFramThree(void);         //������������ʾ 
  TARGET_EXT void displayFramFour(void);          //���ĸ�������ʾ 
  TARGET_EXT void displayFramFive(void);          //�����������ʾ 
  TARGET_EXT void displayMima(uchar *s,uchar len,uchar mode);//��ʾ�������� 
#endif