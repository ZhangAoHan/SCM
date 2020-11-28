#include "timer.h"
#include "touch.h" 
#include "lcd.h"
#include "text.h"
#include "fdc2214.h"

extern u8 ch_selsct,mode_selsct;
extern u8 flag;
extern uint32_t date2;
extern uint32_t fre2;
extern uint32_t fre2_last;
extern u8 cle;
//定时器3中断服务程序	 定时检测是否有触摸按下 
void TIM3_IRQHandler(void)
{ 		    		  			    
	if(TIM3->SR&0X0001)//溢出中断
	{
	Rtp_Scan();	    				   				     	    	
	}				   
	TIM3->SR&=~(1<<0);//清除中断标志位 	    
}
//通用定时器3中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<1;	//TIM3时钟使能    
 	TIM3->ARR=arr;  	//设定计数器自动重装值//刚好1ms    
	TIM3->PSC=psc;  	//预分频器7200,得到10Khz的计数时钟		  
	TIM3->DIER|=1<<0;   //允许更新中断	  
	TIM3->CR1|=0x01;    //使能定时器3
  	MY_NVIC_Init(1,3,TIM3_IRQn,2);//抢占1，子优先级3，组2									 
}
void Rtp_Scan(void)   //触摸按键检测函数
{
			tp_dev.scan(0); 		 
		if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
		{	
		 	if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
			{	
				if(flag==0)    //猜拳界面
				{
				if(tp_dev.x[0]>11&&tp_dev.x[0]<60&&tp_dev.y[0]>180&&tp_dev.y[0]<205)//点击石头
				{
					mode_selsct=1;
				}
				if(tp_dev.x[0]>11&&tp_dev.x[0]<60&&tp_dev.y[0]>210&&tp_dev.y[0]<235)//点击剪刀
				{
					mode_selsct=2;
				}
				if(tp_dev.x[0]>11&&tp_dev.x[0]<60&&tp_dev.y[0]>240&&tp_dev.y[0]<265)//点击布
				{
					mode_selsct=3;
				}
					if(tp_dev.x[0]>11&&tp_dev.x[0]<203&&tp_dev.y[0]>61&&tp_dev.y[0]<85)//点击布
				{
						flag=1;   //进入数字识别界面
						cle=0;
						LCD_Clear(WHITE);
						POINT_COLOR=BLUE;
						LCD_DrawRectangle(10,60 ,230 ,310);   //画矩形
						Show_Str(11,61,192,24,"进入猜拳识别界面",24,0);
						POINT_COLOR=RED;   
						Show_Str(11,90,84,24,"通道2：",24,0);
							POINT_COLOR=BLUE;	
						Show_Str(60,120,48,24,"阈值",24,0);
						Show_Str(120,120,96,24,"波动范围",24,0);	
						Show_Str(11,150,48,24,"测1",24,0);
						Show_Str(11,180,48,24,"测2",24,0);
						Show_Str(11,210,48,24,"测3",24,0);
						Show_Str(11,240,48,24,"测4",24,0);
						Show_Str(11,270,48,24,"测5",24,0);
				}
				}	
						else
						{
				if(tp_dev.x[0]>11&&tp_dev.x[0]<75&&tp_dev.y[0]>150&&tp_dev.y[0]<175)//测试1
				{
					mode_selsct=1;
				}
				if(tp_dev.x[0]>11&&tp_dev.x[0]<75&&tp_dev.y[0]>180&&tp_dev.y[0]<205)//测试2
				{
					mode_selsct=2;
				}
				if(tp_dev.x[0]>11&&tp_dev.x[0]<75&&tp_dev.y[0]>210&&tp_dev.y[0]<235)//测试3
				{
					mode_selsct=3;
				}
			   	if(tp_dev.x[0]>11&&tp_dev.x[0]<75&&tp_dev.y[0]>240&&tp_dev.y[0]<265)//测试4
				{
					mode_selsct=4;
				}
				if(tp_dev.x[0]>11&&tp_dev.x[0]<75&&tp_dev.y[0]>270&&tp_dev.y[0]<295)//测试5
				{
					mode_selsct=5;
				}
				if(tp_dev.x[0]>11&&tp_dev.x[0]<203&&tp_dev.y[0]>61&&tp_dev.y[0]<85)//点击布
				{
						flag=0;   //进入猜拳识别界面
						cle=0;
//				FDC2214_GetChannelData(FDC2214_Channel_2, &date2);
//				fre2 = FDC2214_CalculateFrequency(FDC2214_Channel_2, date2);    
//				fre2_last=fre2;	
				LCD_Clear(WHITE);

				}
						}	

			   
			}
}
		}












