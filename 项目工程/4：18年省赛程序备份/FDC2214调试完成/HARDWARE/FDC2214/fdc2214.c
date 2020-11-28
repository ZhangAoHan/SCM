#include "fdc2214.h"
#include "delay.h"
#include "led.h"
#include "sys.h"
#include "usart.h"

u32 Data_FDC;
//FDC_I2C及读写操作**************************************************

//FDC IIC 延时函数
void FDC_IIC_Delay(void)
{
	unsigned int a,b;
	for(a=0;a<144;a++);
}


//初始化IIC I/O口
void FDC_IIC_Init(void)
{	
//	RCC->APB2ENR|=1<<2;		//先使能外设IO PORTA时钟 							 
//	GPIOA->CRH&=0XFFF00FFF;	//PA11/12 推挽输出
//	GPIOA->CRH|=0X00033000;	   
//	GPIOA->ODR|=3<<11;     	//PA11/12 输出高
	GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );	//使能GPIOB时钟
    
    RCC_APB2PeriphClockCmd(	RCC_APB2Periph_AFIO, ENABLE );
//    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//关闭JTAG，释放PB3,PB4,PA15
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_SetBits(GPIOB,GPIO_Pin_10|GPIO_Pin_11); 	//输出高
}

//产生IIC起始信号
void FDC_IIC_Start(void)
{
	FDC_SDA_OUT();     //sda线输出
	FDC_IIC_SDA=1;	  	  
	FDC_IIC_SCL=1;
	FDC_IIC_Delay();
 	FDC_IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	FDC_IIC_Delay();
	FDC_IIC_SCL=0;//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void FDC_IIC_Stop(void)
{
	FDC_SDA_OUT();//sda线输出
	FDC_IIC_SCL=0;
	FDC_IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	FDC_IIC_Delay();
	FDC_IIC_SCL=1; 
	FDC_IIC_SDA=1;//发送I2C总线结束信号
	FDC_IIC_Delay();							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 FDC_IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	FDC_SDA_IN();      //SDA设置为输入  
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
	FDC_IIC_SCL=0;//时钟输出0 	   
	return 0;  
}
//产生ACK应答
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
//不产生ACK应答		    
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
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void FDC_IIC_Send_Byte(u8 txd)
{                        
  u8 t;   
	FDC_SDA_OUT(); 	    
    FDC_IIC_SCL=0;//拉低时钟开始数据传输
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
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 FDC_IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	FDC_SDA_IN();//SDA设置为输入
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
        FDC_IIC_NAck();//发送nACK
    else
        FDC_IIC_Ack(); //发送ACK   
    return receive;
}

//FDC寄存器操作***********************************************************************

/*FDC2214设置函数
 *IIC写2个字节 
 *reg:寄存器地址
 *data1:数据1
 *data2:数据2
 *返回值:0    正常
 *     其他  错误代码
*/
u8 Set_FDC2214(u8 reg,u8 MSB,u8 LSB) 				 
{ 
  FDC_IIC_Start(); 
	FDC_IIC_Send_Byte((FDC2214_ADDR<<1)|0);//发送器件地址+写命令
	
	if(FDC_IIC_Wait_Ack())	//等待应答
	{

		FDC_IIC_Stop();		 
		return 1;		
	}
    FDC_IIC_Send_Byte(reg);//写寄存器地址
    FDC_IIC_Wait_Ack();		 //等待应答 
	FDC_IIC_Send_Byte(MSB);  //发送数据1
	if(FDC_IIC_Wait_Ack())	 //等待ACK
	{
		FDC_IIC_Stop();	 
		return 1;		 
	}		 
	FDC_IIC_Send_Byte(LSB);  //发送数据2
	if(FDC_IIC_Wait_Ack())	 //等待ACK
	{
		FDC_IIC_Stop();	 
		return 1;		 
	}	
    FDC_IIC_Stop();	 
	return 0;
}

/*读取FDC2214寄存器数据
 *IIC读2个字节 
 *reg:寄存器地址 
 *返回值:读到的数据
 */
u16 FDC_Read(u8 reg)
{
	u16 res;
  FDC_IIC_Start(); 
	FDC_IIC_Send_Byte((FDC2214_ADDR<<1)|0);//发送器件地址+写命令	
	FDC_IIC_Wait_Ack();		//等待应答 
  FDC_IIC_Send_Byte(reg);	//写寄存器地址
  FDC_IIC_Wait_Ack();		//等待应答
  FDC_IIC_Start();
	FDC_IIC_Send_Byte((FDC2214_ADDR<<1)|1);//发送器件地址+读命令	
  FDC_IIC_Wait_Ack();		//等待应答 
	res=FDC_IIC_Read_Byte(1)<<8;//读取数据,发送ACK
	  
	res|=FDC_IIC_Read_Byte(0);//读取数据,发送nACK
  FDC_IIC_Stop();			//产生一个停止条件
	return res;		
}

/************************************************************************************
得到通道x转换后的数据
 *index:0 -> CH0
 *      1 -> CH1
 *      2 -> CH2
 *      3 -> CH3
返回值:读到的数据
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

/*FDC2214初始化函数
 *返回值:0：初始化正常
 *       1：不正常
 */
u8 FDC2214_Init(void)
{
	u16 res;
	
	//软件IIC总线初始化
	FDC_IIC_Init();
	
	//检测ID是否正确，再初始化寄存器
	res=FDC_Read(DEVICE_ID);
	printf("res:  %X\r\n",res);
	if(res==0x3055)
	{
		//设置Set_FDC2214寄存器
		Set_FDC2214(RCOUNT_CH0,0xFF,0xFF);				//参考计数转换间隔时间（T=(RCOUNT_CH0*16)/Frefx）
		Set_FDC2214(RCOUNT_CH1,0xFF,0xFF);
		Set_FDC2214(RCOUNT_CH2,0xFF,0xFF);
		
		Set_FDC2214(SETTLECOUNT_CH0,0x04,0x00);		//转换之前的稳定时间（T=(SETTLECOUNT_CHx*16)/Frefx）
		Set_FDC2214(SETTLECOUNT_CH1,0x04,0x00);
		Set_FDC2214(SETTLECOUNT_CH2,0x04,0x00);
		
		Set_FDC2214(CLOCK_DIVIDERS_C_CH0,0x10,0x01);//选择在0.01MHz ~ 10MHz的传感器频率
		Set_FDC2214(CLOCK_DIVIDERS_C_CH1,0x10,0x01);//Frefx = Fclk = 43.4MHz/2(2分频)
		Set_FDC2214(CLOCK_DIVIDERS_C_CH2,0x10,0x01);//CHx_REF_DIVIDER=2;CHx_FIN_SEL=2
		
		Set_FDC2214(DRIVE_CURRENT_CH0,0x8C,0x40);//0.146ma（传感器时钟建立+转换时间的驱动电流）
		Set_FDC2214(DRIVE_CURRENT_CH1,0x8C,0x40);
		Set_FDC2214(DRIVE_CURRENT_CH2,0x88,0x00);
		Set_FDC2214(DRIVE_CURRENT_CH3,0x88,0x00);		
		
		
		Set_FDC2214(ERROR_CONFIG,0x00,0x00);//全部禁止错误汇报
		
		Set_FDC2214(MUX_CONFIG,0xC2,0x0C);//通道0，1，2 ，3；选择10Mhz为超过振荡槽振荡频率的最低设置，多通道，四通道
		
		Set_FDC2214(CONFIG,0x1E,0x01);
		return 1;
	}
	
	return 0;
}

/*测量线路电容
 *index:0：线路0
 *      1：线路1
 *      2：线路2
 *      3：线路3
 *返回值：线路总电容C
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



