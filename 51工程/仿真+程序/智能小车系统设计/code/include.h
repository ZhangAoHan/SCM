#ifndef  include_H
#define  include_H 1
  #include "kongzhi.h"
  #include "keyboard.h"
  #include "pwmout.h"
   			 
  #define    key     P2   							
  #define    PWM_T   100			      //定义PWM的周期T为10ms 

  #define    uchar unsigned char
  #define    uint  unsigned int
  uchar      PWM_t,PWM_t0;                //PWM_t为脉冲宽度(0~100)时间为0~10ms
  uchar      flag;		//flag为小车状态标志,0:停止,1:前进,2:后退
  uchar      flag2;		//flag2为小车状态恢复寄存区,当小车遇到障碍物停止,等到障碍物排除之后,小车在停止之前的状态就寄存在flag2中
  uchar      flag3;		//flag3为小车避障停止延时标志,初始化为0,等待障碍排除之后赋值为1,开始计时,数秒之后恢复停止前的行进状态
  uchar      flag4;     //--flag4为看门狗复位后状态恢复寄存区
  uchar      kind = 0;	//传感器的种类 



#endif