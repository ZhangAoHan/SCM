
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"


/***********************************************************************/
//此程序适用于七彩光子太极M3—STM32F103开发板及部分兼容的STM32系统，
//只供学习使用，未经作者许可，不得用于其它任何用途！
/***********************************************************************/
 
 
u32 count=0;


u8  Uart1_RxBuf[1024]={0};//串口接收缓存
u32 Uart1_RxCnt=0;//接收计数
u8  Uart1_RxOK=0;//接收到一帧数据
//
int main(void)
{
	delay_init();	    //延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	LED_Init();
	
	USART1_Init(115200);//串口1初始化
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);// 打开串口1空闲中断
	
	printf("太极M3 STM32开发板串口空闲中断测试程序。\r\n");
	
	
	while(1)
	{
		//关于串口空闲中断的说明:
		//空闲中断是在检测到在数据收受后，
		//总线上在一个字节的时间内没有再接收到数据时发生。
		//即串口的RXNE位被置位之后才开始检测，检测到空闲之后，
		//串口的CR1寄存器的IDLE位被硬件置1，必须采用软件将IDLE位清零才能避免反复进入空闲中断。
		//具体的做法是先读取USART_SR，再读取USART_DR。
		//需要注意的是，不能采用库函数USART_ClearFlag（）或者USART_ClearItPending()来清除IDEL标志
		//空闲中断可以非常方便的接收一帧数据
		
		
		if(Uart1_RxOK!=0){
			LED_TOGGLE(LED0);
			USART_SendString(USART1,"串口1接收到1帧数据:\r\n");
			USART_SendBuf(USART1,Uart1_RxBuf,Uart1_RxCnt);
			USART_SendString(USART1,"\r\n");
			Uart1_RxOK=0;
			Uart1_RxCnt=0;
			count=0;
		}
		delay_ms(1);
		count++;
		if(count>6000){//超过6秒未发送数据,提示用户发送数据
			USART_SendString(USART1,"\r\n请通过串口发送一帧数据\r\n");
			count=0;
		}
	}
}

//串口1中断函数
void USART1_IRQHandler(void)
{
	uint8_t Clear=Clear;//这种定义方法，用来消除编译器的"没有用到"提醒
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET){ //如果接收到1个字节
		if(Uart1_RxCnt<1024){
			Uart1_RxBuf[Uart1_RxCnt++] = USART1->DR;// 把接收到的字节保存，数组地址加1
		}
	} 
	else if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET){// 如果接收到1帧数据
		Clear=USART1->SR;// 读SR寄存器
		Clear=USART1->DR;// 读DR寄存器(先读SR再读DR，就是为了清除IDLE中断)
		Uart1_RxOK=1;// 标记接收到了1帧数据
	}
}























