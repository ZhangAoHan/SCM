
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"


/***********************************************************************/
//�˳����������߲ʹ���̫��M3��STM32F103�����弰���ּ��ݵ�STM32ϵͳ��
//ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;��
/***********************************************************************/
 
 
u32 count=0;


int main(void)
{
	delay_init();	    //��ʱ������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	LED_Init();
	
	USART1_Init(115200);//����1��ʼ��
	USART2_Init(115200);//����2��ʼ��
	USART3_Init(115200);//����3��ʼ��
	UART4_Init (115200);//����4��ʼ��
	UART5_Init (115200);//����5��ʼ��
	
	
	while(1)
	{
		delay_ms(1000);
		delay_ms(1000);
		LED_TOGGLE(LED0);
		printf("̫��M3 STM32�����崮�ڲ��Գ��򣬵�%d�η��͡�\r\n\r\n",count++);
		USART_SendString(USART1,"��ʾ:\r\n    ��������յ����ݻ�ԭ�����أ�֧�ִ���1��2��3��4��5");
		USART_SendByte(USART1,'\r');
		USART_SendByte(USART1,'\n');
		USART_SendBuf(USART1,"\r\n",2);
	}
}




