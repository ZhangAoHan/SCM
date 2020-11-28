#define TARGET_GLOBAL 1
#include "target.h"
#include "dot.h"
void target_init(void)
{
  Lcd_Initial(); //lcd��ʼ��
  key_init();	 //����ɨ���ʼ��
}
/**********************************
*�������ƣ�displayFramOne(void)
*�����ܣ���ʾ��һ����������
*������ڣ���
*������ڣ���
*˵������ʾ����ӭʹ�á�
**********************************/
void displayFramOne(void)
{
  Lcd_Clear();
  Lcd_Character_16X16(1,2,32,fram_one[0]);
  Lcd_Character_16X16(1,2,48,fram_one[1]);
  Lcd_Character_16X16(1,2,64,fram_one[2]);
  Lcd_Character_16X16(1,2,80,fram_one[3]);
}
/**********************************
*�������ƣ�displayFramTwo(bit posBit)
*�����ܣ���ʾ�ڶ�����������
*������ڣ�posBit,�������λ��
*������ڣ���
*˵����posbit=0,��һ�кڰ���ʾ
	   posbit=1,�ڶ��кڰ���ʾ
	   ��ʾ��A:����ϵͳ��
	       ��B:�������롱
**********************************/           
void displayFramTwo(bit posBit)
{
  uchar i;
  uchar temp;
  Lcd_Clear();
  Lcd_Character_16X8(1,8,0,other_dot[0]);
  Lcd_Character_16X8(1,8,8,other_dot[2]);
  Lcd_Character_16X8(1,60,0,other_dot[1]);
  Lcd_Character_16X8(1,60,8,other_dot[2]);
  temp=16;
  for(i=0;i<4;i++)
  {
    if(posBit==0)
       Lcd_Character_16X16(0,8,temp,fram_two[i]);
	else
	   Lcd_Character_16X16(1,8,temp,fram_two[i]);
	temp+=16;
  }
  temp=16;
  for(i=0;i<4;i++)
  {
    if(posBit==1)
       Lcd_Character_16X16(0,60,temp,fram_two[i+4]);
	else
	   Lcd_Character_16X16(1,60,temp,fram_two[i+4]);
	temp+=16;
  } 
}
/**********************************
*�������ƣ�displayFramThree(void)
*�����ܣ���ʾ��������������
*������ڣ���
*������ڣ���
*˵������ʾ�����������롱
**********************************/           
void displayFramThree(void)
{
  uchar temp,i;
  temp=0;
  Lcd_Clear();
  for(i=0;i<5;i++)
  {
    Lcd_Character_16X16(1,10,temp,fram_three[i]);
	temp+=16;
  }
  Lcd_Character_16X8(1,10,80,other_dot[2]); 
  
}
/**********************************
*�������ƣ�displayFramFour(void)
*�����ܣ���ʾ���ĸ���������
*������ڣ���
*������ڣ���
*˵������ʾ�����������롱
**********************************/      
void displayFramFour(void)
{
  uchar temp,i;
  Lcd_Clear();
  Lcd_Character_16X16(1,10,0,fram_three[0]);
  temp=16;
  for(i=0;i<4;i++)
  {
    Lcd_Character_16X16(1,10,temp,fram_two[i+4]);
    temp+=16;
  }
  Lcd_Character_16X8(1,10,80,other_dot[2]);
}
/**********************************
*�������ƣ�displayFramFour(void)
*�����ܣ���ʾ�������������
*������ڣ���
*������ڣ���
*˵������ʾ����ϲ��,����ˡ�
**********************************/
void displayFramFive(void)
{
  uchar i,temp;
  Lcd_Clear();
  temp=0;
  for(i=0;i<3;i++)
  {
    Lcd_Character_16X16(1,10,temp,fram_five[i]);
	temp+=16;
  }
  Lcd_Character_16X8(1,10,temp,other_dot[4]);
  temp+=8;
  for(i=0;i<3;i++)
  {
    Lcd_Character_16X16(1,10,temp,fram_five[i+3]);
	temp+=16;
  }

}
/****************************************************
*�������ƣ�displayMima(uchar *s,uchar len,uchar mode)
*�����ܣ���ʾ��������
*������ڣ�s-��������ָ��;len-�������볤��;mode-ΪҪ
�����������,0x01Ϊ��������,0x02Ϊ������������
*������ڣ���
*****************************************************/           
void displayMima(uchar *s,uchar len,uchar mode)
{
  uchar temp,i;
  if(mode==0x01)   //��������,��ʱ��10��,88�п�ʼ��ʾlen��*
  {
    temp=88;
    for(i=0;i<len;i++)
	{
	  Lcd_Character_16X8(1,10,temp,other_dot[3]);
	  temp+=8;
	}
	 
  }
  else           //��������,��ʱ��10��,88�п�ʼ��ʾs[0]~s[len]
  {
    temp=88;
    for(i=0;i<len;i++)
	{
	  Lcd_Character_16X8(1,10,temp,digital_dot[s[i]]);
	  temp+=8;
	}
  }
}