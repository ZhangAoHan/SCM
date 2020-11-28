#include "spb.h" 
#include "piclib.h"
#include "touch.h"
#include "delay.h"
#include "string.h"
#include "common.h"
#include "calendar.h"
#include "sim900a.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F103������
//SPBЧ��ʵ�� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/3/6
//�汾��V1.1
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved
//*******************************************************************************
//V1.1 20150322
//����gui_draw_bline����
//�޸����4.3/7��������ͼ����ʾ��ʽ,ֱ��ȫ������DMA,������ٶ�.
////////////////////////////////////////////////////////////////////////////////// 	

//SPB ������
m_spb_dev spbdev; 


//����ͼ·��,���ݲ�ͬ��lcdѡ��ͬ��·��
u8*const spb_bkpic_path_tbl[3][2]=
{
	{
		"1:/SYSTEM/SPB/BACKPIC/left_240224.jpg",
		"1:/SYSTEM/SPB/BACKPIC/right_240224.jpg",	
	},
	{
		"1:/SYSTEM/SPB/BACKPIC/left_320364.jpg",
		"1:/SYSTEM/SPB/BACKPIC/right_320364.jpg",	
	},
	{
		"1:/SYSTEM/SPB/BACKPIC/back_480610.jpg",
		"",	
	},	
};	
//����ͼ���·����
u8*const spb_icos_path_tbl[3][2][8]=
{
{
	{
		"1:/SYSTEM/SPB/ICOS/ebook_56.bmp",
	 	"1:/SYSTEM/SPB/ICOS/picture_56.bmp",	    
	  	"1:/SYSTEM/SPB/ICOS/music_56.bmp",	    
	 	"1:/SYSTEM/SPB/ICOS/tomcat_56.bmp",	    
	 	"1:/SYSTEM/SPB/ICOS/clock_56.bmp",	    
	 	"1:/SYSTEM/SPB/ICOS/set_56.bmp",	    
	  	"1:/SYSTEM/SPB/ICOS/game_56.bmp",		    
	  	"1:/SYSTEM/SPB/ICOS/notepad_56.bmp",  
	},	    
 	{ 
	 	"1:/SYSTEM/SPB/ICOS/setup_56.bmp",	   
		"1:/SYSTEM/SPB/ICOS/paint_56.bmp",
	 	"1:/SYSTEM/SPB/ICOS/camera_56.bmp",	    
	  	"1:/SYSTEM/SPB/ICOS/recorder_56.bmp",	    
	  	"1:/SYSTEM/SPB/ICOS/usb_56.bmp",	    
	 	"1:/SYSTEM/SPB/ICOS/earthnet_56.bmp",
	  	"1:/SYSTEM/SPB/ICOS/wireless_56.bmp",	
	  	"1:/SYSTEM/SPB/ICOS/calc_56.bmp",	  
	},	
},
{
	{
		"1:/SYSTEM/SPB/ICOS/ebook_70.bmp",
	 	"1:/SYSTEM/SPB/ICOS/picture_70.bmp",	    
	  	"1:/SYSTEM/SPB/ICOS/music_70.bmp",	    
	 	"1:/SYSTEM/SPB/ICOS/tomcat_70.bmp",	    
	 	"1:/SYSTEM/SPB/ICOS/clock_70.bmp",	    
	 	"1:/SYSTEM/SPB/ICOS/set_70.bmp",	    
	  	"1:/SYSTEM/SPB/ICOS/game_70.bmp",		    
	  	"1:/SYSTEM/SPB/ICOS/notepad_70.bmp",  
	},	    
 	{ 
	 	"1:/SYSTEM/SPB/ICOS/setup_70.bmp",	   
		"1:/SYSTEM/SPB/ICOS/paint_70.bmp",
	 	"1:/SYSTEM/SPB/ICOS/camera_70.bmp",	    
	  	"1:/SYSTEM/SPB/ICOS/recorder_70.bmp",	    
	  	"1:/SYSTEM/SPB/ICOS/usb_70.bmp",	    
	 	"1:/SYSTEM/SPB/ICOS/earthnet_70.bmp",
	  	"1:/SYSTEM/SPB/ICOS/wireless_70.bmp",	
	  	"1:/SYSTEM/SPB/ICOS/calc_70.bmp",	  
	},	
},
{
	{
		"1:/SYSTEM/SPB/ICOS/ebook_110.bmp",
	 	"1:/SYSTEM/SPB/ICOS/picture_110.bmp",	    
	  	"1:/SYSTEM/SPB/ICOS/music_110.bmp",	    
	 	"1:/SYSTEM/SPB/ICOS/tomcat_110.bmp",	    
	 	"1:/SYSTEM/SPB/ICOS/clock_110.bmp",	    
	 	"1:/SYSTEM/SPB/ICOS/set_110.bmp",	    
	  	"1:/SYSTEM/SPB/ICOS/game_110.bmp",		    
	  	"1:/SYSTEM/SPB/ICOS/notepad_110.bmp",  
	},	    
 	{ 
	 	"1:/SYSTEM/SPB/ICOS/setup_110.bmp",	   
		"1:/SYSTEM/SPB/ICOS/paint_110.bmp",
	 	"1:/SYSTEM/SPB/ICOS/camera_110.bmp",	    
	  	"1:/SYSTEM/SPB/ICOS/recorder_110.bmp",	    
	  	"1:/SYSTEM/SPB/ICOS/usb_110.bmp",	    
	 	"1:/SYSTEM/SPB/ICOS/earthnet_110.bmp",
	  	"1:/SYSTEM/SPB/ICOS/wireless_110.bmp",	
	  	"1:/SYSTEM/SPB/ICOS/calc_110.bmp",	  
	},	
},
};
//������ͼ���·����
u8*const spb_micos_path_tbl[3][3]=
{ 
{
	"1:/SYSTEM/SPB/ICOS/phone_56.bmp",
	"1:/SYSTEM/SPB/ICOS/app_56.bmp",	    
	"1:/SYSTEM/SPB/ICOS/sms_56.bmp",	   
},	    
{ 
	"1:/SYSTEM/SPB/ICOS/phone_70.bmp",
	"1:/SYSTEM/SPB/ICOS/app_70.bmp",	    
	"1:/SYSTEM/SPB/ICOS/sms_70.bmp",  
},	    
{ 
	"1:/SYSTEM/SPB/ICOS/phone_110.bmp",
	"1:/SYSTEM/SPB/ICOS/app_110.bmp",	    
	"1:/SYSTEM/SPB/ICOS/sms_110.bmp",
},	 
};
//����ͼ��ICOS�Ķ�Ӧ��������
u8*const icos_name_tbl[GUI_LANGUAGE_NUM][2][8]=
{
	{
		{
			"����ͼ��","�������","���ֲ���","TOM è",
			"ʱ��","ϵͳ����","FC��Ϸ��","���±�",	   
		},
		{
			"������","��д����","�����","¼����",
			"USB ����","����ͨ��","���ߴ���","������",
		},
	},
	{
		{
			"��ӈD��","���a���","��������","TOM ؈",
			"�r�","ϵ�y�O��","FC�[��C","ӛ�±�",	   
		},
		{
			"�\����","�֌����P","�����","����C ",
			"USB �B��","�W�jͨ��","�o������","Ӌ����",
		},
	},
	{
		{
			"EBOOK","PHOTOS","MUSIC","TOM CAT",
			"TIME","SETTINGS","FC GAMES","NOTEPAD",	   
		},
		{
			"EXE","PAINT","CAMERA","RECODER",
			"USB","ETHERNET","WIRELESS","CALC",
		},
	},
};						  
//��ͼ���Ӧ������
u8*const micos_name_tbl[GUI_LANGUAGE_NUM][3]=
{ 
{
	"����","Ӧ������","����",    
},
{
	"��̖","��������","����", 
}, 
{
	"PHONE","APPS","SMS", 
}, 
}; 
//��ʼ��spb��������	
//����ֵ:0,�����ɹ�
//    ����,�������
u8 spb_init(void)
{
	u16 i,j;
	u8 res=0;
	u8 lcdtype=0;//0,240*320;1,320*480;2,480*800
	memset((void*)&spbdev,0,sizeof(spbdev)); 
	spbdev.selico=0xff; 
	if(lcddev.width==240)	//����240*320��LCD��Ļ
	{ 
		lcdtype=0;
		spbdev.stabarheight=20;
		spbdev.spbheight=224;
		spbdev.spbwidth =240; 
		for(i=0;i<2;i++)
		{
			for(j=0;j<8;j++)
			{
				spbdev.icos[i][j].x=2+(j%4)*60;
				spbdev.icos[i][j].y=spbdev.stabarheight+4+(j/4)*74;
				spbdev.icos[i][j].width=56;//���� ����ͼƬ�Ŀ�ȳߴ�
				spbdev.icos[i][j].height=56+2+12+1;
				spbdev.icos[i][j].path=(u8*)spb_icos_path_tbl[lcdtype][i][j];
				spbdev.icos[i][j].name=(u8*)icos_name_tbl[gui_phy.language][i][j];
 			}
		}
		for(i=0;i<3;i++)
		{
			spbdev.micos[i].x=30+i*60;
			spbdev.micos[i].y=spbdev.stabarheight+spbdev.spbheight+4;
			spbdev.micos[i].width=56;//���� ����ͼƬ�Ŀ�ȳߴ�
			spbdev.micos[i].height=56+12+2;
			spbdev.micos[i].path=(u8*)spb_micos_path_tbl[lcdtype][i];
			spbdev.micos[i].name=(u8*)micos_name_tbl[gui_phy.language][i]; 
		}
	}else if(lcddev.width==320)	//����320*480��LCD��Ļ
	{
		lcdtype=1;
		spbdev.stabarheight=24;
		spbdev.spbheight=364;
		spbdev.spbwidth =320; 
		for(i=0;i<2;i++)
		{
			for(j=0;j<8;j++)
			{
				spbdev.icos[i][j].x=5+(j%4)*80;
				spbdev.icos[i][j].y=spbdev.stabarheight+6+(j/4)*90;
				spbdev.icos[i][j].width=70;//���� ����ͼƬ�Ŀ�ȳߴ�
				spbdev.icos[i][j].height=70+2+12+1;
				spbdev.icos[i][j].path=(u8*)spb_icos_path_tbl[lcdtype][i][j];
				spbdev.icos[i][j].name=(u8*)icos_name_tbl[gui_phy.language][i][j];
 			}
		} 
		for(i=0;i<3;i++)
		{
			spbdev.micos[i].x=40+i*80;
			spbdev.micos[i].y=spbdev.stabarheight+spbdev.spbheight+6;
			spbdev.micos[i].width=70;//���� ����ͼƬ�Ŀ�ȳߴ�
			spbdev.micos[i].height=70+12+2;
			spbdev.micos[i].path=(u8*)spb_micos_path_tbl[lcdtype][i];
			spbdev.micos[i].name=(u8*)micos_name_tbl[gui_phy.language][i]; 
		}	
	}else if(lcddev.width==480)	//����480*800��LCD��Ļ
	{ 
		lcdtype=2;
		spbdev.stabarheight=30;
		spbdev.spbheight=770;
		spbdev.spbwidth =480; 
		for(i=0;i<16;i++)
		{
			spbdev.icos[i/8][i%8].x=5+(i%4)*120;
			spbdev.icos[i/8][i%8].y=spbdev.stabarheight+10+(i/4)*150;
			spbdev.icos[i/8][i%8].width=110;//���� ����ͼƬ�Ŀ�ȳߴ�
			spbdev.icos[i/8][i%8].height=110+6+16+2;
			spbdev.icos[i/8][i%8].path=(u8*)spb_icos_path_tbl[lcdtype][i/8][i%8];
			spbdev.icos[i/8][i%8].name=(u8*)icos_name_tbl[gui_phy.language][i/8][i%8]; 
		} 		
		for(i=0;i<3;i++)
		{
			spbdev.micos[i].x=60+i*120;
			spbdev.micos[i].y=spbdev.stabarheight+610+18;
			spbdev.micos[i].width=110;
			spbdev.micos[i].height=110+16+6;
			spbdev.micos[i].path=(u8*)spb_micos_path_tbl[lcdtype][i];
			spbdev.micos[i].name=(u8*)micos_name_tbl[gui_phy.language][i]; 
		}	
	} 
	//ָ��EX SRAM LCD BUF  
	pic_phy.read_point=slcd_read_point;
	pic_phy.draw_point=slcd_draw_point;	 
	pic_phy.fillcolor=slcd_fill_color; 
	gui_phy.read_point=slcd_read_point;
	gui_phy.draw_point=slcd_draw_point;	 
	if(lcdtype==2)
	{ 
		sramlcdbuf=gui_memex_malloc(lcddev.width*(lcddev.height-spbdev.stabarheight)*2);	//1֡����͹���
		if(sramlcdbuf==NULL)return 1;//����	
		spbdev.frame=0;
		res=ai_load_picfile(spb_bkpic_path_tbl[2][0],0,0,spbdev.spbwidth,610,0);//4.3/7����,ֻ��һ�ű���ͼƬ,�߶�610
		if(res==0)res=spb_load_icos(0);		//����ǰ��ͼ��
		if(res==0)res=spb_load_icos(1);		//���غ��ͼ�� 
		for(i=610;i<spbdev.spbheight;i++)	//��䱳��ɫ
		{
			for(j=0;j<spbdev.spbwidth;j++)slcd_draw_point(j,i,SPB_MICO_BKCOLOR);
		}
		if(res==0)res=spb_load_micos();		//����������ͼ��  
	}else
	{
		sramlcdbuf=gui_memex_malloc(spbdev.spbheight*spbdev.spbheight*4);			//��Ҫ2֡����
		if(sramlcdbuf==NULL)return 1;//����	
		spbdev.frame=0;
		res=ai_load_picfile(spb_bkpic_path_tbl[lcdtype][0],0,0,spbdev.spbwidth,spbdev.spbheight,0);//���ص�һҳ����ͼƬ
		if(res==0)res=spb_load_icos(0);		//���ص�0֡ͼ�� 
		spbdev.frame=1;
		if(res==0)res=ai_load_picfile(spb_bkpic_path_tbl[lcdtype][1],0,0,spbdev.spbwidth,spbdev.spbheight,0);//���صڶ�ҳ����ͼƬ
		if(res==0)res=spb_load_icos(1);		//���ص�1֡ͼ��
	}  
	//ָ��LCD
	pic_phy.read_point=LCD_ReadPoint;
	pic_phy.draw_point=LCD_Fast_DrawPoint;	 
	pic_phy.fillcolor=piclib_fill_color;  
	gui_phy.read_point=LCD_ReadPoint;
	gui_phy.draw_point=LCD_Fast_DrawPoint;
	spbdev.frame=0;//Ĭ���ǵ�0֡
	return 0;
} 
//ɾ��SPB
void spb_delete(void)
{
	memset((void*)&spbdev,0,sizeof(spbdev));
	gui_memex_free(sramlcdbuf);
}
//װ��������ICOS
//frame:֡��� 
//����ֵ:0,�����ɹ�
//    ����,�������
u8 spb_load_icos(u8 frame)
{
	u8 j;
	u8 res=0; 
	u8 fontsize=12;
	for(j=0;j<8;j++)
	{
		res=minibmp_decode(spbdev.icos[frame][j].path,spbdev.icos[frame][j].x,spbdev.icos[frame][j].y-spbdev.stabarheight,spbdev.icos[frame][j].width,spbdev.icos[frame][j].width,0,0);
 		if(res)return 1;
		if(lcddev.width==480)fontsize=16;//4.3������16*16���� 
		gui_show_strmid(spbdev.icos[frame][j].x,spbdev.icos[frame][j].y+spbdev.icos[frame][j].width-spbdev.stabarheight,spbdev.icos[frame][j].width,fontsize,SPB_FONT_COLOR,fontsize,spbdev.icos[frame][j].name);//��ʾ����  
	} 
	return 0;
} 
//װ��������ICOS
//frame:֡��� 
//����ֵ:0,�����ɹ�
//    ����,�������
u8 spb_load_micos(void)
{
	u8 j;
	u8 res=0;  
	u8 fontsize=12;
	u8 stabarheight=0;
	if(lcddev.width!=480)gui_fill_rectangle(0,spbdev.stabarheight+spbdev.spbheight,lcddev.width,lcddev.height-spbdev.stabarheight-spbdev.spbheight,SPB_MICO_BKCOLOR);
	for(j=0;j<3;j++)
	{
		if(lcddev.width==480)
		{
			stabarheight=spbdev.stabarheight;
			fontsize=16;//4.3������16*16���� 
		}
		res=minibmp_decode(spbdev.micos[j].path,spbdev.micos[j].x,spbdev.micos[j].y-stabarheight,spbdev.micos[j].width,spbdev.micos[j].width,0,0);
		if(res)return 1;
		gui_show_strmid(spbdev.micos[j].x,spbdev.micos[j].y-stabarheight+spbdev.micos[j].width,spbdev.micos[j].width,fontsize,SPB_FONT_COLOR,fontsize,spbdev.micos[j].name);//��ʾ����  
	} 
	return 0;
}
//SD��ͼ��
//PCtoLCD2002ȡģ��ʽ:����,����ʽ,˳��
const u8 SPB_SD_ICO[60]=
{
0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xFF,0x00,0x0F,0xFF,0x00,0x0F,0xFF,0x00,0x0F,
0xFF,0x00,0x0F,0xFF,0x00,0x0F,0xFF,0x00,0x0F,0xFF,0x00,0x0F,0xFF,0x00,0x0F,0xFC,
0x00,0x0F,0xFE,0x00,0x0F,0xFF,0x00,0x0F,0xFF,0x00,0x0F,0xFC,0x00,0x0A,0xAC,0x00,
0x0A,0xAC,0x00,0x0A,0xAC,0x00,0x0F,0xFC,0x00,0x00,0x00,0x00,
};
//USB ͼ�� 
//PCtoLCD2002ȡģ��ʽ:����,����ʽ,˳��
const u8 SPB_USB_ICO[60]=
{
0x00,0x00,0x00,0x00,0x60,0x00,0x00,0xF0,0x00,0x01,0xF8,0x00,0x00,0x60,0x00,0x00,
0x67,0x00,0x04,0x67,0x00,0x0E,0x62,0x00,0x0E,0x62,0x00,0x04,0x62,0x00,0x04,0x7C,
0x00,0x06,0x60,0x00,0x03,0xE0,0x00,0x00,0x60,0x00,0x00,0x60,0x00,0x00,0x60,0x00,
0x00,0xF0,0x00,0x00,0xF0,0x00,0x00,0x60,0x00,0x00,0x00,0x00,
}; 
//��ʾgsm�ź�ǿ��,ռ��20*20���ش�С
//x,y:��ʼ����
//signal:�ź�ǿ��,��Χ:0~30
void spb_gsm_signal_show(u16 x,u16 y,u8 signal)
{ 
	u8 t;
	u16 color;
	signal/=5;
	if(signal>5)signal=5;
	for(t=0;t<5;t++)
	{
		if(signal)//���ź�
		{
			signal--;
			color=WHITE;
		}else color=0X6B4D;//���ź�
		gui_fill_rectangle(x+1+t*4,y+20-6-t*3,3,(t+1)*3,color); 
	}
}
//GSMģ�K��ʾ��Ϣ 
u8* const spb_sim900a_msg[GUI_LANGUAGE_NUM][3]=
{
"���ƶ���","�й��ƶ�","�й���ͨ",
"�o�ƄӾW","�Ї��Ƅ�","�Ї�ͨ",
" NO NET ","CHN Mobi","CHN Unic",
}; 
//���¶�����Ϣ����Ϣ����
//clr:0,���������
//    1,�������
void spb_stabar_msg_show(u8 clr)
{ 
	u8 temp; 
	if(clr)
	{
		gui_fill_rectangle(0,0,lcddev.width,spbdev.stabarheight,BLACK);
		gui_show_string("CPU:  %",24+64+20+2+20+2,(spbdev.stabarheight-16)/2,64,16,16,WHITE);//��ʾCPU����
		gui_show_string(":",lcddev.width-42+16,(spbdev.stabarheight-16)/2,8,16,16,WHITE);		//��ʾ':'
  	}
	//SIM900A��Ϣ��ʾ
	spb_gsm_signal_show(2,(spbdev.stabarheight-20)/2,sim900dev.csq);//��ʾ�ź�����
	gui_fill_rectangle(2+20+2,(spbdev.stabarheight-16)/2,64,16,BLACK);
	if(sim900dev.status&(1<<5))
	{
		if(sim900dev.status&(1<<4))temp=2;
		else temp=1;
		gui_show_string(spb_sim900a_msg[gui_phy.language][temp],2+20+2,(spbdev.stabarheight-16)/2,64,16,16,WHITE);//��ʾ��Ӫ������
	}else gui_show_string(spb_sim900a_msg[gui_phy.language][0],2+20+2,(spbdev.stabarheight-16)/2,64,16,16,WHITE);//��ʾ��Ӫ������	
	//����SD����Ϣ 
	if(gui_phy.memdevflag&(1<<0))app_show_mono_icos(24+64+2,(spbdev.stabarheight-20)/2,20,20,(u8*)SPB_SD_ICO,WHITE,BLACK);
	else gui_fill_rectangle(24+64+2,0,20,spbdev.stabarheight,BLACK);
	//��ʾCPUʹ����
	gui_phy.back_color=BLACK;
	temp=OSCPUUsage;
	if(OSCPUUsage>99)temp=99;//�����ʾ��99%
	gui_show_num(24+64+2+20+20+2+32,(spbdev.stabarheight-16)/2,2,WHITE,16,temp,0);//��ʾCPUʹ����
	//��ʾʱ��
	RTC_Get();//����ʱ��
	gui_show_num(lcddev.width-42,(spbdev.stabarheight-16)/2,2,WHITE,16,calendar.hour,0X80);	//��ʾʱ��
	gui_show_num(lcddev.width-2-16,(spbdev.stabarheight-16)/2,2,WHITE,16,calendar.min,0X80);//��ʾ����	
}
extern u8*const sysset_remindmsg_tbl[2][GUI_LANGUAGE_NUM];
//����SPB������UI
//����ֵ:0,�����ɹ�
//    ����,�������
u8 spb_load_mui(void)
{
	u8 res=0;
	if(spbdev.spbheight==0&&spbdev.spbwidth==0)
	{
		LCD_Clear(BLACK);				//����
		window_msg_box((lcddev.width-220)/2,(lcddev.height-100)/2,220,100,(u8*)sysset_remindmsg_tbl[1][gui_phy.language],(u8*)sysset_remindmsg_tbl[0][gui_phy.language],12,0,0,0);
 		res=spb_init(); 
	}
	if(res==0)
	{
		spb_stabar_msg_show(1);			//��ʾ״̬����Ϣ,������к���ʾ
		slcd_frame_show(spbdev.pos);	//��ʾ������ICOS
		if(lcddev.width!=480)res=spb_load_micos();//ֻ��2.8/3.5����Ҫ���¼���micos
	}
	return res;
}
//�ƶ���Ļ
//dir:����,0:����;1,����
//skips:ÿ����Ծ����
//pos:��ʼλ��
void spb_frame_move(u8 dir,u8 skips,u16 pos)
{
	u16 x ;				 
	if(dir)//��Ļ����
	{
		for(x=pos;x>0;)
		{
			if(x>skips)x-=skips;
			else x=0;
			slcd_frame_show(x);
 	 	}
		spbdev.frame=0;		
	}else //��Ļ����
	{
		for(x=pos;x<lcddev.width;)
		{
			x+=skips;
			if(x>lcddev.width)x=lcddev.width;
			slcd_frame_show(x);
 	 	}
		spbdev.frame=1;		
	} 
} 
//���ĳ��micoͼ���ѡ��״̬
//selx:16~18,��ʾ��Ҫ���ѡ��״̬��mico���.
void spb_unsel_micos(u8 selx)
{ 
	u8 fontsize=12;
	if(selx>=16&&selx<19)	//�Ϸ��ı��
	{
		selx-=16;
		gui_fill_rectangle(spbdev.micos[selx].x,spbdev.micos[selx].y,spbdev.micos[selx].width,spbdev.micos[selx].height,SPB_MICO_BKCOLOR); 
		minibmp_decode(spbdev.micos[selx].path,spbdev.micos[selx].x,spbdev.micos[selx].y,spbdev.micos[selx].width,spbdev.micos[selx].width,0,0);
 		if(lcddev.width==480)fontsize=16;//4.3������16*16����
		gui_show_strmid(spbdev.micos[selx].x,spbdev.micos[selx].y+spbdev.micos[selx].width,spbdev.micos[selx].width,fontsize,SPB_FONT_COLOR,fontsize,spbdev.micos[selx].name);//��ʾ����
	}	
}
//����ѡ���ĸ�ͼ��
//sel:0~18����ǰҳ��ѡ��ico 
void spb_set_sel(u8 sel)
{ 
	u8 fontsize=12;
	slcd_frame_show(spbdev.pos);						//ˢ�±���  
	if(lcddev.width!=480)spb_unsel_micos(spbdev.selico);//2.8/3.5����Ҫ�����ͼ��ѡ��״̬
	spbdev.selico=sel;
	if(lcddev.width==480)fontsize=16;//4.3������16*16����
	if(sel<16)
	{
		sel%=8;
		gui_alphablend_area(spbdev.icos[spbdev.frame][sel].x,spbdev.icos[spbdev.frame][sel].y,spbdev.icos[spbdev.frame][sel].width,spbdev.icos[spbdev.frame][sel].height,SPB_ALPHA_COLOR,SPB_ALPHA_VAL);
		if(lcddev.id!=0X1963&&lcddev.id!=0X5510)minibmp_decode(spbdev.icos[spbdev.frame][sel].path,spbdev.icos[spbdev.frame][sel].x,spbdev.icos[spbdev.frame][sel].y,spbdev.icos[spbdev.frame][sel].width,spbdev.icos[spbdev.frame][sel].width,0,0);
		gui_show_strmid(spbdev.icos[spbdev.frame][sel].x,spbdev.icos[spbdev.frame][sel].y+spbdev.icos[spbdev.frame][sel].width,spbdev.icos[spbdev.frame][sel].width,fontsize,SPB_FONT_COLOR,fontsize,spbdev.icos[spbdev.frame][sel].name);//��ʾ����
	}else
	{
		sel-=16;
		gui_alphablend_area(spbdev.micos[sel].x,spbdev.micos[sel].y,spbdev.micos[sel].width,spbdev.micos[sel].height,SPB_ALPHA_COLOR,SPB_ALPHA_VAL); 
		if(lcddev.id!=0X1963&&lcddev.id!=0X5510)minibmp_decode(spbdev.micos[sel].path,spbdev.micos[sel].x,spbdev.micos[sel].y,spbdev.micos[sel].width,spbdev.micos[sel].width,0,0);
		gui_show_strmid(spbdev.micos[sel].x,spbdev.micos[sel].y+spbdev.micos[sel].width,spbdev.micos[sel].width,fontsize,SPB_FONT_COLOR,fontsize,spbdev.micos[sel].name);//��ʾ����
	}
} 
//��Ļ�������������
//����ֵ:0~17,��˫����ͼ����.		    
//       0xff,û���κ�ͼ�걻˫�����߰���
u8 spb_move_chk(void)
{		 
	u8 i=0xff;
	u16 movecnt=0;	//�õ���������
	u8 skips=10;	//Ĭ��ÿ����10������
	tp_dev.scan(0);	//ɨ��										 
	if(lcddev.width==320)skips=15;	//3.5����15������
	if(lcddev.width==480)			//4.3��,��֧�ֻ���,��������
	{
		if(tp_dev.sta&TP_PRES_DOWN)//�а���������
		{ 		  		    
			spbdev.spbsta|=1<<15;				//��ǰ���	    
			spbdev.curxpos=tp_dev.x[0];			//��¼��ǰ����
			spbdev.curypos=tp_dev.y[0];			//��¼��ǰ����	
		}else if(spbdev.spbsta&0x8000)//֮ǰ�а���
		{
			for(i=0;i<19;i++)
			{
				if(i<16)//����icos
				{
					spbdev.frame=i/8;
					if((spbdev.curxpos>spbdev.icos[spbdev.frame][i%8].x)&&(spbdev.curxpos<spbdev.icos[spbdev.frame][i%8].x+spbdev.icos[spbdev.frame][i%8].width)&&(spbdev.curxpos>spbdev.icos[spbdev.frame][i%8].x)&&
					   (spbdev.curypos<spbdev.icos[spbdev.frame][i%8].y+spbdev.icos[spbdev.frame][i%8].height))
					{
						break;//�õ�ѡ�еı��	
					}
				}else	//��icos
				{
					if((spbdev.curxpos>spbdev.micos[i-16].x)&&(spbdev.curxpos<spbdev.micos[i-16].x+spbdev.micos[i-16].width)&&
					   (spbdev.curypos>spbdev.micos[i-16].y)&&(spbdev.curypos<spbdev.micos[i-16].y+spbdev.micos[i-16].height))
					{
						break;//�õ�ѡ�еı��	
					}
				}
			}
			if(i<19)
			{
				if(i!=spbdev.selico)//ѡ���˲�ͬ��ͼ��,�л�ͼ��
				{
					spb_set_sel(i);
					i=0xff;
				}else
				{
					spbdev.selico=0XFF;//������˫��,���¸�λselico.
				}
			}else i=0xff;//��Ч�ĵ㰴.
			spbdev.spbsta=0;//��ձ�־
		} 
	}else
	{
		if(tp_dev.sta&TP_PRES_DOWN)//�а���������
		{
			if(spbdev.spbsta&0X8000)//�Ѿ��������
			{
				movecnt=spbdev.spbsta&0X3FFF;//�õ���������
				if(gui_disabs(spbdev.curxpos,tp_dev.x[0])>=SPB_MOVE_WIN)//�ƶ����ڵ���SPB_MOVE_WIN����
				{
					if(movecnt<SPB_MOVE_MIN/SPB_MOVE_WIN)spbdev.spbsta++;//��������1	
				}
			}			  		    
			spbdev.curxpos=tp_dev.x[0];				//��¼��ǰ����
			spbdev.curypos=tp_dev.y[0];				//��¼��ǰ����
			if((spbdev.spbsta&0X8000)==0)			//������һ�α�����
			{
				if(spbdev.curxpos>4096||spbdev.curypos>4096)return 0XFF;//�Ƿ�������
				spbdev.spbsta=0;				 	//״̬����
				spbdev.spbsta|=1<<15;				//��ǰ���	    
				spbdev.oldxpos=tp_dev.x[0];			//��¼����ʱ������ 
			}else if(spbdev.spbsta&0X4000)			//�л���
			{
				if(spbdev.oldxpos>tp_dev.x[0]) 		//x����,��Ļpos����
				{
					if(spbdev.pos<lcddev.width)spbdev.pos+=spbdev.oldxpos-tp_dev.x[0]; 
					if(spbdev.pos>lcddev.width)spbdev.pos=lcddev.width;	//�����. 
				}else 								//����,��Ļpos����
				{			    
					if(spbdev.pos>0)spbdev.pos-=tp_dev.x[0]-spbdev.oldxpos;
					if(spbdev.pos>lcddev.width)spbdev.pos=0;		//�����.	   		  
				}	    
				spbdev.oldxpos=tp_dev.x[0];
				slcd_frame_show(spbdev.pos);
			}else if((gui_disabs(spbdev.curxpos,spbdev.oldxpos)>=SPB_MOVE_MIN)&&(movecnt>=SPB_MOVE_MIN/SPB_MOVE_WIN))//�������볬��SPB_MOVE_MIN,���Ҽ�⵽����Ч������������SPB_MOVE_MIN/SPB_MOVE_WIN.
			{ 
				spbdev.spbsta|=1<<14;//��ǻ���	
			}   
		}else //�����ɿ���
		{
			
			if(spbdev.spbsta&0x8000)//֮ǰ�а���
			{	  
				if(spbdev.spbsta&0X4000)//�л���
				{										    
					if(spbdev.frame==1)//ԭ���ڵڶ�֡,ֻ������ 
					{	
						if((lcddev.width-spbdev.pos)>SPB_MOVE_ACT)
						{
							spb_frame_move(1,skips,spbdev.pos);
							spbdev.pos=0;
						}else 
						{
							spb_frame_move(0,skips,spbdev.pos);
							spbdev.pos=lcddev.width;
						}			 
					}else	   //ԭ���ڵ�һ֡,ֻ������  0��ʼ
					{
						if(spbdev.pos>SPB_MOVE_ACT)
						{
							spb_frame_move(0,skips,spbdev.pos);
							spbdev.pos=lcddev.width;
						}else 
						{	
							spb_frame_move(1,skips,spbdev.pos);
							spbdev.pos=0;
						}		   

					}
					spb_unsel_micos(spbdev.selico);	//�����ͼ��ѡ��״̬
					spbdev.selico=0xff;				//ȡ��spbdev.selicoԭ�ȵ�����  
				}else	//���ڵ㰴.
				{
					for(i=0;i<11;i++)
					{
						if(i<8)
						{
							if((spbdev.curxpos>spbdev.icos[spbdev.frame][i].x)&&(spbdev.curxpos<spbdev.icos[spbdev.frame][i].x+spbdev.icos[spbdev.frame][i].width)&&(spbdev.curxpos>spbdev.icos[spbdev.frame][i].x)&&
							   (spbdev.curypos<spbdev.icos[spbdev.frame][i].y+spbdev.icos[spbdev.frame][i].height))
							{
								break;//�õ�ѡ�еı��	
							}
						}else
						{
							if((spbdev.curxpos>spbdev.micos[i-8].x)&&(spbdev.curxpos<spbdev.micos[i-8].x+spbdev.micos[i-8].width)&&
							   (spbdev.curypos>spbdev.micos[i-8].y)&&(spbdev.curypos<spbdev.micos[i-8].y+spbdev.micos[i-8].height))
							{
								break;//�õ�ѡ�еı��	
							}
						}
					}
					if(i<11)
					{
						if(i>=8)i+=8;
						if(i!=spbdev.selico)//ѡ���˲�ͬ��ͼ��,�л�ͼ��
						{
							spb_set_sel(i);
							i=0xff;
						}else
						{
							if(spbdev.frame==1&&i<8)i+=8;//�ڶ�ҳ����,���ƫ�Ƶ�8~15
							spbdev.selico=0XFF;//������˫��,���¸�λselico.
						}
					}else i=0xff;//��Ч�ĵ㰴.
				}
			} 							
			spbdev.spbsta=0;//��ձ�־
		}
	}
	return i;

}











