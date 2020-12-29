/************************************************************
*实例名称：步进电机
*实例说明：实现步进电机的正反转以及加减速控制，并在LCD屏上实时
显示步进电机的状态
*作者：yd
*时间：09.06.20
************************************************************/
#include "target.h"
#include "key.h"
#define MOTER_SPEED_NORMAL 10   //电机正常运行上限
#define MOTER_SPEED_MIN    25   //电机低速运行下限
uchar timer0Count;              //timer0中断溢出计数  
uchar moterStep;	            //电机步数	     (0x00~0x07)
uint  moterSpeed;	            //速度值变化量	 (0~moterSpeedMax)
uint  moterSpeedMax;            //速度最快值
uchar moterState;               //电机运行状态
uchar moterDirect;              //电机运转方向,静止/0x00;正转/0x01;反转/0x02
uchar moterAddReduce;           //电机加速及减速量
uchar speedDirect;              //0x01,电机加速;0x02,电机减速
bit display_is_ok;              //显示屏是否需要更新
/**********************************************************
MOTER_STOP,停止;MOTER_FRONT_ADD,正转加速
MOTER_FRONT_REDUCE,正转减速;MOTER_FRONT_NORMAL,正转正常
MOTER_FRONT_LOWER,正转低速;MOTER_QUEEN_ADD,反转加速
MOTER_QUEEN_REDUCE,反转减速,MOTER_QUEEN_NOMAL,反转正常
MOTER_QUEEN_LOWER,反转低速
***********************************************************/
void main()
{
  uchar keyValueRead;
  target_init();
  moterState=MOTER_STOP;
  timer0Count=0x00;
  moterAddReduce=0x00;
  moterStep=0x00;
  moterSpeed=0x00;   
  moterSpeedMax=0x00;  //默认停止
  moterDirect=0x00;	   //默认停止
  moter_state_display(MOTER_STOP);
  display_is_ok=1;
  sei();
  while(1)
  {
    keyValueRead=get_key_value();
	switch(keyValueRead)
	{
	  case KEY_FRONT:	  //正转
	  {
	    moterState=MOTER_FRONT_LOWER;
		moterDirect=0x01;
		moterSpeedMax=MOTER_SPEED_MIN;
		display_is_ok=0;
		//moter_state_display(MOTER_FRONT_LOWER);
		break; 
	  }
	  case KEY_QUEEN:	  //反转
	  {
	    moterState=MOTER_QUEEN_LOWER;
		moterDirect=0x02;
		moterSpeedMax=MOTER_SPEED_MIN;
		display_is_ok=0;
		//moter_state_display(MOTER_QUEEN_LOWER);
		break;
	  }
	  case KEY_ADD:		  //加速
	  {
	    speedDirect=0x01;
	    moterAddReduce=100;
		display_is_ok=0;
		if(moterDirect==0x01)  //正转
		  moter_state_display(MOTER_FRONT_ADD);
		else if(moterDirect==0x02)
		  	  moter_state_display(MOTER_QUEEN_ADD);
		break;
	  }
	  case KEY_REDUCE:	  //减速
	  {
		speedDirect=0x02;
	    moterAddReduce=100;
		display_is_ok=0;
		if(moterDirect==0x01) //正转
		  moter_state_display(MOTER_FRONT_REDUCE);
		else if(moterDirect==0x02)
		 	  moter_state_display(MOTER_QUEEN_REDUCE);
		break;
	  }
	  case KEY_STOP:      //停止
	  {
	    moterState=MOTER_STOP;
	    moterSpeedMax=0x00;    //默认停止
        moterDirect=0x00;	   //默认停止
		moter_state_display(MOTER_STOP);
		display_is_ok=1;
		break;
	  }
	  default:
	    break;
	}
	if(display_is_ok==0)   //判断LCD内容是否需要更新
	{
	   switch(moterSpeedMax)
       {
         case MOTER_SPEED_NORMAL:
	     {
	       if(moterDirect==0x01)
		     moter_state_display(MOTER_FRONT_NORMAL);
		   else if(moterDirect==0x02)
		     moter_state_display(MOTER_QUEEN_NOMAL);
		   display_is_ok=1;
	       break;
	     }
	    case MOTER_SPEED_MIN:
	    {
	      if(moterDirect==0x01)
		    moter_state_display(MOTER_FRONT_LOWER);
		  else if(moterDirect==0x02)
		    moter_state_display(MOTER_QUEEN_LOWER);
		  display_is_ok=1;
	      break;
	    }
	    default:
	      break;
      }
	}
  
 
  }
}
void timer0_overflow(void) interrupt 1 //timer0定时10ms
{
   TH0=0xEE;	  //定时10ms
   TL0=0x00;
   if(timer0Count<moterAddReduce)  //是否中断100次，moterAddReduce在加速减速处赋值
     timer0Count++;
   else
   {
     timer0Count=0x00;
	 if(speedDirect==0x01)	 //如果为加速
	 {
	   if(moterSpeedMax>MOTER_SPEED_NORMAL)
	     moterSpeedMax--;					//最大加速到正常值
	   else
	   {
	     moterAddReduce=0x00;
		 speedDirect=0x00;	     //已经加速到正常值，不再加速
	   }
	     
	 }
	 else if(speedDirect==0x02)
	 {
	   	if(moterSpeedMax<MOTER_SPEED_MIN)
	      moterSpeedMax++;
	    else
	    {
	      moterAddReduce=0x00;
		  speedDirect=0x00;
	    }
	 }
        
   }

   if(moterSpeed<moterSpeedMax)
     moterSpeed++;
   else
   {
     moterSpeed=0x00;
	 if(moterDirect==0x01) //正转
	 {
	   if(moterStep>0x00)
	     moterStep--;
	   else
	     moterStep=0x07;
	 }
	 else if(moterDirect==0x02)	//反转
	      {
		    if(moterStep<0x07)
	          moterStep++;
	        else
	          moterStep=0x00;
	      }
	 ground(moterStep);
   }

}