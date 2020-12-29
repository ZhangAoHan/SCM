/********************************************************************************
 曲谱存贮格式 unsigned char code MusicName{音高，音长，音高，音长...., 0,0};	末尾:0,0 表示结束(Important)

 音高由三位数字组成：
 		个位是表示 1~7 这七个音符 
 		十位是表示音符所在的音区:1-低音，2-中音，3-高音;
 		百位表示这个音符是否要升半音: 0-不升，1-升半音。
 
 音长最多由三位数字组成： 
 		个位表示音符的时值，其对应关系是： 
 			|数值(n):  |0 |1 |2 |3 | 4 | 5 | 6 
 			|几分音符: |1 |2 |4 |8 |16 |32 |64 		音符=2^n
 		十位表示音符的演奏效果(0-2):  0-普通，1-连音，2-顿音
 		百位是符点位: 0-无符点，1-有符点

 调用演奏子程序的格式
 		Play(乐曲名,调号,升降八度,演奏速度);
	|乐曲名           : 要播放的乐曲指针,结尾以(0,0)结束;
	|调号(0-11)       :	是指乐曲升多少个半音演奏;
	|升降八度(1-3)	  : 1:降八度, 2:不升不降, 3:升八度;
	|演奏速度(1-12000):	值越大速度越快;

***************************************************************************/
#ifndef MUSIC_H
#define MUSIC_H 1
  #include "Include.h"
  #ifndef MUSIC_GLOBAL 
   #define MUSIC_EXT extern
  #else
   #define MUSIC_EXT
  #endif
  #define SYSTEM_OSC 	11059200	//定义晶振频率11.0592MHZ
  #define SOUND_SPACE 	4/5 		//定义普通音符演奏的长度分率,//每4分音符间隔
  #define PlayIO        P1_7		//定义输出管脚
  #ifdef MUSIC_GLOBAL
    uint  code FreTab[12]  = { 262,277,294,311,330,349,369,392,415,440,466,494 }; //原始频率表
    uchar code SignTab[7]  = { 0,2,4,5,7,9,11 }; 								  //1~7在频率表中的位置
    uchar code LengthTab[7]= { 1,2,4,8,16,32,64 };						
    uchar Sound_Temp_TH0,Sound_Temp_TL0;	//音符定时器初值暂存 
    uchar Sound_Temp_TH1,Sound_Temp_TL1;	//音长定时器初值暂存
  #endif
  MUSIC_EXT	void InitialPlayer(void);
  MUSIC_EXT void Delay1ms(uint count);
  MUSIC_EXT	void Play(uchar *Sound,uchar Signature,uchar Octachord,uint Speed);
#endif