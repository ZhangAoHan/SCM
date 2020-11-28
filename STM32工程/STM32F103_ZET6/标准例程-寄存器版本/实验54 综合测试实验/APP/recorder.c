#include "recorder.h"
#include "calendar.h"
#include "audioplay.h"
#include "vs10xx.h" 
#include "spi.h"
#include "settings.h"
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
 

#define RECORDER_TITLE_COLOR   	0XFFFF		//¼����������ɫ	
#define RECORDER_TITLE_BKCOLOR	0X0000		//¼�������ⱳ��ɫ	

#define RECORDER_VU_BKCOLOR    	0X39C7		//VU Meter����ɫ	
#define RECORDER_VU_L1COLOR    	0X07FF		//VU Meter L1ɫ	
#define RECORDER_VU_L2COLOR    	0xFFE0		//VU Meter L2ɫ	
#define RECORDER_VU_L3COLOR    	0xF800		//VU Meter L3ɫ	

#define RECORDER_TIME_COLOR    	0X07FF		//ʱ����ɫ
#define RECORDER_MAIN_BKCOLOR	0X18E3		//������ɫ

//������Ƕ����ɫ
#define RECORDER_INWIN_FONT_COLOR		0X736C		//0XAD53		


u8*const RECORDER_DEMO_PIC="1:/SYSTEM/APP/RECORDER/Demo.bmp";		//demoͼƬ·�� 	      
u8*const RECORDER_RECR_PIC="1:/SYSTEM/APP/RECORDER/RecR.bmp";		//¼�� �ɿ�
u8*const RECORDER_RECP_PIC="1:/SYSTEM/APP/RECORDER/RecP.bmp";		//¼�� ����
u8*const RECORDER_PAUSER_PIC="1:/SYSTEM/APP/RECORDER/PauseR.bmp";	//��ͣ �ɿ�
u8*const RECORDER_PAUSEP_PIC="1:/SYSTEM/APP/RECORDER/PauseP.bmp";	//��ͣ ����
u8*const RECORDER_STOPR_PIC="1:/SYSTEM/APP/RECORDER/StopR.bmp";		//ֹͣ �ɿ�
u8*const RECORDER_STOPP_PIC="1:/SYSTEM/APP/RECORDER/StopP.bmp";		//ֹͣ ����    
//��˷���������
const u8* recoder_set_tbl[GUI_LANGUAGE_NUM]={"��˷���������","�����L�����O��","MIC GAIN SET"};	   
//¼����ʾ��Ϣ
u8*const recorder_remind_tbl[3][GUI_LANGUAGE_NUM]=
{
"�Ƿ񱣴��¼���ļ�?","�Ƿ񱣴�ԓ����ļ�?","Do you want to save?", 
{"����ֹͣ¼��!","Ո��ֹͣ���!","Please stop REC first!",},	  
{"�ڴ治��!!","�ȴ治��!!","Out of memory!",},	 	 
};	
//00������ѡ������
u8*const recorder_modesel_tbl[GUI_LANGUAGE_NUM]=
{
"¼������","����O��","Recorder Set",
};	

