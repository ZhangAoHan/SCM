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
 	Stm32_Clock_Init(9);		//ϵͳʱ������
	uart_init(72,9600); 	//���ڳ�ʼ��Ϊ115200	
	delay_init(72);	   	 		//��ʱ��ʼ�� 	
 	LED_Init();		  			//��ʼ����LED���ӵ�Ӳ���ӿ�
	KEY_Init();					//��ʼ������
	LCD_Init();			   		//��ʼ��LCD   
	DHT11_Init();
	Adc_Init(); //��ʼ������������
	TIM3_PWM_Init(200,7199); //50HZ����
 	POINT_COLOR=RED;			//��������Ϊ��ɫ 
	LCD_ShowString(30,70,200,16,16,"OV7725_OV7670 TEST");	
	LCD_ShowString(30,110,200,16,16,"2018/5/12"); 	 
  	LCD_ShowString(30,130,200,16,16,"OV7725_OV7670 Init...");	  
	while(1)//�ȴ�7725��ʼ���ɹ�
	{
		if(OV7725_Init()==0)   
		{
			sensor=OV7725;
			LCD_ShowString(30,230,200,16,16,"OV7725 Init OK       ");			
			OV7725_Light_Mode(lightmode);
			OV7725_Color_Saturation(saturation);
			OV7725_Brightness(brightness);
			OV7725_Contrast(contrast);
			OV7725_Special_Effects(effect);
			OV7725_CS=0;
			OV7725_Window_Set(OV7725_WINDOW_WIDTH,OV7725_WINDOW_HEIGHT,0);//Ĭ��QVGAģʽ���  1ΪVGRģʽ
			break;   
		}
		else
		{
			LCD_ShowString(30,230,200,16,16,"OV7725_OV7670 Error!!");
			delay_ms(200);
			LCD_Fill(30,230,239,246,WHITE);
			delay_ms(200);
		}
	}

	TIM6_Int_Init(10000,7199);			//10Khz����Ƶ��,1�����ж�	
	EXTI8_Init();						//ʹ���ⲿ�ж�8,����֡�ж�			
	LCD_Clear(WHITE);
 	while(1)
	{	
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
		case 0x09:   //��ת
		{
			motor++;
			delay_ms(20);
			if(motor>18) motor=18;
			DJ=motor;
		}
		break;
		case 0x10:   //��ת
		{
			motor--;
			delay_ms(20);
			if(motor<6) motor=6;
			DJ=motor;
		}
		break;
	}
}
void Dispay_1(void)   //������ҳ��
{
	POINT_COLOR=RED;			//��������Ϊ��ɫ
	LCD_ShowString(36,0,168,24,24,"Welcome To Use");  //24=12*24
	POINT_COLOR=BLACK;			//��������Ϊ��ɫ
	LCD_ShowString(12,100,216,24,24,"Camera Mode Order:");   //��������ͷģʽ
	LCD_ShowString(0,130,48,24,24,"0X00");
	LCD_ShowString(0,200,240,24,24,"Physical Mode Order:");   //��������ͷģʽ
	LCD_ShowString(0,230,48,24,24,"0X01");
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
		if((4096-Candela)>=3000)
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



