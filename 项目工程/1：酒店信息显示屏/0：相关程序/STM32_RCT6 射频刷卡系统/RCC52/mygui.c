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



//��ӵ�ͷ�ļ�
#include "touch.h" 
//#include "rtc.h"
//#include "ds18b20.h"
//#include "rc522_add.h"


//�ҵ�ͷ�ļ�
#include "mygui.h"



u8 input[5]={0,0,0,0,0};
u8 length=0;
u8 card_num[12]={0,0,0,0,0,0,0,0,0,0,0,0};//����12λ
u8 password[6]={0,0,0,0,0,0};							//����6λ

u8 card_status=0;




/****************************
        ���ְ�������
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
	Show_Str(0,0,"�����룺",16,0);
	Show_Str(10,49,"ɾ��",16,0);
	Show_Str(195,49,"ȷ��",16,0);

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
     ���ְ�����������
****************************/
void my_GUI_TOUCH_2(void)
{
	u8 i=0;

// 	Touch_Init();	 //��ʼ��
	LCD_Clear(WHITE);//����

	GUI_DISP_0();	 //���ְ�������

	//����ɨ��
	while(1)
	{	
		if(Pen_Point.Key_Sta==Key_Down)//������������
		{
			Pen_Int_Set(0);//�ر��ж�

				Convert_Pos();//ת����������ݴ�������У׼����������ת����Ľ��,������X0,Y0��
				Pen_Point.Key_Sta=Key_Up;

				if(Pen_Point.X0>0&&Pen_Point.X0<59&&Pen_Point.Y0>79&&Pen_Point.Y0<139)
				{
					while(PEN==0)  //�ȴ������ͷ�
					{
						LCD_Fill(0,79,59,139,BLACK);//���鴥������
					}
					LCD_Fill(0,79,59,139,WHITE);
					GUI_DISP_0();

					LCD_ShowNum(119,39,1,1,16);  												//1
				}
				else if(Pen_Point.X0>59&&Pen_Point.X0<119&&Pen_Point.Y0>79&&Pen_Point.Y0<139) 
				{
					while(PEN==0)  //�ȴ������ͷ�
					{
						LCD_Fill(59,79,119,139,BLACK);//���鴥������
					}
					LCD_Fill(59,79,119,139,WHITE);
					GUI_DISP_0();

					LCD_ShowNum(119,39,2,1,16);													//2
				}
				else if(Pen_Point.X0>119&&Pen_Point.X0<179&&Pen_Point.Y0>79&&Pen_Point.Y0<139) 
				{
					while(PEN==0)  //�ȴ������ͷ�
					{
						LCD_Fill(119,79,179,139,BLACK);//���鴥������
					}
					LCD_Fill(119,79,179,139,WHITE);
					GUI_DISP_0();

					LCD_ShowNum(119,39,3,1,16);												  //3
				}
				else if(Pen_Point.X0>179&&Pen_Point.X0<239&&Pen_Point.Y0>79&&Pen_Point.Y0<139) 
				{
					while(PEN==0)  //�ȴ������ͷ�
					{
						LCD_Fill(179,79,239,139,BLACK);//���鴥������
					}
					LCD_Fill(179,79,239,139,WHITE);
					GUI_DISP_0();

					LCD_ShowChar(119,39,'A',16,0);											//A
				}

				else if(Pen_Point.X0>0&&Pen_Point.X0<59&&Pen_Point.Y0>139&&Pen_Point.Y0<199)
				{
					while(PEN==0)  //�ȴ������ͷ�
					{
						LCD_Fill(0,139,59,199,BLACK);//���鴥������
					}
					LCD_Fill(0,139,59,199,WHITE);
					GUI_DISP_0();

					LCD_ShowNum(119,39,4,1,16); 												//4
				}
				else if(Pen_Point.X0>59&&Pen_Point.X0<119&&Pen_Point.Y0>139&&Pen_Point.Y0<199)
				{
					while(PEN==0)  //�ȴ������ͷ�
					{
						LCD_Fill(59,139,119,199,BLACK);//���鴥������
					}
					LCD_Fill(59,139,119,199,WHITE);
					GUI_DISP_0();

					LCD_ShowNum(119,39,5,1,16); 												//5
				}
				else if(Pen_Point.X0>119&&Pen_Point.X0<179&&Pen_Point.Y0>139&&Pen_Point.Y0<199)
				{
					while(PEN==0)  //�ȴ������ͷ�
					{
						LCD_Fill(119,139,179,199,BLACK);//���鴥������
					}
					LCD_Fill(119,139,179,199,WHITE);
					GUI_DISP_0();

					LCD_ShowNum(119,39,6,1,16);													//6
				}
				else if(Pen_Point.X0>179&&Pen_Point.X0<239&&Pen_Point.Y0>139&&Pen_Point.Y0<199)
				{  	
					while(PEN==0)  //�ȴ������ͷ�
					{
						LCD_Fill(179,139,239,199,BLACK);//���鴥������
					}
					LCD_Fill(179,139,239,199,WHITE);
					GUI_DISP_0();

					LCD_ShowChar(119,39,'B',16,0);											//B
				}

				else if(Pen_Point.X0>0&&Pen_Point.X0<59&&Pen_Point.Y0>199&&Pen_Point.Y0<259)
				{
					while(PEN==0)  //�ȴ������ͷ�
					{
						LCD_Fill(0,199,59,259,BLACK);//���鴥������
					}
					LCD_Fill(0,199,59,259,WHITE);
					GUI_DISP_0();

					LCD_ShowNum(119,39,7,1,16);  												//7
				}
				else if(Pen_Point.X0>59&&Pen_Point.X0<119&&Pen_Point.Y0>199&&Pen_Point.Y0<259)
				{
					while(PEN==0)  //�ȴ������ͷ�
					{
						LCD_Fill(59,199,119,259,BLACK);//���鴥������
					}
					LCD_Fill(59,199,119,259,WHITE);
					GUI_DISP_0();

					LCD_ShowNum(119,39,8,1,16);													//8
				}
				else if(Pen_Point.X0>119&&Pen_Point.X0<179&&Pen_Point.Y0>199&&Pen_Point.Y0<259)
				{
					while(PEN==0)  //�ȴ������ͷ�
					{
						LCD_Fill(119,199,179,259,BLACK);//���鴥������
					}
					LCD_Fill(119,199,179,259,WHITE);
					GUI_DISP_0();

					LCD_ShowNum(119,39,9,1,16);													//9
				}
				else if(Pen_Point.X0>179&&Pen_Point.X0<239&&Pen_Point.Y0>199&&Pen_Point.Y0<259)
				{
					while(PEN==0)  //�ȴ������ͷ�
					{
						LCD_Fill(179,199,239,259,BLACK);//���鴥������
					}
					LCD_Fill(179,199,239,259,WHITE);
					GUI_DISP_0();

					LCD_ShowChar(119,39,'C',16,0);											//C
				}

				else if(Pen_Point.X0>0&&Pen_Point.X0<59&&Pen_Point.Y0>259&&Pen_Point.Y0<319)
				{
					while(PEN==0)  //�ȴ������ͷ�
					{
						LCD_Fill(0,259,59,319,BLACK);//���鴥������
					}
					LCD_Fill(0,259,59,319,WHITE);
					GUI_DISP_0();

					LCD_ShowChar(119,39,'*',16,0);											//*
				}
				else if(Pen_Point.X0>59&&Pen_Point.X0<119&&Pen_Point.Y0>259&&Pen_Point.Y0<319)
				{
					while(PEN==0)  //�ȴ������ͷ�
					{
						LCD_Fill(59,259,119,319,BLACK);//���鴥������
					}
					LCD_Fill(59,259,119,319,WHITE);
					GUI_DISP_0();

					LCD_ShowNum(119,39,0,1,16);												  //0
				}
				else if(Pen_Point.X0>119&&Pen_Point.X0<179&&Pen_Point.Y0>259&&Pen_Point.Y0<319)
				{
					while(PEN==0)  //�ȴ������ͷ�
					{
						LCD_Fill(119,259,179,319,BLACK);//���鴥������
					}
					LCD_Fill(119,259,179,319,WHITE);
					GUI_DISP_0();

					LCD_ShowChar(119,39,'#',16,0);											//#
				}
				else if(Pen_Point.X0>179&&Pen_Point.X0<239&&Pen_Point.Y0>259&&Pen_Point.Y0<319)
				{
					while(PEN==0)  //�ȴ������ͷ�
					{
						LCD_Fill(179,259,239,319,BLACK);//���鴥������
					}
					LCD_Fill(179,259,239,319,WHITE);
					GUI_DISP_0();

					LCD_ShowChar(119,39,'D',16,0);											//D
				}

				else if(Pen_Point.X0>0&&Pen_Point.X0<59&&Pen_Point.Y0>19&&Pen_Point.Y0<79)
				{
					while(PEN==0)  //�ȴ������ͷ�
					{
						LCD_Fill(0,19,59,79,BLACK);//���鴥������
					}
					LCD_Fill(0,19,59,79,WHITE);
					GUI_DISP_0();

					LCD_ShowChar(119,39,' ',16,0);			    					 //ɾ��
				}
				else if(Pen_Point.X0>179&&Pen_Point.X0<239&&Pen_Point.Y0>19&&Pen_Point.Y0<79)
				{
					while(PEN==0)  //�ȴ������ͷ�
					{
						LCD_Fill(179,19,239,79,BLACK);//���鴥������
					}
					LCD_Fill(179,19,239,79,WHITE);
					GUI_DISP_0();

					LED1=!LED1;								    										 //ȷ��

//					Pen_Int_Set(1);//�����жϣ���Ϊ������л�������䣬����Ҫ����ǰ��رյ��ж� 
					delay_ms(10);	
					//�л�����							
				}

			Pen_Int_Set(1);//�����ж�
			delay_ms(10);
		}else delay_ms(10);//ÿ��10ms��ѯһ�δ�����


		//LED��˸ָʾ������������,��ʱʱ�� = delay_ms(10)*50 = 500ms
		i++;     
		if(i==50)
		{
			i=0;
			LED0=!LED0;
		}	
	}
}







/****************************
     RTCʵʱʱ����ʾ����
****************************/
void GUI_DISP_1(void) 
{
	u8 t=0;	

	RTC_Init();

//  	Touch_Init();	//��ʼ��
	LCD_Clear(WHITE);//����

	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(60,50,"Mini STM32");	
	LCD_ShowString(60,70,"RTC TEST");	
	LCD_ShowString(60,90,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,"2010/12/30");
		
	//��ʾʱ��
	POINT_COLOR=BLUE;//��������Ϊ��ɫ
	LCD_ShowString(60,130,"    -  -  ");	   
	LCD_ShowString(60,162,"  :  :  ");		    
	while(1)
	{	
		//����ɨ��
		if(Pen_Point.Key_Sta==Key_Down)//������������
		{
			Pen_Int_Set(0);//�ر��ж�

				Convert_Pos();//ת����������ݴ�������У׼����������ת����Ľ��,������X0,Y0��
				Pen_Point.Key_Sta=Key_Up;

				if(Pen_Point.X0>0&&Pen_Point.X0<239&&Pen_Point.Y0>0&&Pen_Point.Y0<319)
				{
					while(PEN==0)  //�ȴ������ͷ�
					{
						LCD_Fill(0,0,239,319,BLUE);//���鴥������
					}
//					Pen_Int_Set(1);//�����жϣ���Ϊ������л�������䣬����Ҫ����ǰ��رյ��ж� 
					delay_ms(10);
					//�л�����
				}

			Pen_Int_Set(1);//�����ж�
			delay_ms(10);
		}else delay_ms(10);//ÿ��10ms��ѯһ�δ�����
		
		
		//���жϷ������������ں�ʱ�䣩							    
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

			//ÿ����˸һ��
			LED0=!LED0;
		}								  
	}  
}







