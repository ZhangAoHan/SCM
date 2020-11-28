#include "tomcatplay.h"
#include "recorder.h"
#include "vs10xx.h"
#include "audioplay.h"
#include "spb.h"
#include "settings.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//APP-TOMè ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2014/2/16
//�汾��V1.1
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//*******************************************************************************
//V1.1 20140216
//�����Ը��ֱַ���LCD��֧��.
////////////////////////////////////////////////////////////////////////////////// 	   


#define TOMCAT_TITLE_COLOR   	0XFFFF		//¼����������ɫ	
#define TOMCAT_TITLE_BKCOLOR	0X0000		//¼�������ⱳ��ɫ	
															    

#define TOMCAT_TIME_COLOR    	0X07FF		//ʱ����ɫ
#define TOMCAT_MAIN_BKCOLOR		0X18E3  	//������ɫ

//������Ƕ����ɫ
#define TOMCAT_INWIN_FONT_COLOR	0X736C		//0XAD53		


//ͨ����������2������,���Կ��Ƽ�������������Ⱥ�Ч��.
//��������һ�δ���TOMCAT_START_LEVELʱ,����¼��.����������
//һ��ʱ������TOMCAT_STOP_LEVEL��ʱ��,ֹͣ¼��,����ʼ����.
#define TOMCAT_STOP_LEVEL		3			//ֹͣ��ֵ
#define TOMCAT_START_LEVEL		5			//������ֵ

 			   
u8*const TOMCAT_DEMO_PIC="1:/SYSTEM/APP/TOMCAT/Demo.bmp";//demoͼƬ·�� 	      
 
//���}
u8*const tomcat_caption_tbl[GUI_LANGUAGE_NUM]={"��˵����è","���fԒ��؈","Talking TOM",};
u8*const tomcat_set_tbl[GUI_LANGUAGE_NUM]={"���漰��������","���漰�Z���O��","GAIN AND SPEED SET"};	      

