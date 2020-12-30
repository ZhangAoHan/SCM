#include "display.h"
#include "lcd.h"
#include "touch.h"  
#include "delay.h"	
#include "text.h"	
#include "as608.h"
#include "as608_control.h"
#include "motor_control.h"

//主要为 非管理员界面以及非操作界面外的所有显示函数
extern u16 car_id[4];      //使用停车位的用户ID
extern u16 t1,t2,t3,t4;     //计时
extern u8 use1,use2,use3,use4;   
extern u8 people_car;   //用户选择完停车位后  用于传递选择的楼层信息  为了下一步的电机控制
extern u8 set;     //自动录入管理员指纹标准量
extern u16 now_people_id;
extern u16 now_people_mark;  
extern u8 page;
 extern u8 dl_success;   //正在进行停车操作的标准量  1正在进行  0操作完成  为了显示 正在停车操作或者显示正在取车操作
 
 /*
	存车显示界面组函数                   最后直接调用save_car_display（）
 */
void save_car_display(void)  //存车显示函数    用户刷指纹 并且之前没有刷过  page=2
{	
	
	POINT_COLOR=BLACK;
	Show_Str(10,0,120,24,"使用者ID：",24,0);
	Show_Str(10,30,120,24,"本次得分：",24,0);
	LCD_ShowNum(130,4,now_people_id,3,16);  
	LCD_ShowNum(130,34,now_people_mark,3,16);  
	car_settle();                //停车位显示及选择界面
	set=1;
	while(set)
	{
		use1_touch();
		if(dl_success)         //选择了停车位  （如果没有选择 则一直在该页面显示 或者点返回）
		{
			if(people_car==1||people_car==2)   //一楼
			{
				cl_display(1,1);
			}
			else if(people_car==3||people_car==4)   //二楼
			{
				cl_display(2,1);
			}
			//存车操作以及完成  返回主页面  并将各种标准量清零
				now_people_id=300;
				now_people_mark=0;
				people_car=0;
				dl_success=0;
				LCD_Clear(WHITE);    //操作完成 返回主页面
				delay_ms(100);
				page=0;
				set=0;
		}
	}

		
}



void car_settle(void)   //停车位选择函数  自带触摸扫描
{
		LCD_DrawRectangle(10,60,110,160);
	LCD_DrawRectangle(9,59,111,161);
		LCD_DrawRectangle(130,60,230,160);
	LCD_DrawRectangle(129,59,231,161);
		LCD_DrawRectangle(10,180,110,280);
	LCD_DrawRectangle(9,179,111,281);
		LCD_DrawRectangle(130,180,230,280);
	LCD_DrawRectangle(129,179,231,281);
		if(car_id[0]==300)
	{
		LCD_Fill(15,65,105,105,GREEN);
		POINT_COLOR=BLACK;
		Show_Str_Mid(15,72,"车位可用",16,90);
	}
	else
	{
		LCD_Fill(15,65,105,105,BLUE);
		POINT_COLOR=BLACK;
		Show_Str_Mid(15,72,"车位被占",16,90);
	}
		if(car_id[1]==300)
	{
		LCD_Fill(135,65,225,105,GREEN);
		POINT_COLOR=BLACK;
		Show_Str_Mid(135,72,"车位可用",16,90);
	}
	else
	{
		LCD_Fill(135,65,225,105,BLUE);
		POINT_COLOR=BLACK;
		Show_Str_Mid(135,72,"车位被占",16,90);
	}
		if(car_id[2]==300)
	{
		LCD_Fill(15,185,105,225,GREEN);
		POINT_COLOR=BLACK;
		Show_Str_Mid(15,192,"车位可用",16,90);
	}
	else
	{
		LCD_Fill(15,185,105,225,BLUE);
		POINT_COLOR=BLACK;
		Show_Str_Mid(15,192,"车位被占",16,90);
	}
		if(car_id[3]==300)
	{
		LCD_Fill(135,185,225,225,GREEN);
		POINT_COLOR=BLACK;
		Show_Str_Mid(135,192,"车位可用",16,90);
	}
	else
	{
		LCD_Fill(135,185,225,225,BLUE);
		POINT_COLOR=BLACK;
		Show_Str_Mid(135,192,"车位被占",16,90);
	}
	Show_Str(100,290,48,24,"返回",24,0);
}

void use1_touch(void)  //选择停车位的附带触摸函数
{
	tp_dev.scan(0); 
	if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
	{
		if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
		{
			if(tp_dev.x[0]>15&&tp_dev.x[0]<105&&tp_dev.y[0]>60&&tp_dev.y[0]<100&&car_id[0]==300)
			{
				car_id[0]=now_people_id;
				use1=1;      //开启计时
				people_car=1;
				dl_success=1;
				LCD_Clear(WHITE); 
				delay_ms(100);
			}
			else if(tp_dev.x[0]>135&&tp_dev.x[0]<225&&tp_dev.y[0]>60&&tp_dev.y[0]<100&&car_id[1]==300)
			{
				car_id[1]=now_people_id;
				use2=1;
				people_car=2;
				dl_success=1;
				LCD_Clear(WHITE); 
				delay_ms(100);
			}
			else if(tp_dev.x[0]>15&&tp_dev.x[0]<105&&tp_dev.y[0]>185&&tp_dev.y[0]<225&&car_id[2]==300)
			{
				car_id[2]=now_people_id;
				use3=1;
				people_car=3;
				dl_success=1;
				LCD_Clear(WHITE); 
				delay_ms(100);
			}
			else if(tp_dev.x[0]>135&&tp_dev.x[0]<225&&tp_dev.y[0]>185&&tp_dev.y[0]<225&&car_id[3]==300)
			{
				car_id[3]=now_people_id;
				use4=1;
				people_car=4;
				dl_success=1;
				LCD_Clear(WHITE); 
				delay_ms(100);
			}
			else if(tp_dev.x[0]>100&&tp_dev.x[0]<150&&tp_dev.y[0]>290&&tp_dev.y[0]<320)
			{
					LCD_Clear(WHITE);    //操作中断 返回主页面  该操作完成后需要清除本次登录的ID信息及得分信息
					now_people_id=300;
					now_people_mark=0;
					people_car=0;
					dl_success=0;
					delay_ms(100);
					page=0;
					set=0;
			}
		}
	}
}