/***********************************
      ���ְ�������ɨ�跴����ֵ
***********************************/
u8 my_GUI_TOUCH_0(void)
{	
	
	//ɨ�败����
	if(Pen_Point.Key_Sta==Key_Down)//������������
	{
		Pen_Int_Set(0);//�ر��ж�

			Convert_Pos();//ת����������ݴ�������У׼����������ת����Ľ��,������X0,Y0��
			Pen_Point.Key_Sta=Key_Up;

			if(Pen_Point.X0>0&&Pen_Point.X0<59&&Pen_Point.Y0>79&&Pen_Point.Y0<139)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(0,79,59,139,BLACK);//���鴥������
				}
				LCD_Fill(0,79,59,139,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 1;
			}
			else if(Pen_Point.X0>59&&Pen_Point.X0<119&&Pen_Point.Y0>79&&Pen_Point.Y0<139) 
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(59,79,119,139,BLACK);//���鴥������
				}
				LCD_Fill(59,79,119,139,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 2;
			}
			else if(Pen_Point.X0>119&&Pen_Point.X0<179&&Pen_Point.Y0>79&&Pen_Point.Y0<139) 
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(119,79,179,139,BLACK);//���鴥������
				}
				LCD_Fill(119,79,179,139,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 3;
			}
			else if(Pen_Point.X0>179&&Pen_Point.X0<239&&Pen_Point.Y0>79&&Pen_Point.Y0<139) 
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(179,79,239,139,BLACK);//���鴥������
				}
				LCD_Fill(179,79,239,139,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 4;
			}

			else if(Pen_Point.X0>0&&Pen_Point.X0<59&&Pen_Point.Y0>139&&Pen_Point.Y0<199)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(0,139,59,199,BLACK);//���鴥������
				}
				LCD_Fill(0,139,59,199,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 5;
			}
			else if(Pen_Point.X0>59&&Pen_Point.X0<119&&Pen_Point.Y0>139&&Pen_Point.Y0<199)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(59,139,119,199,BLACK);//���鴥������
				}
				LCD_Fill(59,139,119,199,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 6;
			}
			else if(Pen_Point.X0>119&&Pen_Point.X0<179&&Pen_Point.Y0>139&&Pen_Point.Y0<199)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(119,139,179,199,BLACK);//���鴥������
				}
				LCD_Fill(119,139,179,199,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 7;
			}
			else if(Pen_Point.X0>179&&Pen_Point.X0<239&&Pen_Point.Y0>139&&Pen_Point.Y0<199)
			{  	
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(179,139,239,199,BLACK);//���鴥������
				}
				LCD_Fill(179,139,239,199,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 8;
			}

			else if(Pen_Point.X0>0&&Pen_Point.X0<59&&Pen_Point.Y0>199&&Pen_Point.Y0<259)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(0,199,59,259,BLACK);//���鴥������
				}
				LCD_Fill(0,199,59,259,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 9;
			}
			else if(Pen_Point.X0>59&&Pen_Point.X0<119&&Pen_Point.Y0>199&&Pen_Point.Y0<259)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(59,199,119,259,BLACK);//���鴥������
				}
				LCD_Fill(59,199,119,259,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 10;
			}
			else if(Pen_Point.X0>119&&Pen_Point.X0<179&&Pen_Point.Y0>199&&Pen_Point.Y0<259)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(119,199,179,259,BLACK);//���鴥������
				}
				LCD_Fill(119,199,179,259,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 11;
			}
			else if(Pen_Point.X0>179&&Pen_Point.X0<239&&Pen_Point.Y0>199&&Pen_Point.Y0<259)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(179,199,239,259,BLACK);//���鴥������
				}
				LCD_Fill(179,199,239,259,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 12;
			}

			else if(Pen_Point.X0>0&&Pen_Point.X0<59&&Pen_Point.Y0>259&&Pen_Point.Y0<319)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(0,259,59,319,BLACK);//���鴥������
				}
				LCD_Fill(0,259,59,319,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 13;
			}
			else if(Pen_Point.X0>59&&Pen_Point.X0<119&&Pen_Point.Y0>259&&Pen_Point.Y0<319)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(59,259,119,319,BLACK);//���鴥������
				}
				LCD_Fill(59,259,119,319,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 14;
			}
			else if(Pen_Point.X0>119&&Pen_Point.X0<179&&Pen_Point.Y0>259&&Pen_Point.Y0<319)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(119,259,179,319,BLACK);//���鴥������
				}
				LCD_Fill(119,259,179,319,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 15;
			}
			else if(Pen_Point.X0>179&&Pen_Point.X0<239&&Pen_Point.Y0>259&&Pen_Point.Y0<319)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(179,259,239,319,BLACK);//���鴥������
				}
				LCD_Fill(179,259,239,319,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 16;
			}

			else if(Pen_Point.X0>0&&Pen_Point.X0<59&&Pen_Point.Y0>19&&Pen_Point.Y0<79)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(0,19,59,79,BLACK);//���鴥������
				}
				LCD_Fill(0,19,59,79,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 17;
			}
			else if(Pen_Point.X0>179&&Pen_Point.X0<239&&Pen_Point.Y0>19&&Pen_Point.Y0<79)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(179,19,239,79,BLACK);//���鴥������
				}
				LCD_Fill(179,19,239,79,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 18;
			}

		Pen_Int_Set(1);//�����ж�
	}

//	delay_ms(10);//ÿ��10ms��ѯһ�δ�����
	return 0;	 //û�д�����������


//	//LED��˸ָʾ������������,��ʱʱ�� = delay_ms(10)*50 = 500ms
//	i++;     
//	if(i==50)
//	{
//		i=0;
//		LED0=!LED0;
//	}	

}




/***********************************
        ���ְ���������ֵ����
***********************************/
void my_GUI_TOUCH_1(void)
{
	u8 key,i=0;

// 	Touch_Init();	 //��ʼ�� 
	LCD_Clear(WHITE);//����

	GUI_DISP_0(); 	 //��������

	while(1)
	{
		key=my_GUI_TOUCH_0();	 //��ȡ������ֵ
		
		switch(key)			       //��Ӧ��ֵ�Ĵ���
		{
			case 0:		LCD_ShowNum(109,20,0,2,16);  	  //û�д�����������
								GUI_DISP_0();   				   			//һֱ��ʾ��������
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

			case 17:	LCD_ShowChar(116,0,'Y',16,0);   //ɾ��	
								break;

			case 18:	LCD_ShowChar(116,0,'N',16,0);   //ȷ��
								break;

			default:	break;
		}



		delay_ms(10);//ÿ��10ms��ѯһ�δ�����

		//LED��˸ָʾ������������,��ʱʱ�� = delay_ms(10)*50 = 500ms
		i++;     
		if(i==50)
		{
			i=0;
			LED0=!LED0;
		}	
	}
}





/***********************************
           �¶���ʾ����
***********************************/
void GUI_DISP_2(void)            
{
	short temp; 
	POINT_COLOR=RED;//��������Ϊ��ɫ	   
	LCD_ShowString(60,50,"Mini STM32");	
	LCD_ShowString(60,70,"DS18B20 TEST");	
	LCD_ShowString(60,90,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,"2011/1/1");
	while(DS18B20_Init())//��ʼ��DS18B20,����18B20
	{
		LCD_ShowString(60,130,"DS18B20 Check Failed!");
		delay_ms(500);		  
		LCD_ShowString(60,130,"Please Check!        ");
		delay_ms(500);
		LED0=!LED0;//DS0��˸
	}
  LCD_ShowString(60,130,"DS18B20 Ready!     ");	 
 	POINT_COLOR=BLUE;//��������Ϊ��ɫ	   
	LCD_ShowString(60,150, "Temperate:   . C");	 
	while(1)
	{	  
		temp=DS18B20_Get_Temp();
		if(temp<0)
		{
			temp=-temp;
			LCD_ShowChar(140,150,'-',16,0);//��ʾ����	
		}						 
		LCD_ShowNum(148,150,temp/10,2,16);//��ʾ�¶�ֵ	  
		LCD_ShowNum(172,150,temp%10,1,16);//��ʾ�¶�ֵ
		//printf("t1:%d\n",temp);
		delay_ms(200);
		LED0=!LED0;
	}			
}













/***********************************
        �˵�����ʾ��������
***********************************/
void GUI_DISP_MENU(void)         
{
	POINT_COLOR=BLACK; 
	LCD_DrawLine(0, 39, 239, 39);										//��
	LCD_DrawLine(0, 39+70+20, 239, 39+70+20);				//��
	LCD_DrawLine(0, 39+70+70+40, 239, 39+70+70+40); //��
	LCD_DrawLine(119, 39, 119, 319);								//��
	
	POINT_COLOR=BLUE; 
	Show_Str(100,10,"�˵���",16,0);
	Show_Str(39+5,75,"��ֵ",16,0);
	Show_Str(39+120+5,75,"����",16,0);
	Show_Str(39+5,75+90,"��ѯ",16,0);
	Show_Str(39+30+120-40,75+90,"��ʧ/���",16,0);
	
	POINT_COLOR=RED; 
	Show_Str(5+10,39+70+70+40+11,"������¶�",16,0);
	Show_Str(5+10+120,39+70+70+40+11,"���ں�ʱ��",16,0);
	
}

//��ֵ����
u8 TOUCH_DISP_MENU(void) 				 		
{
	//ɨ�败����
	if(Pen_Point.Key_Sta==Key_Down)//������������
	{
		  Pen_Int_Set(0);//�ر��ж�

			Convert_Pos();//ת����������ݴ�������У׼����������ת����Ľ��,������X0,Y0��
			Pen_Point.Key_Sta=Key_Up;

			if(Pen_Point.X0>0&&Pen_Point.X0<119&&Pen_Point.Y0>39&&Pen_Point.Y0<129)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(0,39,119,129,BLACK);//���鴥������
				}
				LCD_Fill(0,39,119,129,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 1;
			}
			else if(Pen_Point.X0>119&&Pen_Point.X0<239&&Pen_Point.Y0>39&&Pen_Point.Y0<129) 
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(119,39,239,129,BLACK);//���鴥������
				}
				LCD_Fill(119,39,239,129,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 2;
			}
			else if(Pen_Point.X0>0&&Pen_Point.X0<119&&Pen_Point.Y0>129&&Pen_Point.Y0<219) 
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(0,129,119,219,BLACK);//���鴥������
				}
				LCD_Fill(0,129,119,219,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 3;
			}
			else if(Pen_Point.X0>119&&Pen_Point.X0<239&&Pen_Point.Y0>129&&Pen_Point.Y0<219) 
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(119,129,239,219,BLACK);//���鴥������
				}
				LCD_Fill(119,129,239,219,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 4;
			}


		Pen_Int_Set(1);//�����ж�
	}

//	delay_ms(10);//ÿ��10ms��ѯһ�δ�����
	return 0;	 //û�д�����������


//	//LED��˸ָʾ������������,��ʱʱ�� = delay_ms(10)*50 = 500ms
//	i++;     
//	if(i==50)
//	{
//		i=0;
//		LED0=!LED0;
//	}	
}

