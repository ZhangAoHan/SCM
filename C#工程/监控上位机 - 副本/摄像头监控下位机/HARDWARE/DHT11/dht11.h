#ifndef __DHT11_H
#define __DHT11_H	
#include "sys.h"
#define ADC_CH1  1  	//通道1		 	    
//IO方向设置
#define DHT11_IO_IN()  {GPIOA->CRL&=0XFFFFF0FF;GPIOA->CRL|=0X00000800;}
#define DHT11_IO_OUT() {GPIOA->CRL&=0XFFFFF0FF;GPIOA->CRL|=0X00000300;}
//IO操作函数                                                                              
#define    DHT11_DQ_OUT PAout(2) //数据端口    
#define    DHT11_DQ_IN  PAin(2)  //数据端口      									   
void Adc_Init(void); 				//ADC通道初始化
u16  Get_Adc(u8 ch); 				//获得某个通道值 
u16 Get_Adc_Average(u8 ch,u8 times);//得到某个通道10次采样的平均值 

void DHT11_Init(void);           //初始化DHT11
u8 DHT11_Read_Data(u8 *temp,u8 *humi);//读取温湿度
u8 DHT11_Read_Byte(void); //读出一个字节
u8 DHT11_Read_Bit(void);   //读出一个位
u8 DHT11_Check(void);       //检测是否存在DHT11
void DHT11_Rst(void);         //复位DHT11   
#endif 





