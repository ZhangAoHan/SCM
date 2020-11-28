#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "lcd.h"
#include "touch.h"  
#include "w25qxx.h"  
#include "text.h"	 
#include "fdc2214.h"
#include "IIC.h"
#include "display.h"	 
#include "timer.h"
#include "control.h"

u8 flag=0;                               //��������־λ     flag=0  ��ȭ����  flag=1 ʶ������   Ĭ�ϲ�ȭ����
u8 cle;                                  //�����л�ҳ��������־��   Ϊ�˽���л������BUG
u8 mode_selsct=0;                        //ͨ��ѡ��
u8 mode;                                 //����ѡ��
            /*2214��Ҫ�ı��� */
uint32_t date2;
uint32_t fre2;
uint32_t fre2_init_min,fre2_init_max;    //���10000���� �ҵ����ֵ����Сֵ
uint32_t ch2_middle,ch2_wave;            //��ֵ�Ͳ�������
uint32_t by2,bb2,sy2,sb2,jy2,jb2;        //ʹϵͳ���д洢����
uint32_t y1,b1,y2,b2,y3,b3,y4,b4,y5,b5;  //ʹϵͳ���д洢����
uint32_t result2;                        //����ƽ���˲�
uint32_t fre2_last;                      //һ���˲�

int main(void)
{				 
	Stm32_Clock_Init(9);		//ϵͳʱ������
	delay_init(72);	  			//��ʱ��ʼ��
	uart_init(72,115200); 		//���ڳ�ʼ��Ϊ115200
/*   TFT��ʾ��ʼ������         */
	LCD_Init();
	W25QXX_Init();				//��ʼ��W25Q128 ��SPI2
	tp_dev.init();			    //��������ʼ�� 
	while(font_init()) 			//����ֿ�
	{;}  
		
/*  FDC2214��ʼ������   */
	IIC_Init1();
	FDC2214_Init();  			//���2214
	//��fre2_last����ֵ
	FDC2214_GetChannelData(FDC2214_Channel_2, &date2);
	fre2_last = FDC2214_CalculateFrequency(FDC2214_Channel_2, date2);    

/*��ʱ����ʼ��  ÿ��100ms���һ���Ƿ��а�������*/
	TIM3_Int_Init(999,7199);//10Khz�ļ���Ƶ�ʣ�����1K��Ϊ100ms  
	
	LCD_Clear(WHITE);
		while(1)
	{
		if(flag==0)  //��ȭʶ��
			{
				if(cle==1)
					{
						if(bb2!=0&&by2!=0&&sy2!=0&&sb2!=0&&jy2!=0&&jb2!=0)  //ͨ��2ѧϰ���  
							{
								Show_Str(11,1,96,24,"ѧϰ���",24,0);
								C_Feedback();
							}
						else
							{
								Show_Str(11,1,96,24,"����ѧϰ",24,0);
							}
						FDC2214read();
						C_control();	
					}
				else
					{
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
						cle=1;
					}
			}
		else   //����ʶ��
		{
			if(cle==1)
				{
					if(y1!=0&&b1!=0&&y2!=0&&b2!=0&&y3!=0&&b3!=0&&y4!=0&&b4!=0&&y5!=0&&b5!=0)  //ͨ��2ѧϰ���  
						{
							Show_Str(11,1,96,24,"ѧϰ���",24,0);
							S_Feedback();
						}
					else
						{
							Show_Str(11,1,96,24,"����ѧϰ",24,0);
						}
					FDC2214read();
					S_control();
				}
			else
				{
					LCD_Clear(WHITE);
					POINT_COLOR=BLUE;
					LCD_DrawRectangle(10,60 ,230 ,310);   //������
					Show_Str(11,61,192,24,"�����ȭʶ�����",24,0);
					POINT_COLOR=RED;   
					Show_Str(11,90,84,24,"ͨ��2��",24,0);
					POINT_COLOR=BLUE;	
					Show_Str(60,120,48,24,"��ֵ",24,0);
					Show_Str(120,120,96,24,"������Χ",24,0);	
					Show_Str(11,150,48,24,"��1",24,0);
					Show_Str(11,180,48,24,"��2",24,0);
					Show_Str(11,210,48,24,"��3",24,0);
					Show_Str(11,240,48,24,"��4",24,0);
					Show_Str(11,270,48,24,"��5",24,0);
					cle=1;
				}
			}
	}	
	
} 