//��ֵ����
void TOUCH_GUI_DISP_MENU(void)		 		
{
	u8 key;
// 	u8 i=0;
	u8 t=0;	
	short temp; 
	
	card_status=0;//״̬����

// 	Touch_Init();	 //��ʼ�� 
	LCD_Clear(WHITE);//����

	GUI_DISP_MENU();         //�˵�����ʾ��������
	
	
	//��ʾʱ��
	POINT_COLOR=BLUE;//��������Ϊ��ɫ
	LCD_ShowString(60+65+10,130+70+40+20,"    -  -  ");	   
	LCD_ShowString(60+65+15,162+70+40+20,"  :  :  ");		    

	
	//��ʾ�¶�
	POINT_COLOR=BLUE;//��������Ϊ��ɫ	   
	LCD_ShowString(10,250+20, "      . C");	 

	
	while(1)
	{
		//���жϷ������������ں�ʱ�䣩							    
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

// 			//ÿ����˸һ��
// 			LED0=!LED0;
		}		
		
		
		
		//�����¶�
		temp=DS18B20_Get_Temp();
		if(temp<0)
		{
			temp=-temp;
			LCD_ShowChar(140-110,250+20,'-',16,0);//��ʾ����	
		}						 
		LCD_ShowNum(148-110,250+20,temp/10,2,16);//��ʾ�¶�ֵ	  
		LCD_ShowNum(172-110,250+20,temp%10,1,16);//��ʾ�¶�ֵ
		
		
		
		
		
		key=TOUCH_DISP_MENU(); //��ȡ������ֵ
		switch(key)			       //��Ӧ��ֵ�Ĵ���
		{
			case 0:		GUI_DISP_MENU();   				 //û�д����������£�һֱ��ʾ��������
								break;

			case 1:		TOUCH_GUI_DISP_administrator(); 	  //����Ա��֤
								break;

			case 2:		TOUCH_GUI_DISP_xiaofei(); 		   		//����
								break;

			case 3:		TOUCH_GUI_DISP_chaxun();    		 		//��ѯ
								break;

			case 4:		TOUCH_GUI_DISP_guashijiegua(); 	 		//��ʧ/���	
								break;


			default:	break;
		}
		

		delay_ms(10);//ÿ��10ms��ѯһ�δ�����

// 		//LED��˸ָʾ������������,��ʱʱ�� = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}












/***********************************
        ��ֵ��ʾ��������
***********************************/
void GUI_DISP_chongzhi(void)     
{
	POINT_COLOR=BLACK; 
	LCD_DrawLine(0, 39, 239, 39);					//��
	LCD_DrawLine(0, 79, 239, 79);					//��
	LCD_DrawLine(0, 79+60, 239, 79+60);		//��
	LCD_DrawLine(0, 79+120, 239, 79+120);	//��
	LCD_DrawLine(0, 79+180, 239, 79+180);	//��
	LCD_DrawLine(59, 79+60, 59, 319);			//��
	LCD_DrawLine(119, 79, 119, 319);			//��
	LCD_DrawLine(179, 79+60, 179, 319);		//��
	
	POINT_COLOR=BLUE; 
	Show_Str(60,10,"��ֵ/��λ��Ԫ��",16,0);
	Show_Str(20,10+40+60-5,"���ز˵���",16,0);
	Show_Str(120+45,10+40+60-5,"ȷ��",16,0);
	Show_Str(180+10+5,10+40+60+60-5,"����",16,0);
	
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

//��ֵ����
u8 TOUCH_DISP_chongzhi(void)		 	 
{
	//ɨ�败����
	if(Pen_Point.Key_Sta==Key_Down)//������������
	{
			Pen_Int_Set(0);//�ر��ж�

			Convert_Pos();//ת����������ݴ�������У׼����������ת����Ľ��,������X0,Y0��
			Pen_Point.Key_Sta=Key_Up;

			if(Pen_Point.X0>0&&Pen_Point.X0<119&&Pen_Point.Y0>79&&Pen_Point.Y0<139)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(0,79,119,139,BLACK);//���鴥������
				}
				LCD_Fill(0,79,119,139,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 1;
			}
			else if(Pen_Point.X0>119&&Pen_Point.X0<239&&Pen_Point.Y0>79&&Pen_Point.Y0<139) 
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(119,79,239,139,BLACK);//���鴥������
				}
				LCD_Fill(119,79,239,139,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 2;
			}
			
			
			
			else if(Pen_Point.X0>0&&Pen_Point.X0<59&&Pen_Point.Y0>139&&Pen_Point.Y0<199)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(0,139,59,199,BLACK);//���鴥������
				}
				LCD_Fill(0,139,59,199,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 3;
			}
			else if(Pen_Point.X0>59&&Pen_Point.X0<119&&Pen_Point.Y0>139&&Pen_Point.Y0<199)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(59,139,119,199,BLACK);//���鴥������
				}
				LCD_Fill(59,139,119,199,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 4;
			}
			else if(Pen_Point.X0>119&&Pen_Point.X0<179&&Pen_Point.Y0>139&&Pen_Point.Y0<199)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(119,139,179,199,BLACK);//���鴥������
				}
				LCD_Fill(119,139,179,199,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 5;
			}
			else if(Pen_Point.X0>179&&Pen_Point.X0<239&&Pen_Point.Y0>139&&Pen_Point.Y0<199)
			{  	
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(179,139,239,199,BLACK);//���鴥������
				}
				LCD_Fill(179,139,239,199,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 6;
			}

			
			else if(Pen_Point.X0>0&&Pen_Point.X0<59&&Pen_Point.Y0>199&&Pen_Point.Y0<259)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(0,199,59,259,BLACK);//���鴥������
				}
				LCD_Fill(0,199,59,259,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 7;
			}
			else if(Pen_Point.X0>59&&Pen_Point.X0<119&&Pen_Point.Y0>199&&Pen_Point.Y0<259)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(59,199,119,259,BLACK);//���鴥������
				}
				LCD_Fill(59,199,119,259,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 8;
			}
			else if(Pen_Point.X0>119&&Pen_Point.X0<179&&Pen_Point.Y0>199&&Pen_Point.Y0<259)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(119,199,179,259,BLACK);//���鴥������
				}
				LCD_Fill(119,199,179,259,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 9;
			}
			else if(Pen_Point.X0>179&&Pen_Point.X0<239&&Pen_Point.Y0>199&&Pen_Point.Y0<259)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(179,199,239,259,BLACK);//���鴥������
				}
				LCD_Fill(179,199,239,259,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 10;
			}

			
			else if(Pen_Point.X0>0&&Pen_Point.X0<59&&Pen_Point.Y0>259&&Pen_Point.Y0<319)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(0,259,59,319,BLACK);//���鴥������
				}
				LCD_Fill(0,259,59,319,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 11;
			}
			else if(Pen_Point.X0>59&&Pen_Point.X0<119&&Pen_Point.Y0>259&&Pen_Point.Y0<319)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(59,259,119,319,BLACK);//���鴥������
				}
				LCD_Fill(59,259,119,319,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 12;
			}
			else if(Pen_Point.X0>119&&Pen_Point.X0<179&&Pen_Point.Y0>259&&Pen_Point.Y0<319)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(119,259,179,319,BLACK);//���鴥������
				}
				LCD_Fill(119,259,179,319,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 13;
			}
			else if(Pen_Point.X0>179&&Pen_Point.X0<239&&Pen_Point.Y0>259&&Pen_Point.Y0<319)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(179,259,239,319,BLACK);//���鴥������
				}
				LCD_Fill(179,259,239,319,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 14;
			}

		Pen_Int_Set(1);//�����ж�
	}

//	delay_ms(10);//ÿ��10ms��ѯһ�δ�����
	return 0;	 //û�д�����������


//	//LED��˸ָʾ������������,��ʱʱ�� = delay_ms(10)*50 = 500ms
//	i++;     
//	if(i==50)
//	{
//		i=0;
//		LED0=!LED0;
//	}	
}

