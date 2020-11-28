#ifndef __TOMCATPLAY_H
#define __TOMCATPLAY_H 	
#include "common.h"	
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//APP-TOMè ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2014/2/16
//�汾��V1.1
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//*******************************************************************************
//V1.1 20140216
//�����Ը��ֱַ���LCD��֧��.
////////////////////////////////////////////////////////////////////////////////// 	   
   
////////////////////////////////////////////////////////////////////////////////////////////
//��ͼ��/ͼƬ·��
extern u8*const TOMCAT_DEMO_PIC;//demoͼƬ·�� 	      
////////////////////////////////////////////////////////////////////////////////////////////

void tomcat_load_ui(void);
void tomcat_show_spd(u16 x,u16 y,u16 spd);
u8 tomcat_agcspd_set(u16 x,u16 y,u8 *agc,u16 *speed,u8*caption);
void tomcat_rec_mode(u8 agc);
void tomcat_play_wav(u8 *buf,u32 len);
void tomcat_data_move(u8* buf,u16 size,u16 dx);
u8 tomcat_play(void);



#endif























