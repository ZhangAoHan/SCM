#include "control.h"
#include "lcd.h"
#include "touch.h"  
#include "w25q128.h"  
#include "text.h"
#include "ds18b20.h"   
#include "rc522.h"
#include "timer.h"
#include "adc.h"
#include "led.h"
#include "key.h"
extern u8 n;
extern u8 page;
u8 num=3;
short temperature; 
u16 adcx;
unsigned char CT[2];//卡类型
unsigned char SN[4]; //卡号
u8 KEY[6]={0xff,0xff,0xff,0xff,0xff,0xff};
extern unsigned char card_1[4];
extern unsigned char card_2[4];
extern unsigned char card_3[4];
u8 seat1=0,seat2=0,seat3=0,seat=0;
//  LCD初始化显示
void LCD_init_display(void)
{

	while(font_init()) 			//检查字库
	{
		;
	}
	POINT_COLOR=BLUE;
	Show_Str(48,5,240,24,"车位检测系统",24,0);
	POINT_COLOR=BLACK;
	Show_Str(48,35,240,24,"检测系统",24,0);
	delay_ms(3000);
	LCD_Fill(5,65,240,24,WHITE);
	POINT_COLOR=BLUE;
	Show_Str(48,5,240,24,"车位检测系统",24,0);
	POINT_COLOR=BLACK;
	Show_Str(48,35,240,24,"系统正常",24,0);
	Show_Str(5,65,240,24,"TFT屏字库正常",24,0);	
	while(DS18B20_Init())	//DS18B20初始化	
	{
		Show_Str(5,65,240,24,"检测DS18B20传感器",24,0);
		delay_ms(200);
		LCD_Fill(5,65,240,24,WHITE);
 		delay_ms(200);
	}	
	POINT_COLOR=BLACK;
	Show_Str(5,95,240,24,"DS18B20传感器正常",24,0);
	Show_Str(5,125,240,24,"TFT屏触摸功能正常",24,0);
	Show_Str(5,155,240,24,"雨滴检测传感器正常",24,0);
	Show_Str(5,185,240,24,"红外检测传感器正常",24,0);
	Show_Str(5,215,240,24,"振动检测传感器正常",24,0);
	Show_Str(5,245,240,24,"RFID读写卡功能正常",24,0);
	Show_Str(5,275,240,24,"模拟门杆功能正常",24,0);
	delay_ms(5000);
	LCD_Clear(WHITE);
}

void LCD_page0_display(void)   //主页面设计  (被调用的函数)
{
	num=3;
	POINT_COLOR=BLUE;
	Show_Str(48,5,240,24,"车位检测系统",24,0);
	POINT_COLOR=BLACK;
	Show_Str(5,35,108,24,"环境温度：",24,0);
	
	POINT_COLOR=BLACK;
	temp();                 //读取温度
	LCD_ShowNum(120,39,temperature/10,2,16);
	LCD_ShowString(155,39,8,16,16,".");
	LCD_ShowNum(165,39,temperature%10,1,16);
	
	Show_Str(5,65,108,24,"是否下雨：",24,0);
	adcx=Get_Adc_Average(ADC_CH1,5);
		if(adcx>4000)
	{
		LCD_Fill(120,65,96,24,WHITE);
		Show_Str(120,65,48,24,"无雨",24,0);
	}
		else if(adcx<4000)
	{
		LCD_Fill(120,65,96,24,WHITE);
		Show_Str(120,65,48,24,"有雨",24,0);
	}
	
	Show_Str(5,95,108,24,"地面振动：",24,0);
			if(ZD==0)
	{
		Show_Str(120,95,72,24,"有震动",24,0);
	}
		else if(ZD==1)
	{
		Show_Str(120,95,72,24,"无振动",24,0);
	}
	
	Show_Str(5,125,144,24,"剩余停车位：",24,0);
	if(seat1==1) num=num-1;
	if(seat2==1) num=num-1;
	if(seat3==1) num=num-1;
	LCD_ShowNum(155,129,num,2,16);
	LCD_DrawRectangle(3,155,237,337);

			if(seat1==1)
	{
		LCD_Fill(50,160,190,200,BLUE);
		Show_Str(72,168,96,24,"查看信息",24,1);
	}
		else if(seat1==0)
	{
		LCD_Fill(50,160,190,200,GREEN);
		Show_Str(66,168,108,24,"1车位可用",24,1);
	}
	
		if(seat2==1)
	{
		LCD_Fill(50,210,190,250,BLUE);
		Show_Str(72,218,96,24,"查看信息",24,1);
	}
		else if(seat2==0)
	{
		LCD_Fill(50,210,190,250,GREEN);
		Show_Str(66,218,108,24,"2车位可用",24,1);
	}
	
		if(seat3==1)
	{
		LCD_Fill(50,260,190,300,BLUE);
		POINT_COLOR=BLACK;
		Show_Str(72,268,96,24,"查看信息",24,1);
	}
		else if(seat3==0)
	{
		LCD_Fill(50,260,190,300,GREEN);
		Show_Str(66,268,108,24,"1车位可用",24,1);
	}
}

