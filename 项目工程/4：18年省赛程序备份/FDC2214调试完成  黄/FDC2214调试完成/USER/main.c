/****************************************

@title      FDC2214 Test File
@author		QingChuang Studio
@since		MDK5  
@version    V1.0
@remark     2018.7.16

@file       main.c


					+--------------------------------------------+
					|                                            |
					|                                            |
					|         SCL +------------------> PB10      |
					|                                            |
					| FDC2214                              STM32 |
					|         SDA +------------------> PB11      |
					|                                            |
					|                                            |
					|         3.3 +------------------> 3.3       |
					|                                            |
					|                                            |
					|          SD +------------------> GND       |
					|											 |
					|											 |
					|         GND +------------------> GND       |
					|                                            |
					+--------------------------------------------+

*****************************************/

#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "KEY.H"
#include "fdc2214.h" 
#include "timer.h"
#include "string.h"

#define Gesture_exsit   0.3	//CH3�о������ַ���
/*---��������---*/
void Mode_one(void);
void Mode_two(void);
void Mode_three(void);
void Mode_four(void);
u8 Gesture_judge(float ch0min,float ch0max,float ch1min,float ch1max,float ch2min,float ch2max);
float fbs(float temp);
float range(float temp);

/*---��������---*/
float CH_Data[4];  //ͨ��ֵ
float Temp[4];	   //�ϵ�ֵ

int Run_flag=0;
int Init_flag=0;
unsigned int Mode_flag=0;			  //ģʽ��־

unsigned Mode3_train_flag=0,Mode4_train_flag=0;//ģʽ3,4��ʼѵ����־
unsigned Mode3_train_cnt=0, Mode4_train_cnt=0;//ģʽ3,4ѵ������
unsigned Mode3_judge_flag=0,Mode4_judge_flag=0;//ģʽ3,4��ʼ���б�־
//ģʽִ�б�־����
unsigned int Initial_flag1=0,Initial_flag2=0,Initial_flag3=0,Initial_flag4=0;//��ģʽ��ʼִ�б�־
//��ʱ����
unsigned int cnt1=0;//�о��ɹ���ʱ0.5s
unsigned int cnt2=0;//�о��ɹ���ʱ2s

//ѵ������
extern float trani_ch0[200],trani_ch1[200],trani_ch2[200];//ѵ������
float sum[3];//ѵ��ʱ����200����ֵ
float avr[3];//ѵ��ʱ����200�ξ�ֵ��Ϊ��Сֵ
float shear_min[3],bone_min[3],cloth_min[3],one_min[3],two_min[3],three_min[3],four_min[3],five_min[3];//ѵ�����������Сֵ
float shear_max[3],bone_max[3],cloth_max[3],one_max[3],two_max[3],three_max[3],four_max[3],five_max[3];//ѵ������������ֵ
//float cap0_table[10],cap1_table[10],cap2_table[10];//�����ֵ����,δʹ��
//float cap0_range_max,cap1_range_max,cap2_range_max;//ÿ���о��ɹ����д�ֵ�����ֵ,δʹ��

unsigned int one_cnt=0,two_cnt=0,three_cnt=0,four_cnt=0,five_cnt=0; //�о�ʱ��μ��������ȶ���δʹ��
/*---------------------------------*
���� 	:ϵͳ��ʼ������
˵��	:��
*----------------------------------*/
void Sys_Init(void)
{
	unsigned int status=0;
	int i;
	 
	Stm32_Clock_Init(9);//ʱ�ӱ�Ƶ
	delay_init();	    	//��ʱ������ʼ��
	uart_init(9600);//����һ��ʼ��(������:9600)	 
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
	while(!status)	//��ʼ�����ɹ�,���������λ
	{
		status=FDC2214_Init();
	}
	delay_ms(1000);
	TIM3_Config(49999,72,1,1);//50ms
}

