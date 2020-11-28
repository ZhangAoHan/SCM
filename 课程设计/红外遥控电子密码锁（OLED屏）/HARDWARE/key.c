#include "key.h"
#include "sys.h"
#include "delay.h"
extern u8 KEY;
void key_init(void)
{
	RCC->APB2ENR|=1<<2;  //使能GPIOA时钟
	RCC->APB2ENR|=1<<3;  //使能GPIOB时钟
	JTAG_Set(SWD_ENABLE);	//关闭JTAG,开启SWD
	GPIOA->CRH&=0x0ff00000;    
	GPIOA->CRH|=0x80088888;   
	GPIOA->ODR|=0x9f00;    
	GPIOB->CRL&=0xfff00fff;    
	GPIOB->CRL|=0x00088000;   
	GPIOB->CRH&=0x0000ffff;    
	GPIOB->CRH|=0x88880000;    
	GPIOB->ODR|=0xf018;    
}

void Key_Scan(void)
{
	
			if(key1==0)
			{
				delay_ms(10);
				if(key1==0)
				{	KEY=1;
				while(!key1);}
			}		
	
			else if(key2==0)
			{
				delay_ms(10);
				if(key2==0)
				{	KEY=2;
				while(!key2);}
			}
	
			else if(key3==0)
			{
				delay_ms(10);
				if(key3==0)
				{	KEY=3;
				while(!key3);}
			}	

			else if(key4==0)
			{
				delay_ms(10);
				if(key4==0)
				{	KEY=4;
				while(!key4);}
			}	
	
			else if(key5==0)
			{
				delay_ms(10);
				if(key5==0)
				{	KEY=5;
				while(!key5);}
			}		
	
			else if(key6==0)
			{
				delay_ms(10);
				if(key6==0)
				{	KEY=6;
				while(!key6);}			}		
			else if(key7==0)
			{
				delay_ms(10);
				if(key7==0)
				{	KEY=7;
				while(!key7);}			}	

			else if(key8==0)
			{
				delay_ms(10);
				if(key8==0)
				{	KEY=8;
				while(!key8);}			}	
	
			else if(key9==0)
			{
				delay_ms(10);
				if(key9==0)
				{	KEY=9;
				while(!key9);}			}	

			else if(key10==0)
			{
				delay_ms(10);
				if(key10==0)
				{	KEY=10;
				while(!key10);}			}		
	
			else if(key11==0)
			{
				delay_ms(10);
				if(key11==0)
				{	KEY=11;
				while(!key11);}			}	
	
			else if(key12==0)
			{
				delay_ms(10);
				if(key12==0)
				{	KEY=12;
				while(!key12);}			}

         else KEY=0;  //没有按键按下			
}


