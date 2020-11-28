#include "Control.h"
int Balance_Pwm;
void Set_Pwm(int moto1,int moto2)
{
    	if(moto1>0)			AIN2=0,	BIN1=0,			BIN2=1,		AIN1=1;    //需要前进
			else 	          AIN2=1,BIN1=1,			BIN2=0,			AIN1=0;   //需要后退
		if(moto2>0)			AIN2=0,	BIN1=0,			BIN2=1,		AIN1=1;    //需要前进
			else 	          AIN2=1,BIN1=1,			BIN2=0,			AIN1=0;   //需要后退
			PWMA=myabs(moto1);
			PWMB=myabs(moto2);
}
void Xianfu_Pwm(void)
{	
	  int Amplitude=6900;    //===PWM满幅是7200 限制在6900
    if(Moto1<-Amplitude) Moto1=-Amplitude;	
		if(Moto1>Amplitude)  Moto1=Amplitude;	
	  if(Moto2<-Amplitude) Moto2=-Amplitude;	
		if(Moto2>Amplitude)  Moto2=Amplitude;		
	
}
int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}

u8 Turn_Off(float angle)
{
	    u8 temp;
			if(angle<-20||angle>20)
			{	                                                 //===倾角大于20度关闭电机
      temp=1;                                            
			AIN1=0;                                            
			AIN2=0;
			BIN1=0;
			BIN2=0;
      }
			else
      temp=0;
      return temp;			
}
int balance(float Angle,float Gyro)   //PD直立环
{  
   float Bias,kp=280,kd=1;
	 int balance;
	 Bias=Angle-1.2;       //===求出平衡的角度中值 和机械相关
	 balance=kp*Bias+Gyro*kd;   //===计算平衡控制的电机PWM  PD控制   kp是P系数 kd是D系数 
	 return balance;
}
void Motor_Control(void)
{
	 Balance_Pwm =balance(Angle_Balance,Gyro_Balance);
	 Moto1=Balance_Pwm;                            //===计算左轮电机最终PWM
 	 Moto2=Balance_Pwm;                            //===计算右轮电机最终PWM
   	 Xianfu_Pwm();
     if(Turn_Off(Angle_Balance)==0) 	
	 Set_Pwm(Moto1,Moto2);                                               //===赋值给PWM寄存器 
}

