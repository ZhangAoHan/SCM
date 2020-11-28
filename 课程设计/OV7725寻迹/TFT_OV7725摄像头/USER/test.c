#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 		 	 
#include "lcd.h"  
#include "key.h"   
#include "timer.h"
#include "exti.h"   
#include "ov7725.h"

//ALIENTEKս��STM32������ ʵ��35
//����ͷʵ�� ʵ�� 
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾ 

u8 key;
u8 key1;
//���������ֺ궨��
#define  OV7725 1
u8 flag=0;
//����OV7725��������װ��ʽԭ��,OV7725_WINDOW_WIDTH�൱��LCD�ĸ߶ȣ�OV7725_WINDOW_HEIGHT�൱��LCD�Ŀ��
//ͼ�����������ʽ���LCD��˳��ΪD2U_L2R�����µ���,�����ң�
//ע�⣺�˺궨��ֻ��OV7725��Ч
#define  OV7725_WINDOW_WIDTH		320 // <=320,���ֳߴ�ͼ��������
#define  OV7725_WINDOW_HEIGHT		240 // <=240,���ֳߴ�ͼ��������
u16 color1;

const u8*LMODE_TBL[6]={"Auto","Sunny","Cloudy","Office","Home","Night"};//6�ֹ���ģʽ	    
const u8*EFFECTS_TBL[7]={"Normal","Negative","B&W","Redish","Greenish","Bluish","Antique"};	//7����Ч 
extern u8 ov_sta;	//��exit.c�� �涨��
extern u8 ov_frame;	//��timer.c���涨��

 //���ݲɼ�����
u32 Array[60] ={
	 /*�ɼ����ص���󡾣�16,150������19,154���� 320��*/
	5270,5271,5272,5273,5274,    //46*320+150=14870
	5590,5591,5592,5593,5594,
	5770,5771,5772,5773,5774,
	6090,6091,6092,6093,6094,
	 /*�ɼ����ص���󡾣�100,10������104,13���� 320��*/
	32010,32011,32012,32013,			 
	32330,32331,32332,32333,
	32650,32651,32652,32653,
	32970,32971,32972,32973,
	33290,33291,33292,33293,
	/*�ɼ����ص���󡾣�205,150������208,154���� 320��  */
	65750,65751,65752,65753,65754,		 
	66070,66071,66072,66073,66074,
	66390,66391,66392,66393,66394,
	66710,66711,66712,66713,66714,

};

//����LCD��ʾ(OV7725)
void OV7725_camera_refresh(void)
{
	u32 i,j;
	u8 whitepoint = 0;
	u8 leftblackpoint  = 0;
	u8 rightblackpoint = 0;
 	u16 color;	 
	flag=0;
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
		for(i=0;i<OV7725_WINDOW_HEIGHT*OV7725_WINDOW_WIDTH;i++)
		{
				OV7725_RCK_L;
				color=GPIOC->IDR&0XFF;	//�����ݣ�&0xff  ��Ϊ�˱�֤�������ݲ����ϴ����ݵĸ��ţ�
				OV7725_RCK_H; 
				color<<=8;  
				OV7725_RCK_L;
				color|=GPIOC->IDR&0XFF;	//������   һ����ȡ2B����  ������RGB565��ʽ��
				OV7725_RCK_H;  
				LCD->LCD_RAM=color; 				
				if(i== Array[j]&&(j<=60))//init(k) = 0									  -=
			{
//				if(j < 20)
//				{
//					   
//					 if(!(color&0x8000))  //��ð׵�
//						leftblackpoint++;
//						
//				}
//				else if(j < 40)
//				{
//					if(color&0x8000)
//					whitepoint++;		//��úڵ�
//					
//				}
//				else if(j < 60)
//				{
//						if(!(color&0x8000))  //����Ƭ  �ڣ����bit15Ϊ0����ڵ�
//						rightblackpoint++;
//					
//				}
           if(j==45)	
		   {
			   color=color1;
		   }			   
//				if(j < 20)
//				{
//					   
//					 if(!(color&0x8000))  //��ú�
//						leftblackpoint++;
//						
//				}
//				else if(j < 40)
//				{
//					if(color&0x4000)
//					whitepoint++;		//��ð׵�
//					
//				}
//				else if(j < 60)
//				{
//						if(!(color&0x8000))  //����Ƭ  �ڣ����bit15Ϊ0����ڵ�
//						rightblackpoint++;
//					
//				}	
			j++;
			} 

			
			
		}
		
//		if(whitepoint<=20)	    //�м��δ��⵽��ɫ��ֹͣ
//	{
//		flag = 2;// stop
//	}
//	else
//		flag=1;
//	else 
//	{

//		if((whitepoint>13)&&(leftblackpoint>13)&&(rightblackpoint>13))//��˿��ɫ  �ж˿��ɫ �Ҷ˿��ɫ 
//		{
//			flag = 1;       
//		}
//	
//		if(leftblackpoint <= 13 && rightblackpoint >13)	//��˺�ɫ �Ҷ˰�ɫ ��������
//		{
//			flag = 2;  //goleft
//		}

//		if(leftblackpoint > 13 && rightblackpoint <= 13)	//�Ҷ˺�ɫ ��˰�ɫ ��������
//		{
//			flag = 3;  //goright
//		}
//    }	
 		ov_sta=0;					//����֡�жϱ��
		ov_frame++; 
		LCD_Scan_Dir(DFT_SCAN_DIR);	//�ָ�Ĭ��ɨ�跽�� 
	} 
}



