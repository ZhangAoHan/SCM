#include "24l01.h"
#include "delay.h"
#include "spi.h"
#include "ezio.h"





/*************************** 文件说明 *******************************/
//NRF24L01+ 驱动代码
//此程序适用于七彩光子太极M3—STM32F103开发板及部分兼容的STM32系统，
//淘宝搜索"七彩光子 太极M3 STM32开发板"购买超高性价比开发板或获取更多资料
//只供学习使用，未经作者许可，不得用于其它任何用途！
/********************************************************************/  



//版本说明
/*
 V0.001
 2018.06.21   15:27 初始版本

*/








//-----------------------IO 口定义-----------------------------------
//NRF24L01_CE
#define NRF24L01_CE_IO   PG8
#define NRF24L01_CE_PORT GPIOG
#define NRF24L01_CE_PIN  GPIO_Pin_8

//NRF24L01_CS
#define NRF24L01_CS_IO    PG7
#define NRF24L01_CS_PORT  GPIOG
#define NRF24L01_CS_PIN   GPIO_Pin_7

//NRF24L01_IRQ
#define NRF24L01_IQR_IO    PG6
#define NRF24L01_IQR_PORT  GPIOG
#define NRF24L01_IQR_PIN   GPIO_Pin_6


//-----------------   IO 操作定义  -------------------------------------
#define NRF24L01_CS_L() (NRF24L01_CS_PORT->BRR=NRF24L01_CS_PIN)
#define NRF24L01_CS_H() (NRF24L01_CS_PORT->BSRR=NRF24L01_CS_PIN)

#define NRF24L01_CE_L()  (NRF24L01_CE_PORT->BRR=NRF24L01_CE_PIN)
#define NRF24L01_CE_H()  (NRF24L01_CE_PORT->BSRR=NRF24L01_CE_PIN)

#define NRF24L01_IQR_READ()   (((NRF24L01_IQR_PORT->IDR&NRF24L01_IQR_PIN)==0)?(0):(1))

			   	   
//-----------------------   SPI 接口函数嫁接  ------------------------

#define NRF24L01_SPI_Init()     SPI2_Init()
#define NRF24L01_Read_Byte()    SPI2_ReadWriteByte(0xFF)
#define NRF24L01_Write_Byte(x)  SPI2_ReadWriteByte(x)
#define NRF24L01_RW_Byte(x)     SPI2_ReadWriteByte(x)
#define NRF24L01_SPI_SetSpeed_10M()     SPI2_SetSpeed(SPI_BaudRatePrescaler_16) //SPI速度设置,这里设置为小于10M





const u8 NRF_TX_ADDRESS[TX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x02}; //发送地址,对方的接收地址
const u8 NRF_RX_ADDRESS[RX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x02}; //接收地址,对方的发送地址





//初始化24L01的IO口
void NRF24L01_Init(void)
{ 
	Pin_ModeSet(NRF24L01_CS_IO,OUTPUT_PP|OUT_H);     //CS 引脚初始化
	Pin_ModeSet(NRF24L01_CE_IO,OUTPUT_PP|OUT_L);  //CE 引脚初始化
	Pin_ModeSet(NRF24L01_IQR_IO,INPUT_PU);           //IQR 中断引脚初始化
	

	NRF24L01_SPI_Init();
	NRF24L01_SPI_SetSpeed_10M();
	SPI_Cmd(SPI2,ENABLE);

	
	delay_ms(10);
	
	NRF24L01_CE_L(); 			//使能24L01
	NRF24L01_Write_Buf(NRF_WRITE_REG+RX_ADDR_P0,(u8*)NRF_RX_ADDRESS,RX_ADR_WIDTH);	//写RX节点地址 
	NRF24L01_Write_Buf(NRF_WRITE_REG+TX_ADDR,(u8*)NRF_TX_ADDRESS,TX_ADR_WIDTH); 		//写TX节点地址  
	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_AA,0x01); 													//使能通道0的自动应答 
	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_RXADDR,0x01);											//使能通道0的接收地址 
	NRF24L01_Write_Reg(NRF_WRITE_REG+SETUP_RETR,0x1a);											//设置自动重发间隔时间:500us;最大自动重发次数:10次 
	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_CH,40);														//设置RF通道为CHANAL
	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_SETUP,0x0f); 												//设置TX发射参数,0db增益,2Mbps,低噪声增益开启
	NRF24L01_Write_Reg(NRF_WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);								//选择通道0的有效数据宽度 
	NRF24L01_Write_Reg(NRF_WRITE_REG + CONFIG, 0x0f);   		 // IRQ收发完成中断开启,16位CRC,主接收
	NRF24L01_CE_H();
	
}
//检测24L01是否存在
//返回值:0，成功;1，失败	
u8 NRF24L01_Check(void)
{
	u8 buf[5]={0XA5,0XA5,0XA5,0XA5,0XA5};
	u8 i;
	//NRF24L01_CE_L();
	NRF24L01_Write_Buf(NRF_WRITE_REG+TX_ADDR,buf,5);//写入5个字节的地址.	
	NRF24L01_Read_Buf(TX_ADDR,buf,5); //读出写入的地址  
	//NRF24L01_CE_H();
	for(i=0;i<5;i++){
		if(buf[i]!=0XA5){
			return 1;//检测24L01错误	
		}
	}
	return 0;		 //检测到24L01
}	 	 
//SPI写寄存器
//reg:指定寄存器地址
//value:写入的值
u8 NRF24L01_Write_Reg(u8 reg,u8 value)
{
	u8 status;	
   	NRF24L01_CS_L();                 //使能SPI传输
  	status =NRF24L01_RW_Byte(reg);//发送寄存器号 
  	NRF24L01_RW_Byte(value);      //写入寄存器的值
  	NRF24L01_CS_H();                 //禁止SPI传输	   
  	return(status);       			//返回状态值
}
//读取SPI寄存器值
//reg:要读的寄存器
u8 NRF24L01_Read_Reg(u8 reg)
{
	u8 reg_val;	    
 	NRF24L01_CS_L();          //使能SPI传输		
  NRF24L01_RW_Byte(reg);   //发送寄存器号
  reg_val=NRF24L01_RW_Byte(0XFF);//读取寄存器内容
	reg_val=NRF24L01_Read_Byte();//读取寄存器内容
  NRF24L01_CS_H();          //禁止SPI传输		    
  return(reg_val);           //返回状态值
}	

