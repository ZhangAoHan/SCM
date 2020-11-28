#include "nesplay.h"
#include "nes_main.h"	 
#include "spb.h"	  
#include "audioplay.h"	
#include "usart3.h"	
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//APP-NES模拟器 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/7/20
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//*******************************************************************************
//修改信息
//无
////////////////////////////////////////////////////////////////////////////////// 	   
  
u8 *rom_file;
u8*const nes_caption_tbl[GUI_LANGUAGE_NUM]={"NES模拟器","NES模擬器","NES Emulator",};

u8*const nes_remindmsg_tbl[GUI_LANGUAGE_NUM]=
{
"1,P8:PB10接COM3_RX,PB11接COM3_TX\r\
2,K1:打到JOYPAD档\r\
3,将手柄插入COM3接口\r\
4,退出本应用后，请恢复原来的设置！",
"1,P8:PB10接COM3_RX,PB11接COM3_TX\r\
2,K1:打到JOYPAD檔\r\
3,將手柄插入COM3接口\r\
4,退出本應用後，請恢復原來的設置！",
"1,P8:PB10-COM3_RX,PB11-COM3_TX\r\
2,K1:Turn to JOYPAD\r\
3,Insert GAMEPAD to COM3\r\
4,Exit,restore the orig settings",
}; 
//错误提示
u8*const nes_errormsg_tbl[3][GUI_LANGUAGE_NUM]=
{
{"内存不够!","內存不夠!","Out of memory!",},
{"文件读取错误!","文件讀取錯誤!","Read file error!",},
{"MAP不支持!","MAP不支持!","Not supported MAP!",},
};

