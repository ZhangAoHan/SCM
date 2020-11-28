#include "sys.h"    //����ͷ��ʾͷ�ļ�
#include "delay.h"
#include "usart.h" 
#include "led.h" 		 	 
#include "lcd.h"  
#include "key.h"   
#include "timer.h"
#include "exti.h"   
#include "ov7725.h"
#include "adc.h"
#include "dht11.h"
#include "rcc52.h"
u8 res=0x00,res0=0x00;   //��������
u8 key=0,key1=0;
u8 T,H,S,L; //����������� 
u8 sensor=0;
s8 saturation=0,brightness=0,contrast=0,lightmode=0,effect=0;


u8 A1,A2,A3;  //��������
u8 temperature;
u8 humidity;
u16 Candela;
u8 motor=12;
//���������ֺ궨��
#define  OV7725 1
//ע�⣺�˺궨��ֻ��OV7725��Ч
#define  OV7725_WINDOW_WIDTH		320 // <=320,���ֳߴ�ͼ��������
#define  OV7725_WINDOW_HEIGHT		240 // <=240,���ֳߴ�ͼ��������

extern u8 ov_sta;	//��exit.c�� �涨��
extern u8 ov_frame;	//��timer.c���涨��
//RC522��Ҫ����
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
unsigned char card_1[4]={22,76,117,37};  //zhang
unsigned char card_2[4]={22,200,198,37};  //wang
unsigned char card_3[4]={22,26,43,37};  //zhu
unsigned char card_4[4]={38,208,71,37};  //li
u8 KEY[6]={0xff,0xff,0xff,0xff,0xff,0xff};
unsigned char RFID1[16]={0x01,0x00,0x00,0x00,0x00,0x00,0xff,0x07,0x80,0x29,0xff,0xff,0xff,0xff,0xff,0xff};
unsigned char status;
u8 Name;
u8 name=1;

void Video_display(void);
void Dispay_1(void);
void Display_2(void);
void Blue_Tooth(void);
void JC(void);
//����LCD��ʾ(OV7725)
void OV7725_camera_refresh(void)
{
	u32 i,j;
 	u16 color;	 
	if(ov_sta)//��֡�жϸ���
	{
		LCD_Scan_Dir(U2D_L2R);		//���ϵ���,������  
		LCD_Set_Window((lcddev.width-OV7725_WINDOW_WIDTH)/2,(lcddev.height-OV7725_WINDOW_HEIGHT)/2,OV7725_WINDOW_WIDTH,OV7725_WINDOW_HEIGHT);//����ʾ�������õ���Ļ����
		if(lcddev.id==0X1963)LCD_Set_Window((lcddev.width-OV7725_WINDOW_WIDTH)/2,(lcddev.height-OV7725_WINDOW_HEIGHT)/2,OV7725_WINDOW_HEIGHT,OV7725_WINDOW_WIDTH);//����ʾ�������õ���Ļ����
		LCD_WriteRAM_Prepare();     //��ʼд��GRAM	
		OV7725_RRST=0;				//��ʼ��λ��ָ�� 
		OV7725_RCK_L;
		OV7725_RCK_H;
		OV7725_RCK_L;
		OV7725_RRST=1;				//��λ��ָ����� 
		OV7725_RCK_H; 
		for(i=0;i<OV7725_WINDOW_HEIGHT;i++)
		{
			for(j=0;j<OV7725_WINDOW_WIDTH;j++)
			{
				OV7725_RCK_L;
				color=GPIOC->IDR&0XFF;	//������
				OV7725_RCK_H; 
				color<<=8;  
				OV7725_RCK_L;
				color|=GPIOC->IDR&0XFF;	//������
				OV7725_RCK_H; 
				LCD->LCD_RAM=color;  
			}
		}
 		ov_sta=0;					//����֡�жϱ��
		ov_frame++; 
		LCD_Scan_Dir(DFT_SCAN_DIR);	//�ָ�Ĭ��ɨ�跽�� 
	} 
}

	   

