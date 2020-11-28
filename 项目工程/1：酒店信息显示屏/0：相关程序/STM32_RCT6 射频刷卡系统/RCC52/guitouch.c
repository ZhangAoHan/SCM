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

//�ҵ�ͷ�ļ�
#include "guitouch.h"




/****************************
        ���ְ�������
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
//	Show_Str(0,0,"�����룺",16,0);
//	Show_Str(10,49,"ɾ��",16,0);
//	Show_Str(195,49,"ȷ��",16,0);

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
u8 my_Touch_0(void)
{
	//ɨ�败����
	if(Pen_Point.Key_Sta==Key_Down)//������������
	{
		Pen_Int_Set(0);//�ر��ж�

			Convert_Pos();//ת����������ݴ�������У׼����������ת����Ľ��,������X0,Y0��
			Pen_Point.Key_Sta=Key_Up;

			if(Pen_Point.X0>0&&Pen_Point.X0<59&&Pen_Point.Y0>79&&Pen_Point.Y0<139)				 //1
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(0,79,59,139,BLACK);//���鴥������
				}
				LCD_Fill(0,79,59,139,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 1;
			}
			else if(Pen_Point.X0>59&&Pen_Point.X0<119&&Pen_Point.Y0>79&&Pen_Point.Y0<139) 		//2
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(59,79,119,139,BLACK);//���鴥������
				}
				LCD_Fill(59,79,119,139,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 2;
			}
			else if(Pen_Point.X0>119&&Pen_Point.X0<179&&Pen_Point.Y0>79&&Pen_Point.Y0<139) 		//3
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(119,79,179,139,BLACK);//���鴥������
				}
				LCD_Fill(119,79,179,139,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 3;
			}
			else if(Pen_Point.X0>179&&Pen_Point.X0<239&&Pen_Point.Y0>79&&Pen_Point.Y0<139) 		//A
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(179,79,239,139,BLACK);//���鴥������
				}
				LCD_Fill(179,79,239,139,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 4;
			}

			else if(Pen_Point.X0>0&&Pen_Point.X0<59&&Pen_Point.Y0>139&&Pen_Point.Y0<199)		//4
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(0,139,59,199,BLACK);//���鴥������
				}
				LCD_Fill(0,139,59,199,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 5;
			}
			else if(Pen_Point.X0>59&&Pen_Point.X0<119&&Pen_Point.Y0>139&&Pen_Point.Y0<199)		//5
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(59,139,119,199,BLACK);//���鴥������
				}
				LCD_Fill(59,139,119,199,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 6;
			}
			else if(Pen_Point.X0>119&&Pen_Point.X0<179&&Pen_Point.Y0>139&&Pen_Point.Y0<199)		 //6
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(119,139,179,199,BLACK);//���鴥������
				}
				LCD_Fill(119,139,179,199,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 7;
			}
			else if(Pen_Point.X0>179&&Pen_Point.X0<239&&Pen_Point.Y0>139&&Pen_Point.Y0<199)		 //B
			{  	
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(179,139,239,199,BLACK);//���鴥������
				}
				LCD_Fill(179,139,239,199,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 8;
			}

			else if(Pen_Point.X0>0&&Pen_Point.X0<59&&Pen_Point.Y0>199&&Pen_Point.Y0<259)		 //7
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(0,199,59,259,BLACK);//���鴥������
				}
				LCD_Fill(0,199,59,259,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 9;
			}
			else if(Pen_Point.X0>59&&Pen_Point.X0<119&&Pen_Point.Y0>199&&Pen_Point.Y0<259)		//8
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(59,199,119,259,BLACK);//���鴥������
				}
				LCD_Fill(59,199,119,259,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 10;
			}
			else if(Pen_Point.X0>119&&Pen_Point.X0<179&&Pen_Point.Y0>199&&Pen_Point.Y0<259)		 //9
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(119,199,179,259,BLACK);//���鴥������
				}
				LCD_Fill(119,199,179,259,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 11;
			}
			else if(Pen_Point.X0>179&&Pen_Point.X0<239&&Pen_Point.Y0>199&&Pen_Point.Y0<259)		//C
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(179,199,239,259,BLACK);//���鴥������
				}
				LCD_Fill(179,199,239,259,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 12;
			}

			else if(Pen_Point.X0>0&&Pen_Point.X0<59&&Pen_Point.Y0>259&&Pen_Point.Y0<319)	   //*
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(0,259,59,319,BLACK);//���鴥������
				}
				LCD_Fill(0,259,59,319,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 13;
			}
			else if(Pen_Point.X0>59&&Pen_Point.X0<119&&Pen_Point.Y0>259&&Pen_Point.Y0<319)		//0
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(59,259,119,319,BLACK);//���鴥������
				}
				LCD_Fill(59,259,119,319,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 14;
			}
			else if(Pen_Point.X0>119&&Pen_Point.X0<179&&Pen_Point.Y0>259&&Pen_Point.Y0<319)		//#
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(119,259,179,319,BLACK);//���鴥������
				}
				LCD_Fill(119,259,179,319,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 15;
			}
			else if(Pen_Point.X0>179&&Pen_Point.X0<239&&Pen_Point.Y0>259&&Pen_Point.Y0<319)		 //D
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(179,259,239,319,BLACK);//���鴥������
				}
				LCD_Fill(179,259,239,319,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 16;
			}

			else if(Pen_Point.X0>0&&Pen_Point.X0<59&&Pen_Point.Y0>19&&Pen_Point.Y0<79)			 //
			{
				while(PEN==0)  //�ȴ������ͷ�
				{
					LCD_Fill(0,19,59,79,BLACK);//���鴥������
				}
				LCD_Fill(0,19,59,79,WHITE);

				Pen_Int_Set(1);//�����ж�

				return 17;
			}
			else if(Pen_Point.X0>179&&Pen_Point.X0<239&&Pen_Point.Y0>19&&Pen_Point.Y0<79)		 //
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
void my_GUI_Touch_0(void)
{
	u8 key,i=0;

	Touch_Init();	 //��ʼ�� 
	LCD_Clear(WHITE);//����

	my_GUI_0(); 	 //��������

	while(1)
	{
		key=my_Touch_0();	     //��ȡ������ֵ
		
		switch(key)			     //��Ӧ��ֵ�Ĵ���
		{
			case 0:		LCD_ShowNum(109,20,0,2,16);  	   //û�д�����������
						my_GUI_0();  				       //һֱ��ʾ��������
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
//						return;							   //���ؿ�ֵ���˳��˺���
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


















