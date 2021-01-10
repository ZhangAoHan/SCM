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
#include "oscilloscope.h"
#include "ucos_ii.h"
#include "pincfg.h"
#include "tft_api.h"
#include "dac.h"
#include "stdio.h"

#include "task_main.h"
#include "task_gui.h"

/*-----------------------------------------
		    	��������
 ˵��: WaveTab������Ϊ���������
------------------------------------------*/
unsigned int   IntFullTime=0; 		//�������β�TIM5�ж��������

extern uint16_t SineWaveTab[32];	 //32�������Ҳ���
extern uint16_t TriangleWaveTab[32];
extern uint16_t SquareWaveTab[32];
extern uint16_t SawtoothWaveTab[32];
extern uint16_t AnyWaveTab[32];
extern uint8_t  InterruptTimes;

extern WaveType 	WaveInfo;
extern WaveMode 	WaveCtrl;
extern FG_WaveType  FG_WaveInfo;
/*-------------------------------------------
 ��������: �Զ�ɨ���������
 ����ֵ  : float��ɨ������
 ����ʾ��: AutoGain = GainScan();
-------------------------------------------*/
float AutoGainScan(void)
{
 	unsigned char i;
	float gain;
	for(i=1;i<=14;i++)
	{
	 	switch(i)	  //ÿ������ɨ����250ms�Է��̵�������������
		{
			case 1:   GAINX0_05;  gain = 0.05;OSTimeDlyHMSM(0,0,1,250);break;
			case 2:   GAINX0_1;	  gain = 0.1; OSTimeDlyHMSM(0,0,1,250);break;
			case 3:   GAINX1;	  gain = 1.0; OSTimeDlyHMSM(0,0,1,250);break;
			case 4:   GAINX2;	  gain = 2.0; OSTimeDlyHMSM(0,0,1,250);break;
			case 5:   GAINX4;	  gain = 4.0; OSTimeDlyHMSM(0,0,1,250);break;
			case 6:   GAINX10;	  gain = 10.0;OSTimeDlyHMSM(0,0,1,250);break;
			case 7:   GAINX25;	  gain = 25.0;OSTimeDlyHMSM(0,0,1,250);break;
			default:  break;
		}
		ShowRealTimeWave();
		if(WaveInfo.Vmax>=2.40 && WaveInfo.Vmax<=3.3 && WaveInfo.Vmin<1.0) //����ɼ�����AD���ں��ʵĵ�λ
		{
//			GainControl(gain);
			return gain;  //��������ֵ
		}	
	}
	return 0.0;  //���ִ����14��ɨ�趼û�гɹ�
}

void ManualGainScan(unsigned int gain)
{
	switch(gain)	  //ÿ������ɨ����250ms�Է��̵�������������
	{
		case 1:   GAINX0_05;  LCD_Write_String(300,230,"X0.05 ",Yellow,Black);
				  break;
		case 2:   GAINX0_1;	  LCD_Write_String(300,230,"X0.1  ",Yellow,Black);
				  break;
		case 3:   GAINX1;	  LCD_Write_String(300,230,"X1.0  ",Yellow,Black);
				  break;
		case 4:   GAINX2;	  LCD_Write_String(300,230,"X2.0  ",Yellow,Black);
				  break;
		case 5:   GAINX4;	  LCD_Write_String(300,230,"X4.0  ",Yellow,Black);
			      break;
		case 6:   GAINX5;	  LCD_Write_String(300,230,"X5.0  ",Yellow,Black);
				  break;
		case 7:   GAINX10;	  LCD_Write_String(300,230,"X10.0 ",Yellow,Black);
				  break;
		case 8:   GAINX25;	  LCD_Write_String(300,230,"X25.0 ",Yellow,Black);
			      break;
		default:  break;
	}   
}

