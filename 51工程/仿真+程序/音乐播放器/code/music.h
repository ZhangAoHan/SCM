/********************************************************************************
 ���״�����ʽ unsigned char code MusicName{���ߣ����������ߣ�����...., 0,0};	ĩβ:0,0 ��ʾ����(Important)

 ��������λ������ɣ�
 		��λ�Ǳ�ʾ 1~7 ���߸����� 
 		ʮλ�Ǳ�ʾ�������ڵ�����:1-������2-������3-����;
 		��λ��ʾ��������Ƿ�Ҫ������: 0-������1-��������
 
 �����������λ������ɣ� 
 		��λ��ʾ������ʱֵ�����Ӧ��ϵ�ǣ� 
 			|��ֵ(n):  |0 |1 |2 |3 | 4 | 5 | 6 
 			|��������: |1 |2 |4 |8 |16 |32 |64 		����=2^n
 		ʮλ��ʾ����������Ч��(0-2):  0-��ͨ��1-������2-����
 		��λ�Ƿ���λ: 0-�޷��㣬1-�з���

 ���������ӳ���ĸ�ʽ
 		Play(������,����,�����˶�,�����ٶ�);
	|������           : Ҫ���ŵ�����ָ��,��β��(0,0)����;
	|����(0-11)       :	��ָ���������ٸ���������;
	|�����˶�(1-3)	  : 1:���˶�, 2:��������, 3:���˶�;
	|�����ٶ�(1-12000):	ֵԽ���ٶ�Խ��;

***************************************************************************/
#ifndef MUSIC_H
#define MUSIC_H 1
  #include "Include.h"
  #ifndef MUSIC_GLOBAL 
   #define MUSIC_EXT extern
  #else
   #define MUSIC_EXT
  #endif
  #define SYSTEM_OSC 	11059200	//���徧��Ƶ��11.0592MHZ
  #define SOUND_SPACE 	4/5 		//������ͨ��������ĳ��ȷ���,//ÿ4���������
  #define PlayIO        P1_7		//��������ܽ�
  #ifdef MUSIC_GLOBAL
    uint  code FreTab[12]  = { 262,277,294,311,330,349,369,392,415,440,466,494 }; //ԭʼƵ�ʱ�
    uchar code SignTab[7]  = { 0,2,4,5,7,9,11 }; 								  //1~7��Ƶ�ʱ��е�λ��
    uchar code LengthTab[7]= { 1,2,4,8,16,32,64 };						
    uchar Sound_Temp_TH0,Sound_Temp_TL0;	//������ʱ����ֵ�ݴ� 
    uchar Sound_Temp_TH1,Sound_Temp_TL1;	//������ʱ����ֵ�ݴ�
  #endif
  MUSIC_EXT	void InitialPlayer(void);
  MUSIC_EXT void Delay1ms(uint count);
  MUSIC_EXT	void Play(uchar *Sound,uchar Signature,uchar Octachord,uint Speed);
#endif