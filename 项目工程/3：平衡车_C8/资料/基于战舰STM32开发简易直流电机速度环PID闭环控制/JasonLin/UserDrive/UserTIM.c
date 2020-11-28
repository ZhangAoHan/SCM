#include"stm32f10x.h"
#include "UserConfiguration.h"

void TIM1_Configuration(void)//TIM1四通道分别输出PWM1/PWM2/PWM3/PWM4,对应引脚为PA8/PA9/PA10/PA11
{
    GPIO_InitTypeDef GPIO_InitStructure; 
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;    
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;       
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   //复用满负载输出为3.3V      
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
	
	TIM1->CCR1 = 0;  //PA8 上理论能输出0.33V电压  误差0.1V
	TIM1->CCR2 = 0;  //PA9 上理论能输出0.66V电压	误差0.1V
	TIM1->CCR3 = 0;  //PA10上理论能输出0.99V电压	误差0.1V
	TIM1->CCR4 = 0;  //PA11上理论能输出1.32V电压	误差0.1V

	TIM_Cmd(TIM1, ENABLE);
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
	
}
////////////////////////////

void TIM8_Configuration(void)//TIM8四通道分别输出PWM1/PWM2/PWM3/PWM4,对应引脚为PC6/PC7/PC8/PC9
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
	
	TIM8->CCR1 = 0; //PC6上理论能输出1.65V电压  误差0.1V
	TIM8->CCR2 = 0; //PC7上理论能输出1.98V电压  误差0.1V
	TIM8->CCR3 = 0; //PC8上理论能输出2.31V电压  误差0.1V
	TIM8->CCR4 = 0; //PC9上理论能输出2.64V电压  误差0.1V

	TIM_Cmd(TIM8, ENABLE);
	TIM_CtrlPWMOutputs(TIM8, ENABLE);	

}

/////////////////////////////

void TIM2_Configuration(void)//编码器接口设置（TIM2）/PA15-A相  PB3-B相
{
    GPIO_InitTypeDef GPIO_InitStructure; 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM_ICInitStructure;

	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);  //关闭JTAG接口
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //关闭JTAG接口 开启SWD

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

	GPIO_PinRemapConfig(GPIO_FullRemap_TIM2,ENABLE);       //TIM2引脚重定向 
	                                                      				
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
	
   	TIM_TimeBaseStructure.TIM_Period = PWMPeriod; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = 0; //设置用来作为TIMx时钟频率除数的预分频值  不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 
	
	//设置定时器2为编码器模式  IT1 IT2为上升沿计数
	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12,TIM_ICPolarity_BothEdge,TIM_ICPolarity_BothEdge);
	TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 6;  //输入滤波器
    TIM_ICInit(TIM2, &TIM_ICInitStructure);
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);  //清除所有标志位
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); //允许中断更新
    TIM2->CNT = 0;
	TIM_Cmd(TIM2, ENABLE);
}


void TIM3_Configuration(void)//编码器接口设置（TIM3）/PA6-A相  PA7-B相
{
    GPIO_InitTypeDef GPIO_InitStructure; 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM_ICInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  //使能GPIOA外设时钟
	                                                       				
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;          //设置为上拉输入模式 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	   //IO口的速率为50M 
	GPIO_Init(GPIOA, &GPIO_InitStructure);				   //IO口配置函数
	GPIO_WriteBit(GPIOA, GPIO_Pin_6,Bit_SET);
	GPIO_WriteBit(GPIOA, GPIO_Pin_7,Bit_SET); 

   	TIM_TimeBaseStructure.TIM_Period = PWMPeriod; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = 0; //设置用来作为TIMx时钟频率除数的预分频值  不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;     //设置时钟分割
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 
	
	//设置定时器3为编码器模式  IT1 IT2为上升沿计数
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12,TIM_ICPolarity_BothEdge,TIM_ICPolarity_BothEdge);
	TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 6;      //输入滤波器
    TIM_ICInit(TIM3, &TIM_ICInitStructure);
    TIM_ClearFlag(TIM3, TIM_FLAG_Update);      //清除所有标志位
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); //允许中断更新
    TIM3->CNT = 0;
	TIM_Cmd(TIM3, ENABLE);
}

