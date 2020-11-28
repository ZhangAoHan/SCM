#include "includes.h"		 
#include "audioplay.h"
#include "settings.h"
#include "ucos_ii.h"
#include "mp3player.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//APP-���ֲ����� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/7/10
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//*******************************************************************************
//�޸���Ϣ
//��
////////////////////////////////////////////////////////////////////////////////// 	   

//audio���ſ�����
//_m_audiodev  *audiodev=NULL;
_lyric_obj *lrcdev=NULL;				//��ʿ����� 
//���ֲ��ſ�����
__audiodev audiodev;	 

//AUDIO PLAY����
//�����������ȼ�
#define AUDIO_PLAY_TASK_PRIO       		2 
//���������ջ��С
#define AUDIO_PLAY_STK_SIZE  		    800
//�����ջ�������ڴ����ķ�ʽ��������	
OS_STK * AUDIO_PLAY_TASK_STK;	
//������
void audio_play_task(void *pdata); 
//����������������
OS_EVENT * audiombox;//�¼����ƿ�	
 
////////////////////////////////////////////////////////////////////////////////////

u8*const AUDIO_BTN_PIC_TBL[2][5]=  	//5��ͼƬ��ť��·��
{
{
	"1:/SYSTEM/APP/AUDIO/ListR.bmp",
	"1:/SYSTEM/APP/AUDIO/PrevR.bmp", 
	"1:/SYSTEM/APP/AUDIO/PauseR.bmp", 
	"1:/SYSTEM/APP/AUDIO/NextR.bmp",
	"1:/SYSTEM/APP/AUDIO/ExitR.bmp", 
},
{
	"1:/SYSTEM/APP/AUDIO/ListP.bmp",  
	"1:/SYSTEM/APP/AUDIO/PrevP.bmp",  
	"1:/SYSTEM/APP/AUDIO/PlayP.bmp",  
	"1:/SYSTEM/APP/AUDIO/NextP.bmp", 
	"1:/SYSTEM/APP/AUDIO/ExitP.bmp",  
},
};
u8*const AUDIO_PLAYR_PIC="1:/SYSTEM/APP/AUDIO/PlayR.bmp";		//���� �ɿ�
u8*const AUDIO_PLAYP_PIC="1:/SYSTEM/APP/AUDIO/PlayP.bmp";		//���� ����
u8*const AUDIO_PAUSER_PIC="1:/SYSTEM/APP/AUDIO/PauseR.bmp";		//��ͣ �ɿ�
u8*const AUDIO_PAUSEP_PIC="1:/SYSTEM/APP/AUDIO/PauseP.bmp";		//��ͣ ����

u8*const AUDIO_BACK_PIC[3]=										//����ͼƬ	
{
"1:/SYSTEM/APP/AUDIO/a_240164.jpg",
"1:/SYSTEM/APP/AUDIO/a_320296.jpg",
"1:/SYSTEM/APP/AUDIO/a_480550.jpg",	
};
////////////////////////////////////////////////////////////////////////////////////

 
//��ʼ��Ƶ����
void audio_start(void)
{
	audiodev.status|=1<<1;		//��������
	audiodev.status|=1<<0;		//����ͣ״̬
} 
//ֹͣ��Ƶ����
void audio_stop(void)
{
	audiodev.status&=~(1<<0);	//��ͣλ����
	audiodev.status&=~(1<<1);	//��������
}    
void audio_task_delete(void);
//���ֲ�������,ͨ���������򴴽�
void audio_play_task(void *pdata)
{
	DIR audiodir;			//audiodirר��	  
 	FILINFO audioinfo;	 	   
	u8 rval;	
	u8 *pname=0; 
	u8 res;  		
	VS_HD_Reset();
	VS_Soft_Reset();			 	
	while(audiodev.status&0x80)
	{
		audiodev.curindex=(u32)OSMboxPend(audiombox,0,&rval)-1;	//��������,Ҫ��ȥ1,��Ϊ���͵�ʱ��������1
 		audioinfo.lfsize=_MAX_LFN*2+1;							//���ļ�����󳤶�
		audioinfo.lfname=gui_memin_malloc(audioinfo.lfsize);	//Ϊ���ļ������������ڴ� 
		if(audioinfo.lfname)rval=f_opendir(&audiodir,(const TCHAR*)audiodev.path);	//��ѡ�е�Ŀ¼ 
		while(rval==0)
		{	  	 			   
			ff_enter(audiodir.fs);//����fatfs,��ֹ�����.
			dir_sdi(&audiodir,audiodev.mfindextbl[audiodev.curindex]);
			ff_leave(audiodir.fs);//�˳�fatfs,��������os��
			rval=f_readdir(&audiodir,&audioinfo);//��ȡ�ļ���Ϣ
			if(rval)break;//��ʧ��   
			audiodev.name=(u8*)(*audioinfo.lfname?audioinfo.lfname:audioinfo.fname);
			pname=gui_memin_malloc(strlen((const char*)audiodev.name)+strlen((const char*)audiodev.path)+2);//�����ڴ�
			if(pname==NULL)break;//����ʧ��	    
			pname=gui_path_name(pname,audiodev.path,audiodev.name);	//�ļ�������·��  
			audiodev.status|=1<<5;//����и���
			audiodev.status|=1<<4;//������ڲ������� 
			printf("play:%s\r\n",pname); 
			if((f_typetell(pname)&0X40)==0X40)//����Ƶ�ļ�
			{ 
				res=mp3_play_song(pname);	//���������ļ� 
			}
			gui_memin_free(pname);//�ͷ��ڴ�
			if(res&0X80)printf("audio error:%d\r\n",res); 
			printf("audiodev.status:%d\r\n",audiodev.status);
			if((audiodev.status&(1<<6))==0)//����ֹ����
			{
				if(systemset.audiomode==0)//˳�򲥷�
				{
					if(audiodev.curindex<(audiodev.mfilenum-1))audiodev.curindex++;
					else audiodev.curindex=0;
				}else if(systemset.audiomode==1)//�������
				{						    
					audiodev.curindex=app_get_rand(audiodev.mfilenum);//�õ���һ�׸���������	  
				}else audiodev.curindex=audiodev.curindex;//����ѭ��				
			}else break;   
		}
		printf("audio play over:%d\r\n",audiodev.status);
 		gui_memin_free(audioinfo.lfname);   
		audiodev.status&=~(1<<6);	//����Ѿ��ɹ���ֹ����
		audiodev.status&=~(1<<4);	//��������ֲ���
	}
	audio_task_delete();			//ɾ������ 
} 
///////////////////////////////////////////////////////////////////////////////////////////
//����ֹͣaudio����
//audiodevx:audio�ṹ��
void audio_stop_req(__audiodev *audiodevx)
{
	while(audiodevx->status&(1<<4))	//�ȴ���ֹ���ųɹ�  
	{
		audiodevx->status&=~(1<<1);	//�����������,���˳����ڲ��ŵĽ��� 
		audiodevx->status|=1<<6;	//������ֹ����,ֹͣ�Զ�ѭ��/�������
		delay_ms(10);
	};
	audiodev.status&=~(1<<6);		//�������� 
}   
//�����б�
u8*const MUSIC_LIST[GUI_LANGUAGE_NUM]=
{
	"�����б�","�����б�","MUSIC LIST",
};
 
