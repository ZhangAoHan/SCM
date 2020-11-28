#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "lcd.h"
#include "touch.h"  
#include "w25qxx.h"  
#include "text.h"	 
#include "fdc2214.h"
#include "IIC.h"
#include "timer.h"    
uint32_t date2;
uint32_t fre2;
uint32_t fre2_init_min,fre2_init_max;  //���10000���� �ҵ����ֵ����Сֵ
uint32_t ch2_middle,ch2_wave; //��ֵ�Ͳ�������
uint32_t by2,bb2,sy2,sb2,jy2,jb2;  //ʹϵͳ���д洢����
uint32_t y1,b1,y2,b2,y3,b3,y4,b4,y5,b5;  //ʹϵͳ���д洢����
//��������ѡ��
u8 mode_selsct=0;   //ͨ��ѡ��
u8 mode;  //����ѡ��
//����ƽ���˲�
uint32_t result2;
//һ���˲�
uint32_t fre2_last;
//��������־λ
u8 flag;
void FDC2214read(void);
void Display(void);
void Scan_sjb(void);  //���ʯͷ����������
void Feedback(void);    //������ʾ����
void Display_sz(void);
void Feedback_sz(void);

int main(void)
{		
//	u8 j;	
	Stm32_Clock_Init(9);	//ϵͳʱ������
	delay_init(72);	  		//��ʱ��ʼ��
	uart_init(72,115200); 	//���ڳ�ʼ��Ϊ115200
	TIM3_Int_Init(999,7199);//10Khz�ļ���Ƶ�ʣ�����5K��Ϊ100ms  
	LCD_Init();
	W25QXX_Init();				//��ʼ��W25Q128 ��SPI2
	tp_dev.init();			//��������ʼ�� 
	IIC_Init1();
	FDC2214_Init();  //���2214
	while(font_init()) 			//����ֿ�
	{;}  
    FDC2214_GetChannelData(FDC2214_Channel_2, &date2);
	fre2 = FDC2214_CalculateFrequency(FDC2214_Channel_2, date2);    
	fre2_last=fre2;	
	LCD_Clear(WHITE);
	POINT_COLOR=BLUE;
	LCD_DrawRectangle(10,60 ,230 ,310);   //������
	Show_Str(11,61,192,24,"��������ʶ�����",24,0);
	POINT_COLOR=RED;   
	Show_Str(11,90,84,24,"ͨ��2��",24,0);
	POINT_COLOR=BLUE;	
	Show_Str(60,150,48,24,"��ֵ",24,0);
	Show_Str(120,150,96,24,"������Χ",24,0);	
	Show_Str(11,180,48,24,"ʯͷ",24,0);
	POINT_COLOR=BLUE;
	Show_Str(11,210,48,24,"����",24,0);
	Show_Str(11,240,48,24,"��",24,0);
		while(1)
	{
		if(flag==0)  //��ȭʶ��
		{
			if(bb2!=0&&by2!=0&&sy2!=0&&sb2!=0&&jy2!=0&&jb2!=0)  //ͨ��2ѧϰ���  
		{
			Show_Str(11,1,96,24,"ѧϰ���",24,0);
			Feedback();
		}
		else
		{
			Show_Str(11,1,96,24,"����ѧϰ",24,0);
		}
	FDC2214read();
	Display();	
		}
		else   //����ʶ��
		{
					if(y1!=0&&b1!=0&&y2!=0&&b2!=0&&y3!=0&&b3!=0&&y4!=0&&b4!=0&&y5!=0&&b5!=0)  //ͨ��2ѧϰ���  
		{
			Show_Str(11,1,96,24,"ѧϰ���",24,0);
			Feedback_sz();
		}
		else
		{
			Show_Str(11,1,96,24,"����ѧϰ",24,0);
		}
	FDC2214read();
	Display_sz();	
		}

	}
} 
void FDC2214read(void)
{
	u8 i;
	for(i=0;i<30;i++)
	{
        FDC2214_GetChannelData(FDC2214_Channel_2, &date2);
	    fre2 = FDC2214_CalculateFrequency(FDC2214_Channel_2, date2);    
	//����ƽ���˲�
		result2	=result2+fre2;
		i++;
	}
	fre2=result2/30;
	fre2=result2/30*0.8+fre2_last*0.2;
	fre2_last=fre2;
	result2=0;
}
/*
ͨ����ʱ��Ч�ļ�С�˰������ƶԲ�����Χ��Ӱ�죬����Ҫת��λ�� �ǲ����ﵽ1000����  Ч�����
*/
void Display(void)   
{
	u8 i;
	POINT_COLOR=RED;        //��ɫ����
	Show_Str(11,90,84,24,"ͨ��2��",24,0);
	if(mode_selsct==1)   //ѡ��ʯͷ����ѧϰ��ֵ
	{   
	
	for(i=0;i<10;i++)   //��ʱ  ��С�������ƶԲ�����Ӱ��
		{
		FDC2214read();
	fre2_init_min=fre2_init_max=fre2;   //����ֵ
		}
	POINT_COLOR=RED;
	Show_Str(11,180,48,24,"ʯͷ",24,0);

		for(i=0;i<100;i++)
		{
			Scan_sjb();     //ѧϰ��ֵ		
			POINT_COLOR=BLACK;
			LCD_ShowxNum(96,94,fre2,8,16,0);	
			LCD_ShowxNum(60,184,ch2_middle,8,16,0);	   //��ʾ��ֵ
			LCD_ShowxNum(130,184,ch2_wave,5,16,0);    //��ʾ������Χ
		}
	sy2=ch2_middle;
	sb2=ch2_wave;
	POINT_COLOR=BLUE;  
	Show_Str(11,180,48,24,"ʯͷ",24,0);
	mode_selsct=0;
	}
	if(mode_selsct==2)   //ѡ�����
	{      
	for(i=0;i<10;i++)   //��ʱ  ��С�������ƶԲ�����Ӱ��
		{
		FDC2214read();
	fre2_init_min=fre2_init_max=fre2;   //����ֵ
		}
	POINT_COLOR=RED;
	Show_Str(11,210,48,24,"����",24,0);
	FDC2214read();
	fre2_init_min=fre2_init_max=fre2;   //����ֵ
		for(i=0;i<100;i++)
		{
			Scan_sjb();     //ѧϰ��ֵ		
			POINT_COLOR=BLACK;
			LCD_ShowxNum(96,94,fre2,8,16,0);	
			LCD_ShowxNum(60,214,ch2_middle,8,16,0);	   //��ʾ��ֵ
			LCD_ShowxNum(130,214,ch2_wave,5,16,0);    //��ʾ������Χ
		}
	jy2=ch2_middle;
	jb2=ch2_wave;
	POINT_COLOR=BLUE;  
	Show_Str(11,210,48,24,"����",24,0);
	mode_selsct=0;
	}
	if(mode_selsct==3)   //ѡ��
	{      
	for(i=0;i<10;i++)   //��ʱ  ��С�������ƶԲ�����Ӱ��
		{
		FDC2214read();
	fre2_init_min=fre2_init_max=fre2;   //����ֵ
		}
	POINT_COLOR=RED;
	Show_Str(11,240,48,24,"��",24,0);
	FDC2214read();
	fre2_init_min=fre2_init_max=fre2;   //����ֵ
		for(i=0;i<100;i++)
		{
			Scan_sjb();     //ѧϰ��ֵ		
			POINT_COLOR=BLACK;
			LCD_ShowxNum(96,94,fre2,8,16,0);	
			LCD_ShowxNum(60,244,ch2_middle,8,16,0);	   //��ʾ��ֵ
			LCD_ShowxNum(130,244,ch2_wave,5,16,0);    //��ʾ������Χ
		}
	by2=ch2_middle;
	bb2=ch2_wave;
	POINT_COLOR=BLUE;  
	Show_Str(11,240,48,24,"��",24,0);
	mode_selsct=0;
	}
	//��ʾ���ֵ  ��ʹϵͳ���д洢����
			POINT_COLOR=BLACK;
			LCD_ShowxNum(60,184,sy2,8,16,0);	   //��ʾ��ֵ
			LCD_ShowxNum(130,184,sb2,5,16,0);    //��ʾ������Χ
			LCD_ShowxNum(60,214,jy2,8,16,0);	   //��ʾ��ֵ
			LCD_ShowxNum(130,214,jb2,5,16,0);    //��ʾ������Χ
			LCD_ShowxNum(60,244,by2,8,16,0);	   //��ʾ��ֵ
			LCD_ShowxNum(130,244,bb2,5,16,0);    //��ʾ������Χ
	
	
	POINT_COLOR=BLACK;
	LCD_ShowxNum(96,94,fre2,8,16,0);	
}
void Display_sz(void)
{
	u8 i;
	POINT_COLOR=RED;        //��ɫ����
	Show_Str(11,90,84,24,"ͨ��2��",24,0);
	if(mode_selsct==1)   //����1
	{      
	POINT_COLOR=RED;
	Show_Str(11,150,60,24,"��1",24,0);
	FDC2214read();
	fre2_init_min=fre2_init_max=fre2;   //����ֵ
		for(i=0;i<100;i++)
		{
			Scan_sjb();     //ѧϰ��ֵ		
			POINT_COLOR=BLACK;
			LCD_ShowxNum(96,94,fre2,8,16,0);	
			LCD_ShowxNum(60,154,ch2_middle,8,16,0);	   //��ʾ��ֵ
			LCD_ShowxNum(130,154,ch2_wave,5,16,0);    //��ʾ������Χ
		}
	y1=ch2_middle;
	b1=ch2_wave;
	POINT_COLOR=BLUE;  
	Show_Str(11,150,48,24,"��1",24,0);
	mode_selsct=0;
	}
	if(mode_selsct==2)   //��2
	{      
	POINT_COLOR=RED;
	Show_Str(11,180,48,24,"��2",24,0);
	FDC2214read();
	fre2_init_min=fre2_init_max=fre2;   //����ֵ
		for(i=0;i<100;i++)
		{
			Scan_sjb();     //ѧϰ��ֵ		
			POINT_COLOR=BLACK;
			LCD_ShowxNum(96,94,fre2,8,16,0);	
			LCD_ShowxNum(60,184,ch2_middle,8,16,0);	   //��ʾ��ֵ
			LCD_ShowxNum(130,184,ch2_wave,5,16,0);    //��ʾ������Χ
		}
	y2=ch2_middle;
	b2=ch2_wave;
	POINT_COLOR=BLUE;  
	Show_Str(11,180,48,24,"��2",24,0);
	mode_selsct=0;
	}
	if(mode_selsct==3)   //����3
	{      
	POINT_COLOR=RED;
	Show_Str(11,210,48,24,"��3",24,0);
	FDC2214read();
	fre2_init_min=fre2_init_max=fre2;   //����ֵ
		for(i=0;i<100;i++)
		{
			Scan_sjb();     //ѧϰ��ֵ		
			POINT_COLOR=BLACK;
			LCD_ShowxNum(96,94,fre2,8,16,0);	
			LCD_ShowxNum(60,214,ch2_middle,8,16,0);	   //��ʾ��ֵ
			LCD_ShowxNum(130,214,ch2_wave,5,16,0);    //��ʾ������Χ
		}
	y3=ch2_middle;
	b3=ch2_wave;
	POINT_COLOR=BLUE;  
	Show_Str(11,210,48,24,"��3",24,0);
	mode_selsct=0;
	}
		if(mode_selsct==4)   //����4
	{      
	POINT_COLOR=RED;
	Show_Str(11,240,48,24,"��4",24,0);
	FDC2214read();
	fre2_init_min=fre2_init_max=fre2;   //����ֵ
		for(i=0;i<100;i++)
		{
			Scan_sjb();     //ѧϰ��ֵ		
			POINT_COLOR=BLACK;
			LCD_ShowxNum(96,94,fre2,8,16,0);	
			LCD_ShowxNum(60,244,ch2_middle,8,16,0);	   //��ʾ��ֵ
			LCD_ShowxNum(130,244,ch2_wave,5,16,0);    //��ʾ������Χ
		}
	y4=ch2_middle;
	b4=ch2_wave;
	POINT_COLOR=BLUE;  
	Show_Str(11,240,48,24,"��4",24,0);
	mode_selsct=0;
	}
		if(mode_selsct==5)   //����5
	{      
	POINT_COLOR=RED;
	Show_Str(11,270,48,24,"��5",24,0);
	FDC2214read();
	fre2_init_min=fre2_init_max=fre2;   //����ֵ
		for(i=0;i<100;i++)
		{
			Scan_sjb();     //ѧϰ��ֵ		
			POINT_COLOR=BLACK;
			LCD_ShowxNum(96,94,fre2,8,16,0);	
			LCD_ShowxNum(60,274,ch2_middle,8,16,0);	   //��ʾ��ֵ
			LCD_ShowxNum(130,274,ch2_wave,5,16,0);    //��ʾ������Χ
		}
	y5=ch2_middle;
	b5=ch2_wave;
	POINT_COLOR=BLUE;  
	Show_Str(11,270,48,24,"��5",24,0);
	mode_selsct=0;
	}
	//��ʾ���ֵ  ��ʹϵͳ���д洢����
			POINT_COLOR=BLACK;
			LCD_ShowxNum(60,154,y1,8,16,0);	   //��ʾ��ֵ
			LCD_ShowxNum(130,154,b1,5,16,0);    //��ʾ������Χ
			LCD_ShowxNum(60,184,y2,8,16,0);	   //��ʾ��ֵ
			LCD_ShowxNum(130,184,b2,5,16,0);    //��ʾ������Χ
			LCD_ShowxNum(60,214,y3,8,16,0);	   //��ʾ��ֵ
			LCD_ShowxNum(130,214,b3,5,16,0);    //��ʾ������Χ
			LCD_ShowxNum(60,244,y4,8,16,0);	   //��ʾ��ֵ
			LCD_ShowxNum(130,244,b4,5,16,0);    //��ʾ������Χ
			LCD_ShowxNum(60,274,y5,8,16,0);	   //��ʾ��ֵ
			LCD_ShowxNum(130,274,b5,5,16,0);    //��ʾ������Χ
	
	
	POINT_COLOR=BLACK;
	LCD_ShowxNum(96,94,fre2,8,16,0);	
}

