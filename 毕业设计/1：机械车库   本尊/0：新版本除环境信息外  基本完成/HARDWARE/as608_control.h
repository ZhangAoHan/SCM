#ifndef __AS608_CONTROL_H
#define __AS608_CONTROL_H
#include "sys.h"



void Add_FR(u8 g);	//¼ָ��
void Del_FR(void);	//ɾ��ָ��
void press_FR(void);//ˢָ��
void ShowErrMessage(u8 ensure);//��ʾȷ���������Ϣ
void AS608_load_keyboard(u16 x,u16 y,u8 **kbtbl);//�����������
u8  AS608_get_keynum(u16 x,u16 y);//��ȡ������
u16 GET_NUM(void);//��ȡ��ֵ
void as608_use_init(void) ;
void gly_id_save(void);    //�Զ�¼����Աָ��  ¼�������
void gly_scan(void);
void page_0(void);  
void gly_page_0(void)    ;
void gly_page_1(void) ;
void gly_page_2(void);
void gly_page_3(void)  ;
#endif


