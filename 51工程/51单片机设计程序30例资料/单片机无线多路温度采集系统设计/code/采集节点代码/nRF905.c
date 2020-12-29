/*****************************************************************************************
*文件名称：nRF905.c
*说明：本文件为无线通信器件nRF905驱动函数文件
*功能：驱动函数实例化
*修改：无
*版本：V1.0.0
*作者：YuanDong
*时间：2009.07.03
*****************************************************************************************/
#define  _NRF905_GLOBAL_  1
#include "nRF905.h"
uchar code TxAddress[2]={0xCC,0xCC};	//发送地址缓冲区
/******************nRF905寄存器配置参数*********************************/
uchar code nRFConfig[10]=	 
{
	0x6b,               	  //CH_NO,配置频段在433.1MHZ
	0x0c,               	  //输出功率为10db,不重发,节电为正常模式
	0x22,                	  //地址宽度设置,为2字节
	0x05,0x05,            	//接收发送有效数据长度为5字节
	0xCC,0xCC,0xCC,0xCC,  	//接收地址
	0x58                  	//CRC充许,8位CRC校验,外部时钟信号不使能,16M晶振
};
/*****************************************************************************************
*函数名称：nRF_Delay(uint i)
*函数功能：延时函数
*函数入口：延时时间i
*函数出口：无
*****************************************************************************************/
void nRF_Delay(uint time)
{
	 uint i;
	 for(i=0;i<time;i++)
	 {
	 	 _nop_();
	 }
}
/*****************************************************************************************
*函数名称：Spi_Write(uchar TxDATA)
*函数功能：Spi口写数据到nRF905内
*函数入口：Spi发送数据TxDATA
*函数出口：无
*****************************************************************************************/
void Spi_Write(uchar TxDATA)
{
	register uchar i = 8;
	while(i--)
	{
		nRF_Delay(10);
		SCK = 0;
		MOSI = (bit)(TxDATA & 0x80);
		TxDATA <<= 1;
		nRF_Delay(10);
		SCK = 1;
	}
	SCK = 0;
}
/*****************************************************************************************
*函数名称：Spi_Read(void)
*函数功能：Spi口从nRF905内读数据
*函数入口：无
*函数出口：返回Spi读取数据
*****************************************************************************************/
uchar Spi_Read(void)
{
	register uchar i = 8;
	uchar readData;
	while(i--)
	{
		 readData <<= 1;
		 SCK = 0;
		 nRF_Delay(2);
		 readData |= MISO;
		 SCK = 1;
		 nRF_Delay(2);
	}
	SCK = 0;
	return readData;
}
/******************************************************************************************函数名称：nRF905_StandBy(void)
*函数功能：切换nRF905到待机状态
*函数入口：无
*函数出口：无
*****************************************************************************************/             
void nRF905_StandBy(void)
{
    PWR    = 1;
    TX_EN  = 0;
    TRX_CE = 0;
}
/*****************************************************************************************
*函数名称：nRF905_Off(void)
*函数功能：关闭nRF905
*函数入口：无
*函数出口：无
*****************************************************************************************/   
void nRF905_Off(void)
{
    PWR = 0;
}
/*****************************************************************************************
*函数名称：nRF905_TxOn(void)
*函数功能：数据发送使能
*函数入口：无
*函数出口：无
*****************************************************************************************/   
void nRF905_TxOn(void)
{
	  PWR    = 1;
	  TX_EN  = 1;
	  TRX_CE = 0;
}
/*****************************************************************************************
*函数名称：nRF905_TxSend(void)
*函数功能：产生数据发送/接收使能脉冲
*函数入口：无
*函数出口：无
*****************************************************************************************/  
void nRF905_TxSend(void)
{
    TRX_CE = 1;
    nRF_Delay(650);//延时686us>650us,模式切换
    TRX_CE = 0;
}
/******************************************************************************************函数名称：nRF905_RxOn(void)
*函数功能：使能数据接收功能
*函数入口：无
*函数出口：无
*****************************************************************************************/  
void nRF905_RxOn(void)
{
    PWR    = 1;
    TX_EN  = 0;
    TRX_CE = 1;
}
/*****************************************************************************************
*函数名称：nRF905_Config(void)
*函数功能：主机通过Spi接口向905配置寄存器写入配置数据
*函数入口：无
*函数出口：无
*****************************************************************************************/
void nRF905_Config(void)
{
	uchar i;
	CSN = 0;                //使能SPI口写配置命令
	Spi_Write(WC);	        //写放配置命令
	SPI_WR(WC);					
	for (i=0;i<10;i++)			//写放配置字
	{
		SPI_WR(nRFConfig[i]);
	}
	CSN = 1;;			//关闭SPI口
}
/*****************************************************************************************
*函数名称：nRF905_Init(void)
*函数功能：初始化nRF905
*函数入口：无
*函数出口：无
*****************************************************************************************/
void nRF905_Init(void)
{
	nRF905_StandBy();			//切换到待机状态
	nRF_Delay(3);				  //延时切换到上电模式  
	nRF905_Config();			//向905配置寄存器写入信息
}
/*****************************************************************************************
*函数名称：nRF905_SetTxAddress(void)
*函数功能：写TX地址
*函数入口：无
*函数出口：无
*****************************************************************************************/
void nRF905_SetTxAddress(void)
{
	uchar i;
	CSN = 0;              //使能SPI口发送控制命令
	SPI_WR(WTA);				  //发送地址命令
	for (i=0;i<2;i++)			//发送两个字节地址
	{
		SPI_WR(TxAddress[i]);
	}
	CSN = 1;
}
/*****************************************************************************************
*函数名称：nRF905_SetData(void)
*函数功能：写TX地址
*函数入口：无
*函数出口：无
*****************************************************************************************/
void nRF905_SetData(void)
{
	uchar i;
  CSN = 0;                 //使能SPI口发送控制命令
	SPI_WR(WTP);			       //向TX-Payload寄存器写入发送有效数据
	for (i=0;i<5;i++)
	{
		SPI_WR(TxdBuf[i]);		 //SPI口传送发送缓冲区数据
	}							           
	CSN = 1;	
}
/*****************************************************************************************
*函数名称：nRF905_WaitSended(void)
*函数功能：等待Tx结束
*函数入口：无
*函数出口：无
*****************************************************************************************/
void nRF905_WaitSended(void)
{
   while(DR == 0);
}
/*****************************************************************************************
*函数名称：RF905_SendData(void)
*函数功能：发送数据
*函数入口：无
*函数出口：无
*****************************************************************************************/
void nRF905_SendData(void)
{
   nRF905_TxOn();				    //切换到发送模式
   nRF905_SetTxAddress();		//写发送地址
   nRF905_SetData();			  //写发送数据
   nRF905_TxSend();				  //启动发送一次
   nRF905_WaitSended();			//等待发送结束
}
/*****************************************************************************************
*函数名称：nRF905_ReadData()
*函数功能：读出接收到的数据
*函数入口：无
*函数出口：无
*****************************************************************************************/
void nRF905_ReadData()
{
	uchar i;
  	Clr_Bit(PORTB,CSN);	                   
	SPI_WR(RRP);				// Read payload command		
   	for (i=0;i<5;i++)
	{     
		RxdBuf[i]=SPI_WR(0x00);	// Read data and save to buffer
	}
	Set_Bit(PORTB,CSN); 
}
/****************************************************************************************
*函数名称：nRF905_ReceiveData(void)
*函数功能：接收数据
*函数入口：无
*函数出口：无
*****************************************************************************************/
void nRF905_ReceiveData(void)
{
	nRF905_RxOn();            //切换到接收模式
	nRF_Delay(650);		   	    //延时686us>650us,模式贴换	 
  if(AM == 0) return;       //一般先AM=1指示地址匹配对
  if(DR == 0) return;       //DR=1时表示数据接收对而且Crc正确
  TRX_CE = 0;               //进入待机状态
	nRF905_ReadData();			  //接收数据
}