int main(void)
{		
	u8 t;
 	Stm32_Clock_Init(9);		//ϵͳʱ������
	uart_init(72,9600); 	//���ڳ�ʼ��Ϊ115200	
	delay_init(72);	   	 		//��ʱ��ʼ�� 	
// 	LED_Init();		  			//��ʼ����LED���ӵ�Ӳ���ӿ�
//	KEY_Init();					//��ʼ������
	LCD_Init();			   		//��ʼ��LCD   
//	Adc_Init(); //��ʼ������������
	InitRc522();
//	DHT11_Init();
//	TIM3_PWM_Init(200,7199); //50HZ����
 	POINT_COLOR=RED;			//��������Ϊ��ɫ 
	LCD_ShowString(30,70,200,16,16,"OV7725_OV7670 TEST");	
	LCD_ShowString(30,110,200,16,16,"2018/5/12"); 	 
  	LCD_ShowString(30,130,200,16,16,"OV7725_OV7670 Init...");	  
//	while(1)//�ȴ�7725��ʼ���ɹ�
//	{
//		if(OV7725_Init()==0)   
//		{
//			sensor=OV7725;
//			LCD_ShowString(30,230,200,16,16,"OV7725 Init OK       ");			
//			OV7725_Light_Mode(lightmode);
//			OV7725_Color_Saturation(saturation);
//			OV7725_Brightness(brightness);
//			OV7725_Contrast(contrast);
//			OV7725_Special_Effects(effect);
//			OV7725_CS=0;
//			OV7725_Window_Set(OV7725_WINDOW_WIDTH,OV7725_WINDOW_HEIGHT,0);//Ĭ��QVGAģʽ���  1ΪVGRģʽ
//			LCD_Clear(WHITE);
//			break;   
//		}
//		else
//		{
//			LCD_ShowString(30,230,200,16,16,"OV7725_OV7670 Error!!");
//			delay_ms(200);
//			LCD_Fill(30,230,239,246,WHITE);
//			delay_ms(200);
//		}
//	}

//	TIM6_Int_Init(10000,7199);			//10Khz����Ƶ��,1�����ж�	
//	EXTI8_Init();						//ʹ���ⲿ�ж�8,����֡�ж�			
	LCD_Clear(WHITE);
 	while(1)
	{	
			while(name)  //���ID��
	{
		LCD_ShowString(12,100,216,24,24,"Please Log In:");
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
				  if(SN[t]==card_1[t]) 
				  {
						Name=1;
					  name=0;
					  LCD_Clear(WHITE);
					  break;
					}
				  if(SN[t]==card_4[t]) 
				  {
						Name=4;
					  name=0;
					  LCD_Clear(WHITE);
					  break;
				  }
				  				  if(SN[t]==card_2[t]) 
				  {
						Name=2;
					  name=0;
					  LCD_Clear(WHITE);
					  break;
				  }
				  				  if(SN[t]==card_3[t]) 
				  {
						Name=3;
					  name=0;
					  LCD_Clear(WHITE);
					  break;
				  }
//					LCD_ShowNum(0,116+t*16,SN[t],3,16);
			  }	 

		  }
	}
		JC();
		Blue_Tooth();
}
 }
