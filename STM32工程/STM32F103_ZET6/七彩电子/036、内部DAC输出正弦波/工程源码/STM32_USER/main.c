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

#include "math.h"




/*************************** �ļ�˵�� *******************************/
//�˳����������߲ʹ���̫��M3��STM32F103�����弰���ּ��ݵ�STM32ϵͳ��
//�Ա�����"�߲ʹ��� ̫��M3 STM32������"���򳬸��Լ۱ȿ�������ȡ��������
//ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;��
/********************************************************************/ 


//u8 lcd_buf[50]={0};//������ʱ�洢LCD��ʾ���ַ���



float  angle = 0;//�Ƕ�ֵ
float  rad = 0;//������
float  amplitude =3.3;//���εķ��ֵ

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
	
	while(1)
	{
		//˵��!!!
		//˵��!!!
		//˵��!!!
		//������������Ҳ��������������Ҳ�,��Ϊ�޷������ѹ,���������������ƫ�ƶ���֮һ��ֵ�����Ҳ�
		//DACͨ��PA4�����ѹ,ͨ��ʾ�����ɹ۲첨��
		
		
		rad=angle*3.1415926/180.0;//�Ƕ�ֵת��Ϊ������
		voltage=sin(rad)*(amplitude/2.0)+(amplitude/2.0);//�������ѹ
		Dac1_Set_Vol((u32)(voltage*1000.0));//��ѹ���
		
		delay_us(50);//��ʱ
		
		angle+=0.1;//����0.1��,ÿ���������360��0.1=3600��
		if(angle>360){//���һ������,���¿�ʼ
			angle=0;
		}
		
	}
}




