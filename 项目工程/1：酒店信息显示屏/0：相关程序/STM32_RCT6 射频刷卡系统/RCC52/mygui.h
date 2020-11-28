#ifndef __MYGUI_H
#define __MYGUI_H

#include "sys.h"


/**************************************
		  我的GUI触摸函数声明
**************************************/


//显示界面
void GUI_DISP_0(void);				    //数字按键界面
void GUI_DISP_1(void);            //RTC实时时钟显示界面
void GUI_DISP_2(void);            //温度显示界面



//触摸操作
//TFTLCD触摸校准函数
u8 my_GUI_TOUCH_0(void);				  //数字按键触摸扫描反馈键值
void my_GUI_TOUCH_1(void);				//数字按键触摸键值处理
void my_GUI_TOUCH_2(void);				//数字按键触摸处理










//毕业设计操作界面及触摸响应函数
void GUI_DISP_MENU(void);         //菜单栏显示触摸界面
u8 TOUCH_DISP_MENU(void); 				 		//键值返回
void TOUCH_GUI_DISP_MENU(void);		 		//键值处理

void GUI_DISP_chongzhi(void);     //充值
u8 TOUCH_DISP_chongzhi(void);			 		//键值返回
void TOUCH_GUI_DISP_chongzhi(void);		//键值处理
void GUI_DISP_chongzhi0(void);    //充值金额
void TOUCH_GUI_DISP_chongzhi0(void);	
void GUI_DISP_chongzhi1(void);    //成功
void TOUCH_GUI_DISP_chongzhi1(void);
void GUI_DISP_chongzhi2(void);    //失败
void TOUCH_GUI_DISP_chongzhi2(void);		
void GUI_DISP_chongzhi3(void);    //失败
void TOUCH_GUI_DISP_chongzhi3(void);		

void GUI_DISP_xiaofei(void);      //消费
u8 TOUCH_DISP_xiaofei(void);			 		//键值返回
void TOUCH_GUI_DISP_xiaofei(void);		//键值处理
void GUI_DISP_xiaofei0(void);     //消费金额
void TOUCH_GUI_DISP_xiaofei0(void);	
void GUI_DISP_xiaofei1(void);     //成功
void TOUCH_GUI_DISP_xiaofei1(void);		
void GUI_DISP_xiaofei2(void);     //失败（显示余额不足）
void TOUCH_GUI_DISP_xiaofei2(void);
void GUI_DISP_xiaofei3(void);		  //不存在此卡！（此卡未激活）
void TOUCH_GUI_DISP_xiaofei3(void);
void GUI_DISP_xiaofei4(void);		  //未解锁！（此卡已挂失）
void TOUCH_GUI_DISP_xiaofei4(void);


void GUI_DISP_chaxun(void);       //查询
void TOUCH_GUI_DISP_chaxun(void);			//键值处理
void GUI_DISP_chaxun0(void);      //查询结果
void TOUCH_GUI_DISP_chaxun0(void);		//键值处理	

void GUI_DISP_guashijiegua(void); //挂失/解挂
u8 TOUCH_DISP_guashijiegua(void);			 		//键值返回
void TOUCH_GUI_DISP_guashijiegua(void);		//键值处理
void GUI_DISP_jiegua(void);				//解挂
void TOUCH_GUI_DISP_jiegua(void);	
void GUI_DISP_guashi(void);				//挂失
void TOUCH_GUI_DISP_guashi(void);	
void GUI_DISP_guashijiegua0(void);//挂失成功
void TOUCH_GUI_DISP_guashijiegua0(void);		
void GUI_DISP_guashijiegua1(void);//挂失失败（输入密码不正确！）
void TOUCH_GUI_DISP_guashijiegua1(void);	
void GUI_DISP_guashijiegua2(void);//解挂成功
void TOUCH_GUI_DISP_guashijiegua2(void);	
void GUI_DISP_guashijiegua3(void);//解挂失败（输入卡号和实际卡号不一致）
void TOUCH_GUI_DISP_guashijiegua3(void);	
void GUI_DISP_guashijiegua4(void);//解挂失败（输入密码不正确！）
void TOUCH_GUI_DISP_guashijiegua4(void);	
void GUI_DISP_guashijiegua5(void);//挂失失败，不存在此卡
void TOUCH_GUI_DISP_guashijiegua5(void);	
void GUI_DISP_guashijiegua6(void);//解挂失败，不存在此卡
void TOUCH_GUI_DISP_guashijiegua6(void);	



u8 TOUCH_all(void);						//全屏触摸键值返回

void GUI_DISP_administrator(void); 
void TOUCH_GUI_DISP_administrator(void); //判断是否是管理员的卡号
void GUI_DISP_administrator0(void); 
void TOUCH_GUI_DISP_administrator0(void);//不是管理员卡号


#endif