/*******************************
������	: int main(void)
���� 	:������
˵��	:
*******************************/
 int main(void)
 {	
	
	Sys_Init();
	while(1)
	{
//		printf("CH0=%f  CH1=%f  CH2=%f  CH3=%f\n",CH_Data[0],CH_Data[1],CH_Data[2],CH_Data[3]);
//		Mode_one();
//		Mode_two();
//		KEY_Scan();
//		Mode_flag=4;
		#if 1
		switch(Mode_flag)
		{
			case 0://ģʽ0
			{
				LED0=1;
				Mode3_train_flag=0;Mode4_train_flag=0;
				Mode3_judge_flag=0;Mode4_judge_flag=0;
				Initial_flag1=0;Initial_flag2=0;Initial_flag3=0;Initial_flag4=0;
				break;
			}
			/*--------------------------------------------------------------------------------------*/
			case 1:					//ģʽһ����ȭ
			{
				if(Initial_flag1==0)//���η���ģʽ�л�
				{
					Initial_flag1++;
					USART_SendData(USART1,0x01);
				    while((USART1->SR&0X40)==0);
				}
				Mode_one();
				break;
			}
			/*--------------------------------------------------------------------------------------*/
			case 2:			//ģʽ������ȭ
			{
				if(Initial_flag2==0)
				{
					Initial_flag2++;
					USART_SendData(USART1,0x02);
					while((USART1->SR&0X40)==0);
					Init_flag=0;//FDC��ֵ��λ
				}
				Mode_two();
				break;
			}
			/*--------------------------------------------------------------------------------------*/
			case 3:
			{
				if(Initial_flag3==0)
				{
					Mode3_train_cnt=0;//ģʽ3����ѵ����������
					Initial_flag3++;
					USART_SendData(USART1,0x03);
					while((USART1->SR&0X40)==0);
					Init_flag=0;//FDC��ֵ��λ
				}
				
				else if((Mode3_train_flag==0)&&(Mode3_judge_flag==1))//������
				{
					Mode_three();
				}
				break;
			}
			/*--------------------------------------------------------------------------------------*/
			case 4:
			{
				if(Initial_flag4==0)
				{
					Mode4_train_cnt=0;//ģʽ4����ѵ����������
					Initial_flag4++;
					USART_SendData(USART1,0x04);
					while((USART1->SR&0X40)==0);
					Init_flag=0;//FDC��ֵ��λ
				}
				if((Mode4_train_flag==0)&&(Mode4_judge_flag==1))//������
				{
					Mode_four();
				}
				break;
			}
			default:break;
		}
	    
		#endif
	}
 }
 /*------------------------------------------------------------------------------------------------*/
									/*MODE01*/
/*------------------------------------------------------------------------------------------------*/
 void Mode_one(void)
 {
		 if(Gesture_judge(0.25,0.35,0.05,0.25,0,0.02)==1)
		 {
			 cnt1=0;
			 printf("����\n");
			 while(cnt1<=20)//0.5s
			 {
				 LED0=0;
			 }
			 LED0=1; 
		 }
		 
		 if(Gesture_judge(0,0.25,0.47,1,0.3,0.75)==1)
		 {
			 cnt1=0;
			 printf("ʯͷ\n");
			 while(cnt1<=20)//0.5s
			 {
				 LED0=0;
			 }
			 LED0=1;
		 } 
		
		  else if(Gesture_judge(0.6,0.85,0.52,0.8,0.32,0.56)==1)
		 {
			 cnt1=0;
			 printf("��\n");
			 while(cnt1<=20)//0.5s
			 {
				 LED0=0;
			 }
			 LED0=1;
		 }
 }
 /*------------------------------------------------------------------------------------------------*/
									/*MODE02*/
