#include "Key.h"
#include "led.h"
#define KEY_VALID_VALUE  0      //�����˰�����Ч��ƽ 
#define MOD_TWO          0x49   //ģʽ��ʾ�ַ� 
#define ALARM_COUNT_TIME 1000   //ѡ�ֻش�ʱ����ʱ�䣬10S
sbit KEY_START=P2^4;
sbit KEY_CLEAR=P2^5;
sbit ALARM_OUT=P2^6;
const uchar displayMode=0x04;
uint  alarmCountTemp;           //ѡ�����𱨾���ʱ 
uchar clockCountLTemp=0x00; //����ʱ��ԭʼֵ��ΪBCD��ʽ�� 
uchar clockCountHTemp=0x03;
uchar displayBuff[4]={'0','0',0x7e,'0'}; //�������ʾ������������λΪʱ�䣬���λΪ����� 
uchar musicFre[4]={0x10,0x20,0x30,0x40};
uchar musicFreTemp;
uchar musicFreCount;
uchar alarm_can_out; //��������� 
uchar game_is_ok;   //������״̬������0x01Ϊ����ʼ 
uchar time_is_over;	//����ʱ����������� 
uchar key_is_press;
uchar clockCountL;  //����ʱ�����ֵ��λ 
uchar clockCountH;  //����ʱ�����ֵ��λ
uchar timer0Temp;   //tiemr0 �жϼ������� 
uchar workMode;     //����������ģʽ,0Ϊ����ģʽ��1Ϊʱ�����ģʽ 
void init_timer0(void)	              //��ʱ10ms 
{
   TMOD|=0x01;                        //GATE=0,TR=1����;C/T=1,counter,0,timer;01ʮ������  
   TH0=0xdc;
   TL0=0x00;
   TR0=1;	                          //timer0 ����λ��Ϊ1ʱ����timer0
   ET0=1;                             //timer0 �ж�ʹ�� 
}
void main()
{
  uchar gameKeyScan;
  init_led();
  init_key();
  init_timer0();
  clockCountL=clockCountLTemp;
  clockCountH=clockCountHTemp;
  displayBuff[S_H]=clockCountH+'0';
  displayBuff[S_L]=clockCountL+'0'; 
  gameKeyScan=0x00;
  game_is_ok=0x00;
  timer0Temp=0x00;
  musicFreTemp=0x00;
  time_is_over=0x00;
  key_is_press=0x00;
  workMode=0x00;
  alarm_can_out=0x00;
  alarmCountTemp=0x00;
  sei();
  while(1)
  {
    ledSweepDisplay(displayBuff,displayMode,4); 
	if(KEY_START==KEY_VALID_VALUE)
	 {
	   if(workMode==0x00)       //ģʽ1 
	   {
	     if(game_is_ok!=0x01)
	     {
	 	   clockCountL=clockCountLTemp;
           clockCountH=clockCountHTemp;
		   displayBuff[S_H]=clockCountH+'0';
		   displayBuff[S_L]=clockCountL+'0'; 
		   displayBuff[NO]='0';
	       game_is_ok=0x01;//����ʼ  
	      }
	   }
	   else	               //ģʽ2 
	   {
	     while(KEY_START==KEY_VALID_VALUE);
		 if(clockCountLTemp<0x09)
		   clockCountLTemp++;
		 else
		  {
		    clockCountLTemp=0x00;
			if(clockCountHTemp<0x05)
			  clockCountHTemp++;
			else
			  clockCountHTemp=0x00;
		  }
          clockCountL=clockCountLTemp;
          clockCountH=clockCountHTemp;
		  displayBuff[S_H]=clockCountH+'0';
		  displayBuff[S_L]=clockCountL+'0'; 		 
	   } 
	 }
	else if(KEY_CLEAR==KEY_VALID_VALUE)
	   {
		 if(workMode!=0x00)
		 {
		   workMode=0x00;      
           displayBuff[SET_MOD]=0x7e;
		 }   
		 else
		 {
		    if(game_is_ok!=0x01)
			{
			   delay(100);    
			   if(KEY_CLEAR==KEY_VALID_VALUE)
			   {
			      delay(100);
				  if(KEY_CLEAR==KEY_VALID_VALUE)
				  {
				    delay(100);
				     while(KEY_CLEAR==KEY_VALID_VALUE)
				     {
					   workMode=0x01;                 //����ģʽ2
				       displayBuff[SET_MOD]=MOD_TWO;
					   ledSweepDisplay(displayBuff,displayMode,4); 
				     }
				  }
			   }
			       
			 }
		  }
		game_is_ok=0x00;
		time_is_over=0x00;
		alarm_can_out=0x00;
        clockCountL=clockCountLTemp;
        clockCountH=clockCountHTemp;
		displayBuff[S_H]=clockCountH+'0';
		displayBuff[S_L]=clockCountL+'0';
		displayBuff[NO]='0';  
	  }
		 


	if(game_is_ok==0x01)
	 {
	   if(time_is_over!=0x01)
	   {
	     gameKeyScan=get_key_value();
		 if(gameKeyScan!=0x00)
		 {
		   game_is_ok=0x00;
		   musicFreCount=musicFre[1];
		   alarm_can_out=0x02;
		   if(KEY_ONE==gameKeyScan)
		     displayBuff[NO]=0x01+'0';
		   if(KEY_TWO==gameKeyScan)
		     displayBuff[NO]=0x02+'0';
		   if(KEY_THREE==gameKeyScan)
		     displayBuff[NO]=0x03+'0';
		   if(KEY_FOUR==gameKeyScan)
		     displayBuff[NO]=0x04+'0';
		   if(KEY_FIVE==gameKeyScan)
		     displayBuff[NO]=0x05+'0';
		   if(KEY_SIX==gameKeyScan)
		     displayBuff[NO]=0x06+'0';
		   if(KEY_SEVEN==gameKeyScan)
		     displayBuff[NO]=0x07+'0';
		   if(KEY_EIGHT==gameKeyScan)
		     displayBuff[NO]=0x08+'0';
		 }
		  
	   }
	  else	//����ʼ��ʱ�䵽 
	   {
	     musicFreCount=musicFre[0];
		 alarm_can_out=0x01;  
	   }

	 }
  }
 }

