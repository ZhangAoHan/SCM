/*******************************************************************************
* 文件名称：kongzhi.c                         
* 说明：本文件为小车控制的c文件
* 功能：1.检测障碍物传感器查询 
        2.小车的状态控制
* 修改： 无
* 版本：1.0.0
* 作者：YuanDong 
* 时间：2009.7.14 
*******************************************************************************/

#include	<AT89X52.h>
#define     kongzhi_GLOBAL 1
#include	<kongzhi.h>

  uchar      PWM_t,PWM_t0;                //PWM_t为脉冲宽度(0~100)时间为0~10ms
  uchar      time_count;                  //定时计数
  uint       number,number1;
  uchar      flag;		//flag为小车状态标志,0:停止,1:前进,2:后退
  uchar      flag2;		//flag2为小车状态恢复寄存区,当小车遇到障碍物停止,等到障碍物排除之后,小车在停止之前的状态就寄存在flag2中
  uchar      flag3;		//flag3为小车避障停止延时标志,初始化为0,等待障碍排除之后赋值为1,开始计时,数秒之后恢复停止前的行进状态
  uchar      flag4;     //--flag4为看门狗复位后状态恢复寄存区
  uchar      kind = 0;	//传感器的种类

/********************************************************
*函数名称：void bizhang()
*函数功能：遇到障碍物时的处理函数
*函数入口：无
*函数出口：无
********************************************************/
void	bizhang()
{	
		zhang_ai = 1;
		if(zhang_ai == 0)
	{	
		flag2=flag;
		flag=0;
		while(zhang_ai == 0)
		{	
		keyboard();
		xunji();
		stop();
		WDT_CONTR=0x3b;
		}
		flag3=1;
	}
}

/********************************************************
*函数名称：void stop()
*函数功能：到达目标点的控制函数
*函数入口：无
*函数出口：无
********************************************************/
void	stop()
{
		stop_1=1;				  //目标站点1
		if(stop_1==0)flag=0;
		stop_2=1;				  //目标站点2
		if(stop_2==0)flag=0;	  
		stop_3=1;				  //目标站点3
		if(stop_3==0)flag=0;
}
  
/*******************************************************
*函数名称：void xunji()
*函数功能：查询传感器反馈回来的路线状况，生成相应代码
*函数入口：无
*函数出口：无
********************************************************/
void	xunji()
{		
        uchar	jiekou;
		spy=0xff;
		if(flag==1)
	{
		jiekou=spy&0x0f;
			switch(jiekou)
		{
			/*****左转*****/
			case 0x0d:kind=1;break;	 //0b0000 1101	 
			case 0x0c:kind=2;break;	 //0b0000 1100		 
			case 0x0e:kind=2;break;	 //0b0000 1110
			/*****右转*****/
			case 0x0b:kind=3;break;	 //0b0000 1011
			case 0x07:kind=4;break;	 //0b0000 0111
			case 0x03:kind=4;break;	 //0b0000 0011
			case 0x00:flag=0;break;	 //0b0000 0000
			default:kind=0;break;
		}
	}
		spy=0xff;
		if(flag==2)
	{
		jiekou=spy&0xf0;
			switch(jiekou)
		{
			/*****左转*****/
			case 0xd0:kind=3;break;	 //Ob1101 0000
			case 0xc0:kind=4;break;	 //0b1100 0000
			case 0xe0:kind=4;break;	 //0b1110 0000
			/*****右转*****/
			case 0xb0:kind=1;break;	 //0b1011 0000
			case 0x70:kind=2;break;	 //0b0111 0000
			case 0x30:kind=2;break;	 //0b0011 0000
			case 0x00:flag=0;break;	 //0b0000 0000
			default:kind=0;break;
		}
	}
}

