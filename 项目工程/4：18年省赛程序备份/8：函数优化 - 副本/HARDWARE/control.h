#ifndef __CONTROL_H
#define __CONTROL_H
#include "sys.h"
#include "lcd.h"
#include "text.h"
   	

extern u8 flag;   					            //����ѡ���׼��
extern u8 cle; 					 	      	    //������־��
extern uint32_t date2;
extern uint32_t fre2;
extern uint32_t fre2_last;
extern uint32_t result2;
extern uint32_t fre2_init_min,fre2_init_max;    //���10000���� �ҵ����ֵ����Сֵ
extern uint32_t ch2_middle,ch2_wave;            //��ֵ�Ͳ�������
extern uint32_t by2,bb2,sy2,sb2,jy2,jb2;        //ʹϵͳ���д洢����
extern uint32_t y1,b1,y2,b2,y3,b3,y4,b4,y5,b5;  //ʹϵͳ���д洢����
extern u8 mode_selsct;                        //ͨ��ѡ��
extern u8 mode;                                 //����ѡ��

void FDC2214read(void);  
void Scan_sjb(void);
void C_control(void);
void S_control(void);
void C_Feedback(void);
void S_Feedback(void);
void Scan(u8 d);

#endif