//����tom cat������UI	  
void tomcat_load_ui(void)
{	
 	gui_fill_rectangle(0,0,lcddev.width,gui_phy.tbheight,TOMCAT_TITLE_BKCOLOR);				//��䱳��ɫ
	gui_show_strmid(0,0,lcddev.width,gui_phy.tbheight,TOMCAT_TITLE_COLOR,gui_phy.tbfsize,(u8*)tomcat_caption_tbl[gui_phy.language]);//��ʾ����
 	gui_fill_rectangle(0,gui_phy.tbheight,lcddev.width,lcddev.height-gui_phy.tbheight,TOMCAT_MAIN_BKCOLOR);//����ɫ 
 	minibmp_decode((u8*)TOMCAT_DEMO_PIC,(lcddev.width-100)/2,100+(lcddev.height-320)/2,100,100,0,0);//����100*100��ͼƬDEMO
 	recorder_vu_meter((lcddev.width-218)/2,(lcddev.height-100)/2+100,0);					//��ʾvu meter;
	app_gui_tcbar(0,lcddev.height-gui_phy.tbheight,lcddev.width,gui_phy.tbheight,0x01);		//�Ϸֽ��� 
}  	
//��ʾAGC��С
//x,y:����
//spd:����ֵ 4000~16000;
void tomcat_show_spd(u16 x,u16 y,u16 spd)
{
	gui_phy.back_color=APP_WIN_BACK_COLOR;						//���ñ���ɫΪ��ɫ
	gui_fill_rectangle(x,y,30,12,APP_WIN_BACK_COLOR);			//��䱳��ɫ 
 	gui_show_num(x,y,5,TOMCAT_INWIN_FONT_COLOR,12,spd,0X80);	//��ʾ��ֵ	
} 
//AGC�벥���ٶ����ý���.�̶��ߴ�:180*158    
//x,y:���Ͻ�����
//agc:�Զ�����ָ��	1~10
//speed:�ٶ�ָ�� 	0~24->(8~32)*500K
//caption:��������				  
//����ֵ:0,�ɹ�����;
//    ����,����������
u8 tomcat_agcspd_set(u16 x,u16 y,u8 *agc,u16 *speed,u8*caption)
{
 	u8 rval=0,res;
   	_window_obj* twin=0;			//����
 	_btn_obj * rbtn=0;				//ȡ����ť		  
 	_btn_obj * okbtn=0;				//ȷ����ť		  
	_progressbar_obj * agcprgb;		//AGC���ý�����
 	_progressbar_obj * speedprgb;	//�ٶ����ý�����
	u8 tempagc=0;
	u16 tempspd=*speed;

	if(*agc)tempagc=*agc-1;
	
  	twin=window_creat(x,y,180,158,0,1|1<<5,16);			//�������� ��
 	agcprgb=progressbar_creat(x+10,y+52,160,15,0X20);	//����������
	if(agcprgb==NULL)rval=1;
 	speedprgb=progressbar_creat(x+10,y+52+35,160,15,0X20);	//����������
	if(agcprgb==NULL)rval=1;
  	okbtn=btn_creat(x+20,y+118,60,30,0,0x02);		//������ť
 	rbtn=btn_creat(x+20+60+20,y+118,60,30,0,0x02);	//������ť
	if(twin==NULL||rbtn==NULL||okbtn==NULL||rval)rval=1;
	else
	{
		//���ڵ����ֺͱ���ɫ
		twin->caption=caption;
		twin->windowbkc=APP_WIN_BACK_COLOR;	
		//���ذ�ť����ɫ    
		rbtn->bkctbl[0]=0X8452;		//�߿���ɫ
		rbtn->bkctbl[1]=0XAD97;		//��һ�е���ɫ				
		rbtn->bkctbl[2]=0XAD97;		//�ϰ벿����ɫ
		rbtn->bkctbl[3]=0X8452;		//�°벿����ɫ
		okbtn->bkctbl[0]=0X8452;	//�߿���ɫ
		okbtn->bkctbl[1]=0XAD97;	//��һ�е���ɫ				
		okbtn->bkctbl[2]=0XAD97;	//�ϰ벿����ɫ
		okbtn->bkctbl[3]=0X8452;	//�°벿����ɫ

		agcprgb->totallen=9;		//���AGCΪ9(0~9,��Ӧ1~10�����汶��)
	   	agcprgb->curpos=tempagc;	//��ǰ�ߴ�

		speedprgb->totallen=24;		//���SPEEDΪ24(0~24,��Ӧ(8~32)*500K�Ĳ�����)
	   	speedprgb->curpos=tempspd;	//��ǰ�ߴ�

		rbtn->caption=(u8*)GUI_CANCEL_CAPTION_TBL[gui_phy.language];	//����Ϊȡ��
 		okbtn->caption=(u8*)GUI_OK_CAPTION_TBL[gui_phy.language];		//����Ϊȷ��
  		window_draw(twin);				//��������
		btn_draw(rbtn);					//����ť
		btn_draw(okbtn);				//����ť
		progressbar_draw_progressbar(agcprgb);
  		progressbar_draw_progressbar(speedprgb);
 		gui_show_string("AGC:",x+10,y+38,24,12,12,TOMCAT_INWIN_FONT_COLOR);//��ʾSIZE
		recorder_show_agc(x+10+24,y+38,tempagc+1);
 		gui_show_string("SPEED:     Hz",x+10,y+38+35,84,12,12,TOMCAT_INWIN_FONT_COLOR);//��ʾSIZE
 		tomcat_show_spd(x+10+36,y+38+35,(tempspd+8)*500);	//��ʾ�ٶ�
 		while(rval==0)
		{
			tp_dev.scan(0);    
			in_obj.get_key(&tp_dev,IN_TYPE_TOUCH);	//�õ�������ֵ   
			delay_ms(1000/OS_TICKS_PER_SEC);		//��ʱһ��ʱ�ӽ���
			if(system_task_return)break;			//TPAD����
			res=btn_check(rbtn,&in_obj);			//ȡ����ť���
			if(res&&((rbtn->sta&0X80)==0))			//����Ч����
			{
				rval=1;
				break;//�˳�
			}
			res=btn_check(okbtn,&in_obj); 			//ȷ�ϰ�ť���
			if(res&&((okbtn->sta&0X80)==0))			//����Ч����
			{
				rval=0XFF;		   
				break;//ȷ����
			}	  	  
			res=progressbar_check(agcprgb,&in_obj);
 			if(res&&(tempagc!=agcprgb->curpos))	//�������Ķ���
			{
				tempagc=agcprgb->curpos;		//�������µĽ��  
 				recorder_show_agc(x+10+24,y+38,tempagc+1);
				VS_WR_Cmd(SPI_AICTRL1,1024*(tempagc+1));//��������,0,�Զ�����.1024�൱��1��,512�൱��0.5��,���ֵ65535=64��	
 			} 	
 			res=progressbar_check(speedprgb,&in_obj);
 			if(res&&(tempspd!=speedprgb->curpos))	//�������Ķ���
			{
				tempspd=speedprgb->curpos;		//�������µĽ��  
  				tomcat_show_spd(x+10+36,y+38+35,(tempspd+8)*500);	//��ʾ�ٶ�  
			} 	
		}
	}
	window_delete(twin);			//ɾ������
	btn_delete(rbtn);				//ɾ����ť	
	btn_delete(okbtn);				//ɾ����ť	
	progressbar_delete(agcprgb);	//ɾ��������  
	progressbar_delete(speedprgb);	//ɾ��������  
	system_task_return=0;		 

	if(rval==0XFF)
	{
		*agc=tempagc+1;
		*speed=tempspd;
		return 0;
 	}
	return rval;
}
//����¼��ģʽ(����)
void tomcat_rec_mode(u8 agc)
{ 
	recorder_enter_rec_mode();	
	recoder_set_agc(agc);
 	while(VS_RD_Reg(SPI_HDAT1)>>8);		//�ȵ�buf ��Ϊ�����ٿ�ʼ  
} 
//����wav�ļ�
void tomcat_play_wav(u8 *buf,u32 len)
{
	u32 i=0;
 	VS_HD_Reset();
	VS_Soft_Reset();  		//��λVS1053	   
	VS_Set_Vol(vsset.mvol);	//�������� 
	VS_SPK_Set(1);			//���ư������ȿ���
	do//������ѭ��
    {  	
		if(VS_Send_MusicData(buf+i)==0)//��VS10XX������Ƶ����
		{
			i+=32;
		}else delay_ms(5);				//�������   	    	    
 		if(system_task_return)break; 	//TPAD����
 	}while(i<len);//ѭ����������
}
//�������ݴ���
//�ú���ʵ������fifo����,��buf��size���ȵ�������������dx�ֽ�.
//buf:���ݻ���
//size:���ݳ���
//dx:���Ƶ��ֽ���
void tomcat_data_move(u8* buf,u16 size,u16 dx)
{
	u16 i=0;	    
	for(i=0;i<(size-dx);i++)	
	{
		buf[i]=buf[i+dx];
	}
} 
//tomè��Ϸ
u8 tomcat_play(void)
{
	u8 res;
	u8 rval=0;
	__WaveHeader *wavhead=0;
   	_btn_obj * rbtn=0;				//ȡ����ť		  
 	_btn_obj * mbtn=0;				//ѡ�ť		  
	u8 *mainbuf;					//�������ַ=���ݻ�������С+sizeof(__WaveHeader);
	u8 *databuf;					//���ݻ����׵�ַ	
		  
 	u16 w;				  
	u8 rec_sta=0;				 	//[0]:0,�ȴ�����״̬;1,����¼��;
									
 	u8  vutimecnt=0;		    	//vuɨ��ʱ�������  
 	u16 timecnt=0;					//��ʱ��   
  
	u8 vulevel=0;
	u8 temp;
	short tempval;
	u16 maxval=0;

	u16 idx=0;
	u32 dcnt=0;		//���ݼ�����			 
	/////////////////////////////////////////
	u8 recagc=4;	//Ĭ��agcΪ4.���Զ�����
	u16 wavspd=18;	//wav�����ٶ�,0~24.��Ӧ8~32��. Ĭ���ٶ�:Ϊ(18+8)*500K	 
	
	mainbuf=gui_memex_malloc(176*1000+sizeof(__WaveHeader));	//����176K+__WaveHeaderͷ���ֽ���,�������11�������
	if(mainbuf==NULL)//�ڴ治��?�ͷ�������ռ���ڴ�,����������
	{
		spb_delete();//�ͷ�SPBռ�õ��ڴ�
		mainbuf=gui_memex_malloc(176*1000+sizeof(__WaveHeader));//����176K+__WaveHeaderͷ���ֽ���,�������11�������
	}
	tomcat_load_ui();		//װ�������� 
	rbtn=btn_creat(lcddev.width-2*gui_phy.tbfsize-8-1,lcddev.height-gui_phy.tbheight,2*gui_phy.tbfsize+8,gui_phy.tbheight-1,0,0x03);//�������ְ�ť
	mbtn=btn_creat(0,lcddev.height-gui_phy.tbheight,2*gui_phy.tbfsize+8,gui_phy.tbheight-1,0,0x03);//�������ְ�ť
	if(mainbuf&&rbtn&&mbtn)
	{ 
	 	rbtn->caption=(u8*)GUI_BACK_CAPTION_TBL[gui_phy.language];		//���� 
	 	rbtn->font=gui_phy.tbfsize;//�����µ������С	 
		rbtn->bcfdcolor=WHITE;	//����ʱ����ɫ
		rbtn->bcfucolor=WHITE;	//�ɿ�ʱ����ɫ
		
	 	mbtn->caption=(u8*)GUI_OPTION_CAPTION_TBL[gui_phy.language];	//ѡ�� 
	 	mbtn->font=gui_phy.tbfsize;//�����µ������С
		mbtn->bcfdcolor=WHITE;	//����ʱ����ɫ
		mbtn->bcfucolor=WHITE;	//�ɿ�ʱ����ɫ
		
		wavhead=(__WaveHeader*)mainbuf;				//��mainbuf���ʼ����ת��Ϊwavͷ����
		databuf=mainbuf+sizeof(__WaveHeader);		//����������wavͷ֮��
		
		btn_draw(rbtn);	
		btn_draw(mbtn);	
		if(audiodev.status&(1<<7))					//��ǰ�ڷŸ�??����ֹͣ
		{
			audio_stop_req(&audiodev);				//ֹͣ��Ƶ����
			audio_task_delete();					//ɾ�����ֲ�������.
		}
		recorder_wav_init(wavhead);					//��ʼ��wav����	
		wavhead->fmt.SampleRate=(wavspd+8)*500;	 	//���ò�����,�Ի�ò�ͬ��Ч��.
		tomcat_rec_mode(recagc);					//����¼��ģʽ	  
		delay_ms(300);
		vutimecnt=240;//�������ݻ�������������8192�ֽڣ�
   	   	while(rval==0)
		{
			tp_dev.scan(0);    
			in_obj.get_key(&tp_dev,IN_TYPE_TOUCH);	//�õ�������ֵ   
			delay_ms(1000/OS_TICKS_PER_SEC);		//��ʱһ��ʱ�ӽ���
			if(system_task_return)break;			//TPAD����
 			res=btn_check(rbtn,&in_obj); 			//��鷵�ذ�ť
			if(res&&((rbtn->sta&(1<<7))==0)&&(rbtn->sta&(1<<6)))
			{ 
				if(rec_sta&0X80)//�������¼��,�򱣴����¼���ļ�
				{
		     	 	break;
				}
				break;//���ذ�ť	 
			}
 			res=btn_check(mbtn,&in_obj); 			//������ð�ť
			if(res&&((mbtn->sta&(1<<7))==0)&&(mbtn->sta&(1<<6)))//�������ý���
			{   
				app_read_bkcolor((lcddev.width-180)/2,(lcddev.height-158)/2,180,158,(u16*)databuf);//��ȡ����ɫ
				res=tomcat_agcspd_set((lcddev.width-180)/2,(lcddev.height-158)/2,&recagc,&wavspd,(u8*)tomcat_set_tbl[gui_phy.language]);//�������������
				if(res==0)
				{
					VS_WR_Cmd(SPI_AICTRL1,1024*recagc);	//��������:1~10
					wavhead->fmt.SampleRate=(wavspd+8)*500;	//���ò�����,�Ի�ò�ͬ��Ч��.
 				}	
				app_recover_bkcolor((lcddev.width-180)/2,(lcddev.height-158)/2,180,158,(u16*)databuf);//�ָ�����ɫ  				  
 				dcnt=0;//ִ����һ�����ݻ���,������ݼ�����
			} 	   		  
	  		w=VS_RD_Reg(SPI_HDAT1);	
			if((w>=256)&&(w<896))
			{
 				idx=0;				   	 
	  			while(idx<256) //һ�ζ�ȡ256��,512�ֽ�
				{	 
		 			w=VS_RD_Reg(SPI_HDAT0);
					tempval=(short)w;
					if(tempval<0)tempval=-tempval;
					if(maxval<tempval)maxval=tempval;
					if(rec_sta)//����¼��
					{
						if(dcnt<(176*1000-1))//��ʼ¼��,�ܼ�¼���Ȳ��ܳ���BUF��С(11����)
						{	    
		 					databuf[dcnt++]=w&0XFF;
							databuf[dcnt++]=w>>8;
						}					
					}else//û�п�ʼ¼����ʱ��,���Ǽ�¼����8192����Ƶ����
					{
						if(dcnt>=8192)//����8192,����512�ֽ�.
						{
							tomcat_data_move(databuf,8192,512);	//��������512�ֽ�
							dcnt-=512;							//�������512�ֽ�	
						}
						if(dcnt<8192)//����8192,������¼
						{	    
		 					databuf[dcnt++]=w&0XFF;
							databuf[dcnt++]=w>>8;   			    
						}
					}
					idx++;
				}	  		      
				vutimecnt++;
				if(vutimecnt==2)//ÿ��ȡ1024�ֽڽ���һ��
				{	 
					vutimecnt=0;
					temp=recorder_vu_get(maxval);
 					if(rec_sta)//����¼��
					{
						if(temp<TOMCAT_STOP_LEVEL)timecnt++;
						else timecnt=0;	 
					}else	//��¼��״̬
					{	  
						if(temp>TOMCAT_START_LEVEL)//�յ���Ч��ƽ
						{		    		
							timecnt=0;//��ռ�ʱ��
							rec_sta=1;//���Ҫ��ʼ¼����.	  
						}
					}

					if(temp>=vulevel)vulevel=temp;
					else if(vulevel)vulevel--; 
 					recorder_vu_meter((lcddev.width-218)/2,(lcddev.height-100)/2+100,vulevel);	//��ʾvu meter;
					maxval=0;							  
	 			}  	 
			}
			if(rec_sta)//����¼��
			{
				if(timecnt>=10)//����0.64��û�м�⵽��Ч��Ƶ
				{  	
					wavhead->riff.ChunkSize=dcnt+36;	//�����ļ��Ĵ�С-8;
			   		wavhead->data.ChunkSize=dcnt;		//���ݴ�С				 
 					tomcat_play_wav(mainbuf,dcnt+sizeof(__WaveHeader));//����¼��
					tomcat_rec_mode(recagc);			//����¼��ģʽ	  
					delay_ms(500);
					dcnt=0;
 				   	timecnt=0;
 					rec_sta=0;
				}
			} 
		}					   
		VS_HD_Reset();	//Ӳ��λVS1003
	}						  
 	gui_memex_free(mainbuf);	  
	btn_delete(rbtn);	 
	btn_delete(mbtn);	 
 	return rval;
}
			   			   


































