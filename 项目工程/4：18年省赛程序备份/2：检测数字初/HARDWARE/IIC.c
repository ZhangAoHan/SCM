#include "IIC.h"
#include "delay.h"


//初始化IIC
void IIC_Init1(void)
{					     
 	RCC->APB2ENR|=1<<4;//先使能外设IO PORTC时钟 							 
	GPIOC->CRL&=0XFFFFFF00;//PC1  0 推挽输出
	GPIOC->CRL|=0X00000033;	   
	GPIOC->ODR|=3<<0;     //PC1   0 输出高
}
//产生IIC起始信号
void IIC_Start1(void)
{
	SDA_OUT();     //sda线输出
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL=0;//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void IIC_Stop1(void)
{
	SDA_OUT();//sda线输出
	IIC_SCL=0;
	IIC_SDA=0;
 	delay_us(4); 
	IIC_SCL=1;//STOP:when CLK is high DATA change form low to high
 	delay_us(4); 
	IIC_SDA=1;//发送I2C总线结束信号 						   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 IIC_Wait_Ack1(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA设置为输入  
	IIC_SDA=1;delay_us(1);	   
	IIC_SCL=1;delay_us(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop1();
			return 1;
		}
	}
	IIC_SCL=0;//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void IIC_Ack1(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}
//不产生ACK应答		    
void IIC_NAck1(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_Byte1(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    IIC_SCL=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		delay_us(2);   //对TEA5767这三个延时都是必须的
		IIC_SCL=1;
		delay_us(2); 
		IIC_SCL=0;	
		delay_us(2);
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 IIC_Read_Byte1(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        delay_us(2);
		IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck1();//发送nACK
    else
        IIC_Ack1(); //发送ACK   
    return receive;
}

//IIC连续写
//addr:器件地址 
//reg:寄存器地址
//len:写入长度
//buf:数据区
//返回值:0,正常
//    其他,错误代码
uint8_t I2C_Write_Len(uint8_t addr,uint8_t reg,uint8_t len,uint8_t *buf)
{
    uint8_t i;
    IIC_Start1();
    IIC_Send_Byte1(addr); //发送器件地址+写命令
    IIC_Wait_Ack1();
    IIC_Send_Byte1(reg);         //写寄存器地址
    IIC_Wait_Ack1();             //等待应答
    for(i=0;i<len;i++)
    {
        IIC_Send_Byte1(buf[i]);  //发送数据
        if(IIC_Wait_Ack1())      //等待ACK
        {
            IIC_Stop1();
            return 1;
        }
    }
    IIC_Stop1();
    return 0;
} 

//IIC连续读
//addr:器件地址
//reg:要读取的寄存器地址
//len:要读取的长度
//buf:读取到的数据存储区
//返回值:0,正常
//    其他,错误代码
uint8_t I2C_Read_Len(uint8_t addr,uint8_t reg,uint8_t len,uint8_t *buf)
{ 
    IIC_Start1();
    IIC_Send_Byte1(addr); //发送器件地址+写命令
    IIC_Wait_Ack1();         //等待应答
    IIC_Send_Byte1(reg);         //写寄存器地址
    IIC_Wait_Ack1();             //等待应答
	IIC_Start1();                
    IIC_Send_Byte1(addr|0x01); //发送器件地址+读命令
    IIC_Wait_Ack1();             //等待应答
    while(len)
    {
        if(len==1)*buf=IIC_Read_Byte1(0);//读数据,发送nACK 
		else *buf=IIC_Read_Byte1(1);		//读数据,发送ACK  
		len--;
		buf++;  
    }
    IIC_Stop1();                 //产生一个停止条件
    return 0;       
}

//IIC写一个字节 
//devaddr:器件IIC地址
//reg:寄存器地址
//data:数据
//返回值:0,正常
//    其他,错误代码
uint8_t I2C_Write_Byte(uint8_t addr,uint8_t reg,uint8_t data)
{
    IIC_Start1();
    IIC_Send_Byte1(addr); //发送器件地址+写命令
    IIC_Wait_Ack1();
    IIC_Send_Byte1(reg);         //写寄存器地址
    IIC_Wait_Ack1();             //等待应答
    IIC_Send_Byte1(data);        //发送数据
    IIC_Wait_Ack1();
    IIC_Stop1();
    return 0;
}

//IIC读一个字节
//reg:寄存器地址 
//返回值:读到的数据
uint8_t I2C_Read_Byte(uint8_t addr,uint8_t reg)
{
    uint8_t res;
    IIC_Start1();
    IIC_Send_Byte1(addr); //发送器件地址+写命令
    IIC_Wait_Ack1();             //等待应答
    IIC_Send_Byte1(reg);         //写寄存器地址
    IIC_Wait_Ack1();             //等待应答
	IIC_Start1();                
    IIC_Send_Byte1(addr | 0x01); //发送器件地址+读命令
    IIC_Wait_Ack1();             //等待应答
    res=IIC_Read_Byte1(0);		//读数据,发送nACK  
    IIC_Stop1();                 //产生一个停止条件
    return res;  
}


























