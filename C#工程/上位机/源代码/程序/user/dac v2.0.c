/*------------------------------------------------------------------------------------------
		    				STM32 DAC������������(v2.0)
 
 ˵��: 1) STM32�ڲ��Դ�2��12λDAC,��ѹ�����.���������������е�DAC1ͨ�������ѹ.ת����Χ��
          0~Vref,�ܶ���ӷ�PA4->DAC1  PA5->DAC2,ʹ�÷�����,��������.ʹ��TIM2��Ϊ��������
		  Դ����DAC1�������ǲ�.

	   2) V2.0������Ӳ���������ǲ�,���ò�����DMA�������Ҳ�,���ǲ�,���β��ȵ�,���ܸ���
	      ǿ�����,ʹ����DMA2ͨ��3,��DAC1.ע��!�����������sdcard.c���ڳ�ͻ,ͬʱʹ�ÿ��ܵ�
		  ������.SDIO��DMAʹ�õ���DMA2ͨ��4,DAC2-DMAʹ�õ�Ҳ��DMA2ͨ��4
		  Ƶ�ʼ��㹫ʽ:
		  Feq=72MHz/(TIM_Prescaler+1)/TIM_Period/���ε���
 
 ʱ��: 2014��2��5��    BoX��д
 �汾: V1.0-�������ǲ���֤ͨ��
       V2.0-��������β��� 
-----------------------------------------------------------------------------------------*/
#include "dac.h"
#include "stm32f10x.h"
/*--------------------------
 	  1������32�㲨�α�
--------------------------*/
uc16 SineWaveTab[32] = {2047, 2447, 2831, 3185, 3498, 3750, 3939, 4056, 4095, 4056,
                      	3939, 3750, 3495, 3185, 2831, 2447, 2047, 1647, 1263, 909, 
                      	599 , 344 , 155 , 38,0, 38, 155, 344, 599, 909, 1263, 1647};

uc16 TriangleWaveTab[32] = {0,255,511,767,1023,1279,1535,1791,2047,2303,2559,2815,3071,3327,3583,3839,4095,
							3839,3583,3327,3071,2815,2559,2303,2047,1791,1535,1279,1023,767,511,255};

uc16 SawtoothWaveTab[32] = {127,255,383,511,639,767,895,1023,1151,1279,1407,1535,1663,1791,1919,2047,2175,
							2303,2431,2559,2687,2815,2943,3071,3199,3327,3455,3583,3711,3839,3967,4095};

u16  AnyWaveTab[32] = {0};	  //�洢����Ĳ�������
/*-------------------------------------
 ��������: DAC��������,Ĭ�ϲ������Ҳ�
 ��������: ��
 �� �� ֵ: ��
-------------------------------------*/
void DAC_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	DAC_InitTypeDef  DAC_InitStructure;
	DMA_InitTypeDef  DMA_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC,ENABLE);
	//DAC1->PA4   DAC2->PA5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//����Ϊģ������
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_4);   //PA4 = 1
		
	DAC_InitStructure.DAC_Trigger = DAC_Trigger_T2_TRGO;
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;
	DAC_Init(DAC_Channel_1, &DAC_InitStructure);
	
	DACTriggerByTIM2(800,0);		  //2812Hz���Ҳ�
	
	DMA_DeInit(DMA2_Channel3);
	DMA_InitStructure.DMA_PeripheralBaseAddr = 0x40007408; //DAC_DHR12R1_Address
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)SineWaveTab;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStructure.DMA_BufferSize = 32;				   //���ε���32
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
/*--------------------------
 ��������: DAC���ֱ����ѹ����
 ��������: ��ѹֵvol
 �� �� ֵ: ��
--------------------------*/
void Set_DAC_Value(unsigned int vol)	//vod:0~3300 = 0~3.3V
{
	float temp;
	temp = vol;
	temp /= 1000;
	temp = temp*(4095/3.3);
	DAC_SetChannel1Data(DAC_Align_12b_R,temp);
}
/*-----------------------------------------------
��������: TIM2��ʱ������ģ��
��������: ARR�Ĵ���ֵ0-65535,Ԥ��Ƶֵ0-65535
����ʾ��: DACTriggerByTIM2(1,1);
-----------------------------------------------*/
void DACTriggerByTIM2(unsigned short int Auto_Reload,unsigned short int Clock_Div)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

	TIM_TimeBaseStructure.TIM_Prescaler =  Clock_Div; 			//ʱ��Ԥ��Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode =  TIM_CounterMode_Up;//���ϼ���
	TIM_TimeBaseStructure.TIM_Period = Auto_Reload;				//�Զ���װֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;	    //ʱ�ӷ�Ƶ1
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);
	TIM_SelectOutputTrigger(TIM2,TIM_TRGOSource_Update);       //ʹ��TIM2�¼�������ΪDAC����
	TIM_Cmd(TIM2,ENABLE);    //��TIM2
}
