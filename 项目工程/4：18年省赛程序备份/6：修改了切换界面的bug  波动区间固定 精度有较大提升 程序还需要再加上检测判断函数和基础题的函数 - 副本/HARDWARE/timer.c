#include "timer.h"
#include "touch.h" 
#include "lcd.h"
#include "text.h"
#include "fdc2214.h"

extern u8 ch_selsct,mode_selsct;
extern u8 flag;
extern uint32_t date2;
extern uint32_t fre2;
extern uint32_t fre2_last;
extern u8 cle;
//��ʱ��3�жϷ������	 ��ʱ����Ƿ��д������� 
void TIM3_IRQHandler(void)
{ 		    		  			    
	if(TIM3->SR&0X0001)//����ж�
	{
	Rtp_Scan();	    				   				     	    	
	}				   
	TIM3->SR&=~(1<<0);//����жϱ�־λ 	    
}
//ͨ�ö�ʱ��3�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<1;	//TIM3ʱ��ʹ��    
 	TIM3->ARR=arr;  	//�趨�������Զ���װֵ//�պ�1ms    
	TIM3->PSC=psc;  	//Ԥ��Ƶ��7200,�õ�10Khz�ļ���ʱ��		  
	TIM3->DIER|=1<<0;   //��������ж�	  
	TIM3->CR1|=0x01;    //ʹ�ܶ�ʱ��3
  	MY_NVIC_Init(1,3,TIM3_IRQn,2);//��ռ1�������ȼ�3����2									 
}
void Rtp_Scan(void)   //����������⺯��
{
			tp_dev.scan(0); 		 
		if(tp_dev.sta&TP_PRES_DOWN)			//������������
		{	
		 	if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
			{	
				if(flag==0)    //��ȭ����
				{
				if(tp_dev.x[0]>11&&tp_dev.x[0]<60&&tp_dev.y[0]>180&&tp_dev.y[0]<205)//���ʯͷ
				{
					mode_selsct=1;
				}
				if(tp_dev.x[0]>11&&tp_dev.x[0]<60&&tp_dev.y[0]>210&&tp_dev.y[0]<235)//�������
				{
					mode_selsct=2;
				}
				if(tp_dev.x[0]>11&&tp_dev.x[0]<60&&tp_dev.y[0]>240&&tp_dev.y[0]<265)//�����
				{
					mode_selsct=3;
				}
					if(tp_dev.x[0]>11&&tp_dev.x[0]<203&&tp_dev.y[0]>61&&tp_dev.y[0]<85)//�����
				{
						flag=1;   //��������ʶ�����
						cle=0;
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
				}
				}	
						else
						{
				if(tp_dev.x[0]>11&&tp_dev.x[0]<75&&tp_dev.y[0]>150&&tp_dev.y[0]<175)//����1
				{
					mode_selsct=1;
				}
				if(tp_dev.x[0]>11&&tp_dev.x[0]<75&&tp_dev.y[0]>180&&tp_dev.y[0]<205)//����2
				{
					mode_selsct=2;
				}
				if(tp_dev.x[0]>11&&tp_dev.x[0]<75&&tp_dev.y[0]>210&&tp_dev.y[0]<235)//����3
				{
					mode_selsct=3;
				}
			   	if(tp_dev.x[0]>11&&tp_dev.x[0]<75&&tp_dev.y[0]>240&&tp_dev.y[0]<265)//����4
				{
					mode_selsct=4;
				}
				if(tp_dev.x[0]>11&&tp_dev.x[0]<75&&tp_dev.y[0]>270&&tp_dev.y[0]<295)//����5
				{
					mode_selsct=5;
				}
				if(tp_dev.x[0]>11&&tp_dev.x[0]<203&&tp_dev.y[0]>61&&tp_dev.y[0]<85)//�����
				{
						flag=0;   //�����ȭʶ�����
						cle=0;
//				FDC2214_GetChannelData(FDC2214_Channel_2, &date2);
//				fre2 = FDC2214_CalculateFrequency(FDC2214_Channel_2, date2);    
//				fre2_last=fre2;	
				LCD_Clear(WHITE);

				}
						}	

			   
			}
}
		}












