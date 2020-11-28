/******************************************************************************
* 文件名称：TRAFFIC.c							   
* 功能：十字路口交通灯控制程序：
        正常时，EW方向计时60s，SN方向计时40s
       	若按时间加按键（Add_Button）按钮，EW、SN方向各加5s，不可大于99s，79s
    	若按时间减按键（Reduces_Button）按键，EW、SN方向各减5s，不可小于40s，20s
		若按EW方向强制通行(QZ_EW_Btton)按钮，EW方向强制通行，SN方向禁止通行	  
		若按SN方向强制通行(QZ_SN_Btton)按钮，SN方向强制通行，EW方向禁止通行
* 当前版本：1.0
* 作者：YuanDong
* 完成日期：2009年6月18日
******************************************************************************/
	
#define TRAFFIC_GLOBAL 1  
#include "TRAFFIC.H"  
/********************************************************************************************
* 函数名称：延时子程序
* 功    能：延时，给LED显示的延时时间
* 入口参数：时间参数
* 出口参数：无
*********************************************************************************************/
void	Delay(uchar	 a)
	{
		uchar	i;
		i=a;
		while(i--){;}
	}


/********************************************************************************************
* 函数名称：显示子函数
* 功    能：EW方向，SN方向主干道数码管显示驱动
* 入口参数：无
* 出口参数：无
*********************************************************************************************/
void	Display(void)
	{
		char h,l;
		h=Time_EW/10;		//EW方向计时的十位数
		l=Time_EW%10;		//EW方向计时的个位数
  	    P0=table[l];		//显示EW计时时间的低位
		EW_LED2=1;
		Delay(2);
		EW_LED2=0;
	    P0=table[h];		//显示EW计时时间的高位
		EW_LED1=1;
		Delay(2);
		EW_LED1=0;

		h=Time_SN/10;		//SN方向计时的十位数
		l=Time_SN%10;		//SN方向计时的个位数
		P0=table[l];		//显示SN计时时间的低位
		SN_LED2=1;
		Delay(2);
		SN_LED2=0;
	    P0=table[h];		//显示SN计时时间的高位
		SN_LED1=1;
		Delay(2);
		SN_LED1=0;
		

		h= EW1/10;			//直行时间的十位
		l= EW1%10;			//直行时间的个位
		P0=table[l];		//时间的个位显示
		Time_Show_LED1=1;
		Delay(2);
        Time_Show_LED1=0;
		P0=table[h];		//时间的十位显示
		Time_Show_LED2=1;
		Delay(2);
	    Time_Show_LED2=0;
} 


/********************************************************************************************
* 函数名称：外部0中断服务程序
* 功    能：中断，检测按钮的类别，执行相应的操作；
            若Add_Button==0，通行时间加5s ；
            若Reduces_Button==0，通行时间减5s ；
            若Busy_Btton==0，开繁忙信号灯，关特殊信号灯，通行时间45s，30s；
            若Add_Button==0，关繁忙信号灯，开特殊信号灯，通行时间75s，55s；
* 入口参数：无
* 出口参数：无
*********************************************************************************************/
void	EXINT0(void) interrupt 0 using 0
	{
		EA = 0;                    //关中断
if(Add_Button==0)                  //时间加
       { 
            EW1+=5;				   //通行时间加5s
            SN1+=5;
              if(EW1>=100)		   //通行时间不得大于100s,80s
			   {
			     EW1=99;
			     SN1=79;
               }
            }
if(Reduces_Button==0)             //时间减
       {
            EW1-=5;			      //通行时间减5s
            SN1-=5;
            if(EW1<=40)		      //通行时间不得小于40s，20s
              { 
			     EW1=40;
                 SN1=20;
               }
		    } 		
		EA = 1;                  //开中断
	}
 
/******************************************************************************
* 函数名称:外部中断1
* 功    能:中断，当遇到紧急情况，需要人工控制时，强制直行的函数处理
           若QZ_EW_Btton按下时，EW方向绿灯亮，SN方向红灯亮 ，并点亮QZ_EW_LED指示灯
		   若QZ_SN_Btton按下时，EW方向红灯亮，SN方向绿灯亮 ，并点亮QZ_SN_LED指示灯
* 入口参数:无
* 出口参数:无
********************************************************************************/
void EXINT1(void) interrupt 2 using 2
{
EA = 0;  

if(QZ_EW_Btton==0)              //EW方向强制通行按键是否按下
        {	    
			QZ_EW = ~QZ_EW; 	//
			QZ_SN = 0;							   		
			if(QZ_EW)  
			{QZ_EW_LED = 1;
			 QZ_SN_LED = 0;}
			else  	   QZ_EW_LED = 0;
        }
if(QZ_SN_Btton==0)             //测试按键是否按下，按下为特殊状态
        {
		    QZ_SN = ~QZ_SN;
			QZ_EW = 0;	 
			if(QZ_SN)  
			{QZ_SN_LED = 1;
			 QZ_EW_LED = 0;} 
			else  	   
			 QZ_SN_LED = 0;
	    }			              
EA = 1;			 
}


