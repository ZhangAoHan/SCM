/*-------------------------------------------------------------------------------------------
 			                   STM32ʾ����������
 
 ˵��: ʾ��������������˻�ȡƵ�����ڵ�ʱ������͵����������ɼ���,�Ǻ�������,���ȼ����
 	   ��������λ������,��������λ������λ������ͨѶ������,�Զ�����ͨ��Э��,ÿһ֡����16Byte
	   ������֡������֡���,֡ͷ��֡β��ΪУ����.��ϸͨ��Э����ƶ�д�ڡ�STM32ʾ����ͨ��Э�顷
	   Excel�����.��ζ����ݽ�����Ч����ͽ���ͬʱ��Ҫ���нϸߵĴ���Ч���ǱȽ�ͷ�۵�����,����
	   Ŀǰ��ˮƽ�����˽�Ϊ�򵥵�ASCII����Э�鼼��,ͬʱΪ�˿�����Ӧ��λ������,�ѽ���ģ�����
	   ISR�����,��Ӧ�ٶ�С��1.5ms,ͬʱ�Դ�������֡��δ���Ҳ��һ����Ȥ������.
	   ��������,�Զ����ͨ��Э����Ч���������������ɴ�16000bps,ʵ�ʲ���10666bps.

 �汾: v1.0 2013/11/30 	���ԭʼ�汾  
 	   v3.0 2014/2/18   ������ɰ汾    
  
 BoX��д   
-------------------------------------------------------------------------------------------*/
#include "task_main.h"
#include "task_gui.h"
#include "task_sd.h"

#include "stdio.h"
#include "stdlib.h"
#include "ucos_ii.h"
#include "pincfg.h"
#include "delay.h"
#include "tft_api.h"
#include "indkey.h"
#include "timer.h"
#include "EXTI.H"
#include "adc.h"
#include "usart1.h"
/*-----------------------------------------
		    	��������
------------------------------------------*/
extern OS_EVENT *LCD_Buffer_MUTEX;
extern OS_EVENT *USART_Buffer_MUTEX;
extern OS_EVENT *SDtoRAM_Buffer_MUTEX;

extern uint8_t LCD_Buffer[LCD_BUFFER_SIZE];
extern uint8_t USART_Buffer[USART_BUFFER_SIZE];
extern volatile uint16_t ADCConvertedValue[SAMPDEPTH];

WaveType 	WaveInfo;
WaveMode 	WaveCtrl;
FG_WaveType FG_WaveInfo;	//�źŷ���������

/*-----------------------------------------
 ����˵��:��ʼ���������ò���
------------------------------------------*/
void WaveMode_Init(WaveMode* WaveCtrl)
{
    WaveCtrl->UpdatTrue = 0;
    WaveCtrl->TriggerMode = Trigger_Rising;
	WaveCtrl->TimeBase = 99;
	WaveCtrl->Gain = 3;
}
/*-----------------------------------------
 ����˵��:�����ջ��� 
------------------------------------------*/
void TaskStackChack(void)
{
	OS_STK_DATA data;
	uint8_t i,err;
	for(i=0;i<5;i++)	  //��ǰ������5������
	{
	 	OSTaskStkChk(11+i,&data);
		LCD_Write_String(30,20,"Prio Total Free Used ",Green,Black);

		OSMutexPend(LCD_Buffer_MUTEX,0,&err);	   //ռ���ź���		
		sprintf(LCD_Buffer," %2d  %2d  %2d  %2d ",  11+i,
													 data.OSFree+data.OSUsed,
													 data.OSFree,
													 data.OSUsed);
		LCD_Write_String(30,40+20*i,LCD_Buffer,Green,Black);		
		OSMutexPost(LCD_Buffer_MUTEX);			   //�ͷ��ź���
	}
}
/*-----------------------------------------
 ����˵��:��ȡƵ������ֵ,ͨ������oscilloscope.c
          �е�GetSquareWavePriod()�õ�
------------------------------------------*/
void GetFrequence(void)
{	
	//������ڲ�����Ƶ�ʼ���		
    WaveInfo.Priod = GetSquareWavePriod();
	WaveInfo.Frequency = 1000000 / WaveInfo.Priod;
	
	//��ɸߵ�ƽ������ռ�ձȼ���
	WaveInfo.HighWidth = WaveInfo.Priod - WaveInfo.LowWidth;
	WaveInfo.DutyCycle = WaveInfo.HighWidth*100 / WaveInfo.Priod;		
}

