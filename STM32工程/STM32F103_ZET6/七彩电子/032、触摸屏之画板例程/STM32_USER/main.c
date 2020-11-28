/*  main.c  */

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "ezio.h"
#include "key.h"

#include "LcdApi.h"
#include "LcdBsp.h"
#include "touch.h"




/*************************** 文件说明 *******************************/
//ezio 单片机IO简明操作函数封装,不用声明和填写冗长的结构体,一个函数搞定
//像Arduino一样操作IO
//此程序适用于七彩光子太极M3—STM32F103开发板及部分兼容的STM32系统，
//淘宝搜索"七彩光子 太极M3 STM32开发板"购买超高性价比开发板或获取更多资料
//只供学习使用，未经作者许可，不得用于其它任何用途！
/********************************************************************/ 





#define COLOR_COUNT 8


u16 CurrentColor=RED;//画笔颜色
u16 ColorList[COLOR_COUNT]={BLACK,BLUE,BRED,YELLOW,GBLUE,RED,GREEN,CYAN};//调色板颜色列表




//画调色板
void Draw_Palette(void){
	u8 i=0;
	//u32 u32_t=0;
	LCD_Fill(5,5,35,35,RED);
	LCD_DrawRectangle(5,5,35,35);
	
	for(i=0;i<COLOR_COUNT;i++){
		LCD_Fill(i*24+40,5,i*24+40+20,25,ColorList[i]);
		//LCD_DrawRectangle(5,5,35,35);
	}
}
//画画布
void Draw_Canvas(void){
	POINT_COLOR=YELLOW;//设置字体为红色
	LCD_DrawRectangle(0,40,240-1,320-1);
	LCD_DrawRectangle(1,41,240-2,320-2);
	POINT_COLOR=BLACK;//设置字体为红色
	LCD_DrawRectangle(2,42,240-3,320-3);
}




int main(void)
{
	u8 i=0;
	delay_init();	    //延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	USART1_Init(115200);//串口1初始化
	
	LCD_Init();    //LCD初始化
	TP_Init();     //触摸屏初始化,注意这里用到了24C02来存储校准数据,因此需要24C02的驱动支持,移植的时候注意
	
	Draw_Palette();  //画调色板
	Draw_Canvas();   //画画布
	
	while(1)
	{
		//屏幕扫描
		TP_Scan(0);
		if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
		{
			if(tp_dev.y<45){   //在调色板区域
				if(tp_dev.x>45 && tp_dev.x<(240-2) && tp_dev.y>5 && tp_dev.y<25){//颜色选择区,更换笔刷颜色
					i=(tp_dev.x-45)/24;     //获取所选择的调色板颜色索引号
					CurrentColor=ColorList[i];
					LCD_Fill(5,5,35,35,CurrentColor);
					POINT_COLOR=BLACK;
					LCD_DrawRectangle(5,5,35,35);
				}
				else if(tp_dev.x>5 && tp_dev.x<35 && tp_dev.y>5 && tp_dev.y<35){//笔刷颜色指示区,点击治理清空画布
					LCD_Fill(3,43,240-4,320-4,WHITE);
				}
			}
			else if(tp_dev.y<315){                                 //画布区域
				TP_Draw_Big_Point(tp_dev.x,tp_dev.y,CurrentColor);		//画图
			}
		}
		else {
			delay_ms(10);	//没有按键按下的时候
		}
		
		//按键扫描
		switch(Key_Scan(0)){
			case KEY0_PRES:{//KEY0 按下
				if(Key_GetSta(KEY2)){//按键同时按下测试,按住KEY2 再按KEY0
					
				}
				else{                 //只有KEY0按下
					LCD_Clear(WHITE);   //清屏
					TP_Adjust();         //屏幕校准 
					TP_Save_Adjdata();
					NVIC_SystemReset();  //校准完毕 , 重启,
				}
				break;
			}
			case KEY1_PRES:{//KEY1 按下
				
				break;
			}
			case KEY2_PRES:{//KEY2 按下
				
				break;
			}
			case WKUP_PRES:{//KEY3 按下
				
				break;
			}
		}
		
	}
}