//VS1053��WAV¼����bug,���plugin��������������� 							    
const u16 wav_plugin[40]=/* Compressed plugin */ 
{ 
0x0007, 0x0001, 0x8010, 0x0006, 0x001c, 0x3e12, 0xb817, 0x3e14, /* 0 */ 
0xf812, 0x3e01, 0xb811, 0x0007, 0x9717, 0x0020, 0xffd2, 0x0030, /* 8 */ 
0x11d1, 0x3111, 0x8024, 0x3704, 0xc024, 0x3b81, 0x8024, 0x3101, /* 10 */ 
0x8024, 0x3b81, 0x8024, 0x3f04, 0xc024, 0x2808, 0x4800, 0x36f1, /* 18 */ 
0x9811, 0x0007, 0x0001, 0x8028, 0x0006, 0x0002, 0x2a00, 0x040e,  
}; 
//����ADPCM ¼��ģʽ
//agc:0,�Զ�����.1024�൱��1��,512�൱��0.5��,���ֵ65535=64��		  
void recorder_enter_rec_mode(void)
{
	//�����IMA ADPCM,�����ʼ��㹫ʽ����:
 	//������=CLKI/256*d;	
	//����d=0,��2��Ƶ,�ⲿ����Ϊ12.288M.��ôFc=(2*12288000)/256*6=16Khz
	//���������PCM,������ֱ�Ӿ�д����ֵ 
   	VS_WR_Cmd(SPI_BASS,0x0000);     	
	VS_WR_Cmd(SPI_AICTRL0,8000);	//���ò�����,����Ϊ8Khz	
	VS_WR_Cmd(SPI_AICTRL2,0);		//�����������ֵ,0,�������ֵ65536=64X
 	VS_WR_Cmd(SPI_AICTRL3,6);		//��ͨ��(MIC����������)
	VS_WR_Cmd(SPI_CLOCKF,0X2000);	//����VS10XX��ʱ��,MULT:2��Ƶ;ADD:������;CLK:12.288Mhz
	VS_WR_Cmd(SPI_MODE,0x1804);		//MIC,¼������    
 	delay_ms(5);					//�ȴ�����1.35ms 
 	VS_Load_Patch((u16*)wav_plugin,40);//VS1053��WAV¼����Ҫplugin
}  
//����VS1053��AGC
//agc:0,�Զ�����.1~64,��ʾ1~64��		  
void recoder_set_agc(u16 agc)
{
	if(agc>=64)agc=65535;
	else agc*=1024;
	VS_WR_Cmd(SPI_AICTRL1,agc);	//�������� 	
}
//��ʼ��WAVͷ.
//wavhead:wav�ļ�ͷ�ṹ��
void recorder_wav_init(__WaveHeader* wavhead) 	   
{
	wavhead->riff.ChunkID=0X46464952;	//"RIFF"
	wavhead->riff.ChunkSize=0;			//��δȷ��,�����Ҫ����
	wavhead->riff.Format=0X45564157; 	//"WAVE"
	wavhead->fmt.ChunkID=0X20746D66; 	//"fmt "
	wavhead->fmt.ChunkSize=16; 			//��СΪ16���ֽ�
	wavhead->fmt.AudioFormat=0X01; 		//0X01,��ʾPCM;0X01,��ʾIMA ADPCM
 	wavhead->fmt.NumOfChannels=1;		//������
 	wavhead->fmt.SampleRate=8000;		//������,��λ:Hz,
 	wavhead->fmt.ByteRate=wavhead->fmt.SampleRate*2;//�ֽ�����=������*ͨ����*(ADCλ��/8),����ȷ��
 	wavhead->fmt.BlockAlign=2;			//���С=ͨ����*(ADCλ��/8)
 	wavhead->fmt.BitsPerSample=16;		//16λPCM
   	wavhead->data.ChunkID=0X61746164;	//"data"
 	wavhead->data.ChunkSize=0;			//���ݴ�С,����Ҫ����  
} 
//��VS10XX������         
//address���Ĵ�����ַ
//����ֵ��������ֵ
//ע�ⲻҪ�ñ��ٶ�ȡ,�����
u16 recorder_read_data(u8 address)
{ 
	u16 temp=0;    	 
    while(VS_DQ==0);//�ǵȴ�����״̬ 	
	VS_XDCS=1;       
	VS_XCS=0;        
	VS_SPI_ReadWriteByte(VS_READ_COMMAND);	//����VS10XX�Ķ�����
	VS_SPI_ReadWriteByte(address);       	//��ַ
	temp=VS_SPI_ReadWriteByte(0xff); 		//��ȡ���ֽ�
	temp=temp<<8;
	temp+=VS_SPI_ReadWriteByte(0xff); 		//��ȡ���ֽ�
	VS_XCS=1;     
   return temp; 
}   
//��ƽ��ֵ��
const u16 vu_val_tbl[10]={3000,4500,6500,9000,11000,14000,18000,22000,27000,32000};
//���źŵ�ƽ�õ�vu����ֵ
//signallevel:�źŵ�ƽ
//����ֵ:vuֵ
u8 recorder_vu_get(u16 signallevel)
{
	u8 i;
	for(i=10;i>0;i--)
	{
		if(signallevel>=vu_val_tbl[i-1])break;
	}
	return i; 
}
//��ʾVU Meter
//level:0~10;
//x,y:����
void recorder_vu_meter(u16 x,u16 y,u8 level)
{
	u8 i;
	u16 vucolor=RECORDER_VU_L1COLOR;
 	if(level>10)return ;
	if(level==0)
	{
		gui_fill_rectangle(x,y,218,10,RECORDER_VU_BKCOLOR);	//��䱳��ɫ
		return;
	}   
	for(i=0;i<level;i++)
	{
		if(i==9)vucolor=RECORDER_VU_L3COLOR;
		else if(i>5)vucolor=RECORDER_VU_L2COLOR;
		gui_fill_rectangle(x+22*i,y,20,10,vucolor);	//��䱳��ɫ
	}
	if(level<10)gui_fill_rectangle(x+level*22,y,218-level*22,10,RECORDER_VU_BKCOLOR);	//��䱳��ɫ	 
}   
//��ʾ¼��ʱ��
//��ʾ�ߴ�Ϊ:150*60
//x,y:��ַ
//tsec:������.
void recorder_show_time(u16 x,u16 y,u32 tsec)
{
	u8 min;
	if(tsec>=60*100)min=99;
	else min=tsec/60;	 
	gui_phy.back_color=RECORDER_MAIN_BKCOLOR;
	gui_show_num(x,y,2,RECORDER_TIME_COLOR,60,min,0X80);	//XX					   
	gui_show_ptchar(x+60,y,lcddev.width,lcddev.height,0,RECORDER_TIME_COLOR,60,':',0);	//":" 
	gui_show_num(x+90,y,2,RECORDER_TIME_COLOR,60,tsec%60,0X80);	//XX	    	    
} 
//��ʾ����
//x,y:����(��Ҫ��0��ʼ)
//name:����
void recorder_show_name(u16 x,u16 y,u8 *name)
{
 	gui_fill_rectangle(x-1,y-1,lcddev.width,13,RECORDER_MAIN_BKCOLOR);	//��䱳��ɫ
 	gui_show_ptstrwhiterim(x,y,lcddev.width,y+12,0,BLACK,WHITE,12,name); 	  
}
//��ʾ������
//x,y:����(��Ҫ��0��ʼ)
//samplerate:������
void recorder_show_samplerate(u16 x,u16 y,u16 samplerate)
{
	u8 *buf=0;
	float temp;
	temp=(float)samplerate/1000; 
	buf=gui_memin_malloc(60);//�����ڴ�
	if(buf==0)return;
	if(samplerate%1000)sprintf((char*)buf,"%.1fKHz",temp);//��С����
	else sprintf((char*)buf,"%dKHz",samplerate/1000);  
 	gui_fill_rectangle(x,y,42,12,RECORDER_MAIN_BKCOLOR);//��䱳��ɫ
	gui_show_string(buf,x,y,42,12,12,RECORDER_INWIN_FONT_COLOR);//��ʾagc  	  
	gui_memin_free(buf);//�ͷ��ڴ� 
}
//����¼����������UI	  
void recorder_load_ui(void)
{	
 	gui_fill_rectangle(0,0,lcddev.width,gui_phy.tbheight,RECORDER_TITLE_BKCOLOR);				//��䱳��ɫ
	gui_show_strmid(0,0,lcddev.width,gui_phy.tbheight,RECORDER_TITLE_COLOR,gui_phy.tbfsize,(u8*)APP_MFUNS_CAPTION_TBL[11][gui_phy.language]);//��ʾ����
 	gui_fill_rectangle(0,gui_phy.tbheight,lcddev.width,lcddev.height-gui_phy.tbheight,RECORDER_MAIN_BKCOLOR);//����ɫ 
 	minibmp_decode((u8*)RECORDER_DEMO_PIC,(lcddev.width-100)/2,100+(lcddev.height-320)/2,100,100,0,0);//����100*100��ͼƬDEMO
	recorder_vu_meter((lcddev.width-218)/2,(lcddev.height-320)/2+200+5,0);				//��ʾvu meter;
	app_gui_tcbar(0,lcddev.height-gui_phy.tbheight,lcddev.width,gui_phy.tbheight,0x01);	//�Ϸֽ���
}

