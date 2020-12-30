#include "sys.h"
#include "usart.h"		
#include "delay.h"	 
#include "lcd.h"
#include "touch.h"  
#include "w25q128.h"  
#include "text.h"
#include "ds18b20.h"   
#include "memory.h" 
#include "rc522.h"

/*ȫ�ֱ���*/
unsigned char CT[2];//������
unsigned char SN[4]; //����
unsigned char RFID[16];			//���RFID 
unsigned char lxl_bit=0;
unsigned char card1_bit=0;
unsigned char card2_bit=0;
unsigned char card3_bit=0;
unsigned char card4_bit=0;
unsigned char total=0;
unsigned char lxl[4]={6,109,250,186};
unsigned char card_1[4]={66,193,88,0};
unsigned char card_2[4]={66,191,104,0};
unsigned char card_3[4]={62,84,28,11};
unsigned char card_4[4]={126,252,248,12};
u8 KEY[6]={0xff,0xff,0xff,0xff,0xff,0xff};
unsigned char RFID1[16]={0x01,0x00,0x00,0x00,0x00,0x00,0xff,0x07,0x80,0x29,0xff,0xff,0xff,0xff,0xff,0xff};

//void rtp_test(void);
//void Load_Drow_Dialog(void);
//void gui_fill_circle(u16 x0,u16 y0,u16 r,u16 color);
//u16 my_abs(u16 x1,u16 x2);
//void lcd_draw_bline(u16 x1, u16 y1, u16 x2, u16 y2,u8 size,u16 color);
//void test_touch(void)
//{
//	tp_dev.scan(0); 
//if(tp_dev.sta&TP_PRES_DOWN)			//������������
//{
//	if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
//	{
//		if(tp_dev.x[0]>11&&tp_dev.x[0]<150&&tp_dev.y[0]>10&&tp_dev.y[0]<80)
//		{
//			Show_Str(50,200,24,24,"��",24,0);
//		}
//		else if(tp_dev.x[0]>11&&tp_dev.x[0]<150&&tp_dev.y[0]>100&&tp_dev.y[0]<170)
//		{
//			Show_Str(50,200,24,24,"��",24,0);
//		}
//		else if(tp_dev.x[0]>150&&tp_dev.x[0]<200&&tp_dev.y[0]>200&&tp_dev.y[0]<230)
//		{
//			TP_Adjust();
//		}
//		else
//		{
//			Show_Str(50,200,24,24,"��",24,0);
//			LCD_ShowxNum(10,240,tp_dev.x[0],9,16,0);
//			LCD_ShowxNum(10,280,tp_dev.y[0],9,16,0);

//		}
//	}
//}	
//	else Show_Str(50,200,24,24,"��",24,0);
//}
//�����Ļ�������Ͻ���ʾ"RST"
//void Load_Drow_Dialog(void)
//{
//	LCD_Clear(WHITE);	//����   
// 	POINT_COLOR=BLUE;	//��������Ϊ��ɫ 
//	LCD_ShowString(lcddev.width-24,0,200,16,16,"RST");//��ʾ��������
//  	POINT_COLOR=RED;	//���û�����ɫ 
//}

// //5�����ص����ɫ												 
//const u16 POINT_COLOR_TBL[CT_MAX_TOUCH]={RED,GREEN,BLUE,BROWN,GRED};  
////���败�������Ժ���
//void rtp_test(void)
//{  
//	while(1)
//	{
//		tp_dev.scan(0); 		 
//		if(tp_dev.sta&TP_PRES_DOWN)			//������������
//		{	
//		 	if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
//			{	
//				if(tp_dev.x[0]>(lcddev.width-24)&&tp_dev.y[0]<16)Load_Drow_Dialog();//���
//				else TP_Draw_Big_Point(tp_dev.x[0],tp_dev.y[0],RED);		//��ͼ	  			   
//			}
//		}else delay_ms(10);	//û�а������µ�ʱ�� 	    
//	}
//}

int main(void)
{		
	unsigned char status;
	unsigned char s=7;
	u8 t;
	Stm32_Clock_Init(9);	//ϵͳʱ������
	delay_init(72);	  		//��ʱ��ʼ��
	uart_init(72,115200); 	//���ڳ�ʼ��Ϊ115200
	LCD_Init();
	W25QXX_Init();				//��ʼ��W25Q128 ��SPI2
	tp_dev.init();			//��������ʼ�� 
	while(font_init()) 			//����ֿ�
	{;}  
	InitRc522();
	Show_Str(150,200,48,24,"У׼",24,0);
//	while(DS18B20_Init())	//DS18B20��ʼ��	
//	{
//		LCD_ShowString(60,130,200,16,16,"DS18B20 Error");
//		delay_ms(200);
//		LCD_Fill(60,130,239,130+16,WHITE);
// 		delay_ms(200);
//	}
//	Show_Str(5,5,132,24,"��һ�����ݣ�",24,0);
//	Show_Str(5,35,132,24,"�ڶ������ݣ�",24,0);
//	Show_Str(5,65,108,24,"�¶����ݣ�",24,0);
//		LCD_DrawRectangle(10,10,150,80);
//		LCD_ShowString(11,11,80,16,16,"right");
//		LCD_DrawRectangle(10,100,150,170);
//		LCD_ShowString(11,101,64,16,16,"left");
//		Show_Str(150,200,48,24,"У׼",24,0);
		
  	while(1)
	{
////		test_touch();
//		rtp_test(); 	
//LCD_ShowChar(60+40,150,' ',16,0);			//ȥ������
//			LCD_ShowNum(60+40+8,150,temperature/10,2,16);	//��ʾ��������	    
//   			LCD_ShowNum(60+40+32,150,temperature%10,1,16);	//��ʾС������ 	
//		temp_memory();
 	while(1)
	{	
		status = PcdRequest(PICC_REQALL,CT);/*����*/
		if(status==MI_OK)//�����ɹ�
		{
			 status=MI_ERR;
			 status = PcdAnticoll(SN);/*����ײ*/
		}	
		if(status==MI_OK)
		{
			status=MI_ERR;
			status =PcdSelect(SN);
		}

		if(status==MI_OK)//�x���ɹ�
		{
			 status=MI_ERR;
			 status =PcdAuthState(0x61,0x06,KEY,SN);
		 }
	
		 if(status==MI_OK)//��C�ɹ�
		 {
			  status=MI_ERR;
			  for(t=0;t<4;t++)
			  {
					LCD_ShowNum(0,116+t*16,SN[t],3,16);
			  }	  
		  }
//	 if(status==MI_OK)//��C�ɹ�
//		 {
//			status=MI_ERR;
////			LCD_ShowNum(0,116+t*16,SN[t],3,16);
//			 date1=SN[0];
//			 date2=SN[1];
//			 date3=SN[2];
//			 date4=SN[3];
//			LCD_ShowNum(5,5,date1,3,16);	//��ʾС������ 
//			LCD_ShowNum(5,25,date2,3,16);	//��ʾС������ 
//			LCD_ShowNum(5,45,date3,3,16);	//��ʾС������ 
//			LCD_ShowNum(5,65,date4,3,16);	//��ʾС������  

//			  }	 
	}
}
	}	 







