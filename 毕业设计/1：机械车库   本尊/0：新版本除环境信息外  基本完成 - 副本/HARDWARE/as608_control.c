#include "as608_control.h"
#include "lcd.h"
#include "malloc.h"	   
#include "as608.h"
#include "touch.h"  
#include "delay.h"	
#include "text.h"	
#include "dht11.h"
#include "adc.h"

SysPara AS608Para;//ָ��ģ��AS608����
u16 ValidN;//ģ������Чָ�Ƹ���
u8** kbd_tbl;
const  u8* kbd_menu[15]={"ɾָ��"," : ","¼ָ��","1","2","3","4","5","6","7","8","9","DEL","0","Enter",};//������
const  u8* kbd_delFR[15]={"����"," : ","���ָ��","1","2","3","4","5","6","7","8","9","DEL","0","Enter",};//������
extern u8 set;     //�Զ�¼�����Աָ�Ʊ�׼��
extern u16 now_people_id;
extern u16 now_people_mark;  
extern u8 page;
extern u8 gly_page;
extern u16 car_id[4];      //ʹ��ͣ��λ���û�ID
extern u16 t1,t2,t3,t4;     //��ʱ
extern	u8 temperature;  	    
extern u8 humidity;
	extern u16 adcx;    //tr
//���ذ������棨�ߴ�x,yΪ240*150��
//x,y:������ʼ���꣨240*320�ֱ��ʵ�ʱ��x����Ϊ0��
void AS608_load_keyboard(u16 x,u16 y,u8 **kbtbl)
{
	u16 i;
	POINT_COLOR=RED;
	kbd_tbl=kbtbl;
	LCD_Fill(x,y,x+240,y+150,WHITE);
	LCD_DrawRectangle(x,y,x+240,y+150);						   
	LCD_DrawRectangle(x+80,y,x+160,y+150);	 
	LCD_DrawRectangle(x,y+30,x+240,y+60);
	LCD_DrawRectangle(x,y+90,x+240,y+120);
	POINT_COLOR=BLUE;
	for(i=0;i<15;i++)
	{
		if(i==1)//�������2����:������Ҫ�м���ʾ
			Show_Str(x+(i%3)*80+2,y+7+30*(i/3),80,30,(u8*)kbd_tbl[i],16,0);	
		else
			Show_Str_Mid(x+(i%3)*80,y+7+30*(i/3),(u8*)kbd_tbl[i],16,80);
	} 
}
//����״̬����
//x,y:��������
//key:��ֵ(0~14)
//sta:״̬��0���ɿ���1�����£�
void AS608_key_staset(u16 x,u16 y,u8 keyx,u8 sta)
{		  
	u16 i=keyx/3,j=keyx%3;
	if(keyx>16)return;
	if(sta &&keyx!=1)//�������2����:������Ҫ���
		LCD_Fill(x+j*80+1,y+i*30+1,x+j*80+78,y+i*30+28,GREEN);
	else if(keyx!=1)
		LCD_Fill(x+j*80+1,y+i*30+1,x+j*80+78,y+i*30+28,WHITE);
	if(keyx!=1)//���ǡ�����
		Show_Str_Mid(x+j*80,y+7+30*i,(u8*)kbd_tbl[keyx],16,80);	
}
//�õ�������������
//x,y:��������
//����ֵ:��1~15,��Ӧ������
u8 AS608_get_keynum(u16 x,u16 y)
{
	u16 i,j;
	static u8 key_x=0;//0,û���κΰ�������
	u8 key=0;
	tp_dev.scan(0); 		 
	if(tp_dev.sta&TP_PRES_DOWN)//������������
	{	
		for(i=0;i<5;i++)
		{
			for(j=0;j<3;j++)
			{
			 	if(tp_dev.x[0]<(x+j*80+80)&&tp_dev.x[0]>(x+j*80)&&tp_dev.y[0]<(y+i*30+30)&&tp_dev.y[0]>(y+i*30))
				{	
					key=i*3+j+1;	 
					break;	 		   
				}
			}
			if(key)
			{	   
				if(key_x==key)key=0;
				else 
				{
					AS608_key_staset(x,y,key_x-1,0);
					key_x=key;
					AS608_key_staset(x,y,key_x-1,1);
				}
				break;
			}
	  }  
	}else if(key_x) 
	{
		AS608_key_staset(x,y,key_x-1,0);
		key_x=0;
	} 
	return key; 
}
//��ȡ������ֵ
u16 GET_NUM(void)
{
	u8  key_num=0;
	u16 num=0;
	while(1)
	{
		key_num=AS608_get_keynum(0,170);	
		if(key_num)
		{
			if(key_num==1)return 0xFFFF;//�����ء���
			if(key_num==3)return 0xFF00;//		
			if(key_num>3&&key_num<13&&num<99)//��1-9����(��������3λ��)
				num =num*10+key_num-3;		
			if(key_num==13)num =num/10;//��Del����			
			if(key_num==14&&num<99)num =num*10;//��0����
			if(key_num==15)return num;  //��Enter����
		}
		LCD_ShowNum(80+15,170+7,num,6,16);
	}	
}
//��ʾȷ���������Ϣ
void ShowErrMessage(u8 ensure)
{
	LCD_Fill(0,210,lcddev.width,160,WHITE);
	Show_Str_Mid(0,210,(u8*)EnsureMessage(ensure),16,240);
}
//¼ָ��
void Add_FR(u8 g)    //0����ģʽ   1�Զ�¼����Աģʽ
{
	u8 i,ensure ,processnum=0;
	u16 ID;
	while(1)
	{
		switch (processnum)
		{
			case 0:
				i++;
				LCD_Fill(0,100,lcddev.width,160,WHITE);
				Show_Str_Mid(0,100,"�밴ָ��",16,240);
				ensure=PS_GetImage();
				if(ensure==0x00) 
				{	
					ensure=PS_GenChar(CharBuffer1);//��������
					if(ensure==0x00)
					{
						LCD_Fill(0,120,lcddev.width,160,WHITE);
						Show_Str_Mid(0,120,"ָ������",16,240);
						i=0;
						processnum=1;//�����ڶ���						
					}else ShowErrMessage(ensure);				
				}else ShowErrMessage(ensure);						
				break;
			
			case 1:
				i++;
				LCD_Fill(0,100,lcddev.width,160,WHITE);
				Show_Str_Mid(0,100,"�밴�ٰ�һ��ָ��",16,240);
				ensure=PS_GetImage();
				if(ensure==0x00) 
				{
					ensure=PS_GenChar(CharBuffer2);//��������
					if(ensure==0x00)
					{
						LCD_Fill(0,120,lcddev.width,160,WHITE);
						Show_Str_Mid(0,120,"ָ������",16,240);
						i=0;
						processnum=2;//����������
					}else ShowErrMessage(ensure);	
				}else ShowErrMessage(ensure);		
				break;

			case 2:
				LCD_Fill(0,100,lcddev.width,160,WHITE);
				Show_Str_Mid(0,100,"�Ա�����ָ��",16,240);
				ensure=PS_Match();
				if(ensure==0x00) 
				{
					LCD_Fill(0,120,lcddev.width,160,WHITE);
					Show_Str_Mid(0,120,"�Աȳɹ�,����ָ��һ��",16,240);
					processnum=3;//�������Ĳ�
				}
				else 
				{
					LCD_Fill(0,100,lcddev.width,160,WHITE);
					Show_Str_Mid(0,100,"�Ա�ʧ�ܣ�������¼��ָ��",16,240);
					ShowErrMessage(ensure);
					i=0;
					processnum=0;//���ص�һ��		
				}
				delay_ms(1200);
				break;

			case 3:
				LCD_Fill(0,100,lcddev.width,160,WHITE);
				Show_Str_Mid(0,100,"����ָ��ģ��",16,240);
				ensure=PS_RegModel();
				if(ensure==0x00) 
				{
					LCD_Fill(0,120,lcddev.width,160,WHITE);
					Show_Str_Mid(0,120,"����ָ��ģ��ɹ�",16,240);
					processnum=4;//�������岽
				}else {processnum=0;ShowErrMessage(ensure);}
				delay_ms(1200);
				break;
				
			case 4:	
				if(g==0)    //����ģʽ
				{
					LCD_Fill(0,100,lcddev.width,160,WHITE);
					Show_Str_Mid(0,100,"�����봢��ID,��Enter����",16,240);
					Show_Str_Mid(0,120,"0=< ID <=298",16,240);
					do
					ID=GET_NUM();
//					while(!(ID<AS608Para.PS_max));//����ID����С�����������ֵ
					while(!(ID<299));//����ID����С�����������ֵ
					ensure=PS_StoreChar(CharBuffer2,ID);//����ģ��
					if(ensure==0x00) 
					{			
					LCD_Fill(0,100,lcddev.width,160,WHITE);					
					Show_Str_Mid(0,120,"¼��ָ�Ƴɹ�",16,240);
					PS_ValidTempleteNum(&ValidN);//����ָ�Ƹ���
					Show_Str(0,80,96,24,"ʣ��⣺",24,0);
					LCD_ShowNum(100,84,AS608Para.PS_max-ValidN,3,16);   //��ʾʣ��ָ������
					delay_ms(1500);
					LCD_Fill(0,100,240,160,WHITE);
					set=0;		    //�����׼��
					return ;
					}else {processnum=0;ShowErrMessage(ensure);}		
				}
				else    //¼����Աָ��
				{ 
					ID=299;
					ensure=PS_StoreChar(CharBuffer2,ID);//����ģ��
										if(ensure==0x00) 
					{			
					LCD_Fill(0,100,lcddev.width,160,WHITE);					
					Show_Str_Mid(0,120,"¼��ָ�Ƴɹ�",16,240);
					PS_ValidTempleteNum(&ValidN);//����ָ�Ƹ���
					Show_Str(0,80,96,24,"ʣ��⣺",24,0);
					LCD_ShowNum(100,84,AS608Para.PS_max-ValidN,3,16);   //��ʾʣ��ָ������
					delay_ms(1500);
					LCD_Clear(WHITE);
					POINT_COLOR=BLUE;
					Show_Str_Mid(0,50,"����Ա¼ָ�Ƴɹ�",24,240);
					delay_ms(3000);
					LCD_Clear(WHITE);
					set=0;		    //�����׼��
					return ;
					}else {processnum=0;ShowErrMessage(ensure);}
				}	
				break;				
		}
		delay_ms(400);
		if(i==5)//����5��û�а���ָ���˳�
		{
			LCD_Fill(0,100,lcddev.width,160,WHITE);
			break;	
		}				
	}
}

