#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "lcd.h"
#include "touch.h"  
#include "w25qxx.h"  
#include "text.h"	
#include "timer.h"	
#include "exit.h"   
#include "sccb.h" 
#include "ov7670.h" 
#include "math.h" 

#define  OV7670 2
const u8*LMODE_TBL[6]={"Auto","Sunny","Cloudy","Office","Home","Night"};//6种光照模式	    
const u8*EFFECTS_TBL[7]={"Normal","Negative","B&W","Redish","Greenish","Bluish","Antique"};	//7种特效 
extern u8 ov_sta;	//在exit.c里 面定义
extern u8 ov_frame;	//在timer.c里面定义
//u16 Black_dot;
u16 black_left,black_right,black_down,black_under;   //记录边界黑点的坐标值
u16 black_x,black_y;   //记录当前黑点的坐标值
u16 dot_all;   //边界总像素个数
u16 dot_duty;  //边界值内的黑点个数
u16 black_left_x,black_left_y,black_right_x,black_right_y,black_down_x,black_down_y,black_under_x,black_under_y;
/*
   本函数需要：
1：将图像二值化
2：返回图像边界坐标值（black_left,black_right,black_down,black_under）
3：将图像校准

*/
//更新LCD显示(OV7670)
void OV7670_camera_refresh(void)
{
	u32 j;
 	u16 color;
	u8 r,g,b;
    u16 w_x,w_y;
	u16 r_min,r_max,g_min,g_max,b_min,b_max;
	u16 r_min_last,r_max_last,g_min_last,g_max_last,b_min_last,b_max_last;
	u8 du;
	if(ov_sta)//有帧中断更新
	{
		LCD_Scan_Dir(U2D_L2R);		//从上到下,从左到右  
		if(lcddev.id==0X1963)LCD_Set_Window((lcddev.width-240)/2,(lcddev.height-320)/2,240,320);//将显示区域设置到屏幕中央
		LCD_WriteRAM_Prepare();     //开始写入GRAM	
		OV7670_RRST=0;				//开始复位读指针 
		OV7670_RCK_L;
		OV7670_RCK_H;
		OV7670_RCK_L;
		OV7670_RRST=1;				//复位读指针结束 
		OV7670_RCK_H;
		for(du=0;du<10;du++)
		{
				for(j=0;j<76800;j++)
		{
			OV7670_RCK_L;
			color=GPIOC->IDR&0XFF;	//读数据
			OV7670_RCK_H; 
			color<<=8;  
			OV7670_RCK_L;
			color|=GPIOC->IDR&0XFF;	//读数据
			OV7670_RCK_H; 
			w_x=j/320;
			w_y=j%320;
			r=(color&0xf800)>>8;
			g=(color&0x07e0)>>3;
			b=(color&0x001f)<<3;
			//将图像二值化
//			if(r<55&&g<55&&b<55) 
//			{
//			color=0x0000;
//				r=0x00;
//				g=0x00;
//				b=0x00;
//			}
//			else
//			{
//				color=0xffff;
//				r=0xff;
//				g=0xff;
//				b=0xff;
//			}	
       //根据图像形状画框（可斜）
      		if(w_x>21&&w_x<219&&w_y>21&&w_y<299)    //发现黑点
			{
//				if(w_x>=black_right_x) 
//				{
//					black_right_x=w_x;
//					black_right_y=w_y;     //记录x最大值时的点
//					if(black_left_x==0)
//					{
//						black_left_x=w_x;
//						black_left_y=w_y; 
//					}
//				}
//				if(w_x<black_left_x) black_left_x=w_x,black_left_y=w_y;     //记录x最小值时的点
//				if(w_y>=black_down_y) 
//				{
//					black_down_y=w_y;
//					black_down_x=w_x;    //记录y最大值的点
//					if(black_under_y==0)
//					{
//						black_under_y=w_y;
//						black_under_x=w_x; 
//					}
//				}
//				if(w_y<black_under_y) black_under_y=w_y,black_under_x=w_x;  //记录y最小值的点
//				
//				if(w_x<=black_right_x&&w_x>black_left_x&&w_y<=black_down_y&&w_y>black_under_y) dot_duty++;
				if(r_min==0&&r_max==0) r_max=r_min=r;
				if(g_min==0&&g_max==0) g_max=g_min=g;
				if(b_min==0&&b_max==0) b_max=b_min=b;
				
				if(r>r_max) r_max=r;
				if(r<r_min) r_min=r;
				
				if(g>g_max) g_max=g;
				if(g<g_min) g_min=g;
				
				if(b>b_max) b_max=b;
				if(b<b_min) b_min=b;
			}				

			
			
					

			
		}
		 		
		r_max_last=r_max+r_max_last;
		r_min_last=r_min_last+r_min;
		g_max_last=g_max_last+g_max;
		g_min_last=g_min_last+g_min;
		b_min_last=b_min_last+b_min;
		b_max_last=b_max_last+b_max;
			}
		LCD->LCD_RAM=color;
 		ov_sta=0;					//清零帧中断标记
		ov_frame++; 

		LCD_Scan_Dir(DFT_SCAN_DIR);	//恢复默认扫描方向 		
		POINT_COLOR=BLACK;
		LCD_DrawRectangle(20,20,220,300);
		POINT_COLOR=YELLOW;
//		LCD_DrawLine(black_left_x,black_left_y,black_under_x,black_under_y);   //左上线
//		LCD_DrawLine(black_left_x,black_left_y,black_down_x,black_down_y);   //左下线
//		LCD_DrawLine(black_right_x,black_right_y,black_under_x,black_under_y);   //右上线
//		LCD_DrawLine(black_right_x,black_right_y,black_down_x,black_down_y);   //右下线
//		LCD_DrawLine(black_left_x,black_left_y,black_right_x,black_right_y);   //十字线(对角线)
//		LCD_DrawLine(black_under_x,black_under_y,black_down_x,black_down_y);   //十字线	
			//计算总像素个数
		dot_all=sqrt(abs((black_down_x-black_left_x)*(black_down_x-black_left_x))+abs((black_down_y-black_left_y)*(black_down_y-black_left_y)))*sqrt(abs((black_under_x-black_left_x)*(black_under_x-black_left_x))+abs((black_under_y-black_left_y)*(black_under_y-black_left_y)));
		POINT_COLOR=BLACK;
//		Show_Str(25,40,72,24,"总面积",24,0);	
			r_max_last=r_max_last/10;
			r_min_last=r_min_last/10;
			g_max_last=g_max_last/10;
			g_min_last=g_min_last/10;
			b_min_last=b_min_last/10;
			b_max_last=b_max_last/10;
		LCD_ShowNum(100,40,r_max,3,16);
		
		LCD_ShowNum(140,40,r_min,3,16);
		
		LCD_ShowNum(100,60,g_max,3,16);
		
		LCD_ShowNum(140,60,g_min,3,16);
		
		LCD_ShowNum(100,80,b_max,3,16);
		
		LCD_ShowNum(140,80,b_min,3,16);
//		Show_Str(25,70,72,24,"占空比",24,0);	
//		LCD_ShowNum(100,70,dot_duty,8,16);
		black_left_x=black_right_x=black_down_x=black_under_x=0,black_left_y=black_right_y=black_down_y=black_under_y=dot_duty=dot_all=0;
		r_min=r_max=g_min=g_max=b_min=b_max=0;
		r_min_last=r_max_last=g_min_last=g_max_last=b_min_last=b_max_last=0;
	}
}	   