/*
	取车或者查看信息组函数
*/

void qu_car_display(void)   //用户取车或者查看信息  page=3
{

	POINT_COLOR=BLACK;
	Show_Str(10,0,120,24,"使用者ID：",24,0);
	Show_Str(10,30,120,24,"本次得分：",24,0);
	LCD_ShowNum(130,4,now_people_id,3,16);  
	LCD_ShowNum(130,34,now_people_mark,3,16); 
	Show_Str(0,80,120,24,"使用车位：",24,0); 
	Show_Str(0,120,120,24,"使用时间：",24,0); 
	LCD_ShowChar(155,124,'H',16,0);         //显示使用时间
	LCD_ShowChar(190,124,'M',16,0);
	LCD_ShowChar(225,124,'S',16,0);
	POINT_COLOR=RED;
	Show_Str_Mid(0,150,"停止使用本停车位",24,240);	
	Show_Str_Mid(0,290,"返回",24,240);	
	POINT_COLOR=BLACK;
			    //显示信息
		set=1;
	while(set)
	{
		
		if(now_people_id==car_id[0]) 
		{ 
			people_car=1;   //提供取车楼层
			Show_Str(120,80,96,24,"停车位1",24,0); 
			LCD_ShowNum(135,124,(t1/60)/24,2,16); 
			LCD_ShowNum(170,124,(t1/60)%24,2,16); 
			LCD_ShowNum(205,124,t1%60,2,16);
		} 
		if(now_people_id==car_id[1]) 
		{
			people_car=2;
			use2=0;
			Show_Str(120,80,96,24,"停车位2",24,0); 
			LCD_ShowNum(135,124,(t2/60)/24,2,16); 
			LCD_ShowNum(170,124,(t2/60)%24,2,16); 
			LCD_ShowNum(205,124,t2%60,2,16);
		}
		if(now_people_id==car_id[2])
		{
			people_car=3;
			use3=0;
			Show_Str(120,80,96,24,"停车位3",24,0); 
			LCD_ShowNum(135,124,(t3/60)/24,2,16); 
			LCD_ShowNum(170,124,(t3/60)%24,2,16); 
			LCD_ShowNum(205,124,t3%60,2,16);
		}	
		if(now_people_id==car_id[3])
		{
			people_car=4;
			use4=0;
			Show_Str(120,80,96,24,"停车位4",24,0); 
			LCD_ShowNum(135,124,(t4/60)/24,2,16); 
			LCD_ShowNum(170,124,(t4/60)%24,2,16); 
			LCD_ShowNum(205,124,t4%60,2,16);
		}
		use_qc_scan();               //虚拟按键扫描函数
		if(dl_success)
		{
			if(people_car==1||people_car==2)   //一楼
			{
				cl_display(1,2);
			}
			else if(people_car==3||people_car==4)   //二楼
			{
				cl_display(2,2);
			}
			//存车操作以及完成  返回主页面  并将各种标准量清零
			now_people_id=300;
			now_people_mark=0;
			people_car=0;
			dl_success=0;
			LCD_Clear(WHITE);    //操作完成 返回主页面
			delay_ms(100);
			page=0;	
			set=0;
		}
		
			
	}
		
		
}

void use_qc_scan(void)
{
		tp_dev.scan(0); 
	if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
	{
		if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
		{
			if(tp_dev.x[0]>0&&tp_dev.x[0]<240&&tp_dev.y[0]>150&&tp_dev.y[0]<175)   //取车
			{
					dl_success=1;
				if(now_people_id==car_id[0]) car_id[0]=300,use1=0,t1=0;   //停止计时
				if(now_people_id==car_id[1]) car_id[1]=300,use2=0,t2=0;   //停止计时
				if(now_people_id==car_id[2]) car_id[2]=300,use3=0,t3=0;   //停止计时
				if(now_people_id==car_id[3]) car_id[3]=300,use4=0,t4=0;   //停止计时
					LCD_Clear(WHITE); 
					delay_ms(100);
					
			}
			if(tp_dev.x[0]>0&&tp_dev.x[0]<240&&tp_dev.y[0]>290&&tp_dev.y[0]<320)   //查看信息  返回
			{
					now_people_id=300;
					now_people_mark=0;
					people_car=0;
					dl_success=0;
					LCD_Clear(WHITE); 
					delay_ms(100);
					page=0;
					set=0;
			}
		}
	}
}


















