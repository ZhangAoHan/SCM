#include "sys.h"
#include "usart.h"		
#include "delay.h"	 

void HMISends(char *buf1);
void HMISendb(u8 buf);
void HMISendstart(void);
int main(void)
{				 
	u8 t=0; 
	u8 len;
	u8 temp[64];
	u8 value;
	Stm32_Clock_Init(9);	//系统时钟设置
	delay_init(72);	  		//延时初始化
	uart_init(72,9600); 	//串口初始化为9600
    uart2_init(72,19200);
	HMISendstart();          //为确保串口HMI正常通信
  	while(1)
	{
			if(USART1_RX_STA&0x80)
		{					   
			len=USART1_RX_STA&0x3f;//得到此次接收到的数据长度
			for(t=0;t<len;t++)
			{
				temp[t]=USART1_RX_BUF[t];
				USART1->DR=USART1_RX_BUF[t];
				while((USART1->SR&0X40)==0);//等待发送结束
//				printf("%d\r\n",temp[t]-48);//插入换行
			}
		
			USART1_RX_STA=0;
		}


		value=temp[0]-48;
			switch(value)
			{
				case 0:HMISends("money1.val=0");HMISendb(0xff);break;
				case 1:HMISends("money1.val=1");HMISendb(0xff);break;
				case 2:HMISends("money1.val=2");HMISendb(0xff);break;
				case 3:HMISends("money1.val=3");HMISendb(0xff);break;
				case 4:HMISends("money1.val=4");HMISendb(0xff);break;
				case 5:HMISends("money1.val=5");HMISendb(0xff);break;
				case 6:HMISends("money1.val=6");HMISendb(0xff);break;
				case 7:HMISends("money1.val=7");HMISendb(0xff);break;
				case 8:HMISends("money1.val=8");HMISendb(0xff);break;
				case 9:HMISends("money1.val=9");HMISendb(0xff);break;
			}



		}
}

void HMISends(char *buf1)		  //字符串发送函数
{
	u8 i=0;
	while(1)
	{
	 if(buf1[i]!=0)
	 	{
			
			USART2->DR=buf1[i];
			while((USART2->SR&0X40)==0) { };  //等待发送结束
		 	i++;
		}
	 else 
	 return ;

		}
	}
void HMISendb(u8 k)		         //字节发送函数
{		 
	u8 i;
	 for(i=0;i<3;i++)
	 {
	 if(k!=0)
	 	{
			USART2->DR=k;
			while((USART2->SR&0X40)==0);//等待发送结束
		}
	 else 
	 return ;

	 } 
} 
void HMISendstart(void)
	{
	 	delay_ms(200);
		HMISendb(0xff);
		delay_ms(200);
	}
		


