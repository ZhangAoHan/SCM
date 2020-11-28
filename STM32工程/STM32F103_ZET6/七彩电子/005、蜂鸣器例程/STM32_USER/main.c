
#include "sys.h"
#include "delay.h"
#include "beep.h"

/***********************************************************************/
//�˳����������߲ʹ���̫��M3��STM32F103�����弰���ּ��ݵ�STM32ϵͳ��
//ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;��
/***********************************************************************/
 



int main(void)
{
	delay_init();	    //��ʱ������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	Beep_Init();
	while(1)
	{
		BEEP_ON();
		delay_ms(100);
		BEEP_TOGGLE();
		delay_ms(200);
		BEEP_TOGGLE();
		delay_ms(100);
		BEEP_TOGGLE();
		delay_ms(100);
		BEEP_TOGGLE();
		delay_ms(200);
		BEEP_OFF();
		delay_ms(1000);
	}
}




