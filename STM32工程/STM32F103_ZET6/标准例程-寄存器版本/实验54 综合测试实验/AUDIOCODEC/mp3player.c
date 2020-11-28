#include "mp3player.h"
#include "audioplay.h"
#include "vs10xx.h"	 
#include "delay.h" 
#include "key.h"
#include "lcd.h"		 
#include "malloc.h"
#include "text.h"
#include "string.h"
#include "exfuns.h"  
#include "ff.h"   
#include "flac.h"	
#include "usart.h"	
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板V3
//MP3播放驱动 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2015/1/20
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved								  						    								  
//////////////////////////////////////////////////////////////////////////////////

//获取当前播放的信息
//fx：文件指针
void mp3_get_info(FIL*fx)
{
	static u16 temps=0;
	u32 temp;
	temp=VS_Get_DecodeTime();
	if(temp!=temps)
	{
		temps=temp;
		if(audiodev.samplerate==0)		//获取音频采样率
		{
			audiodev.samplerate=VS_RD_Reg(SPI_AUDATA)&0XFFFE;//舍弃最低位
		}
		temp=VS_Get_HeadInfo();			//得到位速 
		temp*=1000;
		if(audiodev.bitrate!=temp)
		{
			audiodev.bitrate=temp;
			audiodev.totsec=fx->fsize/(audiodev.bitrate/8);//重新计算总时间
		}
	}
} 
//得到当前播放时间
//fx:文件指针 
void mp3_get_curtime(FIL*fx)
{ 
	audiodev.cursec=fx->fptr*audiodev.totsec/(fx->fsize);	//当前播放到第多少秒了?	 	
}

//mp3文件快进快退函数
//pos:需要定位到的文件位置
//返回值:当前文件位置(即定位后的结果)
u32 mp3_file_seek(u32 pos)
{
	if(pos>audiodev.file->fsize)
	{
		pos=audiodev.file->fsize;
	}
	f_lseek(audiodev.file,pos);
	return audiodev.file->fptr;
} 
//播放一曲音乐
//fname:MP3文件路径.
//返回值:0,正常播放完成
//[b7]:0,正常状态;1,错误状态
//[b6:0]:b7=0时,表示操作码 
//       b7=1时,表示有错误(这里不判定具体错误,0X80~0XFF,都算是错误)
u8 mp3_play_song(u8 *pname)
{	  
    u16 br;
	u8 res;	  
	u8 *databuf;	   		   
	u16 i=0;   
	u8 t=0;  
 	databuf=(u8*)mymalloc(SRAMIN,4096);	//开辟4096字节的内存区域
	audiodev.file=(FIL*)mymalloc(SRAMIN,sizeof(FIL)); 
	audiodev.file_seek=mp3_file_seek; 
	if(!databuf||!audiodev.file) 		//内存申请失败.
	{
 		myfree(SRAMIN,databuf);
		myfree(SRAMIN,audiodev.file);
		return AP_ERR;		//错误 
	}   
	audiodev.totsec=0;		//总时间清零
	audiodev.cursec=0;		//当前播放时间清零
	audiodev.bitrate=0;		//位速清零
	audiodev.samplerate=0;	//采用率清零
	audiodev.bps=16;		//全部设置为16位 
 	VS_Restart_Play();		//重启播放 
	VS_Set_All();			//设置音量等信息 			 
	VS_Reset_DecodeTime();	//复位解码时间 	  
	res=f_typetell(pname);	//得到文件后缀	 			  	 						 
	if(res==0x4c)			//如果是flac,加载patch
	{	
		VS_Load_Patch((u16*)vs1053b_patch,VS1053B_PATCHLEN);
	}  				 		   		 						  
	res=f_open(audiodev.file,(const TCHAR*)pname,FA_READ);//打开文件	 
	if(res==0)									//打开成功.
	{ 
		audio_start();							//开始播放 
		VS_SPI_SpeedHigh();	//高速						   
		while(res==0)
		{
			res=f_read(audiodev.file,databuf,4096,(UINT*)&br);//读出4096个字节 			
			if(res)			//读数据出错了
			{
				res=AP_ERR;
				break;
			} 
			i=0;
			do				//主播放循环
			{  	
				if(VS_Send_MusicData(databuf+i)==0)//给VS10XX发送音频数据
				{
					i+=32;
				}else   
				{ 
					while(audiodev.status&(1<<1))//正常播放中
					{			 
						t++;
						if(t==40)//200ms更新一次
						{
							mp3_get_info(audiodev.file);  
						} 
						delay_ms(1000/OS_TICKS_PER_SEC);
						mp3_get_curtime(audiodev.file);  
						if(audiodev.status&0X01)break;//没有按下暂停 
					}
					if((audiodev.status&(1<<1))==0)//请求结束播放/播放完成
					{  
						res=AP_NEXT;//跳出上上级循环 
						break;
					}    
				}	    	    
			}while(i<4096);//循环发送4096个字节 
			if(br!=4096||res!=0)
			{
				res=AP_OK;	//播放完成
				break;		//读完了.		  
			} 							 
		}
		audio_stop();	//关闭音频输出
	}else res=AP_ERR;	//错误误	    
	f_close(audiodev.file);				     	 
	myfree(SRAMIN,databuf);	  	 		  	    
	myfree(SRAMIN,audiodev.file);
	return res;
}














