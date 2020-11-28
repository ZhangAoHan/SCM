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
#include "math.h" 

#define  OV7670 2
const u8*LMODE_TBL[6]={"Auto","Sunny","Cloudy","Office","Home","Night"};//6�ֹ���ģʽ	    
const u8*EFFECTS_TBL[7]={"Normal","Negative","B&W","Redish","Greenish","Bluish","Antique"};	//7����Ч 
extern u8 ov_sta;	//��exit.c�� �涨��
extern u8 ov_frame;	//��timer.c���涨��
//u16 Black_dot;
u16 black_left,black_right,black_down,black_under;   //��¼�߽�ڵ������ֵ
u16 black_x,black_y;   //��¼��ǰ�ڵ������ֵ
u16 dot_all;   //�߽������ظ���
u16 dot_duty;  //�߽�ֵ�ڵĺڵ����
u16 black_left_x,black_left_y,black_right_x,black_right_y,black_down_x,black_down_y,black_under_x,black_under_y;
u8 Dot_x[2000]; 
u16 draw1,draw2,draw3;
/*
   ��������Ҫ��
1����ͼ���ֵ��
2������ͼ��߽�����ֵ��black_left,black_right,black_down,black_under��
3����ͼ��У׼

*/
//����LCD��ʾ(OV7670)
void OV7670_camera_refresh(void)
{
	u32 j,i;
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
			//��ͼ���ֵ��
			if(r<65&&g<65&&b<65) 
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
       //����ͼ����״���򣨿�б��
      		if(w_x>21&&w_x<219&&w_y>21&&w_y<299&&r==0x00&&g==0x00&&b==0x00)    //���ֺڵ�
			{
				dot_duty++;
				Dot_x[i]=w_x;
				i++;
				if(w_x>=black_right_x) 
				{
					black_right_x=w_x;
					black_right_y=w_y;     //��¼x���ֵʱ�ĵ�
					if(black_left_x==0)
					{
						black_left_x=w_x;
						black_left_y=w_y; 
					}
				}
				if(w_x<black_left_x) black_left_x=w_x,black_left_y=w_y;     //��¼x��Сֵʱ�ĵ�
				if(w_y>=black_down_y) 
				{
					black_down_y=w_y;
					black_down_x=w_x;    //��¼y���ֵ�ĵ�
					if(black_under_y==0)
					{
						black_under_y=w_y;
						black_under_x=w_x; 
					}
				}
				if(w_y<black_under_y) black_under_y=w_y,black_under_x=w_x;  //��¼y��Сֵ�ĵ�			
			}							
			
			LCD->LCD_RAM=color; 					
		}  
 		ov_sta=0;					//����֡�жϱ��
		ov_frame++; 
		LCD_Scan_Dir(DFT_SCAN_DIR);	//�ָ�Ĭ��ɨ�跽�� 		
		POINT_COLOR=BLACK;
		LCD_DrawRectangle(20,20,220,300);
		POINT_COLOR=YELLOW;
		LCD_DrawLine(black_left_x,black_under_y,black_right_x,black_under_y);  
		LCD_DrawLine(black_left_x,black_down_y,black_right_x,black_down_y);   
		LCD_DrawLine(black_left_x,black_under_y,black_left_x,black_down_y);   //������
		LCD_DrawLine(black_right_x,black_under_y,black_right_x,black_down_y);   //������
//		LCD_DrawLine(black_left_x,black_left_y,black_right_x,black_right_y);   //ʮ����(�Խ���)
//		LCD_DrawLine(black_under_x,black_under_y,black_down_x,black_down_y);   //ʮ����	
			//���������ظ���
		dot_all=(black_right_x-black_left_x)*(black_down_y-black_under_y);
		
		if((black_right_x-black_left_x)>=3)
		{
			u8 draw=(black_right_x-black_left_x)/3;
			for(j=0;j<=i;j++)
			{
				if(Dot_x[j]>=black_left_x&&Dot_x[j]<(black_left_x+draw)) draw1++;
				if(Dot_x[j]>=(black_left_x+draw)&&Dot_x[j]<(black_left_x+2*draw)) draw2++;
				if(Dot_x[j]>=(black_left_x+2*draw)&&Dot_x[j]<black_right_x) draw3++;
			}
		}
		

		
				

		POINT_COLOR=BLACK;
		
				//�жϺ���
		
		if(dot_duty!=0&&draw2>draw1&&draw2>draw3)   
		{
			if(draw3>draw1*1.5)LCD_ShowNum(100,40,7,8,24);
			else
				LCD_ShowNum(100,40,1,8,24);
		}
		if(dot_duty!=0&&(draw1+draw3)*2>dot_duty&&draw2<draw1&&draw2<draw3)  LCD_ShowNum(100,40,0,8,24);   //0  2  3 5 6 8 9
		
		LCD_ShowNum(10,50,draw1,8,16);
		LCD_ShowNum(10,70,draw2,8,16);
		LCD_ShowNum(10,90,draw3,8,16);
		LCD_ShowNum(10,130,dot_all,8,16);
		LCD_ShowNum(10,150,dot_duty,8,16);		
//		Show_Str(25,40,72,24,"�����",24,0);	
//		LCD_ShowNum(100,40,dot_all,8,16);
//		Show_Str(25,70,72,24,"ռ�ձ�",24,0);	
//		LCD_ShowNum(100,70,dot_duty,8,16);
		black_left_x=black_right_x=black_down_x=black_under_x=0,black_left_y=black_right_y=black_down_y=black_under_y=dot_duty=dot_all=0;
		draw1=draw2=draw3=0;
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

