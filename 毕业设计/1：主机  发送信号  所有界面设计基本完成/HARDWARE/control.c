#include "control.h"
#include "date_control.h"
#include "text.h"	
#include "lcd.h"
#include "touch.h"  
#include "delay.h"	 
#include "date_control.h"
#include "motor_control.h"
#include "led.h"
#include "motor.h"

extern u16 ValidN;//模块内有效指纹个数
 const  u8* kbd_menu1[15]={"删指纹"," : ","录指纹","1","2","3","4","5","6","7","8","9","DEL","0","Enter",};//按键表
 const  u8* kbd_delFR1[15]={"返回"," : ","清空指纹","1","2","3","4","5","6","7","8","9","DEL","0","Enter",};//按键表
extern u8 tmp_buf[33]; 
extern u8 page;
extern char *str1;
extern u8 ste;  
extern u8 use_start;   //按键启动标准量
 extern u8 dl_success;   //正在进行停车操作的标准量
 extern u8 people_car;
 extern u8 people_id;
 extern u16 car_id[4];      //使用停车位的用户ID
 extern u8 use_error; 
 extern u8 use1,use2,use3,use4; 
extern u8 gly_page;
 extern u16 t1,t2,t3,t4; 
void use_control(void)   //所有页面最终都会先回归主页面，再从主页面进入其他页面  
{
	if(page==0)        //显示主页面  登录界面  一直扫描指纹模块，看是否有人登录，并且得出用户是否来取车
	{
		DL_Display();
		use_as608_scan();		
	}
	else if(page==1)   //来存车
	{
		save_car_display();
	}
	else if(page==2)   //来取车或者查看信息
	{
		qu_car_display();
	}
	else if(page==3)   //管理员登录界面
	{
		if(gly_page==0)
		{
			Gly_page_0_display();
		}
		else if(gly_page==1)
		{
			Gly_page_1_display();
		}
		else if(gly_page==2)
		{
			Gly_page_2_display();
		}
		gly_scan();	

	}
	


}