/*
0X00:��ҳ��  00
0X01:����ͷ����  01
0X02:����������� 02
0X03:����ͷģʽ����  01
0X04:����ͷɫ�� 01
0X05:����ͷ���� 01
0X06:����ͷ�Աȶ� 01
0X07:����ͷ��Ч 01
0X08:����ͷ���û�ԭ����ģʽ 01
0x09����ͷ��ת
0x10����ͷ��ת
0x11 �˳���¼
*/
void Blue_Tooth(void)
{
	if(res0!=res)
	{
		LCD_Clear(WHITE);  //����
		res0=res;		
	}
	
	switch(res)
	{
		case 0x00:Dispay_1();break;	//��ҳ��
		case 0x01:if(sensor==OV7725)OV7725_camera_refresh();break;  //����ͷ��ʾ
		case 0x02:Display_2();break;  //����������ҳ��
		case 0x03:  //����ͷģʽ����
		{
			lightmode++;
			delay_ms(100);
			if(lightmode==6) lightmode=0;
			OV7725_Light_Mode(lightmode);
		}
		break;
		case 0x04:
		{
			saturation++;
			delay_ms(100);
			if(saturation==5) saturation=-4;
			OV7725_Color_Saturation(saturation);
		}
		break;
				case 0x05:
		{
			brightness++;
			delay_ms(100);
			if(brightness==5) brightness=-4;
			OV7725_Brightness(brightness);
		}
		break;
				case 0x06:
		{
			contrast++;
			delay_ms(100);
			if(contrast==5) contrast=-4;
			OV7725_Contrast(contrast);
		}
		break;
						case 0x07:
		{
			effect++;
			delay_ms(100);
			if(effect==6) effect=0;
			OV7725_Special_Effects(effect);
		}
		break;
		case 0x08:   //һ������
		{
			lightmode=saturation=brightness=contrast=effect=0;
			OV7725_Light_Mode(lightmode);
			OV7725_Color_Saturation(saturation);
			OV7725_Brightness(brightness);
			OV7725_Contrast(contrast);
			OV7725_Special_Effects(effect);
		}
		break;
//		case 0x09:   //��ת
//		{
//			motor++;
//			delay_ms(20);
//			if(motor>18) motor=18;
//			DJ=motor;
//		}
//		break;
//		case 0x10:   //��ת
//		{
//			motor--;
//			delay_ms(20);
//			if(motor<6) motor=6;
//			DJ=motor;
//		}
//		break;
				case 0x11:   //�˳���¼
		{
			name=1;
			LCD_Clear(WHITE);
		}
		break;
	}
}
void Dispay_1(void)   //������ҳ��
{
	POINT_COLOR=RED;			//��������Ϊ��ɫ
	LCD_ShowString(36,0,168,24,24,"Welcome To Use");  //24=12*24
	POINT_COLOR=BLACK;			//��������Ϊ��ɫ
	LCD_ShowString(12,100,216,24,24,"Already Log In:");  
	LCD_ShowString(0,150,96,24,24,"Card Id:"); 
	LCD_ShowString(0,200,60,24,24,"Name:"); 
	if(Name==1)
	{
		LCD_ShowNum(100,150,card_1[0],2,24);
		LCD_ShowNum(124,150,card_1[1],2,24);
		LCD_ShowNum(148,150,card_1[2],3,24);
		LCD_ShowNum(184,150,card_1[3],2,24);
		LCD_ShowString(100,200,100,24,24,"Mi.Zhang"); 
		LCD_ShowString(50,250,150,24,24,"You Can Use");
	}
		if(Name==2)
	{
		LCD_ShowNum(100,150,card_2[0],2,24);
		LCD_ShowNum(124,150,card_2[1],2,24);
		LCD_ShowNum(148,150,card_2[2],3,24);
		LCD_ShowNum(184,150,card_2[3],2,24);
		LCD_ShowString(100,200,100,24,24,"Mi.Wang"); 
		LCD_ShowString(50,250,150,24,24,"You Can Use");
	}
		if(Name==3)
	{
		LCD_ShowNum(100,150,card_3[0],2,24);
		LCD_ShowNum(124,150,card_3[1],2,24);
		LCD_ShowNum(148,150,card_3[2],3,24);
		LCD_ShowNum(184,150,card_3[3],2,24);
		LCD_ShowString(100,200,100,24,24,"Mi.Zhu"); 
		LCD_ShowString(50,250,150,24,24,"You Can Use");
	}
		if(Name==4)
	{
		LCD_ShowNum(100,150,card_4[0],2,24);
		LCD_ShowNum(124,150,card_4[1],3,24);
		LCD_ShowNum(160,150,card_4[2],3,24);
		LCD_ShowNum(196,150,card_4[3],2,24);
		LCD_ShowString(100,200,100,24,24,"Mi.Li"); 
		LCD_ShowString(50,250,150,24,24,"You Can Use");
	}	
	}
