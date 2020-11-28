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


#define  OV7670 2
const u8*LMODE_TBL[6]={"Auto","Sunny","Cloudy","Office","Home","Night"};//6�ֹ���ģʽ	    
const u8*EFFECTS_TBL[7]={"Normal","Negative","B&W","Redish","Greenish","Bluish","Antique"};	//7����Ч 
extern u8 ov_sta;	//��exit.c�� �涨��
extern u8 ov_frame;	//��timer.c���涨��
u16 Black_dot;
u16 black_left,black_right,black_down,black_under;   //��¼�߽�ڵ������ֵ
u16 black_x,black_y;   //��¼��ǰ�ڵ������ֵ


//����LCD��ʾ(OV7670)
void OV7670_camera_refresh(void)
{
	u32 j;
 	u16 color;
	u8 r,g,b;
    u16 w_x,w_y;	
	if(ov_sta)//��֡�жϸ���
	{
		LCD_Scan_Dir(U2D_L2R);		//���ϵ���,������  
		if(lcddev.id==0X1963)LCD_Set_Window((lcddev.width-240)/2,(lcddev.height-320)/2,240,320);//����ʾ�������õ���Ļ����
		LCD_WriteRAM_Prepare();     //��ʼд��GRAM	
		OV7670_RRST=0;				//��ʼ��λ��ָ�� 
		OV7670_RCK_L;
		OV7670_RCK_H;
		OV7670_RCK_L;
		OV7670_RRST=1;				//��λ��ָ����� 
		OV7670_RCK_H;
		for(j=0;j<76800;j++)
		{
			OV7670_RCK_L;
			color=GPIOC->IDR&0XFF;	//������
			OV7670_RCK_H; 
			color<<=8;  
			OV7670_RCK_L;
			color|=GPIOC->IDR&0XFF;	//������
			OV7670_RCK_H; 
			w_x=j/320;
			w_y=j%320;
			r=(color&0xf800)>>8;
			g=(color&0x07e0)>>3;
			b=(color&0x001f)<<3;
			if(r<50&&g<50&&b<50) 
			{
			color=0x0000;
				r=0x00;
				g=0x00;
				b=0x00;
			}
			else
			{
				color=0xffff;
				r=0xff;
				g=0xff;
				b=0xff;
			}			
				
			if(w_x>21&&w_x<219&&w_y>21&&w_y<299&&r==0x00&&g==0x00&&b==0x00)    //���ֺڵ�
			{
		  Black_dot++;
		if(w_x>=black_right) 
		{
			black_right=w_x;
			if(black_left==0)  black_left=w_x;
		}			
		if(w_y>=black_down)   
		{
			black_down=w_y;
			if(black_under==0)
			{
				black_under=w_y;
			}
		}  
		if(w_y<black_under)  black_under=w_y;
			}
			LCD->LCD_RAM=color; 		

			
		}  
 		ov_sta=0;					//����֡�жϱ��
		ov_frame++; 

		LCD_Scan_Dir(DFT_SCAN_DIR);	//�ָ�Ĭ��ɨ�跽�� 
		LCD_ShowNum(40,40,Black_dot,8,16);
LCD_ShowNum(40,60,black_right,8,16);	
LCD_ShowNum(40,80,black_left,8,16);	
LCD_ShowNum(40,100,black_down,8,16);	
LCD_ShowNum(40,120,black_under,8,16);			
		POINT_COLOR=BLACK;
		LCD_DrawRectangle(20,20,220,300);
		POINT_COLOR=YELLOW;
////		LCD_DrawRectangle(25,50,50,100);
		LCD_DrawRectangle(black_left,black_under,black_right,black_down);
//		POINT_COLOR=RED;
//		LCD_DrawLine(black_left+(black_right-black_left)/2,black_under,black_left+(black_right-black_left)/2,black_down);
//		LCD_DrawLine(black_left,black_under+(black_down-black_under)/2,black_right,black_under+(black_down-black_under)/2);	
		black_right=black_left=black_down=black_under=Black_dot=0;
	}
}	   



int main(void)
{		
	u8 sensor=0;
	u8 lightmode=0,effect=0;
	s8 saturation=0,brightness=0,contrast=0;	

	Stm32_Clock_Init(9);	//ϵͳʱ������
	delay_init(72);	  		//��ʱ��ʼ��
	uart_init(72,115200); 	//���ڳ�ʼ��Ϊ115200
	LCD_Init();
	W25QXX_Init();				//��ʼ��W25Q128 ��SPI2
	POINT_COLOR=RED;
	tp_dev.init();			//��������ʼ�� 
	while(font_init()) 			//����ֿ�
	{;}  
	POINT_COLOR=RED;			//��������Ϊ��ɫ 
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
//	Show_Str(30,50,200,16,"ս��STM32F103������",16,0);	
	while(1)//��ʼ��OV7725_OV7670
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
			OV7670_Window_Set(12,176,240,320);//���ô���
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

	TIM6_Int_Init(9999,7199);			//10Khz����Ƶ��,1�����ж�	
	EXTI8_Init();						//ʹ���ⲿ�ж�8,����֡�ж�			
	LCD_Clear(BLACK);		
//	color1=0xffff;     //��ֵ  
		while(1)
	{
		if(sensor==OV7670)OV7670_camera_refresh();	//������ʾ

			
		
//		Show_Str(30,260,168,12,"�е���ɫֵΪ:",12,0);	
	
	}
} 





//		printf("t:%d\r\n",t);

