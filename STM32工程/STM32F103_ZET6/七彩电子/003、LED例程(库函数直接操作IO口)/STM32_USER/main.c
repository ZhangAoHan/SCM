
#include "sys.h"
#include "delay.h"

/***********************************************************************/
//�˳����������߲ʹ���̫��M3��STM32F103�����弰���ּ��ݵ�STM32ϵͳ��
//ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;��
/***********************************************************************/
 
#define LED0_GPIO  GPIOB
#define LED1_GPIO  GPIOE

#define LED0_PIN   GPIO_Pin_5
#define LED1_PIN   GPIO_Pin_5


int main(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	delay_init();	    //��ʱ������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE, ENABLE);	 //ʹ��PB,PE�˿�ʱ��

	GPIO_InitStructure.GPIO_Pin = LED0_PIN;				       //LED0�˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(LED0_GPIO, &GPIO_InitStructure);					   //�����趨������ʼ��LED0
	GPIO_SetBits(LED0_GPIO,LED0_PIN);						         //LED0�����

	GPIO_InitStructure.GPIO_Pin = LED1_PIN;	    		     //LED1�˿�����, �������
	GPIO_Init(LED1_GPIO, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
	GPIO_SetBits(LED1_GPIO,LED1_PIN); 						         //LED1����� 
	
	
	while(1)
	{
		GPIO_ResetBits(LED0_GPIO,LED0_PIN); 
		delay_ms(500);
		GPIO_SetBits(LED0_GPIO,LED0_PIN);
		GPIO_ResetBits(LED1_GPIO,LED1_PIN); 
		delay_ms(500);
		GPIO_SetBits(LED1_GPIO,LED1_PIN);
	}
}




