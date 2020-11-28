#include "timer.h"
#include "sys.h"


//定时器3给电机输出2路PWM
void Timer_init(u16 arr,u16 psc)
{
	RCC->APB1ENR |=1<<1;       //使能定时器3
	TIM3->CR1 |=1<<0;          //使能计数器、定时器初始时钟为72M、计数器向上计数
	TIM3->CR1 |=0X0080;
  	TIM3->PSC =psc;  
	TIM3->ARR =arr; 
	
	TIM3->CCMR1 |=7<<4;        //通道1配置
	TIM3->CCMR1 |=1<<3;
	TIM3->CCER  |=1<<0;        //通道1有效电平极性配置（TIM3->CCER=1：pwm为低电平有效，=3：pwm为高电平有效）
	
	TIM3->CCMR1 |=7<<12;       //通道2配置
	TIM3->CCMR1 |=1<<11;
	TIM3->CCER  |=1<<4;
}

void MOTO_PWM_init(void)
{
	
	RCC->APB2ENR|=1<<2;        //使能GPIOA
	GPIOA->CRL&=0X00FFFFFF;    //通道1 GPIOA6,复用推挽输出、输出速度50M
	GPIOA->CRL|=0XBB000000;    //通道2 GPIOA7,复用推挽输出、输出速度50M
	GPIOA->ODR|=1<<6;          //设置GPIOA6为输出模式
	GPIOA->ODR|=1<<7;          //设置GPIOA7为输出模式
}

//定时器2 计算2个电机的速度
void TIM2_init(u16 arr)
{
	RCC->APB1ENR|=1<<0;     //TIM2时钟使能
	RCC->APB2ENR|=1<<2;    //使能PORTA时钟
	GPIOA->CRL&=0XFFFFFF00;//PA0 PA1
	GPIOA->CRL|=0X00000044;//浮空输入
	TIM2->DIER|=1<<0;   //允许更新中断				
	TIM2->DIER|=1<<6;   //允许触发中断
	MY_NVIC_Init(1,3,TIM2_IRQn,1);  //65536（arr）/72M=910us  溢出频率
	TIM2->PSC = 0x0;//预分频器
	TIM2->ARR = arr;//设定计数器自动重装值 
	TIM2->CR1 &=~(3<<8);// 选择时钟分频：不分频
	TIM2->CR1 &=~(3<<5);// 选择计数模式:边沿对齐模式
		
	TIM2->CCMR1 |= 1<<0; //CC1S='01' IC1FP1映射到TI1
	TIM2->CCMR1 |= 1<<8; //CC2S='01' IC2FP2映射到TI2
	TIM2->CCER &= ~(1<<1);	 //CC1P='0'	 IC1FP1不反相，IC1FP1=TI1
	TIM2->CCER &= ~(1<<5);	 //CC2P='0'	 IC2FP2不反相，IC2FP2=TI2
	TIM2->CCMR1 |= 3<<4; //	IC1F='1000' 输入捕获1滤波器
	TIM2->SMCR |= 3<<0;	 //SMS='011' 所有的输入均在上升沿和下降沿有效
	TIM2->CR1 |= 0x01;    //CEN=1，使能定时器
}

void TIM4_init(u16 arr)
{
	RCC->APB1ENR|=1<<2;     //TIM4时钟使能
	RCC->APB2ENR|=1<<3;     //使能PORTB时钟
	GPIOB->CRL&=0X00FFFFFF; //PB6 PB7
	GPIOB->CRL|=0X44000000; //浮空输入
	TIM4->DIER|=1<<0;   //允许更新中断				
	TIM4->DIER|=1<<6;   //允许触发中断
	MY_NVIC_Init(1,3,TIM4_IRQn,1);
	TIM4->PSC = 0x0;//预分频器
	TIM4->ARR = arr;//设定计数器自动重装值 
	TIM4->CR1 &=~(3<<8);// 选择时钟分频：不分频
	TIM4->CR1 &=~(3<<5);// 选择计数模式:边沿对齐模式
		
	TIM4->CCMR1 |= 1<<0; //CC1S='01' IC1FP1映射到TI1
	TIM4->CCMR1 |= 1<<8; //CC2S='01' IC2FP2映射到TI2
	TIM4->CCER &= ~(1<<1);	 //CC1P='0'	 IC1FP1不反相，IC1FP1=TI1
	TIM4->CCER &= ~(1<<5);	 //CC2P='0'	 IC2FP2不反相，IC2FP2=TI2
	TIM4->CCMR1 |= 3<<4; //	IC1F='1000' 输入捕获1滤波器
	TIM4->SMCR |= 3<<0;	 //SMS='011' 所有的输入均在上升沿和下降沿有效
	TIM4->CR1 |= 0x01;    //CEN=1，使能定时器
}
void TIM2_IRQHandler(void)
{ 		    		  			    
	if(TIM2->SR&0X0001)//溢出中断
	{    				   				     	    	
	}				   
	TIM2->SR&=~(1<<0);//清除中断标志位 	    
}
void TIM4_IRQHandler(void)
{ 		    		  			    
	if(TIM4->SR&0X0001)//溢出中断
	{    				   				     	    	
	}				   
	TIM4->SR&=~(1<<0);//清除中断标志位 	    
}
int Read_val(u8 TIMX)     //读取编码器返回的速度值
{
    int Encoder_TIM;    
   switch(TIMX)
	 {
	   case 2:  Encoder_TIM= (short)TIM2 -> CNT;  TIM2 -> CNT=0;break;	
	   case 4:  Encoder_TIM= (short)TIM4 -> CNT;  TIM4 -> CNT=0;break;	
		 default:  Encoder_TIM=0;
	 }
		return Encoder_TIM;
}




