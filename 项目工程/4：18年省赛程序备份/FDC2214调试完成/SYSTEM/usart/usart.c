#include "sys.h"
#include "usart.h"	  
#include "led.h"
#include "delay.h"

extern int Run_flag;
extern int Init_flag;
extern unsigned Mode3_train_flag,Mode4_train_flag;//模式3,4开始训练标志
extern unsigned Mode3_train_cnt, Mode4_train_cnt;//模式3,4训练计数
extern unsigned Mode3_judge_flag,Mode4_judge_flag;//模式3,4开始评判标志
extern unsigned Mode3_Gesture_flag;		  //Mode3训练标志
extern unsigned int Mode_flag;			  //模式标志
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos 使用	  
#endif

//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

 
#if EN_USART1_RX   //如果使能了接收
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART_RX_STA=0;       //接收状态标记	  
  
void uart_init(u32 bound){
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
   
  //USART1_RX	  GPIOA.10初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

  //Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART1, &USART_InitStructure); //初始化串口1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART1, ENABLE);                    //使能串口1 

}

void USART1_IRQHandler(void)                	//串口1中断服务程序
	{
	u8 Res;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
		{
		Res =USART_ReceiveData(USART1);	//读取接收到的数据
		if(Res==0x28)//开始标志
		{
			Run_flag=1;
		}
		if(Res==0x01)		//模式切换信号，由屏幕发起，返回给屏幕保证同步
		{
			Mode_flag++;
			LED0=0;
			delay_ms(100);
			LED0=1;
			if(Mode_flag>=5) //4种模式
			{
				Mode_flag=0;
				USART_SendData(USART1,0x10);//模式0标志
				while((USART1->SR&0X40)==0);
			}
		}
		if(Res==0x02)  //FDC2214初始复位信号
		{
			Init_flag=0;
			printf("reset  mode=%d\n",Mode_flag);
		}
		if(Res==0xA0)//模式3进行训练
		{
			Mode3_train_flag=1;
			Mode3_train_cnt++;
			LED0=0;
			delay_ms(100);
			LED0=1;
		}
		if(Res==0xB0)//模式3开始评判
		{
			Mode3_judge_flag=1;
			LED0=0;
			delay_ms(100);
			LED0=1;
		}
		if(Res==0xC0)//模式4进行训练
		{
			Mode4_train_flag=1;
			Mode4_train_cnt++;
			LED0=0;
			delay_ms(100);
			LED0=1;
		}
		if(Res==0xD0)//模式4开始评判
		{
			Mode4_judge_flag=1;
			LED0=0;
			delay_ms(100);
			LED0=1;
		} 
//		if(Res==0xAA)//模式3训练标志
//		{
//			Mode3_Gesture_flag=2;
//		} 
     } 
} 
#endif	

