#include "Control.h"
int Balance_Pwm,Velocity_Pwm,Turn_Pwm;
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
	  int Amplitude=5000;    //===PWM满幅是7200 限制在6900
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
   float Bias,kp=185,kd=0.35;
	 int balance;
	 Bias=Angle-2.0;       //===求出平衡的角度中值 和机械相关
	 balance=kp*Bias+Gyro*kd;   //===计算平衡控制的电机PWM  PD控制   kp是P系数 kd是D系数 
	 return balance;
}
int velocity(int Left,int Right,int motor)   //速度  pi控制
{  
		static float Velocity,Encoder_Least,Encoder;
		static float Encoder_Integral;
		float kp=50,ki=kp/200;
		Encoder_Least=(Left+Right)-motor;
		Encoder*=0.8;
		Encoder+=Encoder_Least*0.2;
		Encoder_Integral+=Encoder;
		Velocity=Encoder*kp+ Encoder_Integral*ki;
		return Velocity;
}int turn(int encoder_left,int encoder_right,float gyro)//转向控制
{
	 static float Turn_Target,Turn,Encoder_temp,Turn_Convert=0.9,Turn_Count;
	  float Turn_Amplitude=88/10,Kp=42,Kd=0.5;     
	  //=============遥控左右旋转部分=======================//
  	if(1==Flag_Left||1==Flag_Right)                      //这一部分主要是根据旋转前的速度调整速度的起始速度，增加小车的适应性
		{
			if(++Turn_Count==1)
			Encoder_temp=myabs(encoder_left+encoder_right);
			Turn_Convert=50/Encoder_temp;
			if(Turn_Convert<0.6)Turn_Convert=0.6;
			if(Turn_Convert>3)Turn_Convert=3;
		}	
	  else
		{
			Turn_Convert=0.9;
			Turn_Count=0;
			Encoder_temp=0;
		}			
		if(1==Flag_Left)	           Turn_Target-=Turn_Convert;
		else if(1==Flag_Right)	     Turn_Target+=Turn_Convert; 
		else Turn_Target=0;
	
    if(Turn_Target>Turn_Amplitude)  Turn_Target=Turn_Amplitude;    //===转向速度限幅
	  if(Turn_Target<-Turn_Amplitude) Turn_Target=-Turn_Amplitude;
  	//=============转向PD控制器=======================//
		Turn=-Turn_Target*Kp -gyro*Kd;                 //===结合Z轴陀螺仪进行PD控制
	  return Turn;
}

void Motor_Control(void)
{
	 Balance_Pwm =balance(Angle_Balance,Gyro_Balance);
	 Velocity_Pwm=velocity(left,right,Motor);
	 Turn_Pwm   =turn(left,right,Gyro_Turn);            //===转向环PID控制
	 Moto1=Balance_Pwm-Velocity_Pwm+Turn_Pwm;                            //===计算左轮电机最终PWM
 	 Moto2=Balance_Pwm-Velocity_Pwm-Turn_Pwm;                            //===计算右轮电机最终PWM
   	 Xianfu_Pwm();
     if(Turn_Off(Angle_Balance)==0) 	
	 Set_Pwm(Moto1,Moto2);                                               //===赋值给PWM寄存器 
}

