#ifndef __DATE_CONTROL_H
#define __DATE_CONTROL_H
#include <stdio.h>
#include "stm32f10x.h" 

void Add_FR(void);	//录指纹
void Del_FR(void);	//删除指纹
void press_FR(void);//刷指纹
void ShowErrMessage(u8 ensure);//显示确认码错误信息
void AS608_load_keyboard(u16 x,u16 y,u8 **kbtbl);//加载虚拟键盘
u8  AS608_get_keynum(u16 x,u16 y);//获取键盘数
u16 GET_NUM(void);//获取数值

void car_settle(void) ;
void use1_touch(void);
void use_as608_scan(void) ;
void AS_Init(void);
void use_xx_scan(void);	
void gly_scan(void);
void date_read(void)  ;
void date_read_scan(void);
void gly_id_save(void);  //每次开机前得到管理员ID
#endif