//audio�ļ����,���ļ��洢����
//audiodevx:audio�ṹ��
//����ֵ:0,��������/�����˳���ť.
//		 1,�ڴ����ʧ��		 
u8 audio_filelist(__audiodev *audiodevx)
{
	FILINFO audioinfo;	 	   
	u8 res;
	u8 rval=0;			//����ֵ	  
  	u16 i;	    						   
 	_btn_obj* rbtn;		//���ذ�ť�ؼ�
 	_btn_obj* qbtn;		//�˳���ť�ؼ�

   	_filelistbox_obj * flistbox;
	_filelistbox_list * filelistx; 	//�ļ�
 	app_filebrower((u8*)MUSIC_LIST[gui_phy.language],0X07);	//ѡ��Ŀ���ļ�,���õ�Ŀ������
 
  	flistbox=filelistbox_creat(0,gui_phy.tbheight,lcddev.width,lcddev.height-gui_phy.tbheight*2,1,gui_phy.listfsize);//����һ��filelistbox
 	if(flistbox==NULL)rval=1;							//�����ڴ�ʧ��.
	else if(audiodevx->path==NULL)  
	{
		flistbox->fliter=FLBOX_FLT_MUSIC;	//���������ļ�
 		filelistbox_add_disk(flistbox);		//��Ӵ���·��
		filelistbox_draw_listbox(flistbox);
	}else
	{
		flistbox->fliter=FLBOX_FLT_MUSIC;		//���������ļ�	 
		flistbox->path=(u8*)gui_memin_malloc(strlen((const char*)audiodevx->path)+1);//Ϊ·�������ڴ�
		strcpy((char *)flistbox->path,(char *)audiodevx->path);//����·��	    
		filelistbox_scan_filelist(flistbox);	//����ɨ���б� 
		flistbox->selindex=flistbox->foldercnt+audiodevx->curindex;//ѡ����ĿΪ��ǰ���ڲ��ŵ���Ŀ
		if(flistbox->scbv->totalitems>flistbox->scbv->itemsperpage)flistbox->scbv->topitem=flistbox->selindex;  
		filelistbox_draw_listbox(flistbox);		//�ػ� 		 
	} 	 		 
	//Ϊ���ļ������뻺����
 	audioinfo.lfsize = _MAX_LFN * 2 + 1;
	audioinfo.lfname = gui_memin_malloc(audioinfo.lfsize);
	if(audioinfo.lfname==NULL)rval=1;//�����ڴ�ʧ�� 
   	else gui_memset((u8 *)audioinfo.lfname,0,audioinfo.lfsize); 
	rbtn=btn_creat(lcddev.width-2*gui_phy.tbfsize-8-1,lcddev.height-gui_phy.tbheight,2*gui_phy.tbfsize+8,gui_phy.tbheight-1,0,0x03);//�������ְ�ť
  	qbtn=btn_creat(0,lcddev.height-gui_phy.tbheight,2*gui_phy.tbfsize+8,gui_phy.tbheight,0,0x03);//�����˳����ְ�ť
	if(rbtn==NULL||qbtn==NULL)rval=1;	//û���㹻�ڴ湻����
	else
	{
	 	rbtn->caption=(u8*)GUI_BACK_CAPTION_TBL[gui_phy.language];	//����
	 	rbtn->font=gui_phy.tbfsize;//�����µ������С	 	 
		rbtn->bcfdcolor=WHITE;	//����ʱ����ɫ
		rbtn->bcfucolor=WHITE;	//�ɿ�ʱ����ɫ
		btn_draw(rbtn);//����ť 
		
	 	qbtn->caption=(u8*)GUI_QUIT_CAPTION_TBL[gui_phy.language];	//����
	 	qbtn->font=gui_phy.tbfsize;//�����µ������С	 
		qbtn->bcfdcolor=WHITE;	//����ʱ����ɫ
		qbtn->bcfucolor=WHITE;	//�ɿ�ʱ����ɫ
		btn_draw(qbtn);//����ť
	}	   
   	while(rval==0)
	{
		tp_dev.scan(0);    
		in_obj.get_key(&tp_dev,IN_TYPE_TOUCH);	//�õ�������ֵ   
		delay_ms(1000/OS_TICKS_PER_SEC);		//��ʱһ��ʱ�ӽ���
		if(system_task_return)break;			//TPAD����
		filelistbox_check(flistbox,&in_obj);	//ɨ���ļ�
		res=btn_check(rbtn,&in_obj);
		if(res)
		{
			if(((rbtn->sta&0X80)==0))//��ť״̬�ı���
			{
				if(flistbox->dbclick!=0X81)
				{
 					filelistx=filelist_search(flistbox->list,flistbox->selindex);//�õ���ʱѡ�е�list����Ϣ
					if(filelistx->type==FICO_DISK)//�Ѿ�������������
					{				 
						break;
					}else filelistbox_back(flistbox);//�˻���һ��Ŀ¼	 
				} 
 			}	 
		}
		res=btn_check(qbtn,&in_obj);
		if(res)
		{
			if(((qbtn->sta&0X80)==0))//��ť״̬�ı���
			{ 
				break;//�˳�
 			}	 
		}   
		if(flistbox->dbclick==0X81)//˫���ļ���
		{											 
			audio_stop_req(audiodevx);
			gui_memin_free(audiodevx->path);		//�ͷ��ڴ�
			gui_memex_free(audiodevx->mfindextbl);	//�ͷ��ڴ�
			audiodevx->path=(u8*)gui_memin_malloc(strlen((const char*)flistbox->path)+1);//Ϊ�µ�·�������ڴ�
			if(audiodevx->path==NULL){rval=1;break;}
			audiodevx->path[0]='\0';//���ʼ���������.
 			strcpy((char *)audiodevx->path,(char *)flistbox->path);
			audiodevx->mfindextbl=(u16*)gui_memex_malloc(flistbox->filecnt*2);//Ϊ�µ�tbl�����ڴ�
			if(audiodevx->mfindextbl==NULL){rval=1;break;}
		    for(i=0;i<flistbox->filecnt;i++)audiodevx->mfindextbl[i]=flistbox->findextbl[i];//����
			audiodevx->mfilenum=flistbox->filecnt;		//��¼�ļ�����	 
			OSMboxPost(audiombox,(void*)(flistbox->selindex-flistbox->foldercnt+1));//��������,��Ϊ���䲻��Ϊ��,������������1
 			flistbox->dbclick=0;
			break;	 							   			   
		}
	}	
	filelistbox_delete(flistbox);	//ɾ��filelist
	btn_delete(qbtn);				//ɾ����ť	  	 
	btn_delete(rbtn);				//ɾ����ť	   
  	gui_memin_free(audioinfo.lfname);	
	if(rval)
	{
		gui_memin_free(audiodevx->path);		//�ͷ��ڴ�
		gui_memex_free(audiodevx->mfindextbl); 	//�ͷ��ڴ�
		gui_memin_free(audiodevx);
 	}	 
 	return rval; 
} 
//audio����������
void audio_load_ui(void)
{	
	u8 aui_tpbar_height=0;	//�����������߶�
	u8 aui_msgbar_height=0;	//��Ϣ���߶�
	u8 aui_prgbar_height=0;	//����������߶�
	u8 aui_btnbar_height=0;	//�ײ���ť���߶� 
	u8 pixpitch=0;
	u8 toffy=0; 
	u8 idx=0;
 	if(lcddev.width==240)
	{
		aui_tpbar_height=20;
		aui_msgbar_height=46;
		aui_prgbar_height=30;
		aui_btnbar_height=60;
		pixpitch=6; 
		idx=0;
	}else if(lcddev.width==320)
	{
		aui_tpbar_height=24;
		aui_msgbar_height=50;
		aui_prgbar_height=30;
		aui_btnbar_height=80;
		pixpitch=20; 
		idx=1;
	}else if(lcddev.width==480)
	{
		aui_tpbar_height=30;
		aui_msgbar_height=60;
		aui_prgbar_height=40;
		aui_btnbar_height=120;
		pixpitch=30; 
		idx=2;
	} 
	gui_fill_rectangle(0,0,lcddev.width,aui_tpbar_height,AUDIO_TITLE_BKCOLOR);	//����������ɫ 
	gui_show_strmid(0,0,lcddev.width,aui_tpbar_height,AUDIO_TITLE_COLOR,16,(u8*)APP_MFUNS_CAPTION_TBL[2][gui_phy.language]);	//��ʾ����
	gui_fill_rectangle(0,aui_tpbar_height,lcddev.width,aui_msgbar_height,AUDIO_MAIN_BKCOLOR);									//�����Ϣ������ɫ   
	toffy=(aui_msgbar_height-44)/2;
	minibmp_decode((u8*)APP_VOL_PIC,pixpitch+2,aui_tpbar_height+20+toffy-2,16,16,0,0);				//��������ͼ��
 	gui_show_string("00%",pixpitch+20,aui_tpbar_height+20+toffy+12,66,12,12,AUDIO_INFO_COLOR); 		//��ʾ����
  	gui_fill_rectangle(0,lcddev.height-aui_btnbar_height-aui_prgbar_height,lcddev.width,aui_prgbar_height,AUDIO_MAIN_BKCOLOR);	//��������������ɫ
	gui_fill_rectangle(0,lcddev.height-aui_btnbar_height,lcddev.width,aui_btnbar_height,AUDIO_BTN_BKCOLOR);						//��䰴ť������ɫ   
	gui_fill_rectangle(0,aui_tpbar_height+aui_msgbar_height,lcddev.width,lcddev.height-aui_tpbar_height-aui_msgbar_height-aui_prgbar_height-aui_btnbar_height,AUDIO_MAIN_BKCOLOR);//����ɫ
 	ai_load_picfile(AUDIO_BACK_PIC[idx],0,aui_tpbar_height+aui_msgbar_height,lcddev.width,lcddev.height-aui_tpbar_height-aui_msgbar_height-aui_prgbar_height-aui_btnbar_height,0);//���ر���ͼƬ
	if(lrcdev!=NULL)audio_lrc_bkcolor_process(lrcdev,0);//��ȡLRC����ɫ 
}
//��ʾ�����ٷֱ�  
//pctx:�ٷֱ�ֵ
void audio_show_vol(u8 pctx)
{
	u16 sx,sy;
	if(lcddev.width==240)
	{
		sx=6+20;
		sy=20+20+1+12; 
	}else if(lcddev.width==320)
	{
		sx=20+20;
		sy=24+20+3+12;  
	}else if(lcddev.width==480)
	{
		sx=30+20;
		sy=30+20+8+12;  
	}
	gui_phy.back_color=AUDIO_MAIN_BKCOLOR;//���ñ���ɫΪ��ɫ
 	gui_fill_rectangle(sx,sy,24,12,AUDIO_MAIN_BKCOLOR);//��䱳��ɫ 
	if(pctx==100)
	{
		gui_show_num(sx,sy,3,AUDIO_INFO_COLOR,12,pctx,0x80);//��ʾ�����ٷֱ�   
		gui_show_ptchar(sx+18,sy,sx+18+6,sy+12,0,AUDIO_INFO_COLOR,12,'%',0);	//��ʾ�ٷֺ�
	}else 
	{
		gui_show_num(sx,sy,2,AUDIO_INFO_COLOR,12,pctx,0x80);//��ʾ�����ٷֱ�   
 		gui_show_ptchar(sx+12,sy,sx+12+6,sy+12,0,AUDIO_INFO_COLOR,12,'%',0);	//��ʾ�ٷֺ�
  	}	 
}  
//��ʾaudio����ʱ��
//sx,sy:��ʼ����
//sec:ʱ��
void audio_time_show(u16 sx,u16 sy,u16 sec)
{
	u16 min;
	min=sec/60;//�õ�������
	if(min>99)min=99;
	sec=sec%60;//�õ������� 
	gui_phy.back_color=AUDIO_MAIN_BKCOLOR;//���ñ���ɫΪ��ɫ
	gui_show_num(sx,sy,2,AUDIO_INFO_COLOR,12,min,0x80);//��ʾʱ��
	gui_show_ptchar(sx+12,sy,lcddev.width,lcddev.height,0,AUDIO_INFO_COLOR,12,':',0);//��ʾð��
	gui_show_num(sx+18,sy,2,AUDIO_INFO_COLOR,12,sec,0x80);//��ʾʱ��	  
}
//audiodevx:audio������
//audioprgbx:������
//lrcx:��ʿ�����
void audio_info_upd(__audiodev *audiodevx,_progressbar_obj* audioprgbx,_progressbar_obj* volprgbx,_lyric_obj* lrcx)
{
	static u16 temp;
	u8 aui_tpbar_height;	//�����������߶�
	u8 aui_msgbar_height;	//��Ϣ���߶� 
	u8 pixpitch;
	u8 toffy;
	u16 tempx;
	u8 *buf;
	float ftemp;
	if(lcddev.width==240)
	{
		aui_tpbar_height=20;
		aui_msgbar_height=46;
		pixpitch=6;
	}else if(lcddev.width==320)
	{
		aui_tpbar_height=24;
		aui_msgbar_height=50;
		pixpitch=20;
	}else if(lcddev.width==480)
	{
		aui_tpbar_height=30;
		aui_msgbar_height=60;
		pixpitch=30;
	}
	toffy=(aui_msgbar_height-44)/2;
	if((audiodevx->status&(1<<5))&&(audiodevx->status&(1<<1))&&audiodev.samplerate!=0)//ִ����һ�θ����л�,���������Ѿ��ڲ���������ȷ��ȡ�˲�����,���¸������ֺ͵�ǰ������Ŀ����,audioprgb���ȵ���Ϣ
	{
		audiodevx->status&=~(1<<5);//��ձ�־λ  
		buf=gui_memin_malloc(100);	//����100�ֽ��ڴ�
		if(buf==NULL)return;		//game over   
		gui_fill_rectangle(0,aui_tpbar_height+3,lcddev.width,14,AUDIO_MAIN_BKCOLOR);//���¸������һ��,���֮ǰ����ʾ 
		gui_show_ptstrwhiterim(4,aui_tpbar_height+4,lcddev.width-4,lcddev.height,0,0X0000,0XFFFF,12,audiodevx->name);	//��ʾ�µ�����		
		audiodevx->namelen=strlen((const char*)audiodevx->name);//�õ���ռ�ַ��ĸ���
		audiodevx->namelen*=6;//�õ�����
		audiodevx->curnamepos=0;//�õ�����
		gui_phy.back_color=AUDIO_MAIN_BKCOLOR;//���ñ���ɫΪ��ɫ 
		//��ʾ�����ٷֱ�
		audio_show_vol((volprgbx->curpos*100)/volprgbx->totallen);//��ʾ�����ٷֱ� 			
		//��ʾ��Ŀ���
		sprintf((char*)buf,"%03d/%03d",audiodevx->curindex+1,audiodevx->mfilenum);
		gui_fill_rectangle(pixpitch+20+volprgbx->width-42,aui_tpbar_height+20+toffy+12,42,12,AUDIO_MAIN_BKCOLOR);	//���֮ǰ����ʾ  
		gui_show_string(buf,pixpitch+20+volprgbx->width-42,aui_tpbar_height+20+toffy+12,42,12,12,AUDIO_INFO_COLOR);	
		//��ʾxxxKhz
		tempx=pixpitch*2+20+volprgbx->width+6;//��ʼx����
		gui_fill_rectangle(tempx,aui_tpbar_height+20+toffy,54,12,AUDIO_MAIN_BKCOLOR);		//���֮ǰ����ʾ  
		ftemp=(float)audiodevx->samplerate/1000;//xxx.xKhz 
		sprintf((char*)buf,"%3.1fKhz",ftemp);
		gui_show_string(buf,tempx,aui_tpbar_height+20+toffy,54,12,12,AUDIO_INFO_COLOR);	 
		//��ʾλ��	 	
		tempx=pixpitch*2+20+volprgbx->width+60;//��ʼx����
		gui_fill_rectangle(tempx,aui_tpbar_height+20+toffy,30,12,AUDIO_MAIN_BKCOLOR);		//���֮ǰ����ʾ
		sprintf((char*)buf,"%02dbit",audiodevx->bps); 
		gui_show_string(buf,tempx,aui_tpbar_height+20+toffy,30,12,12,AUDIO_INFO_COLOR);	       
 		//��������
 	 	temp=0;
 		audioprgbx->totallen=audiodevx->file->fsize;	//�����ܳ���	
		audioprgbx->curpos=0;	 
		if(lrcx)
		{
			lrc_read(lrcx,audiodevx->path,audiodevx->name);
			audio_lrc_bkcolor_process(lrcx,1);//�ָ�����ɫ
			lrcdev->curindex=0;	//�������ø��λ��Ϊ0.
			lrcdev->curtime=0;	//����ʱ��
		}
		gui_memin_free(buf);//�ͷ��ڴ�		
	}
	if(audiodevx->namelen>lcddev.width-8)//������Ļ����
	{
		gui_fill_rectangle(0,aui_tpbar_height+3,lcddev.width,14,AUDIO_MAIN_BKCOLOR);//���¸������һ��,���֮ǰ����ʾ 
		gui_show_ptstrwhiterim(4,aui_tpbar_height+4,lcddev.width-4,lcddev.height,audiodevx->curnamepos,0X0000,0XFFFF,12,audiodevx->name);	//��ʾ�µ�����
		audiodevx->curnamepos++;
		if(audiodevx->curnamepos+lcddev.width-8>(audiodevx->namelen+lcddev.width/2-10))audiodevx->curnamepos=0;//ѭ����ʾ		
	}
	if(audiodevx->status&(1<<7))//audio���ڲ���
	{ 
	 	audioprgbx->curpos=f_tell(audiodevx->file);//�õ���ǰ�Ĳ���λ��
		progressbar_draw_progressbar(audioprgbx);//���½�����λ�� 
		if(temp!=audiodevx->cursec)
		{
 			temp=audiodevx->cursec;
			buf=gui_memin_malloc(100);	//����100�ֽ��ڴ�
			if(buf==NULL)return;		//game over   
			//��ʾ����(Kbps )		 
			tempx=pixpitch*2+20+volprgbx->width+6;//��ʼx���� 
			gui_fill_rectangle(tempx,aui_tpbar_height+20+toffy+12,48,12,AUDIO_MAIN_BKCOLOR);	//���֮ǰ����ʾ   
			sprintf((char*)buf,"%04dKbps",audiodevx->bitrate/1000);  
			gui_show_string(buf,tempx,aui_tpbar_height+20+toffy+12,48,12,12,AUDIO_INFO_COLOR);	//��ʾ�ֱ���
			gui_memin_free(buf);		//�ͷ��ڴ�		
 			//��ʾʱ��
			if(lcddev.width==240)
			{
				audio_time_show(5,lcddev.height-48-12-12-9,audiodevx->cursec);			//��ʾ����ʱ��   
				audio_time_show(40+160+5,lcddev.height-48-12-12-9,audiodevx->totsec);	//��ʾ��ʱ��   
			}else if(lcddev.width==320)
			{
				audio_time_show(10,lcddev.height-60-20-12-9,audiodevx->cursec);			//��ʾ����ʱ��   
				audio_time_show(45+230+5,lcddev.height-60-20-12-9,audiodevx->totsec);	//��ʾ��ʱ��   
			}else if(lcddev.width==480)
			{
				audio_time_show(30,lcddev.height-80-40-12-14,audiodevx->cursec);		//��ʾ����ʱ��   
				audio_time_show(70+340+10,lcddev.height-80-40-12-14,audiodevx->totsec);	//��ʾ��ʱ��   
			}
		}	    
	}
}
//lrc����ɫ����
//lrcx:��ʿ��ƽṹ��
//mode:0,��ȡ����ɫ
//     1,�ָ�����ɫ
void audio_lrc_bkcolor_process(_lyric_obj* lrcx,u8 mode)
{ 
	u8 lrcdheight;
	u16 sy; 
	u16 i; 
	if(lcddev.width==240)
	{
		lrcdheight=4;
		sy=20+46+(164-8*lrcdheight-112)/2; 
	}else if(lcddev.width==320)
	{
		lrcdheight=6;
		sy=24+50+(296-8*lrcdheight-112)/2; 
	}else if(lcddev.width==480)
	{
		lrcdheight=10;
		sy=30+60+(550-8*lrcdheight-112)/2; 
	}	 
	for(i=0;i<7;i++)
	{
		if(mode==0)//��ȡ����ɫ
		{
			 app_read_bkcolor(20,sy,lcddev.width-40,16,lrcx->lrcbkcolor[i]);
		}else
		{ 
			app_recover_bkcolor(20,sy,lcddev.width-40,16,lrcx->lrcbkcolor[i]);			
		}
		if(i==2||i==3)sy+=16+lrcdheight*2;
		else sy+=16+lrcdheight;		
	} 
}
//��ʾ���
//audiodevx:audio������
//lrcx:��ʿ�����
void audio_lrc_show(__audiodev *audiodevx,_lyric_obj* lrcx)
{
	u8 t;
	u16 temp,temp1;	  
	u16 lrcwidth=lcddev.width-40;
	u8 lrcdheight;
	u16 sy;
	u16 syadd;
	if(lcddev.width==240)
	{
		lrcdheight=4;
		sy=20+46+(164-8*lrcdheight-112)/2; 
	}else if(lcddev.width==320)
	{
		lrcdheight=6;
		sy=24+50+(296-8*lrcdheight-112)/2; 
	}else if(lcddev.width==480)
	{
		lrcdheight=10;
		sy=30+60+(550-8*lrcdheight-112)/2; 
	}
	if(lrcx->oldostime!=GUI_TIMER_10MS)//ÿ10ms����һ��
	{
		t=gui_disabs(GUI_TIMER_10MS,lrcx->oldostime);//��ֹ�ܾ�û�н����������µ�©��
		lrcx->oldostime=GUI_TIMER_10MS;
		if(t>10)t=1;
		lrcx->curtime+=t;//����10ms	 
		if(lrcx->indexsize)//�и�ʴ��� 
		{
			lrcx->detatime+=t;//��־ʱ��������10ms
			if(lrcx->curindex<lrcx->indexsize)//��û��ʾ��
			{
	 			if((lrcx->curtime%100)>80)//1���Ӻ����800ms,��Ҫ��ѯ����ʱ��Ĵ�����ͬ�����
				{							 	 
					lrcx->curtime=audiodevx->cursec*100;//��������
				}
				if(lrcx->curtime>=lrcx->time_tbl[lrcx->curindex])//��ǰʱ�䳬����,��Ҫ���¸��
				{   
					syadd=sy;
					temp1=lrcx->curindex;//���ݵ�ǰlrcx->curindex.
					if(lrcx->curindex>=3)
					{
						lrcx->curindex-=3;
						temp=0;
					}else 
					{
						temp=3-lrcx->curindex;
						lrcx->curindex=0;
					}
					for(t=0;t<7;t++)	//��ʾ7�����
					{
						if(t!=3)lrcx->color=AUDIO_LRC_SCOLOR;
						else lrcx->color=AUDIO_LRC_MCOLOR;
						
						app_recover_bkcolor(20,syadd,lcddev.width-40,16,lrcx->lrcbkcolor[t]);//�ָ�����ɫ  
						if(lrcx->curindex<=(lrcx->indexsize-1)&&lrcx->curindex>=temp)
						{
							lrc_show_linelrc(lrcx,20,syadd,lrcwidth,16);//��ʾ���
							lrcx->curindex++;
						}
						if(temp)temp--;
						if(t==2||t==3)syadd+=16+lrcdheight*2;
						else syadd+=16+lrcdheight;	 
					}
					lrcx->curindex=temp1;//�ָ�ԭ����ֵ
					lrc_show_linelrc(lrcx,0,0,0,0);//��ȡ��ǰ���,���ǲ���ʾ.
					lrcx->curindex++;	//ƫ�Ƶ���һ�����
					if(lrcx->namelen>(lcddev.width-40))//��Ҫ�������
					{
						if(lrcx->curindex<lrcx->indexsize)//�������һ���ʻ��Ǵ��ڵ�.
						{
							temp=lrcx->time_tbl[lrcx->curindex-1];//��ǰ��ʵ�ʱ��
							temp1=lrcx->time_tbl[lrcx->curindex]; //��һ���ʵ�ʱ�� 	 	   
							lrcx->updatetime=(temp1-temp)/(lrcx->namelen-150);//����õ��������ʱ��,�������50����λ,��Ϊǰ��ĳ���ִ��ʱ��Ӱ��.
							if(lrcx->updatetime>20)lrcx->updatetime=20;//��󲻳���200ms;
 						}else lrcx->updatetime=5;//Ĭ�Ϲ���ʱ��.50ms	  
					}													   
				}
			}
			if(lrcx->detatime>=lrcx->updatetime)//ÿlrcx->updatetime*10ms������ʾ��ǰ���(�����Ҫ�����Ļ�)
			{			  
				if(lrcx->namelen>(lcddev.width-40))//��������ʾ����,��Ҫ������ʾ������
				{
					syadd=sy+3*16+lrcdheight*4; 
					app_recover_bkcolor(20,syadd,lcddev.width-40,16,lrcx->lrcbkcolor[3]);  
					gui_show_ptstr(20,syadd,lcddev.width-21,lcddev.height,lrcx->curnamepos,AUDIO_LRC_MCOLOR,lrcx->font,lrcx->buf,1);//������ʾ������
					lrcx->curnamepos++;
					if(lrcx->curnamepos+200>lrcx->namelen+50)lrcx->curnamepos=0;//ѭ����ʾ		
				}
				lrcx->detatime=0;		  
			}
		}   
	}
}	 
//����audio task
//����ֵ:0,�ɹ�
//    ����,�������
u8 audio_task_creat(void)
{ 
    OS_CPU_SR cpu_sr=0;
	u8 res;     	 
	u8 i;
	u32 size;
	lrcdev=lrc_creat();									//������ʹ���ṹ��
	if(lrcdev)
	{
		lrcdev->font=16; 
		size=(lcddev.width-40)*16*2;//һ����ʱ������ڴ��С
		for(i=0;i<7;i++)//����7����ʵı���ɫ��
		{
			lrcdev->lrcbkcolor[i]=gui_memex_malloc(size);
			if(lrcdev->lrcbkcolor[i]==NULL)break;
		}
		if(i!=7)//�ڴ�����ʧ��
		{
			audio_task_delete();
			return 2;
		}
	}else return 1;										//����ʧ��
 	AUDIO_PLAY_TASK_STK=gui_memin_malloc(AUDIO_PLAY_STK_SIZE*sizeof(OS_STK));
	if(AUDIO_PLAY_TASK_STK==0)return 1;					//�ڴ�����ʧ��
	audiodev.status=1<<7;								//������Ƶ������������
	OS_ENTER_CRITICAL();//�����ٽ���(�޷����жϴ��)    
	res=OSTaskCreate(audio_play_task,(void *)0,(OS_STK*)&AUDIO_PLAY_TASK_STK[AUDIO_PLAY_STK_SIZE-1],AUDIO_PLAY_TASK_PRIO);						   
	OS_EXIT_CRITICAL();	//�˳��ٽ���(���Ա��жϴ��) 
	return res;
}
//ɾ��audio_task
void audio_task_delete(void)
{
	u8 i;
 	if(audiodev.status==0)return;		//�����Ѿ�ֹͣ��
	audiodev.status=0;					//����ֹͣ 
	gui_memin_free(audiodev.path);		//�ͷ��ڴ�
	gui_memex_free(audiodev.mfindextbl);//�ͷ��ڴ�  
	for(i=0;i<7;i++)//�ͷ��ڴ�
	{
		gui_memex_free(lrcdev->lrcbkcolor[i]); 
	}	
	lrc_delete(lrcdev);					//�ͷŸ����ʾ������ڴ�
	lrcdev=NULL;						//ָ��յ�ַ
	VS_SPK_Set(0);						//�ر�������� 
	VS_Set_Vol(0);						//��������Ϊ0 
	gui_memin_free(AUDIO_PLAY_TASK_STK);//�ͷ��ڴ�
	OSTaskDel(AUDIO_PLAY_TASK_PRIO);	//ɾ�����ֲ�������
}

