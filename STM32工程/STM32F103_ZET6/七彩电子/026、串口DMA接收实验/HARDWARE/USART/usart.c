//
#include "sys.h"
#include "usart.h"	  


/***********************************************************************/
//串口驱动程序(支持USART1 USART2 USART3 UART4 UART5)
//此程序适用于七彩光子太极M3—STM32F103开发板及部分兼容的STM32系统，
//移植注意，并不是所有的STM32F103芯片都支持5个串口
//只供学习使用，未经作者许可，不得用于其它任何用途！
/***********************************************************************/	 


#define USE_MICROLIB   0//是否使用MicroLIB,默认不使用(不必关心)
#define PRINTF_COM     USART1//printf 端口选择  USART1、USART2、USART3、UART4、UART5




//串口1初始化函数
void USART1_Init(u32 bound){
  
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//使能USART1，GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	
  
	//GPIO端口设置
	//USART1_TX   GPIOA.9初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;        //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	 //复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);           //初始化GPIOA.9
   
  //USART1_RX	  GPIOA.10初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  
	

 
  //USART 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART1, &USART_InitStructure);      //初始化串口1
	
	//Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	
	
	USART_ClearFlag(USART1,USART_FLAG_TC); 
	
	
////  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //开启串口接受中断
	
  USART_Cmd(USART1, ENABLE);                     //使能串口1 
}



								 
//串口2初始化函数
void USART2_Init(u32 bound)
{  
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
 
	//时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//使能GPIOA,D时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//使能USART2时钟
	
	//GPIO端口设置
	//TX
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	           //PA2
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	     //复用推挽
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
	//RX
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;             //PA3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);  

	RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2,ENABLE);      //复位串口2
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2,DISABLE);     //停止复位

	USART_InitStructure.USART_BaudRate = bound;                  //波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;  //8位数据长度
	USART_InitStructure.USART_StopBits = USART_StopBits_1;       //一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;          ///奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//收发模式

  USART_Init(USART2, &USART_InitStructure);                //初始化串口
	USART_ClearFlag(USART2,USART_FLAG_TC); 
  
	//中断
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn; //使能串口2中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; //先占优先级2级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; //从优先级2级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //使能外部中断通道
	NVIC_Init(&NVIC_InitStructure); //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
 
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启中断
   
  USART_Cmd(USART2, ENABLE);                    //使能串口 
}


//串口3初始化函数
void USART3_Init(u32 bound)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef  GPIO_InitValue;
	USART_InitTypeDef USART_InitValue;
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	
	//GPIO端口设置
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
	USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);//配置串口接收非空中断
	
  NVIC_InitStructure.NVIC_IRQChannel =USART3_IRQn ; 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =3; //抢占优先级3
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;   //子优先级3
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;   //使能USART3中断
  NVIC_Init(&NVIC_InitStructure);  
	
  USART_Cmd(USART3,ENABLE);
}

//串口4初始化函数
void UART4_Init(u32 bound){
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);    
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);  
	//注意UART4是挂载在APB1总线上的，用RCC_APB1PeriphClockCmd()函数初始化！
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE); 
	
	//GPIO端口设置
	//UART4_TX   PC.10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;      //将UART4 的TX 配置为复用推挽输出 AF_PP
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; //输出速度50MHz
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;   //推挽输出模式 Out_PP
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	//将UART4 的RX 配置为复用浮空输入 IN_FLOATING
	//UART4_RX	  PC.11
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING; //浮空输入 IN_FLOATING 
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	//UART4配置 N 8 1
	USART_InitStructure.USART_BaudRate = bound; //波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; //字长8位
	USART_InitStructure.USART_StopBits = USART_StopBits_1; //1位停止字节
	USART_InitStructure.USART_Parity = USART_Parity_No; //无奇偶校验
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //无流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //打开Rx接收和Tx发送功能
	USART_Init(UART4 , &USART_InitStructure);
	
	//UART4 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	USART_ClearFlag(UART4,USART_FLAG_TC); 
	USART_ITConfig(UART4,USART_IT_RXNE,ENABLE);//配置串口接收非空中断
	
	USART_Cmd(UART4,ENABLE);
}

