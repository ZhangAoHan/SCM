#include "camera.h"
#include "common.h"	
#include "ov7670.h"  
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//APP-����� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/10/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   
 
extern vu8 frame_cnt;
extern vu8 ov_sta;	

	   

//����ͷ��ʾ
u8*const camera_remind_tbl[3][GUI_LANGUAGE_NUM]=
{
{"��ʼ��OV7670,���Ժ�...","��ʼ��OV7670,Ո����...","OV7670 Init,Please wait...",},	 
{"δ��⵽OV7670,����...","δ�z�y��OV7670,Ո�z��...","No OV7670 find,Please check...",},	 
{"����Ϊ:","�����:","SAVE AS:",},	 
};
//���ճɹ���ʾ�����
u8*const camera_saveok_caption[GUI_LANGUAGE_NUM]=
{
"���ճɹ���","���ճɹ���","Take Photo OK��",
};
													    
//00������ѡ������
u8*const camera_l00fun_caption[GUI_LANGUAGE_NUM]=
{
"�������","���C�O��","Camera Set",
};

//00������ѡ���
u8*const camera_l00fun_table[GUI_LANGUAGE_NUM][6]=
{
{"����ģʽ","��������","��Ч����","��������","ɫ������","�Աȶ�����",},
{"����ģʽ","�����O��","��Ч�O��","�����O��","ɫ���O��","���ȶ��O��",},
{"Priority","Scene","Effects","Brightness","Saturation","Contrast"},
};	
//////////////////////////////////////////////////////////////////////////	  
//10������ѡ���
//�ٶ�
u8*const camera_l10fun_table[GUI_LANGUAGE_NUM][2]=
{
{"����������","�ٶ�����",},
{"�����ȃ���","�ٶȃ���",},
{"Definition","Speed",},
};
//11������ѡ���
//����ģʽ
u8*const camera_l11fun_table[GUI_LANGUAGE_NUM][5]=
{
{"�Զ�","����","����","�칫��","��ͥ",},
{"�Ԅ�","����","���","�k����","��ͥ",},
{"Auto","Sunny","Cloudy","Office","Home"},
};	
//12������ѡ���
//��Ч����
u8*const camera_l12fun_table[GUI_LANGUAGE_NUM][7]=
{
{"��ͨ","��Ƭ","�ڰ�","ƫ��ɫ","ƫ��ɫ","ƫ��ɫ","����"},
{"��ͨ","ؓƬ","�ڰ�","ƫ�tɫ","ƫ�Gɫ","ƫ�{ɫ","�͹�"},
{"Normal","Negative","B&W","Redish","Greenish","Bluish","Antique",},
};	
//13~15������ѡ���
//����-2~2��5��ֵ
u8*const camera_l135fun_table[GUI_LANGUAGE_NUM][5]=
{
{"-2","-1","0","+1","+2",},					   
{"-2","-1","0","+1","+2",},					   
{"-2","-1","0","+1","+2",},					   
};	   
//////////////////////////////////////////////////////////////////////////	  
//����LCD��ʾ
void camera_refresh(void)
{
	u32 j;
 	u16 color;	 
	if(ov_sta)//��֡�жϸ��£�
	{
		LCD_Scan_Dir(U2D_L2R);		//���ϵ���,������  
		if(lcddev.id==0X1963)LCD_Set_Window((lcddev.width-240)/2,(lcddev.height-320)/2,240,320);//����ʾ�������õ���Ļ����
		else if(lcddev.id==0X5510||lcddev.id==0X5310)LCD_Set_Window((lcddev.width-320)/2,(lcddev.height-240)/2,320,240);//����ʾ�������õ���Ļ����
		LCD_WriteRAM_Prepare();     //��ʼд��GRAM	
		OV7670_RRST=0;				//��ʼ��λ��ָ�� 
		OV7670_RCK_L;
		OV7670_RCK_H;
		OV7670_RCK_L;
		OV7670_RRST=1;				//��λ��ָ����� 
		OV7670_RCK_H;
		for(j=0;j<76800;j++)
		{
			OV7670_RCK_L;
			color=GPIOC->IDR&0XFF;	//������
			OV7670_RCK_H; 
			color<<=8;  
			OV7670_RCK_L;
			color|=GPIOC->IDR&0XFF;	//������
			OV7670_RCK_H; 
			LCD->LCD_RAM=color;    
		}   							  
 		ov_sta=0;					//����֡�жϱ��
		frame_cnt++; 
		LCD_Scan_Dir(DFT_SCAN_DIR);	//�ָ�Ĭ��ɨ�跽�� 
	}
}	  
//ͨ��ʱ���ȡ�ļ���
//��ϳ�:����"0:PHOTO/PIC20120321210633.bmp"���ļ���
void camera_new_pathname(u8 *pname)
{	 
	RTC_Get();//����ʱ��
	sprintf((char*)pname,"0:PHOTO/PIC%04d%02d%02d%02d%02d%02d.bmp",calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,calendar.min,calendar.sec);
}
//����ͷ��ʼ��
//������Ƭ�ļ�,��������SD��PHOTO�ļ�����.
u8 camera_play(void)
{	
 	u8 rval=0;
	u8 res;
 	u8 *caption=0;
	u8 *pname;
	u8 selx=0;
	u8 l00sel=0,l10sel=0,l11sel=0,l12sel=0;//Ĭ��ѡ����
	u8 l345sel[3];
	u8 *psn;
	u8 speedctrl=0;

 	//��ʾ��ʼ���OV7670
 	window_msg_box((lcddev.width-200)/2,(lcddev.height-80)/2,200,80,(u8*)camera_remind_tbl[0][gui_phy.language],(u8*)APP_REMIND_CAPTION_TBL[gui_phy.language],12,0,0,0);
	if(gui_phy.memdevflag&(1<<0))f_mkdir("0:PHOTO");//ǿ�ƴ����ļ���,���������
	if(OV7670_Init())	//��ʼ��ov7670
	{
		window_msg_box((lcddev.width-200)/2,(lcddev.height-80)/2,200,80,(u8*)camera_remind_tbl[1][gui_phy.language],(u8*)APP_REMIND_CAPTION_TBL[gui_phy.language],12,0,0,0);
 		delay_ms(500);  
		rval=1;
	} 
	pname=gui_memin_malloc(40);	//����40���ֽ��ڴ�,���ڴ���ļ���
	psn=gui_memin_malloc(50);	//����50���ֽ��ڴ�,���ڴ�����ƣ�������Ϊ:0:PHOTO/PIC20120321210633.bmp"������ʾ��
	if(pname==NULL)rval=1;		//����ʧ��	  
	if(rval==0)//OV7670����
	{ 
		l345sel[0]=2;//����Ĭ��Ϊ2,ʵ��ֵ0
		l345sel[1]=2;//ɫ��Ĭ��Ϊ2,ʵ��ֵ0
		l345sel[2]=2;//�Աȶ�Ĭ��Ϊ2,ʵ��ֵ0
		OV7670_Light_Mode(l11sel);
 		OV7670_Special_Effects(l12sel);	 
		OV7670_Brightness(l345sel[0]);
  		OV7670_Color_Saturation(l345sel[1]);
		OV7670_Contrast(l345sel[2]);  
		EXTI8_Init();						//ʹ���ⲿ�ж�8,����֡�ж�
		OV7670_Window_Set(12,176,240,320);	//���ô���	  
	  	OV7670_CS=0; 			
		LCD_Clear(BLACK); 
		TIM3_Int_Init(10000-1,7200-1);		//����TIM3 ,1s�ж�һ��	
		while(1)	 
		{		 	
			tp_dev.scan(0);
			if(tp_dev.sta&TP_PRES_DOWN)
			{    		 
				caption=(u8*)camera_l00fun_caption[gui_phy.language];
				res=app_items_sel((lcddev.width-160)/2,(lcddev.height-72-32*6)/2,160,72+32*6,(u8**)camera_l00fun_table[gui_phy.language],6,(u8*)&l00sel,0X90,caption);//��ѡ 
				if(res==0)
				{
					caption=(u8*)camera_l00fun_table[gui_phy.language][l00sel];
					camera_refresh();//ˢ��һ��
					switch(l00sel)
					{
						case 0://����ģʽ	  
							res=app_items_sel((lcddev.width-160)/2,(lcddev.height-72-32*2)/2,160,72+32*2,(u8**)camera_l10fun_table[gui_phy.language],2,(u8*)&l10sel,0X90,caption);//��ѡ
							if(res==0)
							{
								if(l10sel==0)speedctrl=1;	//15֡
								else speedctrl=0; 			//30֡
								SCCB_WR_Reg(0X11,speedctrl);//15/30֡�ٶ�,15֡ʱ�������ȱ��
							}
							break;
						case 1://��������		 
							res=app_items_sel((lcddev.width-160)/2,(lcddev.height-72-32*5)/2,160,72+32*5,(u8**)camera_l11fun_table[gui_phy.language],5,(u8*)&l11sel,0X90,caption);//��ѡ
							if(res==0)
							{
								OV7670_Light_Mode(l11sel);		//��ƽ������	 
							}
							break;
						case 2://��Ч����	  
							res=app_items_sel((lcddev.width-160)/2,(lcddev.height-72-32*7)/2,160,72+32*7,(u8**)camera_l12fun_table[gui_phy.language],7,(u8*)&l12sel,0X90,caption);//��ѡ
							if(res==0)
							{
								OV7670_Special_Effects(l12sel);	//��Ч����
							}
							break;
						case 3://����,ɫ��,�Աȶ�����.	    
						case 4://����,ɫ��,�Աȶ�����.
						case 5://����,ɫ��,�Աȶ�����.
							selx=l345sel[l00sel-3];//�õ�֮ǰ��ѡ��
							res=app_items_sel((lcddev.width-160)/2,(lcddev.height-72-32*5)/2,160,72+32*5,(u8**)camera_l135fun_table[gui_phy.language],5,(u8*)&selx,0X90,caption);//��ѡ
							if(res==0)
							{
								l345sel[l00sel-3]=selx;//��¼��ֵ
							 	if(l00sel==3)OV7670_Brightness(selx);	   	//��������
								if(l00sel==4)OV7670_Color_Saturation(selx);	//ɫ������
								if(l00sel==5)OV7670_Contrast(selx);			//�Աȶ�����
							}
							break;
					}
				}
				LCD_Clear(BLACK);
 			}
 			if(system_task_return)break;//TPAD����
 			camera_refresh();
 			if(KEY_Scan(0)==WKUP_PRES)//KEY_UP������һ��,����һ��
			{					 	
				LED1=0;//DS1��,��ʾ���ڱ���
				pname[0]='\0';//��ӽ�����
				camera_new_pathname(pname);
				if(pname!=NULL)
				{		    
					if(bmp_encode(pname,(lcddev.width-240)/2,(lcddev.height-320)/2,240,320,0))//��������
					{
						window_msg_box((lcddev.width-200)/2,(lcddev.height-100)/2,200,100,(u8*)APP_CREAT_ERR_MSG_TBL[gui_phy.language],(u8*)APP_REMIND_CAPTION_TBL[gui_phy.language],12,0,0,0);//��ʾSD���Ƿ����
						delay_ms(2000);//�ȴ�2����
					}else
					{
						strcpy((char*)psn,(const char *)camera_remind_tbl[2][gui_phy.language]);
						strcat((char*)psn,(const char *)pname);
 						window_msg_box((lcddev.width-180)/2,(lcddev.height-80)/2,180,80,psn,(u8*)camera_saveok_caption[gui_phy.language],12,0,0,0);
	 					BEEP=1;	//�������̽У���ʾ�������
						delay_ms(100);
			 		}
					system_task_return=0;//���TPAD
				}
				LED1=1;	//DS1��,��ʾ�������
				BEEP=0;	//�������̽�
				delay_ms(1800);
			}   
 		}
	}
	gui_memin_free(pname);	
	gui_memin_free(psn);							  
	TIM3->CR1&=~(1<<0);//�رն�ʱ��3
	EXTI->IMR&=~(1<<8);//�ر�line8�ж�		  
	return 0;	 
}















