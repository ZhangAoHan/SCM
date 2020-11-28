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
//#include "ds18b20.h"
//#include "rc522_add.h"


//我的头文件
#include "mygui.h"



u8 input[5]={0,0,0,0,0};
u8 length=0;
u8 card_num[12]={0,0,0,0,0,0,0,0,0,0,0,0};//卡号12位
u8 password[6]={0,0,0,0,0,0};							//密码6位

u8 card_status=0;




/****************************
        数字按键界面
****************************/
void GUI_DISP_0(void)
{
	POINT_COLOR=BLACK; 
	LCD_DrawLine(59, 79, 59, 319);
	LCD_DrawLine(119, 79, 119, 319);
	LCD_DrawLine(179, 79, 179, 319);
	LCD_DrawLine(0, 79, 239, 79);
	LCD_DrawLine(0, 139, 239, 139);
	LCD_DrawLine(0, 199, 239, 199);
	LCD_DrawLine(0, 259, 239, 259);

	POINT_COLOR=BLUE; 
	Show_Str(0,0,"请输入：",16,0);
	Show_Str(10,49,"删除",16,0);
	Show_Str(195,49,"确定",16,0);

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
void my_GUI_TOUCH_2(void)
{
	u8 i=0;

// 	Touch_Init();	 //初始化
	LCD_Clear(WHITE);//清屏

	GUI_DISP_0();	 //数字按键界面

	//触摸扫描
	while(1)
	{	
		if(Pen_Point.Key_Sta==Key_Down)//触摸屏被按下
		{
			Pen_Int_Set(0);//关闭中断

				Convert_Pos();//转换结果，根据触摸屏的校准参数来决定转换后的结果,保存在X0,Y0中
				Pen_Point.Key_Sta=Key_Up;

				if(Pen_Point.X0>0&&Pen_Point.X0<59&&Pen_Point.Y0>79&&Pen_Point.Y0<139)
				{
					while(PEN==0)  //等待触摸释放
					{
						LCD_Fill(0,79,59,139,BLACK);//检验触摸区域
					}
					LCD_Fill(0,79,59,139,WHITE);
					GUI_DISP_0();

					LCD_ShowNum(119,39,1,1,16);  												//1
				}
				else if(Pen_Point.X0>59&&Pen_Point.X0<119&&Pen_Point.Y0>79&&Pen_Point.Y0<139) 
				{
					while(PEN==0)  //等待触摸释放
					{
						LCD_Fill(59,79,119,139,BLACK);//检验触摸区域
					}
					LCD_Fill(59,79,119,139,WHITE);
					GUI_DISP_0();

					LCD_ShowNum(119,39,2,1,16);													//2
				}
				else if(Pen_Point.X0>119&&Pen_Point.X0<179&&Pen_Point.Y0>79&&Pen_Point.Y0<139) 
				{
					while(PEN==0)  //等待触摸释放
					{
						LCD_Fill(119,79,179,139,BLACK);//检验触摸区域
					}
					LCD_Fill(119,79,179,139,WHITE);
					GUI_DISP_0();

					LCD_ShowNum(119,39,3,1,16);												  //3
				}
				else if(Pen_Point.X0>179&&Pen_Point.X0<239&&Pen_Point.Y0>79&&Pen_Point.Y0<139) 
				{
					while(PEN==0)  //等待触摸释放
					{
						LCD_Fill(179,79,239,139,BLACK);//检验触摸区域
					}
					LCD_Fill(179,79,239,139,WHITE);
					GUI_DISP_0();

					LCD_ShowChar(119,39,'A',16,0);											//A
				}

				else if(Pen_Point.X0>0&&Pen_Point.X0<59&&Pen_Point.Y0>139&&Pen_Point.Y0<199)
				{
					while(PEN==0)  //等待触摸释放
					{
						LCD_Fill(0,139,59,199,BLACK);//检验触摸区域
					}
					LCD_Fill(0,139,59,199,WHITE);
					GUI_DISP_0();

					LCD_ShowNum(119,39,4,1,16); 												//4
				}
				else if(Pen_Point.X0>59&&Pen_Point.X0<119&&Pen_Point.Y0>139&&Pen_Point.Y0<199)
				{
					while(PEN==0)  //等待触摸释放
					{
						LCD_Fill(59,139,119,199,BLACK);//检验触摸区域
					}
					LCD_Fill(59,139,119,199,WHITE);
					GUI_DISP_0();

					LCD_ShowNum(119,39,5,1,16); 												//5
				}
				else if(Pen_Point.X0>119&&Pen_Point.X0<179&&Pen_Point.Y0>139&&Pen_Point.Y0<199)
				{
					while(PEN==0)  //等待触摸释放
					{
						LCD_Fill(119,139,179,199,BLACK);//检验触摸区域
					}
					LCD_Fill(119,139,179,199,WHITE);
					GUI_DISP_0();

					LCD_ShowNum(119,39,6,1,16);													//6
				}
				else if(Pen_Point.X0>179&&Pen_Point.X0<239&&Pen_Point.Y0>139&&Pen_Point.Y0<199)
				{  	
					while(PEN==0)  //等待触摸释放
					{
						LCD_Fill(179,139,239,199,BLACK);//检验触摸区域
					}
					LCD_Fill(179,139,239,199,WHITE);
					GUI_DISP_0();

					LCD_ShowChar(119,39,'B',16,0);											//B
				}

				else if(Pen_Point.X0>0&&Pen_Point.X0<59&&Pen_Point.Y0>199&&Pen_Point.Y0<259)
				{
					while(PEN==0)  //等待触摸释放
					{
						LCD_Fill(0,199,59,259,BLACK);//检验触摸区域
					}
					LCD_Fill(0,199,59,259,WHITE);
					GUI_DISP_0();

					LCD_ShowNum(119,39,7,1,16);  												//7
				}
				else if(Pen_Point.X0>59&&Pen_Point.X0<119&&Pen_Point.Y0>199&&Pen_Point.Y0<259)
				{
					while(PEN==0)  //等待触摸释放
					{
						LCD_Fill(59,199,119,259,BLACK);//检验触摸区域
					}
					LCD_Fill(59,199,119,259,WHITE);
					GUI_DISP_0();

					LCD_ShowNum(119,39,8,1,16);													//8
				}
				else if(Pen_Point.X0>119&&Pen_Point.X0<179&&Pen_Point.Y0>199&&Pen_Point.Y0<259)
				{
					while(PEN==0)  //等待触摸释放
					{
						LCD_Fill(119,199,179,259,BLACK);//检验触摸区域
					}
					LCD_Fill(119,199,179,259,WHITE);
					GUI_DISP_0();

					LCD_ShowNum(119,39,9,1,16);													//9
				}
				else if(Pen_Point.X0>179&&Pen_Point.X0<239&&Pen_Point.Y0>199&&Pen_Point.Y0<259)
				{
					while(PEN==0)  //等待触摸释放
					{
						LCD_Fill(179,199,239,259,BLACK);//检验触摸区域
					}
					LCD_Fill(179,199,239,259,WHITE);
					GUI_DISP_0();

					LCD_ShowChar(119,39,'C',16,0);											//C
				}

				else if(Pen_Point.X0>0&&Pen_Point.X0<59&&Pen_Point.Y0>259&&Pen_Point.Y0<319)
				{
					while(PEN==0)  //等待触摸释放
					{
						LCD_Fill(0,259,59,319,BLACK);//检验触摸区域
					}
					LCD_Fill(0,259,59,319,WHITE);
					GUI_DISP_0();

					LCD_ShowChar(119,39,'*',16,0);											//*
				}
				else if(Pen_Point.X0>59&&Pen_Point.X0<119&&Pen_Point.Y0>259&&Pen_Point.Y0<319)
				{
					while(PEN==0)  //等待触摸释放
					{
						LCD_Fill(59,259,119,319,BLACK);//检验触摸区域
					}
					LCD_Fill(59,259,119,319,WHITE);
					GUI_DISP_0();

					LCD_ShowNum(119,39,0,1,16);												  //0
				}
				else if(Pen_Point.X0>119&&Pen_Point.X0<179&&Pen_Point.Y0>259&&Pen_Point.Y0<319)
				{
					while(PEN==0)  //等待触摸释放
					{
						LCD_Fill(119,259,179,319,BLACK);//检验触摸区域
					}
					LCD_Fill(119,259,179,319,WHITE);
					GUI_DISP_0();

					LCD_ShowChar(119,39,'#',16,0);											//#
				}
				else if(Pen_Point.X0>179&&Pen_Point.X0<239&&Pen_Point.Y0>259&&Pen_Point.Y0<319)
				{
					while(PEN==0)  //等待触摸释放
					{
						LCD_Fill(179,259,239,319,BLACK);//检验触摸区域
					}
					LCD_Fill(179,259,239,319,WHITE);
					GUI_DISP_0();

					LCD_ShowChar(119,39,'D',16,0);											//D
				}

				else if(Pen_Point.X0>0&&Pen_Point.X0<59&&Pen_Point.Y0>19&&Pen_Point.Y0<79)
				{
					while(PEN==0)  //等待触摸释放
					{
						LCD_Fill(0,19,59,79,BLACK);//检验触摸区域
					}
					LCD_Fill(0,19,59,79,WHITE);
					GUI_DISP_0();

					LCD_ShowChar(119,39,' ',16,0);			    					 //删除
				}
				else if(Pen_Point.X0>179&&Pen_Point.X0<239&&Pen_Point.Y0>19&&Pen_Point.Y0<79)
				{
					while(PEN==0)  //等待触摸释放
					{
						LCD_Fill(179,19,239,79,BLACK);//检验触摸区域
					}
					LCD_Fill(179,19,239,79,WHITE);
					GUI_DISP_0();

					LED1=!LED1;								    										 //确定

//					Pen_Int_Set(1);//开启中断：因为下面的切换界面语句，这里要开启前面关闭的中断 
					delay_ms(10);	
					//切换界面							
				}

			Pen_Int_Set(1);//开启中断
			delay_ms(10);
		}else delay_ms(10);//每过10ms查询一次触摸屏


		//LED闪烁指示程序正在运行,延时时间 = delay_ms(10)*50 = 500ms
		i++;     
		if(i==50)
		{
			i=0;
			LED0=!LED0;
		}	
	}
}







/****************************
     RTC实时时钟显示界面
****************************/
void GUI_DISP_1(void) 
{
	u8 t=0;	

	RTC_Init();

//  	Touch_Init();	//初始化
	LCD_Clear(WHITE);//清屏

	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(60,50,"Mini STM32");	
	LCD_ShowString(60,70,"RTC TEST");	
	LCD_ShowString(60,90,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,"2010/12/30");
		
	//显示时间
	POINT_COLOR=BLUE;//设置字体为蓝色
	LCD_ShowString(60,130,"    -  -  ");	   
	LCD_ShowString(60,162,"  :  :  ");		    
	while(1)
	{	
		//触摸扫描
		if(Pen_Point.Key_Sta==Key_Down)//触摸屏被按下
		{
			Pen_Int_Set(0);//关闭中断

				Convert_Pos();//转换结果，根据触摸屏的校准参数来决定转换后的结果,保存在X0,Y0中
				Pen_Point.Key_Sta=Key_Up;

				if(Pen_Point.X0>0&&Pen_Point.X0<239&&Pen_Point.Y0>0&&Pen_Point.Y0<319)
				{
					while(PEN==0)  //等待触摸释放
					{
						LCD_Fill(0,0,239,319,BLUE);//检验触摸区域
					}
//					Pen_Int_Set(1);//开启中断：因为下面的切换界面语句，这里要开启前面关闭的中断 
					delay_ms(10);
					//切换界面
				}

			Pen_Int_Set(1);//开启中断
			delay_ms(10);
		}else delay_ms(10);//每过10ms查询一次触摸屏
		
		
		//秒中断发生（更新日期和时间）							    
		if(t!=timer.sec)
		{
			t=timer.sec;
			LCD_ShowNum(60,130,timer.w_year,4,16);									  
			LCD_ShowNum(100,130,timer.w_month,2,16);									  
			LCD_ShowNum(124,130,timer.w_date,2,16);	 
			switch(timer.week)
			{
				case 0:
					LCD_ShowString(60,148,"Sunday   ");
					break;
				case 1:
					LCD_ShowString(60,148,"Monday   ");
					break;
				case 2:
					LCD_ShowString(60,148,"Tuesday  ");
					break;
				case 3:
					LCD_ShowString(60,148,"Wednesday");
					break;
				case 4:
					LCD_ShowString(60,148,"Thursday ");
					break;
				case 5:
					LCD_ShowString(60,148,"Friday   ");
					break;
				case 6:
					LCD_ShowString(60,148,"Saturday ");
					break;  
			}
			LCD_ShowNum(60,162,timer.hour,2,16);									  
			LCD_ShowNum(84,162,timer.min,2,16);									  
			LCD_ShowNum(108,162,timer.sec,2,16);

			//每秒闪烁一次
			LED0=!LED0;
		}								  
	}  
}







/***********************************
      数字按键触摸扫描反馈键值
***********************************/
u8 my_GUI_TOUCH_0(void)
{	
	
	//扫描触摸屏
	if(Pen_Point.Key_Sta==Key_Down)//触摸屏被按下
	{
		Pen_Int_Set(0);//关闭中断

			Convert_Pos();//转换结果，根据触摸屏的校准参数来决定转换后的结果,保存在X0,Y0中
			Pen_Point.Key_Sta=Key_Up;

			if(Pen_Point.X0>0&&Pen_Point.X0<59&&Pen_Point.Y0>79&&Pen_Point.Y0<139)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(0,79,59,139,BLACK);//检验触摸区域
				}
				LCD_Fill(0,79,59,139,WHITE);

				Pen_Int_Set(1);//开启中断

				return 1;
			}
			else if(Pen_Point.X0>59&&Pen_Point.X0<119&&Pen_Point.Y0>79&&Pen_Point.Y0<139) 
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(59,79,119,139,BLACK);//检验触摸区域
				}
				LCD_Fill(59,79,119,139,WHITE);

				Pen_Int_Set(1);//开启中断

				return 2;
			}
			else if(Pen_Point.X0>119&&Pen_Point.X0<179&&Pen_Point.Y0>79&&Pen_Point.Y0<139) 
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(119,79,179,139,BLACK);//检验触摸区域
				}
				LCD_Fill(119,79,179,139,WHITE);

				Pen_Int_Set(1);//开启中断

				return 3;
			}
			else if(Pen_Point.X0>179&&Pen_Point.X0<239&&Pen_Point.Y0>79&&Pen_Point.Y0<139) 
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(179,79,239,139,BLACK);//检验触摸区域
				}
				LCD_Fill(179,79,239,139,WHITE);

				Pen_Int_Set(1);//开启中断

				return 4;
			}

			else if(Pen_Point.X0>0&&Pen_Point.X0<59&&Pen_Point.Y0>139&&Pen_Point.Y0<199)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(0,139,59,199,BLACK);//检验触摸区域
				}
				LCD_Fill(0,139,59,199,WHITE);

				Pen_Int_Set(1);//开启中断

				return 5;
			}
			else if(Pen_Point.X0>59&&Pen_Point.X0<119&&Pen_Point.Y0>139&&Pen_Point.Y0<199)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(59,139,119,199,BLACK);//检验触摸区域
				}
				LCD_Fill(59,139,119,199,WHITE);

				Pen_Int_Set(1);//开启中断

				return 6;
			}
			else if(Pen_Point.X0>119&&Pen_Point.X0<179&&Pen_Point.Y0>139&&Pen_Point.Y0<199)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(119,139,179,199,BLACK);//检验触摸区域
				}
				LCD_Fill(119,139,179,199,WHITE);

				Pen_Int_Set(1);//开启中断

				return 7;
			}
			else if(Pen_Point.X0>179&&Pen_Point.X0<239&&Pen_Point.Y0>139&&Pen_Point.Y0<199)
			{  	
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(179,139,239,199,BLACK);//检验触摸区域
				}
				LCD_Fill(179,139,239,199,WHITE);

				Pen_Int_Set(1);//开启中断

				return 8;
			}

			else if(Pen_Point.X0>0&&Pen_Point.X0<59&&Pen_Point.Y0>199&&Pen_Point.Y0<259)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(0,199,59,259,BLACK);//检验触摸区域
				}
				LCD_Fill(0,199,59,259,WHITE);

				Pen_Int_Set(1);//开启中断

				return 9;
			}
			else if(Pen_Point.X0>59&&Pen_Point.X0<119&&Pen_Point.Y0>199&&Pen_Point.Y0<259)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(59,199,119,259,BLACK);//检验触摸区域
				}
				LCD_Fill(59,199,119,259,WHITE);

				Pen_Int_Set(1);//开启中断

				return 10;
			}
			else if(Pen_Point.X0>119&&Pen_Point.X0<179&&Pen_Point.Y0>199&&Pen_Point.Y0<259)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(119,199,179,259,BLACK);//检验触摸区域
				}
				LCD_Fill(119,199,179,259,WHITE);

				Pen_Int_Set(1);//开启中断

				return 11;
			}
			else if(Pen_Point.X0>179&&Pen_Point.X0<239&&Pen_Point.Y0>199&&Pen_Point.Y0<259)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(179,199,239,259,BLACK);//检验触摸区域
				}
				LCD_Fill(179,199,239,259,WHITE);

				Pen_Int_Set(1);//开启中断

				return 12;
			}

			else if(Pen_Point.X0>0&&Pen_Point.X0<59&&Pen_Point.Y0>259&&Pen_Point.Y0<319)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(0,259,59,319,BLACK);//检验触摸区域
				}
				LCD_Fill(0,259,59,319,WHITE);

				Pen_Int_Set(1);//开启中断

				return 13;
			}
			else if(Pen_Point.X0>59&&Pen_Point.X0<119&&Pen_Point.Y0>259&&Pen_Point.Y0<319)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(59,259,119,319,BLACK);//检验触摸区域
				}
				LCD_Fill(59,259,119,319,WHITE);

				Pen_Int_Set(1);//开启中断

				return 14;
			}
			else if(Pen_Point.X0>119&&Pen_Point.X0<179&&Pen_Point.Y0>259&&Pen_Point.Y0<319)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(119,259,179,319,BLACK);//检验触摸区域
				}
				LCD_Fill(119,259,179,319,WHITE);

				Pen_Int_Set(1);//开启中断

				return 15;
			}
			else if(Pen_Point.X0>179&&Pen_Point.X0<239&&Pen_Point.Y0>259&&Pen_Point.Y0<319)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(179,259,239,319,BLACK);//检验触摸区域
				}
				LCD_Fill(179,259,239,319,WHITE);

				Pen_Int_Set(1);//开启中断

				return 16;
			}

			else if(Pen_Point.X0>0&&Pen_Point.X0<59&&Pen_Point.Y0>19&&Pen_Point.Y0<79)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(0,19,59,79,BLACK);//检验触摸区域
				}
				LCD_Fill(0,19,59,79,WHITE);

				Pen_Int_Set(1);//开启中断

				return 17;
			}
			else if(Pen_Point.X0>179&&Pen_Point.X0<239&&Pen_Point.Y0>19&&Pen_Point.Y0<79)
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
void my_GUI_TOUCH_1(void)
{
	u8 key,i=0;

// 	Touch_Init();	 //初始化 
	LCD_Clear(WHITE);//清屏

	GUI_DISP_0(); 	 //操作界面

	while(1)
	{
		key=my_GUI_TOUCH_0();	 //获取触摸键值
		
		switch(key)			       //相应键值的处理
		{
			case 0:		LCD_ShowNum(109,20,0,2,16);  	  //没有触摸按键按下
								GUI_DISP_0();   				   			//一直显示操作界面
								break;

			case 1:		LCD_ShowNum(109,0,1,2,16); 	    //1 
								break;

			case 2:		LCD_ShowNum(109,0,2,2,16); 		  //2 
								break;

			case 3:		LCD_ShowNum(109,0,3,2,16); 		  //3 
								break;

			case 4:		LCD_ShowChar(116,0,'A',16,0); 	//A 	
								break;

			case 5:		LCD_ShowNum(109,0,4,2,16); 		  //4 
								break;

			case 6:		LCD_ShowNum(109,0,5,2,16); 		  //5 
								break;

			case 7:		LCD_ShowNum(109,0,6,2,16); 		  //6 
								break;

			case 8:		LCD_ShowChar(116,0,'B',16,0);	  //B 
								break;

			case 9:		LCD_ShowNum(109,0,7,2,16); 		  //7 
								break;

			case 10:	LCD_ShowNum(109,0,8,2,16);      //8	
								break;

			case 11:	LCD_ShowNum(109,0,9,2,16);	    //9
								break;

			case 12:	LCD_ShowChar(116,0,'C',16,0);   //C	
								break;

			case 13:	LCD_ShowChar(116,0,'*',16,0);   //*
								break;

			case 14:	LCD_ShowNum(109,0,0,2,16);	    //0	
								break;

			case 15:	LCD_ShowChar(116,0,'#',16,0);	  //#	
								break;

			case 16:	LCD_ShowChar(116,0,'D',16,0);   //D	
								break;

			case 17:	LCD_ShowChar(116,0,'Y',16,0);   //删除	
								break;

			case 18:	LCD_ShowChar(116,0,'N',16,0);   //确定
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





/***********************************
           温度显示界面
***********************************/
void GUI_DISP_2(void)            
{
	short temp; 
	POINT_COLOR=RED;//设置字体为红色	   
	LCD_ShowString(60,50,"Mini STM32");	
	LCD_ShowString(60,70,"DS18B20 TEST");	
	LCD_ShowString(60,90,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,"2011/1/1");
	while(DS18B20_Init())//初始化DS18B20,兼检测18B20
	{
		LCD_ShowString(60,130,"DS18B20 Check Failed!");
		delay_ms(500);		  
		LCD_ShowString(60,130,"Please Check!        ");
		delay_ms(500);
		LED0=!LED0;//DS0闪烁
	}
  LCD_ShowString(60,130,"DS18B20 Ready!     ");	 
 	POINT_COLOR=BLUE;//设置字体为蓝色	   
	LCD_ShowString(60,150, "Temperate:   . C");	 
	while(1)
	{	  
		temp=DS18B20_Get_Temp();
		if(temp<0)
		{
			temp=-temp;
			LCD_ShowChar(140,150,'-',16,0);//显示负号	
		}						 
		LCD_ShowNum(148,150,temp/10,2,16);//显示温度值	  
		LCD_ShowNum(172,150,temp%10,1,16);//显示温度值
		//printf("t1:%d\n",temp);
		delay_ms(200);
		LED0=!LED0;
	}			
}













/***********************************
        菜单栏显示触摸界面
***********************************/
void GUI_DISP_MENU(void)         
{
	POINT_COLOR=BLACK; 
	LCD_DrawLine(0, 39, 239, 39);										//横
	LCD_DrawLine(0, 39+70+20, 239, 39+70+20);				//横
	LCD_DrawLine(0, 39+70+70+40, 239, 39+70+70+40); //横
	LCD_DrawLine(119, 39, 119, 319);								//竖
	
	POINT_COLOR=BLUE; 
	Show_Str(100,10,"菜单栏",16,0);
	Show_Str(39+5,75,"充值",16,0);
	Show_Str(39+120+5,75,"消费",16,0);
	Show_Str(39+5,75+90,"查询",16,0);
	Show_Str(39+30+120-40,75+90,"挂失/解挂",16,0);
	
	POINT_COLOR=RED; 
	Show_Str(5+10,39+70+70+40+11,"今天的温度",16,0);
	Show_Str(5+10+120,39+70+70+40+11,"日期和时间",16,0);
	
}

//键值返回
u8 TOUCH_DISP_MENU(void) 				 		
{
	//扫描触摸屏
	if(Pen_Point.Key_Sta==Key_Down)//触摸屏被按下
	{
		  Pen_Int_Set(0);//关闭中断

			Convert_Pos();//转换结果，根据触摸屏的校准参数来决定转换后的结果,保存在X0,Y0中
			Pen_Point.Key_Sta=Key_Up;

			if(Pen_Point.X0>0&&Pen_Point.X0<119&&Pen_Point.Y0>39&&Pen_Point.Y0<129)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(0,39,119,129,BLACK);//检验触摸区域
				}
				LCD_Fill(0,39,119,129,WHITE);

				Pen_Int_Set(1);//开启中断

				return 1;
			}
			else if(Pen_Point.X0>119&&Pen_Point.X0<239&&Pen_Point.Y0>39&&Pen_Point.Y0<129) 
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(119,39,239,129,BLACK);//检验触摸区域
				}
				LCD_Fill(119,39,239,129,WHITE);

				Pen_Int_Set(1);//开启中断

				return 2;
			}
			else if(Pen_Point.X0>0&&Pen_Point.X0<119&&Pen_Point.Y0>129&&Pen_Point.Y0<219) 
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(0,129,119,219,BLACK);//检验触摸区域
				}
				LCD_Fill(0,129,119,219,WHITE);

				Pen_Int_Set(1);//开启中断

				return 3;
			}
			else if(Pen_Point.X0>119&&Pen_Point.X0<239&&Pen_Point.Y0>129&&Pen_Point.Y0<219) 
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(119,129,239,219,BLACK);//检验触摸区域
				}
				LCD_Fill(119,129,239,219,WHITE);

				Pen_Int_Set(1);//开启中断

				return 4;
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

