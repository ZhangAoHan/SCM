#include "Key.h"
#include "led.h"
#define KEY_VALID_VALUE  0      //主持人按键有效电平 
#define MOD_TWO          0x49   //模式显示字符 
#define ALARM_COUNT_TIME 1000   //选手回答时报警时间，10S
sbit KEY_START=P2^4;
sbit KEY_CLEAR=P2^5;
sbit ALARM_OUT=P2^6;
const uchar displayMode=0x04;
uint  alarmCountTemp;           //选手抢答报警计时 
uchar clockCountLTemp=0x00; //抢答时间原始值，为BCD码式的 
uchar clockCountHTemp=0x03;
uchar displayBuff[4]={'0','0',0x7e,'0'}; //数码管显示缓冲区，低两位为时间，最高位为抢答号 
uchar musicFre[4]={0x10,0x20,0x30,0x40};
uchar musicFreTemp;
uchar musicFreCount;
uchar alarm_can_out; //允许报警输出 
uchar game_is_ok;   //抢答器状态变量，0x01为抢答开始 
uchar time_is_over;	//抢答时间计数到变量 
uchar key_is_press;
uchar clockCountL;  //抢答时间计数值低位 
uchar clockCountH;  //抢答时间计数值高位
uchar timer0Temp;   //tiemr0 中断计数变量 
uchar workMode;     //抢答器工作模式,0为抢答模式，1为时间调整模式 
void init_timer0(void)	              //定时10ms 
{
   TMOD|=0x01;                        //GATE=0,TR=1运行;C/T=1,counter,0,timer;01十六进制  
   TH0=0xdc;
   TL0=0x00;
   TR0=1;	                          //timer0 控制位，为1时启动timer0
   ET0=1;                             //timer0 中断使能 
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
	   if(workMode==0x00)       //模式1 
	   {
	     if(game_is_ok!=0x01)
	     {
	 	   clockCountL=clockCountLTemp;
           clockCountH=clockCountHTemp;
		   displayBuff[S_H]=clockCountH+'0';
		   displayBuff[S_L]=clockCountL+'0'; 
		   displayBuff[NO]='0';
	       game_is_ok=0x01;//抢答开始  
	      }
	   }
	   else	               //模式2 
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
					   workMode=0x01;                 //进入模式2
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
	  else	//抢答开始后时间到 
	   {
	     musicFreCount=musicFre[0];
		 alarm_can_out=0x01;  
	   }

	 }
  }
 }

void timer0_overflowing() interrupt 1 using 1	 //timer0溢出中断，10ms
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
     if(timer0Temp<99)	 //检测1S是否到 
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