#ifndef __DATE_CONTROL_H
#define __DATE_CONTROL_H
#include <stdio.h>
#include "stm32f10x.h" 

void Add_FR(void);	//¼ָ��
void Del_FR(void);	//ɾ��ָ��
void press_FR(void);//ˢָ��
void ShowErrMessage(u8 ensure);//��ʾȷ���������Ϣ
void AS608_load_keyboard(u16 x,u16 y,u8 **kbtbl);//�����������
u8  AS608_get_keynum(u16 x,u16 y);//��ȡ������
u16 GET_NUM(void);//��ȡ��ֵ

void car_settle(void) ;
void use1_touch(void);
void use_as608_scan(void) ;
void AS_Init(void);
void use_xx_scan(void);	
void gly_scan(void);
void date_read(void)  ;
void date_read_scan(void);
void gly_id_save(void);  //ÿ�ο���ǰ�õ�����ԱID
#endif

