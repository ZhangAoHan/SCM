#include "motor.h"
#include "stm32f10x.h"

void Motor_Init(void)
{		
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	//PA����������
	GPIO_InitStructure.GPIO_Pin = MT_LFT_A1 | MT_LFT_B1| MT_LFT_A2 | MT_LFT_B2; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//PC���ҵ������
	GPIO_InitStructure.GPIO_Pin =  MT_RGT_A1 | MT_RGT_B1| MT_RGT_A2 | MT_RGT_B2;                                                        
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);  

	/*��ʼ�����ת��λ��*/
	MT_LFT_OFF();
	MT_RGT_OFF();

	/*��ʼ����ʱ��TIMER*/
	Timer3_Init(200,3599);//�����������
	Timer2_Init(200,3599);//�� 

  }
/***************************************************************************
*����������Ƴ���
****************************************************************************/
void StepLeft(void)
{	
	static int ucRunStepLft=-1;

	switch(GmLeft.cDir)//������з���
	{
		case MOTOR_GOAHEAD:         /*��ǰ����*/
			if(++ucRunStepLft>=8)
		  {
				ucRunStepLft=0;
			}
			break;
		case MOTOR_GOBACK:          /*��󲽽�*/
			if(--ucRunStepLft>=8)//���
			{
				ucRunStepLft=7;
			}
		  break;
		default:
			break;
  }
		
			switch(ucRunStepLft)
			{
				case 0:
					MT_LFT_STEP1_SET();
					break;
				case 1:
					MT_LFT_STEP2_SET();
					break;
				case 2:
					MT_LFT_STEP3_SET();
					break;
				case 3:
					MT_LFT_STEP4_SET();
					break;
				case 4:
					MT_LFT_STEP5_SET();
					break;
				case 5:
					MT_LFT_STEP6_SET();
					break;
				case 6:
					MT_LFT_STEP7_SET();
					break;
				case 7:
					MT_LFT_STEP8_SET();
					break;
				default:
					break;
			} 
}


void StepRight(void)
{	
	static int  ucRunStepRgt=-1;

	switch(GmRight.cDir)
	{
		case MOTOR_GOAHEAD:
			if(++ucRunStepRgt>=8)
		  ucRunStepRgt=0;
			break;
		case MOTOR_GOBACK:
			if(--ucRunStepRgt>=8)
			{
				ucRunStepRgt=7;
			}
			break;
		default:
			break;
  }
	
			switch(ucRunStepRgt)
			{
				case 0:
					MT_RGT_STEP1_SET();
					break;
				case 1:
					MT_RGT_STEP2_SET();
					break;
				case 2:
					MT_RGT_STEP3_SET();
					break;
				case 3:
					MT_RGT_STEP4_SET();
					break;
				case 4:
					MT_RGT_STEP5_SET();
					break;
				case 5:
					MT_RGT_STEP6_SET();
					break;
				case 6:
					MT_RGT_STEP7_SET();
					break;
				case 7:
					MT_RGT_STEP8_SET();
					break;
				default:
					break;
			}
}

/**************************************************************************
*�������������״̬
*GOAHEAD
*GOBACK
*GORIGHE
*GOLEFE	
***************************************************************************/
void Motor_GOStraight(void)
{ 
	GmRight.cDir = MOTOR_GOAHEAD;
	GmRight.cState = MOTOR_RUN;
	GmRight.ulPulse = 20; 

	GmLeft.cDir= MOTOR_GOAHEAD;
	GmLeft.cState = MOTOR_RUN;
	GmLeft.ulPulse = 20; 
  
}
void Motor_GOLeft(void)		//����ת �ұ߲������ת��
{
	//GmLeft.cDir= MOTOR_GOAHEAD;
	GmLeft.cState = MOTOR_STOP;
  	GmRight.cDir = MOTOR_GOAHEAD;
	GmRight.cState = MOTOR_RUN;
	GmRight.ulPulse = 20; 
}
void Motor_GORight(void)
{
	GmLeft.cDir= MOTOR_GOAHEAD;
	GmLeft.cState = MOTOR_RUN;
	GmLeft.ulPulse = 20;
 // GmRight.cDir = MOTOR_GOAHEAD;
	GmRight.cState = MOTOR_STOP;
}
void Motor_Stop(void)
{
	//GmLeft.cDir= MOTOR_GOAHEAD;
	GmLeft.cState = MOTOR_STOP;
  //GmRight.cDir = MOTOR_GOAHEAD;
	GmRight.cState = MOTOR_STOP;
}



