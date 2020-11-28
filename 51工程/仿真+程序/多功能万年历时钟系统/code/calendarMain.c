#include "Include.h"
//#include "character.h"
#include "lcd.h"
#include "clock.h"
#include "sensor.h"
#include "calendar.h"
#include "key.h"
uchar alarmStyle;   //���������������ʽ
/****************************************************************************/
sbit bell=P2^0;  //����������˿�
/****************************************************************************
*���ƣ�void Timer0_Initial(void)
*���ܣ���ʼ��timer0
*��ں�������
*���ں�������
****************************************************************************/
void Timer0_Initial(void)
{
  TMOD=0x01 ;          //Timer0������ʽ1��ʱ
  TH0 =0x4c;
  TL0 =0X00;           //��ʱ50 ms
  ET0 =1;              //Timer0���ж�
  TR0 =1;              //timer0����
}
/*****************************************************************************
* ����: Timer0_Overflow() inturrupt 1
* ����: �жϷ������ 1.���㱨ʱ �����ཱུ�����  2.���ӱ�ʱ,����һ����
* ��ڲ���:��
* ���ڲ���:��
*****************************************************************************/
void Timer0_Overflow() interrupt 1
{
   static uchar timer0Count;  //timer0�жϼ���
   static uchar count;
   TH0 = 0x3c;
   TL0 = 0XB0;   //��ʱ 50 ms
   if(alarmStyle&0x01)        //���㱨ʱ
   {
     timer0Count=20;          //��ʱ1��
   }
   else	if(alarmStyle&0x02)   //���ӱ���
        {
		   timer0Count=20;    //��ʱ1��
        }
   if(alarmStyle)
   {
     bell=~bell;
     count++;
	 if(count==timer0Count)
	 {
	   count=0x00;
	   alarmStyle=0x00;
	 } 
   }
   else
   {
     timer0Count=0x00;
	 count=0x00;
   }
}
/******************************************************************************
* ��������:main()
* ��    ��:������
* ��ڲ���:��
* ���ڲ���:��
********************************************************************************/
void main( void )
{        
    uchar clock_time[7] = { 0x00, 0x30, 0x08, 0x10, 0x01, 0x09 };        //����ʱ����� ��  �� ʱ �� �� ��
    uchar alarm_time[2] = { 0, 0}; //��������  alarm_time[0]: ����  alarm_time[1] :Сʱ
	uchar temperature[2];          //�����¶ȱ���   temperature[0]  ��8λ   temperature[1]  ��8λ
   	key_init();
    Lcd_Initial();                 //LCD��ʼ��
	Timer0_Initial();              //timer0��ʼ��,50ms��ʱ
	Clock_Initial(clock_time);     //ʱ�ӳ��Ի�
	alarmStyle=0x00;               //��ʼ��������ʽ����ʱ������
    sei();
    while( 1 )
	{
	   if(KEY_FUNC==Key_Scan())
	   {
	     Key_Function( clock_time, alarm_time );
	   }
	   Clock_Fresh( clock_time );     //ʱ��ˢ��
	   Lcd_Clock( clock_time );       //ʱ����ʾ
       Sensor_Fresh( temperature );   //�¶ȸ���
	   Lcd_Temperture( temperature ); //�¶���ʾ
       Calendar_Convert( 0 , clock_time );//��������ת����ʾ�ӳ���
	   Week_Convert( 0, clock_time );
	   if((*clock_time==0x59)&&(*(clock_time+1)==0x59 ))//���㱨ʱ
	   {
		 bell = 0;
	     alarmStyle=alarmStyle|0x01;   //������ʽ��ֵ
	   }
       //���ӱ���
       if( * alarm_time == * ( clock_time + 1 ) ) //�������Ǻ�
	    if( * ( alarm_time + 1 ) == *( clock_time + 2 ) ) //Сʱ���Ǻ�
	    {
		  bell=0;
		  alarmStyle=alarmStyle|0x02;   //������ʽ��ֵ
	    }
	   
	}
}
