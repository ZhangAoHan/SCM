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
            /*2214需要的变量 */
uint32_t date2;
uint32_t fre2;
uint32_t fre2_init_min,fre2_init_max;    //检测10000个数 找到最大值和最小值
uint32_t ch2_middle,ch2_wave;            //中值和波动区间
uint32_t by2,bb2,sy2,sb2,jy2,jb2;        //使系统具有存储功能
uint32_t y1,b1,y2,b2,y3,b3,y4,b4,y5,b5;  //使系统具有存储功能
uint32_t result2;                        //算术平均滤波
uint32_t fre2_last;                      //一阶滤波

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
	
	LCD_Clear(WHITE);
		while(1)
	{
		if(flag==0)  //猜拳识别
			{
				if(cle==1)
					{
						if(bb2!=0&&by2!=0&&sy2!=0&&sb2!=0&&jy2!=0&&jb2!=0)  //通道2学习完成  
							{
								Show_Str(11,1,96,24,"学习完成",24,0);
								C_Feedback();
							}
						else
							{
								Show_Str(11,1,96,24,"请先学习",24,0);
							}
						FDC2214read();
						C_control();	
					}
				else
					{
						LCD_Clear(WHITE);
						POINT_COLOR=BLUE;
						LCD_DrawRectangle(10,60 ,230 ,310);   //画矩形
						Show_Str(11,61,192,24,"进入数字识别界面",24,0);
						POINT_COLOR=RED;   
						Show_Str(11,90,84,24,"通道2：",24,0);
						POINT_COLOR=BLUE;	
						Show_Str(60,150,48,24,"阈值",24,0);
						Show_Str(120,150,96,24,"波动范围",24,0);	
						Show_Str(11,180,48,24,"石头",24,0);
						POINT_COLOR=BLUE;
						Show_Str(11,210,48,24,"剪刀",24,0);
						Show_Str(11,240,48,24,"布",24,0);
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
					cle=1;
				}
			}
	}	
	
} 




