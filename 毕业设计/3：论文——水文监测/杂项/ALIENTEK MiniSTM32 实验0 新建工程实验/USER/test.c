#include "sys.h"
#include "usart.h"		
#include "delay.h"	 
#include "ds18b20.h"
#include "sensor.h"
#include "timer.h"
#include "csb.h"   
#include "dht11.h"
#include "led.h"
#include "24l01.h"
#include "rc522.h"

u8 tmp_buf[33];

int Temperature1,Temperature2,Candela;
u16 adcx;
u16 adcx1;
u32 Distance;  
u8 temperature;  	    
u8 humidity;  
u8 times;
unsigned char CT[2];//卡类型
unsigned char SN[4]; //卡号
unsigned char RFID[16];			//存放RFID 
unsigned char RFID1[16]={0x01,0x00,0x00,0x00,0x00,0x00,0xff,0x07,0x80,0x29,0xff,0xff,0xff,0xff,0xff,0xff};
u8 KEY[6]={0xff,0xff,0xff,0xff,0xff,0xff};

u8 set=0;
void date_read(void);
void Rc522_read(void);
int main(void)
{				 


//	u8 t;
	Stm32_Clock_Init(9);	//系统时钟设置
	delay_init(72);	  		//延时初始化
	uart_init(72,9600); 	//串口初始化为9600
	Adc_Init();
	LED_Init();
	TIM2_Cap_Init(0XFFFF,72-1);	
	TIM3_Int_Init(9999,7199);//10Khz的计数频率，100ms
	while(DHT11_Init())	//DHT11初始化	
	{;}	
	while(DS18B20_Init()) {;} //DS18B20初始化	
	NRF24L01_Init();    	//初始化NRF24L01 
 	while(NRF24L01_Check())	//检查NRF24L01是否在位.	
	{;}
		InitRc522();
	NRF24L01_TX_Mode();
  	while(1)
	{
			Rc522_read();	
		if(NRF24L01_TxPacket(tmp_buf)==TX_OK)
		{	
			date_read();

		}	
	
	}
}


void date_read(void)
{
	Read_Distane();	
	Temperature1=DS18B20_Get_Temp();

	adcx=Get_Adc_Average(ADC_CH1,10);    //TDS
	
	DHT11_Read_Data(&temperature,&humidity);
	
	tmp_buf[0]='D';
	tmp_buf[1]=48+temperature/10;  //环境温度
	tmp_buf[2]=48+temperature%10;
	tmp_buf[3]=48+humidity/10;     //环境湿度
	tmp_buf[4]=48+humidity%10;
	tmp_buf[5]=48+adcx/1000;     //TDS
	tmp_buf[6]=48+(adcx%1000)/100;
	tmp_buf[7]=48+(adcx%100)/10;
	tmp_buf[8]=48+adcx%10;
	tmp_buf[9]=48+Distance/100;  //距离
	tmp_buf[10]=48+(Distance%100)/10;
	tmp_buf[11]=48+Distance%10;
	tmp_buf[12]=48+Temperature1/100;  //水温
	tmp_buf[13]=48+(Temperature1%100)/10;
	tmp_buf[14]=48+Temperature1%10;

	if(YD==0)   //下雨
	{
		tmp_buf[15]=48+0;
	}
	else
	{
		tmp_buf[15]=48+1;
	}
	
//		tmp_buf[16]=48+set; 
	tmp_buf[17]=48+SN[0]/100;
	tmp_buf[18]=48+(SN[0]%100)/10;
	tmp_buf[19]=48+SN[0]%10;
	tmp_buf[20]=48+SN[1]/100;
	tmp_buf[21]=48+(SN[1]%100)/10;
	tmp_buf[22]=48+SN[1]%10;
	tmp_buf[23]=48+SN[2]/100;
	tmp_buf[24]=48+(SN[2]%100)/10;
	tmp_buf[25]=48+SN[2]%10;
	tmp_buf[26]=48+SN[3]/100;
	tmp_buf[27]=48+(SN[3]%100)/10;
	tmp_buf[28]=48+SN[3]%10;
	tmp_buf[29]=48+SN[3]%10;
	
	tmp_buf[32]=0; 
	
}
void Rc522_read(void)
{
		unsigned char status;
		status = PcdRequest(PICC_REQALL,CT);/*尋卡*/
		if(status==MI_OK)//尋卡成功
		{
			 status=MI_ERR;
			 status = PcdAnticoll(SN);/*防冲撞*/
		 
		}	
		
		if(status==MI_OK)
		{
			status=MI_ERR;
			status =PcdSelect(SN);
		}

		if(status==MI_OK)//選卡成功
		{
			 status=MI_ERR;
			 status =PcdAuthState(0x61,0x06,KEY,SN);
		 }
		if(status==MI_OK)//驗證成功
		 {
			  status=MI_ERR;
			 delay_ms(200);
		  }

}


