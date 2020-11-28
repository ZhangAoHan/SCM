#include"stm32f10x.h"
#include "UserConfiguration.h"

void TIM1_Configuration(void)//TIM1��ͨ���ֱ����PWM1/PWM2/PWM3/PWM4,��Ӧ����ΪPA8/PA9/PA10/PA11
{
    GPIO_InitTypeDef GPIO_InitStructure; 
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;    
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;       
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   //�������������Ϊ3.3V      
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = PWMPeriod;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;

	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);
	
	TIM1->CCR1 = 0;  //PA8 �����������0.33V��ѹ  ���0.1V
	TIM1->CCR2 = 0;  //PA9 �����������0.66V��ѹ	���0.1V
	TIM1->CCR3 = 0;  //PA10�����������0.99V��ѹ	���0.1V
	TIM1->CCR4 = 0;  //PA11�����������1.32V��ѹ	���0.1V

	TIM_Cmd(TIM1, ENABLE);
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
	
}
////////////////////////////

void TIM8_Configuration(void)//TIM8��ͨ���ֱ����PWM1/PWM2/PWM3/PWM4,��Ӧ����ΪPC6/PC7/PC8/PC9
{
	GPIO_InitTypeDef GPIO_InitStructure; 
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;    
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;       
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;       
    GPIO_Init(GPIOC, &GPIO_InitStructure); 
	   
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = PWMPeriod;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;

	TIM_OC1Init(TIM8, &TIM_OCInitStructure);
	TIM_OC2Init(TIM8, &TIM_OCInitStructure);
	TIM_OC3Init(TIM8, &TIM_OCInitStructure);
	TIM_OC4Init(TIM8, &TIM_OCInitStructure);
	
	TIM8->CCR1 = 0; //PC6�����������1.65V��ѹ  ���0.1V
	TIM8->CCR2 = 0; //PC7�����������1.98V��ѹ  ���0.1V
	TIM8->CCR3 = 0; //PC8�����������2.31V��ѹ  ���0.1V
	TIM8->CCR4 = 0; //PC9�����������2.64V��ѹ  ���0.1V

	TIM_Cmd(TIM8, ENABLE);
	TIM_CtrlPWMOutputs(TIM8, ENABLE);	

}

/////////////////////////////

void TIM2_Configuration(void)//�������ӿ����ã�TIM2��/PA15-A��  PB3-B��
{
    GPIO_InitTypeDef GPIO_InitStructure; 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM_ICInitStructure;

	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);  //�ر�JTAG�ӿ�
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //�ر�JTAG�ӿ� ����SWD

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

	GPIO_PinRemapConfig(GPIO_FullRemap_TIM2,ENABLE);       //TIM2�����ض��� 
	                                                      				
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;			   //PA15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;          
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	   
	GPIO_Init(GPIOA, &GPIO_InitStructure);				  
	GPIO_WriteBit(GPIOA, GPIO_Pin_15,Bit_SET);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;			   //PB3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;          
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	   
	GPIO_Init(GPIOB, &GPIO_InitStructure);				   
	GPIO_WriteBit(GPIOB, GPIO_Pin_3,Bit_SET);
	
   	TIM_TimeBaseStructure.TIM_Period = PWMPeriod; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = 0; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 
	
	//���ö�ʱ��2Ϊ������ģʽ  IT1 IT2Ϊ�����ؼ���
	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12,TIM_ICPolarity_BothEdge,TIM_ICPolarity_BothEdge);
	TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 6;  //�����˲���
    TIM_ICInit(TIM2, &TIM_ICInitStructure);
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);  //������б�־λ
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); //�����жϸ���
    TIM2->CNT = 0;
	TIM_Cmd(TIM2, ENABLE);
}