void qu_car_display(void)   //用户取车或者查看信息
{ 
		POINT_COLOR=BLUE;
		Show_Str(0,30,100,24,"用户ID：",24,0);    
		POINT_COLOR=BLACK;
		LCD_ShowNum(120,34,people_id,3,16);      //显示ID
		Show_Str(0,80,120,24,"使用车位：",24,0); 
		Show_Str(0,120,120,24,"使用时间：",24,0); 
		POINT_COLOR=RED;
		Show_Str_Mid(0,150,"停止使用本停车位",24,240);	
		Show_Str_Mid(0,180,"返回",24,240);	
		POINT_COLOR=BLACK;
		LCD_ShowChar(155,124,'H',16,0);         //显示使用时间
		LCD_ShowChar(190,124,'M',16,0);
		LCD_ShowChar(225,124,'S',16,0);
 
		    //显示ID
		if(people_id==car_id[0]) 
		{
			Show_Str(120,80,96,24,"停车位1",24,0); 
			LCD_ShowNum(50,280,car_id[0],3,16); 
			LCD_ShowNum(135,124,(t1/60)/24,2,16); 
			LCD_ShowNum(170,124,(t1/60)%24,2,16); 
			LCD_ShowNum(205,124,t1%60,2,16);
		} 
		if(people_id==car_id[1]) 
		{
			Show_Str(120,80,96,24,"停车位2",24,0); 
			LCD_ShowNum(50,280,car_id[1],3,16); 
			LCD_ShowNum(135,124,(t2/60)/24,2,16); 
			LCD_ShowNum(170,124,(t2/60)%24,2,16); 
			LCD_ShowNum(205,124,t2%60,2,16);
		}
		if(people_id==car_id[2])
		{
			Show_Str(120,80,96,24,"停车位3",24,0); 
			LCD_ShowNum(50,280,car_id[2],3,16); 
			LCD_ShowNum(135,124,(t3/60)/24,2,16); 
			LCD_ShowNum(170,124,(t3/60)%24,2,16); 
			LCD_ShowNum(205,124,t3%60,2,16);
		}	
		if(people_id==car_id[3])
		{
			Show_Str(120,80,96,24,"停车位4",24,0); 
			LCD_ShowNum(50,280,car_id[3],3,16); 
			LCD_ShowNum(135,124,(t4/60)/24,2,16); 
			LCD_ShowNum(170,124,(t4/60)%24,2,16); 
			LCD_ShowNum(205,124,t4%60,2,16);
		}		
		
		use_xx_scan();
		if(dl_success==1)
		{
			LCD_Clear(WHITE); 
			delay_ms(50);
			Show_Str_Mid(0,150,"用户正在进行",24,240);
			Show_Str_Mid(0,180,"取车操作",24,240);	
			while(dl_success)
			{
				if(people_id==car_id[0]||people_id==car_id[1])
				{
					use_motor_control(1);
				}
				else if(people_id==car_id[2]||people_id==car_id[3])
				{
					use_motor_control(2);
				}
			}	
			//取车完成后清除所有关于该停车位的信息   car_id   use
			if(people_id==car_id[0]) 
			{
				car_id[0]=0;
				use1=0;
				people_car=0;
				page=0;
				use_start=0;
				LCD_Clear(WHITE);    //操作完成 返回主页面
				delay_ms(50);
				
			}
			else if(people_id==car_id[1]) 
			{
				car_id[1]=0;
				use2=0;
				people_car=0;
				page=0;
				use_start=0;
				LCD_Clear(WHITE);    //操作完成 返回主页面
				delay_ms(50);
			
			}
			else if(people_id==car_id[2]) 
			{
				car_id[2]=0;
				use3=0;
				use_start=0;
				people_car=0;
				page=0;
							LCD_Clear(WHITE);    //操作完成 返回主页面
			delay_ms(50);
			
			}
			else if(people_id==car_id[3]) 
			{
				car_id[3]=0;
				use4=0;
				people_car=0;
				use_start=0;
				page=0;
				LCD_Clear(WHITE);    //操作完成 返回主页面
				delay_ms(50);
			
			}
		}
}
void save_car_display(void)  //存车显示函数
{
		car_settle();                //停车位显示界面
		POINT_COLOR=BLUE;
		Show_Str(0,30,100,24,"用户ID：",24,0);    
		POINT_COLOR=BLACK;
		LCD_ShowNum(120,34,people_id,3,16);      //显示ID
		use1_touch();            //选择停车位的按键检测   选完停车位将进入停车操作
		if(dl_success==1)
		{
			LCD_Clear(WHITE); 
			use_start=0;
			delay_ms(50);
			Show_Str_Mid(0,150,"用户正在进行",24,240);
			Show_Str_Mid(0,180,"停车操作",24,240);	
			while(dl_success)     //开始进行停车操作函数
			{
				if(people_car==1||people_car==2)   //一楼
				{
					use_motor_control(1);
				}
				else if(people_car==3||people_car==4)   //二楼
				{
					use_motor_control(2);
				}
				
			}
			people_car=0;
			LCD_Clear(WHITE);    //操作完成 返回主页面
			delay_ms(50);
			page=0;			
				
		}

}
void use_touch_scan(void)     // use_start=0  还没开始  use_start=1 开始  use_start=2  结束 
{
	if(KEY_TOUCH==1&&use_start==0)
	{
		use_start=1;
	}
	else if(KEY_TOUCH==1&&use_start==1)
	{
		use_start=2;    //结束标志
	}
}
void use_motor_control(u8 lc)             //停车操作，完成标准为dl_success=1
{
	if(lc==1)
	{
		if(KEY_DOWN==0&&use_start==1)   //存车或者取车
		{
			PWM=8;    //开门
		}
		else if(KEY_DOWN==0&&use_start==2)   //存车完成或者取车完成
		{
			PWM=18;   
			use_start=0;
			dl_success=0;
		}
		
	}
	else if(lc==2)
	{
		if(KEY_UP==1&&use_start==1)  //启动  但是没到2楼   //此时KEY_DOWN=0
		{
			motor_up();
		}
		else if(KEY_UP==0&&use_start==1)  //已启动  也到了2楼    
		{
			motor_stop();
			PWM=8; 
		}
		else if(KEY_DOWN==1&&use_start==2)    //再按一下 开始下降  直到底下的触碰开关碰到为止
		{
			PWM=18;   
			motor_down();
		}
		else if(KEY_DOWN==0&&use_start==2)   //操作完成
		{
			motor_stop();
			dl_success=0;
			use_start=0;

		}
		else  //其余情况  都为非法操作  停止
		{
			motor_stop();
		}

	}
}
u8 motor_rest(void)           //电梯复位
{
	if(KEY_DOWN==1)
	{
		motor_down();
		return 1;
	}
	else 
	{
		motor_stop();
		PWM=18;  
		return 0;
	}
}
void motor_up(void)
{
		PWMA=500;
		AIN1=1;
		AIN2=0;
}
void motor_down(void)
{
	PWMA=500;
	AIN1=0;
	AIN2=1;
}
void motor_stop(void)
{
	AIN1=0;
	AIN2=0;
}
void DL_Display(void)       //登录界面   page==0
{
	POINT_COLOR=BLUE;
	Show_Str_Mid(0,50,"机械车库系统",16,240);
	POINT_COLOR=BLACK;
	Show_Str(48,100,144,24,"请刷指纹登录",24,0);
}
void Error_0_display(void)   //用户没有录过指纹，警告界面   显示5秒
{
	POINT_COLOR=BLUE;
	Show_Str_Mid(0,50,"没有您的指纹信息",24,240);
	POINT_COLOR=BLACK;
	Show_Str_Mid(0,100,"请联系管理员录指纹信息",16,240);
}
void Error_1_display(void)   //用户没有录过指纹，警告界面   显示5秒
{
	POINT_COLOR=BLUE;
	Show_Str_Mid(0,50,"禁止删除管理员ID",24,240);

}
void Success_0_display(void)   //用户存车等待界面   显示5秒
{
	POINT_COLOR=BLACK;
	Show_Str_Mid(0,50,"正在进行存车操作",16,240);
}
void display_main(void)         //用户主页面 用户存车取车 界面及接口（用户已经登录完成，要么取车，要么存车）
{
	
}

