#include "control.h"
#include "24l01.h"
#include "rc522.h"
#include "timer.h"
#include "led.h"
	extern u8 temperature;  	    
	extern u8 humidity; 
	extern u16 adcx;
	extern u16 adcx1;  //光敏
	extern u16 adcx2;    //MQ3	
	extern unsigned char CT[2];//卡类型

extern unsigned char SN[4]; //卡号
extern u8 KEY[6];
extern u8 set;
extern u8 settle;
extern u8 door;
void Nrf_communicate(void)
{				    	
		NRF24L01_TX_Mode();	   		
while(1)
{

		if(NRF24L01_TxPacket(tmp_buf)==TX_OK)
		{
		date_read();	
		}	
	if(adcx2>430)  //烟雾超标
	{
		FS_JDQ=0;
		LED_RED=1;
		LED_GREEN=0;
	}
	else 
	{
		FS_JDQ=1;
				LED_RED=0;
		LED_GREEN=1;
	}
	PWM_VAL=(4095-adcx1)*2;
	
}	



					    	
}

void user_control(void)
{
	Nrf_communicate();

}

void date_read(void)
{	
//	u8 t;
	tmp_buf[0]='D';
	tmp_buf[1]=48+temperature/10;
	tmp_buf[2]=48+temperature%10;
	tmp_buf[3]=48+humidity/10;
	tmp_buf[4]=48+humidity%10;
	tmp_buf[5]=48+adcx/1000;     //土壤
	tmp_buf[6]=48+(adcx%1000)/100;
	tmp_buf[7]=48+(adcx%100)/10;
	tmp_buf[8]=48+adcx%10;
	tmp_buf[9]=48+adcx1/1000;  //光强
	tmp_buf[10]=48+(adcx1%1000)/100;
	tmp_buf[11]=48+(adcx1%100)/10;
	tmp_buf[12]=48+adcx1%10;
	tmp_buf[13]=48+adcx2/1000;  //烟雾
	tmp_buf[14]=48+(adcx2%1000)/100;
	tmp_buf[15]=48+(adcx2%100)/10;
	tmp_buf[16]=48+adcx2%10;
		if(set==0)
	{
		tmp_buf[17]=48;
		tmp_buf[18]=48;
		tmp_buf[19]=48;
							tmp_buf[20]=48;
		tmp_buf[21]=48;
		tmp_buf[22]=48;
						tmp_buf[23]=48;
		tmp_buf[24]=48;
		tmp_buf[25]=48;
						tmp_buf[26]=48;
		tmp_buf[27]=48;
		tmp_buf[28]=48;
	}
	else
	{
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
	}
	tmp_buf[30]=48+settle;
	tmp_buf[31]=48+set;

	
}

void Rc522_read(void)
{
		unsigned char status;
		u8 t;
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
			  for(t=0;t<4;t++)
			  {
					//rc522
					door=1;
				//	LCD_ShowNum(0,116+t*16,SN[t],3,16);
				  set=1;
			  }
		  }

}

