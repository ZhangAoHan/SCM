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
	delay_init();	    //��ʱ������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	LED_Init();
	USART1_Init(115200);//����1��ʼ��
	
	LCD_Init();	
	
	while(1)
	{
		LED_TOGGLE(LED0);
		LCD_Clear(BLUE);
		LCD_DrawRectangle(50,50,100,100);//������
		delay_ms(500);
		LED_TOGGLE(LED1);
		LCD_Clear(RED);
		LCD_DrawLine(20,20,200,200);
		delay_ms(500);
		LED_TOGGLE(LED0);
		LCD_Clear(YELLOW);
		LCD_Draw_Circle(100,100,90);
		delay_ms(500);
	}
}




