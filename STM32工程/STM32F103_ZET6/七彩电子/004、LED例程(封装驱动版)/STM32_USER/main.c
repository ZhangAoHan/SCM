
#include "sys.h"
#include "delay.h"
#include "led.h"

/***********************************************************************/
//�˳����������߲ʹ���̫��M3��STM32F103�����弰���ּ��ݵ�STM32ϵͳ��
//ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;��
/***********************************************************************/
 



int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	delay_init();	    //��ʱ������ʼ��
	LED_Init();
	while(1)
	{
		LED_ON(LED0);
		delay_ms(500);
		LED_OFF(LED0);
		LED_ON(LED1);
		delay_ms(500);
		LED_OFF(LED1);
	}
}




