//
#include "sys.h"
#include "usart.h"	  


/***********************************************************************/
//������������(֧��USART1 USART2 USART3 UART4 UART5)
//�˳����������߲ʹ���̫��M3��STM32F103�����弰���ּ��ݵ�STM32ϵͳ��
//��ֲע�⣬���������е�STM32F103оƬ��֧��5������
//ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;��
/***********************************************************************/	 


#define USE_MICROLIB   0//�Ƿ�ʹ��MicroLIB,Ĭ�ϲ�ʹ��(���ع���)
#define PRINTF_COM     USART1//printf �˿�ѡ��  USART1��USART2��USART3��UART4��UART5




//����1��ʼ������
void USART1_Init(u32 bound){
  
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//ʹ��USART1��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	
  
	//GPIO�˿�����
	//USART1_TX   GPIOA.9��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;        //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	 //�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);           //��ʼ��GPIOA.9
   
  //USART1_RX	  GPIOA.10��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  
	

 
  //USART ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART1, &USART_InitStructure);      //��ʼ������1
	
	//Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	
	
	USART_ClearFlag(USART1,USART_FLAG_TC); 
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //�������ڽ����ж�
  USART_Cmd(USART1, ENABLE);                     //ʹ�ܴ���1 
}



								 
//����2��ʼ������
void USART2_Init(u32 bound)
{  
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
 
	//ʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��GPIOA,Dʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//ʹ��USART2ʱ��
	
	//GPIO�˿�����
	//TX
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	           //PA2
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	     //��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
	//RX
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;             //PA3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);  

	RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2,ENABLE);      //��λ����2
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2,DISABLE);     //ֹͣ��λ

	USART_InitStructure.USART_BaudRate = bound;                  //����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;  //8λ���ݳ���
	USART_InitStructure.USART_StopBits = USART_StopBits_1;       //һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;          ///��żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//�շ�ģʽ

  USART_Init(USART2, &USART_InitStructure);                //��ʼ������
	USART_ClearFlag(USART2,USART_FLAG_TC); 
  
	//�ж�
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn; //ʹ�ܴ���2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; //��ռ���ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; //�����ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure); //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
 
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�����ж�
   
  USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ��� 
}


//����3��ʼ������
void USART3_Init(u32 bound)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef  GPIO_InitValue;
	USART_InitTypeDef USART_InitValue;
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	
	//GPIO�˿�����
	GPIO_InitValue.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitValue.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitValue.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB,&GPIO_InitValue);
	
  GPIO_InitValue.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitValue.GPIO_Pin =GPIO_Pin_11;
  GPIO_Init(GPIOB,&GPIO_InitValue);
  
	USART_InitValue.USART_BaudRate = bound;
  USART_InitValue.USART_WordLength = USART_WordLength_8b;
  USART_InitValue.USART_StopBits = USART_StopBits_1;
  USART_InitValue.USART_Parity = USART_Parity_No;
  USART_InitValue.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitValue.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
  USART_Init(USART3,&USART_InitValue);
	USART_ClearFlag(USART3,USART_FLAG_TC); 
	USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);//���ô��ڽ��շǿ��ж�
	
  NVIC_InitStructure.NVIC_IRQChannel =USART3_IRQn ; 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =3; //��ռ���ȼ�3
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;   //�����ȼ�3
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;   //ʹ��USART3�ж�
  NVIC_Init(&NVIC_InitStructure);  
	
  USART_Cmd(USART3,ENABLE);
}

//����4��ʼ������
void UART4_Init(u32 bound){
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);    
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);  
	//ע��UART4�ǹ�����APB1�����ϵģ���RCC_APB1PeriphClockCmd()������ʼ����
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE); 
	
	//GPIO�˿�����
	//UART4_TX   PC.10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;      //��UART4 ��TX ����Ϊ����������� AF_PP
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; //����ٶ�50MHz
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;   //�������ģʽ Out_PP
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	//��UART4 ��RX ����Ϊ���ø������� IN_FLOATING
	//UART4_RX	  PC.11
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING; //�������� IN_FLOATING 
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	//UART4���� N 8 1
	USART_InitStructure.USART_BaudRate = bound; //������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; //�ֳ�8λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1; //1λֹͣ�ֽ�
	USART_InitStructure.USART_Parity = USART_Parity_No; //����żУ��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //��������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //��Rx���պ�Tx���͹���
	USART_Init(UART4 , &USART_InitStructure);
	
	//UART4 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	USART_ClearFlag(UART4,USART_FLAG_TC); 
	USART_ITConfig(UART4,USART_IT_RXNE,ENABLE);//���ô��ڽ��շǿ��ж�
	
	USART_Cmd(UART4,ENABLE);
}