/*------------------------------------------------------------------------------------------------*/
 void Mode_two(void)
 {
	 unsigned int i;
	 /*------------------1----------------------*/
	if(Gesture_judge(0.15,0.23,0,0.05,0,0.05)==1)
	{
		one_cnt++;
		if(one_cnt>=500)	//5����������
		{
			 cnt1=0;
			 printf("1\n");
			 while(cnt1<=20)//1s
			 {
				 LED0=0;
			 }
			 LED0=1;
			 Init_flag=0;
			 one_cnt=0;
		}	 
	}
	/*------------------2----------------------*/
    else if(Gesture_judge(0.28,0.4,0.09,0.23,0,0.09)==1)	
	{
		two_cnt++;
		if(two_cnt>=500)
		{
			cnt1=0;
			 printf("2\n");
			 while(cnt1<=20)//1s
			 {
				 LED0=0;
			 }
			 LED0=1;
			 Init_flag=0;
			 two_cnt=0;
		}	 
	}
	/*------------------3----------------------*/
	else if(Gesture_judge(0.40,0.52,0.15,0.35,0,0.02)==1)	
	{
		three_cnt++;
		if(three_cnt>=500)
		{
			 cnt1=0;
			 printf("3\n");
			 while(cnt1<=20)//1s
			 {
				 LED0=0;
			 }
			 LED0=1;
			 Init_flag=0;
			 three_cnt=0;
		}	
	}
	/*------------------4----------------------*/
	else if(Gesture_judge(0.5,0.71,0.47,0.68,0,0.08)==1)	
	{
		four_cnt++;
		if(four_cnt>=500)
		{
			 cnt1=0;
			 printf("4\n");
			 while(cnt1<=20)//1s
			 {
				 LED0=0;
			 }
			 LED0=1;
			 Init_flag=0;
			 four_cnt=0;
		} 
	}
	/*------------------5----------------------*/
	else if(Gesture_judge(0.6,0.85,0.52,0.8,0.32,0.56)==1)	
	{
		five_cnt++;
		if(five_cnt>=500)
		{
			 cnt1=0;
			 printf("5\n");
			 while(cnt1<=20)//1s
			 {
				 LED0=0;
			 }
			 LED0=1;
			 Init_flag=0;
			 five_cnt=0;
		} 
	}
	else
	{
		one_cnt=0;two_cnt=0;three_cnt=0;four_cnt=0;five_cnt=0;
	}
 }
  /*------------------------------------------------------------------------------------------------*/
									/*MODE03*/
/*------------------------------------------------------------------------------------------------*/
 void Mode_three(void)
 {
	 /************����**************/
	 if(Gesture_judge(shear_min[0],shear_max[0],shear_min[1],shear_max[1],shear_min[2],shear_max[2])==1)
	 {
		 cnt1=0;
		 printf("����\n");
		 while(cnt1<=20)//0.5s
		 {
			 LED0=0;
		 }
		 LED0=1; 
	 }
	 
	 /************ʯͷ**************/
	 else if(Gesture_judge(bone_min[0],bone_max[0],bone_min[1],bone_max[1],bone_min[2],bone_max[2])==1)
	 {
		 cnt1=0;
		 printf("ʯͷ\n");
		 while(cnt1<=20)//0.5s
		 {
			 LED0=0;
		 }
		 LED0=1; 
	 }
	 /************��**************/
	  else if(Gesture_judge(cloth_min[0],cloth_max[0],cloth_min[1],cloth_max[1],cloth_min[2],cloth_max[2])==1)
	 {
		 cnt1=0;
		 printf("��\n");
		 while(cnt1<=20)//0.5s
		 {
			 LED0=0;
		 }
		 LED0=1; 
	 }
 }
 /*------------------------------------------------------------------------------------------------*/
									/*MODE04*/
