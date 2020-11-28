#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include <stdio.h>
#include "KEY.H"
#include "led.h"

extern float CH_Data[4];  //ͨ��ֵ
extern int Init_flag;//FDC2214��λ��־
extern unsigned int Mode_flag;
extern unsigned int Mode3_Gesture_cnt;     //��¼ģʽ3,4���Ƹ���
extern unsigned int Mode4_Gesture_cnt;     //��¼ģʽ3,4���Ƹ���

float trani_ch0[200],trani_ch1[200],trani_ch2[200];//ѵ������


void KEY_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //ʹ��PE�˿�ʱ�ӣ�GPIO�����ǹ�����APB2�����ϵģ�
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;		 //����Ҫ�õ�GPIO��ΪPE5,PE6
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPU;			 //����Ϊ�������루��Ϊ�ⲿû�����������裬ֻ�ܽ��͵�ƽ��Ч�İ���IO������Ϊ�������룩
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //��ʼ��GPIOE5,6
}

u8 KEY_Scan(void)
{
	static u8 key_up_mode=1;//ģʽ���������־
	static u8 key_up_train=1;//ģʽ���������־
	static u8 reset=1;//ģʽ���������־
	unsigned int i;
		
	 if(key_up_mode&&(KEY_mode==KEY_PRESSED) )			//ģʽȷ�ϰ���
	{
		delay_ms(10);
		key_up_mode=0;
		if(Mode_flag>=5) //4��ģʽ
		{
			Mode_flag=0;
			USART_SendData(USART1,0x10);//ģʽ0��־
			while((USART1->SR&0X40)==0);
		}
		LED0=0;
		delay_ms(100);
		LED0=1;
	}
	else if(KEY_mode==1) key_up_mode=1;
/*-----------------------------------------------------*/	
	if(key_up_train&&(KEY_train==KEY_PRESSED) )			//ѵ�����Ƽ�������
	{
		delay_ms(10);
		key_up_train=0;
		
	}
	else if(KEY_train==1) key_up_train=1;
	/*-----------------------------------------------------*/
//	if(reset&&(FDC2214_reset==KEY_PRESSED) )			//ѵ�����Ƽ�������
//	{
//		delay_ms(10);
//		reset=0;
//		Init_flag=1;
//	}
//	else if(FDC2214_reset==1) reset=1;
}
//ѡ������
void Sort_chooes(float *arr)
{
	int i,j;
	float temp;
	
	for(i=0;i<199;i++)
	{
		for(j=i+1;j<200;j++)
		{
			if(arr[i]>arr[j])
			{
				temp=arr[i];
				arr[i]=arr[j];
				arr[j]=temp;
			}
		}
	}
	
}
