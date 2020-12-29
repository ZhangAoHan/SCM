#include "Include.h"
//#include "character.h"
#include "lcd.h"
#include "clock.h"
#include "sensor.h"
#include "calendar.h"
#include "key.h"
uchar alarmStyle;   //定义蜂鸣器报警方式
/****************************************************************************/
sbit bell=P2^0;  //定义蜂鸣器端口
/****************************************************************************
*名称：void Timer0_Initial(void)
*功能：初始化timer0
*入口函数：无
*出口函数：无
****************************************************************************/
void Timer0_Initial(void)
{
  TMOD=0x01 ;          //Timer0工作方式1定时
  TH0 =0x4c;
  TL0 =0X00;           //定时50 ms
  ET0 =1;              //Timer0开中断
  TR0 =1;              //timer0启动
}
/*****************************************************************************
* 名称: Timer0_Overflow() inturrupt 1
* 功能: 中断服务程序 1.整点报时 三声嘟嘟的声音  2.闹钟报时,持续一分钟
* 入口参数:无
* 出口参数:无
*****************************************************************************/
void Timer0_Overflow() interrupt 1
{
   static uchar timer0Count;  //timer0中断计数
   static uchar count;
   TH0 = 0x3c;
   TL0 = 0XB0;   //延时 50 ms
   if(alarmStyle&0x01)        //整点报时
   {
     timer0Count=20;          //报时1秒
   }
   else	if(alarmStyle&0x02)   //闹钟报警
        {
		   timer0Count=20;    //报时1秒
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
* 函数名称:main()
* 功    能:主函数
* 入口参数:无
* 出口参数:无
********************************************************************************/
void main( void )
{        
    uchar clock_time[7] = { 0x00, 0x30, 0x08, 0x10, 0x01, 0x09 };        //定义时间变量 秒  分 时 日 月 年
    uchar alarm_time[2] = { 0, 0}; //闹钟设置  alarm_time[0]: 分钟  alarm_time[1] :小时
	uchar temperature[2];          //定义温度变量   temperature[0]  低8位   temperature[1]  高8位
   	key_init();
    Lcd_Initial();                 //LCD初始化
	Timer0_Initial();              //timer0初始化,50ms延时
	Clock_Initial(clock_time);     //时钟初试化
	alarmStyle=0x00;               //初始化报警方式，此时不报警
    sei();
    while( 1 )
	{
	   if(KEY_FUNC==Key_Scan())
	   {
	     Key_Function( clock_time, alarm_time );
	   }
	   Clock_Fresh( clock_time );     //时间刷新
	   Lcd_Clock( clock_time );       //时间显示
       Sensor_Fresh( temperature );   //温度更新
	   Lcd_Temperture( temperature ); //温度显示
       Calendar_Convert( 0 , clock_time );//调用阴历转换显示子程序
	   Week_Convert( 0, clock_time );
	   if((*clock_time==0x59)&&(*(clock_time+1)==0x59 ))//整点报时
	   {
		 bell = 0;
	     alarmStyle=alarmStyle|0x01;   //报警方式赋值
	   }
       //闹钟报警
       if( * alarm_time == * ( clock_time + 1 ) ) //分钟相吻合
	    if( * ( alarm_time + 1 ) == *( clock_time + 2 ) ) //小时相吻合
	    {
		  bell=0;
		  alarmStyle=alarmStyle|0x02;   //报警方式赋值
	    }
	   
	}
}