//在指定位置读出指定长度的数据
//reg:寄存器(位置)
//*pBuf:数据指针
//len:数据长度
//返回值,此次读到的状态寄存器值 
u8 NRF24L01_Read_Buf(u8 reg,u8 *pBuf,u8 len)
{
	u8 status,u8_ctr;	       
	NRF24L01_CS_L();           //使能SPI传输
	status=NRF24L01_RW_Byte(reg);//发送寄存器值(位置),并读取状态值   	   
	for(u8_ctr=0;u8_ctr<len;u8_ctr++)
		pBuf[u8_ctr]=NRF24L01_RW_Byte(0XFF);//读出数据
	NRF24L01_CS_H();       //关闭SPI传输
	return status;        //返回读到的状态值
}
//在指定位置写指定长度的数据
//reg:寄存器(位置)
//*pBuf:数据指针
//len:数据长度
//返回值,此次读到的状态寄存器值
u8 NRF24L01_Write_Buf(u8 reg, u8 *pBuf, u8 len)
{
	u8 status,u8_ctr;	    
 	NRF24L01_CS_L();          //使能SPI传输
  	status = NRF24L01_RW_Byte(reg);//发送寄存器值(位置),并读取状态值
  	for(u8_ctr=0; u8_ctr<len; u8_ctr++)NRF24L01_RW_Byte(*pBuf++); //写入数据	 
  	NRF24L01_CS_H();       //关闭SPI传输
  	return status;          //返回读到的状态值
}


//启动NRF24L01发送一次数据
//txbuf:待发送数据首地址
//返回值:发送完成状况
u8 NRF24L01_TxPacket(u8 *txbuf)
{
	u8 sta;   
	SPI2_SetSpeed(SPI_BaudRatePrescaler_8);
	NRF24L01_CE_L();
  	NRF24L01_Write_Buf(WR_TX_PLOAD,txbuf,TX_PLOAD_WIDTH);//写数据到TX BUF  32个字节
 	NRF24L01_CE_H();//启动发送
	while(NRF24L01_IQR_READ()!=0);//等待发送完成
	sta=NRF24L01_Read_Reg(STATUS);  //读取状态寄存器的值	   
	NRF24L01_Write_Reg(NRF_WRITE_REG+STATUS,sta); //清除TX_DS或MAX_RT中断标志
	if(sta&MAX_TX){//达到最大重发次数
		NRF24L01_Write_Reg(FLUSH_TX,0xff);//清除TX FIFO寄存器 
		return MAX_TX; 
	}
	if(sta&TX_OK)//发送完成
	{
		return TX_OK;
	}
	return 0xff;//其他原因发送失败
}
//启动NRF24L01发送一次数据
//txbuf:待发送数据首地址
//返回值:0，接收完成；其他，错误代码
u8 NRF24L01_RxPacket(u8 *rxbuf)
{
	u8 sta;
	if(NRF24L01_IQR_READ()==0){
		sta=NRF24L01_Read_Reg(STATUS);  //读取状态寄存器的值    	 
		NRF24L01_Write_Reg(NRF_WRITE_REG+STATUS,sta); //清除TX_DS或MAX_RT中断标志
		if(sta&RX_OK){//接收到数据
			NRF24L01_Read_Buf(RD_RX_PLOAD,rxbuf,RX_PLOAD_WIDTH);//读取数据
			NRF24L01_Write_Reg(FLUSH_RX,0xff);//清除RX FIFO寄存器 
			return 0; 
		}
	}
	return 1;//没收到任何数据
}


//NRF24L01 模式切换
void NRF24L01_Set_Mode(u8 model)
{
	NRF24L01_CE_L();
	if(model==NRF_MODEL_RX){				//RX
		NRF24L01_Write_Reg(NRF_WRITE_REG + CONFIG, 0x0f);   		 // IRQ收发完成中断开启,16位CRC,主接收
	}
	else if(model==NRF_MODEL_TX){		//TX
		NRF24L01_Write_Reg(NRF_WRITE_REG + CONFIG, 0x0e);   		 // IRQ收发完成中断开启,16位CRC,主发送
	}
	NRF24L01_CE_H();
}

