/*------------------------------------------------------------------------------------------------*/
 void Mode_four(void)
 {
	 /**********"1"*************/
	 if(Gesture_judge(one_min[0],one_max[0],one_min[1],one_max[1],one_min[2],one_max[2])==1)
	 {
		 cnt1=0;
		 printf("1\n");
		 while(cnt1<=20)//0.5s
		 {
			 LED0=0;
		 }
		 LED0=1; 
	 }
	 /**********"2"*************/
	 else if(Gesture_judge(two_min[0],two_max[0],two_min[1],two_max[1],two_min[2],two_max[2])==1)
	 {
		 cnt1=0;
		 printf("2\n");
		 while(cnt1<=20)//0.5s
		 {
			 LED0=0;
		 }
		 LED0=1; 
	 }
	 /**********"3"*************/
	  else if(Gesture_judge(three_min[0],three_max[0],three_min[1],three_max[1],three_min[2],three_max[2])==1)
	 {
		 cnt1=0;
		 printf("3\n");
		 while(cnt1<=20)//0.5s
		 {
			 LED0=0;
		 }
		 LED0=1; 
	 }
	 /**********"4"*************/
	  else if(Gesture_judge(four_min[0],four_max[0],four_min[1],four_max[1],four_min[2],four_max[2])==1)
	 {
		 cnt1=0;
		 printf("4\n");
		 while(cnt1<=20)//0.5s
		 {
			 LED0=0;
		 }
		 LED0=1; 
	 }
	 /**********"5"*************/
	  else if(Gesture_judge(five_min[0],five_max[0],five_min[1],five_max[1],five_min[2],five_max[2])==1)
	 {
		 cnt1=0;
		 printf("5\n");
		 while(cnt1<=20)//0.5s
		 {
			 LED0=0;
		 }
		 LED0=1; 
	 }
 }
