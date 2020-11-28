#include "stm32f10x.h"
#include "stm32f10x_it.h" 

#define prd    10000
#define Vbreak 8000

u16 cnt2,cnt3,cnt4,cnt5;
s32 CNT2,CNT3,CNT4,CNT5;
s32 V2,V3,V4,V5;

extern s32 rcnt2,rcnt3,rcnt4,rcnt5;

void get_encoder_ONE(void)//*******************计算当前实际速度V
{
  s32 CNT2_temp,CNT2_last;
  
  cnt2 = TIM2 -> CNT;
  CNT2_last = CNT2;
  CNT2_temp = rcnt2 * prd + cnt2;  
  V2 = CNT2_temp - CNT2_last;		
  
  while (V2>Vbreak)				 
  {							      
   rcnt2--;					      
   CNT2_temp = rcnt2 * prd + cnt2;
   V2 = CNT2_temp - CNT2_last;		 
  }							     
  while (V2<-Vbreak)			   
  {							      
   rcnt2++;					      
   CNT2_temp = rcnt2 * prd + cnt2;
   V2 = CNT2_temp - CNT2_last;		 
  }
  CNT2 = CNT2_temp;						 
  
}

void get_encoder_TWO(void)//******************计算当前实际速度V
{
  s32 CNT3_temp,CNT3_last;
 
  cnt3 = TIM3 -> CNT;
  CNT3_last = CNT3;
  CNT3_temp = rcnt3 * prd + cnt3; 
  V3 = CNT3_temp - CNT3_last;		
  
  while (V3>Vbreak)				 
  {							      
   rcnt3--;					      
   CNT3_temp = rcnt3 * prd + cnt3;
   V3 = CNT3_temp - CNT3_last;		 
  }							     
  while (V3<-Vbreak)			   
  {							      
   rcnt3++;					      
   CNT3_temp = rcnt3 * prd + cnt3;
   V3 = CNT3_temp - CNT3_last;		 
  }
  CNT3 = CNT3_temp;						 
  
}


void get_encoder_THR(void)//*********************计算当前实际速度V
{
  s32 CNT4_temp,CNT4_last;
  
  cnt4 = TIM4 -> CNT;
  CNT4_last = CNT4;
  CNT4_temp = rcnt4 * prd + cnt4;  
  V4 = CNT4_temp - CNT4_last;		 
  
  while (V4>Vbreak)				 
  {							      
   rcnt4--;					     
   CNT4_temp = rcnt4 * prd + cnt4;
   V4 = CNT4_temp - CNT4_last;		 
  }							      
  while (V4<-Vbreak)			   
  {							    
   rcnt4++;					      
   CNT4_temp = rcnt4 * prd + cnt4;
   V4 = CNT4_temp - CNT4_last;		  
  }
  CNT4 = CNT4_temp;						
  
}


void get_encoder_FOU(void)//*********************计算当前实际速度V
{
  s32 CNT5_temp,CNT5_last;
  
  cnt5 = TIM5 -> CNT;
  CNT5_last = CNT5;
  CNT5_temp = rcnt5 * prd + cnt5;  
  V5 = CNT5_temp - CNT5_last;		  
  
  while (V5>Vbreak)				  
  {							      
   rcnt5--;					      
   CNT5_temp = rcnt5 * prd + cnt5;
   V5 = CNT5_temp - CNT5_last;		 
  }							      
  while (V5<-Vbreak)			    
  {							     
   rcnt5++;					      
   CNT5_temp = rcnt5 * prd + cnt5;
   V5 = CNT5_temp - CNT5_last;		 
  }
  CNT5 = CNT5_temp;					
  
}







