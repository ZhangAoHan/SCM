#include "fdc2214.h"
#include "delay.h"
#include "led.h"
#include "sys.h"
#include "usart.h"

u32 Data_FDC;
//FDC_I2C����д����**************************************************

//FDC IIC ��ʱ����
void FDC_IIC_Delay(void)
{
	unsigned int a,b;
	for(a=0;a<144;a++);
}


//��ʼ��IIC I/O��
void FDC_IIC_Init(void)
{	
//	RCC->APB2ENR|=1<<2;		//��ʹ������IO PORTAʱ�� 							 
//	GPIOA->CRH&=0XFFF00FFF;	//PA11/12 �������
//	GPIOA->CRH|=0X00033000;	   
//	GPIOA->ODR|=3<<11;     	//PA11/12 �����
	GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );	//ʹ��GPIOBʱ��
    
    RCC_APB2PeriphClockCmd(	RCC_APB2Periph_AFIO, ENABLE );
//    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//�ر�JTAG���ͷ�PB3,PB4,PA15
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_SetBits(GPIOB,GPIO_Pin_10|GPIO_Pin_11); 	//�����
}

//����IIC��ʼ�ź�
void FDC_IIC_Start(void)
{
	FDC_SDA_OUT();     //sda�����
	FDC_IIC_SDA=1;	  	  
	FDC_IIC_SCL=1;
	FDC_IIC_Delay();
 	FDC_IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	FDC_IIC_Delay();
	FDC_IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void FDC_IIC_Stop(void)
{
	FDC_SDA_OUT();//sda�����
	FDC_IIC_SCL=0;
	FDC_IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	FDC_IIC_Delay();
	FDC_IIC_SCL=1; 
	FDC_IIC_SDA=1;//����I2C���߽����ź�
	FDC_IIC_Delay();							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 FDC_IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	FDC_SDA_IN();      //SDA����Ϊ����  
	FDC_IIC_SDA=1;FDC_IIC_Delay();	   
	FDC_IIC_SCL=1;FDC_IIC_Delay();	 
	while(FDC_READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			FDC_IIC_Stop();
			return 1;
		}
	}
	FDC_IIC_SCL=0;//ʱ�����0 	   
	return 0;  
}
//����ACKӦ��
void FDC_IIC_Ack(void)
{
	FDC_IIC_SCL=0;
	FDC_SDA_OUT();
	FDC_IIC_SDA=0;
	FDC_IIC_Delay();
	FDC_IIC_SCL=1;
	FDC_IIC_Delay();
	FDC_IIC_SCL=0;
}
//������ACKӦ��		    
void FDC_IIC_NAck(void)
{
	FDC_IIC_SCL=0;
	FDC_SDA_OUT();
	FDC_IIC_SDA=1;
	FDC_IIC_Delay();
	FDC_IIC_SCL=1;
	FDC_IIC_Delay();
	FDC_IIC_SCL=0;
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void FDC_IIC_Send_Byte(u8 txd)
{                        
  u8 t;   
	FDC_SDA_OUT(); 	    
    FDC_IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        FDC_IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		    FDC_IIC_SCL=1;
		    FDC_IIC_Delay(); 
		    FDC_IIC_SCL=0;	
		    FDC_IIC_Delay();
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 FDC_IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	FDC_SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        FDC_IIC_SCL=0; 
        FDC_IIC_Delay();
		FDC_IIC_SCL=1;
        receive<<=1;
        if(FDC_READ_SDA)receive++;   
		FDC_IIC_Delay(); 
    }				 
    if (!ack)
        FDC_IIC_NAck();//����nACK
    else
        FDC_IIC_Ack(); //����ACK   
    return receive;
}

//FDC�Ĵ�������***********************************************************************

/*FDC2214���ú���
 *IICд2���ֽ� 
 *reg:�Ĵ�����ַ
 *data1:����1
 *data2:����2
 *����ֵ:0    ����
 *     ����  �������
*/
u8 Set_FDC2214(u8 reg,u8 MSB,u8 LSB) 				 
{ 
  FDC_IIC_Start(); 
	FDC_IIC_Send_Byte((FDC2214_ADDR<<1)|0);//����������ַ+д����
	
	if(FDC_IIC_Wait_Ack())	//�ȴ�Ӧ��
	{

		FDC_IIC_Stop();		 
		return 1;		
	}
    FDC_IIC_Send_Byte(reg);//д�Ĵ�����ַ
    FDC_IIC_Wait_Ack();		 //�ȴ�Ӧ�� 
	FDC_IIC_Send_Byte(MSB);  //��������1
	if(FDC_IIC_Wait_Ack())	 //�ȴ�ACK
	{
		FDC_IIC_Stop();	 
		return 1;		 
	}		 
	FDC_IIC_Send_Byte(LSB);  //��������2
	if(FDC_IIC_Wait_Ack())	 //�ȴ�ACK
	{
		FDC_IIC_Stop();	 
		return 1;		 
	}	
    FDC_IIC_Stop();	 
	return 0;
}

/*��ȡFDC2214�Ĵ�������
 *IIC��2���ֽ� 
 *reg:�Ĵ�����ַ 
 *����ֵ:����������
 */
