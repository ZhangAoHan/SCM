#include "date_control.h"
#include "lcd.h"
#include "touch.h"  
#include "malloc.h"
#include "text.h"	
#include "delay.h"	 
#include "as608.h"
#include "control.h"
#include "at24c02.h" 


SysPara AS608Para;//ָ��ģ��AS608����
u16 ValidN;//ģ������Чָ�Ƹ���
u8** kbd_tbl;
const  u8* kbd_menu[15]={"ɾָ��"," : ","¼ָ��","1","2","3","4","5","6","7","8","9","DEL","0","Enter",};//������
const  u8* kbd_delFR[15]={"����"," : ","���ָ��","1","2","3","4","5","6","7","8","9","DEL","0","Enter",};//������
extern u8 page;
extern char *str1;
u8 people;
//extern u8 car[4] ;    //��4��ͣ��λ�ɹ�ѡ��
extern u16 car_id[4];      //ʹ��ͣ��λ���û�ID
extern u16 people_id;
extern u16 t1,t2,t3,t4; 
extern u8 use1,use2,use3,use4; 
extern u8 dl_success;   //��ʼ����ͣ�������ı�־��
extern u8 use_error; 
extern u8 people_car;   //��ʾ�����û�ͣ����λ��
extern u16 gly_id;
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
		delay_ms(200);         //ÿ0.5s��ȡһ������
	}	
}
//��ʾȷ���������Ϣ
void ShowErrMessage(u8 ensure)
{
	LCD_Fill(0,120,lcddev.width,160,WHITE);
	Show_Str_Mid(0,120,(u8*)EnsureMessage(ensure),16,240);
}
//¼ָ��
void Add_FR(void)
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
				delay_ms(1000);
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
					delay_ms(200);
					processnum=3;//�������Ĳ�
				}
				else 
				{
					LCD_Fill(0,100,lcddev.width,160,WHITE);
					Show_Str_Mid(0,100,"�Ա�ʧ�ܣ�������¼��ָ��",16,240);
					delay_ms(200);
					ShowErrMessage(ensure);
					i=0;
					processnum=0;//���ص�һ��		
				}
				delay_ms(1200);
				break;

			case 3:
				LCD_Fill(0,100,lcddev.width,160,WHITE);
				Show_Str_Mid(0,100,"����ָ��ģ��",16,240);
				delay_ms(200);
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
				LCD_Fill(0,100,lcddev.width,160,WHITE);
				Show_Str_Mid(0,100,"�����봢��ID,��Enter����",16,240);
				Show_Str_Mid(0,120,"0=< ID <=298",16,240);
				do
					ID=GET_NUM();
				while(!(ID<AS608Para.PS_max));//����ID����С�����������ֵ
				ensure=PS_StoreChar(CharBuffer2,ID);//����ģ��
				LCD_ShowNum(10,10,ID,3,16);///////////////
				people=1;   ///////////////////////////
				if(ensure==0x00) 
				{			
					LCD_Fill(0,100,lcddev.width,160,WHITE);					
					Show_Str_Mid(0,120,"¼��ָ�Ƴɹ�",16,240);
					PS_ValidTempleteNum(&ValidN);//����ָ�Ƹ���
					LCD_ShowNum(56,80,AS608Para.PS_max-ValidN,3,16);
					delay_ms(1500);
					LCD_Fill(0,100,240,160,WHITE);
					AS608_load_keyboard(0,170,(u8**)kbd_menu); //////////////
					return ;
				}else {processnum=0;ShowErrMessage(ensure);}					
				break;				
		}
		delay_ms(400);
		if(i==5)//����5��û�а���ָ���˳�
		{
			LCD_Fill(0,100,lcddev.width,160,WHITE);
			delay_ms(200);
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
				LCD_Fill(0,100,lcddev.width,160,WHITE);
				//Show_Str_Mid(0,100,"ˢָ�Ƴɹ�",16,240);				
				str=mymalloc(SRAMIN,50);
				sprintf(str,"ȷ�д���,ID:%d  ƥ��÷�:%d",seach.pageID,seach.mathscore);
				//Show_Str_Mid(0,140,(u8*)str,16,240);
				myfree(SRAMIN,str);   
				people=1;		     //��ʾ�ɹ�		
				people_id=seach.pageID;
//				LCD_ShowNum(100,10,people_id,3,16);
			}
			else 
			{
				ShowErrMessage(ensure);	   //����ʧ��
				people=0;	
			}
								
	  }
		else
		{
				ShowErrMessage(ensure);
				people=0;	
		}
		
	
	 delay_ms(600);   //�ӳ�ɨ��
	// LCD_Fill(0,100,lcddev.width,160,WHITE);
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
	AS608_load_keyboard(0,170,(u8**)kbd_delFR);    ////////////
	num=GET_NUM();//��ȡ���ص���ֵ
	if(num==0xFFFF)
		goto MENU ; //������ҳ��
	else if(num==0xFF00)
		ensure=PS_Empty();//���ָ�ƿ�
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
	LCD_ShowNum(56,80,AS608Para.PS_max-ValidN,3,16);