//ͨ��ʱ���ȡ�ļ���
//������SD������,��֧��FLASH DISK����
//��ϳ�:����"0:RECORDER/REC20120321210633.wav"���ļ���
void recorder_new_pathname(u8 *pname)
{	  
	RTC_Get();
	if(gui_phy.memdevflag&(1<<0))sprintf((char*)pname,"0:RECORDER/REC%04d%02d%02d%02d%02d%02d.wav",calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,calendar.min,calendar.sec);		//��ѡ������SD��
}
//��ʾAGC��С
//x,y:����
//agc:����ֵ 0~15,0,�Զ�����;1~15,�Ŵ���
void recorder_show_agc(u16 x,u16 y,u8 agc)
{ 
	gui_phy.back_color=APP_WIN_BACK_COLOR;					//���ñ���ɫΪ��ɫ
	gui_fill_rectangle(x,y,24,12,APP_WIN_BACK_COLOR);		//��䱳��ɫ 
	if(agc==0)
	{
   		gui_show_string("AUTO",x,y,24,12,12,RECORDER_INWIN_FONT_COLOR);//��ʾagc
	}else
	{
		gui_show_num(x,y,2,RECORDER_INWIN_FONT_COLOR,12,agc,0X80);	//��ʾ��ֵ	
	}
}	
//agc���ý���.�̶��ߴ�:180*122    
//x,y:���Ͻ�����
//agc:�Զ�����ָ��,��Χ:0~15,0,�Զ�����;1~15��Ӧ1~15��
//caption:��������				  
//����ֵ:0,�ɹ�����;
//    ����,����������
u8 recorder_agc_set(u16 x,u16 y,u8 *agc,u8*caption)
{
 	u8 rval=0,res;
   	_window_obj* twin=0;			//����
 	_btn_obj * rbtn=0;				//ȡ����ť		  
 	_btn_obj * okbtn=0;				//ȷ����ť		  
	_progressbar_obj * agcprgb;		//AGC���ý�����
 	u8 tempagc=*agc;

  	twin=window_creat(x,y,180,122,0,1|1<<5,16);			//�������� ��
 	agcprgb=progressbar_creat(x+10,y+52,160,15,0X20);	//����������
	if(agcprgb==NULL)rval=1;
  	okbtn=btn_creat(x+20,y+82,60,30,0,0x02);		//������ť
 	rbtn=btn_creat(x+20+60+20,y+82,60,30,0,0x02);	//������ť
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
		agcprgb->totallen=15;		//���AGCΪ15
	   	agcprgb->curpos=tempagc;	//��ǰ�ߴ� 
		rbtn->caption=(u8*)GUI_CANCEL_CAPTION_TBL[gui_phy.language];	//����Ϊȡ��
 		okbtn->caption=(u8*)GUI_OK_CAPTION_TBL[gui_phy.language];		//����Ϊȷ��
  		window_draw(twin);				//��������
		btn_draw(rbtn);					//����ť
		btn_draw(okbtn);				//����ť
		progressbar_draw_progressbar(agcprgb);
   		gui_show_string("AGC:",x+10,y+38,24,12,12,RECORDER_INWIN_FONT_COLOR);//��ʾSIZE
		recorder_show_agc(x+10+24,y+38,tempagc);
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
 				recorder_show_agc(x+10+24,y+38,tempagc);
				recoder_set_agc(tempagc);		//�������� 
			} 		
 		}
	}
	window_delete(twin);							//ɾ������
	btn_delete(rbtn);								//ɾ����ť	
	btn_delete(okbtn);								//ɾ����ť	
	progressbar_delete(agcprgb);//ɾ��������  
	system_task_return=0;		 
	if(rval==0XFF)
	{
		*agc=tempagc;
		return 0;
 	}
	return rval;
}

