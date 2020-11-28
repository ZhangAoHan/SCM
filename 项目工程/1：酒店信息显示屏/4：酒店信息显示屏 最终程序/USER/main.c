#include "sys.h"
#include "usart.h"		
#include "delay.h"	 
#include "ds18b20.h"
#include "sensor.h"
#include "oled.h"


int Temperature1,Temperature2,Candela;
u16 adcx;
void HMI_display(void);
void HMISends(char *buf1);
void HMISendb(u8 buf);
void HMISendstart(void);
void ds18b20(void);

u8 home;
u8 value;
u8 temp[64];
u8 temp2[16];

int main(void)
{				 
	u8 t=0; 
	u8 len;


	Stm32_Clock_Init(9);	//系统时钟设置
	delay_init(72);	  		//延时初始化
	uart_init(72,9600); 	//串口初始化为9600
    uart2_init(72,19200);
	uart3_init(72,19200);

	HMISendstart();          //为确保串口HMI正常通信
	OLED_Init();	
	OLED_Clear();
	Adc_Init();
	delay_ms(1000);
	OLED_ShowCHinese(0,0,9);    //温度
	OLED_ShowCHinese(16,0,10);
	OLED_ShowChar(32,0,':',16);
	OLED_ShowCHinese(0,2,0);    //烟雾
	OLED_ShowCHinese(16,2,1);
	OLED_ShowChar(32,2,':',16);
	OLED_ShowCHinese(0,4,11);    //光强
	OLED_ShowCHinese(16,4,12);
	OLED_ShowChar(32,4,':',16);
	while(DS18B20_Init()) {;} //DS18B20初始化	
  	while(1)
	{
//	
//			if(USART1_RX_STA&0x80)
//		{					   
//			len=USART1_RX_STA&0x3f;//得到此次接收到的数据长度
//			for(t=0;t<len;t++)
//			{
//				temp[t]=USART1_RX_BUF[t];
//			}
//			USART1_RX_STA=0;
//		}
//		if(USART2_RX_STA&0x80)  //串口屏发送完数据
//		{
//			len=USART2_RX_STA&0x3f;//得到此次接收到的数据长度
//			for(t=0;t<len;t++)
//			{
//				temp2[t]=USART2_RX_BUF[t];   //得到接收的数据
//			}
//			if(temp2[0]==1||temp2[0]==2||temp2[0]==3||temp2[0]==4)
//			{
//				printf("房间号为：%d号房\r\n",temp2[0]);//插入换行
//				for(t=1;t<len;t++)
//				{
//				printf("预约时间为：%dH\r\n",temp2[t]-48);//插入换行
//				}
//				
//			}
//			else
//			{		
//				printf("错误提示：串口屏数据发送失败 %d\r\n",9);//插入换行
//				printf("\r\n");//插入换行
//			}
//			USART2_RX_STA=0;
//		}
//	    	HMI_display();
//			ds18b20();
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
		
void HMI_display()
{
			home=temp[0]-48;
		    value=temp[1]-48;
	if(home==1)
	{
		switch(value)
			{
				case 0:HMISends("Home1.home1money.val=0");HMISendb(0xff);break;
				case 1:HMISends("Home1.home1money.val=1");HMISendb(0xff);break;
				case 2:HMISends("Home1.home1money.val=2");HMISendb(0xff);break;
				case 3:HMISends("Home1.home1money.val=3");HMISendb(0xff);break;
				case 4:HMISends("Home1.home1money.val=4");HMISendb(0xff);break;
				case 5:HMISends("Home1.home1money.val=5");HMISendb(0xff);break;
				case 6:HMISends("Home1.home1money.val=6");HMISendb(0xff);break;
				case 7:HMISends("Home1.home1money.val=7");HMISendb(0xff);break;
				case 8:HMISends("Home1.home1money.val=8");HMISendb(0xff);break;
				case 9:HMISends("Home1.home1money.val=9");HMISendb(0xff);break;
			}
	}
		if(home==2)
	{
		switch(value)
			{
				case 0:HMISends("Home2.home2money.val=0");HMISendb(0xff);break;
				case 1:HMISends("Home2.home2money.val=1");HMISendb(0xff);break;
				case 2:HMISends("Home2.home2money.val=2");HMISendb(0xff);break;
				case 3:HMISends("Home2.home2money.val=3");HMISendb(0xff);break;
				case 4:HMISends("Home2.home2money.val=4");HMISendb(0xff);break;
				case 5:HMISends("Home2.home2money.val=5");HMISendb(0xff);break;
				case 6:HMISends("Home2.home2money.val=6");HMISendb(0xff);break;
				case 7:HMISends("Home2.home2money.val=7");HMISendb(0xff);break;
				case 8:HMISends("Home2.home2money.val=8");HMISendb(0xff);break;
				case 9:HMISends("Home2.home2money.val=9");HMISendb(0xff);break;
			}
	}
		if(home==3)
	{
		switch(value)
			{
				case 0:HMISends("Home3.home3money.val=0");HMISendb(0xff);break;
				case 1:HMISends("Home3.home3money.val=1");HMISendb(0xff);break;
				case 2:HMISends("Home3.home3money.val=2");HMISendb(0xff);break;
				case 3:HMISends("Home3.home3money.val=3");HMISendb(0xff);break;
				case 4:HMISends("Home3.home3money.val=4");HMISendb(0xff);break;
				case 5:HMISends("Home3.home3money.val=5");HMISendb(0xff);break;
				case 6:HMISends("Home3.home3money.val=6");HMISendb(0xff);break;
				case 7:HMISends("Home3.home3money.val=7");HMISendb(0xff);break;
				case 8:HMISends("Home3.home3money.val=8");HMISendb(0xff);break;
				case 9:HMISends("Home3.home3money.val=9");HMISendb(0xff);break;
			}
	}
		if(home==4)
	{
		switch(value)
			{
				case 0:HMISends("Home4.home4money.val=0");HMISendb(0xff);break;
				case 1:HMISends("Home4.home4money.val=1");HMISendb(0xff);break;
				case 2:HMISends("Home4.home4money.val=2");HMISendb(0xff);break;
				case 3:HMISends("Home4.home4money.val=3");HMISendb(0xff);break;
				case 4:HMISends("Home4.home4money.val=4");HMISendb(0xff);break;
				case 5:HMISends("Home4.home4money.val=5");HMISendb(0xff);break;
				case 6:HMISends("Home4.home4money.val=6");HMISendb(0xff);break;
				case 7:HMISends("Home4.home4money.val=7");HMISendb(0xff);break;
				case 8:HMISends("Home4.home4money.val=8");HMISendb(0xff);break;
				case 9:HMISends("Home4.home4money.val=9");HMISendb(0xff);break;
			}
	}
	
	if(home==5)     //预定房间
	{
		switch(value)
		{
			case 1:HMISends("Main.home1.bco=63488");HMISendb(0xff);break;
			case 2:HMISends("Main.home2.bco=63488");HMISendb(0xff);break;
			case 3:HMISends("Main.home3.bco=63488");HMISendb(0xff);break;
			case 4:HMISends("Main.home4.bco=63488");HMISendb(0xff);break;
		}
	}
	if(home==6)    //退房
	{
		switch(value)
		{
			case 1:HMISends("Main.home1.bco=2016");HMISendb(0xff);break;
			case 2:HMISends("Main.home2.bco=2016");HMISendb(0xff);break;
			case 3:HMISends("Main.home3.bco=2016");HMISendb(0xff);break;
			case 4:HMISends("Main.home4.bco=2016");HMISendb(0xff);break;
		}
	}
}
void ds18b20()
{
	Candela=Get_Adc_Average(ADC_CH1,10);
	Candela=409-Candela/10;
	OLED_ShowNum(48,4,Candela,3,16);
	OLED_ShowString(72,4,"Cd",16);
	
	adcx=Get_Adc_Average(ADC_CH4,10);
	adcx=(float)adcx*(3.3/4096);
	OLED_ShowNum(48,2,adcx,3,16);
	OLED_ShowString(72,2,"Ppm",16);
	
	Temperature1=DS18B20_Get_Temp();
	Temperature2=Temperature1/10;
	Temperature1=Temperature1/10; 
	OLED_ShowNum(48,0,Temperature1,2,16);
	OLED_ShowChar(64,0,'.',16);
	OLED_ShowNum(72,0,Temperature2,1,16);
	OLED_ShowChar(80,0,'C',16);
}
