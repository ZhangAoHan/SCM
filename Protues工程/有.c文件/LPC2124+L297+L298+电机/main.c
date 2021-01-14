
/****************************************************************************
* File：Main.C
* 功能：
****************************************************************************/
#include  "config.h"

/*******************************************************************************
*名称:IRQ_Eint0()
*功能:外部中断EINT0服务函数
*******************************************************************************/
void  __irq  IRQ_Eint0(void)
{  uint32   i;
   
   i=VICIRQStatus;                //读出VICIRQStatus的值
   i=IO0SET;                      //读取当前P0.5控制值
   if((i&1<<5)==0)                //控制P0.5输出
   { IO0SET=1<<5;
   }
   else
   { IO0CLR=1<<5;
   }
   while((EXTINT&0x01)!=0)        //等待外部中断信号恢复为高电平
   { EXTINT=0x01;                  //清除EINT0中断标志
   }
   VICVectAddr=0x00;
}
/*******************************************************************************
*名称: IRQ_Eint1()
*功能: 外部中断EINT1服务函数
*******************************************************************************/
void  __irq IRQ_Eint1(void)
{ uint32  i;

  i=VICIRQStatus;                   //读出VICIRQStatus的值
  
  i=IO0SET;                         //读出当前P0.4控制值
  if((i&1<<4)==0)                   //控制P0.4控制值
  { IO0SET=1<<4; 
  }
  else
  { IO0CLR=1<<4;
  }
  while((EXTINT&0x02)!=0)           //等待外部中断信号恢复为高电平
  { EXTINT=0x02;                    //清除EINT1中断标志
  }
  
  VICVectAddr=0x00;
}
/*******************************************************************************
*名称:main()
*功能:初始化外部中断0,外部中断1及I/O连接等
*******************************************************************************/
int main(void)
{ 
  PINSEL0=0x20080000;               //设置I/O口工作模式,P0.14设置为EINT1
  PINSEL1=0x00000001;               //P0.16设置为EINT0
  TargetInit();   
  IO0DIR=1<<5|1<<4|1<<9;            //设置P0.4,P0.5和P0.9为输出,其它I/O为输入
  IO0CLR=1<<5|1<<4;
  
  IO0SET=1<<5|1<<4;
  VICIntSelect=0x00000000;          //设置所有通道为IRQ中断
  VICVectCntl0=0x2E;                //EINT0通道分配到IRQ Slot0,即优先级最高
  VICVectAddr0=(int)IRQ_Eint0;      //设置EINT0向量地址
  VICVectCntl1=0x2F;
  VICVectAddr1=(int)IRQ_Eint1;
  VICIntEnable=0x0001C000;           //使能EINT0,EINT1中断
  EXTINT=0x07;                       //清除外部中断
 
  while(1)                           //等待中断
  {
      
    PWMMR0=Fpclk/4;                  //设置PWM周期
    PWMMR6=Fpclk/4/2;                //设置PWM占空比
    PWMLER=0x41;                     //PWMMR0,PWMMR6锁存,更新PWM占空比
  }
 
}
