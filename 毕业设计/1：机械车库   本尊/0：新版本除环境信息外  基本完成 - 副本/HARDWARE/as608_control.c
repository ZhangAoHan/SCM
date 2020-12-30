#include "as608_control.h"
#include "lcd.h"
#include "malloc.h"	   
#include "as608.h"
#include "touch.h"  
#include "delay.h"	
#include "text.h"	
#include "dht11.h"
#include "adc.h"

SysPara AS608Para;//指纹模块AS608参数
u16 ValidN;//模块内有效指纹个数
u8** kbd_tbl;
const  u8* kbd_menu[15]={"删指纹"," : ","录指纹","1","2","3","4","5","6","7","8","9","DEL","0","Enter",};//按键表
const  u8* kbd_delFR[15]={"返回"," : ","清空指纹","1","2","3","4","5","6","7","8","9","DEL","0","Enter",};//按键表
extern u8 set;     //自动录入管理员指纹标准量
extern u16 now_people_id;
extern u16 now_people_mark;  
extern u8 page;
extern u8 gly_page;
extern u16 car_id[4];      //使用停车位的用户ID
extern u16 t1,t2,t3,t4;     //计时
extern	u8 temperature;  	    
extern u8 humidity;
	extern u16 adcx;    //tr
//加载按键界面（尺寸x,y为240*150）
//x,y:界面起始坐标（240*320分辨率的时候，x必须为0）
void AS608_load_keyboard(u16 x,u16 y,u8 **kbtbl)
{
	u16 i;
	POINT_COLOR=RED;
	kbd_tbl=kbtbl;
	LCD_Fill(x,y,x+240,y+150,WHITE);
	LCD_DrawRectangle(x,y,x+240,y+150);						   
	LCD_DrawRectangle(x+80,y,x+160,y+150);	 
	LCD_DrawRectangle(x,y+30,x+240,y+60);
	LCD_DrawRectangle(x,y+90,x+240,y+120);
	POINT_COLOR=BLUE;
	for(i=0;i<15;i++)
	{
		if(i==1)//按键表第2个‘:’不需要中间显示
			Show_Str(x+(i%3)*80+2,y+7+30*(i/3),80,30,(u8*)kbd_tbl[i],16,0);	
		else
			Show_Str_Mid(x+(i%3)*80,y+7+30*(i/3),(u8*)kbd_tbl[i],16,80);
	} 
}
//按键状态设置
//x,y:键盘坐标
//key:键值(0~14)
//sta:状态，0，松开；1，按下；
void AS608_key_staset(u16 x,u16 y,u8 keyx,u8 sta)
{		  
	u16 i=keyx/3,j=keyx%3;
	if(keyx>16)return;
	if(sta &&keyx!=1)//按键表第2个‘:’不需要清除
		LCD_Fill(x+j*80+1,y+i*30+1,x+j*80+78,y+i*30+28,GREEN);
	else if(keyx!=1)
		LCD_Fill(x+j*80+1,y+i*30+1,x+j*80+78,y+i*30+28,WHITE);
	if(keyx!=1)//不是‘：’
		Show_Str_Mid(x+j*80,y+7+30*i,(u8*)kbd_tbl[keyx],16,80);	
}
//得到触摸屏的输入
//x,y:键盘坐标
//返回值:（1~15,对应按键表）
u8 AS608_get_keynum(u16 x,u16 y)
{
	u16 i,j;
	static u8 key_x=0;//0,没有任何按键按下
	u8 key=0;
	tp_dev.scan(0); 		 
	if(tp_dev.sta&TP_PRES_DOWN)//触摸屏被按下
	{	
		for(i=0;i<5;i++)
		{
			for(j=0;j<3;j++)
			{
			 	if(tp_dev.x[0]<(x+j*80+80)&&tp_dev.x[0]>(x+j*80)&&tp_dev.y[0]<(y+i*30+30)&&tp_dev.y[0]>(y+i*30))
				{	
					key=i*3+j+1;	 
					break;	 		   
				}
			}
			if(key)
			{	   
				if(key_x==key)key=0;
				else 
				{
					AS608_key_staset(x,y,key_x-1,0);
					key_x=key;
					AS608_key_staset(x,y,key_x-1,1);
				}
				break;
			}
	  }  
	}else if(key_x) 
	{
		AS608_key_staset(x,y,key_x-1,0);
		key_x=0;
	} 
	return key; 
}
//获取键盘数值
u16 GET_NUM(void)
{
	u8  key_num=0;
	u16 num=0;
	while(1)
	{
		key_num=AS608_get_keynum(0,170);	
		if(key_num)
		{
			if(key_num==1)return 0xFFFF;//‘返回’键
			if(key_num==3)return 0xFF00;//		
			if(key_num>3&&key_num<13&&num<99)//‘1-9’键(限制输入3位数)
				num =num*10+key_num-3;		
			if(key_num==13)num =num/10;//‘Del’键			
			if(key_num==14&&num<99)num =num*10;//‘0’键
			if(key_num==15)return num;  //‘Enter’键
		}
		LCD_ShowNum(80+15,170+7,num,6,16);
	}	
}
//显示确认码错误信息
void ShowErrMessage(u8 ensure)
{
	LCD_Fill(0,210,lcddev.width,160,WHITE);
	Show_Str_Mid(0,210,(u8*)EnsureMessage(ensure),16,240);
}
//录指纹
void Add_FR(u8 g)    //0正常模式   1自动录管理员模式
{
	u8 i,ensure ,processnum=0;
	u16 ID;
	while(1)
	{
		switch (processnum)
		{
			case 0:
				i++;
				LCD_Fill(0,100,lcddev.width,160,WHITE);
				Show_Str_Mid(0,100,"请按指纹",16,240);
				ensure=PS_GetImage();
				if(ensure==0x00) 
				{	
					ensure=PS_GenChar(CharBuffer1);//生成特征
					if(ensure==0x00)
					{
						LCD_Fill(0,120,lcddev.width,160,WHITE);
						Show_Str_Mid(0,120,"指纹正常",16,240);
						i=0;
						processnum=1;//跳到第二步						
					}else ShowErrMessage(ensure);				
				}else ShowErrMessage(ensure);						
				break;
			
			case 1:
				i++;
				LCD_Fill(0,100,lcddev.width,160,WHITE);
				Show_Str_Mid(0,100,"请按再按一次指纹",16,240);
				ensure=PS_GetImage();
				if(ensure==0x00) 
				{
					ensure=PS_GenChar(CharBuffer2);//生成特征
					if(ensure==0x00)
					{
						LCD_Fill(0,120,lcddev.width,160,WHITE);
						Show_Str_Mid(0,120,"指纹正常",16,240);
						i=0;
						processnum=2;//跳到第三步
					}else ShowErrMessage(ensure);	
				}else ShowErrMessage(ensure);		
				break;

			case 2:
				LCD_Fill(0,100,lcddev.width,160,WHITE);
				Show_Str_Mid(0,100,"对比两次指纹",16,240);
				ensure=PS_Match();
				if(ensure==0x00) 
				{
					LCD_Fill(0,120,lcddev.width,160,WHITE);
					Show_Str_Mid(0,120,"对比成功,两次指纹一样",16,240);
					processnum=3;//跳到第四步
				}
				else 
				{
					LCD_Fill(0,100,lcddev.width,160,WHITE);
					Show_Str_Mid(0,100,"对比失败，请重新录入指纹",16,240);
					ShowErrMessage(ensure);
					i=0;
					processnum=0;//跳回第一步		
				}
				delay_ms(1200);
				break;

			case 3:
				LCD_Fill(0,100,lcddev.width,160,WHITE);
				Show_Str_Mid(0,100,"生成指纹模板",16,240);
				ensure=PS_RegModel();
				if(ensure==0x00) 
				{
					LCD_Fill(0,120,lcddev.width,160,WHITE);
					Show_Str_Mid(0,120,"生成指纹模板成功",16,240);
					processnum=4;//跳到第五步
				}else {processnum=0;ShowErrMessage(ensure);}
				delay_ms(1200);
				break;
				
			case 4:	
				if(g==0)    //正常模式
				{
					LCD_Fill(0,100,lcddev.width,160,WHITE);
					Show_Str_Mid(0,100,"请输入储存ID,按Enter保存",16,240);
					Show_Str_Mid(0,120,"0=< ID <=298",16,240);
					do
					ID=GET_NUM();
//					while(!(ID<AS608Para.PS_max));//输入ID必须小于容量的最大值
					while(!(ID<299));//输入ID必须小于容量的最大值
					ensure=PS_StoreChar(CharBuffer2,ID);//储存模板
					if(ensure==0x00) 
					{			
					LCD_Fill(0,100,lcddev.width,160,WHITE);					
					Show_Str_Mid(0,120,"录入指纹成功",16,240);
					PS_ValidTempleteNum(&ValidN);//读库指纹个数
					Show_Str(0,80,96,24,"剩余库：",24,0);
					LCD_ShowNum(100,84,AS608Para.PS_max-ValidN,3,16);   //显示剩余指纹数量
					delay_ms(1500);
					LCD_Fill(0,100,240,160,WHITE);
					set=0;		    //清除标准量
					return ;
					}else {processnum=0;ShowErrMessage(ensure);}		
				}
				else    //录管理员指纹
				{ 
					ID=299;
					ensure=PS_StoreChar(CharBuffer2,ID);//储存模板
										if(ensure==0x00) 
					{			
					LCD_Fill(0,100,lcddev.width,160,WHITE);					
					Show_Str_Mid(0,120,"录入指纹成功",16,240);
					PS_ValidTempleteNum(&ValidN);//读库指纹个数
					Show_Str(0,80,96,24,"剩余库：",24,0);
					LCD_ShowNum(100,84,AS608Para.PS_max-ValidN,3,16);   //显示剩余指纹数量
					delay_ms(1500);
					LCD_Clear(WHITE);
					POINT_COLOR=BLUE;
					Show_Str_Mid(0,50,"管理员录指纹成功",24,240);
					delay_ms(3000);
					LCD_Clear(WHITE);
					set=0;		    //清除标准量
					return ;
					}else {processnum=0;ShowErrMessage(ensure);}
				}	
				break;				
		}
		delay_ms(400);
		if(i==5)//超过5次没有按手指则退出
		{
			LCD_Fill(0,100,lcddev.width,160,WHITE);
			break;	
		}				
	}
}

