#include "sys.h"
#include "usart.h"		
#include "delay.h"	   
#include "TFT.h"   

u8 temp0[]={ "cls RED 0xff 0xff 0xff" };
int main(void)
{
//	u8 lcd_id[12]; //��� LCD ID �ַ���
	u8 t;
//	u8 value;
	//u8 temp[3];
	Stm32_Clock_Init(9); //ϵͳʱ������
	uart_init(72,9600); //���ڳ�ʼ��Ϊ 115200
	delay_init(72); //��ʱ��ʼ��
	LCD_Init();
	
	//sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//�� LCD ID ��ӡ�� lcd_id ���顣
	LCD_Clear(WHITE);
	while(1)
	{
//		POINT_COLOR=BLACK;
//		LCD_ShowString(30,30,150,54,24,"STM32");   //X,Y,�����С���ֺ�*�ַ����� �ֺ�  �ַ�
//		LCD_Fill(17,56,47,86,RED);
//		POINT_COLOR=BLUE;
//		LCD_Draw_Circle(32,71,15);
//		LCD_DrawRectangle(16,55,48,87);
					   

for(t=0;t<22;t++)
			{
				USART1->DR=temp0[t];	
			while((USART1->SR&0X40)==0) { ; }
		}
			
//			printf("U%d %d",t,temp[t]);
//			printf("U%d %d",t,USART_RX_BUF[t]);
//			printf("\r\n\r\n");//���뻻��	
			
//			value=temp[0]*100+temp[1]*10+temp[2];


			
		
		
//			printf("\r\n\r\n");//���뻻��
			
			

		}
			


		
		


		
	}


