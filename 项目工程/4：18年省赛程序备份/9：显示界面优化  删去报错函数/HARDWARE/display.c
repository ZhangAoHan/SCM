//��ʾ�Ӻ���
/*
	1��ҳ����ƣ�2��ҳ�棨��ȭʶ��ҳ�������ʶ��ҳ�棩��
*/


#include "display.h"	 

void C_display_init(void)   //��ȭ�����ʼ�����
{
	POINT_COLOR=BLACK;
	LCD_DrawRectangle(1,1 ,239 ,27);   //������  ��ʾ״̬   ��ʾ��Χ��2-238  2-26��
	
	POINT_COLOR=BLUE;
	LCD_DrawRectangle(1,29 ,239 ,55);   //������  ��ʾ���  ��ʾ��Χ��180-228����λ���֣����㲹�ո� 30-54��
	POINT_COLOR=BLACK;
	Show_Str(2,30,168,24,"�о������ʾ��",24,1);
	
	POINT_COLOR=RED;
	LCD_DrawRectangle(1,57 ,150 ,83);   //������ ��������
	POINT_COLOR=BLACK;
	Show_Str(2,58,144,24,"����ʶ������",24,0);
	
	POINT_COLOR=YELLOW;
	LCD_DrawRectangle(1,85 ,239 ,245);   //������  ��ʾ�о�����
	LCD_DrawRectangle(1,135 ,130 ,245);   //������ 
	LCD_DrawRectangle(130,135 ,239 ,245);   //������ 
	LCD_DrawRectangle(1,136,55 ,245);   //������ 
	LCD_Fill(2,137,54,159,MAGENTA);
	LCD_DrawLine(1,160,239,160);
	LCD_DrawLine(1,187,239,187);
	LCD_DrawLine(1,217,239,217);
	POINT_COLOR=BLACK;
	Show_Str(2,86,192,24,"�о�������ʾ����",24,0);
	Show_Str(2,110,144,24,"ͨ��2���ݣ�",24,0);   //��ʾ��Χ��150-240   110-134��
	Show_Str(65,136,48,24,"��ֵ",24,0);
	Show_Str(154,136,48,24,"��ֵ",24,0);
	Show_Str(2,160,48,24,"ʯͷ",24,0);
	Show_Str(2,190,48,24,"����",24,0);
	Show_Str(2,220,48,24,"��",24,0);
}

void S_display_init(void)    //����ʶ���ʼ�����
{
	POINT_COLOR=BLACK;
	LCD_DrawRectangle(1,1 ,239 ,27);   //������  ��ʾ״̬   ��ʾ��Χ��2-238  2-26��
	
	POINT_COLOR=BLUE;
	LCD_DrawRectangle(1,29 ,239 ,55);   //������  ��ʾ���  ��ʾ��Χ��180-228����λ���֣����㲹�ո� 30-54��
	POINT_COLOR=BLACK;
	Show_Str(2,30,168,24,"�о������ʾ��",24,1);
	
	POINT_COLOR=RED;
	LCD_DrawRectangle(1,57 ,150 ,83);   //������ ��������
	POINT_COLOR=BLACK;
	Show_Str(2,58,144,24,"�����ȭ����",24,0);
	POINT_COLOR=YELLOW;
	LCD_DrawRectangle(1,85 ,239 ,307);   //������  ��ʾ�о�����
	LCD_DrawRectangle(1,135 ,130 ,307);   //������ 
	LCD_DrawRectangle(130,135 ,239 ,307);   //������ 
	LCD_DrawRectangle(1,136,55 ,307);   //������ 
	LCD_Fill(2,137,54,159,MAGENTA);
	LCD_DrawLine(1,161,239,161);
	LCD_DrawLine(1,188,239,188);
	LCD_DrawLine(1,217,239,217);
	LCD_DrawLine(1,247,239,247);
	LCD_DrawLine(1,277,239,277);
	POINT_COLOR=BLACK;
	Show_Str(2,86,192,24,"�о�������ʾ����",24,0);
	Show_Str(2,110,144,24,"ͨ��2���ݣ�",24,0);   //��ʾ��Χ��150-240   110-134��
	Show_Str(65,136,48,24,"��ֵ",24,0);
	Show_Str(154,136,48,24,"��ֵ",24,0);
	Show_Str(2,162,48,24,"��1",24,0);
	Show_Str(2,190,48,24,"��2",24,0);
	Show_Str(2,220,48,24,"��3",24,0);
	Show_Str(2,250,48,24,"��4",24,0);
	Show_Str(2,280,48,24,"��5",24,0);
}
