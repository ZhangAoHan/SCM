/************************************************************
*ʵ�����ƣ��������
*ʵ��˵����ʵ�ֲ������������ת�Լ��Ӽ��ٿ��ƣ�����LCD����ʵʱ
��ʾ���������״̬
*���ߣ�yd
*ʱ�䣺09.06.20
************************************************************/
#include "target.h"
#include "key.h"
#define MOTER_SPEED_NORMAL 10   //���������������
#define MOTER_SPEED_MIN    25   //���������������
uchar timer0Count;              //timer0�ж��������  
uchar moterStep;	            //�������	     (0x00~0x07)
uint  moterSpeed;	            //�ٶ�ֵ�仯��	 (0~moterSpeedMax)
uint  moterSpeedMax;            //�ٶ����ֵ
uchar moterState;               //�������״̬
uchar moterDirect;              //�����ת����,��ֹ/0x00;��ת/0x01;��ת/0x02
uchar moterAddReduce;           //������ټ�������
uchar speedDirect;              //0x01,�������;0x02,�������
bit display_is_ok;              //��ʾ���Ƿ���Ҫ����
/**********************************************************
MOTER_STOP,ֹͣ;MOTER_FRONT_ADD,��ת����
MOTER_FRONT_REDUCE,��ת����;MOTER_FRONT_NORMAL,��ת����
MOTER_FRONT_LOWER,��ת����;MOTER_QUEEN_ADD,��ת����
MOTER_QUEEN_REDUCE,��ת����,MOTER_QUEEN_NOMAL,��ת����
MOTER_QUEEN_LOWER,��ת����
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
  moterSpeedMax=0x00;  //Ĭ��ֹͣ
  moterDirect=0x00;	   //Ĭ��ֹͣ
  moter_state_display(MOTER_STOP);
  display_is_ok=1;
  sei();
  while(1)
  {
    keyValueRead=get_key_value();
	switch(keyValueRead)
	{
	  case KEY_FRONT:	  //��ת
	  {
	    moterState=MOTER_FRONT_LOWER;
		moterDirect=0x01;
		moterSpeedMax=MOTER_SPEED_MIN;
		display_is_ok=0;
		//moter_state_display(MOTER_FRONT_LOWER);
		break; 
	  }
	  case KEY_QUEEN:	  //��ת
	  {
	    moterState=MOTER_QUEEN_LOWER;
		moterDirect=0x02;
		moterSpeedMax=MOTER_SPEED_MIN;
		display_is_ok=0;
		//moter_state_display(MOTER_QUEEN_LOWER);
		break;
	  }
	  case KEY_ADD:		  //����
	  {
	    speedDirect=0x01;
	    moterAddReduce=100;
		display_is_ok=0;
		if(moterDirect==0x01)  //��ת
		  moter_state_display(MOTER_FRONT_ADD);
		else if(moterDirect==0x02)
		  	  moter_state_display(MOTER_QUEEN_ADD);
		break;
	  }
	  case KEY_REDUCE:	  //����
	  {
		speedDirect=0x02;
	    moterAddReduce=100;
		display_is_ok=0;
		if(moterDirect==0x01) //��ת
		  moter_state_display(MOTER_FRONT_REDUCE);
		else if(moterDirect==0x02)
		 	  moter_state_display(MOTER_QUEEN_REDUCE);
		break;
	  }
	  case KEY_STOP:      //ֹͣ
	  {
	    moterState=MOTER_STOP;
	    moterSpeedMax=0x00;    //Ĭ��ֹͣ
        moterDirect=0x00;	   //Ĭ��ֹͣ
		moter_state_display(MOTER_STOP);
		display_is_ok=1;
		break;
	  }
	  default:
	    break;
	}
	if(display_is_ok==0)   //�ж�LCD�����Ƿ���Ҫ����
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
void timer0_overflow(void) interrupt 1 //timer0��ʱ10ms
{
   TH0=0xEE;	  //��ʱ10ms
   TL0=0x00;
   if(timer0Count<moterAddReduce)  //�Ƿ��ж�100�Σ�moterAddReduce�ڼ��ټ��ٴ���ֵ
     timer0Count++;
   else
   {
     timer0Count=0x00;
	 if(speedDirect==0x01)	 //���Ϊ����
	 {
	   if(moterSpeedMax>MOTER_SPEED_NORMAL)
	     moterSpeedMax--;					//�����ٵ�����ֵ
	   else
	   {
	     moterAddReduce=0x00;
		 speedDirect=0x00;	     //�Ѿ����ٵ�����ֵ�����ټ���
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
	 if(moterDirect==0x01) //��ת
	 {
	   if(moterStep>0x00)
	     moterStep--;
	   else
	     moterStep=0x07;
	 }
	 else if(moterDirect==0x02)	//��ת
	      {
		    if(moterStep<0x07)
	          moterStep++;
	        else
	          moterStep=0x00;
	      }
	 ground(moterStep);
   }

}