//传感器数据换算
void temp(void)         //温度传感器数据读取
{
	temperature=DS18B20_Get_Temp();	
	if(temperature<0)
	{
		LCD_ShowChar(60+40,150,'-',16,0);			//显示负号
		temperature=-temperature;					//转为正数
	}
}
//RFID信息读取函数                         被调用的函数
void RFID_read(void)
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
			 LCD_Clear(WHITE);	
				page=1;
			 delay_ms(10);
		  } 
}

//RFID刷卡进入显示函数
void RFID_display(void)
{
	POINT_COLOR=BLUE;
	Show_Str(48,5,240,24,"车位检测系统",24,0);
	POINT_COLOR=BLACK;
	if(seat==0)
	{
	Show_Str(24,40,192,24,"欢迎进入本停车场",24,0);	
	Show_Str(5,70,144,24,"用户信息为：",24,0);
	LCD_ShowNum(10,100,SN[0],3,16);
	LCD_ShowNum(58,100,SN[1],3,16);	
	LCD_ShowNum(106,100,SN[2],3,16);	
	LCD_ShowNum(154,100,SN[3],3,16);			
	
	Show_Str(5,140,144,24,"请选择停车位",24,0);
	LCD_DrawRectangle(3,170,237,337);
		if(seat1==1)  //表示被占
	{
		LCD_Fill(40,175,200,215,BLUE);
		Show_Str(72,183,96,24,"车位被占",24,1);
	}
	 if(seat1==0)  //表示未被占
	{
		LCD_Fill(40,175,200,215,GREEN);
		Show_Str(72,183,96,24,"车位可用",24,1);
	}
		if(seat2==1)  //表示被占
	{
		LCD_Fill(40,220,200,260,BLUE);
		Show_Str(72,228,96,24,"车位被占",24,1);
	}
	 if(seat2==0)  //表示未被占
	{
		LCD_Fill(40,220,200,260,GREEN);
		Show_Str(72,228,96,24,"车位可用",24,1);
	}
		if(seat3==1)  //表示被占
	{
		LCD_Fill(40,265,200,305,BLUE);
		Show_Str(72,273,96,24,"车位被占",24,1);
	}
	 if(seat3==0)  //表示未被占
	{
		LCD_Fill(40,265,200,305,GREEN);
		Show_Str(72,273,96,24,"车位可用",24,1);
	}
	
	}
	

	if(seat==1)
	{
	Show_Str(12,40,216,24,"对不起！车位已满。",24,0);		
	}
	if(seat1==1&&seat2==1&&seat3==1)
	{
		seat=1;
	}
	else 
	{
		seat=0;
	}
//	Show_Str(5,290,48,24,"返回",24,0);

}
//  用户信息函数
void user_date_display(void)   //page=2
{
	POINT_COLOR=BLUE;
	Show_Str(48,5,240,24,"车位检测系统",24,0);
	POINT_COLOR=BLACK;
	Show_Str(24,40,192,24,"欢迎使用查询系统",24,0);	
	POINT_COLOR=MAGENTA;
	Show_Str(24,70,100,24,"用户ID：",24,0);	
	POINT_COLOR=BLACK;
		if(n==1)
	{
	LCD_ShowNum(20,100,card_1[0],3,16);
	LCD_ShowNum(68,100,card_1[1],3,16);	
	LCD_ShowNum(116,100,card_1[2],3,16);	
	LCD_ShowNum(164,100,card_1[3],3,16);	
	}
	else if(n==2)
	{
	LCD_ShowNum(20,100,card_2[0],3,16);
	LCD_ShowNum(68,100,card_2[1],3,16);	
	LCD_ShowNum(116,100,card_2[2],3,16);	
	LCD_ShowNum(164,100,card_2[3],3,16);	
	}
	else if(n==3)
	{
	LCD_ShowNum(20,100,card_3[0],3,16);
	LCD_ShowNum(68,100,card_3[1],3,16);	
	LCD_ShowNum(116,100,card_3[2],3,16);	
	LCD_ShowNum(164,100,card_3[3],3,16);	
	}
	POINT_COLOR=MAGENTA;
	Show_Str(24,130,132,24,"已使用时间：",24,0);
	POINT_COLOR=BLACK;
	LCD_ShowChar(70,155,'H',16,0);
	LCD_ShowChar(120,155,'M',16,0);
	LCD_ShowChar(170,155,'S',16,0);
if(n==1)
{
	LCD_ShowNum(40,155,(t1/60)/24,2,16);	
	LCD_ShowNum(90,155,(t1/60)%24,2,16);	
	LCD_ShowNum(140,155,t1%60,2,16);	   
}
if(n==2)
{
	LCD_ShowNum(40,155,(t2/60)/24,2,16);	
	LCD_ShowNum(90,155,(t2/60)%24,2,16);	
	LCD_ShowNum(140,155,t2%60,2,16);	   
}
if(n==3)
{
	LCD_ShowNum(40,155,(t3/60)/24,2,16);	
	LCD_ShowNum(90,155,(t3/60)%24,2,16);	
	LCD_ShowNum(140,155,t3%60,2,16);	   
}
	POINT_COLOR=MAGENTA;
	Show_Str(24,180,72,24,"费率：",24,0);
	POINT_COLOR=BLACK;
	Show_Str(90,180,100,24,"5元/Min",24,0);
	POINT_COLOR=MAGENTA;
	Show_Str(24,210,144,24,"用户应缴费：",24,0);
	POINT_COLOR=BLACK;
if(n==1) LCD_ShowNum(170,214,((t1/60)%24+1)*5,3,16);
if(n==2) LCD_ShowNum(170,214,((t2/60)%24+1)*5,3,16);
if(n==3) LCD_ShowNum(170,214,((t3/60)%24+1)*5,3,16);
	Show_Str(215,210,24,24,"元",24,0);
	Show_Str(0,240,240,24,"不足一分钟按一分钟算",24,0);
	POINT_COLOR=RED;
	Show_Str(24,290,120,24,"返回主页面",24,0);	
	Show_Str(35,265,168,24,"停止使用停车位",24,0);	
}