/*-----------------------------------------------
 ��������:TIM3�жϷ������
 ����˵��:ÿ10ms����һ���ж�,������100Hz
 ʵ������ʱ��: ms
-----------------------------------------------*/
void TIM3_IRQHandler(void)
{
	int i;
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET )//RESET = 0, SET = !RESET����Ƿ��������ж�
	{	
		cnt1++;
		/*---------------------------------------*/
		if(Init_flag==0)//FDC2214��ֵ��λ����ռ�ڴ�
		{
			cnt2++;
			if(cnt2<=10)   //0.5s��ȡ��ֵ��ֵ�ɱ�
			{
				LED0=0;
				Temp[0]= Cap_Calculate(0);
				Temp[1]= Cap_Calculate(1);
				Temp[2]= Cap_Calculate(2);
				Temp[3]= Cap_Calculate(3);
			}
			else if(cnt2>10)
			{
				cnt2=0;Init_flag=1;
				LED0=1;
			}
		}
		/*---------------------------------------*/
		else if(Mode3_train_flag==1)	
		{
			if(Mode3_train_cnt==1)//ģʽ3����1ѵ����
			{
				for(i=0;i<=199;i++)			
				{
					trani_ch0[i]=Cap_Calculate(0)-Temp[0];
					trani_ch1[i]=Cap_Calculate(1)-Temp[1];
					trani_ch2[i]=Cap_Calculate(2)-Temp[2];
					sum[0]+=trani_ch0[i];
					sum[1]+=trani_ch1[i];
					sum[2]+=trani_ch2[i];
				}
				avr[0]=sum[0]/200;
				avr[1]=sum[1]/200;
				avr[2]=sum[2]/200;
				Sort_chooes(trani_ch0);//�Ը��������������С����
				Sort_chooes(trani_ch1);
				Sort_chooes(trani_ch2);
				shear_min[0]=avr[0];//200������ֵ��Ϊ���������ֵ
				shear_min[1]=avr[1];
				shear_min[2]=avr[2];
				shear_max[0]=trani_ch0[199];
				shear_max[1]=trani_ch1[199];
				shear_max[2]=trani_ch2[199];
				memset(sum,0,sizeof(sum));
				memset(avr,0,sizeof(avr));
				USART_SendData(USART1,0xFF);//ģʽ3���Ƹ�����ͷ
				while( USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET); 
				USART_SendData(USART1,(Mode3_train_cnt));//ģʽ3���Ƹ���
				while( USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET); 
				printf("����\n");				
				printf("min0=%f,max0=%f  min1=%f,max1=%f  min2=%f,max2=%f\n",shear_min[0],shear_max[0],avr[1],shear_max[1],avr[2],shear_max[2]);
				Mode3_train_flag=0;
			}
			else if(Mode3_train_cnt==2)//ģʽ3����2ѵ����
			{
				for(i=0;i<=199;i++)			
				{
					trani_ch0[i]=Cap_Calculate(0)-Temp[0];
					trani_ch1[i]=Cap_Calculate(1)-Temp[1];
					trani_ch2[i]=Cap_Calculate(2)-Temp[2];
					sum[0]+=trani_ch0[i];
					sum[1]+=trani_ch1[i];
					sum[2]+=trani_ch2[i];
				}
				avr[0]=sum[0]/200;
				avr[1]=sum[1]/200;
				avr[2]=sum[2]/200;
				Sort_chooes(trani_ch0);//�Ը��������������С����
				Sort_chooes(trani_ch1);
				Sort_chooes(trani_ch2);
				bone_min[0]=avr[0];
				bone_min[1]=avr[1];
				bone_min[2]=avr[2];
				bone_max[0]=trani_ch0[199];
				bone_max[1]=trani_ch1[199];
				bone_max[2]=trani_ch2[199];
				memset(sum,0,sizeof(sum));
				memset(avr,0,sizeof(avr));
				USART_SendData(USART1,0xFF);//ģʽ3���Ƹ�����ͷ
				while( USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET); 
				USART_SendData(USART1,(Mode3_train_cnt));//ģʽ3���Ƹ���
				while( USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET); 
				printf("ʯͷ\n");				
				printf("min0=%f,max0=%f  min1=%f,max1=%f  min2=%f,max2=%f\n",bone_min[0],bone_max[0],bone_min[1],bone_max[1],bone_min[2],bone_max[2]);
				Mode3_train_flag=0;
			}
			else if(Mode3_train_cnt==3)//ģʽ3����3ѵ����
			{
				for(i=0;i<=199;i++)			
				{
					trani_ch0[i]=Cap_Calculate(0)-Temp[0];
					trani_ch1[i]=Cap_Calculate(1)-Temp[1];
					trani_ch2[i]=Cap_Calculate(2)-Temp[2];
					sum[0]+=trani_ch0[i];
					sum[1]+=trani_ch1[i];
					sum[2]+=trani_ch2[i];
				}
				avr[0]=sum[0]/200;
				avr[1]=sum[1]/200;
				avr[2]=sum[2]/200;
				Sort_chooes(trani_ch0);//�Ը��������������С����
				Sort_chooes(trani_ch1);
				Sort_chooes(trani_ch2);
				cloth_min[0]=avr[0];
				cloth_min[1]=avr[1];
				cloth_min[2]=avr[2];
				cloth_max[0]=trani_ch0[199];
				cloth_max[1]=trani_ch1[199];
				cloth_max[2]=trani_ch2[199];
				memset(sum,0,sizeof(sum));
				memset(avr,0,sizeof(avr));
				USART_SendData(USART1,0xFF);//ģʽ3���Ƹ�����ͷ
				while( USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET); 
				USART_SendData(USART1,(Mode3_train_cnt));//ģʽ3���Ƹ���
				while( USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);
				printf("��\n");				
				printf("min0=%f,max0=%f  min1=%f,max1=%f  min2=%f,max2=%f\n",cloth_min[0],cloth_max[0],cloth_min[1],cloth_max[1],cloth_min[2],cloth_max[2]);
				Mode3_train_flag=0;
				Mode3_train_cnt=0;
			}
			
		}
		/*---------------------------------------*/
		else if(Mode4_train_flag==1)	
		{
			if(Mode4_train_cnt==1)//ģʽ4����1ѵ����
			{
				for(i=0;i<=199;i++)			
				{
					trani_ch0[i]=Cap_Calculate(0)-Temp[0];
					trani_ch1[i]=Cap_Calculate(1)-Temp[1];
					trani_ch2[i]=Cap_Calculate(2)-Temp[2];
					sum[0]+=trani_ch0[i];
					sum[1]+=trani_ch1[i];
					sum[2]+=trani_ch2[i];
				}
				avr[0]=sum[0]/200;
				avr[1]=sum[1]/200;
				avr[2]=sum[2]/200;
				Sort_chooes(trani_ch0);//�Ը��������������С����
				Sort_chooes(trani_ch1);
				Sort_chooes(trani_ch2);
				one_min[0]=avr[0];
				one_min[1]=avr[1];
				one_min[2]=avr[2];
				one_max[0]=trani_ch0[199];
				one_max[1]=trani_ch1[199];
				one_max[2]=trani_ch2[199];
				memset(sum,0,sizeof(sum));
				memset(avr,0,sizeof(avr));
				USART_SendData(USART1,0xFE);//ģʽ4���Ƹ�����ͷ
				while( USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET); 
				USART_SendData(USART1,(Mode4_train_cnt));//ģʽ4���Ƹ���
				while( USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);
				printf("cnt4=%d  min=%f   max=%f\n",Mode4_train_cnt,trani_ch0[0],trani_ch0[199]);
				Mode4_train_flag=0;					
			}
			else if(Mode4_train_cnt==2)//ģʽ4����2ѵ����
			{
				for(i=0;i<=199;i++)			
				{
					trani_ch0[i]=Cap_Calculate(0)-Temp[0];
					trani_ch1[i]=Cap_Calculate(1)-Temp[1];
					trani_ch2[i]=Cap_Calculate(2)-Temp[2];
					sum[0]+=trani_ch0[i];
					sum[1]+=trani_ch1[i];
					sum[2]+=trani_ch2[i];
				}
				avr[0]=sum[0]/200;
				avr[1]=sum[1]/200;
				avr[2]=sum[2]/200;
				Sort_chooes(trani_ch0);//�Ը��������������С����
				Sort_chooes(trani_ch1);
				Sort_chooes(trani_ch2);
				two_min[0]=avr[0];
				two_min[1]=avr[1];
				two_min[2]=avr[2];
				two_max[0]=trani_ch0[199];
				two_max[1]=trani_ch1[199];
				two_max[2]=trani_ch2[199];
				memset(sum,0,sizeof(sum));
				memset(avr,0,sizeof(avr));
				USART_SendData(USART1,0xFE);//ģʽ4���Ƹ�����ͷ
				while( USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET); 
				USART_SendData(USART1,(Mode4_train_cnt));//ģʽ4���Ƹ���
				while( USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);
				printf("cnt4=%d  min=%f   max=%f\n",Mode4_train_cnt,trani_ch0[0],trani_ch0[199]);
				Mode4_train_flag=0;				
			}
			else if(Mode4_train_cnt==3)//ģʽ4����3ѵ����
			{
				for(i=0;i<=199;i++)			
				{
					trani_ch0[i]=Cap_Calculate(0)-Temp[0];
					trani_ch1[i]=Cap_Calculate(1)-Temp[1];
					trani_ch2[i]=Cap_Calculate(2)-Temp[2];
					sum[0]+=trani_ch0[i];
					sum[1]+=trani_ch1[i];
					sum[2]+=trani_ch2[i];
				}
				avr[0]=sum[0]/200;
				avr[1]=sum[1]/200;
				avr[2]=sum[2]/200;
				Sort_chooes(trani_ch0);//�Ը��������������С����
				Sort_chooes(trani_ch1);
				Sort_chooes(trani_ch2);
				three_min[0]=avr[0];
				three_min[1]=avr[1];
				three_min[2]=avr[2];
				three_max[0]=trani_ch0[199];
				three_max[1]=trani_ch1[199];
				three_max[2]=trani_ch2[199];
				memset(sum,0,sizeof(sum));
				memset(avr,0,sizeof(avr));
				USART_SendData(USART1,0xFE);//ģʽ4���Ƹ�����ͷ
				while( USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET); 
				USART_SendData(USART1,(Mode4_train_cnt));//ģʽ4���Ƹ���
				while( USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);
				printf("cnt4=%d  min=%f   max=%f\n",Mode4_train_cnt,trani_ch0[0],trani_ch0[199]);
				Mode4_train_flag=0;				
			}
			else if(Mode4_train_cnt==4)//ģʽ4����4ѵ����
			{
				for(i=0;i<=199;i++)			
				{
					trani_ch0[i]=Cap_Calculate(0)-Temp[0];
					trani_ch1[i]=Cap_Calculate(1)-Temp[1];
					trani_ch2[i]=Cap_Calculate(2)-Temp[2];
					sum[0]+=trani_ch0[i];
					sum[1]+=trani_ch1[i];
					sum[2]+=trani_ch2[i];
				}
				avr[0]=sum[0]/200;
				avr[1]=sum[1]/200;
				avr[2]=sum[2]/200;
				Sort_chooes(trani_ch0);//�Ը��������������С����
				Sort_chooes(trani_ch1);
				Sort_chooes(trani_ch2);
				four_min[0]=avr[0];
				four_min[1]=avr[1];
				four_min[2]=avr[2];
				four_max[0]=trani_ch0[199];
				four_max[1]=trani_ch1[199];
				four_max[2]=trani_ch2[199];
				memset(sum,0,sizeof(sum));
				memset(avr,0,sizeof(avr));
				USART_SendData(USART1,0xFE);//ģʽ4���Ƹ�����ͷ
				while( USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET); 
				USART_SendData(USART1,(Mode4_train_cnt));//ģʽ4���Ƹ���
				while( USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);
				printf("cnt4=%d  min=%f   max=%f\n",Mode4_train_cnt,trani_ch0[0],trani_ch0[199]);
				Mode4_train_flag=0;				
			}
			else if(Mode4_train_cnt==5)//ģʽ4����5ѵ����
			{
				for(i=0;i<=199;i++)			
				{
					trani_ch0[i]=Cap_Calculate(0)-Temp[0];
					trani_ch1[i]=Cap_Calculate(1)-Temp[1];
					trani_ch2[i]=Cap_Calculate(2)-Temp[2];
					sum[0]+=trani_ch0[i];
					sum[1]+=trani_ch1[i];
					sum[2]+=trani_ch2[i];
				}
				avr[0]=sum[0]/200;
				avr[1]=sum[1]/200;
				avr[2]=sum[2]/200;
				Sort_chooes(trani_ch0);//�Ը��������������С����
				Sort_chooes(trani_ch1);
				Sort_chooes(trani_ch2);
				five_min[0]=avr[0];
				five_min[1]=avr[1];
				five_min[2]=avr[2];
				five_max[0]=trani_ch0[199];
				five_max[1]=trani_ch1[199];
				five_max[2]=trani_ch2[199];
				memset(sum,0,sizeof(sum));
				memset(avr,0,sizeof(avr));
				USART_SendData(USART1,0xFE);//ģʽ4���Ƹ�����ͷ
				while( USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET); 
				USART_SendData(USART1,(Mode4_train_cnt));//ģʽ4���Ƹ���
				while( USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);
				Mode4_train_flag=0;
				printf("cnt4=%d  min=%f   max=%f\n",Mode4_train_cnt,trani_ch0[0],trani_ch0[199]);
				Mode4_train_cnt=0;				
			}
		}
		/*---------------------------------------*/
		else						//��Ҫ��ֵ����,ռ�ڴ棬ûģʽ��ʱ��һֱ��ȡ
		{
			CH_Data[0]=Cap_Calculate(0)-Temp[0];
			CH_Data[1]=Cap_Calculate(1)-Temp[1];
			CH_Data[2]=Cap_Calculate(2)-Temp[2];
			CH_Data[3]=Cap_Calculate(3)-Temp[3];
		}
		
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);//��������жϱ�־λ
}
/*---------------------------------*
���� 	:�о�����
˵��	:����/���
*----------------------------------*/
u8 Gesture_judge(float ch0min,float ch0max,float ch1min,float ch1max,float ch2min,float ch2max)
{
	if((CH_Data[0]>ch0min)&&(CH_Data[0]<ch0max)&&(CH_Data[1]>ch1min)&&(CH_Data[1]<ch1max)&&(CH_Data[2]>ch2min)&&(CH_Data[2]<ch2max))
	{
		return 1;
	}
	else return 0;
}
/*---------------------------------*
���� 	:������Χ����
˵��	:����/���
*----------------------------------*/
float range(float temp)
{
	float a;
    
}

/*---------------------------------*
���� 	:����ֵ����
˵��	:double
*----------------------------------*/
float fbs(float temp)
{
	float a;
	if(temp<0)
	a=-temp;
	else a=temp;
	
	return a;
}