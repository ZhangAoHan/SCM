#include "Control.h"

int Balance_Pwm;
int Velocity_Pwm;
// 400 0.8  -0.2  能自动后退
// 410  0.8 -0.04  基本稳定

int balance(float Angle,float Gyro)   //PD直立环
{  
   float Bias,kp=-350,kd=-0.7;
	 int balance;
	 Bias=Angle-0.2;       //===求出平衡的角度中值 和机械相关
	 balance=kp*Bias+Gyro*kd;   //===计算平衡控制的电机PWM  PD控制   kp是P系数 kd是D系数 
	 return balance;
}
int velocity(int Left,int Right)   //速度  pi控制
{  
		static float Velocity,Encoder_Least,Encoder;
		static float Encoder_Integral;
		float kp=90,ki=0.4;
		Encoder_Least=(Left+Right)-0;
		Encoder*=0.8;
		Encoder+=Encoder_Least*0.2;
		Encoder_Integral+=Encoder;
		Velocity=Encoder*kp+ Encoder_Integral*ki;
		return Velocity;
}
void Set_Pwm(int moto1,int moto2)
{
    	if(moto1<0)			AIN2=0,	BIN1=0,			BIN2=1,		AIN1=1;
			else 	          AIN2=1,BIN1=1,			BIN2=0,			AIN1=0;

			PWMA=myabs(moto1);
			PWMB=myabs(moto1);
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
			{	                                                 //===倾角大于40度关闭电机
      temp=1;                                            //===Flag_Stop置1关闭电机
			AIN1=0;                                            
			AIN2=0;
			BIN1=0;
			BIN2=0;
      }
			else
      temp=0;
      return temp;			
}
void Motor_Control()
{
	 Balance_Pwm =balance(Angle_Balance,Gyro_Balance);
	 Velocity_Pwm=velocity(left,right);
//	 Moto1=Balance_Pwm+Velocity_Pwm;                            //===计算左轮电机最终PWM
// 	 Moto2=Balance_Pwm+Velocity_Pwm;                            //===计算右轮电机最终PWM
		 Moto1=Balance_Pwm;                            //===计算左轮电机最终PWM
 	 Moto2=Balance_Pwm;                            //===计算右轮电机最终PWM
   	 Xianfu_Pwm();
     if(Turn_Off(Angle_Balance)==0) 	
	 Set_Pwm(Moto1,Moto2);                                               //===赋值给PWM寄存器 
}