//刷指纹
void press_FR(void)
{
	SearchResult seach;
	u8 ensure;
	char *str;
	ensure=PS_GetImage();
	if(ensure==0x00)//获取图像成功 
	{	
		ensure=PS_GenChar(CharBuffer1);
		if(ensure==0x00) //生成特征成功
		{		
			ensure=PS_HighSpeedSearch(CharBuffer1,0,AS608Para.PS_max,&seach);
			if(ensure==0x00)//搜索成功
			{				
				LCD_Fill(0,150,lcddev.width,320,WHITE);
				Show_Str_Mid(0,150,"刷指纹成功",16,240);				
				str=mymalloc(SRAMIN,50);
				sprintf(str,"确有此人,ID:%d  匹配得分:%d",seach.pageID,seach.mathscore);
				Show_Str_Mid(0,175,(u8*)str,16,240);
				now_people_id=seach.pageID;
				now_people_mark=seach.mathscore;
				myfree(SRAMIN,str);
			}
			else 
				ShowErrMessage(ensure);					
	  }
		else
			ShowErrMessage(ensure);
	 delay_ms(600);
	 LCD_Fill(0,150,lcddev.width,320,WHITE);
	}
		
}

//删除指纹
void Del_FR(void)
{
	u8  ensure;
	u16 ValidN,num;
	LCD_Fill(0,100,lcddev.width,160,WHITE);
	Show_Str_Mid(0,100,"删除指纹",16,240);
	Show_Str_Mid(0,120,"请输入指纹ID按Enter发送",16,240);
	Show_Str_Mid(0,140,"0=< ID <=299",16,240);
	delay_ms(50);
	AS608_load_keyboard(0,170,(u8**)kbd_delFR);
	num=GET_NUM();//获取返回的数值
	if(num==0xFFFF)
		goto MENU ; //返回主页面
	else if(num==0xFF00)
	{
		ensure=PS_Empty();//清空指纹库
		gly_id_save();     //自动录指纹
		AS608_load_keyboard(0,170,(u8**)kbd_menu);//加载虚拟键盘
	}
		
	else 
		ensure=PS_DeletChar(num,1);//删除单个指纹
	if(ensure==0)
	{
		LCD_Fill(0,120,lcddev.width,160,WHITE);
		Show_Str_Mid(0,140,"删除指纹成功",16,240);		
	}
  else
	ShowErrMessage(ensure);	
	delay_ms(1200);
	PS_ValidTempleteNum(&ValidN);//读库指纹个数
	Show_Str(0,80,96,24,"剩余库：",24,0);
	LCD_ShowNum(100,84,AS608Para.PS_max-ValidN,3,16);   //显示剩余指纹数量
MENU:	
	LCD_Fill(0,100,lcddev.width,160,WHITE);
	delay_ms(50);
	AS608_load_keyboard(0,170,(u8**)kbd_menu);   
}