//����5��ʼ������
void UART5_Init(u32 bound){
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);
	
	//GPIO�˿�����
	//UART5_TX   PC.12
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; //����ٶ�50MHz
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;   //�������ģʽ Out_PP
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;      //��UART4 ��TX ����Ϊ����������� AF_PP
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	//��UART5 ��RX ����Ϊ���ø������� IN_FLOATING
	//UART5_RX	  PD.2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING; //�������� IN_FLOATING 
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	
	USART_InitStructure.USART_BaudRate = bound; //������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; //�ֳ�8λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1; //1λֹͣ�ֽ�
	USART_InitStructure.USART_Parity = USART_Parity_No; //����żУ��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //��������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //��Rx���պ�Tx���͹���
	
	USART_Init(UART5 , &USART_InitStructure);
	
	/* Enable the UART5 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	
	USART_ClearFlag(UART5,USART_FLAG_TC); 
	USART_ITConfig(UART5,USART_IT_RXNE,ENABLE);//���ô��ڽ��շǿ��ж�
	
	USART_Cmd(UART5,ENABLE);
}


//����1�жϺ���
void USART1_IRQHandler(void)                	//����1�жϷ������
{
	u8 res;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		res =USART_ReceiveData(USART1);	//��ȡ���յ�������
		USART_SendData(USART1,res); 
	}
}



//����2�жϺ���
void USART2_IRQHandler(void)
{
	u8 res;
 	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) //���յ�����
	{	 
		res =USART_ReceiveData(USART2); 	//��ȡ���յ�������
		USART_SendData(USART2,res); 
	}
} 

//����3�жϺ���
void USART3_IRQHandler(void)
{
	u8 res;
 	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) //���յ�����
	{	 
		res =USART_ReceiveData(USART3); 	//��ȡ���յ�������
		USART_SendData(USART3,res); 
	}
}

//����4�жϺ���
void UART4_IRQHandler(void)
{
	u8 res;
 	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET) //���յ�����
	{	 
		res =USART_ReceiveData(UART4); 	//��ȡ���յ�������
		USART_SendData(UART4,res); 
	}
}

//����5�жϺ���
void UART5_IRQHandler(void)
{
	u8 res;
 	if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET) //���յ�����
	{	 
		res =USART_ReceiveData(UART5); 	//��ȡ���յ�������
		USART_SendData(UART5,res); 
	}
}

//���ڷ���һ���ֽ�
void USART_SendByte(USART_TypeDef *USART_COM,u8 c){
	while((USART_COM->SR&0X40)==0);//ѭ������,ֱ���������
	USART_COM->DR = (u8)(c);
	while((USART_COM->SR&0X40)==0);//ѭ������,ֱ���������
}


//���ڷ����ַ�������
void USART_SendString(USART_TypeDef *USART_COM,unsigned char *s)
{
	while(*s)
	{
		while((USART_COM->SR&0X40)==0);//ѭ������,ֱ���������
    USART_COM->DR = (u8)(*s);
		while((USART_COM->SR&0X40)==0);//ѭ������,ֱ���������
		s++;
	}
}

//���ڷ������麯��
void USART_SendBuf(USART_TypeDef *USART_COM,unsigned char *buf,u16 len){
	while(len--){
		while((USART_COM->SR&0X40)==0);//ѭ������,ֱ���������
    USART_COM->DR = (u8)(*buf++);
		while((USART_COM->SR&0X40)==0);//ѭ������,ֱ���������
	}
}



/********************* printf ʵ�� ****************************/

#if USE_MICROLIB!=1
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{
	while((PRINTF_COM->SR&0X40)==0);//ѭ������,ֱ���������   
    PRINTF_COM->DR = (u8) ch;      
	return ch;
}
#else
/*ʹ��microLib�ķ���*/

int fputc(int ch, FILE *f)
{
	USART_SendData(PRINTF_COM, (uint8_t) ch);
	while (USART_GetFlagStatus(PRINTF_COM, USART_FLAG_TC) == RESET) {}	
  return ch;
}
int GetKey (void){ 
    while (!(PRINTF_COM->SR & USART_FLAG_RXNE));
    return ((int)(PRINTF_COM->DR & 0x1FF));
}

#endif 
 
/****************************** end *********************************/















































 
 
// 
//#if EN_USART1_RX   //���ʹ���˽���
////����1�жϷ������
////ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
//u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
////����״̬
////bit15��	������ɱ�־
////bit14��	���յ�0x0d
////bit13~0��	���յ�����Ч�ֽ���Ŀ
//u16 USART_RX_STA=0;       //����״̬���	  
//  
//void uart_init(u32 bound){
//  //GPIO�˿�����
//  GPIO_InitTypeDef GPIO_InitStructure;
//	USART_InitTypeDef USART_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
//	 
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
//  
//	//USART1_TX   GPIOA.9
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
//  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
//   
//  //USART1_RX	  GPIOA.10��ʼ��
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
//  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  

//  //Usart1 NVIC ����
//  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
//	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
//  
//   //USART ��ʼ������

//	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
//	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
//	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
//	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

//  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
//  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
//  USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 

//}

//void USART1_IRQHandler(void)                	//����1�жϷ������
//	{
//	u8 Res;
//#if SYSTEM_SUPPORT_OS 		//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
//	OSIntEnter();    
//#endif
//	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
//		{
//		Res =USART_ReceiveData(USART1);	//��ȡ���յ�������
//		
//		if((USART_RX_STA&0x8000)==0)//����δ���
//			{
//			if(USART_RX_STA&0x4000)//���յ���0x0d
//				{
//				if(Res!=0x0a)USART_RX_STA=0;//���մ���,���¿�ʼ
//				else USART_RX_STA|=0x8000;	//��������� 
//				}
//			else //��û�յ�0X0D
//				{	
//				if(Res==0x0d)USART_RX_STA|=0x4000;
//				else
//					{
//					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
//					USART_RX_STA++;
//					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
//					}		 
//				}
//			}   		 
//     } 
//#if SYSTEM_SUPPORT_OS 	//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
//	OSIntExit();  											 
//#endif
//} 
//#endif	

