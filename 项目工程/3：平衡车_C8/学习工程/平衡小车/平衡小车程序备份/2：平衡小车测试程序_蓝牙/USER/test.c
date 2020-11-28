#include "sys.h" 
#include "iic.h"
#include "timer.h"
	u8 res;
	
void Bluetooth(void);	
int main(void)
{		
//	u16 led0pwmval=0;    
//	u8 dir=1;
//		u8 t;

//	u8 len;	
//	u16 times=0;  
	Stm32_Clock_Init(9);	//系统时钟设置
	delay_init(72);	  		//延时初始化
	uart_init(72,9600); 	//串口初始化为9600


//	IIC_Init();                  //6050_iic初始化	
//	DMP_Init();                  //6050_DMP初始化
//	MPU6050_initialize();        //6050_初始化
//	iIC_Init(); 

//	Timer_init(899,0);   //不分频，pwm频率为72M/900=80K hz  ，pwm计数总数为900，定时器3内部输出比较寄存器装载值与900比较
//    LED_init();		
  	while(1)
	{
//		Read_DMP();
//			if(USART_RX_STA&0x8000)
//		{					   
//			len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度
//			printf("\r\n您发送的消息为:\r\n");
//			for(t=0;t<len;t++)
//			{
//				USART1->DR=USART_RX_BUF[t];
//				while((USART1->SR&0X40)==0);//等待发送结束
//			}
//			printf("\r\n\r\n");//插入换行
//			USART_RX_STA=0;
//		}else
//		{
//			times++;
//			if(times%200==0)
//			{
//				printf("\r\nALIENTEK MiniSTM32开发板 串口实验\r\n");
//				printf("正点原子@ALIENTEK\r\n\r\n\r\n");
//			}
//			if(times%200==0)printf("请输入数据,以回车键结束\r\n");  
//			if(times%30==0)               //闪烁LED,提示系统正在运行.
//			delay_ms(10);   
//		}
         Bluetooth();
	}	 
} 


void Bluetooth()
{
	switch(res)
	{
		case 0x00:  led=0;   break;
		case 0x01:  led=1;   break;
	}
}