void Display_2(void)
{
	if(key1==0)LCD_ShowString(18,50,204,24,24,"Detection A Point");
	if(key1==1)LCD_ShowString(18,50,204,24,24,"Detection B Point");
	if(key1==2)LCD_ShowString(18,50,204,24,24,"Detection C Point");
	if(key1==3)LCD_ShowString(18,50,204,24,24,"Detection D Point");
	DHT11_Read_Data(&temperature,&humidity);
	Candela=Get_Adc_Average(ADC_CH1,10);
	POINT_COLOR=BLUE;			//��������Ϊ��ɫ
	LCD_ShowString(42,10,156,24,24,"Environmental");   
	LCD_ShowString(30,100,24,24,24,"T:");   //�¶�
	LCD_ShowxNum(60,100,temperature,2,24,0);
	LCD_ShowString(30,140,24,24,24,"H:");   //ʪ��
	LCD_ShowxNum(60,140,humidity,2,24,0);
	LCD_ShowString(30,180,60,24,24,"L:");   //��ǿ
	LCD_ShowxNum(60,180,4096-Candela,4,24,0);
	
	if(temperature>=30)
	{
		if(A1==0)
		{
		LCD_Clear(WHITE); 
			A1=1;
		POINT_COLOR=RED;
		LCD_ShowString(0,210,180,24,24,"Overtemperature");
		}
		else
		{
		POINT_COLOR=RED;
		LCD_ShowString(0,210,180,24,24,"Overtemperature"); 
		}
	}
	else 
	{
		if(A1==1)
		{
		LCD_Clear(WHITE); 
		A1=0;
		POINT_COLOR=GREEN;
		LCD_ShowString(0,210,144,24,24,"Normothermia"); 
		}
		else
		{
		POINT_COLOR=GREEN;
		LCD_ShowString(0,210,144,24,24,"Normothermia"); 
		}
	}
		if(humidity>=50)
		{
			if(A2==0)
			{
			LCD_Clear(WHITE); 
			A2=1;
			POINT_COLOR=RED;
			LCD_ShowString(0,240,240,24,24,"Humidity Is Too High");
			}
			else
			{
			POINT_COLOR=RED;
			LCD_ShowString(0,240,240,24,24,"Humidity Is Too High");
			}
		} 
	else 
	{
		if(A2==1)
		{
		LCD_Clear(WHITE); 
		A2=0;
		POINT_COLOR=GREEN;
		LCD_ShowString(0,240,240,24,24,"Normal Humidity");
		}
		else
		{
		POINT_COLOR=GREEN;
		LCD_ShowString(0,240,240,24,24,"Normal Humidity");
		}
	}
		if((4096-Candela)>=1000)
		{
			if(A3==0)
			{
			LCD_Clear(WHITE); 
			A3=1;
			POINT_COLOR=RED;
			LCD_ShowString(0,270,240,24,24,"Too Bright");
			}
			else
			{
			POINT_COLOR=RED;
			LCD_ShowString(0,270,240,24,24,"Too Bright");
			}
		} 
	else 
	{
		if(A3==1)
		{
			LCD_Clear(WHITE); 
			A3=0;
			POINT_COLOR=GREEN;
			LCD_ShowString(0,270,240,24,24,"Normal Brightness");
		}
		else
		{
			POINT_COLOR=GREEN;
			LCD_ShowString(0,270,240,24,24,"Normal Brightness");
		}
	}
	

}

void JC(void)
{
if(key==0)key1=0,JDQ1=0,JDQ2=1,JDQ3=1,JDQ4=1;
if(key==1)key1=1,JDQ1=1,JDQ2=0,JDQ3=1,JDQ4=1;
if(key==2)key1=2,JDQ1=1,JDQ2=1,JDQ3=0,JDQ4=1;
if(key==3)key1=3,JDQ1=1,JDQ2=1,JDQ3=1,JDQ4=0;
}

//	POINT_COLOR=BLACK;			//��������Ϊ��ɫ 
//		LCD_ShowString(0,0,176,16,16,"Light_Mode:");
//	LCD_ShowNum(177,0,num1,1,16);
//	LCD_ShowString(196,0,18,18,16,"+");
//	LCD_ShowString(220,0,18,18,16,"-");
//		LCD_ShowString(0,20,80,16,16,"Color:");
//	LCD_ShowNum(177,20,num2,1,16);
//	LCD_ShowString(196,20,18,18,16,"+");
//	LCD_ShowString(220,20,18,18,16,"-");
//		LCD_ShowString(0,40,176,16,16,"Brightness:");
//	LCD_ShowNum(177,40,num3,1,16);
//	LCD_ShowString(196,40,18,18,16,"+");
//	LCD_ShowString(220,40,18,18,16,"-");
//		LCD_ShowString(0,60,144,16,16,"Contrast:");
//	LCD_ShowNum(177,0,num4,1,16);
//	LCD_ShowString(196,60,18,18,16,"+");
//	LCD_ShowString(220,0,18,18,16,"-");



