#define MUSIC_GLOBAL 1
#include "music.h"
/********************************************
*�������ƣ�InitialPlayer(void)
*�������ܣ���ʼ�����ֲ�����
*������ڣ���
*�������ڣ���
********************************************/
void InitialPlayer(void)
{
  PlayIO = 0;
  Sound_Temp_TH1 = (65535-(1/1200)*SYSTEM_OSC)/256;	// ����TL1Ӧװ��ĳ�ֵ 	(10ms�ĳ�װֵ)
  Sound_Temp_TL1 = (65535-(1/1200)*SYSTEM_OSC)%256;	// ����TH1Ӧװ��ĳ�ֵ 
  TH1 = Sound_Temp_TH1;
  TL1 = Sound_Temp_TL1;
  TMOD|= 0x11;             //��ʱ��0�Ͷ�ʱ1������ģʽ1
  ET0=1;                   //��ʱ��0����ж�ʹ��
  TR0= 0;                  //������ʱ��0
  TR1= 0;                  //������ʱ��1
}
/************************************
*�������ƣ�Delay1ms(uint count)
*�������ܣ�ms����ʱ
*������ڣ���ʱ����count
*�������ڣ���
************************************/
void Delay1ms(uint count)
{
	unsigned int i,j;
	for(i=0;i<count;i++)
	for(j=0;j<120;j++);
}
/**********************************************
*�������ƣ�MusicTimer0
*�������ܣ�timer0����ж���ڣ����������ж�	
*������ڣ���
*�������ڣ���
**********************************************/
void MusicTimer0(void) interrupt 1
{
	PlayIO = !PlayIO;
	TH0    = Sound_Temp_TH0;
 	TL0    = Sound_Temp_TL0;
}
/************************************************
*�������ƣ�Play(uchar *Sound,uchar Signature,
uchar Octachord,uint Speed)
*�������ܣ��������ֺ���
*������ڣ���������ָ��Sound;����(0-11)Signature,
*���������ٸ���������;�����˶�(1-3)Octachord,
*1:���˶�, 2:��������, 3:���˶�;
*�����ٶ�(1-12000)Speed,ֵԽ���ٶ�Խ��
*�������ڣ���
*************************************************/
void Play(uchar *Sound,uchar Signature,uchar Octachord,uint Speed)
{
	uint NewFreTab[12];		//�µ�Ƶ�ʱ�
	uchar i,j;
	uint Point,LDiv,LDiv0,LDiv1,LDiv2,LDiv4,CurrentFre,Temp_T,SoundLength;
	uchar Tone,Length,SL,SH,SM,SLen,XG,FD;
	for(i=0;i<12;i++) 				// ���ݵ��ż������˶��������µ�Ƶ�ʱ� 
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
	while(Sound[SoundLength] != 0x00)	//�����������
	{
		SoundLength+=2;
	}
	Point = 0;
	Tone   = Sound[Point];	
	Length = Sound[Point+1]; 			// ������һ����������ʱʱֵ
	LDiv0 = 12000/Speed;				// ���1�������ĳ���(����10ms) 	
	LDiv4 = LDiv0/4; 					// ���4�������ĳ��� 
	LDiv4 = LDiv4-LDiv4*SOUND_SPACE; 	// ��ͨ��������׼ 
	TR0	  = 0;
	TR1   = 1;
	while(Point < SoundLength)
	{
		SL=Tone%10; 								//��������� 
		SM=Tone/10%10; 								//������ߵ��� 
		SH=Tone/100; 								//������Ƿ����� 
		CurrentFre = NewFreTab[SignTab[SL-1]+SH]; 	//�����Ӧ������Ƶ�� 	
		if(SL!=0)
		{
			if (SM==1) CurrentFre >>= 2; 		//���� 
			if (SM==3) CurrentFre <<= 2; 		//����
			Temp_T = 65536-(50000/CurrentFre)*10/(12000000/SYSTEM_OSC);//�����������ֵ
			Sound_Temp_TH0 = Temp_T/256; 
			Sound_Temp_TL0 = Temp_T%256; 
			TH0 = Sound_Temp_TH0;  
			TL0 = Sound_Temp_TL0 + 12; //��12�Ƕ��ж���ʱ�Ĳ��� 
		}
		SLen=LengthTab[Length%10]; 	  //����Ǽ�������
		XG=Length/10%10; 			  //�����������(0��ͨ1����2����) 
		FD=Length/100;
		LDiv=LDiv0/SLen; 			  //���������������ĳ���(���ٸ�10ms)
		if (FD==1) 
			LDiv=LDiv+LDiv/2;
		if(XG!=1)	
			if(XG==0) 				//�����ͨ���������೤�� 
				if (SLen<=4)	
					LDiv1=LDiv-LDiv4;
				else
					LDiv1=LDiv*SOUND_SPACE;
			else
				LDiv1=LDiv/2; 		//������������೤�� 
		else
			LDiv1=LDiv;
		if(SL==0) LDiv1=0;
			LDiv2=LDiv-LDiv1; 		//����������ĳ��� 
	  	if (SL!=0)
		{
			TR0=1;
			for(i=LDiv1;i>0;i--) 	//���涨���ȵ��� 
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
			for(i=LDiv2;i>0;i--) 	//������ļ��
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