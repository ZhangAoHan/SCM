#include "sys.h"
#include "usart.h"	  
#include "led.h"
#include "delay.h"

extern int Run_flag;
extern int Init_flag;
extern unsigned Mode3_train_flag,Mode4_train_flag;//ģʽ3,4��ʼѵ����־
extern unsigned Mode3_train_cnt, Mode4_train_cnt;//ģʽ3,4ѵ������
extern unsigned Mode3_judge_flag,Mode4_judge_flag;//ģʽ3,4��ʼ���б�־
extern unsigned Mode3_Gesture_flag;		  //Mode3ѵ����־
extern unsigned int Mode_flag;			  //ģʽ��־
//���ʹ��ucos,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos ʹ��	  
#endif

//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

 
#if EN_USART1_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA=0;       //����״̬���	  
  
void uart_init(u32 bound){
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
   
  //USART1_RX	  GPIOA.10��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  

  //Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 

}

void USART1_IRQHandler(void)                	//����1�жϷ������
	{
	u8 Res;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
		Res =USART_ReceiveData(USART1);	//��ȡ���յ�������
		if(Res==0x28)//��ʼ��־
		{
			Run_flag=1;
		}
		if(Res==0x01)		//ģʽ�л��źţ�����Ļ���𣬷��ظ���Ļ��֤ͬ��
		{
			Mode_flag++;
			LED0=0;
			delay_ms(100);
			LED0=1;
			if(Mode_flag>=5) //4��ģʽ
			{
				Mode_flag=0;
				USART_SendData(USART1,0x10);//ģʽ0��־
				while((USART1->SR&0X40)==0);
			}
		}
		if(Res==0x02)  //FDC2214��ʼ��λ�ź�
		{
			Init_flag=0;
			printf("reset  mode=%d\n",Mode_flag);
		}
		if(Res==0xA0)//ģʽ3����ѵ��
		{
			Mode3_train_flag=1;
			Mode3_train_cnt++;
			LED0=0;
			delay_ms(100);
			LED0=1;
		}
		if(Res==0xB0)//ģʽ3��ʼ����
		{
			Mode3_judge_flag=1;
			LED0=0;
			delay_ms(100);
			LED0=1;
		}
		if(Res==0xC0)//ģʽ4����ѵ��
		{
			Mode4_train_flag=1;
			Mode4_train_cnt++;
			LED0=0;
			delay_ms(100);
			LED0=1;
		}
		if(Res==0xD0)//ģʽ4��ʼ����
		{
			Mode4_judge_flag=1;
			LED0=0;
			delay_ms(100);
			LED0=1;
		} 
//		if(Res==0xAA)//ģʽ3ѵ����־
//		{
//			Mode3_Gesture_flag=2;
//		} 
     } 
} 
#endif	

