#define TARGET_GLOBAL 1
#include "target.h"
#include "dot.h"
void timer0_init(void)
{
   TMOD|=0x01;    //MODEL1,timer
   TH0=0xDC;	  //��ʱ10ms
   TL0=0x00;
   ET0=1;	     //�ж�ʹ��
   TR0=1;		 //�رն�ʱ��0
}
void target_init(void)
{
  timer0_init();
  Lcd_Initial();
}
/************************************************
*�������ƣ�display_head(void)
*�������ܣ���ʾ�������������״̬������
*������ڣ���
*�������ڣ���
************************************************/
void display_head(void)
{
  uchar i,temp;
  temp=0x00;
  for(i=0;i<8;i++)
  {
    Lcd_Character_16X16(1,10,temp,MOTER_HEAD[i]);
	temp+=16;
  }
  
}
/************************************************
*�������ƣ�display_state(state)
*�������ܣ���ʾ���״̬��ֹͣ��,����ת��,����ת��
*������ڣ�state,���״̬
*�������ڣ���
*˵����state:0x01,ֹͣ;0x02,��ת;0x03,��ת
************************************************/
void display_state(state)
{
  switch(state)
  {  
    case 0x01:   //��ʾ��ֹͣ��
	{
	  Lcd_Character_16X16(1,60,0,MOTER_STATE[0]); //ͣ
	  Lcd_Character_16X16(1,60,16,MOTER_STATE[1]);//ֹ
	  break;
	}
	case 0x02:	 //��ʾ����ת��
	{
	  Lcd_Character_16X16(1,60,0,MOTER_STATE[2]); //��
	  break;
	}
	case 0x03:	 //��ʾ����ת��
	{
	  Lcd_Character_16X16(1,60,0,MOTER_STATE[3]); //��
	  break;
	}
	default:
	  break;
  }
  if((state==0x02)||(state==0x03))
    Lcd_Character_16X16(1,60,16,MOTER_STATE[4]); //ת
}
/************************************************
*�������ƣ�display_speed(speed)
*�������ܣ���ʾ����ٶ�״̬
*������ڣ�speed,����ٶ�״̬
*�������ڣ���
*˵����speed:0x01,����;0x02,����;0x03,����;
             0x04,����
************************************************/
void display_speed(speed)
{
   switch(speed)
   {
     case 0x01:
	 {
	   Lcd_Character_16X16(1,60,32,SPEED_STATE[4]); //��
	   Lcd_Character_16X16(1,60,48,SPEED_STATE[5]); //��
	   break;
	 }
	 case 0x02:
	 {
	   Lcd_Character_16X16(1,60,32,SPEED_STATE[2]); //��
	   break;
	 }
	 case 0x03:
	 {
	   Lcd_Character_16X16(1,60,32,SPEED_STATE[0]); //��
	   break;
	 }
	 case 0x04:
	 {
	   Lcd_Character_16X16(1,60,32,SPEED_STATE[1]); //��
	   break;
	 }
	 default:
	   break;
   }
   if((speed==0x02)||(speed==0x03)||(speed==0x04))
     Lcd_Character_16X16(1,60,48,SPEED_STATE[3]);   //�� 
}
/*************************************************
*�������ƣ�moter_state_display(uchar moterState)
*�������ܣ�ʵ�ֲ������״̬��ʾ
*������ڣ�moterState,�������״̬
*�������ڣ���
*˵����moterState:0x01,ֹͣ;0x02,��ת��������;
0x03,��ת��������;0x04,��ת��������;
0x05,��ת��������;0x06,��ת��������;
0x07,��ת��������;0x08,��ת�������У�
0x09,��ת��������
*************************************************/
void moter_state_display(uchar moterState)
{
  Lcd_Clear(); 
  display_head();
  switch(moterState)
  {
    case MOTER_STOP:  //ֹͣ
	{
	  display_state(0x01);
	  break;
	}
	case MOTER_FRONT_ADD:	//��ת��������
	{
	  display_state(0x02);
	  display_speed(0x03);
	  break;
	}
	case MOTER_FRONT_REDUCE:  //��ת��������
	{
	  display_state(0x02);
	  display_speed(0x04);
	  break;
	}
	case MOTER_FRONT_NORMAL:	//��ת��������
	{
	  display_state(0x02);
	  display_speed(0x01);
	  break;
	}
	case MOTER_FRONT_LOWER:	//��ת��������
	{
	  display_state(0x02);
	  display_speed(0x02);
	  break;
	}
	case MOTER_QUEEN_ADD:	//��ת��������
	{
	  display_state(0x03);
	  display_speed(0x03);
	  break;
	}
	case MOTER_QUEEN_REDUCE: //��ת��������
	{
	  display_state(0x03);
	  display_speed(0x04);
	  break;
	}
	case MOTER_QUEEN_NOMAL: //��ת��������
	{
	  display_state(0x03);
	  display_speed(0x01);
	  break;
	}
	case MOTER_QUEEN_LOWER: //��ת��������
	{
	  display_state(0x03);
	  display_speed(0x02);
	  break;
	}
	default:
	  break;
  }
  if(moterState!=MOTER_STOP)
  {
    Lcd_Character_16X16(1,60,64,SPEED_STATE[6]); //��
	Lcd_Character_16X16(1,60,80,SPEED_STATE[7]); //��
  }

}
/*******************************************************
*�������ƣ�ground(step)
*�������ܣ���������ĸ��༫���ź�
*������ڣ�step,�����λ�ĵڼ���
*�������ڣ���
*˵�����������ת�������ְ˲�
*******************************************************/
void ground(step) 
{
  switch(step)
  {
    case 0x00:
	{
	  MOTER_M1= 1; 
	  MOTER_M2= 0;
	  MOTER_M3= 0;
	  MOTER_M4= 0;
	  break;
	}
	case 0x01:
	{
      MOTER_M1= 1;
	  MOTER_M2= 1;
	  MOTER_M3= 0;
	  MOTER_M4= 0;
	  break;	  
	}
	case 0x02:
	{
	  MOTER_M1= 0;
	  MOTER_M2= 1;
	  MOTER_M3= 0;
	  MOTER_M4= 0;
	  break;
	}
	case 0x03:
	{
	  MOTER_M1= 0;
	  MOTER_M2= 1;
	  MOTER_M3= 1;
	  MOTER_M4= 0;
	  break;
	}
	case 0x04:
	{ 
	  MOTER_M1= 0;
	  MOTER_M2= 0;
	  MOTER_M3= 1;
	  MOTER_M4= 0;
	  break; 
	}
	case 0x05:
	{
	  MOTER_M1= 0;
	  MOTER_M2= 0;
	  MOTER_M3= 1;
	  MOTER_M4= 1;
	  break;
	}
	case 0x06:
	{ 
	  MOTER_M1= 0;
	  MOTER_M2= 0;
	  MOTER_M3= 0;
	  MOTER_M4= 1;
	  break;
	}
	case 0x07:
	{
	  MOTER_M1= 0;
	  MOTER_M2= 0;
	  MOTER_M3= 0;
	  MOTER_M4= 1;
	  break;
	}
	default:
	   break;
  }
}