MENU:	
	LCD_Fill(0,100,lcddev.width,160,WHITE);
  
	delay_ms(50);
	AS608_load_keyboard(0,170,(u8**)kbd_menu);           ///////////////
}


void AS_Init(void)
{
	char *str;
	u8 ensure;
	str=mymalloc(SRAMIN,30);
	sprintf(str,"������:%d   ��ַ:%x",57600,AS608Addr);
	ensure=PS_ValidTempleteNum(&ValidN);//����ָ�Ƹ���
	if(ensure!=0x00)
		ShowErrMessage(ensure);//��ʾȷ���������Ϣ	
	ensure=PS_ReadSysPara(&AS608Para);  //������ 
	if(ensure==0x00)
	{
		mymemset(str,0,50);
		sprintf(str,"������:%d     �Աȵȼ�: %d",AS608Para.PS_max-ValidN,AS608Para.PS_level);
		//Show_Str(0,80,240,16,(u8*)str,16,0);
		str1=str;
	}
	else
		ShowErrMessage(ensure);	
	myfree(SRAMIN,str);
	
}

//void AS_Control(u8 mode)       //ָ��ģ����ƺ���    0���û�����   1����Ա����
//{
//	u8 key_num;
//	if(mode==0)           //�û�������¼����ǰ�Լ�¼��ָ���ˣ�
//	{
//		if(car_id[0]!=0&&car_id[1]!=0&&car_id[2]!=0&&car_id[3]!=0)
//		{
//				POINT_COLOR=BLUE;
//				Show_Str_Mid(0,50,"�޿���ͣ��λ",24,240);
//				page=0;
//				delay_ms(2000);
//				LCD_Clear(WHITE); 
//		}
//		else    //�п���ͣ��λ
//		{
//			if(dl_success==0)
//			{
//				if(PS_Sta)	 //���PS_Sta״̬���������ָ����  //����ɹ�������ڶ�ҳ�����ʧ����ʾʧ����Ϣ��Ȼ����2��û����ָ���½��Զ��˳�
//				{
//					press_FR();//ˢָ��
//				if(people==1) //ͣ��
//				{
//					POINT_COLOR=BLUE;
//					Show_Str_Mid(0,0,"��ѡ��ͣ��λ",24,240);
//					Show_Str(20,25,96,24,"�û�ID��",24,1);
//					LCD_ShowNum(130,29,people_id,3,16);      //��ʾID
//					dl_success=1;
//					
//				}
//				}
//			}
//			else
//			{
//					car_settle();
//					use1_touch();
//			}

//					

//	
////		else       //ˢָ�Ƶȴ�����
////		{
////			Show_Str_Mid(0,0,"��ˢָ��",24,240);
////		}
//		}

//	}                       //�������Աģʽ
//	else if(mode==1)
//	{
//		
//		key_num=AS608_get_keynum(0,170);	
//		if(key_num)
//		{
//			if(key_num==1)Del_FR();		//ɾָ��
//			if(key_num==3)Add_FR();		//¼ָ��									
//		}
//		
//	}


//}


