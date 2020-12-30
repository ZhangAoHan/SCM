#include "control.h"
#include "24l01.h"
#include "text.h"
#include "timer.h"
u8 temp[2]; 
//unsigned char ID[12];
extern u8 temperature;  	    
extern u8 humidity; 
extern u16 adc_mq2;
extern u16 adc_gm;
extern u16 adc_tr;
extern unsigned char SN[4]; //卡号
unsigned char NOW_SN[4]; //卡号
extern u8 page;
unsigned char Mr_L_SN[4]={117,173,237,44}; 
unsigned char Mr_Z_SN[4]={243,135,161,181}; 
unsigned char Mr_W_SN[4]={170,243,180,213}; 
extern u16 t1;
extern u16 t2;
extern u16 t3;
extern u16 time1;
extern u16 time2;
extern u16 time3;
void Nrf_communicate(void)
{
	u8 t;
		if(NRF24L01_RxPacket(tmp_buf)==0)//一旦接收到信息,则显示出来.
	{
//		tmp_buf[32]=0;//加入字符串结束符
		for(t=1;t<31;t++)
		{
			tmp_buf[t]=tmp_buf[t]-48;
		}
		//LCD_ShowString(0,230,239,32,16,tmp_buf);  
		temperature=tmp_buf[1]*10+tmp_buf[2];
		humidity=tmp_buf[3]*10+tmp_buf[4];
		adc_tr=tmp_buf[5]*1000+tmp_buf[6]*100+tmp_buf[7]*10+tmp_buf[8];
		adc_gm=tmp_buf[9]*1000+tmp_buf[10]*100+tmp_buf[11]*10+tmp_buf[12];
		adc_mq2=tmp_buf[13]*1000+tmp_buf[14]*100+tmp_buf[15]*10+tmp_buf[16];
//		for(t=0;t<12;t++)
//		{
//		ID[t]=tmp_buf[17+t];
//		}
		
		SN[0]=tmp_buf[17]*100+tmp_buf[18]*10+tmp_buf[19];
		SN[1]=tmp_buf[20]*100+tmp_buf[21]*10+tmp_buf[22];
		SN[2]=tmp_buf[23]*100+tmp_buf[24]*10+tmp_buf[25];
		SN[3]=tmp_buf[26]*100+tmp_buf[27]*10+tmp_buf[28];
		if(tmp_buf[30]==1)
		{
			for(t=0;t<4;t++)
			{
				NOW_SN[t]=SN[t];
			}
			if(Mr_Z_SN[0]==SN[0]&&Mr_Z_SN[1]==SN[1]&&Mr_Z_SN[2]==SN[2]&&Mr_Z_SN[3]==SN[3]&&t1==0) t1=1;
			if(Mr_W_SN[0]==SN[0]&&Mr_W_SN[1]==SN[1]&&Mr_W_SN[2]==SN[2]&&Mr_W_SN[3]==SN[3]&&t2==0) t2=1;
			if(Mr_L_SN[0]==SN[0]&&Mr_L_SN[1]==SN[1]&&Mr_L_SN[2]==SN[2]&&Mr_L_SN[3]==SN[3]&&t3==0) t3=1;
		}

	}	 			    	
}

void user_control(void)
{
	Nrf_communicate();
	if(tmp_buf[0]=='D')
	{
		//date_display();
		if(page==0)
		{
			DL_display();
			use_touch();
		}
		else if(page==1)
		{
			page_1();
			use_touch();
		}
		else if(page==2)
		{
			page_2();
			use_touch();
		}
	}
	PWM=adc_gm*2;
	if(adc_tr>3500||adc_mq2>430)
	{
		LED_RED=1;
		LED_BLUE=0;
		LED_GREEN=0;
	}
	else
	{
		LED_RED=0;
		LED_BLUE=0;
		LED_GREEN=1;
	}


	
	
}

void date_display(u8 y)      //数据显示
{ 

		POINT_COLOR=RED;
		LCD_DrawRectangle(5,y,235,y+121);
		LCD_DrawRectangle(4,y-1,236,y+122);
		POINT_COLOR=BLACK;
		Show_Str(6,y+1,120,24,"环境温度：",24,0);
		Show_Str(6,y+25,120,24,"环境湿度：",24,0);
		Show_Str(6,y+49,120,24,"环境光强：",24,0);
		Show_Str(6,y+73,120,24,"MQ2浓度：",24,0);
		Show_Str(6,y+97,120,24,"土壤湿度：",24,0);
		POINT_COLOR=BLACK;
		LCD_ShowNum(130,y+5,temperature,2,16);	
		LCD_ShowNum(130,y+29,humidity,2,16);	
		LCD_ShowNum(130,y+53,adc_gm,4,16);		
		LCD_ShowNum(130,y+77,adc_mq2,4,16);		
		LCD_ShowNum(130,y+101,adc_tr,4,16);
	
}