//¼����
//����¼���ļ�,��������SD��RECORDER�ļ�����.
u8 recorder_play(void)
{
	u8 res;
	u8 rval=0;
	__WaveHeader *wavhead=0;
	FIL* f_rec=0;			//¼���ļ�	 
	u32 sectorsize=0;
 	_btn_obj * rbtn=0;		//ȡ����ť		  
 	_btn_obj * mbtn=0;		//ѡ�ť	
 	_btn_obj * recbtn=0;	//¼����ť		  
 	_btn_obj * stopbtn=0;	//ֹͣ¼����ť  

 	u16 *pset_bkctbl=0;		//����ʱ����ɫָ��
	u32 recsec=0;			//¼��ʱ��
	
 	u8 *recbuf;				//�����ڴ�
	u8 *pname=0; 	
	u16 w;
	u16 idx=0;
	
	u8 timecnt=0;
	u8 vulevel=0;
 	short tempval;
	u8 temp;
	u16 maxval=0;
	
	u8 rec_sta=0;			//¼��״̬
							//[7]:0,û�п���¼��;1,�Ѿ�����¼��;
							//[6:1]:����
							//[0]:0,����¼��;1,��ͣ¼��;  
  
	u8 recagc=4;			//Ĭ������Ϊ4�� 
	
  	f_rec=(FIL *)gui_memin_malloc(sizeof(FIL));			//����FIL�ֽڵ��ڴ�����  
 	wavhead=(__WaveHeader*)gui_memin_malloc(sizeof(__WaveHeader));//����__WaveHeader�ֽڵ��ڴ����� 
	pname=gui_memin_malloc(60);							//����30���ֽ��ڴ�,����"0:RECORDER/REC20120321210633.wav" 
	recbuf=gui_memin_malloc(512);						//����512�ֽ��ڴ�
	pset_bkctbl=gui_memex_malloc(180*272*2);			//Ϊ����ʱ�ı���ɫ�������ڴ�
	if(!recbuf||!f_rec||!wavhead||!pname||!pset_bkctbl)rval=1;
 	else
	{
		//��������
		res=f_open(f_rec,(const TCHAR*)APP_ASCII_S6030,FA_READ);//���ļ���
		if(res==FR_OK)
		{
			asc2_s6030=(u8*)gui_memex_malloc(f_rec->fsize);	//Ϊ�����忪�ٻ����ַ
			if(asc2_s6030==0)rval=1;
			else 
			{
				res=f_read(f_rec,asc2_s6030,f_rec->fsize,(UINT*)&br);	//һ�ζ�ȡ�����ļ�
 			}
		} 
		if(res)rval=1; 
		recorder_load_ui();			//װ��������
		rbtn=btn_creat(lcddev.width-2*gui_phy.tbfsize-8-1,lcddev.height-gui_phy.tbheight,2*gui_phy.tbfsize+8,gui_phy.tbheight-1,0,0x03);//�������ְ�ť
		mbtn=btn_creat(0,lcddev.height-gui_phy.tbheight,2*gui_phy.tbfsize+8,gui_phy.tbheight-1,0,0x03);//�������ְ�ť
		recbtn=btn_creat((lcddev.width-96)/3,(lcddev.height-320)/2+215+18,48,48,0,1);	//����ͼƬ��ť
		stopbtn=btn_creat((lcddev.width-96)*2/3+48,(lcddev.height-320)/2+215+18,48,48,0,1);//����ͼƬ��ť
		if(!rbtn||!mbtn||!recbtn||!stopbtn)rval=1;//û���㹻�ڴ湻����	
		else
		{																				
			rbtn->caption=(u8*)GUI_BACK_CAPTION_TBL[gui_phy.language];//���� 
			rbtn->font=gui_phy.tbfsize;//�����µ������С	 	 
			rbtn->bcfdcolor=WHITE;	//����ʱ����ɫ
			rbtn->bcfucolor=WHITE;	//�ɿ�ʱ����ɫ
			
			mbtn->caption=(u8*)GUI_OPTION_CAPTION_TBL[gui_phy.language];//���� 
			mbtn->font=gui_phy.tbfsize;//�����µ������С		 
			mbtn->bcfdcolor=WHITE;	//����ʱ����ɫ
			mbtn->bcfucolor=WHITE;	//�ɿ�ʱ����ɫ
			
			recbtn->picbtnpathu=(u8*)RECORDER_RECR_PIC;
			recbtn->picbtnpathd=(u8*)RECORDER_PAUSEP_PIC;
			recbtn->bcfucolor=0X0001;//����䱳��
			recbtn->bcfdcolor=0X0001;//����䱳��
			recbtn->sta=0;	 
			
			stopbtn->picbtnpathu=(u8*)RECORDER_STOPR_PIC;
			stopbtn->picbtnpathd=(u8*)RECORDER_STOPP_PIC;
			stopbtn->bcfucolor=0X0001;//����䱳��
			stopbtn->bcfdcolor=0X0001;//����䱳��
			recbtn->sta=0;	 
		} 
	}
	if(rval==0)
	{    
		if(gui_phy.memdevflag&(1<<0))f_mkdir("0:RECORDER");	//ǿ�ƴ����ļ���,��¼������
 		btn_draw(rbtn);	
		btn_draw(mbtn);	
		btn_draw(recbtn);
		recbtn->picbtnpathu=(u8*)RECORDER_PAUSER_PIC;
		recbtn->picbtnpathd=(u8*)RECORDER_RECP_PIC;	  
		btn_draw(stopbtn);
		if(audiodev.status&(1<<7))		//��ǰ�ڷŸ�??����ֹͣ
		{
			audio_stop_req(&audiodev);	//ֹͣ��Ƶ����
			audio_task_delete();		//ɾ�����ֲ�������.
		}
		rec_sta=0;
		recsec=0; 
		recorder_enter_rec_mode();		//����¼��ģʽ,������AGC
		recorder_show_samplerate((lcddev.width-218)/2,(lcddev.height-320)/2+200+5-15,8000);//��ʾ������
		recoder_set_agc(recagc); 		//��������
   		while(VS_RD_Reg(SPI_HDAT1)>>8);	//�ȵ�buf ��Ϊ�����ٿ�ʼ    		
		recorder_show_time((lcddev.width-150)/2,40+(lcddev.height-320)/2,recsec);//��ʾʱ��
 	   	while(rval==0)
		{
			tp_dev.scan(0);    
			in_obj.get_key(&tp_dev,IN_TYPE_TOUCH);	//�õ�������ֵ    
 			if(system_task_return)break;			//TPAD����
			res=btn_check(rbtn,&in_obj); 			//��鷵�ذ�ť
			if(res&&((rbtn->sta&(1<<7))==0)&&(rbtn->sta&(1<<6)))break;//���ذ�ť
  			res=btn_check(mbtn,&in_obj); 			//������ð�ť
			if(res&&((mbtn->sta&(1<<7))==0)&&(mbtn->sta&(1<<6)))
			{   
				app_read_bkcolor((lcddev.width-180)/2,(lcddev.height-272)/2,180,272,pset_bkctbl);//��ȡ����ɫ
 				res=recorder_agc_set((lcddev.width-180)/2,(lcddev.height-122)/2,&recagc,(u8*)recoder_set_tbl[gui_phy.language]);//����AGC
 				recoder_set_agc(recagc); 			//�������� 
 				app_recover_bkcolor((lcddev.width-180)/2,(lcddev.height-272)/2,180,272,pset_bkctbl);//�ָ�����ɫ  				  
 			}
  			res=btn_check(recbtn,&in_obj); 			//���¼����ť
			if(res&&((recbtn->sta&(1<<7))==0)&&(recbtn->sta&(1<<6)))
			{  
				if(rec_sta&0X01)//ԭ������ͣ,����¼��
				{
					rec_sta&=0XFE;//ȡ����ͣ
					recbtn->picbtnpathu=(u8*)RECORDER_RECR_PIC;
					recbtn->picbtnpathd=(u8*)RECORDER_PAUSEP_PIC;
				}else if(rec_sta&0X80)//�Ѿ���¼����,��ͣ
				{
					rec_sta|=0X01;//��ͣ
					recbtn->picbtnpathu=(u8*)RECORDER_PAUSER_PIC;
					recbtn->picbtnpathd=(u8*)RECORDER_RECP_PIC;
				}else	//��û��ʼ¼�� 
				{
 					rec_sta|=0X80;	//��ʼ¼��
					sectorsize=0;	//�ļ���С����Ϊ0
					recbtn->picbtnpathu=(u8*)RECORDER_RECR_PIC;
					recbtn->picbtnpathd=(u8*)RECORDER_PAUSEP_PIC;	 	 
			 		pname[0]='\0';					//��ӽ�����
					recorder_new_pathname(pname);	//�õ��µ�����
					recorder_show_name(2,gui_phy.tbheight+4,pname);//��ʾ����
			 		recorder_wav_init(wavhead);		//��ʼ��wav����	
					res=f_open(f_rec,(const TCHAR*)pname, FA_CREATE_ALWAYS|FA_WRITE); 
					if(res)//�ļ�����ʧ��
					{
						rec_sta=0;//�����ļ�ʧ��,����¼��
						rval=0XFE;//��ʾ�Ƿ����SD��
					}else res=f_write(f_rec,(const void*)wavhead,sizeof(__WaveHeader),&bw);//д��ͷ����
				}								  
			}
  			res=btn_check(stopbtn,&in_obj); 			//���ֹͣ��ť
			if(res&&((recbtn->sta&(1<<7))==0)&&(recbtn->sta&(1<<6)))
			{
				if(rec_sta&0X80)//��¼��
				{ 
					wavhead->riff.ChunkSize=sectorsize*512+36;	//�����ļ��Ĵ�С-8;
			   		wavhead->data.ChunkSize=sectorsize*512;		//���ݴ�С
					f_lseek(f_rec,0);							//ƫ�Ƶ��ļ�ͷ.
			  		f_write(f_rec,(const void*)wavhead,sizeof(__WaveHeader),&bw);//д��ͷ����
					f_close(f_rec);
					sectorsize=0; 
					recbtn->picbtnpathu=(u8*)RECORDER_RECR_PIC;
					recbtn->picbtnpathd=(u8*)RECORDER_PAUSEP_PIC;
					btn_draw(recbtn);	
					recbtn->picbtnpathu=(u8*)RECORDER_PAUSER_PIC;
					recbtn->picbtnpathd=(u8*)RECORDER_RECP_PIC;	  
				}
				rec_sta=0;
				recsec=0;
				recorder_show_name(2,gui_phy.tbheight+4,"");				//��ʾ����
				recorder_show_time((lcddev.width-150)/2,40+(lcddev.height-320)/2,recsec);//��ʾʱ��
  			}
///////////////////////////////////////////////////////////
//��ȡ����			
			SPI1_SetSpeed(SPI_SPEED_16);		//���õ�����ģʽ,4.5Mhz  
	  		w=recorder_read_data(SPI_HDAT1);	
			if((w>=256)&&(w<896))
			{
 				idx=0;				   	 
	  			while(idx<512) 	//һ�ζ�ȡ512�ֽ�
				{	 
		 			w=recorder_read_data(SPI_HDAT0);
					tempval=(short)w;
					if(tempval<0)tempval=-tempval;
					if(maxval<tempval)maxval=tempval;	    
	 				recbuf[idx++]=w&0XFF;
					recbuf[idx++]=w>>8;
				}	 				      
				timecnt++;
				if((timecnt%2)==0)
				{	 
					temp=recorder_vu_get(maxval);
					if(temp>vulevel)vulevel=temp;
					else if(vulevel)vulevel--;
					recorder_vu_meter((lcddev.width-218)/2,(lcddev.height-320)/2+200+5,vulevel);//��ʾvu meter;
					maxval=0;							  
	 			}  
				if(rec_sta==0X80)//�Ѿ���¼����
				{
	 				res=f_write(f_rec,recbuf,512,&bw);//д���ļ�
					if(res)
					{
						printf("err:%d\r\n",res);
						printf("bw:%d\r\n",bw);
						break;//д�����.	  
					}
					sectorsize++;//����������1,ԼΪ32ms	 
				}			
			}else delay_ms(1000/OS_TICKS_PER_SEC);					//��ʱһ��ʱ�ӽ���
///////////////////////////////////////////////////////////// 
 			if(recsec!=((sectorsize*512)/wavhead->fmt.ByteRate))	//¼��ʱ����ʾ
			{
				recsec=(sectorsize*512)/wavhead->fmt.ByteRate;		//¼��ʱ��
				recorder_show_time((lcddev.width-150)/2,40+(lcddev.height-320)/2,recsec);//��ʾʱ��
			}
		}	 	
	}else
	{
		window_msg_box((lcddev.width-200)/2,(lcddev.height-100)/2,200,100,(u8*)recorder_remind_tbl[2][gui_phy.language],(u8*)APP_REMIND_CAPTION_TBL[gui_phy.language],12,0,0,0);//�ڴ����
		delay_ms(2000);
	}	
	if(rval==0XFE)				//�����ļ�ʧ����,��Ҫ��ʾ�Ƿ����SD��
	{
		window_msg_box((lcddev.width-200)/2,(lcddev.height-100)/2,200,100,(u8*)APP_CREAT_ERR_MSG_TBL[gui_phy.language],(u8*)APP_REMIND_CAPTION_TBL[gui_phy.language],12,0,0,0);//��ʾSD���Ƿ����
		delay_ms(2000);			//�ȴ�2����
 	}
	if(rec_sta&0X80)			//�������¼��,����ʾ�������¼���ļ�
	{
 		res=window_msg_box((lcddev.width-200)/2,(lcddev.height-80)/2,200,80,"",(u8*)recorder_remind_tbl[0][gui_phy.language],12,0,0X03,0);
		if(res==1)//��Ҫ����
		{ 
			wavhead->riff.ChunkSize=sectorsize*512+36;	//�����ļ��Ĵ�С-8;
	   		wavhead->data.ChunkSize=sectorsize*512;		//���ݴ�С
			f_lseek(f_rec,0);							//ƫ�Ƶ��ļ�ͷ.
	  		f_write(f_rec,(const void*)wavhead,sizeof(__WaveHeader),&bw);//д��ͷ����
			f_close(f_rec);
		}
	} 
	VS_HD_Reset();	//Ӳ��λVS1003
	//�ͷ��ڴ�
 	gui_memin_free(recbuf);
 	gui_memin_free(f_rec);
	gui_memin_free(wavhead);  
	gui_memin_free(pname);  
	gui_memex_free(pset_bkctbl);
	gui_memex_free(asc2_s6030);
	asc2_s6030=0;				//����
	btn_delete(rbtn);	 
	btn_delete(mbtn);	 
	btn_delete(recbtn);	 
	btn_delete(stopbtn);	 
	return rval;
}
			   			   


