//键值处理
void TOUCH_GUI_DISP_MENU(void)		 		
{
	u8 key;
// 	u8 i=0;
	u8 t=0;	
	short temp; 
	
	card_status=0;//状态清零

// 	Touch_Init();	 //初始化 
	LCD_Clear(WHITE);//清屏

	GUI_DISP_MENU();         //菜单栏显示触摸界面
	
	
	//显示时间
	POINT_COLOR=BLUE;//设置字体为蓝色
	LCD_ShowString(60+65+10,130+70+40+20,"    -  -  ");	   
	LCD_ShowString(60+65+15,162+70+40+20,"  :  :  ");		    

	
	//显示温度
	POINT_COLOR=BLUE;//设置字体为蓝色	   
	LCD_ShowString(10,250+20, "      . C");	 

	
	while(1)
	{
		//秒中断发生（更新日期和时间）							    
		if(t!=timer.sec)
		{
			t=timer.sec;
			LCD_ShowNum(60+65+10,130+70+40+20,timer.w_year,4,16);									  
			LCD_ShowNum(100+65+10,130+70+40+20,timer.w_month,2,16);									  
			LCD_ShowNum(124+65+10,130+70+40+20,timer.w_date,2,16);	 
			switch(timer.week)
			{
				case 0:
					LCD_ShowString(60+65+20,146+70+40+20,"Sunday   ");
					break;
				case 1:
					LCD_ShowString(60+65+20,146+70+40+20,"Monday   ");
					break;
				case 2:
					LCD_ShowString(60+65+20,146+70+40+20,"Tuesday  ");
					break;
				case 3:
					LCD_ShowString(60+65+20,146+70+40+20,"Wednesday");
					break;
				case 4:
					LCD_ShowString(60+65+20,146+70+40+20,"Thursday ");
					break;
				case 5:
					LCD_ShowString(60+65+20,146+70+40+20,"Friday   ");
					break;
				case 6:
					LCD_ShowString(60+65+20,146+70+40+20,"Saturday ");
					break;  
			}
			LCD_ShowNum(60+65+15,162+70+40+20,timer.hour,2,16);									  
			LCD_ShowNum(84+65+15,162+70+40+20,timer.min,2,16);									  
			LCD_ShowNum(108+65+15,162+70+40+20,timer.sec,2,16);

// 			//每秒闪烁一次
// 			LED0=!LED0;
		}		
		
		
		
		//更新温度
		temp=DS18B20_Get_Temp();
		if(temp<0)
		{
			temp=-temp;
			LCD_ShowChar(140-110,250+20,'-',16,0);//显示负号	
		}						 
		LCD_ShowNum(148-110,250+20,temp/10,2,16);//显示温度值	  
		LCD_ShowNum(172-110,250+20,temp%10,1,16);//显示温度值
		
		
		
		
		
		key=TOUCH_DISP_MENU(); //获取触摸键值
		switch(key)			       //相应键值的处理
		{
			case 0:		GUI_DISP_MENU();   				 //没有触摸按键按下，一直显示操作界面
								break;

			case 1:		TOUCH_GUI_DISP_administrator(); 	  //管理员验证
								break;

			case 2:		TOUCH_GUI_DISP_xiaofei(); 		   		//消费
								break;

			case 3:		TOUCH_GUI_DISP_chaxun();    		 		//查询
								break;

			case 4:		TOUCH_GUI_DISP_guashijiegua(); 	 		//挂失/解挂	
								break;


			default:	break;
		}
		

		delay_ms(10);//每过10ms查询一次触摸屏

// 		//LED闪烁指示程序正在运行,延时时间 = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}












/***********************************
        充值显示触摸界面
***********************************/
void GUI_DISP_chongzhi(void)     
{
	POINT_COLOR=BLACK; 
	LCD_DrawLine(0, 39, 239, 39);					//横
	LCD_DrawLine(0, 79, 239, 79);					//横
	LCD_DrawLine(0, 79+60, 239, 79+60);		//横
	LCD_DrawLine(0, 79+120, 239, 79+120);	//横
	LCD_DrawLine(0, 79+180, 239, 79+180);	//横
	LCD_DrawLine(59, 79+60, 59, 319);			//竖
	LCD_DrawLine(119, 79, 119, 319);			//竖
	LCD_DrawLine(179, 79+60, 179, 319);		//竖
	
	POINT_COLOR=BLUE; 
	Show_Str(60,10,"充值/单位（元）",16,0);
	Show_Str(20,10+40+60-5,"返回菜单栏",16,0);
	Show_Str(120+45,10+40+60-5,"确定",16,0);
	Show_Str(180+10+5,10+40+60+60-5,"重输",16,0);
	
	POINT_COLOR=RED;  
	LCD_ShowNum(26,162,0,1,16);
	LCD_ShowNum(86,162,1,1,16);
	LCD_ShowNum(146,162,2,1,16);
 
	LCD_ShowNum(26,222,3,1,16);
	LCD_ShowNum(86,222,4,1,16);
	LCD_ShowNum(146,222,5,1,16);
	LCD_ShowNum(206,222,6,1,16);
	
	LCD_ShowNum(26,282,7,1,16);
	LCD_ShowNum(86,282,8,1,16);
	LCD_ShowNum(146,282,9,1,16);
	LCD_ShowChar(206,282,'.',16,0);
}

//键值返回
u8 TOUCH_DISP_chongzhi(void)		 	 
{
	//扫描触摸屏
	if(Pen_Point.Key_Sta==Key_Down)//触摸屏被按下
	{
			Pen_Int_Set(0);//关闭中断

			Convert_Pos();//转换结果，根据触摸屏的校准参数来决定转换后的结果,保存在X0,Y0中
			Pen_Point.Key_Sta=Key_Up;

			if(Pen_Point.X0>0&&Pen_Point.X0<119&&Pen_Point.Y0>79&&Pen_Point.Y0<139)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(0,79,119,139,BLACK);//检验触摸区域
				}
				LCD_Fill(0,79,119,139,WHITE);

				Pen_Int_Set(1);//开启中断

				return 1;
			}
			else if(Pen_Point.X0>119&&Pen_Point.X0<239&&Pen_Point.Y0>79&&Pen_Point.Y0<139) 
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(119,79,239,139,BLACK);//检验触摸区域
				}
				LCD_Fill(119,79,239,139,WHITE);

				Pen_Int_Set(1);//开启中断

				return 2;
			}
			
			
			
			else if(Pen_Point.X0>0&&Pen_Point.X0<59&&Pen_Point.Y0>139&&Pen_Point.Y0<199)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(0,139,59,199,BLACK);//检验触摸区域
				}
				LCD_Fill(0,139,59,199,WHITE);

				Pen_Int_Set(1);//开启中断

				return 3;
			}
			else if(Pen_Point.X0>59&&Pen_Point.X0<119&&Pen_Point.Y0>139&&Pen_Point.Y0<199)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(59,139,119,199,BLACK);//检验触摸区域
				}
				LCD_Fill(59,139,119,199,WHITE);

				Pen_Int_Set(1);//开启中断

				return 4;
			}
			else if(Pen_Point.X0>119&&Pen_Point.X0<179&&Pen_Point.Y0>139&&Pen_Point.Y0<199)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(119,139,179,199,BLACK);//检验触摸区域
				}
				LCD_Fill(119,139,179,199,WHITE);

				Pen_Int_Set(1);//开启中断

				return 5;
			}
			else if(Pen_Point.X0>179&&Pen_Point.X0<239&&Pen_Point.Y0>139&&Pen_Point.Y0<199)
			{  	
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(179,139,239,199,BLACK);//检验触摸区域
				}
				LCD_Fill(179,139,239,199,WHITE);

				Pen_Int_Set(1);//开启中断

				return 6;
			}

			
			else if(Pen_Point.X0>0&&Pen_Point.X0<59&&Pen_Point.Y0>199&&Pen_Point.Y0<259)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(0,199,59,259,BLACK);//检验触摸区域
				}
				LCD_Fill(0,199,59,259,WHITE);

				Pen_Int_Set(1);//开启中断

				return 7;
			}
			else if(Pen_Point.X0>59&&Pen_Point.X0<119&&Pen_Point.Y0>199&&Pen_Point.Y0<259)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(59,199,119,259,BLACK);//检验触摸区域
				}
				LCD_Fill(59,199,119,259,WHITE);

				Pen_Int_Set(1);//开启中断

				return 8;
			}
			else if(Pen_Point.X0>119&&Pen_Point.X0<179&&Pen_Point.Y0>199&&Pen_Point.Y0<259)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(119,199,179,259,BLACK);//检验触摸区域
				}
				LCD_Fill(119,199,179,259,WHITE);

				Pen_Int_Set(1);//开启中断

				return 9;
			}
			else if(Pen_Point.X0>179&&Pen_Point.X0<239&&Pen_Point.Y0>199&&Pen_Point.Y0<259)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(179,199,239,259,BLACK);//检验触摸区域
				}
				LCD_Fill(179,199,239,259,WHITE);

				Pen_Int_Set(1);//开启中断

				return 10;
			}

			
			else if(Pen_Point.X0>0&&Pen_Point.X0<59&&Pen_Point.Y0>259&&Pen_Point.Y0<319)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(0,259,59,319,BLACK);//检验触摸区域
				}
				LCD_Fill(0,259,59,319,WHITE);

				Pen_Int_Set(1);//开启中断

				return 11;
			}
			else if(Pen_Point.X0>59&&Pen_Point.X0<119&&Pen_Point.Y0>259&&Pen_Point.Y0<319)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(59,259,119,319,BLACK);//检验触摸区域
				}
				LCD_Fill(59,259,119,319,WHITE);

				Pen_Int_Set(1);//开启中断

				return 12;
			}
			else if(Pen_Point.X0>119&&Pen_Point.X0<179&&Pen_Point.Y0>259&&Pen_Point.Y0<319)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(119,259,179,319,BLACK);//检验触摸区域
				}
				LCD_Fill(119,259,179,319,WHITE);

				Pen_Int_Set(1);//开启中断

				return 13;
			}
			else if(Pen_Point.X0>179&&Pen_Point.X0<239&&Pen_Point.Y0>259&&Pen_Point.Y0<319)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(179,259,239,319,BLACK);//检验触摸区域
				}
				LCD_Fill(179,259,239,319,WHITE);

				Pen_Int_Set(1);//开启中断

				return 14;
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