//��ֵ����
void TOUCH_GUI_DISP_chongzhi(void) 
{
	u8 key;
// 	u8 i=0;
	u8 num=0;
	
	u8 ii=0;
	u8 a=0;
	double temp_chongzhi=0;//��ֵ���
	
	length=0;
	input[0]=0;input[1]=0;input[2]=0;input[3]=0;input[4]=0;

// 	Touch_Init();	 //��ʼ�� 
	LCD_Clear(WHITE);//����

	GUI_DISP_chongzhi(); 	 //��������

	while(1)
	{
		key=TOUCH_DISP_chongzhi();	 //��ȡ������ֵ
		
		switch(key)			     				 //��Ӧ��ֵ�Ĵ���
		{
			case 0:		GUI_DISP_chongzhi();   				 //û�д����������£�һֱ��ʾ��������
								break;

			case 1:		TOUCH_GUI_DISP_MENU(); 	       //���ز˵���
								break;

			case 2:		InitAlldata();								 //��ʼ�����ж���������ݵ�����
			
								temp_chongzhi=temp_chongzhi+input[4]/10.0;//�����������ֺ�С�����ֵ��ܺ�
			
								temp_money=temp_chongzhi;//�����ȫ�ֱ�����
						
								TOUCH_GUI_DISP_chongzhi0(); 	 //ȷ��
								break;

			case 3:		if(ii>=4)	break;//��һ�����ֲ�����0����ֵ���ܳ���4λ��
								else if(a==1)//�Ѱ�С����
								{
									input[4]=0;
									ii=4;
									num++;
									LCD_ShowChar(10+8*num,50,'0',16,0);		 //0
									num++;
									LCD_ShowChar(10+8*num,50,'0',16,0);		 //0
									break;
								}
								
								else if(ii==0)	break;//��һ�����ֲ�����0����ֵ���ܳ���4λ��
								
								else
								{
									num++;
									input[ii]=0;
									ii++;
									LCD_ShowChar(10+8*num,50,'0',16,0);		 //0 
									break;
								}

			case 4:		if(ii>=4)	break;//��ֵ���ܳ���4λ��
								else if(a==1)//�Ѱ�С����
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

			case 5:		if(ii>=4)	break;//��ֵ���ܳ���4λ��
								else if(a==1)//�Ѱ�С����
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
								temp_chongzhi=0;//��ֵ���
								
								LCD_Fill(0,40,239,78,WHITE);			   		 //����
								break;

			case 7:		if(ii>=4)	break;//��ֵ���ܳ���4λ��
								else if(a==1)//�Ѱ�С����
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

			case 8:		if(ii>=4)	break;//��ֵ���ܳ���4λ��
								else if(a==1)//�Ѱ�С����
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

			case 9:		if(ii>=4)	break;//��ֵ���ܳ���4λ��
								else if(a==1)//�Ѱ�С����
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

			case 10:	if(ii>=4)	break;//��ֵ���ܳ���4λ��
								else if(a==1)//�Ѱ�С����
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

			case 11:	if(ii>=4)	break;//��ֵ���ܳ���4λ��
								else if(a==1)//�Ѱ�С����
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

			case 12:	if(ii>=4)	break;//��ֵ���ܳ���4λ��
								else if(a==1)//�Ѱ�С����
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

			case 13:	if(ii>=4)	break;//��ֵ���ܳ���4λ��
								else if(a==1)//�Ѱ�С����
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

			case 14:	if(a==1) break;//�ڶ��ΰ�С����
								else
								{
									num++;	
								
									for(a=0;a<ii;a++)
									{temp_chongzhi=temp_chongzhi+input[a]*Mult10(ii-a-1);}//������������
									a=1;
									length=ii;
									ii=0;
									
									LCD_ShowChar(10+8*num,50,'.',16,0);	     //.	
									break;
								}


			default:	break;
		}


		delay_ms(10);//ÿ��10ms��ѯһ�δ�����

// 		//LED��˸ָʾ������������,��ʱʱ�� = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}

//��ֵ���
void GUI_DISP_chongzhi0(void)      
{
	u8 i=0;
	
	POINT_COLOR=BLUE; 
	Show_Str(40,10,"��������㷵�ز˵���",16,0);
	Show_Str(90,10+50,"��ֵ���",16,0);
	Show_Str(100,120+30,"��Ԫ��",16,0);
	Show_Str(100,50+120+30,"��ſ�",16,0);

	
	//��ʾ��ֵ���
	POINT_COLOR=RED; 
	if(length == 0)	LCD_ShowNum(90-8,100,0,1,16);
	else
		for(i=0;i<length;i++)
			LCD_ShowNum(90+8*i,100,input[i],1,16);			//����
	LCD_ShowChar(90+8*length,100,'.',16,0);	     		//.	
	LCD_ShowNum(90+8*(length+1),100,input[4],1,16); //С��
	LCD_ShowNum(90+8*(length+2),100,0,1,16); 				//С��
	
}

//��ֵ����
void TOUCH_GUI_DISP_chongzhi0(void)		
{
	u8 key;
// 	u8 i=0;
	u8 ii=0;
	u8 j=0;
	u8 jj=0;
	u8 flag_exist=0;
	u8 locked=0;

// 	Touch_Init();	 //��ʼ�� 
	LCD_Clear(WHITE);//����

	GUI_DISP_chongzhi0(); 	 //��������

	while(1)
	{
		key=TOUCH_all();	     //��ȡ������ֵ
		
		switch(key)			     				 //��Ӧ��ֵ�Ĵ���
		{
			case 0:		GUI_DISP_chongzhi0();   				 //û�д����������£�һֱ��ʾ��������
								break;

			case 1:		InitAlldata();									 //��  ��  :  ��ʼ�����ж���������ݵ�����
								TOUCH_GUI_DISP_MENU(); 	         //���ز˵���
								break;


			default:	break;
		}
		
		
		
		if(flag_com==0)//���û�ж�������һֱ��ɨ��
		{
			Read_cardID(); //������
			Read_overage();//��������Ϣ
		}
		else //�Ѿ�������
		{
			AT24CXX_Read(0,&ii,1);		 //�ѵ�һ���ֽڵ����������������Ѵ洢�����ſ���
						
			for(j=0; j<ii; j++)				 //ѭ��������
			{
				AT24CXX_Read(1+j*11,datatemp,4);
				
				for(jj=0;jj<4;jj++)
				{
					if(cardID[jj] != datatemp[jj])
					{
						flag_exist=0;		
						goto L;				 //ֻҪ����һ������һ����������ѭ��
					}						
					else flag_exist=1;
				}
				
				L:
				if(flag_exist == 1)//���ڴ˿��ţ�������д�뿨��
				{
					temp_money=temp_money+Read_overage();//��ֵ���+�������
					write_overage(temp_money); //д�����������WriteData[]�����У�	
							
					TOUCH_GUI_DISP_chongzhi1();//��ʾ��ֵ���  
				}
			}
			
			//��������ڴ˿���
			if(ii < 20)//AT24C02�����Դ�20�ſ��Ŀ��ź�����
			{
				ii++;//��һ�ſ�
				AT24CXX_Write(0,&ii,1);//дii����һ���ֽڵĵ�ַ
				
				

				AT24CXX_Write(1+(ii-1)*11,cardID,4);//д���ţ�4���ֽڣ�
			
				
				locked=1;
				AT24CXX_Write((ii-1)*11+5,&locked,1);//������д1����ַ(ii-1)*11+5
				locked=0;
			}
			else TOUCH_GUI_DISP_chongzhi3();//��ֵʧ��	
			
		}	
	
		
// 		if(flag_com==0)//���û�ж�������һֱ��ɨ��
// 		{
// 			command_choose(0xa0);		
// 			RC522_work();					//��  ��  :  ÿ�������ζ�ʱ���жϣ���50ms����Բ�����������ѡ���жϣ�
// 		}
// 		else TOUCH_GUI_DISP_chongzhi1();//��ʾ��ֵ���  
		
		
		
		
		
		delay_ms(10);//ÿ��10ms��ѯһ�δ�����

// 		//LED��˸ָʾ������������,��ʱʱ�� = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}

//�ɹ�
void GUI_DISP_chongzhi1(void)      
{
	u8 ii=0;
	u8 flag=0;
	
	POINT_COLOR=BLUE; 
	Show_Str(40,10,"��������㷵�ز˵���",16,0);
	Show_Str(80,130,"��ֵ�ɹ���",16,0);
	
	
	
	Show_Str(10,220,"������Ԫ����",16,0);
	
// 	for(ii=16;ii>1;ii--)//ע�ⲻ��for(ii=15;ii>=0;ii--)����Ϊ��u8��ii�ݼ���0��ʱ���ٵݼ�Ҳ��0
// 		LCD_ShowNum(239-ii*8,220,WriteData[ii-1],1,16);//��ʾ��ֵ��ȥ��16������
	
	LCD_ShowNum(239-8,220,0,1,16);					 		//0
	LCD_ShowNum(239-8*2,220,WriteData[0],1,16); //��
	LCD_ShowChar(239-8*3,220,'.',16,0);	     		//.	
	
	if(WriteData[1] == 0)
			LCD_ShowNum(239-8*4,220,0,1,16);				//0
	
  for(ii=16;ii>1;ii--)//ע�ⲻ��for(ii=15;ii>=0;ii--)����Ϊ��u8��ii�ݼ���0��ʱ���ٵݼ�Ҳ��0
	{
		if(WriteData[ii-1] != 0)
		{
			flag=1;//���λ��Ϊ��ı�־				
		}
		
		if(flag)
			LCD_ShowNum(239-ii*8-8*2,220,WriteData[ii-1],1,16);//��ʾ������16������
	}
	
	
	
	//��ʾ�Ѵ洢�����ſ�
	AT24CXX_Read(0,&ii,1);		 		//�ѵ�һ���ֽڵ����������������Ѵ洢�����ſ���
	POINT_COLOR=RED; 
	Show_Str(50,70,"�Ѽ������Ŀ��",16,0);
	LCD_ShowNum(180,70,ii,1,16); //��ʾii��������
	ii=0;

}

//��ֵ����
void TOUCH_GUI_DISP_chongzhi1(void)		
{
	u8 key;
// 	u8 i=0;

// 	Touch_Init();	 //��ʼ�� 
	LCD_Clear(WHITE);//����

	GUI_DISP_chongzhi1(); 	 //��������

	while(1)
	{
		key=TOUCH_all();	   //��ȡ������ֵ
		
		switch(key)			     				 //��Ӧ��ֵ�Ĵ���
		{
			case 0:		GUI_DISP_chongzhi1();   				 //û�д����������£�һֱ��ʾ��������
								break;

			case 1:		InitAlldata();									 //��  ��  :  ��ʼ�����ж���������ݵ�����
								TOUCH_GUI_DISP_MENU(); 	         //���ز˵���
								break;


			default:	break;
		}
		
		
		delay_ms(10);//ÿ��10ms��ѯһ�δ�����

// 		//LED��˸ָʾ������������,��ʱʱ�� = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}

//ʧ��
void GUI_DISP_chongzhi2(void)     
{
	POINT_COLOR=BLUE; 
	Show_Str(40,10,"��������㷵�ز˵���",16,0);
	Show_Str(80,130,"��ֵʧ�ܣ�",16,0);
	Show_Str(10,200,"������Ԫ����",16,0);
}

//��ֵ����
void TOUCH_GUI_DISP_chongzhi2(void)		
{
	u8 key;
// 	u8 i=0;

// 	Touch_Init();	 //��ʼ�� 
	LCD_Clear(WHITE);//����

	GUI_DISP_chongzhi2(); 	 //��������

	while(1)
	{
		key=TOUCH_all();	   //��ȡ������ֵ
		
		switch(key)			     				 //��Ӧ��ֵ�Ĵ���
		{
			case 0:		GUI_DISP_chongzhi2();   				 //û�д����������£�һֱ��ʾ��������
								break;

			case 1:		InitAlldata();									 //��  ��  :  ��ʼ�����ж���������ݵ�����
								TOUCH_GUI_DISP_MENU(); 	         //���ز˵���
								break;


			default:	break;
		}

		
		delay_ms(10);//ÿ��10ms��ѯһ�δ�����

// 		//LED��˸ָʾ������������,��ʱʱ�� = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}

//ʧ��
void GUI_DISP_chongzhi3(void)     
{
	POINT_COLOR=BLUE; 
	Show_Str(40,10,"��������㷵�ز˵���",16,0);
	Show_Str(70,130,"�ѿ�ͨ20�ſ�",16,0);
	Show_Str(80,130,"��ֵʧ�ܣ�",16,0);
}

//��ֵ����
void TOUCH_GUI_DISP_chongzhi3(void)		
{
	u8 key;
// 	u8 i=0;

// 	Touch_Init();	 //��ʼ�� 
	LCD_Clear(WHITE);//����

	GUI_DISP_chongzhi3(); 	 //��������

	while(1)
	{
		key=TOUCH_all();	   //��ȡ������ֵ
		
		switch(key)			     				 //��Ӧ��ֵ�Ĵ���
		{
			case 0:		GUI_DISP_chongzhi3();   				 //û�д����������£�һֱ��ʾ��������
								break;

			case 1:		InitAlldata();									 //��  ��  :  ��ʼ�����ж���������ݵ�����
								TOUCH_GUI_DISP_MENU(); 	         //���ز˵���
								break;


			default:	break;
		}

		
		delay_ms(10);//ÿ��10ms��ѯһ�δ�����

// 		//LED��˸ָʾ������������,��ʱʱ�� = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}













/***********************************
        ������ʾ��������
***********************************/
void GUI_DISP_xiaofei(void)      
{
	POINT_COLOR=BLACK; 
	LCD_DrawLine(0, 39, 239, 39);					//��
	LCD_DrawLine(0, 79, 239, 79);					//��
	LCD_DrawLine(0, 79+60, 239, 79+60);		//��
	LCD_DrawLine(0, 79+120, 239, 79+120);	//��
	LCD_DrawLine(0, 79+180, 239, 79+180);	//��
	LCD_DrawLine(59, 79+60, 59, 319);			//��
	LCD_DrawLine(119, 79, 119, 319);			//��
	LCD_DrawLine(179, 79+60, 179, 319);		//��
	
	POINT_COLOR=BLUE; 
	Show_Str(60,10,"����/��λ��Ԫ��",16,0);
	Show_Str(20,10+40+60-5,"���ز˵���",16,0);
	Show_Str(120+45,10+40+60-5,"ȷ��",16,0);
	Show_Str(180+10+5,10+40+60+60-5,"����",16,0);
	
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

//��ֵ����
u8 TOUCH_DISP_xiaofei(void)			 		
{
	//ɨ�败����
	if(Pen_Point.Key_Sta==Key_Down)//������������
	{
			Pen_Int_Set(0);//�ر��ж�

			Convert_Pos();//ת����������ݴ�������У׼����������ת����Ľ��,������X0,Y0��
			Pen_Point.Key_Sta=Key_Up;

			if(Pen_Point.X0>0&&Pen_Point.X0<119&&Pen_Point.Y0>79&&Pen_Point.Y0<139)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(0,79,119,139,BLACK);//���鴥������
				}
				LCD_Fill(0,79,119,139,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 1;
			}
			else if(Pen_Point.X0>119&&Pen_Point.X0<239&&Pen_Point.Y0>79&&Pen_Point.Y0<139) 
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(119,79,239,139,BLACK);//���鴥������
				}
				LCD_Fill(119,79,239,139,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 2;
			}
			
			
			
			else if(Pen_Point.X0>0&&Pen_Point.X0<59&&Pen_Point.Y0>139&&Pen_Point.Y0<199)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(0,139,59,199,BLACK);//���鴥������
				}
				LCD_Fill(0,139,59,199,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 3;
			}
			else if(Pen_Point.X0>59&&Pen_Point.X0<119&&Pen_Point.Y0>139&&Pen_Point.Y0<199)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(59,139,119,199,BLACK);//���鴥������
				}
				LCD_Fill(59,139,119,199,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 4;
			}
			else if(Pen_Point.X0>119&&Pen_Point.X0<179&&Pen_Point.Y0>139&&Pen_Point.Y0<199)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(119,139,179,199,BLACK);//���鴥������
				}
				LCD_Fill(119,139,179,199,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 5;
			}
			else if(Pen_Point.X0>179&&Pen_Point.X0<239&&Pen_Point.Y0>139&&Pen_Point.Y0<199)
			{  	
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(179,139,239,199,BLACK);//���鴥������
				}
				LCD_Fill(179,139,239,199,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 6;
			}

			
			else if(Pen_Point.X0>0&&Pen_Point.X0<59&&Pen_Point.Y0>199&&Pen_Point.Y0<259)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(0,199,59,259,BLACK);//���鴥������
				}
				LCD_Fill(0,199,59,259,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 7;
			}
			else if(Pen_Point.X0>59&&Pen_Point.X0<119&&Pen_Point.Y0>199&&Pen_Point.Y0<259)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(59,199,119,259,BLACK);//���鴥������
				}
				LCD_Fill(59,199,119,259,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 8;
			}
			else if(Pen_Point.X0>119&&Pen_Point.X0<179&&Pen_Point.Y0>199&&Pen_Point.Y0<259)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(119,199,179,259,BLACK);//���鴥������
				}
				LCD_Fill(119,199,179,259,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 9;
			}
			else if(Pen_Point.X0>179&&Pen_Point.X0<239&&Pen_Point.Y0>199&&Pen_Point.Y0<259)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(179,199,239,259,BLACK);//���鴥������
				}
				LCD_Fill(179,199,239,259,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 10;
			}

			
			else if(Pen_Point.X0>0&&Pen_Point.X0<59&&Pen_Point.Y0>259&&Pen_Point.Y0<319)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(0,259,59,319,BLACK);//���鴥������
				}
				LCD_Fill(0,259,59,319,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 11;
			}
			else if(Pen_Point.X0>59&&Pen_Point.X0<119&&Pen_Point.Y0>259&&Pen_Point.Y0<319)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(59,259,119,319,BLACK);//���鴥������
				}
				LCD_Fill(59,259,119,319,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 12;
			}
			else if(Pen_Point.X0>119&&Pen_Point.X0<179&&Pen_Point.Y0>259&&Pen_Point.Y0<319)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(119,259,179,319,BLACK);//���鴥������
				}
				LCD_Fill(119,259,179,319,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 13;
			}
			else if(Pen_Point.X0>179&&Pen_Point.X0<239&&Pen_Point.Y0>259&&Pen_Point.Y0<319)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(179,259,239,319,BLACK);//���鴥������
				}
				LCD_Fill(179,259,239,319,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 14;
			}

		Pen_Int_Set(1);//�����ж�
	}

//	delay_ms(10);//ÿ��10ms��ѯһ�δ�����
	return 0;	 //û�д�����������


//	//LED��˸ָʾ������������,��ʱʱ�� = delay_ms(10)*50 = 500ms
//	i++;     
//	if(i==50)
//	{
//		i=0;
//		LED0=!LED0;
//	}	
}

