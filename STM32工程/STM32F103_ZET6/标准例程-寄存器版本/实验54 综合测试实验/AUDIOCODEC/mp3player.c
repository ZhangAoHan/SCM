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
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������V3
//MP3�������� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/1/20
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved								  						    								  
//////////////////////////////////////////////////////////////////////////////////

//��ȡ��ǰ���ŵ���Ϣ
//fx���ļ�ָ��
void mp3_get_info(FIL*fx)
{
	static u16 temps=0;
	u32 temp;
	temp=VS_Get_DecodeTime();
	if(temp!=temps)
	{
		temps=temp;
		if(audiodev.samplerate==0)		//��ȡ��Ƶ������
		{
			audiodev.samplerate=VS_RD_Reg(SPI_AUDATA)&0XFFFE;//�������λ
		}
		temp=VS_Get_HeadInfo();			//�õ�λ�� 
		temp*=1000;
		if(audiodev.bitrate!=temp)
		{
			audiodev.bitrate=temp;
			audiodev.totsec=fx->fsize/(audiodev.bitrate/8);//���¼�����ʱ��
		}
	}
} 
//�õ���ǰ����ʱ��
//fx:�ļ�ָ�� 
void mp3_get_curtime(FIL*fx)
{ 
	audiodev.cursec=fx->fptr*audiodev.totsec/(fx->fsize);	//��ǰ���ŵ��ڶ�������?	 	
}

//mp3�ļ�������˺���
//pos:��Ҫ��λ�����ļ�λ��
//����ֵ:��ǰ�ļ�λ��(����λ��Ľ��)
u32 mp3_file_seek(u32 pos)
{
	if(pos>audiodev.file->fsize)
	{
		pos=audiodev.file->fsize;
	}
	f_lseek(audiodev.file,pos);
	return audiodev.file->fptr;
} 
//����һ������
//fname:MP3�ļ�·��.
//����ֵ:0,�����������
//[b7]:0,����״̬;1,����״̬
//[b6:0]:b7=0ʱ,��ʾ������ 
//       b7=1ʱ,��ʾ�д���(���ﲻ�ж��������,0X80~0XFF,�����Ǵ���)
u8 mp3_play_song(u8 *pname)
{	  
    u16 br;
	u8 res;	  
	u8 *databuf;	   		   
	u16 i=0;   
	u8 t=0;  
 	databuf=(u8*)mymalloc(SRAMIN,4096);	//����4096�ֽڵ��ڴ�����
	audiodev.file=(FIL*)mymalloc(SRAMIN,sizeof(FIL)); 
	audiodev.file_seek=mp3_file_seek; 
	if(!databuf||!audiodev.file) 		//�ڴ�����ʧ��.
	{
 		myfree(SRAMIN,databuf);
		myfree(SRAMIN,audiodev.file);
		return AP_ERR;		//���� 
	}   
	audiodev.totsec=0;		//��ʱ������
	audiodev.cursec=0;		//��ǰ����ʱ������
	audiodev.bitrate=0;		//λ������
	audiodev.samplerate=0;	//����������
	audiodev.bps=16;		//ȫ������Ϊ16λ 
 	VS_Restart_Play();		//�������� 
	VS_Set_All();			//������������Ϣ 			 
	VS_Reset_DecodeTime();	//��λ����ʱ�� 	  
	res=f_typetell(pname);	//�õ��ļ���׺	 			  	 						 
	if(res==0x4c)			//�����flac,����patch
	{	
		VS_Load_Patch((u16*)vs1053b_patch,VS1053B_PATCHLEN);
	}  				 		   		 						  
	res=f_open(audiodev.file,(const TCHAR*)pname,FA_READ);//���ļ�	 
	if(res==0)									//�򿪳ɹ�.
	{ 
		audio_start();							//��ʼ���� 
		VS_SPI_SpeedHigh();	//����						   
		while(res==0)
		{
			res=f_read(audiodev.file,databuf,4096,(UINT*)&br);//����4096���ֽ� 			
			if(res)			//�����ݳ�����
			{
				res=AP_ERR;
				break;
			} 
			i=0;
			do				//������ѭ��
			{  	
				if(VS_Send_MusicData(databuf+i)==0)//��VS10XX������Ƶ����
				{
					i+=32;
				}else   
				{ 
					while(audiodev.status&(1<<1))//����������
					{			 
						t++;
						if(t==40)//200ms����һ��
						{
							mp3_get_info(audiodev.file);  
						} 
						delay_ms(1000/OS_TICKS_PER_SEC);
						mp3_get_curtime(audiodev.file);  
						if(audiodev.status&0X01)break;//û�а�����ͣ 
					}
					if((audiodev.status&(1<<1))==0)//�����������/�������
					{  
						res=AP_NEXT;//�������ϼ�ѭ�� 
						break;
					}    
				}	    	    
			}while(i<4096);//ѭ������4096���ֽ� 
			if(br!=4096||res!=0)
			{
				res=AP_OK;	//�������
				break;		//������.		  
			} 							 
		}
		audio_stop();	//�ر���Ƶ���
	}else res=AP_ERR;	//������	    
	f_close(audiodev.file);				     	 
	myfree(SRAMIN,databuf);	  	 		  	    
	myfree(SRAMIN,audiodev.file);
	return res;
}