void control(void)
{

//	use_touch();
	RFID_read();
	LCD_ShowNum(10,100,SN[0],3,16);
	LCD_ShowNum(58,100,SN[1],3,16);	
	LCD_ShowNum(106,100,SN[2],3,16);	
	LCD_ShowNum(154,100,SN[3],3,16);
//	if(door==0)
//	{
//	PWM=5;    //关门
//	}
//	if(page==0)
//	{
//		LCD_page0_display();
//		LED_RED=1;
//		LED_YELLOW=0;	
//		LED_GREEN=0;
//	}
//	else if(page==1)
//	{
//		RFID_display();
//		LED_RED=0;
//		LED_YELLOW=0;	
//		LED_GREEN=1;
//	}
//	else if(page==2)
//	{
//		user_date_display();
//		LED_RED=0;
//		LED_YELLOW=1;	
//		LED_GREEN=0;
//	}
		

}
void use_touch(void)
{
	u8 i;
	tp_dev.scan(0); 
	if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
{
	if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
	{
		if(page==0)          //主页面设计
		{
			if(tp_dev.x[0]>50&&tp_dev.x[0]<190&&tp_dev.y[0]>160&&tp_dev.y[0]<200)
		{
			if(seat1==0)   //车位为被占
			{
//				Show_Str(15,180,40,96,"车位空闲",24,0);
			}
			else if(seat1==1)
			{
			page=2;   //进入第二页
			n=1;   //显示第一个用户信息
			LCD_Clear(WHITE);
			delay_ms(10);
			}
		}
		else if(tp_dev.x[0]>50&&tp_dev.x[0]<190&&tp_dev.y[0]>210&&tp_dev.y[0]<250)
		{
			if(seat2==0)   //车位为被占
			{
//				Show_Str(15,180,40,96,"车位空闲",24,0);
			}
			else if(seat2==1)
			{
			page=2;   //进入第二页
			n=2;   //显示第一个用户信息
				LCD_Clear(WHITE);
				 delay_ms(10);
			}		
		}
		else if(tp_dev.x[0]>50&&tp_dev.x[0]<190&&tp_dev.y[0]>260&&tp_dev.y[0]<300)
		{
			if(seat3==0)   //车位为被占
			{
//				Show_Str(15,180,40,96,"车位空闲",24,0);
			}
			else if(seat3==1)
			{
			page=2;   //进入第二页
			n=3;   //显示第一个用户信息
				LCD_Clear(WHITE);
				 delay_ms(10);
			}	
		}


	}
		else if(page==1)       //选择车位
		{
			if(tp_dev.x[0]>40&&tp_dev.x[0]<200&&tp_dev.y[0]>175&&tp_dev.y[0]<215)
		{
			if(seat1==0)   //车位为被占
			{
				seat1=1;   //表示车位被占
				for(i=0;i<4;i++)  //保持信息
				{
					card_1[i]=SN[i];
				}				
				page=0;   //自动返回主页面
				LCD_Clear(WHITE);
				use1=1;         //开始计时
				door=1;       
				delay_ms(10);
			}
			else if(seat1==1)
			{

			}
		}
			if(tp_dev.x[0]>40&&tp_dev.x[0]<200&&tp_dev.y[0]>220&&tp_dev.y[0]<260)
		{
			if(seat2==0)   //车位为被占
			{
				seat2=1;   //表示车位被占
				for(i=0;i<4;i++)  //保持信息
				{
					card_2[i]=SN[i];
				}				
				page=0;   //自动返回主页面
				LCD_Clear(WHITE);
				use2=1;
				door=1;  
				 delay_ms(10);
			}
			else if(seat2==1)
			{

			}
		}
			if(tp_dev.x[0]>40&&tp_dev.x[0]<200&&tp_dev.y[0]>265&&tp_dev.y[0]<305)
		{
			if(seat3==0)   //车位为被占
			{
				seat3=1;   //表示车位被占
				for(i=0;i<4;i++)  //保持信息
				{
					card_3[i]=SN[i];
				}				
				page=0;   //自动返回主页面
				LCD_Clear(WHITE);
				use3=1;
				door=1;  
				 delay_ms(10);
			}
			else if(seat3==1)
			{

			}
		}
//		else if(tp_dev.x[0]>0&&tp_dev.x[0]<50&&tp_dev.y[0]>290&&tp_dev.y[0]<320)
//		{
//				page=0;   //自动返回主页面
//				LCD_Clear(WHITE);
//			 delay_ms(10);
//		}
		}
		else if(page==2)
		{
			if(tp_dev.x[0]>24&&tp_dev.x[0]<144&&tp_dev.y[0]>290&&tp_dev.y[0]<314)
		{
				page=0;   //自动返回主页面
				LCD_Clear(WHITE);
			 delay_ms(10);
		}
			else if(tp_dev.x[0]>35&&tp_dev.x[0]<200&&tp_dev.y[0]>265&&tp_dev.y[0]<285)
		{
			if(n==1)   
			{
				t1=0;          //清零
				use1=0;
				seat1=0;    //表示车位为被占
				door=1;
			}
						if(n==2)   
			{
				t2=0;          //清零
				use2=0;
				seat2=0;    //表示车位为被占
				door=1;
			}
						if(n==3)   
			{
				t3=0;          //清零
				use3=0;
				seat3=0;    //表示车位为被占
				door=1;
			}
			page=0;   //自动返回主页面
			LCD_Clear(WHITE);
			 delay_ms(10);
		}
		}
}	
}
}

