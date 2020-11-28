#ifndef __RECORDER_H
#define __RECORDER_H 	
#include "common.h"
//#include "wavplay.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//APP-¼���� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/7/20
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//*******************************************************************************
//�޸���Ϣ
//��
////////////////////////////////////////////////////////////////////////////////// 	   
 
////////////////////////////////////////////////////////////////////////////////////////////
//��ͼ��/ͼƬ·��
extern u8*const RECORDER_DEMO_PIC;			//demoͼƬ·�� 	      
extern u8*const RECORDER_RECR_PIC;			//¼�� �ɿ�
extern u8*const RECORDER_RECP_PIC;			//¼�� ����
extern u8*const RECORDER_PAUSER_PIC;		//��ͣ �ɿ�
extern u8*const RECORDER_PAUSEP_PIC;		//��ͣ ����
extern u8*const RECORDER_STOPR_PIC;			//ֹͣ �ɿ�
extern u8*const RECORDER_STOPP_PIC;			//ֹͣ ����
////////////////////////////////////////////////////////////////////////////////////////////
 //RIFF��
typedef __packed struct
{
    u32 ChunkID;		   	//chunk id;����̶�Ϊ"RIFF",��0X46464952
    u32 ChunkSize ;		   	//���ϴ�С;�ļ��ܴ�С-8
    u32 Format;	   			//��ʽ;WAVE,��0X45564157
}ChunkRIFF ;
//fmt��
typedef __packed struct
{
    u32 ChunkID;		   	//chunk id;����̶�Ϊ"fmt ",��0X20746D66
    u32 ChunkSize ;		   	//�Ӽ��ϴ�С(������ID��Size);����Ϊ:20.
    u16 AudioFormat;	  	//��Ƶ��ʽ;0X10,��ʾ����PCM;0X11��ʾIMA ADPCM
	u16 NumOfChannels;		//ͨ������;1,��ʾ������;2,��ʾ˫����;
	u32 SampleRate;			//������;0X1F40,��ʾ8Khz
	u32 ByteRate;			//�ֽ�����; 
	u16 BlockAlign;			//�����(�ֽ�); 
	u16 BitsPerSample;		//�����������ݴ�С;4λADPCM,����Ϊ4
//	u16 ByteExtraData;		//���ӵ������ֽ�;2��; ����PCM,û���������
//	u16 ExtraData;			//���ӵ�����,�����������ݿ��С;0X1F9:505�ֽ�  ����PCM,û���������
}ChunkFMT;	   
//fact�� 
typedef __packed struct 
{
    u32 ChunkID;		   	//chunk id;����̶�Ϊ"fact",��0X74636166;
    u32 ChunkSize ;		   	//�Ӽ��ϴ�С(������ID��Size);����Ϊ:4.
    u32 NumOfSamples;	  	//����������; 
}ChunkFACT;
//data�� 
typedef __packed struct 
{
    u32 ChunkID;		   	//chunk id;����̶�Ϊ"data",��0X61746164
    u32 ChunkSize ;		   	//�Ӽ��ϴ�С(������ID��Size);�ļ���С-60.
}ChunkDATA;

//wavͷ
typedef __packed struct
{ 
	ChunkRIFF riff;	//riff��
	ChunkFMT fmt;  	//fmt��
	//ChunkFACT fact;	//fact�� ����PCM,û������ṹ��	 
	ChunkDATA data;	//data��		 
}__WaveHeader; 
	 		
void recorder_enter_rec_mode(void);
void recorder_wav_init(__WaveHeader* wavhead);//��ʼ��WAVͷ	
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























