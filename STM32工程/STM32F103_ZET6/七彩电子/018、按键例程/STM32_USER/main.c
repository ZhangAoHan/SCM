/*  main.c  */

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "LcdBsp.h"
#include "LcdApi.h"
#include "image.h"
#include "key.h"
#include "beep.h"



/***********************************************************************/
//�˳����������߲ʹ���̫��M3��STM32F103�����弰���ּ��ݵ�STM32ϵͳ��
//ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;��
/***********************************************************************/
 
 
 
 
/*
˵��:
    ����Ϊ��������,������֧�ְ���ͬʱ����,
		����KEY2֮���ٰ�KEY0��ı������״̬
*/
 


int main(void)
{
	//u32 i=0;
	delay_init();	    //��ʱ������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	LED_Init();
	USART1_Init(115200);//����1��ʼ��
	Key_Init();
	LCD_Init();	
	Beep_Init();
	POINT_COLOR = RED;
	LCD_ShowString(20,20,220,16,16,"STM32 Key Test !");//��ʾ�ַ���

	while(1)
	{
		switch(Key_Scan(0)){
			case KEY0_PRES:{
				if(Key_GetSta(KEY2)){//����ͬʱ���²���,��סKEY2 �ٰ�KEY0
					printf("KEY0 Press!");
					BEEP_TOGGLE();
				}
				else{
					LCD_ShowString(20,50,220,16,16,"KEY0_PRES");//��ʾ�ַ���
					printf("KEY2 & KEY0 Press!");
					LED_TOGGLE(LED0);
				}
				break;
			}
			case KEY1_PRES:{
				LCD_ShowString(20,50,220,16,16,"KEY1_PRES");//��ʾ�ַ���
				printf("KEY1 Press!");
				LED_TOGGLE(LED1);
				break;
			}
			case KEY2_PRES:{
				LCD_ShowString(20,50,220,16,16,"KEY2_PRES");//��ʾ�ַ���
				printf("KEY2 Press!");
				LED_TOGGLE(LED0);
				LED_TOGGLE(LED1);
				break;
			}
			case WKUP_PRES:{//�ر�����LED
				LCD_ShowString(20,50,220,16,16,"KEY3_PRES");//��ʾ�ַ���
				printf("KEY3 Press!");
				LED_OFF(LED0);
				LED_OFF(LED1);
				break;
			}
		}
	}
}