void TIM3_Configuration(void)//�������ӿ����ã�TIM3��/PA6-A��  PA7-B��
{
    GPIO_InitTypeDef GPIO_InitStructure; 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM_ICInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  //ʹ��GPIOA����ʱ��
	                                                       				
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;          //����Ϊ��������ģʽ 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	   //IO�ڵ�����Ϊ50M 
	GPIO_Init(GPIOA, &GPIO_InitStructure);				   //IO�����ú���
	GPIO_WriteBit(GPIOA, GPIO_Pin_6,Bit_SET);
	GPIO_WriteBit(GPIOA, GPIO_Pin_7,Bit_SET); 

   	TIM_TimeBaseStructure.TIM_Period = PWMPeriod; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = 0; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;     //����ʱ�ӷָ�
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 
	
	//���ö�ʱ��3Ϊ������ģʽ  IT1 IT2Ϊ�����ؼ���
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12,TIM_ICPolarity_BothEdge,TIM_ICPolarity_BothEdge);
	TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 6;      //�����˲���
    TIM_ICInit(TIM3, &TIM_ICInitStructure);
    TIM_ClearFlag(TIM3, TIM_FLAG_Update);      //������б�־λ
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); //�����жϸ���
    TIM3->CNT = 0;
	TIM_Cmd(TIM3, ENABLE);
}

void TIM4_Configuration(void)//�������ӿ����ã�TIM4��/PB6-A��  PB7-B��
{
    GPIO_InitTypeDef GPIO_InitStructure; 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM_ICInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);  //ʹ��GPIOB����ʱ��
	                                                       				
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;          //����Ϊ��������ģʽ 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	   //IO�ڵ�����Ϊ50M 
	GPIO_Init(GPIOB, &GPIO_InitStructure);				   //IO�����ú���
	GPIO_WriteBit(GPIOB, GPIO_Pin_6,Bit_SET);
	GPIO_WriteBit(GPIOB, GPIO_Pin_7,Bit_SET); 

   	TIM_TimeBaseStructure.TIM_Period = PWMPeriod; 
	TIM_TimeBaseStructure.TIM_Prescaler = 0; 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 
	
	//���ö�ʱ��3Ϊ������ģʽ  IT1 IT2Ϊ�����ؼ���
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12,TIM_ICPolarity_BothEdge,TIM_ICPolarity_BothEdge);
	TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 6;      //�����˲���
    TIM_ICInit(TIM4, &TIM_ICInitStructure);
    TIM_ClearFlag(TIM4, TIM_FLAG_Update);      //������б�־λ
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE); //�����жϸ���
    TIM4->CNT = 0;
	TIM_Cmd(TIM4, ENABLE);
}

void TIM5_Configuration(void)//�������ӿ����ã�TIM5��/PA0-A��  PA1-B��
{
    GPIO_InitTypeDef GPIO_InitStructure; 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM_ICInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE); 
	                                                       				
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 
	GPIO_Init(GPIOA, &GPIO_InitStructure);				 
	GPIO_WriteBit(GPIOA, GPIO_Pin_0,Bit_SET);
	GPIO_WriteBit(GPIOA, GPIO_Pin_1,Bit_SET); 

   	TIM_TimeBaseStructure.TIM_Period = PWMPeriod;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); 
	
	//���ö�ʱ��3Ϊ������ģʽ  IT1 IT2Ϊ�����ؼ���
	TIM_EncoderInterfaceConfig(TIM5, TIM_EncoderMode_TI12,TIM_ICPolarity_BothEdge,TIM_ICPolarity_BothEdge);
	TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 6;  
    TIM_ICInit(TIM5, &TIM_ICInitStructure);
    TIM_ClearFlag(TIM5, TIM_FLAG_Update); 
    TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
    TIM5->CNT = 0;
	TIM_Cmd(TIM5, ENABLE);
}


void TIM7_Configuration(void)
{
   TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
   
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);

   TIM_TimeBaseStructure.TIM_Period = 5000-1;
   TIM_TimeBaseStructure.TIM_Prescaler =72-1;
   TIM_TimeBaseStructure.TIM_ClockDivision = 0;       
   TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
   TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
   TIM_TimeBaseInit(TIM7,&TIM_TimeBaseStructure);
   
   TIM_UpdateRequestConfig(TIM7,TIM_UpdateSource_Regular);
   TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE);
   TIM_Cmd(TIM7,ENABLE);

}
///////////////////////////////

