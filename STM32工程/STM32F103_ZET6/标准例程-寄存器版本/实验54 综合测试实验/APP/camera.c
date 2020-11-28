#include "camera.h"
#include "common.h"	
#include "ov7670.h"  
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//APP-照相机 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/10/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   
 
extern vu8 frame_cnt;
extern vu8 ov_sta;	

	   

//摄像头提示
u8*const camera_remind_tbl[3][GUI_LANGUAGE_NUM]=
{
{"初始化OV7670,请稍侯...","初始化OV7670,請稍後...","OV7670 Init,Please wait...",},	 
{"未检测到OV7670,请检查...","未檢測到OV7670,請檢查...","No OV7670 find,Please check...",},	 
{"保存为:","保存為:","SAVE AS:",},	 
};
//拍照成功提示框标题
u8*const camera_saveok_caption[GUI_LANGUAGE_NUM]=
{
"拍照成功！","拍照成功！","Take Photo OK！",
};
													    
//00级功能选项表标题
u8*const camera_l00fun_caption[GUI_LANGUAGE_NUM]=
{
"相机设置","相機設置","Camera Set",
};

//00级功能选项表
u8*const camera_l00fun_table[GUI_LANGUAGE_NUM][6]=
{
{"优先模式","场景设置","特效设置","亮度设置","色度设置","对比度设置",},
{"優先模式","場景設置","特效設置","亮度設置","色度設置","對比度設置",},
{"Priority","Scene","Effects","Brightness","Saturation","Contrast"},
};	
//////////////////////////////////////////////////////////////////////////	  
//10级功能选项表
//速度
u8*const camera_l10fun_table[GUI_LANGUAGE_NUM][2]=
{
{"清晰度优先","速度优先",},
{"清晰度優先","速度優先",},
{"Definition","Speed",},
};
//11级功能选项表
//场景模式
u8*const camera_l11fun_table[GUI_LANGUAGE_NUM][5]=
{
{"自动","晴天","阴天","办公室","家庭",},
{"自動","晴天","陰天","辦公室","家庭",},
{"Auto","Sunny","Cloudy","Office","Home"},
};	
//12级功能选项表
//特效设置
u8*const camera_l12fun_table[GUI_LANGUAGE_NUM][7]=
{
{"普通","负片","黑白","偏红色","偏绿色","偏蓝色","复古"},
{"普通","負片","黑白","偏紅色","偏綠色","偏藍色","復古"},
{"Normal","Negative","B&W","Redish","Greenish","Bluish","Antique",},
};	
//13~15级功能选项表
//都是-2~2的5個值
u8*const camera_l135fun_table[GUI_LANGUAGE_NUM][5]=
{
{"-2","-1","0","+1","+2",},					   
{"-2","-1","0","+1","+2",},					   
{"-2","-1","0","+1","+2",},					   
};	   
//////////////////////////////////////////////////////////////////////////	  
//更新LCD显示
void camera_refresh(void)
{
	u32 j;
 	u16 color;	 
	if(ov_sta)//有帧中断更新？
	{
		LCD_Scan_Dir(U2D_L2R);		//从上到下,从左到右  
		if(lcddev.id==0X1963)LCD_Set_Window((lcddev.width-240)/2,(lcddev.height-320)/2,240,320);//将显示区域设置到屏幕中央
		else if(lcddev.id==0X5510||lcddev.id==0X5310)LCD_Set_Window((lcddev.width-320)/2,(lcddev.height-240)/2,320,240);//将显示区域设置到屏幕中央
		LCD_WriteRAM_Prepare();     //开始写入GRAM	
		OV7670_RRST=0;				//开始复位读指针 
		OV7670_RCK_L;
		OV7670_RCK_H;
		OV7670_RCK_L;
		OV7670_RRST=1;				//复位读指针结束 
		OV7670_RCK_H;
		for(j=0;j<76800;j++)
		{
			OV7670_RCK_L;
			color=GPIOC->IDR&0XFF;	//读数据
			OV7670_RCK_H; 
			color<<=8;  
			OV7670_RCK_L;
			color|=GPIOC->IDR&0XFF;	//读数据
			OV7670_RCK_H; 
			LCD->LCD_RAM=color;    
		}   							  
 		ov_sta=0;					//清零帧中断标记
		frame_cnt++; 
		LCD_Scan_Dir(DFT_SCAN_DIR);	//恢复默认扫描方向 
	}
}	  
//通过时间获取文件名
//组合成:形如"0:PHOTO/PIC20120321210633.bmp"的文件名
void camera_new_pathname(u8 *pname)
{	 
	RTC_Get();//更新时间
	sprintf((char*)pname,"0:PHOTO/PIC%04d%02d%02d%02d%02d%02d.bmp",calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,calendar.min,calendar.sec);
}
//摄像头初始化
//所有照片文件,均保存在SD卡PHOTO文件夹内.
u8 camera_play(void)
{	
 	u8 rval=0;
	u8 res;
 	u8 *caption=0;
	u8 *pname;
	u8 selx=0;
	u8 l00sel=0,l10sel=0,l11sel=0,l12sel=0;//默认选择项
	u8 l345sel[3];
	u8 *psn;
	u8 speedctrl=0;

 	//提示开始检测OV7670
 	window_msg_box((lcddev.width-200)/2,(lcddev.height-80)/2,200,80,(u8*)camera_remind_tbl[0][gui_phy.language],(u8*)APP_REMIND_CAPTION_TBL[gui_phy.language],12,0,0,0);
	if(gui_phy.memdevflag&(1<<0))f_mkdir("0:PHOTO");//强制创建文件夹,给照相机用
	if(OV7670_Init())	//初始化ov7670
	{
		window_msg_box((lcddev.width-200)/2,(lcddev.height-80)/2,200,80,(u8*)camera_remind_tbl[1][gui_phy.language],(u8*)APP_REMIND_CAPTION_TBL[gui_phy.language],12,0,0,0);
 		delay_ms(500);  
		rval=1;
	} 
	pname=gui_memin_malloc(40);	//申请40个字节内存,用于存放文件名
	psn=gui_memin_malloc(50);	//申请50个字节内存,用于存放类似：“保存为:0:PHOTO/PIC20120321210633.bmp"”的提示语
	if(pname==NULL)rval=1;		//申请失败	  
	if(rval==0)//OV7670正常
	{ 
		l345sel[0]=2;//亮度默认为2,实际值0
		l345sel[1]=2;//色度默认为2,实际值0
		l345sel[2]=2;//对比度默认为2,实际值0
		OV7670_Light_Mode(l11sel);
 		OV7670_Special_Effects(l12sel);	 
		OV7670_Brightness(l345sel[0]);
  		OV7670_Color_Saturation(l345sel[1]);
		OV7670_Contrast(l345sel[2]);  
		EXTI8_Init();						//使能外部中断8,捕获帧中断
		OV7670_Window_Set(12,176,240,320);	//设置窗口	  
	  	OV7670_CS=0; 			
		LCD_Clear(BLACK); 
		TIM3_Int_Init(10000-1,7200-1);		//启动TIM3 ,1s中断一次	
		while(1)	 
		{		 	
			tp_dev.scan(0);
			if(tp_dev.sta&TP_PRES_DOWN)
			{    		 
				caption=(u8*)camera_l00fun_caption[gui_phy.language];
				res=app_items_sel((lcddev.width-160)/2,(lcddev.height-72-32*6)/2,160,72+32*6,(u8**)camera_l00fun_table[gui_phy.language],6,(u8*)&l00sel,0X90,caption);//单选 
				if(res==0)
				{
					caption=(u8*)camera_l00fun_table[gui_phy.language][l00sel];
					camera_refresh();//刷新一下
					switch(l00sel)
					{
						case 0://优先模式	  
							res=app_items_sel((lcddev.width-160)/2,(lcddev.height-72-32*2)/2,160,72+32*2,(u8**)camera_l10fun_table[gui_phy.language],2,(u8*)&l10sel,0X90,caption);//单选
							if(res==0)
							{
								if(l10sel==0)speedctrl=1;	//15帧
								else speedctrl=0; 			//30帧
								SCCB_WR_Reg(0X11,speedctrl);//15/30帧速度,15帧时，清晰度变好
							}
							break;
						case 1://场景设置		 
							res=app_items_sel((lcddev.width-160)/2,(lcddev.height-72-32*5)/2,160,72+32*5,(u8**)camera_l11fun_table[gui_phy.language],5,(u8*)&l11sel,0X90,caption);//单选
							if(res==0)
							{
								OV7670_Light_Mode(l11sel);		//白平衡设置	 
							}
							break;
						case 2://特效设置	  
							res=app_items_sel((lcddev.width-160)/2,(lcddev.height-72-32*7)/2,160,72+32*7,(u8**)camera_l12fun_table[gui_phy.language],7,(u8*)&l12sel,0X90,caption);//单选
							if(res==0)
							{
								OV7670_Special_Effects(l12sel);	//特效设置
							}
							break;
						case 3://亮度,色度,对比度设置.	    
						case 4://亮度,色度,对比度设置.
						case 5://亮度,色度,对比度设置.
							selx=l345sel[l00sel-3];//得到之前的选择
							res=app_items_sel((lcddev.width-160)/2,(lcddev.height-72-32*5)/2,160,72+32*5,(u8**)camera_l135fun_table[gui_phy.language],5,(u8*)&selx,0X90,caption);//单选
							if(res==0)
							{
								l345sel[l00sel-3]=selx;//记录新值
							 	if(l00sel==3)OV7670_Brightness(selx);	   	//亮度设置
								if(l00sel==4)OV7670_Color_Saturation(selx);	//色度设置
								if(l00sel==5)OV7670_Contrast(selx);			//对比度设置
							}
							break;
					}
				}
				LCD_Clear(BLACK);
 			}
 			if(system_task_return)break;//TPAD返回
 			camera_refresh();
 			if(KEY_Scan(0)==WKUP_PRES)//KEY_UP按下了一次,拍照一次
			{					 	
				LED1=0;//DS1亮,提示正在保存
				pname[0]='\0';//添加结束符
				camera_new_pathname(pname);
				if(pname!=NULL)
				{		    
					if(bmp_encode(pname,(lcddev.width-240)/2,(lcddev.height-320)/2,240,320,0))//拍照有误
					{
						window_msg_box((lcddev.width-200)/2,(lcddev.height-100)/2,200,100,(u8*)APP_CREAT_ERR_MSG_TBL[gui_phy.language],(u8*)APP_REMIND_CAPTION_TBL[gui_phy.language],12,0,0,0);//提示SD卡是否存在
						delay_ms(2000);//等待2秒钟
					}else
					{
						strcpy((char*)psn,(const char *)camera_remind_tbl[2][gui_phy.language]);
						strcat((char*)psn,(const char *)pname);
 						window_msg_box((lcddev.width-180)/2,(lcddev.height-80)/2,180,80,psn,(u8*)camera_saveok_caption[gui_phy.language],12,0,0,0);
	 					BEEP=1;	//蜂鸣器短叫，提示拍照完成
						delay_ms(100);
			 		}
					system_task_return=0;//清除TPAD
				}
				LED1=1;	//DS1灭,提示保存完成
				BEEP=0;	//蜂鸣器短叫
				delay_ms(1800);
			}   
 		}
	}
	gui_memin_free(pname);	
	gui_memin_free(psn);							  
	TIM3->CR1&=~(1<<0);//关闭定时器3
	EXTI->IMR&=~(1<<8);//关闭line8中断		  
	return 0;	 
}















