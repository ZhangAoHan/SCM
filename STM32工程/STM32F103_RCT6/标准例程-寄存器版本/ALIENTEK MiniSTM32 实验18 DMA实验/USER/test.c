#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"   
#include "lcd.h"  
#include "key.h"  
#include "dma.h" 
//ALIENTEK Mini STM32开发板范例代码18
//DMA实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司
   	
const u8 TEXT_TO_SEND[]={"ALIENTEK Mini STM32 DMA 串口实验"};
#define TEXT_LENTH  sizeof(TEXT_TO_SEND)-1			//TEXT_TO_SEND字符串长度(不包含结束符)
u8 SendBuff[(TEXT_LENTH+2)*100];

int main(void)
{	
	u16 i;
	u8 t=0; 
	float pro=0;			//进度 
 	Stm32_Clock_Init(9);	//系统时钟设置
	uart_init(72,9600);	 	//串口初始化为9600
	delay_init(72);	   	 	//延时初始化 
	LED_Init();		  		//初始化与LED连接的硬件接口
	LCD_Init();			   	//初始化LCD 
	KEY_Init();				//按键初始化		 	
 	MYDMA_Config(DMA1_Channel4,(u32)&USART1->DR,(u32)SendBuff,(TEXT_LENTH+2)*100);//DMA1通道4,外设为串口1,存储器为SendBuff,长(TEXT_LENTH+2)*100.
 	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(60,50,200,16,16,"Mini STM32");	
	LCD_ShowString(60,70,200,16,16,"DMA TEST");	
	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,200,16,16,"2014/3/9");	
 	LCD_ShowString(60,130,200,16,16,"KEY0:Start");
	//显示提示信息	   
	for(i=0;i<(TEXT_LENTH+2)*100;i++)//填充ASCII字符集数据
    {
		if(t>=TEXT_LENTH)//加入换行符
		{ 
			SendBuff[i++]=0x0d; 
			SendBuff[i]=0x0a; 
			t=0;
		}else SendBuff[i]=TEXT_TO_SEND[t++];//复制TEXT_TO_SEND语句    
    }		 
	POINT_COLOR=BLUE;//设置字体为蓝色	  
	i=0;
	while(1)
	{
		t=KEY_Scan(0);
		if(t==KEY0_PRES)//KEY0按下
		{
			LCD_ShowString(60,150,200,16,16,"Start Transimit....");
			LCD_ShowString(60,170,200,16,16,"   %");//显示百分号
			printf("\r\nDMA DATA:\r\n "); 	    
		    USART1->CR3=1<<7;           //使能串口1的DMA发送       
			MYDMA_Enable(DMA1_Channel4);//开始一次DMA传输！	  
		    //等待DMA传输完成，此时我们来做另外一些事，点灯
		    //实际应用中，传输数据期间，可以执行另外的任务
		    while(1)
		    {
				if(DMA1->ISR&(1<<13))//等待通道4传输完成
				{
					DMA1->IFCR|=1<<13;//清除通道4传输完成标志
					break; 
		        }
				pro=DMA1_Channel4->CNDTR;//得到当前还剩余多少个数据
				pro=1-pro/((TEXT_LENTH+2)*100);//得到百分比	  
				pro*=100;      //扩大100倍
				LCD_ShowNum(60,170,pro,3,16);	  
		    }			    
			LCD_ShowNum(60,170,100,3,16);//显示100%	  
			LCD_ShowString(60,150,200,16,16,"Transimit Finished!");//提示传送完成
		}
		i++;
		delay_ms(10);
		if(i==20)
		{
			LED0=!LED0;//提示系统正在运行	
			i=0;
		}		   
	}
}