//ˢָ��
void press_FR(void)
{
	SearchResult seach;
	u8 ensure;
	char *str;
	ensure=PS_GetImage();
	if(ensure==0x00)//��ȡͼ��ɹ� 
	{	
		ensure=PS_GenChar(CharBuffer1);
		if(ensure==0x00) //���������ɹ�
		{		
			ensure=PS_HighSpeedSearch(CharBuffer1,0,AS608Para.PS_max,&seach);
			if(ensure==0x00)//�����ɹ�
			{				
				LCD_Fill(0,150,lcddev.width,320,WHITE);
				Show_Str_Mid(0,150,"ˢָ�Ƴɹ�",16,240);				
				str=mymalloc(SRAMIN,50);
				sprintf(str,"ȷ�д���,ID:%d  ƥ��÷�:%d",seach.pageID,seach.mathscore);
				Show_Str_Mid(0,175,(u8*)str,16,240);
				now_people_id=seach.pageID;
				now_people_mark=seach.mathscore;
				myfree(SRAMIN,str);
			}
			else 
				ShowErrMessage(ensure);					
	  }
		else
			ShowErrMessage(ensure);
	 delay_ms(600);
	 LCD_Fill(0,150,lcddev.width,320,WHITE);
	}
		
}

//ɾ��ָ��
void Del_FR(void)
{
	u8  ensure;
	u16 ValidN,num;
	LCD_Fill(0,100,lcddev.width,160,WHITE);
	Show_Str_Mid(0,100,"ɾ��ָ��",16,240);
	Show_Str_Mid(0,120,"������ָ��ID��Enter����",16,240);
	Show_Str_Mid(0,140,"0=< ID <=299",16,240);
	delay_ms(50);
	AS608_load_keyboard(0,170,(u8**)kbd_delFR);
	num=GET_NUM();//��ȡ���ص���ֵ
	if(num==0xFFFF)
		goto MENU ; //������ҳ��
	else if(num==0xFF00)
	{
		ensure=PS_Empty();//���ָ�ƿ�
		gly_id_save();     //�Զ�¼ָ��
		AS608_load_keyboard(0,170,(u8**)kbd_menu);//�����������
	}
		
	else 
		ensure=PS_DeletChar(num,1);//ɾ������ָ��
	if(ensure==0)
	{
		LCD_Fill(0,120,lcddev.width,160,WHITE);
		Show_Str_Mid(0,140,"ɾ��ָ�Ƴɹ�",16,240);		
	}
  else
	ShowErrMessage(ensure);	
	delay_ms(1200);
	PS_ValidTempleteNum(&ValidN);//����ָ�Ƹ���
	Show_Str(0,80,96,24,"ʣ��⣺",24,0);
	LCD_ShowNum(100,84,AS608Para.PS_max-ValidN,3,16);   //��ʾʣ��ָ������
MENU:	
	LCD_Fill(0,100,lcddev.width,160,WHITE);
	delay_ms(50);
	AS608_load_keyboard(0,170,(u8**)kbd_menu);   
}