//键值处理
void TOUCH_GUI_DISP_chongzhi(void) 
{
	u8 key;
// 	u8 i=0;
	u8 num=0;
	
	u8 ii=0;
	u8 a=0;
	double temp_chongzhi=0;//充值金额
	
	length=0;
	input[0]=0;input[1]=0;input[2]=0;input[3]=0;input[4]=0;

// 	Touch_Init();	 //初始化 
	LCD_Clear(WHITE);//清屏

	GUI_DISP_chongzhi(); 	 //操作界面

	while(1)
	{
		key=TOUCH_DISP_chongzhi();	 //获取触摸键值
		
		switch(key)			     				 //相应键值的处理
		{
			case 0:		GUI_DISP_chongzhi();   				 //没有触摸按键按下，一直显示操作界面
								break;

			case 1:		TOUCH_GUI_DISP_MENU(); 	       //返回菜单栏
								break;

			case 2:		InitAlldata();								 //初始化所有读卡相关数据的设置
			
								temp_chongzhi=temp_chongzhi+input[4]/10.0;//计算整数部分和小数部分的总和
			
								temp_money=temp_chongzhi;//存放在全局变量中
						
								TOUCH_GUI_DISP_chongzhi0(); 	 //确定
								break;

			case 3:		if(ii>=4)	break;//第一个数字不能是0，充值金额不能超过4位数
								else if(a==1)//已按小数点
								{
									input[4]=0;
									ii=4;
									num++;
									LCD_ShowChar(10+8*num,50,'0',16,0);		 //0
									num++;
									LCD_ShowChar(10+8*num,50,'0',16,0);		 //0
									break;
								}
								
								else if(ii==0)	break;//第一个数字不能是0，充值金额不能超过4位数
								
								else
								{
									num++;
									input[ii]=0;
									ii++;
									LCD_ShowChar(10+8*num,50,'0',16,0);		 //0 
									break;
								}

			case 4:		if(ii>=4)	break;//充值金额不能超过4位数
								else if(a==1)//已按小数点
								{
									input[4]=1;
									ii=4;
									num++;
									LCD_ShowChar(10+8*num,50,'1',16,0);		 //1
									num++;
									LCD_ShowChar(10+8*num,50,'0',16,0);		 //0
									break;
								}
								else
								{
									num++;
									input[ii]=1;
									ii++;
									LCD_ShowChar(10+8*num,50,'1',16,0);		 //1
									break;
								}

			case 5:		if(ii>=4)	break;//充值金额不能超过4位数
								else if(a==1)//已按小数点
								{
									input[4]=2;
									ii=4;
									num++;
									LCD_ShowChar(10+8*num,50,'2',16,0);		 //2
									num++;
									LCD_ShowChar(10+8*num,50,'0',16,0);		 //0
									break;
								}
								else
								{
									num++;
									input[ii]=2;
									ii++;
									LCD_ShowChar(10+8*num,50,'2',16,0);		 //2
									break;
								}

			case 6:		num=0;
								ii=0;
								a=0;
								input[0]=0;
								input[1]=0;
								input[2]=0;
								input[3]=0;
								input[4]=0;
								length=0;
								temp_chongzhi=0;//充值金额
								
								LCD_Fill(0,40,239,78,WHITE);			   		 //重输
								break;

			case 7:		if(ii>=4)	break;//充值金额不能超过4位数
								else if(a==1)//已按小数点
								{
									input[4]=3;
									ii=4;
									num++;
									LCD_ShowChar(10+8*num,50,'3',16,0);		 //3
									num++;
									LCD_ShowChar(10+8*num,50,'0',16,0);		 //0
									break;
								}
								else
								{
									num++;
									input[ii]=3;
									ii++;
									LCD_ShowChar(10+8*num,50,'3',16,0);		 //3
									break;
								}

			case 8:		if(ii>=4)	break;//充值金额不能超过4位数
								else if(a==1)//已按小数点
								{
									input[4]=4;
									ii=4;
									num++;
									LCD_ShowChar(10+8*num,50,'4',16,0);		 //4
									num++;
									LCD_ShowChar(10+8*num,50,'0',16,0);		 //0
									break;
								}
								else
								{
									num++;
									input[ii]=4;
									ii++;
									LCD_ShowChar(10+8*num,50,'4',16,0);		 //4
									break;
								}

			case 9:		if(ii>=4)	break;//充值金额不能超过4位数
								else if(a==1)//已按小数点
								{
									input[4]=5;
									ii=4;
									num++;
									LCD_ShowChar(10+8*num,50,'5',16,0);		 //5
									num++;
									LCD_ShowChar(10+8*num,50,'0',16,0);		 //0
									break;
								}
								else
								{
									num++;
									input[ii]=5;
									ii++;
									LCD_ShowChar(10+8*num,50,'5',16,0);		 //5
									break;
								}

			case 10:	if(ii>=4)	break;//充值金额不能超过4位数
								else if(a==1)//已按小数点
								{
									input[4]=6;
									ii=4;
									num++;
									LCD_ShowChar(10+8*num,50,'6',16,0);		 //6
									num++;
									LCD_ShowChar(10+8*num,50,'0',16,0);		 //0
									break;
								}
								else
								{
									num++;
									input[ii]=6;
									ii++;
									LCD_ShowChar(10+8*num,50,'6',16,0);		 //6
									break;
								}

			case 11:	if(ii>=4)	break;//充值金额不能超过4位数
								else if(a==1)//已按小数点
								{
									input[4]=7;
									ii=4;
									num++;
									LCD_ShowChar(10+8*num,50,'7',16,0);		 //7
									num++;
									LCD_ShowChar(10+8*num,50,'0',16,0);		 //0
									break;
								}
								else
								{
									num++;
									input[ii]=7;
									ii++;
									LCD_ShowChar(10+8*num,50,'7',16,0);		 //7
									break;
								}

			case 12:	if(ii>=4)	break;//充值金额不能超过4位数
								else if(a==1)//已按小数点
								{
									input[4]=8;
									ii=4;
									num++;
									LCD_ShowChar(10+8*num,50,'8',16,0);		 //8
									num++;
									LCD_ShowChar(10+8*num,50,'0',16,0);		 //0
									break;
								}
								else
								{
									num++;
									input[ii]=8;
									ii++;
									LCD_ShowChar(10+8*num,50,'8',16,0);		 //8
									break;
								}

			case 13:	if(ii>=4)	break;//充值金额不能超过4位数
								else if(a==1)//已按小数点
								{
									input[4]=9;
									ii=4;
									num++;
									LCD_ShowChar(10+8*num,50,'9',16,0);		 //9
									num++;
									LCD_ShowChar(10+8*num,50,'0',16,0);		 //0
									break;
								}
								else
								{
									num++;
									input[ii]=9;
									ii++;
									LCD_ShowChar(10+8*num,50,'9',16,0);		 //9
									break;
								}

			case 14:	if(a==1) break;//第二次按小数点
								else
								{
									num++;	
								
									for(a=0;a<ii;a++)
									{temp_chongzhi=temp_chongzhi+input[a]*Mult10(ii-a-1);}//计算整数部分
									a=1;
									length=ii;
									ii=0;
									
									LCD_ShowChar(10+8*num,50,'.',16,0);	     //.	
									break;
								}


			default:	break;
		}


		delay_ms(10);//每过10ms查询一次触摸屏

// 		//LED闪烁指示程序正在运行,延时时间 = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}

//充值金额
void GUI_DISP_chongzhi0(void)      
{
	u8 i=0;
	
	POINT_COLOR=BLUE; 
	Show_Str(40,10,"触摸任意点返回菜单栏",16,0);
	Show_Str(90,10+50,"充值金额",16,0);
	Show_Str(100,120+30,"（元）",16,0);
	Show_Str(100,50+120+30,"请放卡",16,0);

	
	//显示充值金额
	POINT_COLOR=RED; 
	if(length == 0)	LCD_ShowNum(90-8,100,0,1,16);
	else
		for(i=0;i<length;i++)
			LCD_ShowNum(90+8*i,100,input[i],1,16);			//整数
	LCD_ShowChar(90+8*length,100,'.',16,0);	     		//.	
	LCD_ShowNum(90+8*(length+1),100,input[4],1,16); //小数
	LCD_ShowNum(90+8*(length+2),100,0,1,16); 				//小数
	
}

//键值处理
void TOUCH_GUI_DISP_chongzhi0(void)		
{
	u8 key;
// 	u8 i=0;
	u8 ii=0;
	u8 j=0;
	u8 jj=0;
	u8 flag_exist=0;
	u8 locked=0;

// 	Touch_Init();	 //初始化 
	LCD_Clear(WHITE);//清屏

	GUI_DISP_chongzhi0(); 	 //操作界面

	while(1)
	{
		key=TOUCH_all();	     //获取触摸键值
		
		switch(key)			     				 //相应键值的处理
		{
			case 0:		GUI_DISP_chongzhi0();   				 //没有触摸按键按下，一直显示操作界面
								break;

			case 1:		InitAlldata();									 //描  述  :  初始化所有读卡相关数据的设置
								TOUCH_GUI_DISP_MENU(); 	         //返回菜单栏
								break;


			default:	break;
		}
		
		
		
		if(flag_com==0)//如果没有读到卡就一直在扫卡
		{
			Read_cardID(); //读卡号
			Read_overage();//读卡内信息
		}
		else //已经读到卡
		{
			AT24CXX_Read(0,&ii,1);		 //把第一个字节的数读出来（看看已存储多少张卡）
						
			for(j=0; j<ii; j++)				 //循环读卡号
			{
				AT24CXX_Read(1+j*11,datatemp,4);
				
				for(jj=0;jj<4;jj++)
				{
					if(cardID[jj] != datatemp[jj])
					{
						flag_exist=0;		
						goto L;				 //只要存在一个数不一样就跳出此循环
					}						
					else flag_exist=1;
				}
				
				L:
				if(flag_exist == 1)//存在此卡号，计算余额，写入卡内
				{
					temp_money=temp_money+Read_overage();//充值金额+卡内余额
					write_overage(temp_money); //写卡内余额（存放在WriteData[]数组中）	
							
					TOUCH_GUI_DISP_chongzhi1();//显示充值结果  
				}
			}
			
			//如果不存在此卡号
			if(ii < 20)//AT24C02最多可以存20张卡的卡号和密码
			{
				ii++;//加一张卡
				AT24CXX_Write(0,&ii,1);//写ii到第一个字节的地址
				
				

				AT24CXX_Write(1+(ii-1)*11,cardID,4);//写卡号（4个字节）
			
				
				locked=1;
				AT24CXX_Write((ii-1)*11+5,&locked,1);//解锁：写1到地址(ii-1)*11+5
				locked=0;
			}
			else TOUCH_GUI_DISP_chongzhi3();//充值失败	
			
		}	
	
		
// 		if(flag_com==0)//如果没有读到卡就一直在扫卡
// 		{
// 			command_choose(0xa0);		
// 			RC522_work();					//描  述  :  每进入两次定时器中断（即50ms）则对操作类型重新选择（判断）
// 		}
// 		else TOUCH_GUI_DISP_chongzhi1();//显示充值结果  
		
		
		
		
		
		delay_ms(10);//每过10ms查询一次触摸屏

// 		//LED闪烁指示程序正在运行,延时时间 = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}

//成功
void GUI_DISP_chongzhi1(void)      
{
	u8 ii=0;
	u8 flag=0;
	
	POINT_COLOR=BLUE; 
	Show_Str(40,10,"触摸任意点返回菜单栏",16,0);
	Show_Str(80,130,"充值成功！",16,0);
	
	
	
	Show_Str(10,220,"卡内余额（元）：",16,0);
	
// 	for(ii=16;ii>1;ii--)//注意不能for(ii=15;ii>=0;ii--)，因为（u8）ii递减到0的时候，再递减也是0
// 		LCD_ShowNum(239-ii*8,220,WriteData[ii-1],1,16);//显示充值进去的16个数据
	
	LCD_ShowNum(239-8,220,0,1,16);					 		//0
	LCD_ShowNum(239-8*2,220,WriteData[0],1,16); //角
	LCD_ShowChar(239-8*3,220,'.',16,0);	     		//.	
	
	if(WriteData[1] == 0)
			LCD_ShowNum(239-8*4,220,0,1,16);				//0
	
  for(ii=16;ii>1;ii--)//注意不能for(ii=15;ii>=0;ii--)，因为（u8）ii递减到0的时候，再递减也是0
	{
		if(WriteData[ii-1] != 0)
		{
			flag=1;//最高位不为零的标志				
		}
		
		if(flag)
			LCD_ShowNum(239-ii*8-8*2,220,WriteData[ii-1],1,16);//显示读到的16个数据
	}
	
	
	
	//显示已存储多少张卡
	AT24CXX_Read(0,&ii,1);		 		//把第一个字节的数读出来（看看已存储多少张卡）
	POINT_COLOR=RED; 
	Show_Str(50,70,"已激活卡的数目：",16,0);
	LCD_ShowNum(180,70,ii,1,16); //显示ii（卡数）
	ii=0;

}

//键值处理
void TOUCH_GUI_DISP_chongzhi1(void)		
{
	u8 key;
// 	u8 i=0;

// 	Touch_Init();	 //初始化 
	LCD_Clear(WHITE);//清屏

	GUI_DISP_chongzhi1(); 	 //操作界面

	while(1)
	{
		key=TOUCH_all();	   //获取触摸键值
		
		switch(key)			     				 //相应键值的处理
		{
			case 0:		GUI_DISP_chongzhi1();   				 //没有触摸按键按下，一直显示操作界面
								break;

			case 1:		InitAlldata();									 //描  述  :  初始化所有读卡相关数据的设置
								TOUCH_GUI_DISP_MENU(); 	         //返回菜单栏
								break;


			default:	break;
		}
		
		
		delay_ms(10);//每过10ms查询一次触摸屏

// 		//LED闪烁指示程序正在运行,延时时间 = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}

//失败
void GUI_DISP_chongzhi2(void)     
{
	POINT_COLOR=BLUE; 
	Show_Str(40,10,"触摸任意点返回菜单栏",16,0);
	Show_Str(80,130,"充值失败！",16,0);
	Show_Str(10,200,"卡内余额（元）：",16,0);
}

//键值处理
void TOUCH_GUI_DISP_chongzhi2(void)		
{
	u8 key;
// 	u8 i=0;

// 	Touch_Init();	 //初始化 
	LCD_Clear(WHITE);//清屏

	GUI_DISP_chongzhi2(); 	 //操作界面

	while(1)
	{
		key=TOUCH_all();	   //获取触摸键值
		
		switch(key)			     				 //相应键值的处理
		{
			case 0:		GUI_DISP_chongzhi2();   				 //没有触摸按键按下，一直显示操作界面
								break;

			case 1:		InitAlldata();									 //描  述  :  初始化所有读卡相关数据的设置
								TOUCH_GUI_DISP_MENU(); 	         //返回菜单栏
								break;


			default:	break;
		}

		
		delay_ms(10);//每过10ms查询一次触摸屏

// 		//LED闪烁指示程序正在运行,延时时间 = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}

//失败
void GUI_DISP_chongzhi3(void)     
{
	POINT_COLOR=BLUE; 
	Show_Str(40,10,"触摸任意点返回菜单栏",16,0);
	Show_Str(70,130,"已开通20张卡",16,0);
	Show_Str(80,130,"充值失败！",16,0);
}

//键值处理
void TOUCH_GUI_DISP_chongzhi3(void)		
{
	u8 key;
// 	u8 i=0;

// 	Touch_Init();	 //初始化 
	LCD_Clear(WHITE);//清屏

	GUI_DISP_chongzhi3(); 	 //操作界面

	while(1)
	{
		key=TOUCH_all();	   //获取触摸键值
		
		switch(key)			     				 //相应键值的处理
		{
			case 0:		GUI_DISP_chongzhi3();   				 //没有触摸按键按下，一直显示操作界面
								break;

			case 1:		InitAlldata();									 //描  述  :  初始化所有读卡相关数据的设置
								TOUCH_GUI_DISP_MENU(); 	         //返回菜单栏
								break;


			default:	break;
		}

		
		delay_ms(10);//每过10ms查询一次触摸屏

// 		//LED闪烁指示程序正在运行,延时时间 = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}













/***********************************
        消费显示触摸界面
***********************************/
void GUI_DISP_xiaofei(void)      
{
	POINT_COLOR=BLACK; 
	LCD_DrawLine(0, 39, 239, 39);					//横
	LCD_DrawLine(0, 79, 239, 79);					//横
	LCD_DrawLine(0, 79+60, 239, 79+60);		//横
	LCD_DrawLine(0, 79+120, 239, 79+120);	//横
	LCD_DrawLine(0, 79+180, 239, 79+180);	//横
	LCD_DrawLine(59, 79+60, 59, 319);			//竖
	LCD_DrawLine(119, 79, 119, 319);			//竖
	LCD_DrawLine(179, 79+60, 179, 319);		//竖
	
	POINT_COLOR=BLUE; 
	Show_Str(60,10,"消费/单位（元）",16,0);
	Show_Str(20,10+40+60-5,"返回菜单栏",16,0);
	Show_Str(120+45,10+40+60-5,"确定",16,0);
	Show_Str(180+10+5,10+40+60+60-5,"重输",16,0);
	
	POINT_COLOR=RED;  
	LCD_ShowNum(26,162,0,1,16);
	LCD_ShowNum(86,162,1,1,16);
	LCD_ShowNum(146,162,2,1,16);
 
	LCD_ShowNum(26,222,3,1,16);
	LCD_ShowNum(86,222,4,1,16);
	LCD_ShowNum(146,222,5,1,16);
	LCD_ShowNum(206,222,6,1,16);
	
	LCD_ShowNum(26,282,7,1,16);
	LCD_ShowNum(86,282,8,1,16);
	LCD_ShowNum(146,282,9,1,16);
	LCD_ShowChar(206,282,'.',16,0);
}

//键值返回
u8 TOUCH_DISP_xiaofei(void)			 		
{
	//扫描触摸屏
	if(Pen_Point.Key_Sta==Key_Down)//触摸屏被按下
	{
			Pen_Int_Set(0);//关闭中断

			Convert_Pos();//转换结果，根据触摸屏的校准参数来决定转换后的结果,保存在X0,Y0中
			Pen_Point.Key_Sta=Key_Up;

			if(Pen_Point.X0>0&&Pen_Point.X0<119&&Pen_Point.Y0>79&&Pen_Point.Y0<139)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(0,79,119,139,BLACK);//检验触摸区域
				}
				LCD_Fill(0,79,119,139,WHITE);

				Pen_Int_Set(1);//开启中断

				return 1;
			}
			else if(Pen_Point.X0>119&&Pen_Point.X0<239&&Pen_Point.Y0>79&&Pen_Point.Y0<139) 
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(119,79,239,139,BLACK);//检验触摸区域
				}
				LCD_Fill(119,79,239,139,WHITE);

				Pen_Int_Set(1);//开启中断

				return 2;
			}
			
			
			
			else if(Pen_Point.X0>0&&Pen_Point.X0<59&&Pen_Point.Y0>139&&Pen_Point.Y0<199)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(0,139,59,199,BLACK);//检验触摸区域
				}
				LCD_Fill(0,139,59,199,WHITE);

				Pen_Int_Set(1);//开启中断

				return 3;
			}
			else if(Pen_Point.X0>59&&Pen_Point.X0<119&&Pen_Point.Y0>139&&Pen_Point.Y0<199)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(59,139,119,199,BLACK);//检验触摸区域
				}
				LCD_Fill(59,139,119,199,WHITE);

				Pen_Int_Set(1);//开启中断

				return 4;
			}
			else if(Pen_Point.X0>119&&Pen_Point.X0<179&&Pen_Point.Y0>139&&Pen_Point.Y0<199)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(119,139,179,199,BLACK);//检验触摸区域
				}
				LCD_Fill(119,139,179,199,WHITE);

				Pen_Int_Set(1);//开启中断

				return 5;
			}
			else if(Pen_Point.X0>179&&Pen_Point.X0<239&&Pen_Point.Y0>139&&Pen_Point.Y0<199)
			{  	
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(179,139,239,199,BLACK);//检验触摸区域
				}
				LCD_Fill(179,139,239,199,WHITE);

				Pen_Int_Set(1);//开启中断

				return 6;
			}

			
			else if(Pen_Point.X0>0&&Pen_Point.X0<59&&Pen_Point.Y0>199&&Pen_Point.Y0<259)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(0,199,59,259,BLACK);//检验触摸区域
				}
				LCD_Fill(0,199,59,259,WHITE);

				Pen_Int_Set(1);//开启中断

				return 7;
			}
			else if(Pen_Point.X0>59&&Pen_Point.X0<119&&Pen_Point.Y0>199&&Pen_Point.Y0<259)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(59,199,119,259,BLACK);//检验触摸区域
				}
				LCD_Fill(59,199,119,259,WHITE);

				Pen_Int_Set(1);//开启中断

				return 8;
			}
			else if(Pen_Point.X0>119&&Pen_Point.X0<179&&Pen_Point.Y0>199&&Pen_Point.Y0<259)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(119,199,179,259,BLACK);//检验触摸区域
				}
				LCD_Fill(119,199,179,259,WHITE);

				Pen_Int_Set(1);//开启中断

				return 9;
			}
			else if(Pen_Point.X0>179&&Pen_Point.X0<239&&Pen_Point.Y0>199&&Pen_Point.Y0<259)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(179,199,239,259,BLACK);//检验触摸区域
				}
				LCD_Fill(179,199,239,259,WHITE);

				Pen_Int_Set(1);//开启中断

				return 10;
			}

			
			else if(Pen_Point.X0>0&&Pen_Point.X0<59&&Pen_Point.Y0>259&&Pen_Point.Y0<319)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(0,259,59,319,BLACK);//检验触摸区域
				}
				LCD_Fill(0,259,59,319,WHITE);

				Pen_Int_Set(1);//开启中断

				return 11;
			}
			else if(Pen_Point.X0>59&&Pen_Point.X0<119&&Pen_Point.Y0>259&&Pen_Point.Y0<319)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(59,259,119,319,BLACK);//检验触摸区域
				}
				LCD_Fill(59,259,119,319,WHITE);

				Pen_Int_Set(1);//开启中断

				return 12;
			}
			else if(Pen_Point.X0>119&&Pen_Point.X0<179&&Pen_Point.Y0>259&&Pen_Point.Y0<319)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(119,259,179,319,BLACK);//检验触摸区域
				}
				LCD_Fill(119,259,179,319,WHITE);

				Pen_Int_Set(1);//开启中断

				return 13;
			}
			else if(Pen_Point.X0>179&&Pen_Point.X0<239&&Pen_Point.Y0>259&&Pen_Point.Y0<319)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(179,259,239,319,BLACK);//检验触摸区域
				}
				LCD_Fill(179,259,239,319,WHITE);

				Pen_Int_Set(1);//开启中断

				return 14;
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

