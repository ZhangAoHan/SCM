#include "timer.h"
#include "touch.h" 
#include "lcd.h"
#include "fdc2214.h"

extern u8 ch_selsct,mode_selsct;
extern u8 flag;
extern u8 cle;
extern u8 fj,fj_mode;
extern uint32_t by2,bb2,sy2,sb2,jy2,jb2;        //使系统具有存储功能
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
				if(tp_dev.x[0]>2&&tp_dev.x[0]<50&&tp_dev.y[0]>160&&tp_dev.y[0]<184)//点击石头
				{
					mode_selsct=1;
				}
				if(tp_dev.x[0]>2&&tp_dev.x[0]<50&&tp_dev.y[0]>190&&tp_dev.y[0]<214)//点击剪刀
				{
					mode_selsct=2;
				}
				if(tp_dev.x[0]>2&&tp_dev.x[0]<50&&tp_dev.y[0]>220&&tp_dev.y[0]<244)//点击布
				{
					mode_selsct=3;
				}
					if(tp_dev.x[0]>2&&tp_dev.x[0]<146&&tp_dev.y[0]>58&&tp_dev.y[0]<82) //进入数字识别界面
				{
						flag=1;   
						cle=0;
				}
					if(tp_dev.x[0]>2&&tp_dev.x[0]<98&&tp_dev.y[0]>247&&tp_dev.y[0]<271)// 开启附加功能
						{
							switch(fj)
							{
								case 0:fj=1;break;
								case 1:fj=0;break;					}
							
						}
					if(fj)   //如果开启附加功能
						{
							if(tp_dev.x[0]>21&&tp_dev.x[0]<93&&tp_dev.y[0]>290&&tp_dev.y[0]<314)
							{
								fj_mode=1;         //开始检查第一位
							}
							if(tp_dev.x[0]>148&&tp_dev.x[0]<220&&tp_dev.y[0]>290&&tp_dev.y[0]<314)
							{
								fj_mode=2;         //开始检查第二位
							}							
						}
				

				}	
						else
						{
				if(tp_dev.x[0]>2&&tp_dev.x[0]<50&&tp_dev.y[0]>162&&tp_dev.y[0]<196)//测试1
				{
					mode_selsct=1;
				}
				if(tp_dev.x[0]>2&&tp_dev.x[0]<50&&tp_dev.y[0]>190&&tp_dev.y[0]<214)//测试2
				{
					mode_selsct=2;
				}
				if(tp_dev.x[0]>2&&tp_dev.x[0]<50&&tp_dev.y[0]>220&&tp_dev.y[0]<245)//测试3
				{
					mode_selsct=3;
				}
			   	if(tp_dev.x[0]>2&&tp_dev.x[0]<50&&tp_dev.y[0]>250&&tp_dev.y[0]<275)//测试4
				{
					mode_selsct=4;
				}
				if(tp_dev.x[0]>2&&tp_dev.x[0]<50&&tp_dev.y[0]>280&&tp_dev.y[0]<305)//测试5
				{
					mode_selsct=5;
				}
				if(tp_dev.x[0]>2&&tp_dev.x[0]<146&&tp_dev.y[0]>58&&tp_dev.y[0]<82)//点击布
				{
						flag=0;   //进入猜拳识别界面
						cle=0;

				}
						}			   
			}
}
		}