//串口5初始化函数
void UART5_Init(u32 bound){
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);
	
	//GPIO端口设置
	//UART5_TX   PC.12
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; //输出速度50MHz
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;   //推挽输出模式 Out_PP
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;      //将UART4 的TX 配置为复用推挽输出 AF_PP
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	//将UART5 的RX 配置为复用浮空输入 IN_FLOATING
	//UART5_RX	  PD.2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING; //浮空输入 IN_FLOATING 
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	
	USART_InitStructure.USART_BaudRate = bound; //波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; //字长8位
	USART_InitStructure.USART_StopBits = USART_StopBits_1; //1位停止字节
	USART_InitStructure.USART_Parity = USART_Parity_No; //无奇偶校验
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //无流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //打开Rx接收和Tx发送功能
	
	USART_Init(UART5 , &USART_InitStructure);
	
	/* Enable the UART5 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	
	USART_ClearFlag(UART5,USART_FLAG_TC); 
	USART_ITConfig(UART5,USART_IT_RXNE,ENABLE);//配置串口接收非空中断
	
	USART_Cmd(UART5,ENABLE);
}

#if 0
//串口1中断函数
void USART1_IRQHandler(void)                	//串口1中断服务程序
{
	u8 res;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		res =USART_ReceiveData(USART1);	//读取接收到的数据
		USART_SendData(USART1,res); 
	}
}
#endif


//串口2中断函数
void USART2_IRQHandler(void)
{
	u8 res;
 	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) //接收到数据
	{	 
		res =USART_ReceiveData(USART2); 	//读取接收到的数据
		USART_SendData(USART2,res); 
	}
} 

//串口3中断函数
void USART3_IRQHandler(void)
{
	u8 res;
 	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) //接收到数据
	{	 
		res =USART_ReceiveData(USART3); 	//读取接收到的数据
		USART_SendData(USART3,res); 
	}
}

//串口4中断函数
void UART4_IRQHandler(void)
{
	u8 res;
 	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET) //接收到数据
	{	 
		res =USART_ReceiveData(UART4); 	//读取接收到的数据
		USART_SendData(UART4,res); 
	}
}

//串口5中断函数
void UART5_IRQHandler(void)
{
	u8 res;
 	if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET) //接收到数据
	{	 
		res =USART_ReceiveData(UART5); 	//读取接收到的数据
		USART_SendData(UART5,res); 
	}
}

//串口发送一个字节
void USART_SendByte(USART_TypeDef *USART_COM,u8 c){
	while((USART_COM->SR&0X40)==0);//循环发送,直到发送完毕
	USART_COM->DR = (u8)(c);
	while((USART_COM->SR&0X40)==0);//循环发送,直到发送完毕
}


//串口发送字符串函数
void USART_SendString(USART_TypeDef *USART_COM,unsigned char *s)
{
	while(*s)
	{
		while((USART_COM->SR&0X40)==0);//循环发送,直到发送完毕
    USART_COM->DR = (u8)(*s);
		while((USART_COM->SR&0X40)==0);//循环发送,直到发送完毕
		s++;
	}
}

//串口发送数组函数
void USART_SendBuf(USART_TypeDef *USART_COM,unsigned char *buf,u16 len){
	while(len--){
		while((USART_COM->SR&0X40)==0);//循环发送,直到发送完毕
    USART_COM->DR = (u8)(*buf++);
		while((USART_COM->SR&0X40)==0);//循环发送,直到发送完毕
	}
}



/********************* printf 实现 ****************************/

#if USE_MICROLIB!=1
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{
	while((PRINTF_COM->SR&0X40)==0);//循环发送,直到发送完毕   
    PRINTF_COM->DR = (u8) ch;      
	return ch;
}
#else
/*使用microLib的方法*/

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
//#if EN_USART1_RX   //如果使能了接收
////串口1中断服务程序
////注意,读取USARTx->SR能避免莫名其妙的错误   	
//u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
////接收状态
////bit15，	接收完成标志
////bit14，	接收到0x0d
////bit13~0，	接收到的有效字节数目
//u16 USART_RX_STA=0;       //接收状态标记	  
//  
//void uart_init(u32 bound){
//  //GPIO端口设置
//  GPIO_InitTypeDef GPIO_InitStructure;
//	USART_InitTypeDef USART_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
//	 
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
//  
//	//USART1_TX   GPIOA.9
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
//  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
//   
//  //USART1_RX	  GPIOA.10初始化
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
//  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

//  //Usart1 NVIC 配置
//  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
//	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
//  
//   //USART 初始化设置

//	USART_InitStructure.USART_BaudRate = bound;//串口波特率
//	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
//	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
//	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

//  USART_Init(USART1, &USART_InitStructure); //初始化串口1
//  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
//  USART_Cmd(USART1, ENABLE);                    //使能串口1 

//}

//void USART1_IRQHandler(void)                	//串口1中断服务程序
//	{
//	u8 Res;
//#if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
//	OSIntEnter();    
//#endif
//	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
//		{
//		Res =USART_ReceiveData(USART1);	//读取接收到的数据
//		
//		if((USART_RX_STA&0x8000)==0)//接收未完成
//			{
//			if(USART_RX_STA&0x4000)//接收到了0x0d
//				{
//				if(Res!=0x0a)USART_RX_STA=0;//接收错误,重新开始
//				else USART_RX_STA|=0x8000;	//接收完成了 
//				}
//			else //还没收到0X0D
//				{	
//				if(Res==0x0d)USART_RX_STA|=0x4000;
//				else
//					{
//					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
//					USART_RX_STA++;
//					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//接收数据错误,重新开始接收	  
//					}		 
//				}
//			}   		 
//     } 
//#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
//	OSIntExit();  											 
//#endif
//} 
//#endif	

