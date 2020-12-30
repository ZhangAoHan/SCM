#ifndef __ADC_DHT11_H
#define __ADC_DHT11_H
#include "delay.h"	
#include "sys.h"
//IO方向设置
#define DHT11_IO_IN()  {GPIOG->CRH&=0XFFFF0FFF;GPIOG->CRH|=8<<12;}
#define DHT11_IO_OUT() {GPIOG->CRH&=0XFFFF0FFF;GPIOG->CRH|=3<<12;}
////IO操作函数											   
#define	DHT11_DQ_OUT PGout(11) //数据端口	PG11 
#define	DHT11_DQ_IN  PGin(11)  //数据端口	PG11

#define ADC_CH1  1  				//通道1(连接在PA1)	 	    

void  Adc_Init(void);
u16 Get_Adc(u8 ch);
u16 Get_Adc_Average(u8 ch,u8 times);

u8 DHT11_Init(void);		//初始化DHT11
u8 DHT11_Read_Data(u8 *temp,u8 *humi);//读取温湿度
u8 DHT11_Read_Byte(void);	//读出一个字节
u8 DHT11_Read_Bit(void);	//读出一个位
u8 DHT11_Check(void);		//检测是否存在DHT11
void DHT11_Rst(void);		//复位DHT11    


#endif