void UserTIM_Configuration(void)//TIM��ʼ��
{
    TIM1_Configuration();
	TIM8_Configuration();
	TIM2_Configuration();
	TIM3_Configuration();
	TIM4_Configuration();
	TIM5_Configuration();
	TIM7_Configuration();
	
}
///////////////////////////////////////////
  
void UserMotorSpeedSetOne(s32 control)//���1ת��/ת�����ã�TIM1��
{		
	s32 MotorSpeed,PwmOne_Set,PwmOne_Mode;

	MotorSpeed = control;//��ȡPID������ֵ
											   
	if(MotorSpeed > PWMPeriod)  MotorSpeed =   PWMPeriod-1 ;//���� CCR��ֵ����С�ڻ����ARR��ֵ
	if(MotorSpeed <-PWMPeriod)  MotorSpeed = -(PWMPeriod-1);//���� 

	if(MotorSpeed<0) { PwmOne_Set = -MotorSpeed; PwmOne_Mode = MotorOneBack;}
	else { PwmOne_Set = MotorSpeed; PwmOne_Mode = MotorOneForward;}
	
	if(PwmOne_Mode) {TIM1->CCR1 = MotorSpdZero; TIM1->CCR2 = PwmOne_Set;} //MotorOneForward
	else { TIM1->CCR1 = PwmOne_Set; TIM1->CCR2 = MotorSpdZero;} //MotorOneBack	
}
///////////////////////////////////////////
 
void UserMotorSpeedSetTwo(s32 MotorSpeed)//���2ת��/ת�����ã�TIM1��
{
   s32 PwmTwo_Set,PwmTwo_Mode;

   if(MotorSpeed<0) { PwmTwo_Set = -MotorSpeed; PwmTwo_Mode = MotorTwoBack;}
   else { PwmTwo_Set = MotorSpeed; PwmTwo_Mode = MotorTwoForward;}

   if(PwmTwo_Mode) {TIM1->CCR3 = MotorSpdZero; TIM1->CCR4 = PwmTwo_Set;} //MotorTwoForward
   else { TIM1->CCR3 = PwmTwo_Set; TIM1->CCR4 = MotorSpdZero;}	//MotorTwoBack


}
///////////////////////////////////////////

void UserMotorSpeedSetThr(s32 MotorSpeed)//���3ת��/ת������(TIM8)
{		
	s32 PwmOne_Set,PwmOne_Mode;

	if(MotorSpeed<0) { PwmOne_Set = -MotorSpeed; PwmOne_Mode = MotorOneBack;}
	else { PwmOne_Set = MotorSpeed; PwmOne_Mode = MotorOneForward;}

	if(PwmOne_Mode) {TIM8->CCR1 = MotorSpdZero; TIM8->CCR2 = PwmOne_Set;} //MotorOneForward
	else { TIM8->CCR1 = PwmOne_Set; TIM8->CCR2 = MotorSpdZero;} //MotorOneBack	
}
////////////////////////////////////////////

void UserMotorSpeedSetFou(s32 MotorSpeed)//���4ת��/ת������(TIM8)
{
   s32 PwmTwo_Set,PwmTwo_Mode;

   if(MotorSpeed<0) { PwmTwo_Set = -MotorSpeed; PwmTwo_Mode = MotorTwoBack;}
   else { PwmTwo_Set = MotorSpeed; PwmTwo_Mode = MotorTwoForward;}

   if(PwmTwo_Mode) {TIM8->CCR3 = MotorSpdZero; TIM8->CCR4 = PwmTwo_Set;} //MotorTwoForward
   else { TIM8->CCR3 = PwmTwo_Set; TIM8->CCR4 = MotorSpdZero;}	//MotorTwoBack
}













