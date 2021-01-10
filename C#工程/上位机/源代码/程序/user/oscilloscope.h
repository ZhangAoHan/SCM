/*---------------------------------------------------------
		  		ʾ������������ģ���ӳ���

 ˵��: ���������ʾ����������Ĺ���,�������������,ʱ����
 	   ����,���ε���ʾ,��ȡ���ε�Ƶ������.�����źŷ�������
	   ����.

	   ������3��ʮ����Ҫ�Ľṹ��,�ֱ���

	   1) WaveMode�ṹ����Ҫ���ʾ������ʾ���ε�һЩ���ò���
	   2) WaveType�ṹ����Ҫ��ɲ��ε������ʱ������Ĵ���,ע�����η�volatile
	   3) FG_WaveType�ṹ����Ҫ����źŷ�����������Ϣ�Ĵ���
	   4) FunctionGeneratorTypeö������Ϊ�˷�ֹ����ĸ�ֵ

	   ��Ϊ����CD4051ģ�⿪��,�����������õ��������,����
	   �ֹ�����������������ϱ�,���ݾ����Ӳ����ͬ�޸�

 ʱ��: 2014��2��8��		-BoX��д
---------------------------------------------------------*/
#ifndef __OSCILLOSCOPE_H__
#define __OSCILLOSCOPE_H__

/*--------------------------------------------------------
			�����������ݽṹ,�洢�˲������ò���
--------------------------------------------------------*/
typedef struct
{
    unsigned char SavedSD;
	unsigned char ReadSD;
	unsigned char UpdatTrue;
    unsigned char Stop;
    unsigned char TriggerMode;
	unsigned char Gain;
	unsigned int  TimeBase;	
    float AmpDiv;
    float TimDiv;
}WaveMode;
/*--------------------------------------------------------
			�������ݽṹ,�洢�˲��εĳ��ò���
--------------------------------------------------------*/
typedef struct
{
    volatile unsigned int HighWidth;
    volatile unsigned int LowWidth;
    volatile float Vmax;
    volatile float Vmin;
	volatile float Vpp;
	volatile float Vrms;
    volatile unsigned int Priod;
    volatile unsigned int DutyCycle;
    volatile unsigned int Frequency;
}WaveType;
/*--------------------------------------------------------
			�źŷ������������ݽṹ
--------------------------------------------------------*/
typedef struct
{
	volatile float Vpp;
    volatile unsigned char DutyCycle;
    volatile unsigned int Frequency;
}FG_WaveType;
/*--------------------------------------------------------
				  ����������ö������
--------------------------------------------------------*/
typedef enum
{ 
  Sine_Wave = 1,
  Triangle_Wave, 
  Rectangular_Wave,
  Square_Wave,
  Sawtooth_Wave,
  Noise_Wave
}FunctionGeneratorType;
/*--------------------------------------------------------
					��������������
--------------------------------------------------------*/
#define GAINX0_05	WaveCtrl.AmpDiv=9.39;JDQ_AV=1;CD4051C=1;CD4051B=0;CD4051A=1
#define GAINX0_1	WaveCtrl.AmpDiv=5.00;JDQ_AV=1;CD4051C=1;CD4051B=1;CD4051A=0
#define GAINX1		WaveCtrl.AmpDiv=1.00;JDQ_AV=0;CD4051C=1;CD4051B=1;CD4051A=1
#define GAINX2		WaveCtrl.AmpDiv=0.52;JDQ_AV=0;CD4051C=1;CD4051B=0;CD4051A=0
#define GAINX4		WaveCtrl.AmpDiv=0.25;JDQ_AV=0;CD4051C=1;CD4051B=0;CD4051A=0
#define GAINX5		WaveCtrl.AmpDiv=0.20;JDQ_AV=0;CD4051C=0;CD4051B=1;CD4051A=0
#define GAINX10		WaveCtrl.AmpDiv=0.10;JDQ_AV=0;CD4051C=0;CD4051B=0;CD4051A=1
#define GAINX25		WaveCtrl.AmpDiv=0.04;JDQ_AV=0;CD4051C=0;CD4051B=0;CD4051A=0


float AutoGainScan(void);
void ManualGainScan(unsigned int gain);
unsigned int GetSquareWavePriod(void);
unsigned int GetSquareWaveDutyCycles(void);
void FunctionGenerator(FunctionGeneratorType ft,unsigned int feq,float amp,unsigned char duty);
void TimeBaseControl(unsigned short int TimeBASE);
void FG_StartOutput(unsigned short int WaveTab[]);

#endif