//��ֵ����
void TOUCH_GUI_DISP_xiaofei(void)		
{
	u8 key;
// 	u8 i=0;
	u8 num=0;

	u8 ii=0;
	u8 a=0;
	double temp_xiaofei=0;//���ѽ��
	
	length=0;
	input[0]=0;input[1]=0;input[2]=0;input[3]=0;input[4]=0;
	
// 	Touch_Init();	 //��ʼ�� 
	LCD_Clear(WHITE);//����

	GUI_DISP_xiaofei(); 	 //��������

	while(1)
	{
		key=TOUCH_DISP_xiaofei();	   //��ȡ������ֵ
		
		switch(key)			     				 //��Ӧ��ֵ�Ĵ���
		{
			case 0:		GUI_DISP_xiaofei();   				   //û�д����������£�һֱ��ʾ��������
								break;

			case 1:		TOUCH_GUI_DISP_MENU(); 	         //���ز˵���
								break;

			case 2:		InitAlldata();								   //��ʼ�����ж���������ݵ�����
				
								temp_xiaofei=temp_xiaofei+input[4]/10.0;//�����������ֺ�С�����ֵ��ܺ�
								temp_money=temp_xiaofei;//�����ȫ�ֱ�����

								TOUCH_GUI_DISP_xiaofei0(); 		   //ȷ��
								break;

			case 3:		if(ii>=4)	break;//��һ�����ֲ�����0�����ѽ��ܳ���4λ��
								else if(a==1)//�Ѱ�С����
								{
									input[4]=0;
									ii=4;
									num++;
									LCD_ShowChar(10+8*num,50,'0',16,0);		 //0
									num++;
									LCD_ShowChar(10+8*num,50,'0',16,0);		 //0
									break;
								}
								
								else if(ii==0)	break;//��һ�����ֲ�����0�����ѽ��ܳ���4λ��
								
								else
								{
									num++;
									input[ii]=0;
									ii++;
									LCD_ShowChar(10+8*num,50,'0',16,0);		 //0 
									break;
								}

			case 4:		if(ii>=4)	break;//���ѽ��ܳ���4λ��
								else if(a==1)//�Ѱ�С����
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

			case 5:		if(ii>=4)	break;//���ѽ��ܳ���4λ��
								else if(a==1)//�Ѱ�С����
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
								temp_xiaofei=0;//��ֵ���
								
								LCD_Fill(0,40,239,78,WHITE);			   		 //����
								break;

			case 7:		if(ii>=4)	break;//���ѽ��ܳ���4λ��
								else if(a==1)//�Ѱ�С����
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

			case 8:		if(ii>=4)	break;//���ѽ��ܳ���4λ��
								else if(a==1)//�Ѱ�С����
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

			case 9:		if(ii>=4)	break;//���ѽ��ܳ���4λ��
								else if(a==1)//�Ѱ�С����
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

			case 10:	if(ii>=4)	break;//���ѽ��ܳ���4λ��
								else if(a==1)//�Ѱ�С����
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

			case 11:	if(ii>=4)	break;//���ѽ��ܳ���4λ��
								else if(a==1)//�Ѱ�С����
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

			case 12:	if(ii>=4)	break;//���ѽ��ܳ���4λ��
								else if(a==1)//�Ѱ�С����
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

			case 13:	if(ii>=4)	break;//���ѽ��ܳ���4λ��
								else if(a==1)//�Ѱ�С����
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

			case 14:	if(a==1) break;//�ڶ��ΰ�С����
								else
								{
									num++;	
								
									for(a=0;a<ii;a++)
									{temp_xiaofei=temp_xiaofei+input[a]*Mult10(ii-a-1);}//������������
									a=1;
									length=ii;
									ii=0;
									
									LCD_ShowChar(10+8*num,50,'.',16,0);	     //.	
									break;
								}


			default:	break;
		}



		delay_ms(10);//ÿ��10ms��ѯһ�δ�����

// 		//LED��˸ָʾ������������,��ʱʱ�� = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}

//���ѽ��
void GUI_DISP_xiaofei0(void)    
{
	u8 i=0;
	
	POINT_COLOR=BLUE; 
	Show_Str(40,10,"��������㷵�ز˵���",16,0);
	Show_Str(90,10+50,"���ѽ��",16,0);
	Show_Str(100,120+30,"��Ԫ��",16,0);
	Show_Str(100,50+120+30,"��ſ�",16,0);
	
	
	//��ʾ���ѽ��
	POINT_COLOR=RED; 
	if(length == 0)	LCD_ShowNum(90-8,100,0,1,16);
	else
		for(i=0;i<length;i++)
			LCD_ShowNum(90+8*i,100,input[i],1,16);			//����
	LCD_ShowChar(90+8*length,100,'.',16,0);	     		//.	
	LCD_ShowNum(90+8*(length+1),100,input[4],1,16); //С��
	LCD_ShowNum(90+8*(length+2),100,0,1,16); 				//С��	
}

//��ֵ����
void TOUCH_GUI_DISP_xiaofei0(void)		
{
	u8 key;
// 	u8 i=0;
	u8 ii=0;
	u8 j=0;
	u8 jj=0;
	u8 flag_exist=0;
	u8 locked=0;

// 	Touch_Init();	 //��ʼ�� 
	LCD_Clear(WHITE);//����

	GUI_DISP_xiaofei0(); 	 //��������

	while(1)
	{
		key=TOUCH_all();	   //��ȡ������ֵ
		
		switch(key)			     				 //��Ӧ��ֵ�Ĵ���
		{
			case 0:		GUI_DISP_xiaofei0();   				   //û�д����������£�һֱ��ʾ��������
								break;

			case 1:		InitAlldata();									 //��  ��  :  ��ʼ�����ж���������ݵ�����
								TOUCH_GUI_DISP_MENU(); 	         //���ز˵���
								break;


			default:	break;
		}

				
		if(flag_com==0)//���û�ж�������һֱ��ɨ��
		{
			Read_cardID(); //������
			Read_overage();//��������Ϣ
		}
		else //�Ѿ���������������д�뿨��
		{
			AT24CXX_Read(0,&ii,1);		 //�ѵ�һ���ֽڵ����������������Ѵ洢�����ſ���		
						
			for(j=0; j<ii; j++)				 //ѭ��������
			{
				AT24CXX_Read(1+j*11,datatemp,4);
				
				for(jj=0;jj<4;jj++)
				{
					if(cardID[jj] != datatemp[jj])
					{
						flag_exist=0;		
						goto L;				 //ֻҪ����һ������һ����������ѭ��
					}						
					else flag_exist=1;
				}
				
				L:
				if(flag_exist == 1)//���ڴ˿��ţ�������д�뿨��
				{
					AT24CXX_Read(j*11+5,&locked,1);//��������״̬��0����  1����
					
					if(locked)//����
					{
						if(Read_overage() >= temp_money)
						{
							temp_money=Read_overage()-temp_money;//�������-���ѽ��
							write_overage(temp_money);//д�����������WriteData[]�����У�	
								
							TOUCH_GUI_DISP_xiaofei1();//��ʾ���ѽ��  
						}
						else TOUCH_GUI_DISP_xiaofei2();//����ʧ�ܣ�����ʾ���㣩
					}
					else TOUCH_GUI_DISP_xiaofei4();	 //δ���������˿��ѹ�ʧ��																
				}								
			}
			
			//ѭ�������ţ�û�ҵ��˿�
			TOUCH_GUI_DISP_xiaofei3();		 			 //�����ڴ˿������˿�δ���
		}	
		
		
		
// 		if(flag_com==0)//���û�ж�������һֱ��ɨ��
// 		{
// 			Read_overage();//����
// 		}
// 		else //�Ѿ���������������д�뿨��
// 		{
// 			if(Read_overage() >= temp_money)
// 			{
// 				temp_money=Read_overage()-temp_money;//�������-���ѽ��
// 				write_overage(temp_money);//д�����������WriteData[]�����У�	
// 					
// 				TOUCH_GUI_DISP_xiaofei1();//��ʾ���ѽ��  
// 			}
// 			else TOUCH_GUI_DISP_xiaofei2();//����ʧ�ܣ�

// 		}	
		

		
		delay_ms(10);//ÿ��10ms��ѯһ�δ�����

// 		//LED��˸ָʾ������������,��ʱʱ�� = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}

//�ɹ�
void GUI_DISP_xiaofei1(void)     
{
	u8 ii=0;
	u8 flag=0;
	
	POINT_COLOR=BLUE; 
	Show_Str(40,10,"��������㷵�ز˵���",16,0);
	Show_Str(80,130,"���ѳɹ���",16,0);
	
	
	
	Show_Str(10,220,"������Ԫ����",16,0);
	
// 	for(ii=16;ii>1;ii--)//ע�ⲻ��for(ii=15;ii>=0;ii--)����Ϊ��u8��ii�ݼ���0��ʱ���ٵݼ�Ҳ��0
// 		LCD_ShowNum(239-ii*8,220,WriteData[ii-1],1,16);//��ʾ��ֵ��ȥ��16������
	
	LCD_ShowNum(239-8,220,0,1,16);					 		//0
	LCD_ShowNum(239-8*2,220,WriteData[0],1,16); //��
	LCD_ShowChar(239-8*3,220,'.',16,0);	     		//.	
	
	if(WriteData[1] == 0)
			LCD_ShowNum(239-8*4,220,0,1,16);				//0
	
  for(ii=16;ii>1;ii--)//ע�ⲻ��for(ii=15;ii>=0;ii--)����Ϊ��u8��ii�ݼ���0��ʱ���ٵݼ�Ҳ��0
	{
		if(WriteData[ii-1] != 0)
		{
			flag=1;//���λ��Ϊ��ı�־				
		}
		
		if(flag)
			LCD_ShowNum(239-ii*8-8*2,220,WriteData[ii-1],1,16);//��ʾ������16������
	}	
	
}

//��ֵ����
void TOUCH_GUI_DISP_xiaofei1(void)		
{
	u8 key;
// 	u8 i=0;

// 	Touch_Init();	 //��ʼ�� 
	LCD_Clear(WHITE);//����

	GUI_DISP_xiaofei1(); 	 //��������

	while(1)
	{
		key=TOUCH_all();	   //��ȡ������ֵ
		
		switch(key)			     				 //��Ӧ��ֵ�Ĵ���
		{
			case 0:		GUI_DISP_xiaofei1();   				 //û�д����������£�һֱ��ʾ��������
								break;

			case 1:		InitAlldata();									 //��  ��  :  ��ʼ�����ж���������ݵ�����
								TOUCH_GUI_DISP_MENU(); 	         //���ز˵���
								break;


			default:	break;
		}

		
		delay_ms(10);//ÿ��10ms��ѯһ�δ�����

// 		//LED��˸ָʾ������������,��ʱʱ�� = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}

//ʧ�ܣ���ʾ���㣩
void GUI_DISP_xiaofei2(void)    
{
	u8 ii=0;
	u8 flag=0;
	
	POINT_COLOR=BLUE; 
	Show_Str(40,10,"��������㷵�ز˵���",16,0);
	Show_Str(70,70,"��������",16,0);
	Show_Str(80,130,"����ʧ�ܣ�",16,0);
	
	
	
	
	Show_Str(10,220,"������Ԫ����",16,0);
		
// 	for(ii=16;ii>1;ii--)//ע�ⲻ��for(ii=15;ii>=0;ii--)����Ϊ��u8��ii�ݼ���0��ʱ���ٵݼ�Ҳ��0
// 		LCD_ShowNum(239-ii*8,220,Read_Data[ii-1],1,16);//��ʾ��ֵ��ȥ��16������
	
	LCD_ShowNum(239-8,220,0,1,16);					 		//0
	LCD_ShowNum(239-8*2,220,Read_Data[0],1,16); //��
	LCD_ShowChar(239-8*3,220,'.',16,0);	     		//.	
	
	if(Read_Data[1] == 0)
			LCD_ShowNum(239-8*4,220,0,1,16);				//0
	
  for(ii=16;ii>1;ii--)//ע�ⲻ��for(ii=15;ii>=0;ii--)����Ϊ��u8��ii�ݼ���0��ʱ���ٵݼ�Ҳ��0
	{
		if(Read_Data[ii-1] != 0)
		{
			flag=1;//���λ��Ϊ��ı�־				
		}
		
		if(flag)
			LCD_ShowNum(239-ii*8-8*2,220,Read_Data[ii-1],1,16);//��ʾ������16������
	}	
}

//��ֵ����
void TOUCH_GUI_DISP_xiaofei2(void)		
{
	u8 key;
// 	u8 i=0;

// 	Touch_Init();	 //��ʼ�� 
	LCD_Clear(WHITE);//����

	GUI_DISP_xiaofei2(); 	 //��������

	while(1)
	{
		key=TOUCH_all();	   //��ȡ������ֵ
		
		switch(key)			     				 //��Ӧ��ֵ�Ĵ���
		{
			case 0:		GUI_DISP_xiaofei2();   				   //û�д����������£�һֱ��ʾ��������
								break;

			case 1:		InitAlldata();									 //��  ��  :  ��ʼ�����ж���������ݵ�����
								TOUCH_GUI_DISP_MENU(); 	         //���ز˵���
								break;


			default:	break;
		}

		
		delay_ms(10);//ÿ��10ms��ѯһ�δ�����

// 		//LED��˸ָʾ������������,��ʱʱ�� = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}

//�����ڴ˿������˿�δ���
void GUI_DISP_xiaofei3(void)
{
	POINT_COLOR=BLUE; 
	Show_Str(40,10,"��������㷵�ز˵���",16,0);
	Show_Str(70,70,"�˿�δ����",16,0);
	Show_Str(80,130,"����ʧ�ܣ�",16,0);
}

//��ֵ����
void TOUCH_GUI_DISP_xiaofei3(void)		
{
	u8 key;
// 	u8 i=0;

// 	Touch_Init();	 //��ʼ�� 
	LCD_Clear(WHITE);//����

	GUI_DISP_xiaofei3(); 	 //��������

	while(1)
	{
		key=TOUCH_all();	   //��ȡ������ֵ
		
		switch(key)			     				 //��Ӧ��ֵ�Ĵ���
		{
			case 0:		GUI_DISP_xiaofei3();   				   //û�д����������£�һֱ��ʾ��������
								break;

			case 1:		InitAlldata();									 //��  ��  :  ��ʼ�����ж���������ݵ�����
								TOUCH_GUI_DISP_MENU(); 	         //���ز˵���
								break;


			default:	break;
		}

		
		delay_ms(10);//ÿ��10ms��ѯһ�δ�����

// 		//LED��˸ָʾ������������,��ʱʱ�� = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}

//δ���������˿��ѹ�ʧ��
void GUI_DISP_xiaofei4(void)
{
	POINT_COLOR=BLUE; 
	Show_Str(40,10,"��������㷵�ز˵���",16,0);
	Show_Str(70,70,"�˿��ѹ�ʧ",16,0);
	Show_Str(80,130,"����ʧ�ܣ�",16,0);
}

//��ֵ����
void TOUCH_GUI_DISP_xiaofei4(void)		
{
	u8 key;
// 	u8 i=0;

// 	Touch_Init();	 //��ʼ�� 
	LCD_Clear(WHITE);//����

	GUI_DISP_xiaofei4(); 	 //��������

	while(1)
	{
		key=TOUCH_all();	   //��ȡ������ֵ
		
		switch(key)			     				 //��Ӧ��ֵ�Ĵ���
		{
			case 0:		GUI_DISP_xiaofei4();   				   //û�д����������£�һֱ��ʾ��������
								break;

			case 1:		InitAlldata();									 //��  ��  :  ��ʼ�����ж���������ݵ�����
								TOUCH_GUI_DISP_MENU(); 	         //���ز˵���
								break;


			default:	break;
		}

		
		delay_ms(10);//ÿ��10ms��ѯһ�δ�����

// 		//LED��˸ָʾ������������,��ʱʱ�� = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}
















/***********************************
        ��ѯ��ʾ��������
***********************************/
void GUI_DISP_chaxun(void)       
{	
	POINT_COLOR=BLUE; 
	Show_Str(70,50,"��ѯ������Ϣ",16,0);
	Show_Str(100,120,"��ſ�",16,0);
	Show_Str(40,50+120+30,"��������㷵�ز˵���",16,0);
}

//��ֵ����
u8 TOUCH_all(void)			 		
{
	//ɨ�败����
	if(Pen_Point.Key_Sta==Key_Down)//������������
	{
			Pen_Int_Set(0);//�ر��ж�

			Convert_Pos();//ת����������ݴ�������У׼����������ת����Ľ��,������X0,Y0��
			Pen_Point.Key_Sta=Key_Up;

			if(Pen_Point.X0>0&&Pen_Point.X0<239&&Pen_Point.Y0>0&&Pen_Point.Y0<319)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(0,0,239,319,BLACK);//���鴥������
				}
				LCD_Fill(0,0,239,319,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 1;
			}

		Pen_Int_Set(1);//�����ж�
	}

//	delay_ms(10);//ÿ��10ms��ѯһ�δ�����
	return 0;	 //û�д�����������


//	//LED��˸ָʾ������������,��ʱʱ�� = delay_ms(10)*50 = 500ms
//	i++;     
//	if(i==50)
//	{
//		i=0;
//		LED0=!LED0;
//	}	
}

//��ֵ����
void TOUCH_GUI_DISP_chaxun(void)		
{
	u8 key;
// 	u8 i=0;

// 	Touch_Init();	 //��ʼ�� 
	LCD_Clear(WHITE);//����

	GUI_DISP_chaxun(); 	 //��������

	while(1)
	{
		key=TOUCH_all();	   //��ȡ������ֵ
		
		switch(key)			     				 //��Ӧ��ֵ�Ĵ���
		{
			case 0:		GUI_DISP_chaxun();   				     //û�д����������£�һֱ��ʾ��������
								break;

			case 1:		InitAlldata();									 //��  ��  :  ��ʼ�����ж���������ݵ�����
								TOUCH_GUI_DISP_MENU(); 	         //���ز˵���
								break;


			default:	break;
		}

		
		if(flag_com==0)//���û�ж�������һֱ��ɨ��
		{
			Read_cardID();//������
			Read_overage();//���������
		}
		else TOUCH_GUI_DISP_chaxun0();//��ʾ��ѯ���  
				
						
		
		delay_ms(10);//ÿ��10ms��ѯһ�δ�����

// 		//LED��˸ָʾ������������,��ʱʱ�� = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}

//��ѯ���
void GUI_DISP_chaxun0(void)      
{
	u8 ii=0;
	u8 flag=0;
	u8 administrator_flag=0;
	
	POINT_COLOR=BLUE; 
	Show_Str(40,10,"��������㷵�ز˵���",16,0);
	Show_Str(90,50,"������Ϣ",16,0);
	Show_Str(10,120,"������***",16,0);
	Show_Str(10,150,"ѧ�ţ�***",16,0);
	
	
	for(ii=0;ii<4;ii++)
	{
		if(cardID[ii] != administrator[ii])
		{
			administrator_flag=0; //���ǹ���Ա����
			goto L2;							//ֻҪ����һλ���Ų�һ��
		}		
		else administrator_flag=1;
	}
	
	L2:
	if(administrator_flag)
	{	
		POINT_COLOR=RED; 
		Show_Str(10,90,"��ݣ�����Ա",16,0);
	}
	else 
	{
		POINT_COLOR=RED; 
		Show_Str(10,90,"��ݣ��ǹ���Ա",16,0);
	}

	switch(card_status)
	{
		case 1:	//�����ڴ˿������˿�δ���
						Show_Str(150,90,"�˿�δ����",16,0);
						break;
		
		case 2:	//δ���������˿��ѹ�ʧ��	
						Show_Str(150,90,"�˿�δ����",16,0);
						break;
		
		case 3:	//�ѽ���
						Show_Str(150,90,"�˿��ѽ���",16,0);
						break;
		
		
		default:break;
	}
	
	
	
	POINT_COLOR=BLUE; 
	Show_Str(10,180,"���ţ�",16,0);
	
	for(ii=0;ii<4;ii++)//��ʾ���ţ��磺������0x34 0xb2 0x30 0xeb ��ʾ�� 052 178 030 235��
	{
		if(cardID[ii] >= 100)
			LCD_ShowNum(60+ii*8*3,180,cardID[ii],3,16);//��ʾID��3λ10��������
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
	
	
	
	
	Show_Str(10,220,"������Ԫ����",16,0);
	
	LCD_ShowNum(239-8,220,0,1,16);					 		//0
	LCD_ShowNum(239-8*2,220,Read_Data[0],1,16); //��
	LCD_ShowChar(239-8*3,220,'.',16,0);	     		//.	
	
	if(Read_Data[1] == 0)
			LCD_ShowNum(239-8*4,220,0,1,16);				//0
	
  for(ii=16;ii>1;ii--)//ע�ⲻ��for(ii=15;ii>=0;ii--)����Ϊ��u8��ii�ݼ���0��ʱ���ٵݼ�Ҳ��0
	{
		if(Read_Data[ii-1] != 0)
		{
			flag=1;//���λ��Ϊ��ı�־				
		}
		
		if(flag)
			LCD_ShowNum(239-ii*8-8*2,220,Read_Data[ii-1],1,16);//��ʾ������16������
	}
}

//��ֵ����
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

// 	Touch_Init();	 //��ʼ�� 
	LCD_Clear(WHITE);//����

	GUI_DISP_chaxun0(); 	 //��������

	while(1)
	{
		key=TOUCH_all();	   //��ȡ������ֵ
		
		switch(key)			     				 //��Ӧ��ֵ�Ĵ���
		{
			case 0:		GUI_DISP_chaxun0();   				   //û�д����������£�һֱ��ʾ��������
								break;

			case 1:		InitAlldata();									 //��  ��  :  ��ʼ�����ж���������ݵ�����
								TOUCH_GUI_DISP_MENU(); 	         //���ز˵���
								break;


			default:	break;
		}

		
		
		if(card_status == 0)
		{
			AT24CXX_Read(0,&ii,1);		 //�ѵ�һ���ֽڵ����������������Ѵ洢�����ſ���		
						
			for(j=0; j<ii; j++)				 //ѭ��������
			{
				AT24CXX_Read(1+j*11,datatemp,4);
				
				for(jj=0;jj<4;jj++)
				{
					if(cardID[jj] != datatemp[jj])
					{
						flag_exist=0;		
						goto L;				 //ֻҪ����һ������һ����������ѭ��
					}						
					else flag_exist=1;
				}
				
				L:
				if(flag_exist == 1)//���ڴ˿��ţ�������д�뿨��
				{
					AT24CXX_Read(j*11+5,&locked,1);//��������״̬��0����  1����
					
					if(locked)
					{
						card_status=3;		 //�ѽ���
						goto L3;
					}
					else 
					{
						card_status=2;	  //δ���������˿��ѹ�ʧ��
						goto L3;
					}																
				}								
			}
			
			//ѭ�������ţ�û�ҵ��˿�
			card_status=1;		 			 //�����ڴ˿������˿�δ���
		}
		
	
		L3:
		
			
		delay_ms(10);//ÿ��10ms��ѯһ�δ�����

// 		//LED��˸ָʾ������������,��ʱʱ�� = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}














/***********************************
       ��ʧ/�����ʾ��������
***********************************/
void GUI_DISP_guashijiegua(void) 
{
	POINT_COLOR=BLACK; 
	LCD_DrawLine(0, 39, 180, 39);					//��
	LCD_DrawLine(0, 79, 239, 79);					//��
	LCD_DrawLine(0, 79+60, 239, 79+60);		//��
	LCD_DrawLine(0, 79+120, 239, 79+120);	//��
	LCD_DrawLine(0, 79+180, 239, 79+180);	//��
	LCD_DrawLine(80, 0, 80, 79);					//��
	LCD_DrawLine(180, 0, 180, 79);				//��
	LCD_DrawLine(59, 79+60, 59, 319);			//��
	LCD_DrawLine(119, 79, 119, 319);			//��
	LCD_DrawLine(179, 79+60, 179, 319);		//��
	
	POINT_COLOR=BLUE; 
	Show_Str(10,10,"���ţ�",16,0);
	Show_Str(10,10+40,"���룺",16,0);
	Show_Str(20,10+40+60-5,"���ز˵���",16,0);
	Show_Str(120+45,10+40+60-5,"ȷ��",16,0);
	Show_Str(180+10+5,10+40+60+60-5,"����",16,0);
	Show_Str(180+10+5,10+40+60+60+60-5,"���",16,0);
	Show_Str(200-5,10+20,"��ʧ",16,0);
	
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

//��ֵ����
u8 TOUCH_DISP_guashijiegua(void)			 		
{
	//ɨ�败����
	if(Pen_Point.Key_Sta==Key_Down)//������������
	{
			Pen_Int_Set(0);//�ر��ж�

			Convert_Pos();//ת����������ݴ�������У׼����������ת����Ľ��,������X0,Y0��
			Pen_Point.Key_Sta=Key_Up;

			if(Pen_Point.X0>0&&Pen_Point.X0<119&&Pen_Point.Y0>79&&Pen_Point.Y0<139)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(0,79,119,139,BLACK);//���鴥������
				}
				LCD_Fill(0,79,119,139,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 1;
			}
			else if(Pen_Point.X0>119&&Pen_Point.X0<239&&Pen_Point.Y0>79&&Pen_Point.Y0<139) 
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(119,79,239,139,BLACK);//���鴥������
				}
				LCD_Fill(119,79,239,139,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 2;
			}
			
			
			
			else if(Pen_Point.X0>0&&Pen_Point.X0<59&&Pen_Point.Y0>139&&Pen_Point.Y0<199)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(0,139,59,199,BLACK);//���鴥������
				}
				LCD_Fill(0,139,59,199,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 3;
			}
			else if(Pen_Point.X0>59&&Pen_Point.X0<119&&Pen_Point.Y0>139&&Pen_Point.Y0<199)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(59,139,119,199,BLACK);//���鴥������
				}
				LCD_Fill(59,139,119,199,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 4;
			}
			else if(Pen_Point.X0>119&&Pen_Point.X0<179&&Pen_Point.Y0>139&&Pen_Point.Y0<199)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(119,139,179,199,BLACK);//���鴥������
				}
				LCD_Fill(119,139,179,199,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 5;
			}
			else if(Pen_Point.X0>179&&Pen_Point.X0<239&&Pen_Point.Y0>139&&Pen_Point.Y0<199)
			{  	
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(179,139,239,199,BLACK);//���鴥������
				}
				LCD_Fill(179,139,239,199,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 6;
			}

			
			else if(Pen_Point.X0>0&&Pen_Point.X0<59&&Pen_Point.Y0>199&&Pen_Point.Y0<259)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(0,199,59,259,BLACK);//���鴥������
				}
				LCD_Fill(0,199,59,259,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 7;
			}
			else if(Pen_Point.X0>59&&Pen_Point.X0<119&&Pen_Point.Y0>199&&Pen_Point.Y0<259)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(59,199,119,259,BLACK);//���鴥������
				}
				LCD_Fill(59,199,119,259,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 8;
			}
			else if(Pen_Point.X0>119&&Pen_Point.X0<179&&Pen_Point.Y0>199&&Pen_Point.Y0<259)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(119,199,179,259,BLACK);//���鴥������
				}
				LCD_Fill(119,199,179,259,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 9;
			}
			else if(Pen_Point.X0>179&&Pen_Point.X0<239&&Pen_Point.Y0>199&&Pen_Point.Y0<259)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(179,199,239,259,BLACK);//���鴥������
				}
				LCD_Fill(179,199,239,259,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 10;
			}

			
			else if(Pen_Point.X0>0&&Pen_Point.X0<59&&Pen_Point.Y0>259&&Pen_Point.Y0<319)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(0,259,59,319,BLACK);//���鴥������
				}
				LCD_Fill(0,259,59,319,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 11;
			}
			else if(Pen_Point.X0>59&&Pen_Point.X0<119&&Pen_Point.Y0>259&&Pen_Point.Y0<319)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(59,259,119,319,BLACK);//���鴥������
				}
				LCD_Fill(59,259,119,319,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 12;
			}
			else if(Pen_Point.X0>119&&Pen_Point.X0<179&&Pen_Point.Y0>259&&Pen_Point.Y0<319)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(119,259,179,319,BLACK);//���鴥������
				}
				LCD_Fill(119,259,179,319,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 13;
			}
			else if(Pen_Point.X0>179&&Pen_Point.X0<239&&Pen_Point.Y0>259&&Pen_Point.Y0<319)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(179,259,239,319,BLACK);//���鴥������
				}
				LCD_Fill(179,259,239,319,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 14;
			}
			else if(Pen_Point.X0>180&&Pen_Point.X0<239&&Pen_Point.Y0>0&&Pen_Point.Y0<79)
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(180,0,239,79,BLACK);//���鴥������
				}
				LCD_Fill(180,0,239,79,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 15;
			}

		Pen_Int_Set(1);//�����ж�
	}

//	delay_ms(10);//ÿ��10ms��ѯһ�δ�����
	return 0;	 //û�д�����������


//	//LED��˸ָʾ������������,��ʱʱ�� = delay_ms(10)*50 = 500ms
//	i++;     
//	if(i==50)
//	{
//		i=0;
//		LED0=!LED0;
//	}	
}

//��ֵ����
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
	
// 	Touch_Init();	 //��ʼ�� 
	LCD_Clear(WHITE);//����

	GUI_DISP_guashijiegua(); 	 //��������

	while(1)
	{
		key=TOUCH_DISP_guashijiegua();	 //��ȡ������ֵ
		
		switch(key)			     				 		 //��Ӧ��ֵ�Ĵ���
		{
			case 0:		GUI_DISP_guashijiegua();   				   //û�д����������£�һֱ��ʾ��������
								break;

			case 1:		TOUCH_GUI_DISP_MENU(); 	       			 //���ز˵���
								break;

			case 2:		flag=1;															 //ȷ��
								num=0;		 
								ii=0;
								a++;
								break;

			case 3:		if(ii == 1)	break;//���꿨�ŵı�־
			
								if(a >= 2)	break;//���������ȷ���ı�־
							
								if(num>=12)	//���Ų��ܳ���6λ��
								{
									ii=1;
									
									break;
								}
								if(num>=6) //���벻�ܳ���6λ��
								{
									if(a == 1)//���꿨��֮����һ��ȷ��
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
							
								if(num>=12)	//���Ų��ܳ���6λ��
								{
									ii=1;
									
									break;
								}
								if(num>=6) //���벻�ܳ���6λ��
								{
									if(a == 1)//���꿨��֮����һ��ȷ��
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
							
								if(num>=12)	//���Ų��ܳ���6λ��
								{
									ii=1;
									
									break;
								}
								if(num>=6) //���벻�ܳ���6λ��
								{
									if(a == 1)//���꿨��֮����һ��ȷ��
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
								
								//����
								if(flag==0)	
								{
									card_num[0]=0;card_num[1]=0;card_num[2]=0;card_num[3]=0;card_num[4]=0;card_num[5]=0;
									card_num[6]=0;card_num[7]=0;card_num[8]=0;card_num[9]=0;card_num[10]=0;card_num[11]=0;
	
								}
								else if(flag==1) 
								{
									password[0]=0;password[1]=0;password[2]=0;password[3]=0;password[4]=0;password[5]=0;	
								}
								
								LCD_Fill(80+1,0+40*flag,180-1,39+40*flag,WHITE);	//����
								break;

			case 7:		if(ii == 1)	break;
			
								if(a >= 2)	break;
							
								if(num>=12)	//���Ų��ܳ���6λ��
								{
									ii=1;
									
									break;
								}
								if(num>=6) //���벻�ܳ���6λ��
								{
									if(a == 1)//���꿨��֮����һ��ȷ��
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
							
								if(num>=12)	//���Ų��ܳ���6λ��
								{
									ii=1;
									
									break;
								}
								if(num>=6) //���벻�ܳ���6λ��
								{
									if(a == 1)//���꿨��֮����һ��ȷ��
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
							
								if(num>=12)	//���Ų��ܳ���6λ��
								{
									ii=1;
									
									break;
								}
								if(num>=6) //���벻�ܳ���6λ��
								{
									if(a == 1)//���꿨��֮����һ��ȷ��
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
								InitAlldata();								   //��ʼ�����ж���������ݵ�����
								TOUCH_GUI_DISP_jiegua();	        							  //���	
								break;

			case 11:	if(ii == 1)	break;
			
								if(a >= 2)	break;
							
								if(num>=12)	//���Ų��ܳ���6λ��
								{
									ii=1;
									
									break;
								}
								if(num>=6) //���벻�ܳ���6λ��
								{
									if(a == 1)//���꿨��֮����һ��ȷ��
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
							
								if(num>=12)	//���Ų��ܳ���6λ��
								{
									ii=1;
									
									break;
								}
								if(num>=6) //���벻�ܳ���6λ��
								{
									if(a == 1)//���꿨��֮����һ��ȷ��
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
							
								if(num>=12)	//���Ų��ܳ���6λ��
								{
									ii=1;
									
									break;
								}
								if(num>=6) //���벻�ܳ���6λ��
								{
									if(a == 1)//���꿨��֮����һ��ȷ��
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
							
								if(num>=12)	//���Ų��ܳ���6λ��
								{
									ii=1;
									
									break;
								}
								if(num>=6) //���벻�ܳ���6λ��
								{
									if(a == 1)//���꿨��֮����һ��ȷ��
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
								InitAlldata();								   //��ʼ�����ж���������ݵ�����
								TOUCH_GUI_DISP_guashi();	     									  //��ʧ	
								break;
								

			default:	break;
		}



		delay_ms(10);//ÿ��10ms��ѯһ�δ�����

// 		//LED��˸ָʾ������������,��ʱʱ�� = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}

//�ſ�
void GUI_DISP_jiegua(void)       
{	
	POINT_COLOR=BLUE; 
	Show_Str(100,120,"��ſ�",16,0);
	Show_Str(40,50+120+30,"��������㷵�ز˵���",16,0);
}

//��ֵ����
void TOUCH_GUI_DISP_jiegua(void)		
{
	u8 key;
// 	u8 i=0;
	u8 ii=0;
	u8 j=0;
	u8 flag_exist=0;		
	u8 locked=0;
	u8 password_temp[4];

// 	Touch_Init();	 //��ʼ�� 
	LCD_Clear(WHITE);//����

	GUI_DISP_jiegua(); 	 //��������

	while(1)
	{
		key=TOUCH_all();	   //��ȡ������ֵ
		
		switch(key)			     				 //��Ӧ��ֵ�Ĵ���
		{
			case 0:		GUI_DISP_jiegua();   				     //û�д����������£�һֱ��ʾ��������
								break;

			case 1:		InitAlldata();									 //��  ��  :  ��ʼ�����ж���������ݵ�����
								TOUCH_GUI_DISP_MENU(); 	         //���ز˵���
								break;


			default:	break;
		}
		
		
		
		if(flag_com==0)//���û�ж�������һֱ��ɨ��
		{
			Read_cardID();//������ID
		}
		else 
		{			
			for(ii=0;ii<4;ii++)//�ж����뿨�ź�ʵ�ʿ����Ƿ�һ��
			{
				if((card_num[ii*3]*100+card_num[ii*3+1]*10+card_num[ii*3+2]) != cardID[ii])
				{
					TOUCH_GUI_DISP_guashijiegua3();//���뿨�ź�ʵ�ʿ��Ų�һ��
				}
				else flag_exist=1;
			}
			
			if(flag_exist == 1)//���뿨�ź�ʵ�ʿ���һ��
			{
				flag_exist=0;
				
				for(j=0; j<20; j++)//ѭ��������
				{
					AT24CXX_Read(1+j*11,datatemp,4);
					
					for(ii=0;ii<4;ii++)
					{
						if(cardID[ii] != datatemp[ii])
						{
							flag_exist=0;		
	 						goto L1;				 //ֻҪ����һ������һ����������ѭ��
						}						
						else flag_exist=1;
					}
					
					L1:
					if(flag_exist == 1)//���ڴ˿���
					{
						AT24CXX_Read(6+j*11,password_temp,6);//��������

						
						for(ii=0;ii<6;ii++)//�ж����������Ƿ���ȷ
						{
							if(password[ii] != password_temp[ii])
							{
								TOUCH_GUI_DISP_guashijiegua4();//�������벻��ȷ��
							}
						}
						
						locked=1;						
						AT24CXX_Write(j*11+5,&locked,1);//����
						TOUCH_GUI_DISP_guashijiegua2(); //�����ɹ���
					}			
				}
				
				//ѭ�������ţ�û�ҵ��˿�
				TOUCH_GUI_DISP_guashijiegua6();		 	//�����ڴ˿������˿�δ���
				
			}
		}
					
		
// 		if(flag_com==0)//���û�ж�������һֱ��ɨ��
// 		{
// 			Read_cardID();//������ID
// 		}
// 		else 
// 		{
// 			if(flag_guashijiegua)	TOUCH_GUI_DISP_guashijiegua0();//��ʾ��ʧ��� 
// 			else	TOUCH_GUI_DISP_guashijiegua2();//��ʾ��ҽ��  
// 		}
		
		
		delay_ms(10);//ÿ��10ms��ѯһ�δ�����

// 		//LED��˸ָʾ������������,��ʱʱ�� = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}

//��ʧ
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
		for(j=0; j<20; j++)//ѭ��������
		{
			AT24CXX_Read(1+j*11,datatemp,4);
			
			for(ii=0;ii<4;ii++)//�ж����뿨���Ƿ����
			{
				if((card_num[ii*3]*100+card_num[ii*3+1]*10+card_num[ii*3+2]) != datatemp[ii])
				{
					flag_exist=0;		
					goto L1;				 //ֻҪ����һ������һ����������ѭ��
				}						
				else flag_exist=1;
			}
			
			L1:
			if(flag_exist == 1)//���ڴ˿���
			{
				AT24CXX_Read(6+j*11,password_temp,6);//��������

				
				for(ii=0;ii<6;ii++)//�ж����������Ƿ���ȷ
				{
					if(password[ii] != password_temp[ii])
					{
						TOUCH_GUI_DISP_guashijiegua1();//�������벻��ȷ��
					}
				}
				
				locked=0;						
				AT24CXX_Write(j*11+5,&locked,1);//��ʧ����
				TOUCH_GUI_DISP_guashijiegua0(); //��ʧ�ɹ���
			}			
		}
		
		//ѭ�������ţ�û�ҵ��˿�
		TOUCH_GUI_DISP_guashijiegua5();		 	//�����ڴ˿������˿�δ���
	}
}

//��ʧ�ɹ�
void GUI_DISP_guashijiegua0(void)
{
	POINT_COLOR=BLUE; 
	Show_Str(40,10,"��������㷵�ز˵���",16,0);
	Show_Str(80,130,"��ʧ�ɹ���",16,0);
}

//��ֵ����
void TOUCH_GUI_DISP_guashijiegua0(void)		
{
	u8 key;
// 	u8 i=0;

// 	Touch_Init();	 //��ʼ�� 
	LCD_Clear(WHITE);//����

	GUI_DISP_guashijiegua0(); 	 //��������

	while(1)
	{
		key=TOUCH_all();	   //��ȡ������ֵ
		
		switch(key)			     				 //��Ӧ��ֵ�Ĵ���
		{
			case 0:		GUI_DISP_guashijiegua0();   				   //û�д����������£�һֱ��ʾ��������
								break;

			case 1:		InitAlldata();									 //��  ��  :  ��ʼ�����ж���������ݵ�����
								TOUCH_GUI_DISP_MENU(); 	         //���ز˵���
								break;


			default:	break;
		}

	
		delay_ms(10);//ÿ��10ms��ѯһ�δ�����

// 		//LED��˸ָʾ������������,��ʱʱ�� = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}

//�������벻��ȷ��
void GUI_DISP_guashijiegua1(void)
{
	POINT_COLOR=BLUE; 
	Show_Str(40,10,"��������㷵�ز˵���",16,0);
	Show_Str(80,130,"��ʧʧ�ܣ�",16,0);
	Show_Str(50,200,"�������벻��ȷ��",16,0);
}

//��ֵ����
void TOUCH_GUI_DISP_guashijiegua1(void)		
{
	u8 key;
// 	u8 i=0;

// 	Touch_Init();	 //��ʼ�� 
	LCD_Clear(WHITE);//����

	GUI_DISP_guashijiegua1(); 	 //��������

	while(1)
	{
		key=TOUCH_all();	   //��ȡ������ֵ
		
		switch(key)			     				 //��Ӧ��ֵ�Ĵ���
		{
			case 0:		GUI_DISP_guashijiegua1();   				   //û�д����������£�һֱ��ʾ��������
								break;

			case 1:		InitAlldata();									 //��  ��  :  ��ʼ�����ж���������ݵ�����
								TOUCH_GUI_DISP_MENU(); 	         //���ز˵���
								break;


			default:	break;
		}

	
		delay_ms(10);//ÿ��10ms��ѯһ�δ�����

// 		//LED��˸ָʾ������������,��ʱʱ�� = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}

//��ҳɹ�
void GUI_DISP_guashijiegua2(void)
{
	POINT_COLOR=BLUE; 
	Show_Str(40,10,"��������㷵�ز˵���",16,0);
	Show_Str(80,130,"��ҳɹ���",16,0);
}

//��ֵ����
void TOUCH_GUI_DISP_guashijiegua2(void)		
{
	u8 key;
// 	u8 i=0;

// 	Touch_Init();	 //��ʼ�� 
	LCD_Clear(WHITE);//����

	GUI_DISP_guashijiegua2(); 	 //��������

	while(1)
	{
		key=TOUCH_all();	   //��ȡ������ֵ
		
		switch(key)			     				 //��Ӧ��ֵ�Ĵ���
		{
			case 0:		GUI_DISP_guashijiegua2();   				   //û�д����������£�һֱ��ʾ��������
								break;

			case 1:		InitAlldata();									 //��  ��  :  ��ʼ�����ж���������ݵ�����
								TOUCH_GUI_DISP_MENU(); 	         //���ز˵���
								break;


			default:	break;
		}

	
		delay_ms(10);//ÿ��10ms��ѯһ�δ�����

// 		//LED��˸ָʾ������������,��ʱʱ�� = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}

//���뿨�ź�ʵ�ʿ��Ų�һ��
void GUI_DISP_guashijiegua3(void)
{
	POINT_COLOR=BLUE; 
	Show_Str(40,10,"��������㷵�ز˵���",16,0);
	Show_Str(80,130,"���ʧ�ܣ�",16,0);
	Show_Str(20,200,"���뿨�ź�ʵ�ʿ��Ų�һ��",16,0);
}

//��ֵ����
void TOUCH_GUI_DISP_guashijiegua3(void)		
{
	u8 key;
// 	u8 i=0;

// 	Touch_Init();	 //��ʼ�� 
	LCD_Clear(WHITE);//����

	GUI_DISP_guashijiegua3(); 	 //��������

	while(1)
	{
		key=TOUCH_all();	   //��ȡ������ֵ
		
		switch(key)			     				 //��Ӧ��ֵ�Ĵ���
		{
			case 0:		GUI_DISP_guashijiegua3();   				   //û�д����������£�һֱ��ʾ��������
								break;

			case 1:		InitAlldata();									 //��  ��  :  ��ʼ�����ж���������ݵ�����
								TOUCH_GUI_DISP_MENU(); 	         //���ز˵���
								break;


			default:	break;
		}

	
		delay_ms(10);//ÿ��10ms��ѯһ�δ�����

// 		//LED��˸ָʾ������������,��ʱʱ�� = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}

//�������벻��ȷ��
void GUI_DISP_guashijiegua4(void)
{
	POINT_COLOR=BLUE; 
	Show_Str(40,10,"��������㷵�ز˵���",16,0);
	Show_Str(80,130,"���ʧ�ܣ�",16,0);
	Show_Str(50,200,"�������벻��ȷ��",16,0);
}

//��ֵ����
void TOUCH_GUI_DISP_guashijiegua4(void)		
{
	u8 key;
// 	u8 i=0;

// 	Touch_Init();	 //��ʼ�� 
	LCD_Clear(WHITE);//����

	GUI_DISP_guashijiegua4(); 	 //��������

	while(1)
	{
		key=TOUCH_all();	   //��ȡ������ֵ
		
		switch(key)			     				 //��Ӧ��ֵ�Ĵ���
		{
			case 0:		GUI_DISP_guashijiegua4();   				   //û�д����������£�һֱ��ʾ��������
								break;

			case 1:		InitAlldata();									 //��  ��  :  ��ʼ�����ж���������ݵ�����
								TOUCH_GUI_DISP_MENU(); 	         //���ز˵���
								break;


			default:	break;
		}

	
		delay_ms(10);//ÿ��10ms��ѯһ�δ�����

// 		//LED��˸ָʾ������������,��ʱʱ�� = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}

//�����ڴ˿������˿�δ���
void GUI_DISP_guashijiegua5(void)
{
	POINT_COLOR=BLUE; 
	Show_Str(40,10,"��������㷵�ز˵���",16,0);
	Show_Str(70,70,"�˿�δ����",16,0);
	Show_Str(80,130,"��ʧʧ�ܣ�",16,0);
}

//��ֵ����
void TOUCH_GUI_DISP_guashijiegua5(void)		
{
	u8 key;
// 	u8 i=0;

// 	Touch_Init();	 //��ʼ�� 
	LCD_Clear(WHITE);//����

	GUI_DISP_guashijiegua5(); 	 //��������

	while(1)
	{
		key=TOUCH_all();	   //��ȡ������ֵ
		
		switch(key)			     				 //��Ӧ��ֵ�Ĵ���
		{
			case 0:		GUI_DISP_guashijiegua5();   		 //û�д����������£�һֱ��ʾ��������
								break;

			case 1:		InitAlldata();									 //��  ��  :  ��ʼ�����ж���������ݵ�����
								TOUCH_GUI_DISP_MENU(); 	         //���ز˵���
								break;


			default:	break;
		}

		
		delay_ms(10);//ÿ��10ms��ѯһ�δ�����

// 		//LED��˸ָʾ������������,��ʱʱ�� = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}

//�����ڴ˿������˿�δ���
void GUI_DISP_guashijiegua6(void)
{
	POINT_COLOR=BLUE; 
	Show_Str(40,10,"��������㷵�ز˵���",16,0);
	Show_Str(70,70,"�˿�δ����",16,0);
	Show_Str(80,130,"���ʧ�ܣ�",16,0);
}

//��ֵ����
void TOUCH_GUI_DISP_guashijiegua6(void)		
{
	u8 key;
// 	u8 i=0;

// 	Touch_Init();	 //��ʼ�� 
	LCD_Clear(WHITE);//����

	GUI_DISP_guashijiegua6(); 	 //��������

	while(1)
	{
		key=TOUCH_all();	   //��ȡ������ֵ
		
		switch(key)			     				 //��Ӧ��ֵ�Ĵ���
		{
			case 0:		GUI_DISP_guashijiegua6();   		 //û�д����������£�һֱ��ʾ��������
								break;

			case 1:		InitAlldata();									 //��  ��  :  ��ʼ�����ж���������ݵ�����
								TOUCH_GUI_DISP_MENU(); 	         //���ز˵���
								break;


			default:	break;
		}

		
		delay_ms(10);//ÿ��10ms��ѯһ�δ�����

// 		//LED��˸ָʾ������������,��ʱʱ�� = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}















//����Ա��ʾ����
void GUI_DISP_administrator(void)       
{	
	POINT_COLOR=BLUE; 
	Show_Str(100,50,"����Ա",16,0);
	Show_Str(100,120,"��ſ�",16,0);
	Show_Str(40,50+120+30,"��������㷵�ز˵���",16,0);
}

//��ֵ����
void TOUCH_GUI_DISP_administrator(void)		
{
	u8 key;
// 	u8 i=0;
	u8 ii=0;

// 	Touch_Init();	 //��ʼ�� 
	LCD_Clear(WHITE);//����

	GUI_DISP_administrator(); 	 //��������

	while(1)
	{
		key=TOUCH_all();	   //��ȡ������ֵ
		
		switch(key)			     				 //��Ӧ��ֵ�Ĵ���
		{
			case 0:		GUI_DISP_administrator();   		 //û�д����������£�һֱ��ʾ��������
								break;

			case 1:		InitAlldata();									 //��  ��  :  ��ʼ�����ж���������ݵ�����
								TOUCH_GUI_DISP_MENU(); 	         //���ز˵���
								break;


			default:	break;
		}

		
		if(flag_com==0)//���û�ж�������һֱ��ɨ��
		{
			Read_cardID();//������
		}
		else //�ж��Ƿ��ǹ���Ա�Ŀ���
		{
			for(ii=0;ii<4;ii++)
			{
				if(cardID[ii] != administrator[ii])
						TOUCH_GUI_DISP_administrator0();	//���ǹ���Ա����
			}
			
			InitAlldata();							//��  ��  :  ��ʼ�����ж���������ݵ�����
			TOUCH_GUI_DISP_chongzhi();	//�����ֵ����
		}
				
						
		
		delay_ms(10);//ÿ��10ms��ѯһ�δ�����

// 		//LED��˸ָʾ������������,��ʱʱ�� = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}

//�ǹ���Ա��ʾ����
void GUI_DISP_administrator0(void)       
{	
	POINT_COLOR=BLUE; 
	Show_Str(50,50,"���ǹ���Ա���ţ�",16,0);
	Show_Str(40,50+120+30,"��������㷵�ز˵���",16,0);
}

//��ֵ����
void TOUCH_GUI_DISP_administrator0(void)		
{
	u8 key;
// 	u8 i=0;

// 	Touch_Init();	 //��ʼ�� 
	LCD_Clear(WHITE);//����

	GUI_DISP_administrator0(); 	 //��������

	while(1)
	{
		key=TOUCH_all();	   //��ȡ������ֵ
		
		switch(key)			     				 //��Ӧ��ֵ�Ĵ���
		{
			case 0:		GUI_DISP_administrator0();   		 //û�д����������£�һֱ��ʾ��������
								break;

			case 1:		InitAlldata();									 //��  ��  :  ��ʼ�����ж���������ݵ�����
								TOUCH_GUI_DISP_MENU(); 	         //���ز˵���
								break;


			default:	break;
		}

		delay_ms(10);//ÿ��10ms��ѯһ�δ�����

// 		//LED��˸ָʾ������������,��ʱʱ�� = delay_ms(10)*50 = 500ms
// 		i++;     
// 		if(i==50)
// 		{
// 			i=0;
// 			LED0=!LED0;
// 		}	
	}
}































