#ifndef __MYGUI_H
#define __MYGUI_H

#include "sys.h"


/**************************************
		  �ҵ�GUI������������
**************************************/


//��ʾ����
void GUI_DISP_0(void);				    //���ְ�������
void GUI_DISP_1(void);            //RTCʵʱʱ����ʾ����
void GUI_DISP_2(void);            //�¶���ʾ����



//��������
//TFTLCD����У׼����
u8 my_GUI_TOUCH_0(void);				  //���ְ�������ɨ�跴����ֵ
void my_GUI_TOUCH_1(void);				//���ְ���������ֵ����
void my_GUI_TOUCH_2(void);				//���ְ�����������










//��ҵ��Ʋ������漰������Ӧ����
void GUI_DISP_MENU(void);         //�˵�����ʾ��������
u8 TOUCH_DISP_MENU(void); 				 		//��ֵ����
void TOUCH_GUI_DISP_MENU(void);		 		//��ֵ����

void GUI_DISP_chongzhi(void);     //��ֵ
u8 TOUCH_DISP_chongzhi(void);			 		//��ֵ����
void TOUCH_GUI_DISP_chongzhi(void);		//��ֵ����
void GUI_DISP_chongzhi0(void);    //��ֵ���
void TOUCH_GUI_DISP_chongzhi0(void);	
void GUI_DISP_chongzhi1(void);    //�ɹ�
void TOUCH_GUI_DISP_chongzhi1(void);
void GUI_DISP_chongzhi2(void);    //ʧ��
void TOUCH_GUI_DISP_chongzhi2(void);		
void GUI_DISP_chongzhi3(void);    //ʧ��
void TOUCH_GUI_DISP_chongzhi3(void);		

void GUI_DISP_xiaofei(void);      //����
u8 TOUCH_DISP_xiaofei(void);			 		//��ֵ����
void TOUCH_GUI_DISP_xiaofei(void);		//��ֵ����
void GUI_DISP_xiaofei0(void);     //���ѽ��
void TOUCH_GUI_DISP_xiaofei0(void);	
void GUI_DISP_xiaofei1(void);     //�ɹ�
void TOUCH_GUI_DISP_xiaofei1(void);		
void GUI_DISP_xiaofei2(void);     //ʧ�ܣ���ʾ���㣩
void TOUCH_GUI_DISP_xiaofei2(void);
void GUI_DISP_xiaofei3(void);		  //�����ڴ˿������˿�δ���
void TOUCH_GUI_DISP_xiaofei3(void);
void GUI_DISP_xiaofei4(void);		  //δ���������˿��ѹ�ʧ��
void TOUCH_GUI_DISP_xiaofei4(void);


void GUI_DISP_chaxun(void);       //��ѯ
void TOUCH_GUI_DISP_chaxun(void);			//��ֵ����
void GUI_DISP_chaxun0(void);      //��ѯ���
void TOUCH_GUI_DISP_chaxun0(void);		//��ֵ����	

void GUI_DISP_guashijiegua(void); //��ʧ/���
u8 TOUCH_DISP_guashijiegua(void);			 		//��ֵ����
void TOUCH_GUI_DISP_guashijiegua(void);		//��ֵ����
void GUI_DISP_jiegua(void);				//���
void TOUCH_GUI_DISP_jiegua(void);	
void GUI_DISP_guashi(void);				//��ʧ
void TOUCH_GUI_DISP_guashi(void);	
void GUI_DISP_guashijiegua0(void);//��ʧ�ɹ�
void TOUCH_GUI_DISP_guashijiegua0(void);		
void GUI_DISP_guashijiegua1(void);//��ʧʧ�ܣ��������벻��ȷ����
void TOUCH_GUI_DISP_guashijiegua1(void);	
void GUI_DISP_guashijiegua2(void);//��ҳɹ�
void TOUCH_GUI_DISP_guashijiegua2(void);	
void GUI_DISP_guashijiegua3(void);//���ʧ�ܣ����뿨�ź�ʵ�ʿ��Ų�һ�£�
void TOUCH_GUI_DISP_guashijiegua3(void);	
void GUI_DISP_guashijiegua4(void);//���ʧ�ܣ��������벻��ȷ����
void TOUCH_GUI_DISP_guashijiegua4(void);	
void GUI_DISP_guashijiegua5(void);//��ʧʧ�ܣ������ڴ˿�
void TOUCH_GUI_DISP_guashijiegua5(void);	
void GUI_DISP_guashijiegua6(void);//���ʧ�ܣ������ڴ˿�
void TOUCH_GUI_DISP_guashijiegua6(void);	



u8 TOUCH_all(void);						//ȫ��������ֵ����

void GUI_DISP_administrator(void); 
void TOUCH_GUI_DISP_administrator(void); //�ж��Ƿ��ǹ���Ա�Ŀ���
void GUI_DISP_administrator0(void); 
void TOUCH_GUI_DISP_administrator0(void);//���ǹ���Ա����


#endif





