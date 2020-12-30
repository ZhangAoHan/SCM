#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"	
#include "oled.h"
#include "csb.h" 
#include "dht11.h"
#include "adc.h"
#include "rc522.h"
#include "ds18b20.h"   
#include "24l01.h"

u32 Distance;  
float m1,m2;
u8 temperature;  	    
u8 humidity;  	
u16 adcx;
short temperature1; 
unsigned char CT[2];//������
unsigned char SN[4]; //����
unsigned char RFID[16];			//���RFID 
unsigned char RFID1[16]={0x01,0x00,0x00,0x00,0x00,0x00,0xff,0x07,0x80,0x29,0xff,0xff,0xff,0xff,0xff,0xff};
u8 KEY[6]={0xff,0xff,0xff,0xff,0xff,0xff};
u8 tmp_buf[33]; 

void Display(void);
void date_read(void);
void Rc522_read(void);
 int main(void)
 {	
	delay_init(72);	    	 //��ʱ������ʼ��	 
	uart_init(72,9600); 	//���ڳ�ʼ��Ϊ9600	   
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
	 KEY_Init(); 
	OLED_Init();

	 TIM3_Cap_Init(0XFFFF,72-1);	
	 InitRc522();
	 while(DHT11_Init())	//DHT11��ʼ��	
	{;}	
	while(DS18B20_Init())//DS18B20��ʼ��	
	{;}

		NRF24L01_Init();    	//��ʼ��NRF24L01  
	while(NRF24L01_Check())	//���NRF24L01�Ƿ���λ.	
	{;}		
		OLED_Clear();
	Adc_Init();
	NRF24L01_TX_Mode();	
		//�̶���ʾ
		OLED_ShowString(0,0,"ID:",16);    
	
	OLED_ShowCHinese(0,2,0);  //����
	OLED_ShowCHinese(16,2,1);
	OLED_ShowChar(32,2,':',16);
	OLED_ShowChar(56,2,'.',16);
	OLED_ShowString(72,2,"CM",16);
	
	OLED_ShowCHinese(104,2,7);  //��
	
	OLED_ShowCHinese(0,4,2);   //qiwen
	OLED_ShowCHinese(16,4,3); 
	OLED_ShowChar(32,4,':',16);
	OLED_ShowCHinese(60,4,4);   //qiwen
	OLED_ShowCHinese(76,4,5); 
	OLED_ShowChar(92,4,':',16);
	
	OLED_ShowString(0,6,"TDS:",16);
	OLED_ShowCHinese(56,6,9);   //qiwen
	OLED_ShowCHinese(72,6,3); 
	OLED_ShowChar(88,6,':',16);		
	OLED_ShowChar(112,6,'.',16);
	while(1)
	{
		if(NRF24L01_TxPacket(tmp_buf)==TX_OK)
		{
			date_read();
			Display();	
			Rc522_read();	
		}	
	}

 }

void Display()
{
	
	OLED_ShowNum(40,2,m1,2,16);
	OLED_ShowNum(64,2,m2,1,16);
	
	if(ZD==0) OLED_ShowCHinese(88,2,6);     //��
	else OLED_ShowCHinese(88,2,8); 
	
	OLED_ShowNum(40,4,temperature,2,16);
	OLED_ShowNum(100,4,humidity,2,16);
	
	OLED_ShowNum(32,6,adcx,3,16);
	OLED_ShowNum(96,6,temperature1/10,2,16);
	OLED_ShowNum(120,6,temperature1%10,1,16);
}

void date_read(void)
{
	Read_Distane();	 
		
	m1=Distance/10;
	m2=Distance%10;
	adcx=Get_Adc_Average(ADC_CH2,5);
	temperature1=DS18B20_Get_Temp();		
	DHT11_Read_Data(&temperature,&humidity);	
	
	tmp_buf[0]='D';
	
	tmp_buf[1]=48+temperature/10;  //DHT11
	tmp_buf[2]=48+temperature%10;
	
	tmp_buf[3]=48+humidity/10;
	tmp_buf[4]=48+humidity%10;
	
	tmp_buf[5]=48+adcx/100;     //TDS
	tmp_buf[6]=48+(adcx%100)/10;
	tmp_buf[7]=48+adcx%10;
	
	tmp_buf[8]=48+temperature1/100;  //DS18B20
	tmp_buf[9]=48+(temperature1%100)/10;
	tmp_buf[10]=48+temperature1%10;
	
	tmp_buf[11]=48+(int)m1/10;
	tmp_buf[12]=48+(int)m1%10;
	tmp_buf[13]=48+(int)m2;
	if(ZD==0) tmp_buf[14]=48+1;    //��
	else tmp_buf[14]=48+0;  
	
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
		u8 t;
		status = PcdRequest(PICC_REQALL,CT);/*����*/
		if(status==MI_OK)//�����ɹ�
		{
			 status=MI_ERR;
			 status = PcdAnticoll(SN);/*����ײ*/
		 
		}	
		
		if(status==MI_OK)
		{
			status=MI_ERR;
			status =PcdSelect(SN);
		}

		if(status==MI_OK)//�x���ɹ�
		{
			 status=MI_ERR;
			 status =PcdAuthState(0x61,0x06,KEY,SN);
		 }
		if(status==MI_OK)//��C�ɹ�
		 {
			  status=MI_ERR;
			 for(t=0;t<4;t++)
			 {
				 OLED_ShowNum(24+24*t,0,SN[t],3,16);
			 }
			 			
			
		  }

}



