#ifndef __DS18B202_H
#define __DS18B202_H 
#include "sys.h"   

//IO方向设置
#define DS18B202_IO_IN()  {GPIOB->CRH&=0XFFFFF0FF;GPIOB->CRH|=8<<8;}
#define DS18B202_IO_OUT() {GPIOB->CRH&=0XFFFFF0FF;GPIOB->CRH|=3<<8;}
////IO操作函数											   
#define	DS18B202_DQ_OUT PBout(10) //数据端口	PA0
#define	DS18B202_DQ_IN  PBin(10)  //数据端口	PA0 
   	
u8 DS18B202_Init(void);			//初始化DS18B20
short DS18B202_Get_Temp(void);	//获取温度
void DS18B202_Start(void);		//开始温度转换
void DS18B202_Write_Byte(u8 dat);//写入一个字节
u8 DS18B202_Read_Byte(void);		//读出一个字节
u8 DS18B202_Read_Bit(void);		//读出一个位
u8 DS18B202_Check(void);			//检测是否存在DS18B20
void DS18B202_Rst(void);			//复位DS18B20    
#endif















