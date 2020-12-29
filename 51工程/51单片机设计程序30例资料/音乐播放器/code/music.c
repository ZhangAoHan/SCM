#define MUSIC_GLOBAL 1
#include "music.h"
/********************************************
*函数名称：InitialPlayer(void)
*函数功能：初始化音乐播放器
*函数入口：无
*函数出口：无
********************************************/
void InitialPlayer(void)
{
  PlayIO = 0;
  Sound_Temp_TH1 = (65535-(1/1200)*SYSTEM_OSC)/256;	// 计算TL1应装入的初值 	(10ms的初装值)
  Sound_Temp_TL1 = (65535-(1/1200)*SYSTEM_OSC)%256;	// 计算TH1应装入的初值 
  TH1 = Sound_Temp_TH1;
  TL1 = Sound_Temp_TL1;
  TMOD|= 0x11;             //定时器0和定时1工作在模式1
  ET0=1;                   //定时器0溢出中断使能
  TR0= 0;                  //启动定时器0
  TR1= 0;                  //启动定时器1
}
/************************************
*函数名称：Delay1ms(uint count)
*函数功能：ms级延时
*函数入口：延时计数count
*函数出口：无
************************************/
void Delay1ms(uint count)
{
	unsigned int i,j;
	for(i=0;i<count;i++)
	for(j=0;j<120;j++);
}
/**********************************************
*函数名称：MusicTimer0
*函数功能：timer0溢出中断入口，产生音符中断	
*函数入口：无
*函数出口：无
**********************************************/
void MusicTimer0(void) interrupt 1
{
	PlayIO = !PlayIO;
	TH0    = Sound_Temp_TH0;
 	TL0    = Sound_Temp_TL0;
}
/************************************************
*函数名称：Play(uchar *Sound,uchar Signature,
uchar Octachord,uint Speed)
*函数功能：播放音乐函数
*函数入口：乐曲数组指针Sound;调号(0-11)Signature,
*乐曲升多少个半音演奏;升降八度(1-3)Octachord,
*1:降八度, 2:不升不降, 3:升八度;
*演奏速度(1-12000)Speed,值越大速度越快
*函数出口：无
*************************************************/
void Play(uchar *Sound,uchar Signature,uchar Octachord,uint Speed)
{
	uint NewFreTab[12];		//新的频率表
	uchar i,j;
	uint Point,LDiv,LDiv0,LDiv1,LDiv2,LDiv4,CurrentFre,Temp_T,SoundLength;
	uchar Tone,Length,SL,SH,SM,SLen,XG,FD;
	for(i=0;i<12;i++) 				// 根据调号及升降八度来生成新的频率表 
	{
		j = i + Signature;
		if(j > 11)
		{
			j = j-12;
			NewFreTab[i] = FreTab[j]*2;
		}
		else
			NewFreTab[i] = FreTab[j];

		if(Octachord == 1)
			NewFreTab[i]>>=2;
		else if(Octachord == 3)
			NewFreTab[i]<<=2;
	}									
	
	SoundLength = 0;
	while(Sound[SoundLength] != 0x00)	//计算歌曲长度
	{
		SoundLength+=2;
	}
	Point = 0;
	Tone   = Sound[Point];	
	Length = Sound[Point+1]; 			// 读出第一个音符和它时时值
	LDiv0 = 12000/Speed;				// 算出1分音符的长度(几个10ms) 	
	LDiv4 = LDiv0/4; 					// 算出4分音符的长度 
	LDiv4 = LDiv4-LDiv4*SOUND_SPACE; 	// 普通音最长间隔标准 
	TR0	  = 0;
	TR1   = 1;
	while(Point < SoundLength)
	{
		SL=Tone%10; 								//计算出音符 
		SM=Tone/10%10; 								//计算出高低音 
		SH=Tone/100; 								//计算出是否升半 
		CurrentFre = NewFreTab[SignTab[SL-1]+SH]; 	//查出对应音符的频率 	
		if(SL!=0)
		{
			if (SM==1) CurrentFre >>= 2; 		//低音 
			if (SM==3) CurrentFre <<= 2; 		//高音
			Temp_T = 65536-(50000/CurrentFre)*10/(12000000/SYSTEM_OSC);//计算计数器初值
			Sound_Temp_TH0 = Temp_T/256; 
			Sound_Temp_TL0 = Temp_T%256; 
			TH0 = Sound_Temp_TH0;  
			TL0 = Sound_Temp_TL0 + 12; //加12是对中断延时的补偿 
		}
		SLen=LengthTab[Length%10]; 	  //算出是几分音符
		XG=Length/10%10; 			  //算出音符类型(0普通1连音2顿音) 
		FD=Length/100;
		LDiv=LDiv0/SLen; 			  //算出连音音符演奏的长度(多少个10ms)
		if (FD==1) 
			LDiv=LDiv+LDiv/2;
		if(XG!=1)	
			if(XG==0) 				//算出普通音符的演奏长度 
				if (SLen<=4)	
					LDiv1=LDiv-LDiv4;
				else
					LDiv1=LDiv*SOUND_SPACE;
			else
				LDiv1=LDiv/2; 		//算出顿音的演奏长度 
		else
			LDiv1=LDiv;
		if(SL==0) LDiv1=0;
			LDiv2=LDiv-LDiv1; 		//算出不发音的长度 
	  	if (SL!=0)
		{
			TR0=1;
			for(i=LDiv1;i>0;i--) 	//发规定长度的音 
			{
				while(TF1==0);
				TH1 = Sound_Temp_TH1;
				TL1 = Sound_Temp_TL1;
				TF1=0;
			}
		}
		if(LDiv2!=0)
		{
			TR0=0;
			PlayIO=0;
			for(i=LDiv2;i>0;i--) 	//音符间的间隔
			{
				while(TF1==0);
				TH1 = Sound_Temp_TH1;
				TL1 = Sound_Temp_TL1;
				TF1=0;
			}
		}
		Point+=2; 
		Tone=Sound[Point];
		Length=Sound[Point+1];
	}
	PlayIO = 0;
}