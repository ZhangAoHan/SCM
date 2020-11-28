#include "sys.h"
#include "usart.h"
#include "delay.h"

//#include "led.h"
//#include "key.h"
#include "TFT.h"
#include "spi.h"
#include "flash.h"
#include "AT24c02.h"

#include "text.h"		
#include "fontupd.h"
#include "stdio.h"
#include "string.h"


//添加的头文件
#include "touch.h" 
//#include "rtc.h"

//我的头文件
#include "guitouch.h"




/****************************
        数字按键界面
		 1  2  3  A
		 4  5  6  B
		 7  8  9  C
	 	 *  0  #  D
****************************/
void my_GUI_0(void)
{
	POINT_COLOR=BLACK; 
	LCD_DrawLine(59, 79, 59, 319);
	LCD_DrawLine(119, 79, 119, 319);
	LCD_DrawLine(179, 79, 179, 319);
	LCD_DrawLine(0, 79, 239, 79);
	LCD_DrawLine(0, 139, 239, 139);
	LCD_DrawLine(0, 199, 239, 199);
	LCD_DrawLine(0, 259, 239, 259);

//	POINT_COLOR=BLUE; 
//	Show_Str(0,0,"请输入：",16,0);
//	Show_Str(10,49,"删除",16,0);
//	Show_Str(195,49,"确定",16,0);

	POINT_COLOR=RED;  
	LCD_ShowChar(26,282,'*',16,0);
	LCD_ShowNum(86,282,0,1,16);
	LCD_ShowChar(146,282,'#',16,0);
	LCD_ShowChar(206,282,'D',16,0);

	LCD_ShowNum(26,222,7,1,16);
	LCD_ShowNum(86,222,8,1,16);
	LCD_ShowNum(146,222,9,1,16);
	LCD_ShowChar(206,222,'C',16,0);

    LCD_ShowNum(26,162,4,1,16);
	LCD_ShowNum(86,162,5,1,16);
	LCD_ShowNum(146,162,6,1,16);
	LCD_ShowChar(206,162,'B',16,0);

	LCD_ShowNum(26,102,1,1,16);
	LCD_ShowNum(86,102,2,1,16);
	LCD_ShowNum(146,102,3,1,16);
  LCD_ShowChar(206,102,'A',16,0);
}