/*-----------------------------------------
 ����˵��:��ȡAD FIFO�е�ԭʼֵ����ʾ
------------------------------------------*/
void GetWaveADCValue(void)
{
	if(WaveCtrl.UpdatTrue == 1 && WaveCtrl.Stop == 0)
	{
		WaveCtrl.UpdatTrue = 0;		
		ShowRealTimeWave();
//		SD_SaveWaveADValue();		//�洢����
//		WaveCtrl.SavedSD = 0;			
		EXTI->IMR |= EXTI_Line1;	//����AD��һ��ת��	
	}
}
/*------------------------------------------------------
 ����˵��:��λ���������ݵ�MCU,��MCU�������
 ע������:�ȶ�����������,�������������,�ٲ���������д
		  �����.������Ϊ�˼ӿ���Ӧ�ٶ�û�в�ȡ�Ӵ�
		  �����ķ�ʽ,���Ƿ���DMA��������ж��д���,����
		  ����ʱ���Լ1����.
--------------------------------------------------------*/
void ReceiveDataFromPC(void)
{
	INT8U err,JieMaOK=0;		//����OK��־λ
	uint32_t Cmd_Data,Value;
	
	JieMaOK = PCtoMCU_Decoding(USART_Buffer,&Cmd_Data,&Value); //������������
	
	if(Cmd_Data>100 && Cmd_Data<200 && JieMaOK==1) //�յ���������(��ʾ���������)
	{
	 	switch(Cmd_Data)
		{
			//��������������
		 	case 101: printf("STOP/RUN\r\n");
					  WaveCtrl.Stop = !WaveCtrl.Stop;
					  break;
		
			case 102: printf("���Բ���\r\n");
					  ShowSavedWave();
					  break;
			
			case 103: printf("���沨��\r\n");
					  break;

			case 104: printf("AC\r\n");
					  JDQ_ACDC = 1;		  		//�������
					  break;

			case 105: printf("DC\r\n");	  	
					  JDQ_ACDC = 0;		  		//ֱ�����
					  break;
		    
			//�������������
			
			case 111: printf("��������\r\n");
					  if(Value>0 && Value<9)	//ȷ��������ȷ
					  	WaveCtrl.Gain = Value;
			          ManualGainScan(WaveCtrl.Gain);
					  break;
			
			case 112: printf("��������\r\n");				  	  
	   		          if(++WaveCtrl.Gain > 8)
	   					WaveCtrl.Gain = 1;
					  ManualGainScan(WaveCtrl.Gain);
					  break;
			
			case 113: printf("�����С\r\n");				      
	   				  if(--WaveCtrl.Gain < 1)
	   					WaveCtrl.Gain = 8;
					  ManualGainScan(WaveCtrl.Gain);
					  break;
		
			case 114: printf("�Զ�����\r\n");
					  break;
			
			//ʱ������������
			
			case 121: printf("����ʱ��Ϊ:%d\r\n",Value);
					  if(Value>=0 && Value<=1000)  //ȷ��������ȷ
					  	WaveCtrl.TimeBase = Value;
					  TimeBaseControl(WaveCtrl.TimeBase);
					  break;
			
			case 122: printf("ʱ������\r\n");					  
					  WaveCtrl.TimeBase += 5;
					  if(WaveCtrl.TimeBase >= 1000)
					  	WaveCtrl.TimeBase = 1000;
					  TimeBaseControl(WaveCtrl.TimeBase);
					  break;
			
			case 123: printf("ʱ����С\r\n");
					  WaveCtrl.TimeBase -= 5;									  
					  if(WaveCtrl.TimeBase <= 1)
					  	WaveCtrl.TimeBase = 1;
					  TimeBaseControl(WaveCtrl.TimeBase);
					  break;
			
			case 124: printf("�Զ�ʱ��\r\n");
					  break;
			
			//���η�����������
			
			case 131: printf("���ǲ�\r\n");
				      FunctionGenerator(Triangle_Wave,FG_WaveInfo.Frequency,
					  								  FG_WaveInfo.Vpp,
					  								  FG_WaveInfo.DutyCycle);
					  break;
			case 132: printf("���β�\r\n");
					  FunctionGenerator(Square_Wave,FG_WaveInfo.Frequency,
					  								FG_WaveInfo.Vpp,
					  								FG_WaveInfo.DutyCycle);
					  break;
			case 133: printf("���Ҳ�\r\n");
					  FunctionGenerator(Sine_Wave,FG_WaveInfo.Frequency,
					  							  FG_WaveInfo.Vpp,
					  							  FG_WaveInfo.DutyCycle);
					  break;
			case 134: printf("������\r\n");
					  FunctionGenerator(Noise_Wave,FG_WaveInfo.Frequency,
					  							   FG_WaveInfo.Vpp,
					  							   FG_WaveInfo.DutyCycle);
					  break;
			case 135: printf("ɨƵ\r\n");
					  break;
			
			//�źŷ���������
		
			case 141: printf("FFT\r\n");				 
					  break;
			case 142: printf("Ƶ��\r\n");
					  break;
			case 143: printf("������\r\n");
					  break;
			case 144: printf("����\r\n");
					  break;
			case 145: printf("ֱ��\r\n");
					  break;

			 default: break;
		}
	}
	
	if(Cmd_Data>1000 && Cmd_Data<2000 && JieMaOK==1) //�յ���������(��ʾ���������)	
	{
	 	switch(Cmd_Data)
		{
			//���ղ��η���������
		 	case 1301: FG_WaveInfo.Frequency = Value; break; 
			case 1302: FG_WaveInfo.Vpp = Value/10.0;  break;//��λ���Ѹ����͡�10��,Ҫ�»���
			case 1303: FG_WaveInfo.DutyCycle = Value; break;
			default  : break;
		}
	}
}
/*----------------------------------------------------------
 ����˵��:����λ�����������ݽ��н���,�������������Э���
 ��������:Revdata[] - ָ����Ҫ����Ļ�����
 		  CmdorData - ָ��INT32U����ָ��,�������,����ָ��
 		  value     - ָ��INT32U����ָ��,�������֡
 �� �� ֵ:����ɹ�����1,����ʧ��(����)����0
 ����ʾ��:JieMaOK = PCtoMCU_Decoding(USART_Buffer,&Cmd_Data,&Value);
          ������Ϊ�˼ӿ���Ӧ�ٶ�û�в�ȡ�Ӵ󻺳����ķ�ʽ,���Ƿ���
		  DMA��������ж��д���,���봦��ʱ���Լ1����.
----------------------------------------------------------*/
uint8_t PCtoMCU_Decoding(uint8_t Revdata[],uint32_t *CmdorData,uint32_t *value)
{
	uint8_t j,k,m,i;
	uint8_t data[10];				//������ʱ�洢��	
	
	if(Revdata[0]=='(' && Revdata[15]==')' )//֡ͷ-֡β
	{	
	 	if(Revdata[1] == 'C') 	 //CMD
		{
			data[0] = 0x43;
			printf("CMD ");
		}	   		 
		if(Revdata[1] == 'D') 	 //DATA
		{
			data[0] = 0x44;
			printf("DATA ");
		}
//			for(i=0;i<16;i++)printf("%c",USART_Buffer[i]);printf("\r\n");
		j = 2;
		k = 1;
		while(Revdata[j] != 'a' && Revdata[j]>='0' && Revdata[j]<='9')	//û����a֮ǰ
		{
			data[k] = Revdata[j];
			k++;
		 	j++;
			if(k>10) break;		//��ֹ������ѭ��
		}
		*CmdorData = atoi(&data[1]);  //������λ��ʼ����,����CMD��DATA			
		for(m=0; m<10; m++)    	//data����Ϊ10
				data[m] = ' ';	//���data������0x20����
		k = 0;
		j++;
		while(Revdata[j] != 'b' && Revdata[j]>='0' && Revdata[j]<='9')
		{
			data[k] = Revdata[j];
			k++;
		 	j++;
			if(k>10) break;		//��ֹ������ѭ��
		}		 
		*value = atoi(data);	//��������
		for(m=0; m<10; m++)    	//data����Ϊ10
				data[m] = ' ';	//���data������0x20����
	}
	else						
	{							
		printf("DataError\r\n");//������ִ�����������ô��ں�DMA
		USART_Buffer[0] = '(';	//�򴮿ڻ���д����ȷ��֡ͷ֡β
		USART_Buffer[15]= ')';
		USART_Buffer[1] = 'E';	//ͬʱд��E(Error)��������֡
		
		USART1_Config();		//�����������ϵͳ�ȶ���ʮ����Ҫ
		return 0;				
	}
	return 1;							 //�������	 	
}
/*-----------------------------------------
 ����˵��:�Է�����λ�������ݽ��б���
 ��������:
------------------------------------------*/
void MCUtoPC_Coding(uint8_t data[])
{

}
/*-----------------------------------------
 ����˵��:���ڷ��Ͳ��β�������λ��
------------------------------------------*/
void SendDataToPC(void)
{
	OS_CPU_SR  cpu_sr = 0u;
	INT8U err;
	
	if(WaveCtrl.Stop != 1)	 //�������STOP��ֹͣ�������ݵ���λ��
	{
		OSMutexPend(LCD_Buffer_MUTEX,0,&err);	   //ռ���ź���
		/* Start(S)-(data)-A-(data)-B-(data)-C-(data)-D-(data)-ect. */
		sprintf(LCD_Buffer," %dA%dB%dC%dD%dE%.2fF%.2fG%.2fH%.2fI%2dJ" 
											  ,WaveInfo.Frequency
											  ,WaveInfo.Priod
										      ,WaveInfo.HighWidth
										      ,WaveInfo.LowWidth
											  ,WaveInfo.DutyCycle
											  ,WaveInfo.Vmax
											  ,WaveInfo.Vmin
											  ,WaveInfo.Vpp
											  ,WaveInfo.Vrms
											  ,GetTempSensor());
		//���ݷ���ʱ��ϣ�������
		OS_ENTER_CRITICAL();
		printf("%s\r\n",LCD_Buffer);
		OSMutexPost(LCD_Buffer_MUTEX);			   //�ͷ��ź���	
		OS_EXIT_CRITICAL();
	}			
}