//audio����
u8 audio_play(void)
{
	u8 i;
	u8 res;
	u8 tcnt=0;
	u8 rval=0;		//1,�ڴ����;2,����,audio��������;3,����,ֹͣaudio����.
 	u16 lastvolpos; 
	_progressbar_obj* audioprgb,*volprgb;
	_btn_obj* tbtn[5];		    
	
	if((audiodev.status&(1<<7))==0)	//��Ƶ���������Ѿ�ɾ��?/��һ�ν���?
	{
		memset(&audiodev,0,sizeof(__audiodev));//audiodev������������.
		res=audio_task_creat();		//�������� 
		if(res==0)res=audio_filelist(&audiodev);//ѡ����Ƶ�ļ����в���
		if(res||audiodev.status==0X80)			//��������ʧ��/�ڴ����ʧ��/û��ѡ����Ƶ����
		{
			audio_task_delete();
			return 1;
		}
		system_task_return=0;
	}else
	{
		audiodev.status|=1<<5;		//ģ��һ���и�,�Ը�������������
	}
 	if(lcddev.width==240)
	{
		audioprgb=progressbar_creat(40,lcddev.height-48-12-10-11,160,12,0X20);		//audio���Ž�����
		if(audioprgb==NULL)rval=1;
		volprgb=progressbar_creat(6+20,20+20+1+1,110,10,0X20);	//������С������
		if(volprgb==NULL)rval=1;	   
		volprgb->totallen=150;	//�����ܳ���,��Ƶ��100~250.ƫ��Ϊ100. 	
	}else if(lcddev.width==320)
	{
		audioprgb=progressbar_creat(45,lcddev.height-60-20-10-11,230,12,0X20);		//audio���Ž�����
		if(audioprgb==NULL)rval=1;
		volprgb=progressbar_creat(20+20,24+20+3+1,150,10,0X20);	//������С������
		if(volprgb==NULL)rval=1;	   
		volprgb->totallen=150;	//�����ܳ���,��Ƶ��100~250.ƫ��Ϊ100.
	}else if(lcddev.width==480)
	{
		audioprgb=progressbar_creat(70,lcddev.height-80-40-10-16,340,12,0X20);		//audio���Ž�����
		if(audioprgb==NULL)rval=1;
		volprgb=progressbar_creat(30+20,30+20+8+1,280,10,0X20);	//������С������
		if(volprgb==NULL)rval=1;	   
		volprgb->totallen=150;	//�����ܳ���,��Ƶ��100~250.ƫ��Ϊ100.
	} 
	if(vsset.mvol>=100&&vsset.mvol<=250)volprgb->curpos=vsset.mvol-100;
	else//��������� 
	{
		vsset.mvol=0;
		volprgb->curpos=0;
	}	  
	lastvolpos=volprgb->curpos;//�趨�����λ��
	for(i=0;i<5;i++)//ѭ������5����ť
	{
		if(lcddev.width==240)tbtn[i]=btn_creat(0+i*48,lcddev.height-48-6,48,48,0,1);			//����ͼƬ��ť
		else if(lcddev.width==320)tbtn[i]=btn_creat(2+i*(60+4),lcddev.height-60-10,60,60,0,1);	//����ͼƬ��ť
		else if(lcddev.width==480)tbtn[i]=btn_creat(8+i*(80+16),lcddev.height-80-20,80,80,0,1);	//����ͼƬ��ť
		if(tbtn[i]==NULL){rval=1;break;}		//����ʧ��.
		tbtn[i]->bcfdcolor=0X2CFF;				//����ʱ�ı���ɫ
		tbtn[i]->bcfucolor=AUDIO_BTN_BKCOLOR;	//�ɿ�ʱ����ɫ 
		tbtn[i]->picbtnpathu=(u8*)AUDIO_BTN_PIC_TBL[0][i];
		tbtn[i]->picbtnpathd=(u8*)AUDIO_BTN_PIC_TBL[1][i];
 		tbtn[i]->sta=0;	 
	}
	if(rval==0)//û�д���
	{
	   	audioprgb->inbkcolora=0x738E;			//Ĭ��ɫ
	 	audioprgb->inbkcolorb=AUDIO_INFO_COLOR;	//Ĭ��ɫ 
	 	audioprgb->infcolora=0X75D;				//Ĭ��ɫ
	 	audioprgb->infcolorb=0X596;				//Ĭ��ɫ  
	   	volprgb->inbkcolora=AUDIO_INFO_COLOR;	//Ĭ��ɫ
	 	volprgb->inbkcolorb=AUDIO_INFO_COLOR;	//Ĭ��ɫ 
	 	volprgb->infcolora=0X75D;				//Ĭ��ɫ
	 	volprgb->infcolorb=0X596;				//Ĭ��ɫ   
		audio_load_ui();//����������
		for(i=0;i<5;i++)btn_draw(tbtn[i]);		//����ť
		tbtn[2]->picbtnpathu=(u8*)AUDIO_PLAYR_PIC;//����һ��֮���Ϊ�����ɿ�״̬
  		progressbar_draw_progressbar(audioprgb);//��������	 
		progressbar_draw_progressbar(volprgb);	//��������
		system_task_return=0;
		tcnt=0;  
		while(rval==0)
		{
			tcnt++;//��ʱ����.
			tp_dev.scan(0);    
			in_obj.get_key(&tp_dev,IN_TYPE_TOUCH);	//�õ�������ֵ   
			delay_ms(1000/OS_TICKS_PER_SEC);		//��ʱһ��ʱ�ӽ���  
			for(i=0;i<5;i++)
			{
				res=btn_check(tbtn[i],&in_obj);	 
				if((res&&((tbtn[i]->sta&(1<<7))==0)&&(tbtn[i]->sta&(1<<6)))||system_task_return)//�а����������ɿ�,����TP�ɿ��˻���TPAD����
				{ 
					if(system_task_return)i=4;//TPAD����
					switch(i)
					{
						case 0://file list
							audio_filelist(&audiodev); 
							//////////////////////////////////////////////////////////////////
							audio_load_ui();//���¼���������
							audiodev.status|=1<<5;//ģ��һ���и�,�Ը�������������
							if(audiodev.status&(1<<0))	//��������?
							{
								tbtn[2]->picbtnpathu=(u8*)AUDIO_PAUSER_PIC;
							}else tbtn[2]->picbtnpathu=(u8*)AUDIO_PLAYR_PIC;
							for(i=0;i<5;i++)btn_draw(tbtn[i]);		//����ť
							if(audiodev.status&(1<<0))	
							{
								tbtn[2]->picbtnpathu=(u8*)AUDIO_PLAYR_PIC;
							}else tbtn[2]->picbtnpathu=(u8*)AUDIO_PAUSER_PIC; 
							progressbar_draw_progressbar(audioprgb);	//��������	 
							progressbar_draw_progressbar(volprgb);	//������
							if(system_task_return)//�ո��˳��ļ����
							{
								delay_ms(100);
								system_task_return=0;
							}		 
							break;
						case 1://��һ��������һ��
						case 3:
							audio_stop_req(&audiodev);
							if(systemset.audiomode==1)//�������
							{						    
								audiodev.curindex=app_get_rand(audiodev.mfilenum);//�õ���һ�׸���������	  
							}else
							{
								if(i==1)//��һ��
								{
									if(audiodev.curindex)audiodev.curindex--;
									else audiodev.curindex=audiodev.mfilenum-1;
								}else
								{
									if(audiodev.curindex<(audiodev.mfilenum-1))audiodev.curindex++;
									else audiodev.curindex=0;
								}
							}
							OSMboxPost(audiombox,(void*)(audiodev.curindex+1));//��������,��Ϊ���䲻��Ϊ��,������������1
							break;
						case 2://����/��ͣ
							if(audiodev.status&(1<<0))//����ͣ
							{ 
								audiodev.status&=~(1<<0);//�����ͣ 
								tbtn[2]->picbtnpathd=(u8*)AUDIO_PLAYP_PIC; 
								tbtn[2]->picbtnpathu=(u8*)AUDIO_PAUSER_PIC;
							}else//��ͣ״̬
							{
								audiodev.status|=1<<0;//ȡ����ͣ 
								tbtn[2]->picbtnpathd=(u8*)AUDIO_PAUSEP_PIC; 
								tbtn[2]->picbtnpathu=(u8*)AUDIO_PLAYR_PIC;
							}
							break;
						case 4://ֹͣ����/����
							if((audiodev.status&(1<<0))==0)//��ͣ״̬�°��˷���
							{		   
								rval=3;//�˳�����,audioֹͣ����
								audio_stop_req(&audiodev);//����ֹͣ����
							}else//��ͣ״̬�°�����,�Ǿ͹ر�audio���Ź���.
							{
								rval=2;//�˳����Ž���,audio��������
							}	 
							break; 
					}
				}  
			}				
			res=progressbar_check(volprgb,&in_obj);//�������������
			if(res&&lastvolpos!=volprgb->curpos)//��������,��λ�ñ仯��.ִ����������
			{		  
				lastvolpos=volprgb->curpos;
				if(volprgb->curpos)vsset.mvol=100+volprgb->curpos;
				else vsset.mvol=0;		
				VS_Set_Vol(vsset.mvol);//��������	 
				audio_show_vol((volprgb->curpos*100)/volprgb->totallen);	//��ʾ�����ٷֱ�   
			}	  
			res=progressbar_check(audioprgb,&in_obj);
			if(res&&((audioprgb->sta&&PRGB_BTN_DOWN)==0))//��������,�����ɿ���,ִ�п������
			{
				//printf("audioprgb->curpos:%d\r\n",audioprgb->curpos);
				lrcdev->curindex=0;	//�������ø��λ��Ϊ0.
				lrcdev->curtime=0;	//����ʱ��
				audioprgb->curpos=audiodev.file_seek(audioprgb->curpos);//������� 
 			}	  
			if((tcnt%20)==0)audio_info_upd(&audiodev,audioprgb,volprgb,lrcdev);//������ʾ��Ϣ,ÿ100msִ��һ��
			if(lrcdev!=NULL&&((audiodev.status&(1<<5))==0)&&(audiodev.status&(1<<7)))//���ڲ���,������ͣ,�Ҹ�ʽṹ������
			{
				audio_lrc_show(&audiodev,lrcdev);	//������ʾ���	  
			}
		}
	} 
 	for(i=0;i<5;i++)btn_delete(tbtn[i]);//ɾ����ť	
	progressbar_delete(audioprgb);
	progressbar_delete(volprgb);
	if(rval==3)//�˳�audio����.�Ҳ���̨����
	{
		audio_task_delete();//ɾ����Ƶ�������� 
	} 		  
	return rval;
}
 











