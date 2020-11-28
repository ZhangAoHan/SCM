#include  "Key.h"
#include  "led.h"

uchar timeSetBuff[8]={'0','0',LED_MODE_COUNT,'0','0',LED_MODE_COUNT,'0','0'};//ʱ�����ݻ����� 
uchar alarmSetBuff[8]={'0','0',LED_MODE_ALARM,'0','0',LED_MODE_ALARM,'0','0'};//����ʱ�����ݻ����� 
uchar timeDisMod=0x24;                //00100100
uchar secondTemp,minuteTemp,hourTemp;
uchar secondAlarm,minuteAlarm,hourAlarm;
uchar timer0Temp;
uchar alarmKeyCount;                   //������ͣ������ 
bit alarm_is_ok;                       //������ͣ״̬ 
bit time_is_ok;                        //ʱ���Ƿ� 
bit interface_mod;                     // ��ʾ����ģʽ��0Ϊ��ʱ����棬1Ϊ���ý��� 

/********************************************************************************************
* �������ƣ���ʱ��0
* ��    �ܣ���ʱ��0��ʼ��
* ��ڲ�������
* ���ڲ�������
*********************************************************************************************/	   
void initTimer0(void)	              //��ʱ10ms 
{
   TMOD |= 0x01;                        //GATE=0,TR=1����;C/T=1,counter,0,timer;01ʮ������  
   TH0 = 0xdc;
   TL0 = 0x00;
   TR0 = 1;	                          //timer0 ����λ��Ϊ1ʱ����timer0
   ET0 = 1;                             //timer0 �ж�ʹ�� 
}

/********************************************************************************************
* �������ƣ�ʱ�ӱȽ�
* ��    �ܣ��Ƚ�ʱ�Ӻ����ӵ�ʱ�仺������ֻ�Ƚ�ʱ�ͷ�
* ��ڲ�������
* ���ڲ�������
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
* �������ƣ�������
* ��    �ܣ����ò�ִ�и����Ӻ���
* ��ڲ�������
* ���ڲ�������
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
 alarm_is_ok = 0;     //Ĭ��״ֹ̬ͣ 
 time_is_ok = 0;      //Ĭ��ʱ��δ�� 
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


/*�� */ 
/********************************************************************************************
* �������ƣ���ʱ��0�жϺ���
* ��    �ܣ���ʱ��0����ж���ڴ�,��ʱ10ms
* ��ڲ�������
* ���ڲ�������
*********************************************************************************************/
void timer0_overflow(void) interrupt 1 
{
   TH0 = 0xdc;
   TL0 = 0x00;
   if(time_is_ok == 1)	    //���� 
     WARN_TRUMPET = ~WARN_TRUMPET;
   if(timer0Temp < 99)        //�ж�1s�Ƿ� 
       timer0Temp++;
   else	                    //���ж�100�� 
   {
        timer0Temp = 0x00; 	  
	    if(secondTemp < 59)   //�ж�1min�Ƿ�  	
		{
		  secondTemp++;
		}
		else
		{

		  secondTemp = 0x00;
		  if(minuteTemp < 59)  //�ж�1hour�Ƿ� 
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
