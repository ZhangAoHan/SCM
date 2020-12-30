#ifndef __AS608_CONTROL_H
#define __AS608_CONTROL_H
#include "sys.h"



void Add_FR(u8 g);	//录指纹
void Del_FR(void);	//删除指纹
void press_FR(void);//刷指纹
void ShowErrMessage(u8 ensure);//显示确认码错误信息
void AS608_load_keyboard(u16 x,u16 y,u8 **kbtbl);//加载虚拟键盘
u8  AS608_get_keynum(u16 x,u16 y);//获取键盘数
u16 GET_NUM(void);//获取数值
void as608_use_init(void) ;
void gly_id_save(void);    //自动录管理员指纹  录完后清屏
void gly_scan(void);
void page_0(void);  
void gly_page_0(void)    ;
void gly_page_1(void) ;
void gly_page_2(void);
void gly_page_3(void)  ;
#endif


