/*  main.c  */

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "LcdBsp.h"




/***********************************************************************/
//�˳����������߲ʹ���̫��M3��STM32F103�����弰���ּ��ݵ�STM32ϵͳ��
//ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;��
/***********************************************************************/
 
 



int main(void)
{
	u32 i=0;
	delay_init();	    //��ʱ������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	LED_Init();
	USART1_Init(115200);//����1��ʼ��
	
	LCD_Init();	
	POINT_COLOR = RED;
	LCD_ShowString(20,150,220,24,24,"STM32 LCD Test !");//��ʾ�ַ���
	delay_ms(1000);
	delay_ms(1000);
	LCD_Fill(20,150,20+220,150+24,WHITE);
	while(1)
	{
		LED_TOGGLE(LED0);
		for(i=100;i>0;i--){
			LCD_ShowString(20,i*3,220,24,24,"STM32 LCD Test !");//��ʾ�ַ���
			delay_ms(20);
			LCD_Fill(20,i*3,20+220,i*3+24,WHITE);
		}
	}
}




