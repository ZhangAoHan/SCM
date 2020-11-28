
#include "stm32f10x_it.h" 



/*****************************STM32F10x Peripherals Interrupt Handlers**********************************/



#include "UserFunction.h"
#include "led.h"

s32 rcnt2,rcnt3,rcnt4,rcnt5;

/////////////////////////////////////////////TIM Interruption//////////////////////////////////////////


//********************************************TIM75Ms定时5ms中断
void TIM7_IRQHandler(void)
{
  get_encoder_ONE();
  get_encoder_TWO();
  get_encoder_THR();
  get_encoder_FOU();

  User_PidSpeedControl(500);//PID速度环控制（脉冲每周期）

  LED0=!LED0; //LED0提示进入中断

  TIM_ClearITPendingBit(TIM7,TIM_FLAG_Update);

}


//********************************************TIM2编码器接口计数中断
void TIM2_IRQHandler(void)
{
  if (TIM2 -> CR1 & 0X0010)		  //小心注意
   {
    rcnt2 -= 1;
   }
   else rcnt2 += 1;

   TIM_ClearITPendingBit(TIM2, TIM_IT_Update); 
}

//********************************************TIM3编码器接口计数中断
void TIM3_IRQHandler(void)
{
  if (TIM3 -> CR1 & 0X0010)		  //小心注意
   {
    rcnt3 -= 1;
   }
   else rcnt3 += 1;

   TIM_ClearITPendingBit(TIM3, TIM_IT_Update); 
}


//********************************************TIM4编码器接口计数中断
void TIM4_IRQHandler(void)
{
  if (TIM4 -> CR1 & 0X0010)		  //小心注意
   {
    rcnt4 -= 1;
   }
   else rcnt4 += 1;
   TIM_ClearITPendingBit(TIM4, TIM_IT_Update); 
}


//********************************************TIM5编码器接口计数中断
void TIM5_IRQHandler(void)
{
  if (TIM5 -> CR1 & 0X0010)		  //小心注意
   {
    rcnt5 -= 1;
   }
   else rcnt5 += 1;
   TIM_ClearITPendingBit(TIM5, TIM_IT_Update); 
}







/////////////////////////////////////////Serial_Port Interruption////////////////////////////////////////

 uint8_t Usart1_ReceiveData[64];
 uint8_t U1_num=0;
 uint8_t Usart2_ReceiveData[64];
 uint8_t U2_num=0;
 uint8_t Usart3_ReceiveData[64];
 uint8_t U3_num=0;

///////////////////////////////串口1中断  接收寄存器满中断

void USART1_IRQHandler(void)
{

 	if(USART1->SR&(1<<5))//接收到数据
	{	 
		Usart1_ReceiveData[U1_num]=USART1->DR; 
	    U1_num++;
	}  		
}

/////////////////////////////串口2中断  接收寄存器满中断

void USART2_IRQHandler(void)
{


 	if(USART2->SR&(1<<5))//接收到数据
	{	 
		Usart2_ReceiveData[U2_num]=USART2->DR; 
	    U2_num++;
	}  		
}

/////////////////////////////串口3中断  接收寄存器满中断

void USART3_IRQHandler(void)
{


 	if(USART3->SR&(1<<5))//接收到数据
	{	 
		Usart3_ReceiveData[U3_num]=USART3->DR; 
	    U3_num++;
	}  		
}







///////////////////////////////////////////Other Interruption////////////////////////////////////////////


 
void NMI_Handler(void)
{
}
 
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}
 
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

 
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}
 
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}
 
void SVC_Handler(void)
{
}
 
void DebugMon_Handler(void)
{
}
 
void PendSV_Handler(void)
{
}
 
void SysTick_Handler(void)
{
}























