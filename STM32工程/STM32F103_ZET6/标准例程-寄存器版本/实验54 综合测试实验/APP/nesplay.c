#include "nesplay.h"
#include "nes_main.h"	 
#include "spb.h"	  
#include "audioplay.h"	
#include "usart3.h"	
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//APP-NESģ���� ����	   
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
  
u8 *rom_file;
u8*const nes_caption_tbl[GUI_LANGUAGE_NUM]={"NESģ����","NESģ�M��","NES Emulator",};

u8*const nes_remindmsg_tbl[GUI_LANGUAGE_NUM]=
{
"1,P8:PB10��COM3_RX,PB11��COM3_TX\r\
2,K1:��JOYPAD��\r\
3,���ֱ�����COM3�ӿ�\r\
4,�˳���Ӧ�ú���ָ�ԭ�������ã�",
"1,P8:PB10��COM3_RX,PB11��COM3_TX\r\
2,K1:��JOYPAD�n\r\
3,���ֱ�����COM3�ӿ�\r\
4,�˳��������ᣬՈ�֏�ԭ����O�ã�",
"1,P8:PB10-COM3_RX,PB11-COM3_TX\r\
2,K1:Turn to JOYPAD\r\
3,Insert GAMEPAD to COM3\r\
4,Exit,restore the orig settings",
}; 
//������ʾ
u8*const nes_errormsg_tbl[3][GUI_LANGUAGE_NUM]=
{
{"�ڴ治��!","�ȴ治��!","Out of memory!",},
{"�ļ���ȡ����!","�ļ��xȡ�e�`!","Read file error!",},
{"MAP��֧��!","MAP��֧��!","Not supported MAP!",},
};

