#include  "Key.h"
#include  "led.h"

uchar timeSetBuff[8]={'0','0',LED_MODE_COUNT,'0','0',LED_MODE_COUNT,'0','0'};//时钟数据缓冲区 
uchar alarmSetBuff[8]={'0','0',LED_MODE_ALARM,'0','0',LED_MODE_ALARM,'0','0'};//闹钟时间数据缓冲区 
uchar timeDisMod=0x24;                //00100100
uchar secondTemp,minuteTemp,hourTemp;
uchar secondAlarm,minuteAlarm,hourAlarm;
uchar timer0Temp;
uchar alarmKeyCount;                   //闹钟起停键计数 
bit alarm_is_ok;                       //闹钟起停状态 
bit time_is_ok;                        //时间是否到 
bit interface_mod;                     // 显示界面模式，0为主时间界面，1为设置界面 

/********************************************************************************************
* 函数名称：定时器0
* 功    能：定时器0初始化
* 入口参数：无
* 出口参数：无
*********************************************************************************************/	   
void initTimer0(void)	              //定时10ms 
{
   TMOD |= 0x01;                        //GATE=0,TR=1运行;C/T=1,counter,0,timer;01十六进制  
   TH0 = 0xdc;
   TL0 = 0x00;
   TR0 = 1;	                          //timer0 控制位，为1时启动timer0
   ET0 = 1;                             //timer0 中断使能 
}

/********************************************************************************************
* 函数名称：时钟比较
* 功    能：比较时钟和闹钟的时间缓冲区，只比较时和分
* 入口参数：无
* 出口参数：无
*********************************************************************************************/
void timeCompare(void)	    
{
  if((minuteTemp == minuteAlarm) && (hourTemp == hourAlarm))
  {
     time_is_ok = 1;
	 alarm_is_ok = 0;
	 interface_mod = 1;
  }   
}	

/********************************************************************************************
* 函数名称：主函数
* 功    能：调用并执行各个子函数
* 入口参数：无
* 出口参数：无
*********************************************************************************************/
void main()
{
 uchar keyRead;
 init_led();
 init_key();
 initTimer0();
 timer0Temp = 0x00;
 secondTemp = 0x00;
 minuteTemp = 0x00;
 hourTemp = 0x00;
 secondAlarm = 0x00;
 minuteAlarm = 0x00;
 hourAlarm = 0x00;
 alarmKeyCount = 0x02;
 alarm_is_ok = 0;     //默认状态停止 
 time_is_ok = 0;      //默认时间未到 
 interface_mod = 0;
 sei();
 while(1)
 {
  
   if(interface_mod == 1)
     ledSweepDisplay(alarmSetBuff,timeDisMod);
   else
     ledSweepDisplay(timeSetBuff,timeDisMod);
   if(alarm_is_ok == 1)
     timeCompare();
   
   keyRead = get_key_value();
   if(keyRead == KEY_ALARM)
   {
      if(alarm_is_ok == 1 || time_is_ok == 1)
	  {
	    alarm_is_ok = 0;
		time_is_ok = 0;
		interface_mod = 0;
		alarmKeyCount = 0x00;
	  }
	  else
	  {
		if(alarmKeyCount < 0x02)
     	   alarmKeyCount++;
		else
		   alarmKeyCount = 0x00;
		if(alarmKeyCount == 0x01)
		  interface_mod = 1;
		if(alarmKeyCount == 0x02)
		 {
		   alarm_is_ok = 1;
		   interface_mod = 0;
		 }	  
	  }    
    }
   if(keyRead == KEY_SECOND)
   { if(interface_mod == 1)
     {
	   if(secondAlarm < 59)
	     secondAlarm++;
	   else
	     secondAlarm = 0x00;
	   alarmSetBuff[S_L] = secondAlarm % 10 + '0';
	   alarmSetBuff[S_H] = secondAlarm / 10 + '0';
	 }
     else 
	 {
	   if(secondTemp < 59)
	     secondTemp += 1;
	   else
	     secondTemp = 0x00;
	   timeSetBuff[S_L] = secondTemp % 10 + '0';
       timeSetBuff[S_H] = secondTemp / 10 + '0'; 
	 }   
   }
   if(keyRead == KEY_MINUTE)
   { if(interface_mod == 1)
     {
	   if(minuteAlarm < 59)
	     minuteAlarm++;
	   else
	     minuteAlarm=0x00;
	   alarmSetBuff[M_L]=minuteAlarm%10+'0';
	   alarmSetBuff[M_H]=minuteAlarm/10+'0';
	 }
	 else 
	 {
	   if(minuteTemp < 59)
	     minuteTemp += 1;
	   else
	     minuteTemp = 0x00;
	   timeSetBuff[M_L] = minuteTemp % 10 + '0';
       timeSetBuff[M_H] = minuteTemp / 10 + '0'; 
	 }
       
   }
  if(keyRead == KEY_HOUR)
  {
     if(interface_mod == 1)
	 {
	   if(hourAlarm < 23)
	     hourAlarm++;
	   else
	     hourAlarm = 0x00;
	   alarmSetBuff[H_L] = hourAlarm % 10 + '0';
	   alarmSetBuff[H_H] = hourAlarm / 10 + '0';
	 }
	 else 
	 {
	   if(hourTemp < 23)
	     hourTemp += 1;
	   else
	     hourTemp = 0x00;
	   timeSetBuff[H_L] = hourTemp%10+'0';
       timeSetBuff[H_H] = hourTemp/10+'0'; 
	 }
       
  }
    
 }
}


/*， */ 
/********************************************************************************************
* 函数名称：定时器0中断函数
* 功    能：定时器0溢出中断入口处,定时10ms
* 入口参数：无
* 出口参数：无
*********************************************************************************************/
void timer0_overflow(void) interrupt 1 
{
   TH0 = 0xdc;
   TL0 = 0x00;
   if(time_is_ok == 1)	    //报警 
     WARN_TRUMPET = ~WARN_TRUMPET;
   if(timer0Temp < 99)        //判断1s是否到 
       timer0Temp++;
   else	                    //进中断100次 
   {
        timer0Temp = 0x00; 	  
	    if(secondTemp < 59)   //判断1min是否到  	
		{
		  secondTemp++;
		}
		else
		{

		  secondTemp = 0x00;
		  if(minuteTemp < 59)  //判断1hour是否到 
		     minuteTemp++;
       	  else
		  {
		    minuteTemp = 0x00;
			if(hourTemp < 23)
			  hourTemp++;
			else
			  hourTemp = 0x00; 
		  }

		}  
   }
   timeSetBuff[S_L] = secondTemp%10+'0';
   timeSetBuff[S_H] = secondTemp/10+'0';
   timeSetBuff[M_L] = minuteTemp%10+'0';
   timeSetBuff[M_H] = minuteTemp/10+'0';
   timeSetBuff[H_L] = hourTemp%10+'0';
   timeSetBuff[H_H] = hourTemp/10+'0';
   sei();
}