void as608_use_init(void)           //�������ú���
{
	u8 ensure;  //ָ�Ƹ���
	char *str;
	LCD_Clear(WHITE);
	POINT_COLOR=BLUE;
	Show_Str_Mid(0,40,"��AS608ģ������....",16,240);
	while(PS_HandShake(&AS608Addr))//��AS608ģ������
	{
		delay_ms(400);
		LCD_Fill(0,40,240,80,WHITE);
		Show_Str_Mid(0,40,"δ��⵽ģ��!!!",16,240);
		delay_ms(800);
		LCD_Fill(0,40,240,80,WHITE);
		Show_Str_Mid(0,40,"��������ģ��...",16,240);		  
	}
	LCD_Fill(30,40,240,100,WHITE);
	Show_Str_Mid(0,40,"ͨѶ�ɹ�!!!",16,240);
	str=mymalloc(SRAMIN,30);
	Show_Str(0,60,240,16,(u8*)str,16,0);
	ensure=PS_ValidTempleteNum(&ValidN);//����ָ�Ƹ���
	if(ensure!=0x00)
		ShowErrMessage(ensure);//��ʾȷ���������Ϣ	
	ensure=PS_ReadSysPara(&AS608Para);  //������ 
	if(ensure==0x00)
	{
		mymemset(str,0,50);
		sprintf(str,"������:%d     �Աȵȼ�: %d",AS608Para.PS_max-ValidN,AS608Para.PS_level);
		Show_Str(0,80,240,16,(u8*)str,16,0);
	}
	else
		ShowErrMessage(ensure);	
	myfree(SRAMIN,str);
//	AS608_load_keyboard(0,170,(u8**)kbd_menu);//�����������
}

