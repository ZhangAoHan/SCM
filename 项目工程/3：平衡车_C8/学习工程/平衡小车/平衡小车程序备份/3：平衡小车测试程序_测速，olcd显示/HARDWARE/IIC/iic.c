#include "iic.h"
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
void iIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	sDA_OUT(); 	    
    iIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        iIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		iIC_SCL=1;
		delay_us(2); 
		iIC_SCL=0;	
		delay_us(2);
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 iIC_Read_Byte(unsigned char ack)
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
    if (!ack)
        iIC_NAck();//����nACK
    else
        iIC_Ack(); //����ACK   
    return receive;
}