/****************************
     数字按键触摸界面
****************************/
u8 my_Touch_0(void)
{
	//扫描触摸屏
	if(Pen_Point.Key_Sta==Key_Down)//触摸屏被按下
	{
		Pen_Int_Set(0);//关闭中断

			Convert_Pos();//转换结果，根据触摸屏的校准参数来决定转换后的结果,保存在X0,Y0中
			Pen_Point.Key_Sta=Key_Up;

			if(Pen_Point.X0>0&&Pen_Point.X0<59&&Pen_Point.Y0>79&&Pen_Point.Y0<139)				 //1
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(0,79,59,139,BLACK);//检验触摸区域
				}
				LCD_Fill(0,79,59,139,WHITE);

				Pen_Int_Set(1);//开启中断

				return 1;
			}
			else if(Pen_Point.X0>59&&Pen_Point.X0<119&&Pen_Point.Y0>79&&Pen_Point.Y0<139) 		//2
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(59,79,119,139,BLACK);//检验触摸区域
				}
				LCD_Fill(59,79,119,139,WHITE);

				Pen_Int_Set(1);//开启中断

				return 2;
			}
			else if(Pen_Point.X0>119&&Pen_Point.X0<179&&Pen_Point.Y0>79&&Pen_Point.Y0<139) 		//3
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(119,79,179,139,BLACK);//检验触摸区域
				}
				LCD_Fill(119,79,179,139,WHITE);

				Pen_Int_Set(1);//开启中断

				return 3;
			}
			else if(Pen_Point.X0>179&&Pen_Point.X0<239&&Pen_Point.Y0>79&&Pen_Point.Y0<139) 		//A
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(179,79,239,139,BLACK);//检验触摸区域
				}
				LCD_Fill(179,79,239,139,WHITE);

				Pen_Int_Set(1);//开启中断

				return 4;
			}

			else if(Pen_Point.X0>0&&Pen_Point.X0<59&&Pen_Point.Y0>139&&Pen_Point.Y0<199)		//4
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(0,139,59,199,BLACK);//检验触摸区域
				}
				LCD_Fill(0,139,59,199,WHITE);

				Pen_Int_Set(1);//开启中断

				return 5;
			}
			else if(Pen_Point.X0>59&&Pen_Point.X0<119&&Pen_Point.Y0>139&&Pen_Point.Y0<199)		//5
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(59,139,119,199,BLACK);//检验触摸区域
				}
				LCD_Fill(59,139,119,199,WHITE);

				Pen_Int_Set(1);//开启中断

				return 6;
			}
			else if(Pen_Point.X0>119&&Pen_Point.X0<179&&Pen_Point.Y0>139&&Pen_Point.Y0<199)		 //6
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(119,139,179,199,BLACK);//检验触摸区域
				}
				LCD_Fill(119,139,179,199,WHITE);

				Pen_Int_Set(1);//开启中断

				return 7;
			}
			else if(Pen_Point.X0>179&&Pen_Point.X0<239&&Pen_Point.Y0>139&&Pen_Point.Y0<199)		 //B
			{  	
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(179,139,239,199,BLACK);//检验触摸区域
				}
				LCD_Fill(179,139,239,199,WHITE);

				Pen_Int_Set(1);//开启中断

				return 8;
			}

			else if(Pen_Point.X0>0&&Pen_Point.X0<59&&Pen_Point.Y0>199&&Pen_Point.Y0<259)		 //7
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(0,199,59,259,BLACK);//检验触摸区域
				}
				LCD_Fill(0,199,59,259,WHITE);

				Pen_Int_Set(1);//开启中断

				return 9;
			}
			else if(Pen_Point.X0>59&&Pen_Point.X0<119&&Pen_Point.Y0>199&&Pen_Point.Y0<259)		//8
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(59,199,119,259,BLACK);//检验触摸区域
				}
				LCD_Fill(59,199,119,259,WHITE);

				Pen_Int_Set(1);//开启中断

				return 10;
			}
			else if(Pen_Point.X0>119&&Pen_Point.X0<179&&Pen_Point.Y0>199&&Pen_Point.Y0<259)		 //9
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(119,199,179,259,BLACK);//检验触摸区域
				}
				LCD_Fill(119,199,179,259,WHITE);

				Pen_Int_Set(1);//开启中断

				return 11;
			}
			else if(Pen_Point.X0>179&&Pen_Point.X0<239&&Pen_Point.Y0>199&&Pen_Point.Y0<259)		//C
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(179,199,239,259,BLACK);//检验触摸区域
				}
				LCD_Fill(179,199,239,259,WHITE);

				Pen_Int_Set(1);//开启中断

				return 12;
			}

			else if(Pen_Point.X0>0&&Pen_Point.X0<59&&Pen_Point.Y0>259&&Pen_Point.Y0<319)	   //*
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(0,259,59,319,BLACK);//检验触摸区域
				}
				LCD_Fill(0,259,59,319,WHITE);

				Pen_Int_Set(1);//开启中断

				return 13;
			}
			else if(Pen_Point.X0>59&&Pen_Point.X0<119&&Pen_Point.Y0>259&&Pen_Point.Y0<319)		//0
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(59,259,119,319,BLACK);//检验触摸区域
				}
				LCD_Fill(59,259,119,319,WHITE);

				Pen_Int_Set(1);//开启中断

				return 14;
			}
			else if(Pen_Point.X0>119&&Pen_Point.X0<179&&Pen_Point.Y0>259&&Pen_Point.Y0<319)		//#
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(119,259,179,319,BLACK);//检验触摸区域
				}
				LCD_Fill(119,259,179,319,WHITE);

				Pen_Int_Set(1);//开启中断

				return 15;
			}
			else if(Pen_Point.X0>179&&Pen_Point.X0<239&&Pen_Point.Y0>259&&Pen_Point.Y0<319)		 //D
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(179,259,239,319,BLACK);//检验触摸区域
				}
				LCD_Fill(179,259,239,319,WHITE);

				Pen_Int_Set(1);//开启中断

				return 16;
			}

			else if(Pen_Point.X0>0&&Pen_Point.X0<59&&Pen_Point.Y0>19&&Pen_Point.Y0<79)			 //
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(0,19,59,79,BLACK);//检验触摸区域
				}
				LCD_Fill(0,19,59,79,WHITE);

				Pen_Int_Set(1);//开启中断

				return 17;
			}
			else if(Pen_Point.X0>179&&Pen_Point.X0<239&&Pen_Point.Y0>19&&Pen_Point.Y0<79)		 //
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(179,19,239,79,BLACK);//检验触摸区域
				}
				LCD_Fill(179,19,239,79,WHITE);

				Pen_Int_Set(1);//开启中断

				return 18;
			}

		Pen_Int_Set(1);//开启中断
	}