//AS680���ƺ���
/*
	1���Ż���ҳ�溯��   ������Ա������ã�ֱ�ӵ��ã�
	�����ָ�ƣ���   ���ȫ����ָ����Ϣ��Ҫ����¼����Աָ�ƣ����洢��299λ��  
	��¼ָ�ƣ���     ¼ָ��   ��ʾʣ��ָ������     ���Ҳ��ܰ�ָ��¼��299λ��
	
*/
void page_0(void)     //ͨ��ˢָ�������벻ͬ�Ľ���
{
	POINT_COLOR=BLUE;
	Show_Str_Mid(0,50,"��е����ϵͳ",16,240);
	POINT_COLOR=BLACK;
	Show_Str(48,100,144,24,"��ˢָ�Ƶ�¼",24,0);
		if(PS_Sta)	 //���PS_Sta״̬���������ָ����
	{
		press_FR();//ˢָ��	    ������ҳ��		
	}
	if(now_people_id!=300)
	{
		if(now_people_id==299)
		{
			page=1;                           //����Ա����  �������Ա��ҳ��
			LCD_Clear(WHITE);
		}
		else if(now_people_id!=car_id[0]&&now_people_id!=car_id[1]&&now_people_id!=car_id[2]&&now_people_id!=car_id[3]&&now_people_id!=299)
		{
			page=2;                           //�泵����
			LCD_Clear(WHITE);
		}
		else if((now_people_id==car_id[0]||now_people_id==car_id[1]||now_people_id==car_id[2]||now_people_id==car_id[3])&&now_people_id!=299)
		{
			page=3;                           //�泵����
			LCD_Clear(WHITE);
		}
	}

	
}