/*-----------------------------------------------
	��������: ��ȡ���β�����
	��ǰ����: ����Ƶ�ʷ�Χ300Hz~200KHz
	          �������ڷ�Χ3.3ms~5us
-----------------------------------------------*/
unsigned int GetSquareWavePriod(void)
{
	unsigned int temp;
	temp = IntFullTime * 2000;
	temp += (unsigned int)TIM_GetCounter(TIM5);
    IntFullTime = 0;
	TIM_SetCounter(TIM5,0);
	InterruptTimes = 0;
	EXTI->IMR |= EXTI_Line0;	//�����ⲿ�ж�0
	return temp;
}
/*-----------------------------------------------
 ��������: ����������
 ��������: ft   - ��������
 		   feq  - Ƶ��(Hz)
		   amp  - ���(V)
		   duty - ռ�ձ�(%)
-----------------------------------------------*/
void FunctionGenerator(FunctionGeneratorType ft,uint32_t feq,float amp,uint8_t duty)
{
	DAC_InitTypeDef  DAC_InitStructure;
	char i,iH;
		
	DACTriggerByTIM2(2250000/feq,0);   //�趨����Ƶ��
		
	if(ft == Triangle_Wave)			   //�޸ı�׼���εķ�ֵ��������
	{
		for(i=0; i<32; i++)
			AnyWaveTab[i] = (u16)((amp / 3.3) * TriangleWaveTab[i]);
		FG_StartOutput(AnyWaveTab);	   //��ʼ���		
	}

	if(ft == Square_Wave)
	{	
		iH = (32.0 * (duty / 100.0));  //����ռ�ձ��ڲ��α���±���
		for(i=iH; i<32; i++)		   //���ߵ�ƽ
			AnyWaveTab[i] = (u16)((amp / 3.3) * 4095);
		for(i=0; i<iH; i++)		       //���͵�ƽ
			AnyWaveTab[i] = 0;
		FG_StartOutput(AnyWaveTab);
	}
		
	if(ft == Sine_Wave)
	{		
		for(i=0; i<32; i++)
			AnyWaveTab[i] = SineWaveTab[i];
		for(i=0; i<32; i++)
			AnyWaveTab[i] = (u16)((amp / 3.3) * SineWaveTab[i]);
		FG_StartOutput(AnyWaveTab);	
	}

	if(ft == Sawtooth_Wave)
	{
	 	for(i=0; i<32; i++)
			AnyWaveTab[i] = (u16)((amp / 3.3) * SawtoothWaveTab[i]);
		FG_StartOutput(AnyWaveTab);
	}
	//����Ӳ�����
	if(ft == Noise_Wave)
	{
	 	DAC_InitStructure.DAC_Trigger = DAC_Trigger_T2_TRGO;  //DACת����TIM2����������
		DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_Noise;	//��������
		DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_TriangleAmplitude_4095; 
		DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;
	    DAC_Init(DAC_Channel_1,&DAC_InitStructure);
		DAC_Cmd(DAC_Channel_1,ENABLE);
	}		
}
/*-----------------------------------------------
 ��������: ���벨�α�ʼ�������
 ��������: WaveTab[] - 32�㲨�α���������
-----------------------------------------------*/
void FG_StartOutput(uint16_t WaveTab[])
{	
	DMA_InitTypeDef DMA_InitStructure;
	DAC_InitTypeDef  DAC_InitStructure;
	
	DAC_DMACmd(DAC_Channel_1,DISABLE);
	DAC_Cmd(DAC_Channel_1,DISABLE);
	DMA_Cmd(DMA2_Channel3,DISABLE);
	
	DAC_InitStructure.DAC_Trigger = DAC_Trigger_T2_TRGO;
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = 0;	 //����ʡ,���򲻹���
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;
	DAC_Init(DAC_Channel_1, &DAC_InitStructure);

	DMA_DeInit(DMA2_Channel3);
	DMA_InitStructure.DMA_PeripheralBaseAddr = 0x40007408;//DAC_DHR12R1�Ĵ�����ַ(���ֲ�)
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)WaveTab;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStructure.DMA_BufferSize = 32;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA2_Channel3, &DMA_InitStructure);
	
	DMA_Cmd(DMA2_Channel3, ENABLE);	
	DAC_Cmd(DAC_Channel_1, ENABLE);	
	DAC_DMACmd(DAC_Channel_1, ENABLE);
}
/*-----------------------------------------------
 ��������: ʱ������
 ��������: ʱ������(Ԥ��Ƶϵ��)
-----------------------------------------------*/
void TimeBaseControl(uint16_t TimeBASE)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
		
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure); 
	TIM_TimeBaseStructure.TIM_Period = 1;          
	TIM_TimeBaseStructure.TIM_Prescaler = TimeBASE;       
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;    
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);	
}

