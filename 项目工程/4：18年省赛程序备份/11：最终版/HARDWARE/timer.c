#include "timer.h"
#include "touch.h" 
#include "lcd.h"
#include "fdc2214.h"

extern u8 ch_selsct,mode_selsct;
extern u8 flag;
extern u8 cle;
extern u8 fj,fj_mode;
extern uint32_t by2,bb2,sy2,sb2,jy2,jb2;        //ʹϵͳ���д洢����
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
				if(tp_dev.x[0]>2&&tp_dev.x[0]<50&&tp_dev.y[0]>160&&tp_dev.y[0]<184)//���ʯͷ
				{
					mode_selsct=1;
				}
				if(tp_dev.x[0]>2&&tp_dev.x[0]<50&&tp_dev.y[0]>190&&tp_dev.y[0]<214)//�������
				{
					mode_selsct=2;
				}
				if(tp_dev.x[0]>2&&tp_dev.x[0]<50&&tp_dev.y[0]>220&&tp_dev.y[0]<244)//�����
				{
					mode_selsct=3;
				}
					if(tp_dev.x[0]>2&&tp_dev.x[0]<146&&tp_dev.y[0]>58&&tp_dev.y[0]<82) //��������ʶ�����
				{
						flag=1;   
						cle=0;
				}
					if(tp_dev.x[0]>2&&tp_dev.x[0]<98&&tp_dev.y[0]>247&&tp_dev.y[0]<271)// �������ӹ���
						{
							switch(fj)
							{
								case 0:fj=1;break;
								case 1:fj=0;break;					}
							
						}
					if(fj)   //����������ӹ���
						{
							if(tp_dev.x[0]>21&&tp_dev.x[0]<93&&tp_dev.y[0]>290&&tp_dev.y[0]<314)
							{
								fj_mode=1;         //��ʼ����һλ
							}
							if(tp_dev.x[0]>148&&tp_dev.x[0]<220&&tp_dev.y[0]>290&&tp_dev.y[0]<314)
							{
								fj_mode=2;         //��ʼ���ڶ�λ
							}							
						}
				

				}	
						else
						{
				if(tp_dev.x[0]>2&&tp_dev.x[0]<50&&tp_dev.y[0]>162&&tp_dev.y[0]<196)//����1
				{
					mode_selsct=1;
				}
				if(tp_dev.x[0]>2&&tp_dev.x[0]<50&&tp_dev.y[0]>190&&tp_dev.y[0]<214)//����2
				{
					mode_selsct=2;
				}
				if(tp_dev.x[0]>2&&tp_dev.x[0]<50&&tp_dev.y[0]>220&&tp_dev.y[0]<245)//����3
				{
					mode_selsct=3;
				}
			   	if(tp_dev.x[0]>2&&tp_dev.x[0]<50&&tp_dev.y[0]>250&&tp_dev.y[0]<275)//����4
				{
					mode_selsct=4;
				}
				if(tp_dev.x[0]>2&&tp_dev.x[0]<50&&tp_dev.y[0]>280&&tp_dev.y[0]<305)//����5
				{
					mode_selsct=5;
				}
				if(tp_dev.x[0]>2&&tp_dev.x[0]<146&&tp_dev.y[0]>58&&tp_dev.y[0]<82)//�����
				{
						flag=0;   //�����ȭʶ�����
						cle=0;

				}
						}			   
			}
}
		}












