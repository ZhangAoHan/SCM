/*---------------------------------------------------------
		  ADC������������
	˵��: ʾ����AD��������,������������,AD��������Ϊ1.286M
	      ���Ҳ����ʧ�����Ƶ��300kHz
		  ���ǲ����ʧ�����Ƶ��150kHz
		  ���β����ʧ�����Ƶ��100kHz
	ʱ��: 2013��11��19��
---------------------------------------------------------*/
#include "stm32f10x.h"
#include "adc.h"
#include "oscilloscope.h"
#include "ucos_ii.h"
#include "tft_api.h"
/*-----------------------------------------
		    	��������
------------------------------------------*/
extern WaveType WaveInfo;
extern WaveMode WaveCtrl;
volatile u16 ADCConvertedValue[SAMPDEPTH];//ADת��������,ռ��RAM 0.8KB

/*-----------------------------------------
		    	ADC1�˿ڳ�ʼ��
------------------------------------------*/
void ADC1_GPIO_Init(void)
{
	GPIO_InitTypeDef IO_Init;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOC,ENABLE);
	//C1ģ������
	IO_Init.GPIO_Pin = GPIO_Pin_1;
	IO_Init.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOC,&IO_Init);
}

/* #define ADC1_DR_Address ((unsigned int)0x40012400+0x4c) */
/* unsigned short int ADC1_DMA_Value; */
/*--------------------------------------------------
 ����˵��:����ADC1���AD�ɼ�,�Ǳ�ʾ��������ĵĲ���.
 ���÷���:ADC1��TIM3�ṩ�Ĵ����¼����д���ADת��,��
 		  ��TIM3�����ʾͿ�����ɲ����ʵĸı�.ͬʱ��
		  ��DMA������ݴ���,ע��ͨ��1����ڲ��¶ȴ�
		  ����AD�ɼ�. 
--------------------------------------------------*/
void ADC1_Mode_Config(void)
{
	//����DMA
	DMA_InitTypeDef DMA_csh;
	ADC_InitTypeDef ADC_csh;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	DMA_DeInit(DMA1_Channel1);  					   //DMA��λ,ͨ��1
	DMA_csh.DMA_PeripheralBaseAddr = ADC1_DR_Address;  //ADC1��ַ
	DMA_csh.DMA_MemoryBaseAddr = (unsigned int)ADCConvertedValue;  //�ڴ��ַ
	DMA_csh.DMA_DIR = DMA_DIR_PeripheralSRC;  
	DMA_csh.DMA_BufferSize = SAMPDEPTH;  			  		//�����СΪ�������
	DMA_csh.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //�����ַ�̶�
	DMA_csh.DMA_MemoryInc = DMA_MemoryInc_Enable; 			//�ڴ��ַ����
	DMA_csh.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;  
	DMA_csh.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_csh.DMA_Mode = DMA_Mode_Circular;  					//ѭ������
	DMA_csh.DMA_Priority = DMA_Priority_High;  				//DMA���ȼ���
	DMA_csh.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1,&DMA_csh);  						//д��DMA1���ò���
	DMA_Cmd(DMA1_Channel1,ENABLE);	   						//ʹ��DMA1ͨ��1
	DMA_ITConfig(DMA1_Channel1,DMA_IT_TC,ENABLE);			//ʹ��DMA CH1�ж�

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	//����TIM3������18MHz,ΪAD�ṩ����
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure); 
	TIM_TimeBaseStructure.TIM_Period = 1;          
	TIM_TimeBaseStructure.TIM_Prescaler = 99; 	//������18M��ÿ�����ֵʱ�����������      
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;    
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	TIM_SelectOutputTrigger(TIM3,TIM_TRGOSource_Update); //ʹ��TIM3�¼�������ΪADC����
	
	//����ADC
	ADC_csh.ADC_Mode = ADC_Mode_Independent;  		//����ADCģʽ
    ADC_csh.ADC_ScanConvMode = DISABLE;   			//�ر�ɨ��ģʽ
	ADC_csh.ADC_ContinuousConvMode = DISABLE;  		//����ADת������
	ADC_csh.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T3_TRGO;  //��TIM3�ṩ�Ĵ����¼����д���ADת��
	ADC_csh.ADC_DataAlign = ADC_DataAlign_Right; 	//�����Ҷ���
	ADC_csh.ADC_NbrOfChannel = 1;  					//Ҫת����ͨ����Ŀ1
	ADC_Init(ADC1,&ADC_csh);   						//д��ADC1���ò���
	ADC_RegularChannelConfig(ADC1,ADC_Channel_11,1,ADC_SampleTime_1Cycles5);//��������1M
	ADC_DMACmd(ADC1,ENABLE); 						//ʹ��ADC1 DMA
	ADC_ExternalTrigConvCmd(ADC1,ENABLE);			//��ADC1�ⲿ����
	
	ADC_InjectedChannelConfig(ADC1,ADC_Channel_16,1,ADC_SampleTime_239Cycles5);	 //����ADC1ͨ��16Ϊע��ͨ��1
	ADC_ExternalTrigInjectedConvConfig(ADC1,ADC_ExternalTrigInjecConv_None);	 //�������ע��ͨ����ת��
	ADC_TempSensorVrefintCmd(ENABLE);											 //ʹ���¶ȴ�����

	ADC_Cmd(ADC1,ENABLE); 							//ʹ��ADC1
	ADC_ResetCalibration(ADC1);	  					//��λУ׼�Ĵ���
	while(ADC_GetResetCalibrationStatus(ADC1));     //�ȴ�У׼�Ĵ�����λ���
	ADC_StartCalibration(ADC1);	  					//��ʼУ׼
	while(ADC_GetCalibrationStatus(ADC1)); 			//�ȴ�У׼���
	TIM_Cmd(TIM3,ENABLE);
}
/*-----------------------------------------
 ����˵��:ͨ��ע��ͨ��1ת���ڲ��¶ȴ�����
 		  ADֵ,��ȡ10����Ч����ȡƽ������ 
------------------------------------------*/
u16 GetTempSensor(void)   
{ 
	u16 temp=0,i,k=0;
	for(i=0; i<10; )
	{
		ADC_SoftwareStartInjectedConvCmd(ADC1,ENABLE);	//�������ע��ͨ����ת��
		k = (0x6EE - ADC_GetInjectedConversionValue(ADC1,ADC_InjectedChannel_1)) / 0x05 + 25;
		if(k>0 && k<100)
		{
			temp += k;
			i++;
		}
	}
	temp /= 10;
	return temp;	     
}
/*-----------------------------------------
 ����˵��:ADC1��ʼ�� 
------------------------------------------*/
void ADC1_Init(void)
{
	ADC1_GPIO_Init();
	ADC1_Mode_Config();
}
/*-----------------------------------------
 ����˵��:ADC����DMAͨ��1�жϷ������
 		  DMA��ADֵ���䵽��������ɺ�رն�
		  ʱ��3(��Ϊ����ADת���Ķ�ʱ��)ͬʱ
		  �ø�����ɱ�־λΪ1,����ʱ��3��Ӧ
		  ���п���. 
------------------------------------------*/
void DMA1_Channel1_IRQHandler()
{
      OSIntNesting++;  
      DMA_ClearFlag(DMA1_FLAG_TC1);	//���DMA��������ж�
      TIM_Cmd(TIM3,DISABLE);		//�ر�TIM3
      WaveCtrl.UpdatTrue = 1;		//�Ѿ����һ�β���FIFO,����������������
      OSIntExit();
}
/*-----------------------------------------
 ����˵��:����AD������ 
------------------------------------------*/
void Earse_AD_FIFO(void)
{
	uint32_t i;
 	for(i=0; i<SAMPDEPTH; i++)
	{
		ADCConvertedValue[i] = 0;
	}	
}