int main(void)
{		
	u8 sensor=0;
	
 	u8 i=0;	    
	u8 lightmode=0,effect=1;
	s8 saturation=0,brightness=0,contrast=0;
	
 	Stm32_Clock_Init(9);		//ϵͳʱ������
	uart_init(72,115200);		//���ڳ�ʼ��Ϊ115200
	delay_init(72);	   	 		//��ʱ��ʼ�� 	
 	LED_Init();		  			//��ʼ����LED���ӵ�Ӳ���ӿ�
	KEY_Init();					//��ʼ������
	LCD_Init();			   		//��ʼ��LCD   
 	POINT_COLOR=RED;			//��������Ϊ��ɫ 
	LCD_ShowString(30,50,200,16,16,"WarShip STM32");	
	LCD_ShowString(30,70,200,16,16,"OV7725_OV7670 TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2017/11/1"); 
	LCD_ShowString(30,130,200,16,16,"KEY0:Light Mode");
	LCD_ShowString(30,150,200,16,16,"KEY1:Saturation");
	LCD_ShowString(30,170,200,16,16,"KEY2:Brightness");
	LCD_ShowString(30,190,200,16,16,"KEY_UP:Contrast");
	LCD_ShowString(30,210,200,16,16,"TPAD:Effects");	 
  	LCD_ShowString(30,230,200,16,16,"OV7725_OV7670 Init...");	  
	while(1)//�ȴ�7725��ʼ���ɹ�
	{
		if(OV7725_Init()==0)   
		{
			sensor=OV7725;
			LCD_ShowString(30,230,200,16,16,"OV7725 Init OK       ");
			while(1)   //�ȴ�ѡ��ģʽ
			{
				key=KEY_Scan(0);
				if(key==KEY0_PRES)
				{
					OV7725_Window_Set(OV7725_WINDOW_WIDTH,OV7725_WINDOW_HEIGHT,0);//QVGAģʽ���
					i=0;
					break;
				}else if(key==KEY1_PRES)
				{
					OV7725_Window_Set(OV7725_WINDOW_WIDTH,OV7725_WINDOW_HEIGHT,1);//VGAģʽ���
					i=0;
					break;
				}
				i++;
				if(i==100)LCD_ShowString(30,250,210,16,16,"KEY0:QVGA  KEY1:VGA"); //��˸��ʾ��ʾ��Ϣ
				if(i==200)
				{	
					LCD_Fill(30,250,210,250+16,WHITE);
					i=0; 
				}
				delay_ms(5);
			}				
			OV7725_Light_Mode(lightmode);
			OV7725_Color_Saturation(saturation);
			OV7725_Brightness(brightness);
			OV7725_Contrast(contrast);
			OV7725_Special_Effects(effect);
			OV7725_CS=0;
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
	delay_ms(200);
	POINT_COLOR=RED;
	LCD_DrawRectangle(16,150,19,154);
	LCD_DrawRectangle(100,10,104,13);
	LCD_DrawRectangle(205,150,208,154);
 	while(1)
	{	
		
		if(sensor==OV7725) OV7725_camera_refresh();		//������ʾ
//		switch(flag)
//		{
//			case 2:LCD_ShowString(1,1,40,16,16,"BLACK");break;
//			case 1:LCD_ShowString(1,1,40,16,16,"WHITE");break;
////			case 2:LCD_ShowString(1,1,40,16,16,"LEFT");break;
////			case 3:LCD_ShowString(1,1,40,16,16,"RIGHT");break;
//		}
			LCD_DrawRectangle(16,150,19,154);
	LCD_DrawRectangle(100,10,104,13);
	LCD_DrawRectangle(205,150,208,154);
				LCD_ShowNum(10,300,color1&0x80,1,16);
				LCD_ShowNum(18,300,color1&0x40,1,16);	
				LCD_ShowNum(26,300,color1&0x20,1,16);	
				LCD_ShowNum(34,300,color1&0x10,1,16);	
				LCD_ShowNum(42,300,color1&0x08,1,16);	
				LCD_ShowNum(50,300,color1&0x04,1,16);	
				LCD_ShowNum(58,300,color1&0x02,1,16);	
				LCD_ShowNum(64,300,color1&0x01,1,16);
	}	   
}











