#ifndef __DATE_H
#define __DATE_H	
#include "sys.h"

#define JDQ PAout(0)						  	 	    
#define ADC_CH1  1  	//通道1		 
#define DHT11_IO_IN()  {GPIOC->CRH&=0X0FFFFFFF;GPIOC->CRH|=8<<28;}
#define DHT11_IO_OUT() {GPIOC->CRH&=0X0FFFFFFF;GPIOC->CRH|=3<<28;}
	////IO操作函数											   
#define	DHT11_DQ_OUT PCout(15) //数据端口	PG11 
#define	DHT11_DQ_IN  PCin(15)  //数据端口	PG11   									   
void Adc_Init(void); 				//ADC通道初始化
u16  Get_Adc(u8 ch); 				//获得某个通道值 
u16 Get_Adc_Average(u8 ch,u8 times);//得到某个通道10次采样的平均值 
u8 DHT11_Init(void);		//初始化DHT11
u8 DHT11_Read_Data(u8 *temp,u8 *humi);//读取温湿度
u8 DHT11_Read_Byte(void);	//读出一个字节
u8 DHT11_Read_Bit(void);	//读出一个位
u8 DHT11_Check(void);		//检测是否存在DHT11
void DHT11_Rst(void);		//复位DHT11 
void Io_In_Out(void);
#endif 