int main(void)
{		
	u8 sensor=0;
	u8 lightmode=0,effect=0;
	s8 saturation=0,brightness=0,contrast=0;	

	Stm32_Clock_Init(9);	//系统时钟设置
	delay_init(72);	  		//延时初始化
	uart_init(72,115200); 	//串口初始化为115200
	LCD_Init();
	W25QXX_Init();				//初始化W25Q128 和SPI2
	POINT_COLOR=RED;
	tp_dev.init();			//触摸屏初始化 
	while(font_init()) 			//检查字库
	{;}  
	POINT_COLOR=RED;			//设置字体为红色 
	LCD_ShowString(30,50,200,16,16,"ELITE STM32F103 ^_^");	
	LCD_ShowString(30,70,200,16,16,"OV7670_OV7725 TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2017/11/1"); 
	LCD_ShowString(30,130,200,16,16,"KEY0:Light Mode");
	LCD_ShowString(30,150,200,16,16,"KEY1:Saturation");
	LCD_ShowString(30,170,200,16,16,"KEY_UP:Contrast");
	LCD_ShowString(30,190,200,16,16,"TPAD:Effects");	 
  	LCD_ShowString(30,210,200,16,16,"OV7670 Init...");
//	POINT_COLOR=RED;       
//	Show_Str(30,50,200,16,"战舰STM32F103开发板",16,0);	
	while(1)//初始化OV7725_OV7670
	{
		if(OV7670_Init()==0)
		{
			sensor=OV7670;
			LCD_ShowString(30,210,200,16,16,"OV7670 Init OK       ");
			delay_ms(1500);	 	   
			OV7670_Light_Mode(lightmode);
			OV7670_Color_Saturation(saturation);
			OV7670_Brightness(brightness);
			OV7670_Contrast(contrast);
			OV7670_Special_Effects(effect);
			OV7670_Window_Set(12,176,240,320);//设置窗口
			OV7670_CS=0;
			break;
		}else
		{
			LCD_ShowString(30,210,200,16,16,"OV7670 Error!!");
			delay_ms(200);
			LCD_Fill(30,210,239,246,WHITE);
			delay_ms(200);
		}
	}

	TIM6_Int_Init(9999,7199);			//10Khz计数频率,1秒钟中断	
	EXTI8_Init();						//使能外部中断8,捕获帧中断			
	LCD_Clear(BLACK);		
//	color1=0xffff;     //满值  
		while(1)
	{
		if(sensor==OV7670)OV7670_camera_refresh();	//更新显示

			
		
//		Show_Str(30,260,168,12,"中点颜色值为:",12,0);	
	
	}
} 





//		printf("t:%d\r\n",t);