void as608_use_init(void)           //基础配置函数
{
	u8 ensure;  //指纹个数
	char *str;
	LCD_Clear(WHITE);
	POINT_COLOR=BLUE;
	Show_Str_Mid(0,40,"与AS608模块握手....",16,240);
	while(PS_HandShake(&AS608Addr))//与AS608模块握手
	{
		delay_ms(400);
		LCD_Fill(0,40,240,80,WHITE);
		Show_Str_Mid(0,40,"未检测到模块!!!",16,240);
		delay_ms(800);
		LCD_Fill(0,40,240,80,WHITE);
		Show_Str_Mid(0,40,"尝试连接模块...",16,240);		  
	}
	LCD_Fill(30,40,240,100,WHITE);
	Show_Str_Mid(0,40,"通讯成功!!!",16,240);
	str=mymalloc(SRAMIN,30);
	Show_Str(0,60,240,16,(u8*)str,16,0);
	ensure=PS_ValidTempleteNum(&ValidN);//读库指纹个数
	if(ensure!=0x00)
		ShowErrMessage(ensure);//显示确认码错误信息	
	ensure=PS_ReadSysPara(&AS608Para);  //读参数 
	if(ensure==0x00)
	{
		mymemset(str,0,50);
		sprintf(str,"库容量:%d     对比等级: %d",AS608Para.PS_max-ValidN,AS608Para.PS_level);
		Show_Str(0,80,240,16,(u8*)str,16,0);
	}
	else
		ShowErrMessage(ensure);	
	myfree(SRAMIN,str);
//	AS608_load_keyboard(0,170,(u8**)kbd_menu);//加载虚拟键盘
}