u16 FDC_Read(u8 reg)
{
	u16 res;
  FDC_IIC_Start(); 
	FDC_IIC_Send_Byte((FDC2214_ADDR<<1)|0);//����������ַ+д����	
	FDC_IIC_Wait_Ack();		//�ȴ�Ӧ�� 
  FDC_IIC_Send_Byte(reg);	//д�Ĵ�����ַ
  FDC_IIC_Wait_Ack();		//�ȴ�Ӧ��
  FDC_IIC_Start();
	FDC_IIC_Send_Byte((FDC2214_ADDR<<1)|1);//����������ַ+������	
  FDC_IIC_Wait_Ack();		//�ȴ�Ӧ�� 
	res=FDC_IIC_Read_Byte(1)<<8;//��ȡ����,����ACK
	  
	res|=FDC_IIC_Read_Byte(0);//��ȡ����,����nACK
  FDC_IIC_Stop();			//����һ��ֹͣ����
	return res;		
}

/************************************************************************************
�õ�ͨ��xת���������
 *index:0 -> CH0
 *      1 -> CH1
 *      2 -> CH2
 *      3 -> CH3
����ֵ:����������
 ***********************************************************************************/
u32 FCD2214_ReadCH(u8 index) 
{
	u32 result;
	switch(index)
	{
		case 0:
		  result = FDC_Read(DATA_CH0)&0x0FFF;
		  result = (result<<16)|(FDC_Read(DATA_LSB_CH0));
			break;
		case 1:
			result = FDC_Read(DATA_CH1)&0x0FFF;
		  result = (result<<16)|(FDC_Read(DATA_LSB_CH1));
			break;
		case 2:
			result = FDC_Read(DATA_CH2)&0x0FFF;
		  result = (result<<16)|(FDC_Read(DATA_LSB_CH2));
			break;
		case 3:
			result = FDC_Read(DATA_CH3)&0x0FFF;
		  result = (result<<16)|(FDC_Read(DATA_LSB_CH3));
			break;
		default:break;
	}
	result =result&0x0FFFFFFF;
	return result;
}

/*FDC2214��ʼ������
 *����ֵ:0����ʼ������
 *       1��������
 */
u8 FDC2214_Init(void)
{
	u16 res;
	
	//���IIC���߳�ʼ��
	FDC_IIC_Init();
	
	//���ID�Ƿ���ȷ���ٳ�ʼ���Ĵ���
	res=FDC_Read(DEVICE_ID);
	printf("res:  %X\r\n",res);
	if(res==0x3055)
	{
		//����Set_FDC2214�Ĵ���
		Set_FDC2214(RCOUNT_CH0,0xFF,0xFF);				//�ο�����ת�����ʱ�䣨T=(RCOUNT_CH0*16)/Frefx��
		Set_FDC2214(RCOUNT_CH1,0xFF,0xFF);
		Set_FDC2214(RCOUNT_CH2,0xFF,0xFF);
		
		Set_FDC2214(SETTLECOUNT_CH0,0x04,0x00);		//ת��֮ǰ���ȶ�ʱ�䣨T=(SETTLECOUNT_CHx*16)/Frefx��
		Set_FDC2214(SETTLECOUNT_CH1,0x04,0x00);
		Set_FDC2214(SETTLECOUNT_CH2,0x04,0x00);
		
		Set_FDC2214(CLOCK_DIVIDERS_C_CH0,0x10,0x01);//ѡ����0.01MHz ~ 10MHz�Ĵ�����Ƶ��
		Set_FDC2214(CLOCK_DIVIDERS_C_CH1,0x10,0x01);//Frefx = Fclk = 43.4MHz/2(2��Ƶ)
		Set_FDC2214(CLOCK_DIVIDERS_C_CH2,0x10,0x01);//CHx_REF_DIVIDER=2;CHx_FIN_SEL=2
		
		Set_FDC2214(DRIVE_CURRENT_CH0,0x8C,0x40);//0.146ma��������ʱ�ӽ���+ת��ʱ�������������
		Set_FDC2214(DRIVE_CURRENT_CH1,0x8C,0x40);
		Set_FDC2214(DRIVE_CURRENT_CH2,0x88,0x00);
		Set_FDC2214(DRIVE_CURRENT_CH3,0x88,0x00);		
		
		
		Set_FDC2214(ERROR_CONFIG,0x00,0x00);//ȫ����ֹ����㱨
		
		Set_FDC2214(MUX_CONFIG,0xC2,0x0C);//ͨ��0��1��2 ��3��ѡ��10MhzΪ�����񵴲���Ƶ�ʵ�������ã���ͨ������ͨ��
		
		Set_FDC2214(CONFIG,0x1E,0x01);
		return 1;
	}
	
	return 0;
}

/*������·����
 *index:0����·0
 *      1����·1
 *      2����·2
 *      3����·3
 *����ֵ����·�ܵ���C
 */
float Cap_Calculate(u8 index)
{
	float Cap;
	Data_FDC = FCD2214_ReadCH(index);
//	Cap = 56645.763f/((float)Data_FDC);
//	return ((Cap*Cap)-33);
	Cap = 232021045.248/(Data_FDC);
	return (Cap*Cap);
}