void gly_page_0(void)            //����Ա������  gly_page=0  //����㷵�� �����������ID��Ϣ���÷�
{
	POINT_COLOR=BLUE;
	Show_Str_Mid(0,10,"����Ա��¼�ɹ�",24,240);
	POINT_COLOR=RED;
	Show_Str_Mid(100,290,"����",24,140);
	Show_Str_Mid(30,50,"�鿴ͣ��λ��Ϣ",24,180);
	Show_Str_Mid(30,100,"�û���Ϣ����",24,180);
	Show_Str_Mid(30,150,"ͣ��������",24,180);	
	POINT_COLOR=BLACK;
	Show_Str(10,200,120,24,"����ԱID��",24,0);
	Show_Str(10,230,120,24,"���ε÷֣�",24,0);
	LCD_ShowNum(130,204,now_people_id,3,16);  
	LCD_ShowNum(130,234,now_people_mark,3,16);  
	gly_scan();
}
void gly_page_1(void)    //ͣ��λ��ʾ����   gly_page=1
{
	POINT_COLOR=BLUE;
	Show_Str_Mid(0,10,"ͣ��λ��Ϣ",24,240);
	Show_Str(10,50,120,24,"һ��ͣ��λ",24,0);
	Show_Str(10,110,120,24,"����ͣ��λ",24,0);
	Show_Str(10,170,120,24,"����ͣ��λ",24,0);
	Show_Str(10,230,230,24,"�ĺ�ͣ��λ",24,0);
	POINT_COLOR=RED;
	Show_Str_Mid(100,290,"����",24,140);
	POINT_COLOR=BLACK;
	
	Show_Str(10,75,120,24,"�û�ID��",16,0);
	Show_Str(10,92,120,24,"ʹ��ʱ�䣺",16,0);
	
	
	Show_Str(10,135,120,24,"�û�ID��",16,0);
	Show_Str(10,152,120,24,"ʹ��ʱ�䣺",16,0);
	
	
	Show_Str(10,195,120,24,"�û�ID��",16,0);
	Show_Str(10,212,120,24,"ʹ��ʱ�䣺",16,0);
	
	
	Show_Str(10,255,120,24,"�û�ID��",16,0);
	Show_Str(10,272,120,24,"ʹ��ʱ�䣺",16,0);
	
		if(car_id[0]==300)Show_Str(130,75,48,24,"����",16,0);
	else LCD_ShowNum(130,75,car_id[0],3,16);      //��ʾID
		if(car_id[1]==300)Show_Str(130,135,48,24,"����",16,0);
	else LCD_ShowNum(130,135,car_id[1],3,16);      //��ʾID
		if(car_id[2]==300)Show_Str(130,195,48,24,"����",16,0);
	else LCD_ShowNum(130,195,car_id[2],3,16);      //��ʾID
		if(car_id[3]==300)Show_Str(130,255,48,24,"����",16,0);
	else LCD_ShowNum(130,255,car_id[3],3,16);      //��ʾID
	
		LCD_ShowChar(130,92,'H',16,0);         //��ʾʹ��ʱ��
	LCD_ShowChar(165,92,'M',16,0);
	LCD_ShowChar(200,92,'S',16,0);
	LCD_ShowNum(115,92,(t1/60)/24,2,16); 
	LCD_ShowNum(145,92,(t1/60)%24,2,16); 
	LCD_ShowNum(180,92,t1%60,2,16); 
		LCD_ShowChar(130,152,'H',16,0);
	LCD_ShowChar(165,152,'M',16,0);
	LCD_ShowChar(200,152,'S',16,0);
	LCD_ShowNum(115,152,(t2/60)/24,2,16); 
	LCD_ShowNum(145,152,(t2/60)%24,2,16); 
	LCD_ShowNum(180,152,t2%60,2,16); 
		LCD_ShowChar(130,212,'H',16,0);
	LCD_ShowChar(165,212,'M',16,0);
	LCD_ShowChar(200,212,'S',16,0);
	LCD_ShowNum(115,212,(t3/60)/24,2,16); 
	LCD_ShowNum(145,212,(t3/60)%24,2,16); 
	LCD_ShowNum(180,212,t3%60,2,16); 
		LCD_ShowChar(130,272,'H',16,0);
	LCD_ShowChar(165,272,'M',16,0);
	LCD_ShowChar(200,272,'S',16,0);
	LCD_ShowNum(115,272,(t4/60)/24,2,16); 
	LCD_ShowNum(145,272,(t4/60)%24,2,16); 
	LCD_ShowNum(180,272,t4%60,2,16); 
	
	gly_scan();
}
void gly_page_2(void)
{
		u8 key_num;	
		POINT_COLOR=BLUE;
		Show_Str_Mid(0,10,"�û���Ϣ����",24,240);
		PS_ValidTempleteNum(&ValidN);//����ָ�Ƹ���
		Show_Str(0,80,96,24,"ʣ��⣺",24,0);
		LCD_ShowNum(100,84,AS608Para.PS_max-ValidN,3,16);   //��ʾʣ��ָ������
		POINT_COLOR=RED;
		Show_Str_Mid(0,40,"����",24,240);
		AS608_load_keyboard(0,170,(u8**)kbd_menu);//�����������  ������Ա��Ϣ�������  ��Ҫ�ȼ������ⰴ��
		set=1;
		while(set)
		{
			key_num=AS608_get_keynum(0,170);	
			if(key_num)
			{
				if(key_num==1)Del_FR();		//ɾָ��
				if(key_num==3)Add_FR(0);		//¼ָ��									
			}	
			gly_scan();
		}

}
void gly_page_3(void)       //������Ϣ��ʾ����
{
	POINT_COLOR=BLUE;
	Show_Str_Mid(0,10,"ͣ����������Ϣ",24,240);
	POINT_COLOR=BLACK;
	Show_Str(0,50,120,24,"�¶���Ϣ:",24,0);
	Show_Str(0,100,120,24,"ʪ����Ϣ:",24,0);
	Show_Str(0,150,120,24,"��ǿ��Ϣ:",24,0);
		LCD_ShowNum(150,50,temperature,2,24); 
	LCD_ShowString(180,50,60,24,24,"��");
		LCD_ShowNum(150,100,humidity,2,24); 
	LCD_ShowString(180,100,60,24,24,"RH");
			LCD_ShowNum(150,150,adcx,4,24); 
	POINT_COLOR=RED;
	Show_Str_Mid(100,290,"����",24,140);
	gly_scan();
}
void date_read(void)    //������Ϣ���ݸ���
{
	adcx=Get_Adc_Average(ADC_CH1,10);
	DHT11_Read_Data(&temperature,&humidity);	//��ȡ��ʪ��ֵ	
}
void gly_scan(void)     //�������Ա�����Ĵ�������
{
		tp_dev.scan(0); 
	if(tp_dev.sta&TP_PRES_DOWN)			//������������
	{
		if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
		{
			if(gly_page==0)
			{
					if(tp_dev.x[0]>0&&tp_dev.x[0]<240&&tp_dev.y[0]>290&&tp_dev.y[0]<320)   //����
				{
						page=0;               //����Ա����  �ò�����ɺ���Ҫ������ε�¼��ID��Ϣ���÷���Ϣ
						gly_page=0;
						now_people_id=300;
						now_people_mark=0;
						LCD_Clear(WHITE); 
						delay_ms(100);
						
				}
				if(tp_dev.x[0]>30&&tp_dev.x[0]<180&&tp_dev.y[0]>50&&tp_dev.y[0]<80)     //ͣ��λ��Ϣ  gly_page=1
				{
					gly_page=1;
					LCD_Clear(WHITE); 
					delay_ms(100);
					
				}
				if(tp_dev.x[0]>30&&tp_dev.x[0]<180&&tp_dev.y[0]>100&&tp_dev.y[0]<130)  //�û���Ϣ����  gly_page=2
				{
					gly_page=2;
					LCD_Clear(WHITE); 
					delay_ms(100);
				}
				if(tp_dev.x[0]>30&&tp_dev.x[0]<180&&tp_dev.y[0]>150&&tp_dev.y[0]<180)    //������Ϣ  gly_page=3
				{
					gly_page=3;
					LCD_Clear(WHITE); 
					delay_ms(100);
				}
			}
			else if(gly_page==1)
			{
					if(tp_dev.x[0]>0&&tp_dev.x[0]<240&&tp_dev.y[0]>290&&tp_dev.y[0]<320)   //����
				{
						gly_page=0;
						LCD_Clear(WHITE); 
						delay_ms(100);
						
				}
			}
			else if(gly_page==2)
			{
				if(tp_dev.x[0]>0&&tp_dev.x[0]<240&&tp_dev.y[0]>40&&tp_dev.y[0]<65)   //����
				{
						gly_page=0;
						set=0;   //ǿ�Ʒ���
						LCD_Clear(WHITE); 
						delay_ms(100);
						
				}
			}
			else if(gly_page==3)
			{
					if(tp_dev.x[0]>0&&tp_dev.x[0]<240&&tp_dev.y[0]>290&&tp_dev.y[0]<320)   //����
				{
						gly_page=0;
						LCD_Clear(WHITE); 
						delay_ms(100);
						
				}
			}
				
				

		}
	}
}
void gly_id_save(void)    //�Զ�¼����Աָ��  ¼�������
{
	set=1;           //������־��
	LCD_Clear(WHITE);
	POINT_COLOR=BLUE;
	Show_Str_Mid(0,50,"�����Ա¼ָ��",24,240);
	while(set)
	{
			Add_FR(1);
	}
}
