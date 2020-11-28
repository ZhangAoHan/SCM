#ifndef __RECORDER_H
#define __RECORDER_H 	
#include "common.h"
//#include "wavplay.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//APP-录音机 代码	   
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
 
////////////////////////////////////////////////////////////////////////////////////////////
//各图标/图片路径
extern u8*const RECORDER_DEMO_PIC;			//demo图片路径 	      
extern u8*const RECORDER_RECR_PIC;			//录音 松开
extern u8*const RECORDER_RECP_PIC;			//录音 按下
extern u8*const RECORDER_PAUSER_PIC;		//暂停 松开
extern u8*const RECORDER_PAUSEP_PIC;		//暂停 按下
extern u8*const RECORDER_STOPR_PIC;			//停止 松开
extern u8*const RECORDER_STOPP_PIC;			//停止 按下
////////////////////////////////////////////////////////////////////////////////////////////
 //RIFF块
typedef __packed struct
{
    u32 ChunkID;		   	//chunk id;这里固定为"RIFF",即0X46464952
    u32 ChunkSize ;		   	//集合大小;文件总大小-8
    u32 Format;	   			//格式;WAVE,即0X45564157
}ChunkRIFF ;
//fmt块
typedef __packed struct
{
    u32 ChunkID;		   	//chunk id;这里固定为"fmt ",即0X20746D66
    u32 ChunkSize ;		   	//子集合大小(不包括ID和Size);这里为:20.
    u16 AudioFormat;	  	//音频格式;0X10,表示线性PCM;0X11表示IMA ADPCM
	u16 NumOfChannels;		//通道数量;1,表示单声道;2,表示双声道;
	u32 SampleRate;			//采样率;0X1F40,表示8Khz
	u32 ByteRate;			//字节速率; 
	u16 BlockAlign;			//块对齐(字节); 
	u16 BitsPerSample;		//单个采样数据大小;4位ADPCM,设置为4
//	u16 ByteExtraData;		//附加的数据字节;2个; 线性PCM,没有这个参数
//	u16 ExtraData;			//附加的数据,单个采样数据块大小;0X1F9:505字节  线性PCM,没有这个参数
}ChunkFMT;	   
//fact块 
typedef __packed struct 
{
    u32 ChunkID;		   	//chunk id;这里固定为"fact",即0X74636166;
    u32 ChunkSize ;		   	//子集合大小(不包括ID和Size);这里为:4.
    u32 NumOfSamples;	  	//采样的数量; 
}ChunkFACT;
//data块 
typedef __packed struct 
{
    u32 ChunkID;		   	//chunk id;这里固定为"data",即0X61746164
    u32 ChunkSize ;		   	//子集合大小(不包括ID和Size);文件大小-60.
}ChunkDATA;

//wav头
typedef __packed struct
{ 
	ChunkRIFF riff;	//riff块
	ChunkFMT fmt;  	//fmt块
	//ChunkFACT fact;	//fact块 线性PCM,没有这个结构体	 
	ChunkDATA data;	//data块		 
}__WaveHeader; 
	 		
void recorder_enter_rec_mode(void);
void recorder_wav_init(__WaveHeader* wavhead);//初始化WAV头	
void recoder_set_agc(u16 agc);
u16 recorder_read_data(u8 address);
u8 recorder_vu_get(u16 signallevel);
void recorder_vu_meter(u16 x,u16 y,u8 level);
void recorder_show_time(u16 x,u16 y,u32 tsec);
void recorder_show_name(u16 x,u16 y,u8 *name);
void recorder_show_samplerate(u16 x,u16 y,u16 samplerate);
void recorder_load_ui(void);
void recorder_new_pathname(u8 *pname);
void recorder_show_agc(u16 x,u16 y,u8 agc);
u8 recorder_agc_set(u16 x,u16 y,u8 *agc,u8*caption);
u8 recorder_play(void);		   			   
#endif























