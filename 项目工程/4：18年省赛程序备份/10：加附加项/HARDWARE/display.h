#ifndef __DISPLAY_H
#define __DISPLAY_H
#include "sys.h"
#include "lcd.h"
#include "text.h"
   	

extern u8 flag;   					//����ѡ���׼��
extern u8 cle; 					 	//������־��
void C_display_init(void);   //��ȭ�����ʼ�����
void S_display_init(void);   //����ʶ���ʼ�����
void cq_scan(u8 a);         //������  ��ȭ�ȴ�С��ʼ����ʾ
#endif