void car_settle(void)   //ͣ��λѡ����
{
		use1_touch();
		LCD_DrawRectangle(10,60,110,160);
	LCD_DrawRectangle(9,59,111,161);
		LCD_DrawRectangle(130,60,230,160);
	LCD_DrawRectangle(129,59,231,161);
		LCD_DrawRectangle(10,180,110,280);
	LCD_DrawRectangle(9,179,111,281);
		LCD_DrawRectangle(130,180,230,280);
	LCD_DrawRectangle(129,179,231,281);
		if(car_id[0]==0)
	{
		LCD_Fill(15,65,105,105,GREEN);
		POINT_COLOR=BLACK;
		Show_Str_Mid(15,72,"��λ����",16,90);
	}
	else
	{
		LCD_Fill(15,65,105,105,BLUE);
		POINT_COLOR=BLACK;
		Show_Str_Mid(15,72,"��λ��ռ",16,90);
		Show_Str(15,110,40,24,"ID��",16,1);
		LCD_ShowNum(45,110,people_id,3,16);      //��ʾID
		LCD_ShowChar(30,140,'H',16,0);
		LCD_ShowChar(65,140,'M',16,0);
		LCD_ShowChar(100,140,'S',16,0);
		LCD_ShowNum(15,140,(t1/60)/24,2,16); 
		LCD_ShowNum(45,140,(t1/60)%24,2,16); 
		LCD_ShowNum(80,140,t1%60,2,16); 
	}
		if(car_id[1]==0)
	{
		LCD_Fill(135,65,225,105,GREEN);
		POINT_COLOR=BLACK;
		Show_Str_Mid(135,72,"��λ����",16,90);
	}
	else
	{
		LCD_Fill(135,65,225,105,BLUE);
		POINT_COLOR=BLACK;
		Show_Str_Mid(135,72,"��λ��ռ",16,90);
		Show_Str(135,110,40,24,"ID��",16,1);
		LCD_ShowNum(165,110,people_id,3,16);      //��ʾID
		LCD_ShowChar(150,140,'H',16,0);
		LCD_ShowChar(185,140,'M',16,0);
		LCD_ShowChar(220,140,'S',16,0);
		LCD_ShowNum(135,140,(t2/60)/24,2,16); 
		LCD_ShowNum(165,140,(t2/60)%24,2,16); 
		LCD_ShowNum(200,140,t2%60,2,16); 
	}
		if(car_id[2]==0)
	{
		LCD_Fill(15,185,105,225,GREEN);
		POINT_COLOR=BLACK;
		Show_Str_Mid(15,192,"��λ����",16,90);
	}
	else
	{
		LCD_Fill(15,185,105,225,BLUE);
		POINT_COLOR=BLACK;
		Show_Str_Mid(15,192,"��λ��ռ",16,90);
		Show_Str(15,190,40,24,"ID��",16,1);
		LCD_ShowNum(45,220,people_id,3,16);      //��ʾID
		LCD_ShowChar(30,260,'H',16,0);
		LCD_ShowChar(65,260,'M',16,0);
		LCD_ShowChar(100,260,'S',16,0);
		LCD_ShowNum(15,260,(t3/60)/24,2,16); 
		LCD_ShowNum(45,260,(t3/60)%24,2,16); 
		LCD_ShowNum(80,260,t3%60,2,16); 
	}
		if(car_id[3]==0)
	{
		LCD_Fill(135,185,225,225,GREEN);
		POINT_COLOR=BLACK;
		Show_Str_Mid(135,192,"��λ����",16,90);
	}
	else
	{
		LCD_Fill(135,185,225,225,BLUE);
		POINT_COLOR=BLACK;
		Show_Str_Mid(135,192,"��λ��ռ",16,90);
		Show_Str(135,190,40,24,"ID��",16,1);
		LCD_ShowNum(165,220,people_id,3,16);      //��ʾID
		LCD_ShowChar(150,260,'H',16,0);
		LCD_ShowChar(185,260,'M',16,0);
		LCD_ShowChar(220,260,'S',16,0);
		LCD_ShowNum(135,260,(t3/60)/24,2,16); 
		LCD_ShowNum(165,260,(t3/60)%24,2,16); 
		LCD_ShowNum(200,260,t3%60,2,16); 
	}
	Show_Str(100,290,48,24,"����",24,0);
}
void use1_touch(void)  //ѡ��ͣ��λ�ĸ�����������
{
		tp_dev.scan(0); 
	if(tp_dev.sta&TP_PRES_DOWN)			//������������
	{
		if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
		{
			if(tp_dev.x[0]>15&&tp_dev.x[0]<105&&tp_dev.y[0]>60&&tp_dev.y[0]<100&&car_id[0]==0)
			{
				car_id[0]=people_id;
				use1=1;      //������ʱ
				people_car=1;
				dl_success=1;
				LCD_Clear(WHITE); 
				delay_ms(100);
			}
			else if(tp_dev.x[0]>135&&tp_dev.x[0]<225&&tp_dev.y[0]>60&&tp_dev.y[0]<100&&car_id[1]==0)
			{
				car_id[1]=people_id;
				use2=1;
				people_car=2;
				dl_success=1;
				LCD_Clear(WHITE); 
				delay_ms(100);
			}
			else if(tp_dev.x[0]>15&&tp_dev.x[0]<105&&tp_dev.y[0]>185&&tp_dev.y[0]<225&&car_id[2]==0)
			{
				car_id[2]=people_id;
				use3=1;
				dl_success=1;
				people_car=3;
				LCD_Clear(WHITE); 
				delay_ms(100);
			}
			else if(tp_dev.x[0]>135&&tp_dev.x[0]<225&&tp_dev.y[0]>185&&tp_dev.y[0]<225&&car_id[3]==0)
			{
				car_id[3]=people_id;
				use4=1;
				dl_success=1;
				people_car=4;
				LCD_Clear(WHITE); 
				delay_ms(100);
			}
			else if(tp_dev.x[0]>100&&tp_dev.x[0]<150&&tp_dev.y[0]>290&&tp_dev.y[0]<320)
			{
					LCD_Clear(WHITE);    //������� ������ҳ��
					delay_ms(100);
					page=0;
			}
		}
	}
}