//������Ϸ����
void nes_load_ui(void)
{	
	app_filebrower((u8*)nes_caption_tbl[gui_phy.language],0X05);//��ʾ���� 
  	gui_fill_rectangle(0,20,lcddev.width,lcddev.height-20,BLACK);//����ɫ 		    	  
} 
//NES��Ϸ
u8 nes_play(void)
{
  	DIR nesdir;		//nesdirר��	  
	FILINFO nesinfo;	 	   
	u8 res;
	u8 rval=0;			//����ֵ	  
	u8 *pname=0;
	u8 *fn;	
  
 	_btn_obj* rbtn;		//���ذ�ť�ؼ�
   	_filelistbox_obj * flistbox;
	_filelistbox_list * filelistx; 	//�ļ� 	
	
	app_muti_remind_msg((lcddev.width-210)/2,(lcddev.height-158)/2,210,158,APP_REMIND_CAPTION_TBL[gui_phy.language],nes_remindmsg_tbl[gui_phy.language]);
	LCD_Clear(BLACK); 
	app_filebrower((u8*)APP_MFUNS_CAPTION_TBL[6][gui_phy.language],0X07);	//ѡ��Ŀ���ļ�,���õ�Ŀ������
   	flistbox=filelistbox_creat(0,gui_phy.tbheight,lcddev.width,lcddev.height-gui_phy.tbheight*2,1,gui_phy.listfsize);//����һ��filelistbox
 	if(flistbox==NULL)rval=1;							//�����ڴ�ʧ��.
	else  
	{
		flistbox->fliter=FLBOX_FLT_NES;	//�����ı��ļ�
		filelistbox_add_disk(flistbox);	//��Ӵ���·��
		filelistbox_draw_listbox(flistbox);
	}
	//Ϊ���ļ������뻺����
 	nesinfo.lfsize=_MAX_LFN*2+1;
	nesinfo.lfname=gui_memin_malloc(nesinfo.lfsize);
	if(nesinfo.lfname==NULL)rval=1;//�����ڴ�ʧ�� 
   	else gui_memset((u8*)nesinfo.lfname,0,nesinfo.lfsize); 
	rbtn=btn_creat(lcddev.width-2*gui_phy.tbfsize-8-1,lcddev.height-gui_phy.tbheight,2*gui_phy.tbfsize+8,gui_phy.tbheight-1,0,0x03);//�������ְ�ť
 	if(rbtn==NULL)rval=1;	//û���㹻�ڴ湻����
	else
	{
	 	rbtn->caption=(u8*)GUI_BACK_CAPTION_TBL[gui_phy.language];//���� 
	 	rbtn->font=gui_phy.tbfsize;//�����µ������С	 	 
		rbtn->bcfdcolor=WHITE;	//����ʱ����ɫ
		rbtn->bcfucolor=WHITE;	//�ɿ�ʱ����ɫ
		btn_draw(rbtn);//����ť
	}   
   	while(rval==0)
	{
		tp_dev.scan(0);    
		in_obj.get_key(&tp_dev,IN_TYPE_TOUCH);	//�õ�������ֵ   
		delay_ms(5);
		if(system_task_return)break;	  		//TPAD����
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
		if(flistbox->dbclick==0X81)//˫���ļ���
		{
     		rval=f_opendir(&nesdir,(const TCHAR*)flistbox->path); //��ѡ�е�Ŀ¼
			if(rval)break;	 			   
			dir_sdi(&nesdir,flistbox->findextbl[flistbox->selindex-flistbox->foldercnt]);
	 		rval=f_readdir(&nesdir,&nesinfo);//��ȡ�ļ���Ϣ
			if(rval)break;//�򿪳ɹ�    
			fn=(u8*)(*nesinfo.lfname?nesinfo.lfname:nesinfo.fname);
			pname=gui_memin_malloc(strlen((const char*)fn)+strlen((const char*)flistbox->path)+2);//�����ڴ�
			if(pname==NULL)rval=1;//����ʧ��
			else
			{
				pname=gui_path_name(pname,flistbox->path,fn);//�ļ�������·��  
				if(audiodev.status&(1<<7))		//��ǰ�ڷŸ�??
				{
					audio_stop_req(&audiodev);	//ֹͣ��Ƶ����
					audio_task_delete();		//ɾ�����ֲ�������.
					delay_ms(1010);
				}  				
				LCD_Clear(BLACK); 
				app_filebrower(fn,0X05);//��ʾ��ǰ���������Ϸ����
 				//��1963/9341/5510/5310����LCD��LCD,����
				if(lcddev.id!=0X1963&&lcddev.id!=0X9341&&lcddev.id!=0X5510&&lcddev.id!=0X5310)
				{
					FSMC_Bank1E->BWTR[6]&=0XFFFFFFF0;//���֮ǰ������
					FSMC_Bank1E->BWTR[6]|=3<<0;	//��ַ����ʱ�䣨ADDSET��Ϊ4��HCLK  	 	 
				}
				//SRAM����
				FSMC_Bank1->BTCR[5]&=0XFFFF00FF;//���֮ǰ������
				FSMC_Bank1->BTCR[5]|=7<<8;		//���ݱ���ʱ�䣨DATAST��Ϊ8��HCLK 8/128M=62.5ns	 	 
				USART3->CR1&=~(1<<5);			//��ֹ����3���գ���ʱ���ٴ���SIM900A�����Ϣ��
 				//��ʼnes��Ϸ
				res=nes_load(pname);			//��ʼnes��Ϸ
 				if(res)
				{
					window_msg_box((lcddev.width-220)/2,(lcddev.height-100)/2,220,100,(u8*)nes_errormsg_tbl[res-1][gui_phy.language],(u8*)APP_REMIND_CAPTION_TBL[gui_phy.language],12,0,0,0);
					delay_ms(1200); 
				}
				//��1963/9341/5510/5310����LCD��LCD,�ָ�
				if(lcddev.id!=0X1963&&lcddev.id!=0X9341&&lcddev.id!=0X5510&&lcddev.id!=0X5310)
				{
					FSMC_Bank1E->BWTR[6]&=0XFFFFFFF0;//���֮ǰ������
 					FSMC_Bank1E->BWTR[6]|=0<<0;	//��ַ����ʱ�䣨ADDSET��Ϊ1��HCLK  	 	 
				}
				//SRAM����
				FSMC_Bank1->BTCR[5]&=0XFFFF00FF;//���֮ǰ������
				FSMC_Bank1->BTCR[5]|=3<<8;		//���ݱ���ʱ�䣨DATAST��Ϊ7��HCLK 7/128M=55ns	 	 
 				system_task_return=0;			//�˳���־����
				usart3_init(36,115200);			//�ָ�����3����
  			}	       
			flistbox->dbclick=0;				//���÷��ļ����״̬
			gui_memin_free(pname);				//�ͷ��ڴ�		  
		    pname=NULL;
			app_filebrower((u8*)nes_caption_tbl[gui_phy.language],0X07);//ѡ��Ŀ���ļ�,���õ�Ŀ������
			btn_draw(rbtn);//����ť
			delay_ms(100);
			filelistbox_rebuild_filelist(flistbox);//�ؽ�flistbox
 			system_task_return=0;	//�ո��˳����������Ϸ,�������˳����ѭ��
			TPAD_Init(6);			//��������TPADֵ
		}
	}	
	filelistbox_delete(flistbox);	//ɾ��filelist
	btn_delete(rbtn);				//ɾ����ť	  	 
	gui_memin_free(pname);			//�ͷ��ڴ�		  
 	gui_memin_free(nesinfo.lfname);		 
	return rval;  								  
}






















