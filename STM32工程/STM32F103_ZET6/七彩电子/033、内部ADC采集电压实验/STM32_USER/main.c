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


/*************************** �ļ�˵�� *******************************/
//�˳����������߲ʹ���̫��M3��STM32F103�����弰���ּ��ݵ�STM32ϵͳ��
//�Ա�����"�߲ʹ��� ̫��M3 STM32������"���򳬸��Լ۱ȿ�������ȡ��������
//ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;��
/********************************************************************/ 





u8 lcd_buf[50]={0};//������ʱ�洢LCD��ʾ���ַ���

int main(void)
{
	u16 value=0;
	float voltage=0;
	
	delay_init();	    //��ʱ������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	USART1_Init(115200);//����1��ʼ��
	
	LCD_Init();    //LCD��ʼ��
	ADC1_Init();
	
	while(1)
	{
		//ͨ��ADCͨ��1�ɼ�����ʾ�ⲿ��ѹ
		//��ѹ��PA1����
		
		//ע��! ���ɼ���ѹ���ø���3.3V!!!!
		//ע��! ���ɼ���ѹ���ø���3.3V!!!!
		//ע��! ���ɼ���ѹ���ø���3.3V!!!!
		
		value=Get_Adc_Average(1,10);//�ɼ�10��ȡƽ��ֵ
		voltage=(float)value/4095.0*3.3;//�������ѹ
		
		//���ڷ��ͽ��
		printf("ADC Value : %5d  | ",value);
		printf("voltage : %6.3f V\r\n",voltage);
		
		//������ʾ���(û����Ļ����Ӱ���������)
		sprintf((char*)lcd_buf,"ADC Value:%5d ",value);
		Show_Str(10,20,220,24,lcd_buf,16,0);
		sprintf((char*)lcd_buf,"voltage:%6.3fV",voltage);
		Show_Str(10,50,220,24,lcd_buf,16,0);
		
		//��ʱ
		delay_ms(600);
	}
}