//加载游戏界面
void nes_load_ui(void)
{	
	app_filebrower((u8*)nes_caption_tbl[gui_phy.language],0X05);//显示标题 
  	gui_fill_rectangle(0,20,lcddev.width,lcddev.height-20,BLACK);//填充底色 		    	  
} 
//NES游戏
u8 nes_play(void)
{
  	DIR nesdir;		//nesdir专用	  
	FILINFO nesinfo;	 	   
	u8 res;
	u8 rval=0;			//返回值	  
	u8 *pname=0;
	u8 *fn;	
  
 	_btn_obj* rbtn;		//返回按钮控件
   	_filelistbox_obj * flistbox;
	_filelistbox_list * filelistx; 	//文件 	
	
	app_muti_remind_msg((lcddev.width-210)/2,(lcddev.height-158)/2,210,158,APP_REMIND_CAPTION_TBL[gui_phy.language],nes_remindmsg_tbl[gui_phy.language]);
	LCD_Clear(BLACK); 
	app_filebrower((u8*)APP_MFUNS_CAPTION_TBL[6][gui_phy.language],0X07);	//选择目标文件,并得到目标数量
   	flistbox=filelistbox_creat(0,gui_phy.tbheight,lcddev.width,lcddev.height-gui_phy.tbheight*2,1,gui_phy.listfsize);//创建一个filelistbox
 	if(flistbox==NULL)rval=1;							//申请内存失败.
	else  
	{
		flistbox->fliter=FLBOX_FLT_NES;	//查找文本文件
		filelistbox_add_disk(flistbox);	//添加磁盘路径
		filelistbox_draw_listbox(flistbox);
	}
	//为长文件名申请缓存区
 	nesinfo.lfsize=_MAX_LFN*2+1;
	nesinfo.lfname=gui_memin_malloc(nesinfo.lfsize);
	if(nesinfo.lfname==NULL)rval=1;//申请内存失败 
   	else gui_memset((u8*)nesinfo.lfname,0,nesinfo.lfsize); 
	rbtn=btn_creat(lcddev.width-2*gui_phy.tbfsize-8-1,lcddev.height-gui_phy.tbheight,2*gui_phy.tbfsize+8,gui_phy.tbheight-1,0,0x03);//创建文字按钮
 	if(rbtn==NULL)rval=1;	//没有足够内存够分配
	else
	{
	 	rbtn->caption=(u8*)GUI_BACK_CAPTION_TBL[gui_phy.language];//返回 
	 	rbtn->font=gui_phy.tbfsize;//设置新的字体大小	 	 
		rbtn->bcfdcolor=WHITE;	//按下时的颜色
		rbtn->bcfucolor=WHITE;	//松开时的颜色
		btn_draw(rbtn);//画按钮
	}   
   	while(rval==0)
	{
		tp_dev.scan(0);    
		in_obj.get_key(&tp_dev,IN_TYPE_TOUCH);	//得到按键键值   
		delay_ms(5);
		if(system_task_return)break;	  		//TPAD返回
 		filelistbox_check(flistbox,&in_obj);	//扫描文件
		res=btn_check(rbtn,&in_obj);
		if(res)
		{
			if(((rbtn->sta&0X80)==0))//按钮状态改变了
			{
				if(flistbox->dbclick!=0X81)
				{
 					filelistx=filelist_search(flistbox->list,flistbox->selindex);//得到此时选中的list的信息
					if(filelistx->type==FICO_DISK)//已经不能再往上了
					{				 
						break;
					}else filelistbox_back(flistbox);//退回上一层目录	 
				} 
 			}	 
		}
		if(flistbox->dbclick==0X81)//双击文件了
		{
     		rval=f_opendir(&nesdir,(const TCHAR*)flistbox->path); //打开选中的目录
			if(rval)break;	 			   
			dir_sdi(&nesdir,flistbox->findextbl[flistbox->selindex-flistbox->foldercnt]);
	 		rval=f_readdir(&nesdir,&nesinfo);//读取文件信息
			if(rval)break;//打开成功    
			fn=(u8*)(*nesinfo.lfname?nesinfo.lfname:nesinfo.fname);
			pname=gui_memin_malloc(strlen((const char*)fn)+strlen((const char*)flistbox->path)+2);//申请内存
			if(pname==NULL)rval=1;//申请失败
			else
			{
				pname=gui_path_name(pname,flistbox->path,fn);//文件名加入路径  
				if(audiodev.status&(1<<7))		//当前在放歌??
				{
					audio_stop_req(&audiodev);	//停止音频播放
					audio_task_delete();		//删除音乐播放任务.
					delay_ms(1010);
				}  				
				LCD_Clear(BLACK); 
				app_filebrower(fn,0X05);//显示当前正在玩的游戏名字
 				//非1963/9341/5510/5310驱动LCD的LCD,降速
				if(lcddev.id!=0X1963&&lcddev.id!=0X9341&&lcddev.id!=0X5510&&lcddev.id!=0X5310)
				{
					FSMC_Bank1E->BWTR[6]&=0XFFFFFFF0;//清除之前的设置
					FSMC_Bank1E->BWTR[6]|=3<<0;	//地址建立时间（ADDSET）为4个HCLK  	 	 
				}
				//SRAM设置
				FSMC_Bank1->BTCR[5]&=0XFFFF00FF;//清除之前的设置
				FSMC_Bank1->BTCR[5]|=7<<8;		//数据保持时间（DATAST）为8个HCLK 8/128M=62.5ns	 	 
				USART3->CR1&=~(1<<5);			//禁止串口3接收（此时不再处理SIM900A相关信息）
 				//开始nes游戏
				res=nes_load(pname);			//开始nes游戏
 				if(res)
				{
					window_msg_box((lcddev.width-220)/2,(lcddev.height-100)/2,220,100,(u8*)nes_errormsg_tbl[res-1][gui_phy.language],(u8*)APP_REMIND_CAPTION_TBL[gui_phy.language],12,0,0,0);
					delay_ms(1200); 
				}
				//非1963/9341/5510/5310驱动LCD的LCD,恢复
				if(lcddev.id!=0X1963&&lcddev.id!=0X9341&&lcddev.id!=0X5510&&lcddev.id!=0X5310)
				{
					FSMC_Bank1E->BWTR[6]&=0XFFFFFFF0;//清除之前的设置
 					FSMC_Bank1E->BWTR[6]|=0<<0;	//地址建立时间（ADDSET）为1个HCLK  	 	 
				}
				//SRAM设置
				FSMC_Bank1->BTCR[5]&=0XFFFF00FF;//清除之前的设置
				FSMC_Bank1->BTCR[5]|=3<<8;		//数据保持时间（DATAST）为7个HCLK 7/128M=55ns	 	 
 				system_task_return=0;			//退出标志清零
				usart3_init(36,115200);			//恢复串口3功能
  			}	       
			flistbox->dbclick=0;				//设置非文件浏览状态
			gui_memin_free(pname);				//释放内存		  
		    pname=NULL;
			app_filebrower((u8*)nes_caption_tbl[gui_phy.language],0X07);//选择目标文件,并得到目标数量
			btn_draw(rbtn);//画按钮
			delay_ms(100);
			filelistbox_rebuild_filelist(flistbox);//重建flistbox
 			system_task_return=0;	//刚刚退出正在玩的游戏,还不能退出这个循环
			TPAD_Init(6);			//重新设置TPAD值
		}
	}	
	filelistbox_delete(flistbox);	//删除filelist
	btn_delete(rbtn);				//删除按钮	  	 
	gui_memin_free(pname);			//释放内存		  
 	gui_memin_free(nesinfo.lfname);		 
	return rval;  								  
}






