//键值处理
void TOUCH_GUI_DISP_xiaofei(void)		
{
	u8 key;
// 	u8 i=0;
	u8 num=0;

	u8 ii=0;
	u8 a=0;
	double temp_xiaofei=0;//消费金额
	
	length=0;
	input[0]=0;input[1]=0;input[2]=0;input[3]=0;input[4]=0;
	
// 	Touch_Init();	 //初始化 
	LCD_Clear(WHITE);//清屏

	GUI_DISP_xiaofei(); 	 //操作界面

	while(1)
	{
		key=TOUCH_DISP_xiaofei();	   //获取触摸键值
		
		switch(key)			     				 //相应键值的处理
		{
			case 0:		GUI_DISP_xiaofei();   				   //没有触摸按键按下，一直显示操作界面
								break;

			case 1:		TOUCH_GUI_DISP_MENU(); 	         //返回菜单栏
								break;

			case 2:		InitAlldata();								   //初始化所有读卡相关数据的设置
				
								temp_xiaofei=temp_xiaofei+input[4]/10.0;//计算整数部分和小数部分的总和
								temp_money=temp_xiaofei;//存放在全局变量中

								TOUCH_GUI_DISP_xiaofei0(); 		   //确定
								break;

			case 3:		if(ii>=4)	break;//第一个数字不能是0，消费金额不能超过4位数
								else if(a==1)//已按小数点
								{
									input[4]=0;
									ii=4;
									num++;
									LCD_ShowChar(10+8*num,50,'0',16,0);		 //0
									num++;
									LCD_ShowChar(10+8*num,50,'0',16,0);		 //0
									break;
								}
								
								else if(ii==0)	break;//第一个数字不能是0，消费金额不能超过4位数
								
								else
								{
									num++;
									input[ii]=0;
									ii++;
									LCD_ShowChar(10+8*num,50,'0',16,0);		 //0 
									break;
								}

			case 4:		if(ii>=4)	break;//消费金额不能超过4位数
								else if(a==1)//已按小数点
								{
									input[4]=1;
									ii=4;
									num++;
									LCD_ShowChar(10+8*num,50,'1',16,0);		 //1
									num++;
									LCD_ShowChar(10+8*num,50,'0',16,0);		 //0
									break;
								}
								else
								{
									num++;
									input[ii]=1;
									ii++;
									LCD_ShowChar(10+8*num,50,'1',16,0);		 //1
									break;
								}

			case 5:		if(ii>=4)	break;//消费金额不能超过4位数
								else if(a==1)//已按小数点
								{
									input[4]=2;
									ii=4;
									num++;
									LCD_ShowChar(10+8*num,50,'2',16,0);		 //2
									num++;
									LCD_ShowChar(10+8*num,50,'0',16,0);		 //0
									break;
								}
								else
								{
									num++;
									input[ii]=2;
									ii++;
									LCD_ShowChar(10+8*num,50,'2',16,0);		 //2
									break;
								}

			case 6:		num=0;
								ii=0;
								a=0;
								input[0]=0;
								input[1]=0;
								input[2]=0;
								input[3]=0;
								input[4]=0;
								length=0;
								temp_xiaofei=0;//充值金额
								
								LCD_Fill(0,40,239,78,WHITE);			   		 //重输
								break;

			case 7:		if(ii>=4)	break;//消费金额不能超过4位数
								else if(a==1)//已按小数点
								{
									input[4]=3;
									ii=4;
									num++;
									LCD_ShowChar(10+8*num,50,'3',16,0);		 //3
									num++;
									LCD_ShowChar(10+8*num,50,'0',16,0);		 //0
									break;
								}
								else
								{
									num++;
									input[ii]=3;
									ii++;
									LCD_ShowChar(10+8*num,50,'3',16,0);		 //3
									break;
								}

			case 8:		if(ii>=4)	break;//消费金额不能超过4位数
								else if(a==1)//已按小数点
								{
									input[4]=4;
									ii=4;
									num++;
									LCD_ShowChar(10+8*num,50,'4',16,0);		 //4
									num++;
									LCD_ShowChar(10+8*num,50,'0',16,0);		 //0
									break;
								}
								else
								{
									num++;
									input[ii]=4;
									ii++;
									LCD_ShowChar(10+8*num,50,'4',16,0);		 //4
									break;
								}

			case 9:		if(ii>=4)	break;//消费金额不能超过4位数
								else if(a==1)//已按小数点
								{
									input[4]=5;
									ii=4;
									num++;
									LCD_ShowChar(10+8*num,50,'5',16,0);		 //5
									num++;
									LCD_ShowChar(10+8*num,50,'0',16,0);		 //0
									break;
								}
								else
								{
									num++;
									input[ii]=5;
									ii++;
									LCD_ShowChar(10+8*num,50,'5',16,0);		 //5
									break;
								}

			case 10:	if(ii>=4)	break;//消费金额不能超过4位数
								else if(a==1)//已按小数点
								{
									input[4]=6;
									ii=4;
									num++;
									LCD_ShowChar(10+8*num,50,'6',16,0);		 //6
									num++;
									LCD_ShowChar(10+8*num,50,'0',16,0);		 //0
									break;
								}
								else
								{
									num++;
									input[ii]=6;
									ii++;
									LCD_ShowChar(10+8*num,50,'6',16,0);		 //6
									break;
								}

			case 11:	if(ii>=4)	break;//消费金额不能超过4位数
								else if(a==1)//已按小数点
								{
									input[4]=7;
									ii=4;
									num++;
									LCD_ShowChar(10+8*num,50,'7',16,0);		 //7
									num++;
									LCD_ShowChar(10+8*num,50,'0',16,0);		 //0
									break;
								}
								else
								{
									num++;
									input[ii]=7;
									ii++;
									LCD_ShowChar(10+8*num,50,'7',16,0);		 //7
									break;
								}

			case 12:	if(ii>=4)	break;//消费金额不能超过4位数
								else if(a==1)//已按小数点
								{
									input[4]=8;
									ii=4;
									num++;
									LCD_ShowChar(10+8*num,50,'8',16,0);		 //8
									num++;
									LCD_ShowChar(10+8*num,50,'0',16,0);		 //0
									break;
								}
								else
								{
									num++;
									input[ii]=8;
									ii++;
									LCD_ShowChar(10+8*num,50,'8',16,0);		 //8
									break;
								}

			case 13:	if(ii>=4)	break;//消费金额不能超过4位数
								else if(a==1)//已按小数点
								{
									input[4]=9;
									ii=4;
									num++;
									LCD_ShowChar(10+8*num,50,'9',16,0);		 //9
									num++;
									LCD_ShowChar(10+8*num,50,'0',16,0);		 //0
									break;
								}
								else
								{
									num++;
									input[ii]=9;
									ii++;
									LCD_ShowChar(10+8*num,50,'9',16,0);		 //9
									break;
								}

			case 14:	if(a==1) break;//第二次按小数点
								else
								{
									num++;	
								
									for(a=0;a<ii;a++)
									{temp_xiaofei=temp_xiaofei+input[a]*Mult10(ii-a-1);}//计算整数部分
									a=1;
									length=ii;
									ii=0;
									
									LCD_ShowChar(10+8*num,50,'.',16,0);	     //.	
									break;
								}


			default:	break;
		}



		delay_ms(10);//每过10ms查询一次触摸屏

// 		//LED闪烁指示程序正在运行,延时时间 = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}

//消费金额
void GUI_DISP_xiaofei0(void)    
{
	u8 i=0;
	
	POINT_COLOR=BLUE; 
	Show_Str(40,10,"触摸任意点返回菜单栏",16,0);
	Show_Str(90,10+50,"消费金额",16,0);
	Show_Str(100,120+30,"（元）",16,0);
	Show_Str(100,50+120+30,"请放卡",16,0);
	
	
	//显示消费金额
	POINT_COLOR=RED; 
	if(length == 0)	LCD_ShowNum(90-8,100,0,1,16);
	else
		for(i=0;i<length;i++)
			LCD_ShowNum(90+8*i,100,input[i],1,16);			//整数
	LCD_ShowChar(90+8*length,100,'.',16,0);	     		//.	
	LCD_ShowNum(90+8*(length+1),100,input[4],1,16); //小数
	LCD_ShowNum(90+8*(length+2),100,0,1,16); 				//小数	
}

//键值处理
void TOUCH_GUI_DISP_xiaofei0(void)		
{
	u8 key;
// 	u8 i=0;
	u8 ii=0;
	u8 j=0;
	u8 jj=0;
	u8 flag_exist=0;
	u8 locked=0;

// 	Touch_Init();	 //初始化 
	LCD_Clear(WHITE);//清屏

	GUI_DISP_xiaofei0(); 	 //操作界面

	while(1)
	{
		key=TOUCH_all();	   //获取触摸键值
		
		switch(key)			     				 //相应键值的处理
		{
			case 0:		GUI_DISP_xiaofei0();   				   //没有触摸按键按下，一直显示操作界面
								break;

			case 1:		InitAlldata();									 //描  述  :  初始化所有读卡相关数据的设置
								TOUCH_GUI_DISP_MENU(); 	         //返回菜单栏
								break;


			default:	break;
		}

				
		if(flag_com==0)//如果没有读到卡就一直在扫卡
		{
			Read_cardID(); //读卡号
			Read_overage();//读卡内信息
		}
		else //已经读到卡，计算余额，写入卡内
		{
			AT24CXX_Read(0,&ii,1);		 //把第一个字节的数读出来（看看已存储多少张卡）		
						
			for(j=0; j<ii; j++)				 //循环读卡号
			{
				AT24CXX_Read(1+j*11,datatemp,4);
				
				for(jj=0;jj<4;jj++)
				{
					if(cardID[jj] != datatemp[jj])
					{
						flag_exist=0;		
						goto L;				 //只要存在一个数不一样就跳出此循环
					}						
					else flag_exist=1;
				}
				
				L:
				if(flag_exist == 1)//存在此卡号，计算余额，写入卡内
				{
					AT24CXX_Read(j*11+5,&locked,1);//读出卡的状态：0锁定  1解锁
					
					if(locked)//解锁
					{
						if(Read_overage() >= temp_money)
						{
							temp_money=Read_overage()-temp_money;//卡内余额-消费金额
							write_overage(temp_money);//写卡内余额（存放在WriteData[]数组中）	
								
							TOUCH_GUI_DISP_xiaofei1();//显示消费结果  
						}
						else TOUCH_GUI_DISP_xiaofei2();//消费失败！（显示余额不足）
					}
					else TOUCH_GUI_DISP_xiaofei4();	 //未解锁！（此卡已挂失）																
				}								
			}
			
			//循环读卡号，没找到此卡
			TOUCH_GUI_DISP_xiaofei3();		 			 //不存在此卡！（此卡未激活）
		}	
		
		
		
// 		if(flag_com==0)//如果没有读到卡就一直在扫卡
// 		{
// 			Read_overage();//读卡
// 		}
// 		else //已经读到卡，计算余额，写入卡内
// 		{
// 			if(Read_overage() >= temp_money)
// 			{
// 				temp_money=Read_overage()-temp_money;//卡内余额-消费金额
// 				write_overage(temp_money);//写卡内余额（存放在WriteData[]数组中）	
// 					
// 				TOUCH_GUI_DISP_xiaofei1();//显示消费结果  
// 			}
// 			else TOUCH_GUI_DISP_xiaofei2();//消费失败！

// 		}	
		

		
		delay_ms(10);//每过10ms查询一次触摸屏

// 		//LED闪烁指示程序正在运行,延时时间 = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}

//成功
void GUI_DISP_xiaofei1(void)     
{
	u8 ii=0;
	u8 flag=0;
	
	POINT_COLOR=BLUE; 
	Show_Str(40,10,"触摸任意点返回菜单栏",16,0);
	Show_Str(80,130,"消费成功！",16,0);
	
	
	
	Show_Str(10,220,"卡内余额（元）：",16,0);
	
// 	for(ii=16;ii>1;ii--)//注意不能for(ii=15;ii>=0;ii--)，因为（u8）ii递减到0的时候，再递减也是0
// 		LCD_ShowNum(239-ii*8,220,WriteData[ii-1],1,16);//显示充值进去的16个数据
	
	LCD_ShowNum(239-8,220,0,1,16);					 		//0
	LCD_ShowNum(239-8*2,220,WriteData[0],1,16); //角
	LCD_ShowChar(239-8*3,220,'.',16,0);	     		//.	
	
	if(WriteData[1] == 0)
			LCD_ShowNum(239-8*4,220,0,1,16);				//0
	
  for(ii=16;ii>1;ii--)//注意不能for(ii=15;ii>=0;ii--)，因为（u8）ii递减到0的时候，再递减也是0
	{
		if(WriteData[ii-1] != 0)
		{
			flag=1;//最高位不为零的标志				
		}
		
		if(flag)
			LCD_ShowNum(239-ii*8-8*2,220,WriteData[ii-1],1,16);//显示读到的16个数据
	}	
	
}

//键值处理
void TOUCH_GUI_DISP_xiaofei1(void)		
{
	u8 key;
// 	u8 i=0;

// 	Touch_Init();	 //初始化 
	LCD_Clear(WHITE);//清屏

	GUI_DISP_xiaofei1(); 	 //操作界面

	while(1)
	{
		key=TOUCH_all();	   //获取触摸键值
		
		switch(key)			     				 //相应键值的处理
		{
			case 0:		GUI_DISP_xiaofei1();   				 //没有触摸按键按下，一直显示操作界面
								break;

			case 1:		InitAlldata();									 //描  述  :  初始化所有读卡相关数据的设置
								TOUCH_GUI_DISP_MENU(); 	         //返回菜单栏
								break;


			default:	break;
		}

		
		delay_ms(10);//每过10ms查询一次触摸屏

// 		//LED闪烁指示程序正在运行,延时时间 = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}

//失败（显示余额不足）
void GUI_DISP_xiaofei2(void)    
{
	u8 ii=0;
	u8 flag=0;
	
	POINT_COLOR=BLUE; 
	Show_Str(40,10,"触摸任意点返回菜单栏",16,0);
	Show_Str(70,70,"卡内余额不足",16,0);
	Show_Str(80,130,"消费失败！",16,0);
	
	
	
	
	Show_Str(10,220,"卡内余额（元）：",16,0);
		
// 	for(ii=16;ii>1;ii--)//注意不能for(ii=15;ii>=0;ii--)，因为（u8）ii递减到0的时候，再递减也是0
// 		LCD_ShowNum(239-ii*8,220,Read_Data[ii-1],1,16);//显示充值进去的16个数据
	
	LCD_ShowNum(239-8,220,0,1,16);					 		//0
	LCD_ShowNum(239-8*2,220,Read_Data[0],1,16); //角
	LCD_ShowChar(239-8*3,220,'.',16,0);	     		//.	
	
	if(Read_Data[1] == 0)
			LCD_ShowNum(239-8*4,220,0,1,16);				//0
	
  for(ii=16;ii>1;ii--)//注意不能for(ii=15;ii>=0;ii--)，因为（u8）ii递减到0的时候，再递减也是0
	{
		if(Read_Data[ii-1] != 0)
		{
			flag=1;//最高位不为零的标志				
		}
		
		if(flag)
			LCD_ShowNum(239-ii*8-8*2,220,Read_Data[ii-1],1,16);//显示读到的16个数据
	}	
}

//键值处理
void TOUCH_GUI_DISP_xiaofei2(void)		
{
	u8 key;
// 	u8 i=0;

// 	Touch_Init();	 //初始化 
	LCD_Clear(WHITE);//清屏

	GUI_DISP_xiaofei2(); 	 //操作界面

	while(1)
	{
		key=TOUCH_all();	   //获取触摸键值
		
		switch(key)			     				 //相应键值的处理
		{
			case 0:		GUI_DISP_xiaofei2();   				   //没有触摸按键按下，一直显示操作界面
								break;

			case 1:		InitAlldata();									 //描  述  :  初始化所有读卡相关数据的设置
								TOUCH_GUI_DISP_MENU(); 	         //返回菜单栏
								break;


			default:	break;
		}

		
		delay_ms(10);//每过10ms查询一次触摸屏

// 		//LED闪烁指示程序正在运行,延时时间 = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}

//不存在此卡！（此卡未激活）
void GUI_DISP_xiaofei3(void)
{
	POINT_COLOR=BLUE; 
	Show_Str(40,10,"触摸任意点返回菜单栏",16,0);
	Show_Str(70,70,"此卡未激活",16,0);
	Show_Str(80,130,"消费失败！",16,0);
}

//键值处理
void TOUCH_GUI_DISP_xiaofei3(void)		
{
	u8 key;
// 	u8 i=0;

// 	Touch_Init();	 //初始化 
	LCD_Clear(WHITE);//清屏

	GUI_DISP_xiaofei3(); 	 //操作界面

	while(1)
	{
		key=TOUCH_all();	   //获取触摸键值
		
		switch(key)			     				 //相应键值的处理
		{
			case 0:		GUI_DISP_xiaofei3();   				   //没有触摸按键按下，一直显示操作界面
								break;

			case 1:		InitAlldata();									 //描  述  :  初始化所有读卡相关数据的设置
								TOUCH_GUI_DISP_MENU(); 	         //返回菜单栏
								break;


			default:	break;
		}

		
		delay_ms(10);//每过10ms查询一次触摸屏

// 		//LED闪烁指示程序正在运行,延时时间 = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}

//未解锁！（此卡已挂失）
void GUI_DISP_xiaofei4(void)
{
	POINT_COLOR=BLUE; 
	Show_Str(40,10,"触摸任意点返回菜单栏",16,0);
	Show_Str(70,70,"此卡已挂失",16,0);
	Show_Str(80,130,"消费失败！",16,0);
}

//键值处理
void TOUCH_GUI_DISP_xiaofei4(void)		
{
	u8 key;
// 	u8 i=0;

// 	Touch_Init();	 //初始化 
	LCD_Clear(WHITE);//清屏

	GUI_DISP_xiaofei4(); 	 //操作界面

	while(1)
	{
		key=TOUCH_all();	   //获取触摸键值
		
		switch(key)			     				 //相应键值的处理
		{
			case 0:		GUI_DISP_xiaofei4();   				   //没有触摸按键按下，一直显示操作界面
								break;

			case 1:		InitAlldata();									 //描  述  :  初始化所有读卡相关数据的设置
								TOUCH_GUI_DISP_MENU(); 	         //返回菜单栏
								break;


			default:	break;
		}

		
		delay_ms(10);//每过10ms查询一次触摸屏

// 		//LED闪烁指示程序正在运行,延时时间 = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}
















/***********************************
        查询显示触摸界面
***********************************/
void GUI_DISP_chaxun(void)       
{	
	POINT_COLOR=BLUE; 
	Show_Str(70,50,"查询卡内信息",16,0);
	Show_Str(100,120,"请放卡",16,0);
	Show_Str(40,50+120+30,"触摸任意点返回菜单栏",16,0);
}

//键值返回
u8 TOUCH_all(void)			 		
{
	//扫描触摸屏
	if(Pen_Point.Key_Sta==Key_Down)//触摸屏被按下
	{
			Pen_Int_Set(0);//关闭中断

			Convert_Pos();//转换结果，根据触摸屏的校准参数来决定转换后的结果,保存在X0,Y0中
			Pen_Point.Key_Sta=Key_Up;

			if(Pen_Point.X0>0&&Pen_Point.X0<239&&Pen_Point.Y0>0&&Pen_Point.Y0<319)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(0,0,239,319,BLACK);//检验触摸区域
				}
				LCD_Fill(0,0,239,319,WHITE);

				Pen_Int_Set(1);//开启中断

				return 1;
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

//键值处理
void TOUCH_GUI_DISP_chaxun(void)		
{
	u8 key;
// 	u8 i=0;

// 	Touch_Init();	 //初始化 
	LCD_Clear(WHITE);//清屏

	GUI_DISP_chaxun(); 	 //操作界面

	while(1)
	{
		key=TOUCH_all();	   //获取触摸键值
		
		switch(key)			     				 //相应键值的处理
		{
			case 0:		GUI_DISP_chaxun();   				     //没有触摸按键按下，一直显示操作界面
								break;

			case 1:		InitAlldata();									 //描  述  :  初始化所有读卡相关数据的设置
								TOUCH_GUI_DISP_MENU(); 	         //返回菜单栏
								break;


			default:	break;
		}

		
		if(flag_com==0)//如果没有读到卡就一直在扫卡
		{
			Read_cardID();//读卡号
			Read_overage();//读卡内余额
		}
		else TOUCH_GUI_DISP_chaxun0();//显示查询结果  
				
						
		
		delay_ms(10);//每过10ms查询一次触摸屏

// 		//LED闪烁指示程序正在运行,延时时间 = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}

//查询结果
void GUI_DISP_chaxun0(void)      
{
	u8 ii=0;
	u8 flag=0;
	u8 administrator_flag=0;
	
	POINT_COLOR=BLUE; 
	Show_Str(40,10,"触摸任意点返回菜单栏",16,0);
	Show_Str(90,50,"卡内信息",16,0);
	Show_Str(10,120,"姓名：***",16,0);
	Show_Str(10,150,"学号：***",16,0);
	
	
	for(ii=0;ii<4;ii++)
	{
		if(cardID[ii] != administrator[ii])
		{
			administrator_flag=0; //不是管理员卡号
			goto L2;							//只要存在一位卡号不一致
		}		
		else administrator_flag=1;
	}
	
	L2:
	if(administrator_flag)
	{	
		POINT_COLOR=RED; 
		Show_Str(10,90,"身份：管理员",16,0);
	}
	else 
	{
		POINT_COLOR=RED; 
		Show_Str(10,90,"身份：非管理员",16,0);
	}

	switch(card_status)
	{
		case 1:	//不存在此卡！（此卡未激活）
						Show_Str(150,90,"此卡未激活",16,0);
						break;
		
		case 2:	//未解锁！（此卡已挂失）	
						Show_Str(150,90,"此卡未解锁",16,0);
						break;
		
		case 3:	//已解锁
						Show_Str(150,90,"此卡已解锁",16,0);
						break;
		
		
		default:break;
	}
	
	
	
	POINT_COLOR=BLUE; 
	Show_Str(10,180,"卡号：",16,0);
	
	for(ii=0;ii<4;ii++)//显示卡号（如：将卡号0x34 0xb2 0x30 0xeb 显示成 052 178 030 235）
	{
		if(cardID[ii] >= 100)
			LCD_ShowNum(60+ii*8*3,180,cardID[ii],3,16);//显示ID（3位10进制数）
		else if((cardID[ii] >= 10) && (cardID[ii] < 100))
		{
			if(ii == 0)
			{
				LCD_ShowNum(60+(ii+1)*8,180,cardID[ii],2,16);
			}else LCD_ShowNum(60+ii*8*3+8,180,cardID[ii],2,16);
			LCD_ShowNum(60+ii*8*3,180,0,1,16);		
		}	
		else if(cardID[ii] < 10)
		{
			if(ii == 0)
			{
				LCD_ShowNum(60+(ii+2)*8,180,cardID[ii],1,16);
			}else LCD_ShowNum(60+ii*8*3+8*2,180,cardID[ii],1,16);			
			LCD_ShowNum(60+ii*8*3,180,00,2,16);
		}
	}
	
	
	
	
	Show_Str(10,220,"卡内余额（元）：",16,0);
	
	LCD_ShowNum(239-8,220,0,1,16);					 		//0
	LCD_ShowNum(239-8*2,220,Read_Data[0],1,16); //角
	LCD_ShowChar(239-8*3,220,'.',16,0);	     		//.	
	
	if(Read_Data[1] == 0)
			LCD_ShowNum(239-8*4,220,0,1,16);				//0
	
  for(ii=16;ii>1;ii--)//注意不能for(ii=15;ii>=0;ii--)，因为（u8）ii递减到0的时候，再递减也是0
	{
		if(Read_Data[ii-1] != 0)
		{
			flag=1;//最高位不为零的标志				
		}
		
		if(flag)
			LCD_ShowNum(239-ii*8-8*2,220,Read_Data[ii-1],1,16);//显示读到的16个数据
	}
}

//键值处理
void TOUCH_GUI_DISP_chaxun0(void)		
{
	u8 key;
// 	u8 i=0;
	u8 ii=0;
	u8 j=0;
	u8 jj=0;
	u8 flag_exist=0;
	u8 locked=0;
	card_status = 0;

// 	Touch_Init();	 //初始化 
	LCD_Clear(WHITE);//清屏

	GUI_DISP_chaxun0(); 	 //操作界面

	while(1)
	{
		key=TOUCH_all();	   //获取触摸键值
		
		switch(key)			     				 //相应键值的处理
		{
			case 0:		GUI_DISP_chaxun0();   				   //没有触摸按键按下，一直显示操作界面
								break;

			case 1:		InitAlldata();									 //描  述  :  初始化所有读卡相关数据的设置
								TOUCH_GUI_DISP_MENU(); 	         //返回菜单栏
								break;


			default:	break;
		}

		
		
		if(card_status == 0)
		{
			AT24CXX_Read(0,&ii,1);		 //把第一个字节的数读出来（看看已存储多少张卡）		
						
			for(j=0; j<ii; j++)				 //循环读卡号
			{
				AT24CXX_Read(1+j*11,datatemp,4);
				
				for(jj=0;jj<4;jj++)
				{
					if(cardID[jj] != datatemp[jj])
					{
						flag_exist=0;		
						goto L;				 //只要存在一个数不一样就跳出此循环
					}						
					else flag_exist=1;
				}
				
				L:
				if(flag_exist == 1)//存在此卡号，计算余额，写入卡内
				{
					AT24CXX_Read(j*11+5,&locked,1);//读出卡的状态：0锁定  1解锁
					
					if(locked)
					{
						card_status=3;		 //已解锁
						goto L3;
					}
					else 
					{
						card_status=2;	  //未解锁！（此卡已挂失）
						goto L3;
					}																
				}								
			}
			
			//循环读卡号，没找到此卡
			card_status=1;		 			 //不存在此卡！（此卡未激活）
		}
		
	
		L3:
		
			
		delay_ms(10);//每过10ms查询一次触摸屏

// 		//LED闪烁指示程序正在运行,延时时间 = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}














/***********************************
       挂失/解挂显示触摸界面
***********************************/
void GUI_DISP_guashijiegua(void) 
{
	POINT_COLOR=BLACK; 
	LCD_DrawLine(0, 39, 180, 39);					//横
	LCD_DrawLine(0, 79, 239, 79);					//横
	LCD_DrawLine(0, 79+60, 239, 79+60);		//横
	LCD_DrawLine(0, 79+120, 239, 79+120);	//横
	LCD_DrawLine(0, 79+180, 239, 79+180);	//横
	LCD_DrawLine(80, 0, 80, 79);					//竖
	LCD_DrawLine(180, 0, 180, 79);				//竖
	LCD_DrawLine(59, 79+60, 59, 319);			//竖
	LCD_DrawLine(119, 79, 119, 319);			//竖
	LCD_DrawLine(179, 79+60, 179, 319);		//竖
	
	POINT_COLOR=BLUE; 
	Show_Str(10,10,"卡号：",16,0);
	Show_Str(10,10+40,"密码：",16,0);
	Show_Str(20,10+40+60-5,"返回菜单栏",16,0);
	Show_Str(120+45,10+40+60-5,"确定",16,0);
	Show_Str(180+10+5,10+40+60+60-5,"重输",16,0);
	Show_Str(180+10+5,10+40+60+60+60-5,"解挂",16,0);
	Show_Str(200-5,10+20,"挂失",16,0);
	
	POINT_COLOR=RED;  
	LCD_ShowNum(26,162,1,1,16);
	LCD_ShowNum(86,162,2,1,16);
	LCD_ShowNum(146,162,3,1,16);
 
	LCD_ShowNum(26,222,4,1,16);
	LCD_ShowNum(86,222,5,1,16);
	LCD_ShowNum(146,222,6,1,16);
	
	LCD_ShowNum(26,282,7,1,16);
	LCD_ShowNum(86,282,8,1,16);
	LCD_ShowNum(146,282,9,1,16);
	LCD_ShowNum(206,282,0,1,16);
}

//键值返回
u8 TOUCH_DISP_guashijiegua(void)			 		
{
	//扫描触摸屏
	if(Pen_Point.Key_Sta==Key_Down)//触摸屏被按下
	{
			Pen_Int_Set(0);//关闭中断

			Convert_Pos();//转换结果，根据触摸屏的校准参数来决定转换后的结果,保存在X0,Y0中
			Pen_Point.Key_Sta=Key_Up;

			if(Pen_Point.X0>0&&Pen_Point.X0<119&&Pen_Point.Y0>79&&Pen_Point.Y0<139)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(0,79,119,139,BLACK);//检验触摸区域
				}
				LCD_Fill(0,79,119,139,WHITE);

				Pen_Int_Set(1);//开启中断

				return 1;
			}
			else if(Pen_Point.X0>119&&Pen_Point.X0<239&&Pen_Point.Y0>79&&Pen_Point.Y0<139) 
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(119,79,239,139,BLACK);//检验触摸区域
				}
				LCD_Fill(119,79,239,139,WHITE);

				Pen_Int_Set(1);//开启中断

				return 2;
			}
			
			
			
			else if(Pen_Point.X0>0&&Pen_Point.X0<59&&Pen_Point.Y0>139&&Pen_Point.Y0<199)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(0,139,59,199,BLACK);//检验触摸区域
				}
				LCD_Fill(0,139,59,199,WHITE);

				Pen_Int_Set(1);//开启中断

				return 3;
			}
			else if(Pen_Point.X0>59&&Pen_Point.X0<119&&Pen_Point.Y0>139&&Pen_Point.Y0<199)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(59,139,119,199,BLACK);//检验触摸区域
				}
				LCD_Fill(59,139,119,199,WHITE);

				Pen_Int_Set(1);//开启中断

				return 4;
			}
			else if(Pen_Point.X0>119&&Pen_Point.X0<179&&Pen_Point.Y0>139&&Pen_Point.Y0<199)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(119,139,179,199,BLACK);//检验触摸区域
				}
				LCD_Fill(119,139,179,199,WHITE);

				Pen_Int_Set(1);//开启中断

				return 5;
			}
			else if(Pen_Point.X0>179&&Pen_Point.X0<239&&Pen_Point.Y0>139&&Pen_Point.Y0<199)
			{  	
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(179,139,239,199,BLACK);//检验触摸区域
				}
				LCD_Fill(179,139,239,199,WHITE);

				Pen_Int_Set(1);//开启中断

				return 6;
			}

			
			else if(Pen_Point.X0>0&&Pen_Point.X0<59&&Pen_Point.Y0>199&&Pen_Point.Y0<259)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(0,199,59,259,BLACK);//检验触摸区域
				}
				LCD_Fill(0,199,59,259,WHITE);

				Pen_Int_Set(1);//开启中断

				return 7;
			}
			else if(Pen_Point.X0>59&&Pen_Point.X0<119&&Pen_Point.Y0>199&&Pen_Point.Y0<259)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(59,199,119,259,BLACK);//检验触摸区域
				}
				LCD_Fill(59,199,119,259,WHITE);

				Pen_Int_Set(1);//开启中断

				return 8;
			}
			else if(Pen_Point.X0>119&&Pen_Point.X0<179&&Pen_Point.Y0>199&&Pen_Point.Y0<259)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(119,199,179,259,BLACK);//检验触摸区域
				}
				LCD_Fill(119,199,179,259,WHITE);

				Pen_Int_Set(1);//开启中断

				return 9;
			}
			else if(Pen_Point.X0>179&&Pen_Point.X0<239&&Pen_Point.Y0>199&&Pen_Point.Y0<259)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(179,199,239,259,BLACK);//检验触摸区域
				}
				LCD_Fill(179,199,239,259,WHITE);

				Pen_Int_Set(1);//开启中断

				return 10;
			}

			
			else if(Pen_Point.X0>0&&Pen_Point.X0<59&&Pen_Point.Y0>259&&Pen_Point.Y0<319)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(0,259,59,319,BLACK);//检验触摸区域
				}
				LCD_Fill(0,259,59,319,WHITE);

				Pen_Int_Set(1);//开启中断

				return 11;
			}
			else if(Pen_Point.X0>59&&Pen_Point.X0<119&&Pen_Point.Y0>259&&Pen_Point.Y0<319)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(59,259,119,319,BLACK);//检验触摸区域
				}
				LCD_Fill(59,259,119,319,WHITE);

				Pen_Int_Set(1);//开启中断

				return 12;
			}
			else if(Pen_Point.X0>119&&Pen_Point.X0<179&&Pen_Point.Y0>259&&Pen_Point.Y0<319)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(119,259,179,319,BLACK);//检验触摸区域
				}
				LCD_Fill(119,259,179,319,WHITE);

				Pen_Int_Set(1);//开启中断

				return 13;
			}
			else if(Pen_Point.X0>179&&Pen_Point.X0<239&&Pen_Point.Y0>259&&Pen_Point.Y0<319)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(179,259,239,319,BLACK);//检验触摸区域
				}
				LCD_Fill(179,259,239,319,WHITE);

				Pen_Int_Set(1);//开启中断

				return 14;
			}
			else if(Pen_Point.X0>180&&Pen_Point.X0<239&&Pen_Point.Y0>0&&Pen_Point.Y0<79)
			{
				while(PEN==0)  //等待触摸释放
				{
					LCD_Fill(180,0,239,79,BLACK);//检验触摸区域
				}
				LCD_Fill(180,0,239,79,WHITE);

				Pen_Int_Set(1);//开启中断

				return 15;
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

//键值处理
void TOUCH_GUI_DISP_guashijiegua(void)		
{
	u8 key;
// 	u8 i=0;
	u8 num=0;
	u8 flag=0;

	u8 ii=0;
	u8 a=0;
	
	card_num[0]=0;card_num[1]=0;card_num[2]=0;card_num[3]=0;card_num[4]=0;card_num[5]=0;
	card_num[6]=0;card_num[7]=0;card_num[8]=0;card_num[9]=0;card_num[10]=0;card_num[11]=0;
	password[0]=0;password[1]=0;password[2]=0;password[3]=0;password[4]=0;password[5]=0;	
	
// 	Touch_Init();	 //初始化 
	LCD_Clear(WHITE);//清屏

	GUI_DISP_guashijiegua(); 	 //操作界面

	while(1)
	{
		key=TOUCH_DISP_guashijiegua();	 //获取触摸键值
		
		switch(key)			     				 		 //相应键值的处理
		{
			case 0:		GUI_DISP_guashijiegua();   				   //没有触摸按键按下，一直显示操作界面
								break;

			case 1:		TOUCH_GUI_DISP_MENU(); 	       			 //返回菜单栏
								break;

			case 2:		flag=1;															 //确定
								num=0;		 
								ii=0;
								a++;
								break;

			case 3:		if(ii == 1)	break;//输完卡号的标志
			
								if(a >= 2)	break;//输完密码后按确定的标志
							
								if(num>=12)	//卡号不能超过6位数
								{
									ii=1;
									
									break;
								}
								if(num>=6) //密码不能超过6位数
								{
									if(a == 1)//输完卡号之后按了一次确定
									{	
										ii=1;
										
										break;
									}
								}
								
								if(flag==0)	
								{
									card_num[num]=1;
									LCD_ShowChar(82+8*num,10+40*flag,'1',16,0);		  //1 
								}
								else if(flag==1) 
								{
									password[num]=1;
									LCD_ShowChar(82+8*num,10+40*flag,'*',16,0);		  //*
								}
								
								num++;
								
								break;

			case 4:		if(ii == 1)	break;
			
								if(a >= 2)	break;
							
								if(num>=12)	//卡号不能超过6位数
								{
									ii=1;
									
									break;
								}
								if(num>=6) //密码不能超过6位数
								{
									if(a == 1)//输完卡号之后按了一次确定
									{	
										ii=1;
										
										break;
									}
								}
								
								if(flag==0)	
								{
									card_num[num]=2;
									LCD_ShowChar(82+8*num,10+40*flag,'2',16,0);		  //2 
								}
								else if(flag==1) 
								{
									password[num]=2;
									LCD_ShowChar(82+8*num,10+40*flag,'*',16,0);		  //*
								}
								
								num++;
								
								break;

			case 5:		if(ii == 1)	break;
			
								if(a >= 2)	break;
							
								if(num>=12)	//卡号不能超过6位数
								{
									ii=1;
									
									break;
								}
								if(num>=6) //密码不能超过6位数
								{
									if(a == 1)//输完卡号之后按了一次确定
									{	
										ii=1;
										
										break;
									}
								}
								
								if(flag==0)	
								{
									card_num[num]=3;
									LCD_ShowChar(82+8*num,10+40*flag,'3',16,0);		  //3 
								}
								else if(flag==1) 
								{
									password[num]=3;
									LCD_ShowChar(82+8*num,10+40*flag,'*',16,0);		  //*
								}
								
								num++;
								
								break;

			case 6:		num=0;
								ii=0;
								
								//清零
								if(flag==0)	
								{
									card_num[0]=0;card_num[1]=0;card_num[2]=0;card_num[3]=0;card_num[4]=0;card_num[5]=0;
									card_num[6]=0;card_num[7]=0;card_num[8]=0;card_num[9]=0;card_num[10]=0;card_num[11]=0;
	
								}
								else if(flag==1) 
								{
									password[0]=0;password[1]=0;password[2]=0;password[3]=0;password[4]=0;password[5]=0;	
								}
								
								LCD_Fill(80+1,0+40*flag,180-1,39+40*flag,WHITE);	//重输
								break;

			case 7:		if(ii == 1)	break;
			
								if(a >= 2)	break;
							
								if(num>=12)	//卡号不能超过6位数
								{
									ii=1;
									
									break;
								}
								if(num>=6) //密码不能超过6位数
								{
									if(a == 1)//输完卡号之后按了一次确定
									{	
										ii=1;
										
										break;
									}
								}
								
								if(flag==0)	
								{
									card_num[num]=4;
									LCD_ShowChar(82+8*num,10+40*flag,'4',16,0);		  //4
								}
								else if(flag==1) 
								{
									password[num]=4;
									LCD_ShowChar(82+8*num,10+40*flag,'*',16,0);		  //*
								}
								
								num++;
								
								break;

			case 8:		if(ii == 1)	break;
			
								if(a >= 2)	break;
							
								if(num>=12)	//卡号不能超过6位数
								{
									ii=1;
									
									break;
								}
								if(num>=6) //密码不能超过6位数
								{
									if(a == 1)//输完卡号之后按了一次确定
									{	
										ii=1;
										
										break;
									}
								}
								
								if(flag==0)	
								{
									card_num[num]=5;
									LCD_ShowChar(82+8*num,10+40*flag,'5',16,0);		  //5 
								}
								else if(flag==1) 
								{
									password[num]=5;
									LCD_ShowChar(82+8*num,10+40*flag,'*',16,0);		  //*
								}
								
								num++;
								
								break;

			case 9:		if(ii == 1)	break;
			
								if(a >= 2)	break;
							
								if(num>=12)	//卡号不能超过6位数
								{
									ii=1;
									
									break;
								}
								if(num>=6) //密码不能超过6位数
								{
									if(a == 1)//输完卡号之后按了一次确定
									{	
										ii=1;
										
										break;
									}
								}
								
								if(flag==0)	
								{
									card_num[num]=6;
									LCD_ShowChar(82+8*num,10+40*flag,'6',16,0);		  //6 
								}
								else if(flag==1) 
								{
									password[num]=6;
									LCD_ShowChar(82+8*num,10+40*flag,'*',16,0);		  //*
								}
								
								num++;
								
								break;

			case 10:	num=0;
								InitAlldata();								   //初始化所有读卡相关数据的设置
								TOUCH_GUI_DISP_jiegua();	        							  //解挂	
								break;

			case 11:	if(ii == 1)	break;
			
								if(a >= 2)	break;
							
								if(num>=12)	//卡号不能超过6位数
								{
									ii=1;
									
									break;
								}
								if(num>=6) //密码不能超过6位数
								{
									if(a == 1)//输完卡号之后按了一次确定
									{	
										ii=1;
										
										break;
									}
								}
								
								if(flag==0)	
								{
									card_num[num]=7;
									LCD_ShowChar(82+8*num,10+40*flag,'7',16,0);		  //7 
								}
								else if(flag==1) 
								{
									password[num]=7;
									LCD_ShowChar(82+8*num,10+40*flag,'*',16,0);		  //*
								}
								
								num++;
								
								break;

			case 12:	if(ii == 1)	break;
			
								if(a >= 2)	break;
							
								if(num>=12)	//卡号不能超过6位数
								{
									ii=1;
									
									break;
								}
								if(num>=6) //密码不能超过6位数
								{
									if(a == 1)//输完卡号之后按了一次确定
									{	
										ii=1;
										
										break;
									}
								}
								
								if(flag==0)	
								{
									card_num[num]=8;
									LCD_ShowChar(82+8*num,10+40*flag,'8',16,0);		  //8 
								}
								else if(flag==1) 
								{
									password[num]=8;
									LCD_ShowChar(82+8*num,10+40*flag,'*',16,0);		  //*
								}
								
								num++;
								
								break;

			case 13:	if(ii == 1)	break;
			
								if(a >= 2)	break;
							
								if(num>=12)	//卡号不能超过6位数
								{
									ii=1;
									
									break;
								}
								if(num>=6) //密码不能超过6位数
								{
									if(a == 1)//输完卡号之后按了一次确定
									{	
										ii=1;
										
										break;
									}
								}
								
								if(flag==0)	
								{
									card_num[num]=9;
									LCD_ShowChar(82+8*num,10+40*flag,'9',16,0);		  //9 
								}
								else if(flag==1) 
								{
									password[num]=9;
									LCD_ShowChar(82+8*num,10+40*flag,'*',16,0);		  //*
								}
								
								num++;
								
								break;

			case 14:	if(ii == 1)	break;
			
								if(a >= 2)	break;
							
								if(num>=12)	//卡号不能超过6位数
								{
									ii=1;
									
									break;
								}
								if(num>=6) //密码不能超过6位数
								{
									if(a == 1)//输完卡号之后按了一次确定
									{	
										ii=1;
										
										break;
									}
								}
								
								if(flag==0)	
								{
									card_num[num]=0;
									LCD_ShowChar(82+8*num,10+40*flag,'0',16,0);		  //0 
								}
								else if(flag==1) 
								{
									password[num]=0;
									LCD_ShowChar(82+8*num,10+40*flag,'*',16,0);		  //*
								}
								
								num++;
								
								break;
								
			case 15:	num=0;
								InitAlldata();								   //初始化所有读卡相关数据的设置
								TOUCH_GUI_DISP_guashi();	     									  //挂失	
								break;
								

			default:	break;
		}



		delay_ms(10);//每过10ms查询一次触摸屏

// 		//LED闪烁指示程序正在运行,延时时间 = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}

//放卡
void GUI_DISP_jiegua(void)       
{	
	POINT_COLOR=BLUE; 
	Show_Str(100,120,"请放卡",16,0);
	Show_Str(40,50+120+30,"触摸任意点返回菜单栏",16,0);
}

//键值处理
void TOUCH_GUI_DISP_jiegua(void)		
{
	u8 key;
// 	u8 i=0;
	u8 ii=0;
	u8 j=0;
	u8 flag_exist=0;		
	u8 locked=0;
	u8 password_temp[4];

// 	Touch_Init();	 //初始化 
	LCD_Clear(WHITE);//清屏

	GUI_DISP_jiegua(); 	 //操作界面

	while(1)
	{
		key=TOUCH_all();	   //获取触摸键值
		
		switch(key)			     				 //相应键值的处理
		{
			case 0:		GUI_DISP_jiegua();   				     //没有触摸按键按下，一直显示操作界面
								break;

			case 1:		InitAlldata();									 //描  述  :  初始化所有读卡相关数据的设置
								TOUCH_GUI_DISP_MENU(); 	         //返回菜单栏
								break;


			default:	break;
		}
		
		
		
		if(flag_com==0)//如果没有读到卡就一直在扫卡
		{
			Read_cardID();//读卡的ID
		}
		else 
		{			
			for(ii=0;ii<4;ii++)//判断输入卡号和实际卡号是否一致
			{
				if((card_num[ii*3]*100+card_num[ii*3+1]*10+card_num[ii*3+2]) != cardID[ii])
				{
					TOUCH_GUI_DISP_guashijiegua3();//输入卡号和实际卡号不一致
				}
				else flag_exist=1;
			}
			
			if(flag_exist == 1)//输入卡号和实际卡号一致
			{
				flag_exist=0;
				
				for(j=0; j<20; j++)//循环读卡号
				{
					AT24CXX_Read(1+j*11,datatemp,4);
					
					for(ii=0;ii<4;ii++)
					{
						if(cardID[ii] != datatemp[ii])
						{
							flag_exist=0;		
	 						goto L1;				 //只要存在一个数不一样就跳出此循环
						}						
						else flag_exist=1;
					}
					
					L1:
					if(flag_exist == 1)//存在此卡号
					{
						AT24CXX_Read(6+j*11,password_temp,6);//读出密码

						
						for(ii=0;ii<6;ii++)//判断输入密码是否正确
						{
							if(password[ii] != password_temp[ii])
							{
								TOUCH_GUI_DISP_guashijiegua4();//输入密码不正确！
							}
						}
						
						locked=1;						
						AT24CXX_Write(j*11+5,&locked,1);//解锁
						TOUCH_GUI_DISP_guashijiegua2(); //解锁成功！
					}			
				}
				
				//循环读卡号，没找到此卡
				TOUCH_GUI_DISP_guashijiegua6();		 	//不存在此卡！（此卡未激活）
				
			}
		}
					
		
// 		if(flag_com==0)//如果没有读到卡就一直在扫卡
// 		{
// 			Read_cardID();//读卡的ID
// 		}
// 		else 
// 		{
// 			if(flag_guashijiegua)	TOUCH_GUI_DISP_guashijiegua0();//显示挂失结果 
// 			else	TOUCH_GUI_DISP_guashijiegua2();//显示解挂结果  
// 		}
		
		
		delay_ms(10);//每过10ms查询一次触摸屏

// 		//LED闪烁指示程序正在运行,延时时间 = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}

//挂失
void GUI_DISP_guashi(void)		
{

}
void TOUCH_GUI_DISP_guashi(void)	
{
	u8 j=0;
	u8 ii=0;
	u8 flag_exist=0;
	u8 locked=0;
	u8 password_temp[6];
	
	while(1)
	{
		for(j=0; j<20; j++)//循环读卡号
		{
			AT24CXX_Read(1+j*11,datatemp,4);
			
			for(ii=0;ii<4;ii++)//判断输入卡号是否存在
			{
				if((card_num[ii*3]*100+card_num[ii*3+1]*10+card_num[ii*3+2]) != datatemp[ii])
				{
					flag_exist=0;		
					goto L1;				 //只要存在一个数不一样就跳出此循环
				}						
				else flag_exist=1;
			}
			
			L1:
			if(flag_exist == 1)//存在此卡号
			{
				AT24CXX_Read(6+j*11,password_temp,6);//读出密码

				
				for(ii=0;ii<6;ii++)//判断输入密码是否正确
				{
					if(password[ii] != password_temp[ii])
					{
						TOUCH_GUI_DISP_guashijiegua1();//输入密码不正确！
					}
				}
				
				locked=0;						
				AT24CXX_Write(j*11+5,&locked,1);//挂失锁定
				TOUCH_GUI_DISP_guashijiegua0(); //挂失成功！
			}			
		}
		
		//循环读卡号，没找到此卡
		TOUCH_GUI_DISP_guashijiegua5();		 	//不存在此卡！（此卡未激活）
	}
}

//挂失成功
void GUI_DISP_guashijiegua0(void)
{
	POINT_COLOR=BLUE; 
	Show_Str(40,10,"触摸任意点返回菜单栏",16,0);
	Show_Str(80,130,"挂失成功！",16,0);
}

//键值处理
void TOUCH_GUI_DISP_guashijiegua0(void)		
{
	u8 key;
// 	u8 i=0;

// 	Touch_Init();	 //初始化 
	LCD_Clear(WHITE);//清屏

	GUI_DISP_guashijiegua0(); 	 //操作界面

	while(1)
	{
		key=TOUCH_all();	   //获取触摸键值
		
		switch(key)			     				 //相应键值的处理
		{
			case 0:		GUI_DISP_guashijiegua0();   				   //没有触摸按键按下，一直显示操作界面
								break;

			case 1:		InitAlldata();									 //描  述  :  初始化所有读卡相关数据的设置
								TOUCH_GUI_DISP_MENU(); 	         //返回菜单栏
								break;


			default:	break;
		}

	
		delay_ms(10);//每过10ms查询一次触摸屏

// 		//LED闪烁指示程序正在运行,延时时间 = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}

//输入密码不正确！
void GUI_DISP_guashijiegua1(void)
{
	POINT_COLOR=BLUE; 
	Show_Str(40,10,"触摸任意点返回菜单栏",16,0);
	Show_Str(80,130,"挂失失败！",16,0);
	Show_Str(50,200,"输入密码不正确！",16,0);
}

//键值处理
void TOUCH_GUI_DISP_guashijiegua1(void)		
{
	u8 key;
// 	u8 i=0;

// 	Touch_Init();	 //初始化 
	LCD_Clear(WHITE);//清屏

	GUI_DISP_guashijiegua1(); 	 //操作界面

	while(1)
	{
		key=TOUCH_all();	   //获取触摸键值
		
		switch(key)			     				 //相应键值的处理
		{
			case 0:		GUI_DISP_guashijiegua1();   				   //没有触摸按键按下，一直显示操作界面
								break;

			case 1:		InitAlldata();									 //描  述  :  初始化所有读卡相关数据的设置
								TOUCH_GUI_DISP_MENU(); 	         //返回菜单栏
								break;


			default:	break;
		}

	
		delay_ms(10);//每过10ms查询一次触摸屏

// 		//LED闪烁指示程序正在运行,延时时间 = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}

//解挂成功
void GUI_DISP_guashijiegua2(void)
{
	POINT_COLOR=BLUE; 
	Show_Str(40,10,"触摸任意点返回菜单栏",16,0);
	Show_Str(80,130,"解挂成功！",16,0);
}

//键值处理
void TOUCH_GUI_DISP_guashijiegua2(void)		
{
	u8 key;
// 	u8 i=0;

// 	Touch_Init();	 //初始化 
	LCD_Clear(WHITE);//清屏

	GUI_DISP_guashijiegua2(); 	 //操作界面

	while(1)
	{
		key=TOUCH_all();	   //获取触摸键值
		
		switch(key)			     				 //相应键值的处理
		{
			case 0:		GUI_DISP_guashijiegua2();   				   //没有触摸按键按下，一直显示操作界面
								break;

			case 1:		InitAlldata();									 //描  述  :  初始化所有读卡相关数据的设置
								TOUCH_GUI_DISP_MENU(); 	         //返回菜单栏
								break;


			default:	break;
		}

	
		delay_ms(10);//每过10ms查询一次触摸屏

// 		//LED闪烁指示程序正在运行,延时时间 = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}

//输入卡号和实际卡号不一致
void GUI_DISP_guashijiegua3(void)
{
	POINT_COLOR=BLUE; 
	Show_Str(40,10,"触摸任意点返回菜单栏",16,0);
	Show_Str(80,130,"解挂失败！",16,0);
	Show_Str(20,200,"输入卡号和实际卡号不一致",16,0);
}

//键值处理
void TOUCH_GUI_DISP_guashijiegua3(void)		
{
	u8 key;
// 	u8 i=0;

// 	Touch_Init();	 //初始化 
	LCD_Clear(WHITE);//清屏

	GUI_DISP_guashijiegua3(); 	 //操作界面

	while(1)
	{
		key=TOUCH_all();	   //获取触摸键值
		
		switch(key)			     				 //相应键值的处理
		{
			case 0:		GUI_DISP_guashijiegua3();   				   //没有触摸按键按下，一直显示操作界面
								break;

			case 1:		InitAlldata();									 //描  述  :  初始化所有读卡相关数据的设置
								TOUCH_GUI_DISP_MENU(); 	         //返回菜单栏
								break;


			default:	break;
		}

	
		delay_ms(10);//每过10ms查询一次触摸屏

// 		//LED闪烁指示程序正在运行,延时时间 = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}

//输入密码不正确！
void GUI_DISP_guashijiegua4(void)
{
	POINT_COLOR=BLUE; 
	Show_Str(40,10,"触摸任意点返回菜单栏",16,0);
	Show_Str(80,130,"解挂失败！",16,0);
	Show_Str(50,200,"输入密码不正确！",16,0);
}

//键值处理
void TOUCH_GUI_DISP_guashijiegua4(void)		
{
	u8 key;
// 	u8 i=0;

// 	Touch_Init();	 //初始化 
	LCD_Clear(WHITE);//清屏

	GUI_DISP_guashijiegua4(); 	 //操作界面

	while(1)
	{
		key=TOUCH_all();	   //获取触摸键值
		
		switch(key)			     				 //相应键值的处理
		{
			case 0:		GUI_DISP_guashijiegua4();   				   //没有触摸按键按下，一直显示操作界面
								break;

			case 1:		InitAlldata();									 //描  述  :  初始化所有读卡相关数据的设置
								TOUCH_GUI_DISP_MENU(); 	         //返回菜单栏
								break;


			default:	break;
		}

	
		delay_ms(10);//每过10ms查询一次触摸屏

// 		//LED闪烁指示程序正在运行,延时时间 = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}

//不存在此卡！（此卡未激活）
void GUI_DISP_guashijiegua5(void)
{
	POINT_COLOR=BLUE; 
	Show_Str(40,10,"触摸任意点返回菜单栏",16,0);
	Show_Str(70,70,"此卡未激活",16,0);
	Show_Str(80,130,"挂失失败！",16,0);
}

//键值处理
void TOUCH_GUI_DISP_guashijiegua5(void)		
{
	u8 key;
// 	u8 i=0;

// 	Touch_Init();	 //初始化 
	LCD_Clear(WHITE);//清屏

	GUI_DISP_guashijiegua5(); 	 //操作界面

	while(1)
	{
		key=TOUCH_all();	   //获取触摸键值
		
		switch(key)			     				 //相应键值的处理
		{
			case 0:		GUI_DISP_guashijiegua5();   		 //没有触摸按键按下，一直显示操作界面
								break;

			case 1:		InitAlldata();									 //描  述  :  初始化所有读卡相关数据的设置
								TOUCH_GUI_DISP_MENU(); 	         //返回菜单栏
								break;


			default:	break;
		}

		
		delay_ms(10);//每过10ms查询一次触摸屏

// 		//LED闪烁指示程序正在运行,延时时间 = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}

//不存在此卡！（此卡未激活）
void GUI_DISP_guashijiegua6(void)
{
	POINT_COLOR=BLUE; 
	Show_Str(40,10,"触摸任意点返回菜单栏",16,0);
	Show_Str(70,70,"此卡未激活",16,0);
	Show_Str(80,130,"解挂失败！",16,0);
}

//键值处理
void TOUCH_GUI_DISP_guashijiegua6(void)		
{
	u8 key;
// 	u8 i=0;

// 	Touch_Init();	 //初始化 
	LCD_Clear(WHITE);//清屏

	GUI_DISP_guashijiegua6(); 	 //操作界面

	while(1)
	{
		key=TOUCH_all();	   //获取触摸键值
		
		switch(key)			     				 //相应键值的处理
		{
			case 0:		GUI_DISP_guashijiegua6();   		 //没有触摸按键按下，一直显示操作界面
								break;

			case 1:		InitAlldata();									 //描  述  :  初始化所有读卡相关数据的设置
								TOUCH_GUI_DISP_MENU(); 	         //返回菜单栏
								break;


			default:	break;
		}

		
		delay_ms(10);//每过10ms查询一次触摸屏

// 		//LED闪烁指示程序正在运行,延时时间 = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}















//管理员显示界面
void GUI_DISP_administrator(void)       
{	
	POINT_COLOR=BLUE; 
	Show_Str(100,50,"管理员",16,0);
	Show_Str(100,120,"请放卡",16,0);
	Show_Str(40,50+120+30,"触摸任意点返回菜单栏",16,0);
}

//键值处理
void TOUCH_GUI_DISP_administrator(void)		
{
	u8 key;
// 	u8 i=0;
	u8 ii=0;

// 	Touch_Init();	 //初始化 
	LCD_Clear(WHITE);//清屏

	GUI_DISP_administrator(); 	 //操作界面

	while(1)
	{
		key=TOUCH_all();	   //获取触摸键值
		
		switch(key)			     				 //相应键值的处理
		{
			case 0:		GUI_DISP_administrator();   		 //没有触摸按键按下，一直显示操作界面
								break;

			case 1:		InitAlldata();									 //描  述  :  初始化所有读卡相关数据的设置
								TOUCH_GUI_DISP_MENU(); 	         //返回菜单栏
								break;


			default:	break;
		}

		
		if(flag_com==0)//如果没有读到卡就一直在扫卡
		{
			Read_cardID();//读卡号
		}
		else //判断是否是管理员的卡号
		{
			for(ii=0;ii<4;ii++)
			{
				if(cardID[ii] != administrator[ii])
						TOUCH_GUI_DISP_administrator0();	//不是管理员卡号
			}
			
			InitAlldata();							//描  述  :  初始化所有读卡相关数据的设置
			TOUCH_GUI_DISP_chongzhi();	//进入充值界面
		}
				
						
		
		delay_ms(10);//每过10ms查询一次触摸屏

// 		//LED闪烁指示程序正在运行,延时时间 = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}

//非管理员显示界面
void GUI_DISP_administrator0(void)       
{	
	POINT_COLOR=BLUE; 
	Show_Str(50,50,"不是管理员卡号！",16,0);
	Show_Str(40,50+120+30,"触摸任意点返回菜单栏",16,0);
}

//键值处理
void TOUCH_GUI_DISP_administrator0(void)		
{
	u8 key;
// 	u8 i=0;

// 	Touch_Init();	 //初始化 
	LCD_Clear(WHITE);//清屏

	GUI_DISP_administrator0(); 	 //操作界面

	while(1)
	{
		key=TOUCH_all();	   //获取触摸键值
		
		switch(key)			     				 //相应键值的处理
		{
			case 0:		GUI_DISP_administrator0();   		 //没有触摸按键按下，一直显示操作界面
								break;

			case 1:		InitAlldata();									 //描  述  :  初始化所有读卡相关数据的设置
								TOUCH_GUI_DISP_MENU(); 	         //返回菜单栏
								break;


			default:	break;
		}

		delay_ms(10);//每过10ms查询一次触摸屏

// 		//LED闪烁指示程序正在运行,延时时间 = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}