void TIM4_Configuration(void)//编码器接口设置（TIM4）/PB6-A相  PB7-B相
{
    GPIO_InitTypeDef GPIO_InitStructure; 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM_ICInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);  //使能GPIOB外设时钟
	                                                       				
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;          //设置为上拉输入模式 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	   //IO口的速率为50M 
	GPIO_Init(GPIOB, &GPIO_InitStructure);				   //IO口配置函数
	GPIO_WriteBit(GPIOB, GPIO_Pin_6,Bit_SET);
	GPIO_WriteBit(GPIOB, GPIO_Pin_7,Bit_SET); 

   	TIM_TimeBaseStructure.TIM_Period = PWMPeriod; 
	TIM_TimeBaseStructure.TIM_Prescaler = 0; 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 
	
	//设置定时器3为编码器模式  IT1 IT2为上升沿计数
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12,TIM_ICPolarity_BothEdge,TIM_ICPolarity_BothEdge);
	TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 6;      //输入滤波器
    TIM_ICInit(TIM4, &TIM_ICInitStructure);
    TIM_ClearFlag(TIM4, TIM_FLAG_Update);      //清除所有标志位
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE); //允许中断更新
    TIM4->CNT = 0;
	TIM_Cmd(TIM4, ENABLE);
}

void TIM5_Configuration(void)//编码器接口设置（TIM5）/PA0-A相  PA1-B相
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
	
	//设置定时器3为编码器模式  IT1 IT2为上升沿计数
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

void UserTIM_Configuration(void)//TIM初始化
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
  
void UserMotorSpeedSetOne(s32 control)//电机1转速/转向设置（TIM1）
{		
	s32 MotorSpeed,PwmOne_Set,PwmOne_Mode;

	MotorSpeed = control;//读取PID的输入值
											   
	if(MotorSpeed > PWMPeriod)  MotorSpeed =   PWMPeriod-1 ;//上限 CCR的值必须小于或等于ARR的值
	if(MotorSpeed <-PWMPeriod)  MotorSpeed = -(PWMPeriod-1);//下限 

	if(MotorSpeed<0) { PwmOne_Set = -MotorSpeed; PwmOne_Mode = MotorOneBack;}
	else { PwmOne_Set = MotorSpeed; PwmOne_Mode = MotorOneForward;}
	
	if(PwmOne_Mode) {TIM1->CCR1 = MotorSpdZero; TIM1->CCR2 = PwmOne_Set;} //MotorOneForward
	else { TIM1->CCR1 = PwmOne_Set; TIM1->CCR2 = MotorSpdZero;} //MotorOneBack	
}
///////////////////////////////////////////
 
void UserMotorSpeedSetTwo(s32 MotorSpeed)//电机2转速/转向设置（TIM1）
{
   s32 PwmTwo_Set,PwmTwo_Mode;

   if(MotorSpeed<0) { PwmTwo_Set = -MotorSpeed; PwmTwo_Mode = MotorTwoBack;}
   else { PwmTwo_Set = MotorSpeed; PwmTwo_Mode = MotorTwoForward;}

   if(PwmTwo_Mode) {TIM1->CCR3 = MotorSpdZero; TIM1->CCR4 = PwmTwo_Set;} //MotorTwoForward
   else { TIM1->CCR3 = PwmTwo_Set; TIM1->CCR4 = MotorSpdZero;}	//MotorTwoBack


}
///////////////////////////////////////////

void UserMotorSpeedSetThr(s32 MotorSpeed)//电机3转速/转向设置(TIM8)
{		
	s32 PwmOne_Set,PwmOne_Mode;

	if(MotorSpeed<0) { PwmOne_Set = -MotorSpeed; PwmOne_Mode = MotorOneBack;}
	else { PwmOne_Set = MotorSpeed; PwmOne_Mode = MotorOneForward;}

	if(PwmOne_Mode) {TIM8->CCR1 = MotorSpdZero; TIM8->CCR2 = PwmOne_Set;} //MotorOneForward
	else { TIM8->CCR1 = PwmOne_Set; TIM8->CCR2 = MotorSpdZero;} //MotorOneBack	
}
////////////////////////////////////////////

void UserMotorSpeedSetFou(s32 MotorSpeed)//电机4转速/转向设置(TIM8)
{
   s32 PwmTwo_Set,PwmTwo_Mode;

   if(MotorSpeed<0) { PwmTwo_Set = -MotorSpeed; PwmTwo_Mode = MotorTwoBack;}
   else { PwmTwo_Set = MotorSpeed; PwmTwo_Mode = MotorTwoForward;}

   if(PwmTwo_Mode) {TIM8->CCR3 = MotorSpdZero; TIM8->CCR4 = PwmTwo_Set;} //MotorTwoForward
   else { TIM8->CCR3 = PwmTwo_Set; TIM8->CCR4 = MotorSpdZero;}	//MotorTwoBack
}













