
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "string.h"
#include "beep.h"

#include "UartDMA.h"



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
	Beep_Init();
	USART1_Init(115200);//����1��ʼ��
	USART_DMA_Rx_Init(Uart1_RxBuf,1024);
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);// �򿪴���1�����ж�
	delay_ms(1000);
	
	printf("\r\n\r\n̫��M3 STM32�����崮�ڿ���LED�����������Գ���\r\n");
	USART_SendString(USART1,"\r\nͨ�����ڷ���ָ��ɿ���LED�ͷ�����!���ɳ�����ָ��:\r\n\r\n");
	USART_SendString(USART1,"\"����\"   \"�ص�\"  \"�򿪷�����\"   \"�رշ�����\"\r\n");
	
	
	
	// ˵��:
	// ���������DMA���յ�����,Ϊ�˷�ֹ�����Ե�̫����,����DMA��������һ��������ʵ��
	// ������Ȼ�õ���֮ǰ�ù��Ĵ��ڽ��տ����ж�����������,������ͨ��DMA��ʽ�ŵ��ڲ�RAM�е�
	// ����ʵ�ֵĹ�����Ȼ��֮ǰ�Ĵ��ڿ���LED�ͷ�����
	
	
	while(1)
	{
		// ���ڴ��ڿ����жϵ�˵��:
		// �����ж����ڼ�⵽���������ܺ�
		// ��������һ���ֽڵ�ʱ����û���ٽ��յ�����ʱ������
		// �����ڵ�RXNEλ����λ֮��ſ�ʼ��⣬��⵽����֮��
		// ���ڵ�CR1�Ĵ�����IDLEλ��Ӳ����1��������������IDLEλ������ܱ��ⷴ����������жϡ�
		// ������������ȶ�ȡUSART_SR���ٶ�ȡUSART_DR��
		// ��Ҫע����ǣ����ܲ��ÿ⺯��USART_ClearFlag��������USART_ClearItPending()�����IDEL��־
		// �����жϿ��Էǳ�����Ľ���һ֡����
		
		
		if(Uart1_RxOK!=0){
			USART_SendString(USART1,"\r\n����1���յ�1֡����: ");
			USART_SendBuf(USART1,Uart1_RxBuf,Uart1_RxCnt);
			USART_SendString(USART1,"\r\n");
			
			
			//���ݴ���
			if(strstr((char*)Uart1_RxBuf,"����")!=0){//�ַ�������,����ָ��
				LED_ON(LED0);
				LED_ON(LED1);
				USART_SendString(USART1,"\r\n���Ƴɹ�!\r\n");
			}
			else if(strstr((char*)Uart1_RxBuf,"�ص�")!=0){
				LED_OFF(LED0);
				LED_OFF(LED1);
				USART_SendString(USART1,"\r\n�صƳɹ�!\r\n");
			}
			else if(strstr((char*)Uart1_RxBuf,"�򿪷�����")!=0){
				BEEP_ON();
				USART_SendString(USART1,"\r\n�������򿪳ɹ�!\r\n");
			}
			else if(strstr((char*)Uart1_RxBuf,"�رշ�����")!=0){
				BEEP_OFF();
				USART_SendString(USART1,"\r\n�������رճɹ�!\r\n");
			}
			memset(Uart1_RxBuf,0,Uart1_RxCnt);
			
			
			USART_DMA_Rx_Init(Uart1_RxBuf,1024);//ע��,������һ�����ݽ��ղ��Ҵ���������,���¿�ʼ��һ�ν���
			
			
			Uart1_RxOK=0;
			Uart1_RxCnt=0;
			count=0;
		}
		delay_ms(1);
		count++;
		if(count>6000){//����6��δ��������,��ʾ�û���������
			USART_SendString(USART1,"\r\nͨ�����ڷ���ָ��ɿ���LED�ͷ�����!���ɳ�����ָ��:\r\n\r\n");
			USART_SendString(USART1,"\"����\"   \"�ص�\"  \"�򿪷�����\"   \"�رշ�����\"\r\n");
			count=0;
		}
	}
}

//����1�жϺ���
void USART1_IRQHandler(void)
{
	uint8_t Clear=Clear;//���ֶ��巽��������������������"û���õ�"����
	
	
	//DMA���Զ������ݷ��뻺��,������ﲻ��ҪCPU����
////	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET){ //������յ�1���ֽ�
////		if(Uart1_RxCnt<1024){
////			Uart1_RxBuf[Uart1_RxCnt++] = USART1->DR;// �ѽ��յ����ֽڱ��棬�����ַ��1
////		}
////	}
	
	
	if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET){// ������յ�1֡����
		Clear=USART1->SR;// ��SR�Ĵ���
		Clear=USART1->DR;// ��DR�Ĵ���(�ȶ�SR�ٶ�DR������Ϊ�����IDLE�ж�)
		Uart1_RxCnt=DMA_GetCurrDataCounter(DMA1_Channel5);//��ȡ���յ��ĳ���
		Uart1_RxOK=1;// ��ǽ��յ���1֡����
	}
}























