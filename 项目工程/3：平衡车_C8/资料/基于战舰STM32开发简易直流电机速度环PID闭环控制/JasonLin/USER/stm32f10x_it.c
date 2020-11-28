
#include "stm32f10x_it.h" 



/*****************************STM32F10x Peripherals Interrupt Handlers**********************************/



#include "UserFunction.h"
#include "led.h"

s32 rcnt2,rcnt3,rcnt4,rcnt5;

/////////////////////////////////////////////TIM Interruption//////////////////////////////////////////


//********************************************TIM75Ms��ʱ5ms�ж�
void TIM7_IRQHandler(void)
{
  get_encoder_ONE();
  get_encoder_TWO();
  get_encoder_THR();
  get_encoder_FOU();

  User_PidSpeedControl(500);//PID�ٶȻ����ƣ�����ÿ���ڣ�

  LED0=!LED0; //LED0��ʾ�����ж�

  TIM_ClearITPendingBit(TIM7,TIM_FLAG_Update);

}


//********************************************TIM2�������ӿڼ����ж�
void TIM2_IRQHandler(void)
{
  if (TIM2 -> CR1 & 0X0010)		  //С��ע��
   {
    rcnt2 -= 1;
   }
   else rcnt2 += 1;

   TIM_ClearITPendingBit(TIM2, TIM_IT_Update); 
}

//********************************************TIM3�������ӿڼ����ж�
void TIM3_IRQHandler(void)
{
  if (TIM3 -> CR1 & 0X0010)		  //С��ע��
   {
    rcnt3 -= 1;
   }
   else rcnt3 += 1;

   TIM_ClearITPendingBit(TIM3, TIM_IT_Update); 
}


//********************************************TIM4�������ӿڼ����ж�
void TIM4_IRQHandler(void)
{
  if (TIM4 -> CR1 & 0X0010)		  //С��ע��
   {
    rcnt4 -= 1;
   }
   else rcnt4 += 1;
   TIM_ClearITPendingBit(TIM4, TIM_IT_Update); 
}


//********************************************TIM5�������ӿڼ����ж�
void TIM5_IRQHandler(void)
{
  if (TIM5 -> CR1 & 0X0010)		  //С��ע��
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

///////////////////////////////����1�ж�  ���ռĴ������ж�

void USART1_IRQHandler(void)
{

 	if(USART1->SR&(1<<5))//���յ�����
	{	 
		Usart1_ReceiveData[U1_num]=USART1->DR; 
	    U1_num++;
	}  		
}

/////////////////////////////����2�ж�  ���ռĴ������ж�

void USART2_IRQHandler(void)
{


 	if(USART2->SR&(1<<5))//���յ�����
	{	 
		Usart2_ReceiveData[U2_num]=USART2->DR; 
	    U2_num++;
	}  		
}

/////////////////////////////����3�ж�  ���ռĴ������ж�

void USART3_IRQHandler(void)
{


 	if(USART3->SR&(1<<5))//���յ�����
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