void use_as608_scan(void)  //���ָ�ƺ��������ó��û��Ƿ�¼��ָ�ơ��Լ��Ƿ�����ȡ����  page=0�����к��� 
{
	if(PS_Sta)	 //���PS_Sta״̬���������ָ����
	{
		press_FR();       //ˢָ��
		if(people==1)    //���ҳɹ�
		{
			if(people_id==gly_id)//����Ա��¼
			{
				LCD_Clear(WHITE); 
				delay_ms(100);	
				page=3;   //����Ա��¼����
			}				
			else if(people_id==car_id[0]||people_id==car_id[1]||people_id==car_id[2]||people_id==car_id[3])   //���鿴��Ϣ����ȡ�����û�
			{
				LCD_Clear(WHITE); 
				delay_ms(100);	
				page=2;     //�鿴��Ϣ����ȡ������
			} //ȡ�����߲鿴��Ϣ
			else //�泵
			{
				LCD_Clear(WHITE); 
				delay_ms(100);	
				page=1;     //��תͣ��λ����
			}  		
		}
		else    //û��¼ָ��  ��ʾ������Ϣ
		{
		use_error=1;
		LCD_Clear(WHITE); 
		delay_ms(100);		
		Error_0_display();
		while(use_error)
		{;}
		LCD_Clear(WHITE); 
		delay_ms(100);
		page=0;
		}			
			
	}
	
}



void use_xx_scan(void)
{
		tp_dev.scan(0); 
	if(tp_dev.sta&TP_PRES_DOWN)			//������������
	{
		if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
		{
			if(tp_dev.x[0]>0&&tp_dev.x[0]<240&&tp_dev.y[0]>150&&tp_dev.y[0]<175)   //ȡ��
			{
					dl_success=1;
					LCD_Clear(WHITE); 
					delay_ms(100);
					
			}
			if(tp_dev.x[0]>0&&tp_dev.x[0]<240&&tp_dev.y[0]>180&&tp_dev.y[0]<205)   //�鿴��Ϣ  ����
			{
					LCD_Clear(WHITE); 
					delay_ms(100);
					page=0;
			}
		}
	}
}
void gly_scan(void)
{
			tp_dev.scan(0); 
	if(tp_dev.sta&TP_PRES_DOWN)			//������������
	{
		if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
		{
				if(tp_dev.x[0]>0&&tp_dev.x[0]<240&&tp_dev.y[0]>290&&tp_dev.y[0]<320)   //ȡ��
			{
					page=0;
					LCD_Clear(WHITE); 
					delay_ms(100);
					
			}
		}
	}
}

void date_read(void)   //��ҪΪ�˵ó�ָ�Ƶľ���ID��Ϣ  �������еĺ���
{
	u8 key_num;
u8 id1,id2,id3;
	AS608_load_keyboard(0,170,(u8**)kbd_menu);//�����������
	while(1)
	{

		key_num=AS608_get_keynum(0,170);	
		if(key_num)
		{
			if(key_num==1)Del_FR();		//ɾָ��
			if(key_num==3)Add_FR();		//¼ָ��									
		}
		if(PS_Sta)	 //���PS_Sta״̬���������ָ����
		{
			press_FR();//ˢָ��		
			
//			LCD_ShowNum(10,50,,3,24);
		}
		if(people==1)
		{
			while(people)
			{
				if(people_id==299)
				{
					AT24CXX_WriteOneByte(60,people_id/100);
					AT24CXX_WriteOneByte(61,(people_id%100)/10);
					AT24CXX_WriteOneByte(62,people_id%10);
				}
				Show_Str_Mid(0,290,"����",24,90);
				date_read_scan();
			}
		}	
			
	id1=AT24CXX_ReadOneByte(60);
	id2=AT24CXX_ReadOneByte(61);
	id3=AT24CXX_ReadOneByte(62);
	gly_id=id1*100+id2*10+id3;
		LCD_ShowNum(10,50,gly_id,3,24);
	}			
}

void date_read_scan(void)
{
			tp_dev.scan(0); 
	if(tp_dev.sta&TP_PRES_DOWN)			//������������
	{
		if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
		{
				if(tp_dev.x[0]>0&&tp_dev.x[0]<240&&tp_dev.y[0]>290&&tp_dev.y[0]<320)   //ȡ��
			{
					people=0;
//					LCD_Clear(WHITE); 
					delay_ms(100);
					
			}
		}
	}
}

void gly_id_save(void)
{
	u8 id1,id2,id3;
	id1=AT24CXX_ReadOneByte(60);
	id2=AT24CXX_ReadOneByte(61);
	id3=AT24CXX_ReadOneByte(62);
	gly_id=id1*100+id2*10+id3;
}