void timer0_overflowing() interrupt 1 using 1	 //timer0����жϣ�10ms
{
  TH0=0xdc;
  TL0=0x00;
  if((alarm_can_out!=0x01)&&(alarm_can_out!=0x02))
    ALARM_OUT=0;
  else
   {
     if(alarm_can_out==0x01)
      {
	    if(musicFreTemp<musicFreCount)
          musicFreTemp++;
        else
        {
            musicFreTemp=0x00;
	        ALARM_OUT=~ALARM_OUT;
         }
	  }
	 else if(alarm_can_out==0x02)
	  {
	    if(alarmCountTemp<ALARM_COUNT_TIME)
		 {
		    alarmCountTemp++;
		    if(musicFreTemp<musicFreCount)
              musicFreTemp++;
            else
            {
              musicFreTemp=0x00;
	          ALARM_OUT=~ALARM_OUT;
            }
		 }
		else
		 {
		   alarm_can_out=0x00;
		   alarmCountTemp=0x00;
		 }
	  }

   }
  if(game_is_ok==0x01)
  {
     if(timer0Temp<99)	 //���1S�Ƿ� 
       timer0Temp++;
     else
     {
        timer0Temp=0x00;
        if(clockCountL>0x00)
	       clockCountL--;
	    else
	    {
	       if(clockCountH!=0x00)
		    {
		   	  clockCountL=0x09;
			  clockCountH--;
		    } 
		   else
		     time_is_over=0x01;
		   displayBuff[S_H]=clockCountH+'0';	  
	    } 
	    displayBuff[S_L]=clockCountL+'0';
      }  
   }
  
}