#include "IIC.h"
#include "delay.h"


//��ʼ��IIC
void IIC_Init1(void)
{					     
 	RCC->APB2ENR|=1<<4;//��ʹ������IO PORTCʱ�� 							 
	GPIOC->CRL&=0XFFFFFF00;//PC1  0 �������
	GPIOC->CRL|=0X00000033;	   
	GPIOC->ODR|=3<<0;     //PC1   0 �����
}
//����IIC��ʼ�ź�
void IIC_Start1(void)
{
	SDA_OUT();     //sda�����
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void IIC_Stop1(void)
{
	SDA_OUT();//sda�����
	IIC_SCL=0;
	IIC_SDA=0;
 	delay_us(4); 
	IIC_SCL=1;//STOP:when CLK is high DATA change form low to high
 	delay_us(4); 
	IIC_SDA=1;//����I2C���߽����ź� 						   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_Wait_Ack1(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA����Ϊ����  
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
	IIC_SCL=0;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
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
//������ACKӦ��		    
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
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte1(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		IIC_SCL=1;
		delay_us(2); 
		IIC_SCL=0;	
		delay_us(2);
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC_Read_Byte1(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA����Ϊ����
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
        IIC_NAck1();//����nACK
    else
        IIC_Ack1(); //����ACK   
    return receive;
}

//IIC����д
//addr:������ַ 
//reg:�Ĵ�����ַ
//len:д�볤��
//buf:������
//����ֵ:0,����
//    ����,�������
uint8_t I2C_Write_Len(uint8_t addr,uint8_t reg,uint8_t len,uint8_t *buf)
{
    uint8_t i;
    IIC_Start1();
    IIC_Send_Byte1(addr); //����������ַ+д����
    IIC_Wait_Ack1();
    IIC_Send_Byte1(reg);         //д�Ĵ�����ַ
    IIC_Wait_Ack1();             //�ȴ�Ӧ��
    for(i=0;i<len;i++)
    {
        IIC_Send_Byte1(buf[i]);  //��������
        if(IIC_Wait_Ack1())      //�ȴ�ACK
        {
            IIC_Stop1();
            return 1;
        }
    }
    IIC_Stop1();
    return 0;
} 

//IIC������
//addr:������ַ
//reg:Ҫ��ȡ�ļĴ�����ַ
//len:Ҫ��ȡ�ĳ���
//buf:��ȡ�������ݴ洢��
//����ֵ:0,����
//    ����,�������
uint8_t I2C_Read_Len(uint8_t addr,uint8_t reg,uint8_t len,uint8_t *buf)
{ 
    IIC_Start1();
    IIC_Send_Byte1(addr); //����������ַ+д����
    IIC_Wait_Ack1();         //�ȴ�Ӧ��
    IIC_Send_Byte1(reg);         //д�Ĵ�����ַ
    IIC_Wait_Ack1();             //�ȴ�Ӧ��
	IIC_Start1();                
    IIC_Send_Byte1(addr|0x01); //����������ַ+������
    IIC_Wait_Ack1();             //�ȴ�Ӧ��
    while(len)
    {
        if(len==1)*buf=IIC_Read_Byte1(0);//������,����nACK 
		else *buf=IIC_Read_Byte1(1);		//������,����ACK  
		len--;
		buf++;  
    }
    IIC_Stop1();                 //����һ��ֹͣ����
    return 0;       
}

//IICдһ���ֽ� 
//devaddr:����IIC��ַ
//reg:�Ĵ�����ַ
//data:����
//����ֵ:0,����
//    ����,�������
uint8_t I2C_Write_Byte(uint8_t addr,uint8_t reg,uint8_t data)
{
    IIC_Start1();
    IIC_Send_Byte1(addr); //����������ַ+д����
    IIC_Wait_Ack1();
    IIC_Send_Byte1(reg);         //д�Ĵ�����ַ
    IIC_Wait_Ack1();             //�ȴ�Ӧ��
    IIC_Send_Byte1(data);        //��������
    IIC_Wait_Ack1();
    IIC_Stop1();
    return 0;
}

//IIC��һ���ֽ�
//reg:�Ĵ�����ַ 
//����ֵ:����������
uint8_t I2C_Read_Byte(uint8_t addr,uint8_t reg)
{
    uint8_t res;
    IIC_Start1();
    IIC_Send_Byte1(addr); //����������ַ+д����
    IIC_Wait_Ack1();             //�ȴ�Ӧ��
    IIC_Send_Byte1(reg);         //д�Ĵ�����ַ
    IIC_Wait_Ack1();             //�ȴ�Ӧ��
	IIC_Start1();                
    IIC_Send_Byte1(addr | 0x01); //����������ַ+������
    IIC_Wait_Ack1();             //�ȴ�Ӧ��
    res=IIC_Read_Byte1(0);		//������,����nACK  
    IIC_Stop1();                 //����һ��ֹͣ����
    return res;  
}


























