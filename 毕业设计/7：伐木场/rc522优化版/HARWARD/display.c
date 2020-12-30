#include "display.h"
#include "rc522.h"
#include "lcd.h"
#include "text.h"
#include "dht11.h"
#include "adc.h"
#include "usart.h"	
extern u8 user;
extern int ID[12];  
unsigned char card_1[4]={224,147,168,112}; //卡号
unsigned char card_2[4]={213,196,112,34}; //卡号
unsigned char card_3[4]={50,70,216,26}; //卡号
extern unsigned char CT[2];//卡类型
extern unsigned char SN[4]; //卡号
extern unsigned char RFID[16];			//存放RFID 
extern unsigned char RFID1[16];
extern u8 KEY[6];
extern u8 temperature;  	    
extern u8 humidity;  	  
 u16 adcx;
 u16 adcx2;
extern u8 page;
u8 times;
extern int dt[4];         //  电机、粉尘监测、下雨监测、火源检测（1正常   0异常）

void RFID_read(void)
{

		unsigned char status;
		status = PcdRequest(PICC_REQALL,CT);/*尋卡*/
		if(status==MI_OK)//尋卡成功
		{
			 status=MI_ERR;
			 status = PcdAnticoll(SN);/*防冲撞*/
		}	
		if(status==MI_OK)
		{
			status=MI_ERR;
			status =PcdSelect(SN);
		}

		if(status==MI_OK)//選卡成功
		{
			 status=MI_ERR;
			 status =PcdAuthState(0x61,0x06,KEY,SN);
		 }
	
		 if(status==MI_OK)//驗證成功
		 {
			 status=MI_ERR;
			
			if(card_1[0]==SN[0]&&card_1[1]==SN[1]&&card_1[2]==SN[2]&&card_1[3]==SN[3]&&user!=21)	 user=1;
			else if(card_2[0]==SN[0]&&card_2[1]==SN[1]&&card_2[2]==SN[2]&&card_2[3]==SN[3]&&user!=22)	 user=2;
			 else if(card_3[0]==SN[0]&&card_3[1]==SN[1]&&card_3[2]==SN[2]&&card_3[3]==SN[3]&&user!=23)	 user=3;
				
			 
//			 user=!user;
						ID[0]=SN[0]/100;
			 ID[1]=(SN[0]%100)/10;
			 ID[2]=SN[0]%10;
			 			 ID[3]=SN[1]/100;
			 ID[4]=(SN[1]%100)/10;
			 ID[5]=SN[1]%10;
			 			 ID[6]=SN[2]/100;
			 ID[7]=(SN[2]%100)/10;
			 ID[8]=SN[2]%10;
			 			 ID[9]=SN[3]/100;
			 ID[10]=(SN[3]%100)/10;
			 ID[11]=SN[3]%10;
			
			door=1;
		  } 
}




void LED_Init(void)
{
	RCC->APB2ENR|=1<<4;    //使能PORTc时钟	   	 
	   	 
	GPIOC->CRL&=0X00000000; 
	GPIOC->CRL|=0X88333333;   
	GPIOC->ODR|=1<<3;      //P8,9 输出高	
  

											
}

void control(void)
{
	RFID_read();
	adcx=Get_Adc_Average(ADC_CH1,5);   //粉尘
	adcx2=Get_Adc_Average(ADC_CH2,5);	//下雨
	if(adcx>=2000)  //异常
	{
		dt[1]=0;
		dt[0]=0;
		FS=0;  
	}
	else
	{
		dt[1]=1;
	}
	if(adcx2>4000)   //正常
	{
		dt[2]=1;
	}
	else
	{
		dt[2]=0;
	}
	if(HY==0)
	{
		dt[3]=0;
		dt[0]=0;          //开启风扇
		FS=0;  
	}
	else
	{
		dt[3]=1;      
	}
	if(HY==1&&adcx<2000)
	{  
		dt[0]=1;          //关闭风扇
		FS=1;
	}
	
}

void PWM_Init(u16 arr,u16 psc)
{
	RCC->APB2ENR|=1<<3;    //使能PORTB时钟
	RCC->APB1ENR|=1<<2;	//TIM4时钟使能    
	GPIOB->CRH&=0XFFFFFFF0;	//PB8清除之前的设置
	GPIOB->CRH|=0X0000000B;	//复用功能输出
	TIM4->ARR=arr;             //设定计数器自动重装值 
	TIM4->PSC=psc;             //预分频器分频
	TIM4->CCMR2|=6<<4;         //CH3 PWM1模式		 
	TIM4->CCMR2|=1<<3;         //CH3预装载使能	    
	TIM4->CCER|=1<<8;          //CH3输出使能	
	TIM4->CR1=0x0080;          //ARPE使能 
	TIM4->CR1|=0x01;          //使能定时器3	
}
//定时器3中断服务程序	 
void TIM3_IRQHandler(void)
{ 		    		  			    
	if(TIM3->SR&0X0001)//溢出中断
	{
		if(door==1)
		{
			times++;
			PWM=20;    //开门5s
			if(times>=5)
			{
			times=0;
			PWM=10; 	
			door=0;
			}
			
		}
		
	}				   
	TIM3->SR&=~(1<<0);//清除中断标志位 	    
}
void TIM3_Int_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<1;	//TIM3时钟使能    
 	TIM3->ARR=arr;  	//设定计数器自动重装值//刚好1ms    
	TIM3->PSC=psc;  	//预分频器7200,得到10Khz的计数时钟		  
	TIM3->DIER|=1<<0;   //允许更新中断	  
	TIM3->CR1|=0x01;    //使能定时器3
  	MY_NVIC_Init(1,3,TIM3_IRQn,2);//抢占1，子优先级3，组2									 
}