void DL_display(void)           //page=0
{
	POINT_COLOR=BLUE;
	Show_Str(72,10,96,24,"管理系统",24,0);
	POINT_COLOR=RED;
	Show_Str(60,100,120,24,"签到信息",24,0);
	Show_Str(60,150,144,24,"环境数据信息",24,0);
//	Show_Str(60,150,96,24,"环境数据信息",24,0);
}

void page_1(void)             //签到信息界面
{
	u8 t;
	POINT_COLOR=BLUE;
	Show_Str(72,10,96,24,"管理系统",24,0);
	POINT_COLOR=RED;
	Show_Str(180,290,48,24,"返回",24,0);

	
	POINT_COLOR=BLUE;
	Show_Str(17,50,48,24,"姓名",24,0);
	Show_Str(120,50,120,24,"已工作时间",24,0);
	POINT_COLOR=BLACK;
	Show_Str(10,80,72,24,"张某某",24,0);
	Show_Str(10,110,80,24,"张ID：",24,0);
	Show_Str(10,140,72,24,"王某某",24,0);
	Show_Str(10,170,80,24,"王ID:",24,0);
	Show_Str(10,200,72,24,"李某某",24,0);
	Show_Str(10,230,80,24,"李ID:",24,0);
	for(t=0;t<4;t++)
	{	
		LCD_ShowNum(90+35*t,114,Mr_Z_SN[t],3,16);
		LCD_ShowNum(90+35*t,174,Mr_W_SN[t],3,16);
		LCD_ShowNum(90+35*t,234,Mr_L_SN[t],3,16);
	}
	
	
	LCD_ShowNum(120,84,(time1/60)/24,2,16);
	LCD_ShowNum(150,84,(time1/60)%24,2,16);
	LCD_ShowNum(180,84,time1%60,2,16);
	LCD_ShowNum(120,144,(time2/60)/24,2,16);
	LCD_ShowNum(150,144,(time2/60)%24,2,16);
	LCD_ShowNum(180,144,time2%60,2,16);
	LCD_ShowNum(120,204,(time3/60)/24,2,16);
	LCD_ShowNum(150,204,(time3/60)%24,2,16);
	LCD_ShowNum(180,204,time3%60,2,16);

	for(t=0;t<3;t++)
	{
		LCD_ShowChar(140,84+t*60,'H',16,0);
		LCD_ShowChar(170,84+t*60,'M',16,0);
		LCD_ShowChar(200,84+t*60,'S',16,0);
	}

	
	
}
void page_2(void)             //信息显示
{
	
	POINT_COLOR=BLUE;
	Show_Str(72,10,96,24,"管理系统",24,0);
	POINT_COLOR=RED;
	Show_Str(180,290,48,24,"返回",24,0);
	POINT_COLOR=BLACK;
	Show_Str(10,50,120,24,"传感器分组",24,0);
	if(tmp_buf[29]==1) Show_Str(150,50,48,24,"A组",24,0);
	else Show_Str(150,50,48,24,"B组",24,0);
	date_display(80);
	
}

void use_touch(void)
{
	//u8 i;
	tp_dev.scan(0); 
	if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
	{
		if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
		{
			if(page==0)
			{
				if(tp_dev.x[0]>60&&tp_dev.x[0]<180&&tp_dev.y[0]>100&&tp_dev.y[0]<130)
				{
					page=1;
					LCD_Clear(WHITE);
					delay_ms(100);
				}
				if(tp_dev.x[0]>60&&tp_dev.x[0]<204&&tp_dev.y[0]>150&&tp_dev.y[0]<180)
				{
					page=2;
					LCD_Clear(WHITE);
					delay_ms(100);
				}
			}
			else if(page==1)
			{
			if(tp_dev.x[0]>180&&tp_dev.x[0]<240&&tp_dev.y[0]>290&&tp_dev.y[0]<320)
			{
					page=0;
					LCD_Clear(WHITE);
					delay_ms(100);
			}
			}
			else if(page==2)
			{
			if(tp_dev.x[0]>190&&tp_dev.x[0]<240&&tp_dev.y[0]>290&&tp_dev.y[0]<320)
			{
					page=0;
					NOW_SN[0]=NOW_SN[1]=NOW_SN[2]=NOW_SN[3]=0;
					LCD_Clear(WHITE);
					delay_ms(100);
			}
			}
			
		}
	}
}

void LED_Init(void)
{
	RCC->APB2ENR|=1<<4;    //使能PORTa时钟	   	 
	   	 
	GPIOC->CRL&=0XFFFFF000; 
	GPIOC->CRL|=0X00000333;   	 
    GPIOC->ODR|=0<<0;      //PB.5 输出高
	GPIOC->ODR|=0<<1;      //PB.5 输出高
	GPIOC->ODR|=0<<2;      //PB.5 输出高
											
}



