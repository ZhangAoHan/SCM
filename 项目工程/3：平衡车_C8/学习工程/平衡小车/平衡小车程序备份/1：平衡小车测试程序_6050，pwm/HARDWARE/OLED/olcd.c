#include "olcd.h"
#include "delay.h"

//��ʼ��IIC
void iIC_Init(void)
{					     
 	RCC->APB2ENR|=1<<4;//��ʹ������IO PORTCʱ�� 							 
	GPIOC->CRH&=0XFFF00FFF;//PC11/12 �������
	GPIOC->CRH|=0X00033000;	   
	GPIOC->ODR|=3<<11;     //PC11,12 �����
}
//����IIC��ʼ�ź�
void iIC_Start(void)
{
	sDA_OUT();     //sda�����
	iIC_SDA=1;	  	  
	iIC_SCL=1;
	delay_us(4);
 	iIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	iIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void iIC_Stop(void)
{
	sDA_OUT();//sda�����
	iIC_SCL=0;
	iIC_SDA=0;
 	delay_us(4); 
	iIC_SCL=1;//STOP:when CLK is high DATA change form low to high
 	delay_us(4); 
	iIC_SDA=1;//����I2C���߽����ź� 						   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 iIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	sDA_IN();      //SDA����Ϊ����  
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
	iIC_SCL=0;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
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
//������ACKӦ��		    
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
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void iIC_Write_Byte(u8 date)
{                        
    u8 t;   
	sDA_OUT(); 	    
    iIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        iIC_SDA=(date&0x80)>>7;
        date<<=1; 	  
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		iIC_SCL=1;
		delay_us(2); 
		iIC_SCL=0;	
		delay_us(2);
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 iIC_Read_Byte(unsigned char cmd)
{
	unsigned char i,receive=0;
	sDA_IN();//SDA����Ϊ����
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
        iIC_NAck();//����nACK
    else
        iIC_Ack(); //����ACK   
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