void Scan_sjb(void)  //���ʯͷ����������
{
		FDC2214read();
		if(fre2<fre2_init_min) fre2_init_min=fre2;
		if(fre2>fre2_init_max) fre2_init_max=fre2;

		ch2_middle=(fre2_init_min+fre2_init_max)/2;
		ch2_wave=((ch2_middle-fre2_init_min)+(fre2_init_max-ch2_middle))/2;
			
}


void Feedback(void)    //������ʾ����
{	
	if(fre2>sy2&&(fre2-sy2)<(sb2*1.5))   Show_Str(11,30,48,24,"ʯͷ",24,0);   //��⵽ʯͷ

	else if(fre2<sy2&&(sy2-fre2)<(sb2*1.5))   Show_Str(11,30,48,24,"ʯͷ",24,0);  //��⵽ʯͷ

	
	else if(fre2>jy2&&(fre2-jy2)<(jb2*1.5))  Show_Str(11,30,48,24,"����",24,0);   //��⵽����

	else if(fre2<jy2&&(jy2-fre2)<(jb2*1.5))  Show_Str(11,30,48,24,"����",24,0);     //��⵽����

	else if(fre2>by2&&(fre2-by2)<(bb2*1.5))  Show_Str(11,30,48,24,"  ��",24,0);     //��⵽��

	else if(fre2<by2&&(by2-fre2)<(bb2*1.5)) Show_Str(11,30,48,24,"  ��",24,0);     //��⵽��

	else Show_Str(1,30,240,24,"            ",24,0); 
	
}
void Feedback_sz(void)    //������ʾ����
{	
	if(fre2>y1&&(fre2-y1)<(b1*0.8))   Show_Str(11,30,48,24,"1",24,0);   

	else if(fre2<y1&&(y1-fre2)<(b1*0.8))   Show_Str(11,30,48,24,"1",24,0);  

	
	else if(fre2>y2&&(fre2-y2)<(b2*0.8))   Show_Str(11,30,48,24,"2",24,0);   

	else if(fre2<y2&&(y2-fre2)<(b2*0.8))   Show_Str(11,30,48,24,"2",24,0);  

	else if(fre2>y3&&(fre2-y3)<(b3*0.8))   Show_Str(11,30,48,24,"3",24,0);  

	else if(fre2<y3&&(y3-fre2)<(b3*0.8))   Show_Str(11,30,48,24,"3",24,0);
	
	else if(fre2>y4&&(fre2-y4)<(b4*0.8))   Show_Str(11,30,48,24,"4",24,0);  

	else if(fre2<y4&&(y4-fre2)<(b4*0.8))   Show_Str(11,30,48,24,"4",24,0); 
	
	else if(fre2>y5&&(fre2-y5)<(b5*0.8))   Show_Str(11,30,48,24,"5",24,0);  

	else if(fre2<y5&&(y5-fre2)<(b5*0.8))   Show_Str(11,30,48,24,"5",24,0); 	

	else Show_Str(11,30,240,24,"0",24,0); 
	
}
