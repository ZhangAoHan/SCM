/*  main.c  */

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "ezio.h"
#include "key.h"

#include "LcdApi.h"
#include "LcdBsp.h"
#include "touch.h"
#include "adc.h"
#include "dac.h"



/*************************** �ļ�˵�� *******************************/
//�˳����������߲ʹ���̫��M3��STM32F103�����弰���ּ��ݵ�STM32ϵͳ��
//�Ա�����"�߲ʹ��� ̫��M3 STM32������"���򳬸��Լ۱ȿ�������ȡ��������
//ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;��
/********************************************************************/ 


u8 lcd_buf[50]={0};//������ʱ�洢LCD��ʾ���ַ���



int main(void)
{
	u16 adc_value=0;
	float voltage=0;
	float adc_voltage=0;
	delay_init();	    //��ʱ������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	USART1_Init(115200);//����1��ʼ��
	
	LCD_Init(); //LCD��ʼ��
	Dac1_Init();
	ADC1_Init();
	
	while(1)
	{
		//˵��!!!
		//˵��!!!
		//˵��!!!
		//DACͨ��PA4�����ѹ,ADCͨ��PA1�ɼ�,
		//�öŰ�������PA1��PA4��ʵ��ͬ������Ͳɼ�
		
		Dac1_Set_Vol((u32)(voltage*1000.0));//��ѹ���
		
		printf("DAC OUT:%3.1fV  |  ",voltage);
		//������ʾ(û����Ļ����Ӱ���������)
		sprintf((char*)lcd_buf,"DAC OUT:%3.1fV ",voltage);
		Show_Str(10,20,220,24,lcd_buf,16,0);
		
		delay_ms(10);//��ʱ
		
		adc_value=Get_Adc_Average(1,10);//ADC �ɼ�10��ȡƽ��ֵ
		adc_voltage=(float)adc_value/4095.0*3.3;//�������ѹ
		
		printf("ADC IN:%3.1fV \r\n",adc_voltage);
		//������ʾ(û����Ļ����Ӱ���������)
		sprintf((char*)lcd_buf,"ADC IN:%3.1fV ",adc_voltage);
		Show_Str(10,50,220,24,lcd_buf,16,0);
		
		voltage+=0.1;//��ѹ����0.1V
		if(voltage>3.3){
			voltage=0.0;
		}
		
		delay_ms(1000);//��ʱ
	}
}




