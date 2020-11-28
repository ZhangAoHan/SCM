#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "lcd.h"
#include "touch.h"  
#include "w25qxx.h"  
#include "text.h"	 
#include "fdc2214.h"
#include "IIC.h"
#include "display.h"	 
#include "timer.h"
#include "control.h"

u8 flag=0;                               //定义界面标志位     flag=0  猜拳界面  flag=1 识数界面   默认猜拳界面
u8 cle;                                  //定义切换页面清屏标志量   为了解决切换界面的BUG
u8 mode_selsct=0;                        //通道选择
u8 mode;                                 //数字选择
u8 fj,fj_mode,fj_resut,fj_resut1,fj_resut2;                                   //附加功能开启标志位

            /*2214需要的变量 */
uint32_t date2;
uint32_t fre2;
uint32_t fre2_init_min,fre2_init_max;    //检测10000个数 找到最大值和最小值
uint32_t ch2_middle,ch2_wave;            //中值和波动区间
uint32_t by2,bb2,sy2,sb2,jy2,jb2;        //使系统具有存储功能
uint32_t y1,b1,y2,b2,y3,b3,y4,b4,y5,b5;  //使系统具有存储功能
uint32_t result2;                        //算术平均滤波
uint32_t fre2_last;                      //一阶滤波

void fj_control(void);

int main(void)
{				 
	Stm32_Clock_Init(9);		//系统时钟设置
	delay_init(72);	  			//延时初始化
	uart_init(72,115200); 		//串口初始化为115200
/*   TFT显示初始化函数         */
	LCD_Init();
	W25QXX_Init();				//初始化W25Q128 和SPI2
	tp_dev.init();			    //触摸屏初始化 
	while(font_init()) 			//检查字库
	{;}  
		
/*  FDC2214初始化函数   */
	IIC_Init1();
	FDC2214_Init();  			//检测2214
	//给fre2_last赋初值
	FDC2214_GetChannelData(FDC2214_Channel_2, &date2);
	fre2_last = FDC2214_CalculateFrequency(FDC2214_Channel_2, date2);    

/*定时器初始化  每隔100ms检测一次是否有按键按下*/
	TIM3_Int_Init(999,7199);//10Khz的计数频率，计数1K次为100ms  
	fj=0;
	fj_mode=0;
	LCD_Clear(WHITE);
		while(1)
	{
		if(flag==0)  //猜拳识别
			{
				if(cle==1)
					{
						if(bb2!=0&&by2!=0&&sy2!=0&&sb2!=0&&jy2!=0&&jb2!=0)  //通道2学习完成  
							{
								Show_Str(1,1,96,24,"学习完成",24,0);
								C_Feedback();
								cq_scan(0);   //都训练完成后  才显示附加功能   附加功能初始化
								fj_control();
							}
						else
							{
								Show_Str(1,1,96,24,"请先学习",24,0);
							}
						FDC2214read();
						C_control();	
					}
				else
					{
						LCD_Clear(WHITE);
						C_display_init();
						cle=1;
					}
			}
			
			
			
		else   //数字识别
		{
			if(cle==1)
				{
					if(y1!=0&&b1!=0&&y2!=0&&b2!=0&&y3!=0&&b3!=0&&y4!=0&&b4!=0&&y5!=0&&b5!=0)  //通道2学习完成  
						{
							Show_Str(11,1,96,24,"学习完成",24,0);
							S_Feedback();
						}
					else
						{
							Show_Str(11,1,96,24,"请先学习",24,0);
						}
					FDC2214read();
					S_control();
				}
			else
				{
					LCD_Clear(WHITE);
					S_display_init();
					cle=1;
				}
			}
	}	
	
} 

void fj_control(void)
{
	u8 i;
	u8 k1=0,k2=0;
	u8 p=1;
	while(fj)
	{	
		cq_scan(1);   //显示由猜拳开启变为猜拳关闭
		while(p)     //保证一轮检测完成
		{
			if(fj_mode==1)   //检查第一位
			{
				POINT_COLOR=RED;     //开始检查  
				Show_Str(21,276,93,24,"第一位",24,0);
				for(i=0;i<10;i++)   //延时  减小按键手势对波动的影响
				{
					FDC2214read();
					fre2_init_min=fre2_init_max=fre2;   //赋初值
				}
				for(i=0;i<20;i++)
				{
					FDC2214read();
					C_Feedback();      //检测手势
				}
					fj_resut1=fj_resut;
					fj_resut=0;	
					if(fj_resut1==1||fj_resut1==2||fj_resut1==3)   //检测完成
					{
						k1=1;  //表示测试完成
						POINT_COLOR=BLACK;     //开始检查  
						Show_Str(21,276,93,24,"一完成",24,0);
					}
					else
					{
						POINT_COLOR=BLACK;     //开始检查  
						Show_Str(21,276,93,24,"一错误",24,0);
					}
				fj_mode=0;						
				}
			if(fj_mode==2)
			{
				POINT_COLOR=RED;     //开始检查  
				Show_Str(149,276,72,24,"第二位",24,0);
					for(i=0;i<10;i++)   //延时  减小按键手势对波动的影响
				{
					FDC2214read();
					fre2_init_min=fre2_init_max=fre2;   //赋初值
				}

				for(i=0;i<20;i++)
				{
					FDC2214read();
					C_Feedback();      //检测手势
				}
					fj_resut2=fj_resut;
					fj_resut=0;	
					if(fj_resut2==1||fj_resut2==2||fj_resut2==3)   //检测完成
					{
						k2=1;  //表示测试完成
						POINT_COLOR=BLACK;     //开始检查  
						Show_Str(149,276,72,24,"二完成",24,0);
					}
					else
					{
						POINT_COLOR=BLACK;     //开始检查  
						Show_Str(149,276,72,24,"二错误",24,0);
					}
					fj_mode=0;
			}
			    if(k1!=0&&k2!=0)   //测试完成
				{
					if(fj_resut1==1)
					{
						if(fj_resut2==1) 
						{
						p=0;
						Show_Str(170,30,48,24,"平局",24,0);	
						fj_resut1=fj_resut2=0;
						}
						if(fj_resut2==2) 
						{
						p=0;
						Show_Str(170,30,48,24,"一胜",24,0);	
						fj_resut1=fj_resut2=0;
						}
						if(fj_resut2==3) 
						{
						p=0;
						Show_Str(170,30,48,24,"二胜",24,0);	
						fj_resut1=fj_resut2=0;
						}
					}
					
								if(fj_resut1==2)
					{
						if(fj_resut2==1) 
						{
						p=0;
						Show_Str(170,30,48,24,"二胜",24,0);	
						fj_resut1=fj_resut2=0;
						}
						if(fj_resut2==2) 
						{
						p=0;
						Show_Str(170,30,48,24,"平局",24,0);	
						fj_resut1=fj_resut2=0;
						}
						if(fj_resut2==3) 
						{
						p=0;
						Show_Str(170,30,48,24,"一胜",24,0);	
						fj_resut1=fj_resut2=0;
						}
					}
					
										if(fj_resut1==3)
					{
						if(fj_resut2==1) 
						{
						p=0;
						Show_Str(170,30,48,24,"一胜",24,0);	
						fj_resut1=fj_resut2=0;
						}
						if(fj_resut2==2) 
						{
						p=0;
						Show_Str(170,30,48,24,"二胜",24,0);	
						fj_resut1=fj_resut2=0;
						}
						if(fj_resut2==3) 
						{
						p=0;
						Show_Str(170,30,48,24,"平局",24,0);	
						fj_resut1=fj_resut2=0;
						}
					}
				}
				
				
				
				
			}
		}
	}




