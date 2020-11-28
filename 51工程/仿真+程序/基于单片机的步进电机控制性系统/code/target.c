#define TARGET_GLOBAL 1
#include "target.h"
#include "dot.h"
void timer0_init(void)
{
   TMOD|=0x01;    //MODEL1,timer
   TH0=0xDC;	  //定时10ms
   TL0=0x00;
   ET0=1;	     //中断使能
   TR0=1;		 //关闭定时器0
}
void target_init(void)
{
  timer0_init();
  Lcd_Initial();
}
/************************************************
*函数名称：display_head(void)
*函数功能：显示“步进电机运行状态”字样
*函数入口：无
*函数出口：无
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
*函数名称：display_state(state)
*函数功能：显示电机状态“停止”,“正转”,“反转”
*函数入口：state,电机状态
*函数出口：无
*说明：state:0x01,停止;0x02,正转;0x03,反转
************************************************/
void display_state(state)
{
  switch(state)
  {  
    case 0x01:   //显示“停止”
	{
	  Lcd_Character_16X16(1,60,0,MOTER_STATE[0]); //停
	  Lcd_Character_16X16(1,60,16,MOTER_STATE[1]);//止
	  break;
	}
	case 0x02:	 //显示“正转”
	{
	  Lcd_Character_16X16(1,60,0,MOTER_STATE[2]); //正
	  break;
	}
	case 0x03:	 //显示“反转”
	{
	  Lcd_Character_16X16(1,60,0,MOTER_STATE[3]); //反
	  break;
	}
	default:
	  break;
  }
  if((state==0x02)||(state==0x03))
    Lcd_Character_16X16(1,60,16,MOTER_STATE[4]); //转
}
/************************************************
*函数名称：display_speed(speed)
*函数功能：显示电机速度状态
*函数入口：speed,电机速度状态
*函数出口：无
*说明：speed:0x01,正常;0x02,低速;0x03,加速;
             0x04,减速
************************************************/
void display_speed(speed)
{
   switch(speed)
   {
     case 0x01:
	 {
	   Lcd_Character_16X16(1,60,32,SPEED_STATE[4]); //正
	   Lcd_Character_16X16(1,60,48,SPEED_STATE[5]); //常
	   break;
	 }
	 case 0x02:
	 {
	   Lcd_Character_16X16(1,60,32,SPEED_STATE[2]); //低
	   break;
	 }
	 case 0x03:
	 {
	   Lcd_Character_16X16(1,60,32,SPEED_STATE[0]); //加
	   break;
	 }
	 case 0x04:
	 {
	   Lcd_Character_16X16(1,60,32,SPEED_STATE[1]); //减
	   break;
	 }
	 default:
	   break;
   }
   if((speed==0x02)||(speed==0x03)||(speed==0x04))
     Lcd_Character_16X16(1,60,48,SPEED_STATE[3]);   //速 
}
/*************************************************
*函数名称：moter_state_display(uchar moterState)
*函数功能：实现步进电机状态显示
*函数入口：moterState,电机运行状态
*函数出口：无
*说明：moterState:0x01,停止;0x02,正转加速运行;
0x03,正转减速运行;0x04,正转正常运行;
0x05,正转低速运行;0x06,反转加速运行;
0x07,反转减速运行;0x08,反转正常运行；
0x09,反转低速运行
*************************************************/
void moter_state_display(uchar moterState)
{
  Lcd_Clear(); 
  display_head();
  switch(moterState)
  {
    case MOTER_STOP:  //停止
	{
	  display_state(0x01);
	  break;
	}
	case MOTER_FRONT_ADD:	//正转加速运行
	{
	  display_state(0x02);
	  display_speed(0x03);
	  break;
	}
	case MOTER_FRONT_REDUCE:  //正转减速运行
	{
	  display_state(0x02);
	  display_speed(0x04);
	  break;
	}
	case MOTER_FRONT_NORMAL:	//正转正常运行
	{
	  display_state(0x02);
	  display_speed(0x01);
	  break;
	}
	case MOTER_FRONT_LOWER:	//正转低速运行
	{
	  display_state(0x02);
	  display_speed(0x02);
	  break;
	}
	case MOTER_QUEEN_ADD:	//反转加速运行
	{
	  display_state(0x03);
	  display_speed(0x03);
	  break;
	}
	case MOTER_QUEEN_REDUCE: //反转减速运行
	{
	  display_state(0x03);
	  display_speed(0x04);
	  break;
	}
	case MOTER_QUEEN_NOMAL: //反转正常运行
	{
	  display_state(0x03);
	  display_speed(0x01);
	  break;
	}
	case MOTER_QUEEN_LOWER: //反转低速运行
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
    Lcd_Character_16X16(1,60,64,SPEED_STATE[6]); //运
	Lcd_Character_16X16(1,60,80,SPEED_STATE[7]); //行
  }

}
/*******************************************************
*函数名称：ground(step)
*函数功能：给电机的四个相极送信号
*函数入口：step,电机相位的第几步
*函数出口：无
*说明：步进电机转步数，分八步
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