/*******************************************************
*函数名称：void delay()
*函数功能：软件滤波，去抖动
*函数入口：无
*函数出口：无
********************************************************/  
void	delay()
{	
	uchar i,k;
	for(i=20;i>0;i--)
	for(k=248;k>0;k--);
}  
/*******************************************************
*函数名称：uchar du_lie()
*函数功能：读取被按下的键盘的列值
*函数入口：无
k
*函数出口：列数
********************************************************/
uchar	du_lie()
{			
		if((key&0x0f)==0x07){return 0x01;}
		if((key&0x0f)==0x0b){return 0x02;}
		if((key&0x0f)==0x0d){return 0x03;}
		if((key&0x0f)==0x0e){return 0x04;}
		return	0x00;
}
/*******************************************************
*函数名称：uchar key_board()
*函数功能：键盘识别码读取函数
*函数入口：无
*函数出口：键盘的识别码
********************************************************/
uchar	key_board()
{		
		key=0x3f;
		P2_4=0;
		if((key&0x0f)!=0x0f)
	{	delay();
			if((key&0x0f)!=0x0f){return (0x10|du_lie());}
	}	
		key=0x3f;P2_5=0;
		if((key&0x0f)!=0x0f)
	{	delay();
			if((key&0x0f)!=0x0f){return (0x20|du_lie());}
	}			
		return	0x00;
}		
/*******************************************************
*函数名称：void keyboard()
*函数功能：2*4键盘识别,并判断小车运行状况
*函数入口：无
*函数出口：无
********************************************************/
void	keyboard()
{
 		switch(key_board())		
		{	case 0x11:{PWM_t=40;PWM_t0=40;break;}
			case 0x12:{flag=2;flag4=2;flag2=flag;break;}
			case 0x13:{flag=1;flag4=1;flag2=flag;break;}
			case 0x14:{flag=0;flag4=0;break;}
			case 0x21:{PWM_t=100;PWM_t0=100;break;}
			case 0x22:{PWM_t=90;PWM_t0=90;break;}
			case 0x23:{PWM_t=70;PWM_t0=70;break;}
			case 0x24:{PWM_t=50;PWM_t0=50;break;}
			default:break;
		}
}


 	
/*******************************************************
*函数名称：void timer_init()
*函数功能：定时器初始化设置
*函数入口：无
*函数出口：无
********************************************************/
void timer_init()
{
		flag=0;flag3=0;
		key = 0xFF;
	    TMOD = 0x20;						//定时器1为模式2(8位自动重装)
		TF1 = 0;							//清中断标志
		TH1 = timer_data;					//保证定时时长为0.1ms 
		TL1 = TH1;
		ET1 = 1;							//允许T0中断
		TR1 = 1;							//开始计数
		EA = 1;							//中断允许
		ENA = 0;							//电机禁止
	    PWM_t = PWM_t0;					//看门狗复位后速度恢复
	    flag = flag4;						//看门狗复位后小车状态恢复
}
/*******************************************************
*函数名称：void IntTime1() interrupt 3 using 2
*函数功能：定时器中断处理，小车行走控制
*函数入口：无
*函数出口：无
********************************************************/
void IntTime1()interrupt 3	using	2
{
      time_count++;
	  	if(flag3)number++;
		if(number==6000){number=0;number1++;}
		if(number1==8){flag3=0;number1=0;flag=flag2;}	
	  	if(flag==0)ENA=0;				//小车停止,flag=0,小车停止标志
		if(flag==1)						//小车前进,flag=1,小车前进标志
	{
		ENA=1;							//PWM波输出使能
		DR=0;							//直流电机一端接低电平
		DR2=0;							//直流电机一端接低电平
		if(kind==0)						//没有传感器检测到黑线,走直线
        {	if(time_count<PWM_t)
        	{PWM=1;PWM2=1;}
        	else
        	{PWM=0;PWM2=0;}
		}
		if(kind==1)						//左边第一个传感器检测到黑线
        {	
			if(time_count<(PWM_t-20))
        	{PWM=1;}
        	else
        	{PWM=0;}			
			if(time_count<PWM_t)
        	{PWM2=1;}
        	else
        	{PWM2=0;}
		}
		if(kind==2)						//左边第二个传感器检测到黑线
        {	
			if(time_count<3)
        	{PWM=1;}
        	else
        	{PWM=0;}			
			if(time_count<PWM_t)
        	{PWM2=1;}
        	else
        	{PWM2=0;}
		}
		if(kind==3)						//右边第一个传感器检测到黑线
        {	
			if(time_count<(PWM_t-20))
        	{PWM2=1;}
        	else
        	{PWM2=0;}			
			if(time_count<PWM_t)
        	{PWM=1;}
        	else
        	{PWM=0;}
		}
		if(kind==4)						//右边第二个传感器检测到黑线
        {	
			if(time_count<3)
        	{PWM2=1;}
        	else
        	{PWM2=0;}			
			if(time_count<PWM_t)
        	{PWM=1;}
        	else
        	{PWM=0;}
		}
	}
		if(flag==2)						//小车倒退,flag=2,小车倒退标志
	{
		ENA=1;
		PWM=0;
		PWM2=0;
		if(kind==0)						//没有传感器检测到黑线,走直线
	    {	if(time_count<PWM_t)
	        	{DR=1;DR2=1;}
	        	else
	        	{DR=0;DR2=0;}
		}
		if(kind==1)						//左边第一个传感器检测到黑线
	    {	
			if(time_count<(PWM_t-20))
	        {DR=1;}
	        else
	        {DR=0;}			
			if(time_count<PWM_t)
	        {DR2=1;}
	        else
	        {DR2=0;}
		}
		if(kind==2)						//左边第二个传感器检测到黑线
	    {	
			if(time_count<3)
	        {DR=1;}
	        else
	        {DR=0;}			
			if(time_count<PWM_t)
	        {DR2=1;}
	        else
	        {DR2=0;}
		}
		if(kind==3)				   		//右边第一个传感器检测到黑线
	    {	
			if(time_count<(PWM_t-20))
	        {DR2=1;}
	        else
	        {DR2=0;}			
			if(time_count<PWM_t)
	        {DR=1;}
	        else
	        {DR=0;}
		}
		if(kind==4)				  		//右边第二个传感器检测到黑线
	    {	
			if(time_count<3)
	        {DR2=1;}
	        else
	        {DR2=0;}			
			if(time_count<PWM_t)
	        {DR=1;}
	        else
	        {DR=0;}
		}
	}
      if(time_count >= PWM_T)		  	//每输出一个PWM波计数器清一次零,也即PWM波周期长度
        {
         time_count=0;
        }
}