/******************************************************************************
* 函数名称:定时器0中断
* 功    能:作为定时器为交通计时提供时钟信号
* 入口参数:无
* 出口参数:无
********************************************************************************/
	void timer0(void)interrupt 1 using 1
{
	static uchar count;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	count++;
	
	if(count==10)
	{
	  if(Flag_SN_Yellow==1)       //测试SN黄灯标志位
	  {SN_Yellow=~SN_Yellow;}
	  if(Flag_EW_Yellow==1)       //测试EW黄灯标志位
	  {EW_Yellow=~EW_Yellow;} 
	}
	if(count==20)
	{
	Time_EW--;
	Time_SN--;
	if(Flag_SN_Yellow==1)        //测试SN黄灯标志位
	    {SN_Yellow=~SN_Yellow;}
	if(Flag_EW_Yellow==1)        //测试EW黄灯标志位
	    {EW_Yellow=~EW_Yellow;}
	count=0;
	} 	
}  


/******************************************************************************
* 函数名称:main()
* 功    能:主函数
* 入口参数:无
* 出口参数:无
********************************************************************************/
void	main(void)

{ 
	QZ_EW_LED = 0;
	QZ_SN_LED = 0;
	QZ_EW = 0;
	QZ_SN = 0;
	IT0=1;	                    //INT0负跳变触发
	IT1=1;                  	//INT0负跳变触发	
    TMOD=0x01;                  //定时器工作于方式1
	TH0=(65536-50000)/256;      //定时器赋初值
	TL0=(65536-50000)%256;
	EA=1;                       //CPU开中断总允许
	ET0=1;                      //开定时中断
	EX0=1;                      //开外部INTO中断
	EX1=1;                      //开外部INT1中断
    TR0=1;                      //启动定时

     while(1)

{				/*******SN通行，EW红灯*** ***************/
                Flag_EW_Yellow=0;             //EW关黄灯显示信号
				Time_EW=EW;	
				Time_SN=SN;		
				while(Time_SN>=5&QZ_EW == 0&QZ_SN == 0)
			    {P1=LIGHT[0];	              //SN通行，EW红灯
		         Display();}
				/*******SN黄灯亮，等待左拐信号，EW红灯***/
			    P1=0x00;
				while(Time_SN>=0&QZ_EW == 0&QZ_SN == 0)
			   {Flag_SN_Yellow=1;	          //SN开黄灯信号位
			    EW_Red=1;                     //SN黄灯亮，等待左拐信号，EW红灯	 			 
			     Display();
				}
				/*******SN左拐绿灯亮，EW红灯*************/
			    Flag_SN_Yellow=0;             //SN关黄灯显示信号
				Time_SN=SNL;								 
				while(Time_SN>=5&QZ_EW == 0&QZ_SN == 0)
				{P1=LIGHT[2];                 //SN左拐绿灯亮，EW红灯
				 Display();}

			  /*******SN黄灯亮,等待停止信号，EW红灯******/
				P1=0x00;
				while(Time_SN>=0&QZ_EW == 0&QZ_SN == 0)
			   {Flag_SN_Yellow=1;	          //SN开黄灯信号位
			    EW_Red=1;                     //SN黄灯亮,等待停止信号，EW红灯			   	
			    Display();}		   

			   /***********赋值**********/
				EW=EW1;
				SN=SN1;
				EWL=EWL1;
				SNL=SNL1;

				/*******EW通行，SN红灯******************/
				Flag_SN_Yellow=0;              //SN关黄灯显示信号
				Time_EW=SN;
				Time_SN=EW;
			    while(Time_EW>=5&QZ_EW == 0&QZ_SN == 0)
			    {P1=LIGHT[4];	                //EW通行，SN红灯
				 Display();}

				/*****EW黄灯亮，等待左拐信号，SN红灯****/
				P1=0X00;
				while(Time_EW>=0&QZ_EW == 0&QZ_SN == 0)
			   {Flag_EW_Yellow=1;               //EW开黄灯信号位
			    SN_Red=1;                       //EW黄灯亮，等待左拐信号，SN红灯	
			    Display();}

				/*******EW左拐绿灯亮，SN红灯**********/
				Flag_EW_Yellow=0;	            //EW关黄灯显示信号
				Time_EW=EWL;
				while(Time_EW>=5&QZ_EW == 0&QZ_SN == 0)
				{P1=LIGHT[6];                   //EW左拐绿灯亮，SN红灯
				 Display();}

				/****EW黄灯亮，等待停止信号，SN红灯***/
				P1=0X00;							  
				while(Time_EW>=0&QZ_EW == 0&QZ_SN == 0)
			   {Flag_EW_Yellow=1;               //EW开黄灯信号位
			    SN_Red=1;                       //EW黄灯亮，等待停止信号，SN红灯	
			    Display();}

				/*********EW方向强制通行**************/
				while(QZ_EW) 
				{Time_EW = 88;
				 Time_SN = 88;
				 EW1 = 88; 								
				 Display();
				 P1=LIGHT[4];	                //EW通行，SN红灯    	
				 EW1 = 60;
				 SN1 = 40;}  

				/*********SN方向强制通行**************/
				while(QZ_SN)
				{Time_EW = 88;
				 Time_SN = 88;
				 EW1 = 88; 								
				 Display();
				 P1=LIGHT[0];	                 //EW通行，SN红灯  	
				 EW1 = 60;
				 SN1 = 40;}  
			
			   	/***********赋值**********/
			    EW=EW1;
				SN=SN1;
				EWL=EWL1;
				SNL=SNL1;
			}

	}