void Nrf_communicate(void)          //主要发生数据
{
	
//		if(NRF24L01_TxPacket(tmp_buf)==TX_OK)
//		{
//				if(set==1)
//				{
//					tmp_buf[0]='S';
//					tmp_buf[1]=48+1;
//					tmp_buf[32]=0; 
//				}
//				else if(set==2)
//				{
//					tmp_buf[0]='S';
//					tmp_buf[1]=48+2;
//					tmp_buf[32]=0; 
//				}
//				else if(set==0)				
//				{
//					tmp_buf[0]='N';
//					tmp_buf[32]=0; 
//				}
//		}
	
	
	
	
}



void use_touch(void)
{
	
	tp_dev.scan(0); 
	if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
	{
		if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
		{
			if(tp_dev.x[0]>0&&tp_dev.x[0]<240&&tp_dev.y[0]>50&&tp_dev.y[0]<80) 
			{
				 ste=1;
			}
			if(tp_dev.x[0]>0&&tp_dev.x[0]<240&&tp_dev.y[0]>150&&tp_dev.y[0]<180) 
			{
				 ste=2;
			}
//			if(page==0)   //主页面
//			{
//				if(tp_dev.x[0]>30&&tp_dev.x[0]<130&&tp_dev.y[0]>100&&tp_dev.y[0]<130)    //用户登录
//				{
//					set=1;
//					page=1;
//					delay_ms(100);
//					LCD_Clear(WHITE);  
//					
//				}
//				if(tp_dev.x[0]>30&&tp_dev.x[0]<130&&tp_dev.y[0]>140&&tp_dev.y[0]<170)   //管理员登录
//				{
//					set=2;
//					page=1;
//					delay_ms(100);
//					LCD_Clear(WHITE);  
//					AS608_load_keyboard(0,170,(u8**)kbd_menu);  // 管理员界面加载虚拟键盘
//					Show_Str(0,80,240,16,(u8*)str1,16,0);
//				}
//			}
			
		}
	}
}
