//AS680控制函数
/*
	1：优化主页面函数   被管理员界面调用（直接调用）
	：清除指纹（）   清除全部的指纹信息后，要进行录管理员指纹，并存储到299位置  
	：录指纹（）     录指纹   显示剩余指纹数量     并且不能把指纹录入299位置
	
*/
void page_0(void)     //通过刷指纹来进入不同的界面
{
	POINT_COLOR=BLUE;
	Show_Str_Mid(0,50,"机械车库系统",16,240);
	POINT_COLOR=BLACK;
	Show_Str(48,100,144,24,"请刷指纹登录",24,0);
		if(PS_Sta)	 //检测PS_Sta状态，如果有手指按下
	{
		press_FR();//刷指纹	    用于主页面		
	}
	if(now_people_id!=300)
	{
		if(now_people_id==299)
		{
			page=1;                           //管理员界面  进入管理员主页面
			LCD_Clear(WHITE);
		}
		else if(now_people_id!=car_id[0]&&now_people_id!=car_id[1]&&now_people_id!=car_id[2]&&now_people_id!=car_id[3]&&now_people_id!=299)
		{
			page=2;                           //存车界面
			LCD_Clear(WHITE);
		}
		else if((now_people_id==car_id[0]||now_people_id==car_id[1]||now_people_id==car_id[2]||now_people_id==car_id[3])&&now_people_id!=299)
		{
			page=3;                           //存车界面
			LCD_Clear(WHITE);
		}
	}

	
}

