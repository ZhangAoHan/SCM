#include "olcd.h"
#include "delay.h"

//初始化IIC
void iIC_Init(void)
{					     
 	RCC->APB2ENR|=1<<4;//先使能外设IO PORTC时钟 							 
	GPIOC->CRH&=0XFFF00FFF;//PC11/12 推挽输出
	GPIOC->CRH|=0X00033000;	   
	GPIOC->ODR|=3<<11;     //PC11,12 输出高
}
//产生IIC起始信号
void iIC_Start(void)
{
	sDA_OUT();     //sda线输出
	iIC_SDA=1;	  	  
	iIC_SCL=1;
	delay_us(4);
 	iIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	iIC_SCL=0;//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void iIC_Stop(void)
{
	sDA_OUT();//sda线输出
	iIC_SCL=0;
	iIC_SDA=0;
 	delay_us(4); 
	iIC_SCL=1;//STOP:when CLK is high DATA change form low to high
 	delay_us(4); 
	iIC_SDA=1;//发送I2C总线结束信号 						   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 iIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	sDA_IN();      //SDA设置为输入  
	iIC_SDA=1;delay_us(1);	   
	iIC_SCL=1;delay_us(1);	 
	while(rEAD_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			iIC_Stop();
			return 1;
		}
	}
	iIC_SCL=0;//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void iIC_Ack(void)
{
	iIC_SCL=0;
	sDA_OUT();
	iIC_SDA=0;
	delay_us(2);
	iIC_SCL=1;
	delay_us(2);
	iIC_SCL=0;
}
//不产生ACK应答		    
void iIC_NAck(void)
{
	iIC_SCL=0;
	sDA_OUT();
	iIC_SDA=1;
	delay_us(2);
	iIC_SCL=1;
	delay_us(2);
	iIC_SCL=0;
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void iIC_Write_Byte(u8 date)
{                        
    u8 t;   
	sDA_OUT(); 	    
    iIC_SCL=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        iIC_SDA=(date&0x80)>>7;
        date<<=1; 	  
		delay_us(2);   //对TEA5767这三个延时都是必须的
		iIC_SCL=1;
		delay_us(2); 
		iIC_SCL=0;	
		delay_us(2);
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 iIC_Read_Byte(unsigned char cmd)
{
	unsigned char i,receive=0;
	sDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        iIC_SCL=0; 
        delay_us(2);
		iIC_SCL=1;
        receive<<=1;
        if(rEAD_SDA)receive++;   
		delay_us(1); 
    }					 
    if (!cmd)
        iIC_NAck();//发送nACK
    else
        iIC_Ack(); //发送ACK   
    return receive;
}
 void Write_IIC_Command(unsigned char cmd)
{
   iIC_Start();
   iIC_Write_Byte(0x78);            //Slave address,SA0=0
	IIC_Wait_Ack();	
   iIC_Write_Byte(0x00); 			//write command
	IIC_Wait_Ack();	
   iIC_Write_Byte(cmd); 
	IIC_Wait_Ack();	
   IIC_Stop();
}
void Write_IIC_Data(unsigned char date)
{
   IIC_Start();
   iIC_Write_Byte(0x78); 			//D/C#=0; R/W#=0
	IIC_Wait_Ack();	
   iIC_Write_Byte(0x40); 			//write data
	IIC_Wait_Ack();	
   iIC_Write_Byte(date); 
	IIC_Wait_Ack();	
   IIC_Stop();
}
void OLED_WR_Byte(unsigned date,unsigned cmd)
{
	if(cmd)
			{

   Write_IIC_Data(date);
   
		}
	else {
   Write_IIC_Command(date);
		
	}


}
void fill_picture(unsigned char fill_Data)
{
	unsigned char m,n;
	for(m=0;m<8;m++)
	{
		OLED_WR_Byte(0xb0+m,0);		//page0-page1
		OLED_WR_Byte(0x00,0);		//low column start address
		OLED_WR_Byte(0x10,0);		//high column start address
		for(n=0;n<128;n++)
			{
				OLED_WR_Byte(fill_Data,1);
			}
	}
}
