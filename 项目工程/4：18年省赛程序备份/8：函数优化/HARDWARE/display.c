//��ʾ�Ӻ���
/*
	1��ҳ����ƣ�2��ҳ�棨��ȭʶ��ҳ�������ʶ��ҳ�棩��
*/


#include "display.h"	 

void C_display_init(void)   //��ȭ�����ʼ�����
{
	POINT_COLOR=BLUE;
	LCD_DrawRectangle(10,60 ,230 ,310);   //������  ��ɫ
	POINT_COLOR=BLACK;
	Show_Str(11,61,192,24,"��������ʶ�����",24,0);   //������������ʶ�����
	Show_Str(11,90,84,24,"ͨ��2��",24,0);
	POINT_COLOR=BLUE;	
	Show_Str(60,150,48,24,"��ֵ",24,0);
	Show_Str(120,150,96,24,"������Χ",24,0);	
	POINT_COLOR=BLACK;
	Show_Str(11,180,48,24,"ʯͷ",24,0);
	Show_Str(11,210,48,24,"����",24,0);
	Show_Str(11,240,48,24,"��",24,0);
}

void S_display_init(void)    //����ʶ���ʼ�����
{
	POINT_COLOR=BLUE;
	LCD_DrawRectangle(10,60 ,230 ,310);   //������
	POINT_COLOR=BLACK;
	Show_Str(11,61,192,24,"�����ȭʶ�����",24,0);
	POINT_COLOR=RED;   
	Show_Str(11,90,84,24,"ͨ��2��",24,0);
	POINT_COLOR=BLUE;	
	Show_Str(60,120,48,24,"��ֵ",24,0);
	Show_Str(120,120,96,24,"������Χ",24,0);
	POINT_COLOR=BLACK;
	Show_Str(11,150,48,24,"��1",24,0);
	Show_Str(11,180,48,24,"��2",24,0);
	Show_Str(11,210,48,24,"��3",24,0);
	Show_Str(11,240,48,24,"��4",24,0);
	Show_Str(11,270,48,24,"��5",24,0);
}
