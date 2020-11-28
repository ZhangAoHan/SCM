
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"


/***********************************************************************/
//�˳����������߲ʹ���̫��M3��STM32F103�����弰���ּ��ݵ�STM32ϵͳ��
//ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;��
/***********************************************************************/
 
 
u32 count=0;


u8  Uart1_RxBuf[1024]={0};//���ڽ��ջ���
u32 Uart1_RxCnt=0;//���ռ���
u8  Uart1_RxOK=0;//���յ�һ֡����
//
int main(void)
{
	delay_init();	    //��ʱ������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	LED_Init();
	
	USART1_Init(115200);//����1��ʼ��
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);// �򿪴���1�����ж�
	
	printf("̫��M3 STM32�����崮�ڿ����жϲ��Գ���\r\n");
	
	
	while(1)
	{
		//���ڴ��ڿ����жϵ�˵��:
		//�����ж����ڼ�⵽���������ܺ�
		//��������һ���ֽڵ�ʱ����û���ٽ��յ�����ʱ������
		//�����ڵ�RXNEλ����λ֮��ſ�ʼ��⣬��⵽����֮��
		//���ڵ�CR1�Ĵ�����IDLEλ��Ӳ����1��������������IDLEλ������ܱ��ⷴ����������жϡ�
		//������������ȶ�ȡUSART_SR���ٶ�ȡUSART_DR��
		//��Ҫע����ǣ����ܲ��ÿ⺯��USART_ClearFlag��������USART_ClearItPending()�����IDEL��־
		//�����жϿ��Էǳ�����Ľ���һ֡����
		
		
		if(Uart1_RxOK!=0){
			LED_TOGGLE(LED0);
			USART_SendString(USART1,"����1���յ�1֡����:\r\n");
			USART_SendBuf(USART1,Uart1_RxBuf,Uart1_RxCnt);
			USART_SendString(USART1,"\r\n");
			Uart1_RxOK=0;
			Uart1_RxCnt=0;
			count=0;
		}
		delay_ms(1);
		count++;
		if(count>6000){//����6��δ��������,��ʾ�û���������
			USART_SendString(USART1,"\r\n��ͨ�����ڷ���һ֡����\r\n");
			count=0;
		}
	}
}

//����1�жϺ���
void USART1_IRQHandler(void)
{
	uint8_t Clear=Clear;//���ֶ��巽��������������������"û���õ�"����
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET){ //������յ�1���ֽ�
		if(Uart1_RxCnt<1024){
			Uart1_RxBuf[Uart1_RxCnt++] = USART1->DR;// �ѽ��յ����ֽڱ��棬�����ַ��1
		}
	} 
	else if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET){// ������յ�1֡����
		Clear=USART1->SR;// ��SR�Ĵ���
		Clear=USART1->DR;// ��DR�Ĵ���(�ȶ�SR�ٶ�DR������Ϊ�����IDLE�ж�)
		Uart1_RxOK=1;// ��ǽ��յ���1֡����
	}
}