void gly_page_0(void)            //管理员主界面  gly_page=0  //如果点返回 必须清楚本次ID信息及得分
{
	POINT_COLOR=BLUE;
	Show_Str_Mid(0,10,"管理员登录成功",24,240);
	POINT_COLOR=RED;
	Show_Str_Mid(100,290,"返回",24,140);
	Show_Str_Mid(30,50,"查看停车位信息",24,180);
	Show_Str_Mid(30,100,"用户信息管理",24,180);
	Show_Str_Mid(30,150,"停车场环境",24,180);	
	POINT_COLOR=BLACK;
	Show_Str(10,200,120,24,"管理员ID：",24,0);
	Show_Str(10,230,120,24,"本次得分：",24,0);
	LCD_ShowNum(130,204,now_people_id,3,16);  
	LCD_ShowNum(130,234,now_people_mark,3,16);  
	gly_scan();
}
void gly_page_1(void)    //停车位显示函数   gly_page=1
{
	POINT_COLOR=BLUE;
	Show_Str_Mid(0,10,"停车位信息",24,240);
	Show_Str(10,50,120,24,"一号停车位",24,0);
	Show_Str(10,110,120,24,"二号停车位",24,0);
	Show_Str(10,170,120,24,"三号停车位",24,0);
	Show_Str(10,230,230,24,"四号停车位",24,0);
	POINT_COLOR=RED;
	Show_Str_Mid(100,290,"返回",24,140);
	POINT_COLOR=BLACK;
	
	Show_Str(10,75,120,24,"用户ID：",16,0);
	Show_Str(10,92,120,24,"使用时间：",16,0);
	
	
	Show_Str(10,135,120,24,"用户ID：",16,0);
	Show_Str(10,152,120,24,"使用时间：",16,0);
	
	
	Show_Str(10,195,120,24,"用户ID：",16,0);
	Show_Str(10,212,120,24,"使用时间：",16,0);
	
	
	Show_Str(10,255,120,24,"用户ID：",16,0);
	Show_Str(10,272,120,24,"使用时间：",16,0);
	
		if(car_id[0]==300)Show_Str(130,75,48,24,"空闲",16,0);
	else LCD_ShowNum(130,75,car_id[0],3,16);      //显示ID
		if(car_id[1]==300)Show_Str(130,135,48,24,"空闲",16,0);
	else LCD_ShowNum(130,135,car_id[1],3,16);      //显示ID
		if(car_id[2]==300)Show_Str(130,195,48,24,"空闲",16,0);
	else LCD_ShowNum(130,195,car_id[2],3,16);      //显示ID
		if(car_id[3]==300)Show_Str(130,255,48,24,"空闲",16,0);
	else LCD_ShowNum(130,255,car_id[3],3,16);      //显示ID
	
		LCD_ShowChar(130,92,'H',16,0);         //显示使用时间
	LCD_ShowChar(165,92,'M',16,0);
	LCD_ShowChar(200,92,'S',16,0);
	LCD_ShowNum(115,92,(t1/60)/24,2,16); 
	LCD_ShowNum(145,92,(t1/60)%24,2,16); 
	LCD_ShowNum(180,92,t1%60,2,16); 
		LCD_ShowChar(130,152,'H',16,0);
	LCD_ShowChar(165,152,'M',16,0);
	LCD_ShowChar(200,152,'S',16,0);
	LCD_ShowNum(115,152,(t2/60)/24,2,16); 
	LCD_ShowNum(145,152,(t2/60)%24,2,16); 
	LCD_ShowNum(180,152,t2%60,2,16); 
		LCD_ShowChar(130,212,'H',16,0);
	LCD_ShowChar(165,212,'M',16,0);
	LCD_ShowChar(200,212,'S',16,0);
	LCD_ShowNum(115,212,(t3/60)/24,2,16); 
	LCD_ShowNum(145,212,(t3/60)%24,2,16); 
	LCD_ShowNum(180,212,t3%60,2,16); 
		LCD_ShowChar(130,272,'H',16,0);
	LCD_ShowChar(165,272,'M',16,0);
	LCD_ShowChar(200,272,'S',16,0);
	LCD_ShowNum(115,272,(t4/60)/24,2,16); 
	LCD_ShowNum(145,272,(t4/60)%24,2,16); 
	LCD_ShowNum(180,272,t4%60,2,16); 
	
	gly_scan();
}
void gly_page_2(void)
{
		u8 key_num;	
		POINT_COLOR=BLUE;
		Show_Str_Mid(0,10,"用户信息管理",24,240);
		PS_ValidTempleteNum(&ValidN);//读库指纹个数
		Show_Str(0,80,96,24,"剩余库：",24,0);
		LCD_ShowNum(100,84,AS608Para.PS_max-ValidN,3,16);   //显示剩余指纹数量
		POINT_COLOR=RED;
		Show_Str_Mid(0,40,"返回",24,240);
		AS608_load_keyboard(0,170,(u8**)kbd_menu);//加载虚拟键盘  进入人员信息管理界面  需要先加载虚拟按键
		set=1;
		while(set)
		{
			key_num=AS608_get_keynum(0,170);	
			if(key_num)
			{
				if(key_num==1)Del_FR();		//删指纹
				if(key_num==3)Add_FR(0);		//录指纹									
			}	
			gly_scan();
		}

}
void gly_page_3(void)       //环境信息显示界面
{
	POINT_COLOR=BLUE;
	Show_Str_Mid(0,10,"停车场环境信息",24,240);
	POINT_COLOR=BLACK;
	Show_Str(0,50,120,24,"温度信息:",24,0);
	Show_Str(0,100,120,24,"湿度信息:",24,0);
	Show_Str(0,150,120,24,"光强信息:",24,0);
		LCD_ShowNum(150,50,temperature,2,24); 
	LCD_ShowString(180,50,60,24,24,"℃");
		LCD_ShowNum(150,100,humidity,2,24); 
	LCD_ShowString(180,100,60,24,24,"RH");
			LCD_ShowNum(150,150,adcx,4,24); 
	POINT_COLOR=RED;
	Show_Str_Mid(100,290,"返回",24,140);
	gly_scan();
}
void date_read(void)    //环境信息数据更新
{
	adcx=Get_Adc_Average(ADC_CH1,10);
	DHT11_Read_Data(&temperature,&humidity);	//读取温湿度值	
}
void gly_scan(void)     //进入管理员界面后的触摸函数
{
		tp_dev.scan(0); 
	if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
	{
		if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
		{
			if(gly_page==0)
			{
					if(tp_dev.x[0]>0&&tp_dev.x[0]<240&&tp_dev.y[0]>290&&tp_dev.y[0]<320)   //返回
				{
						page=0;               //管理员返回  该操作完成后需要清除本次登录的ID信息及得分信息
						gly_page=0;
						now_people_id=300;
						now_people_mark=0;
						LCD_Clear(WHITE); 
						delay_ms(100);
						
				}
				if(tp_dev.x[0]>30&&tp_dev.x[0]<180&&tp_dev.y[0]>50&&tp_dev.y[0]<80)     //停车位信息  gly_page=1
				{
					gly_page=1;
					LCD_Clear(WHITE); 
					delay_ms(100);
					
				}
				if(tp_dev.x[0]>30&&tp_dev.x[0]<180&&tp_dev.y[0]>100&&tp_dev.y[0]<130)  //用户信息管理  gly_page=2
				{
					gly_page=2;
					LCD_Clear(WHITE); 
					delay_ms(100);
				}
				if(tp_dev.x[0]>30&&tp_dev.x[0]<180&&tp_dev.y[0]>150&&tp_dev.y[0]<180)    //环境信息  gly_page=3
				{
					gly_page=3;
					LCD_Clear(WHITE); 
					delay_ms(100);
				}
			}
			else if(gly_page==1)
			{
					if(tp_dev.x[0]>0&&tp_dev.x[0]<240&&tp_dev.y[0]>290&&tp_dev.y[0]<320)   //返回
				{
						gly_page=0;
						LCD_Clear(WHITE); 
						delay_ms(100);
						
				}
			}
			else if(gly_page==2)
			{
				if(tp_dev.x[0]>0&&tp_dev.x[0]<240&&tp_dev.y[0]>40&&tp_dev.y[0]<65)   //返回
				{
						gly_page=0;
						set=0;   //强制返回
						LCD_Clear(WHITE); 
						delay_ms(100);
						
				}
			}
			else if(gly_page==3)
			{
					if(tp_dev.x[0]>0&&tp_dev.x[0]<240&&tp_dev.y[0]>290&&tp_dev.y[0]<320)   //返回
				{
						gly_page=0;
						LCD_Clear(WHITE); 
						delay_ms(100);
						
				}
			}
				
				

		}
	}
}
void gly_id_save(void)    //自动录管理员指纹  录完后清屏
{
	set=1;           //操作标志量
	LCD_Clear(WHITE);
	POINT_COLOR=BLUE;
	Show_Str_Mid(0,50,"请管理员录指纹",24,240);
	while(set)
	{
			Add_FR(1);
	}
}
