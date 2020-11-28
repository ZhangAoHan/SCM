#include"stm32f10x.h"


void UserNVIC_Configuration(void)
{
   NVIC_InitTypeDef NVIC_InitStructure; 

   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		   //中断分组2 两位抢占（0-3）  两位响应（0-3）

   NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; 		  
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
   NVIC_Init(&NVIC_InitStructure);

   //*****************************************************

   NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; 		 
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);

   //******************************************************
 
   NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn; 		 
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
   NVIC_Init(&NVIC_InitStructure);

   //*******************************************************
 
   NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn; 		 
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; 
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);

   //*******************************************************

   NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn; 	
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; 
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);

 
 /*优先级分组：优先级分组是为了给抢占式优先级和响应优先级在中断优先级寄存器的高四位分配各自所占的位数
               在同一个程序中优先级分组只能设定一次 */

 /*抢占优先级: 当一个中断正在执行而另一个具有更高抢占优先级的中断到来时，抢占优先级高的就会抢占CPU处理权
 			   此时两个中断就属于嵌套中断关系，具有相同抢占优先级的中断没有嵌套关系*/

 /*响应优先级：即副优先级，当两个抢占优先级相同的中断同时到来，具有响应优先级高的中断优先获得CPU的处理权
               如果中断不是同时到来，则后来的要等待正在执行的中断处理完才能获得响应*/

}