//	delay_ms(10);//每过10ms查询一次触摸屏
	return 0;	 //没有触摸按键按下


//	//LED闪烁指示程序正在运行,延时时间 = delay_ms(10)*50 = 500ms
//	i++;     
//	if(i==50)
//	{
//		i=0;
//		LED0=!LED0;
//	}	

}




/***********************************
        数字按键触摸键值处理
***********************************/
void my_GUI_Touch_0(void)
{
	u8 key,i=0;

	Touch_Init();	 //初始化 
	LCD_Clear(WHITE);//清屏

	my_GUI_0(); 	 //操作界面

	while(1)
	{
		key=my_Touch_0();	     //获取触摸键值
		
		switch(key)			     //相应键值的处理
		{
			case 0:		LCD_ShowNum(109,20,0,2,16);  	   //没有触摸按键按下
						my_GUI_0();  				       //一直显示操作界面
						break;

			case 1:		LCD_ShowNum(109,0,1,2,16); 	       //1 
						break;

			case 2:		LCD_ShowNum(109,0,2,2,16); 		   //2 
						break;

			case 3:		LCD_ShowNum(109,0,3,2,16); 		   //3 
						break;

			case 4:		LCD_ShowChar(116,0,'A',16,0); 	   //A 	
						break;

			case 5:		LCD_ShowNum(109,0,4,2,16); 		   //4 
						break;

			case 6:		LCD_ShowNum(109,0,5,2,16); 		   //5 
						break;

			case 7:		LCD_ShowNum(109,0,6,2,16); 		   //6 
						break;

			case 8:		LCD_ShowChar(116,0,'B',16,0);	   //B 
						break;

			case 9:		LCD_ShowNum(109,0,7,2,16); 		   //7 
						break;

			case 10:	LCD_ShowNum(109,0,8,2,16);         //8	
						break;

			case 11:	LCD_ShowNum(109,0,9,2,16);	       //9
						break;

			case 12:	LCD_ShowChar(116,0,'C',16,0);      //C	
						break;

			case 13:	LCD_ShowChar(116,0,'*',16,0);      //*
						break;

			case 14:	LCD_ShowNum(109,0,0,2,16);	       //0	
						break;

			case 15:	LCD_ShowChar(116,0,'#',16,0);	   //#	
						break;

			case 16:	LCD_ShowChar(116,0,'D',16,0);      //D	
						break;

			case 17:	LCD_ShowChar(116,0,'Y',16,0);      //	
						break;

			case 18:	LCD_ShowChar(116,0,'N',16,0);      //
//						return;							   //返回空值，退出此函数
						break;

			default:	break;
		}


		delay_ms(10);//每过10ms查询一次触摸屏


		//LED闪烁指示程序正在运行,延时时间 = delay_ms(10)*50 = 500ms
		i++;     
		if(i==50)
		{
			i=0;
			LED0=!LED0;
		}	
	}
}


















