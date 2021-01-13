/*************************************************************
                      ƽ����תLED����
��Ƭ�� STC12C5A32S2  
�������߹��緽�� ��ת�����ǳ�����
��ģ����õ�PC2002
ʵ�ֹ��ܣ�1��ƽ����ʾ��
		  2��ƽ����ʾ����ʱ�� ������ ���� �������DS18B20 ������ʾ�¶� ��ʱ�ӿɵ� ʱ��оƬ��DS1302 ���󱸵�� ����ʱ�Ӽ�����ʱ��
		  3��ƽ����ʾģ�����ʱ�� 12��3��6��9��ʾ ָ�����ͷ����������ϵ���̻�����Ӧ��ת�ٶȣ����о������ȶ�ʱ ���°���TEST �Ա��������
		  	 ��������Ӧ��������ʡCPU����ʱ�䣬�����������΢��������ͨ��ң�����ġ���������͡����˼����Ե���ʱ����е����������󱣴浽DS1302RAM�У�
		  4������ʱ��ģʽ����ʾʱ���� �Լ���ʾ����
		  5��ͼƬ��ʾģʽ ��8�� ��ͨ������ң�ذ��� ��+�����ߡ�-�� ���л�
		  6������Ч��������λ���������������
		  
�����д��Fucp 
�����գ�13-8-29

�׼����ۣ�http://59tiaoba.taobao.com
���͵�ַ��http://hi.baidu.com/fcping/blog/item/71aaa1ec9c3743f2cf1b3eaa.html?timeStamp=1323178049250
***************************************************************/
//#include "NEW_8051.H"
#include "task.h"

#include <stddef.h>

#define ucNumRows 108 //����һ����ʾ�ָ��� һ����16�� 108/16=8����



uchar Delay=1 ;
bit BIT_timeout=0;
//bit Scan_bit=0;
uint uitime=0;
uint S=0;
uint uiicount=0;
uint uiCountFontNumber;
uchar ucMode=1;
data uint uiicountTwo=0;

uchar ucPCA0_TimeCount;
bit Time0_flag=0;	//��ʱ��T0�жϱ�־λ

uint addr;
uchar OffsetAdder=0;//ͼƬ��ַ��
bit AutoSwitch=1;
uchar DelayTimeCount=0;
uchar  Row=0;
uint S0,T,D;		//�����õı���
uchar DISP_LINE=0;
uchar DISP_LINEE=0;
uchar k;
void delay_200ms(void) ;
uchar code liushui[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};	// ������λ ��ˮ����

/***************ģ����̱���**************/
// uint DISP_LINE=0;
 uchar DISP_LINE_ADJ=0;
 uchar DISP_TIME_ADJ=0;
 uchar Time0_count=0;
 uchar ucAdder=0;

 uchar code TAB_12369[]=
 {

	0xFF,0x03,0xFF,0xB3,0x6B,0x6B,0x9B,0xFF,		
	0x8F,0x77,0x7F,0x8F,0x7F,0x77,0x8F,0xFF,//3
	0xFF,0xFF,0x9F,0x6D,0x6D,0x6B,0x87,0xFF,//6	
	0x9F,0xEF,0xF7,0x87,0x77,0x77,0x8F,0xFF,///9


 };
/*********��ʱ�ӳ���**********/
void delay(unsigned char n)	//ÿ����ʾ��ʱ��
{
	unsigned char a,b;
	for(;n>0;n--)
	{    	
		for(b=100;b>0;b--)
        for(a=2;a>0;a--);
	}
}

/*********PCA�ж��ӳ���**********/
void PCA() interrupt 7	//PCA��ʱ��	��ʱ��˸
{
    if( CCF0 )
	{
		CCF0 = 0;
		CL = 0;
    	CH = 0;
		ucPCA0_TimeCount++;
		if(ucPCA0_TimeCount>12)
		{
			ucPCA0_TimeCount=0;	//��ʱ��˸
			if(ucMode==2)
			 {
			 	flag=~flag;
			 }
			 
		}
	}
}
/************************************/
void Timer0Interrupt(void) interrupt 1
{			 
    Time0_flag=1;	           //��ʱ�жϱ�־λ��1;
	TH0=-Pt/256;TL0=-Pt%256;   //���ö�ʱ��T0�ĳ���ֵ
	DISP_LINE++; 
	DISP_LINEE++;                   //����

}
/************************************************************/
//ͼƬ�л��Լ�ģ�������ʾ����
void display_pic()
{
	uchar date1,date2,date3,date4;
	if(DISP_LINE<180)
	{
		if(Time0_flag)
		{
		 	Time0_flag=0;
			OEA=OEB=OEC=1;
			P2=0XFF;
			LED=0;
			if(ucMode==4)
			{
					 if(DISP_LINEE==180)
					 DISP_LINEE=0;
					if((DISP_LINEE>=0)&&DISP_LINEE<8)	//�� ��λ
					{
						Send_data_C(shuzi[Cent%10][DISP_LINEE]);	
						OEC=0;	
					}
					else if(DISP_LINEE>7&&DISP_LINEE<16)	//����
					{
						Send_data_C(shuzi[10][DISP_LINEE-8]);	
						OEC=0;	
					}
					else if(DISP_LINEE>15&&DISP_LINEE<24)	//�� ʮλ
					{
						Send_data_C(shuzi[Sec/10][DISP_LINEE-16]);	
						OEC=0;	
					}
					else if(DISP_LINEE>23&&DISP_LINEE<32)	//�� ��λ
					{
						Send_data_C(shuzi[Sec%10][DISP_LINEE-24]);	
						OEC=0;	
					}
					else if((DISP_LINEE>147)&&(DISP_LINEE<156))
					{
						ucAdder=DISP_LINEE-148;
						Send_data_C(shuzi[Hour/10][ucAdder]);//ʱ ʮλ	
						OEC=0;
					}
					else if((DISP_LINEE>155)&&(DISP_LINEE<164))	
					{
						ucAdder=DISP_LINEE-156;
						Send_data_C(shuzi[Hour%10][ucAdder]);//ʱ ��λ	
						OEC=0;	
					}
					else if((DISP_LINEE>163)&&(DISP_LINEE<172))	//����
					{
						ucAdder=DISP_LINEE-164;
						Send_data_C(shuzi[10][ucAdder]);	
						OEC=0;	
					}
					else if(DISP_LINEE>171&&DISP_LINEE<180)	//�� ʮλ
					{
						ucAdder=DISP_LINEE-172;
						Send_data_C(shuzi[Cent/10][ucAdder]);	
						OEC=0;	
					}
					Round_table(DISP_LINEE,Hour,Cent,Sec);
			}
			if(ucMode==3)
			{
				  //DISP_LINEE=DISP_LINEE-1;
				      //������,�Լ���ʾ����12,3,6,9
					  if(DISP_LINEE==180)
					 DISP_LINEE=0;
			      if ( (DISP_LINEE >= 175) || (DISP_LINEE <= 3))  //12��
			      {
			       ucAdder=DISP_LINEE+4 ;
			       if ( ucAdder>=180) ucAdder=ucAdder-180 ;
			      }
			      else if ( (DISP_LINEE >= 41) && (DISP_LINEE <= 48)) //3��
			      {
			       ucAdder=DISP_LINEE-41+8*1 ;
			      }
			      else if ( (DISP_LINEE >= 86) && (DISP_LINEE <= 93)) //6��
			      {
			       ucAdder=DISP_LINEE-86+8*2 ;
			      }
			      else if ( (DISP_LINEE >= 131) && (DISP_LINEE <= 138)) //9��
			      {
			       ucAdder=DISP_LINEE-131+8*3 ;
			      }
				  else
				  {
					 ucAdder=250;
					/*************�γɱ���*******************/
				   switch (DISP_LINEE)    
			       {
				        case 180*1/12 :    //1��
				        case 180*2/12 :    //2��
				        case 180*4/12 :    //4��
				        case 180*5/12 :    //5��
				        case 180*7/12 :    //6��
				        case 180*8/12 :    //7��
				        case 180*10/12 :   //10��
				        case 180*11/12 :   //11��
				          //LED=0;
						  Send_data_C(0X0F);
						  OEC=0;
				         break;
			       }
				   }
				   if ( ucAdder < 32 )
				    {
						Send_data_C(TAB_12369[ucAdder]) ; //�����ʾ12,3,6,9
						OEC=0;
					}
			   /****************************************/   
			   	  //��ʾָ��"ʱ"
			//	   i = Hour ;
			//       j = Hour ;
			//      if ( ++i > 179 ) i=0 ;    //i+1,���>179,������
			//      if ( --j > 179 ) i=179 ;   //j-1,���Ϊ��,�����¸�ֵ179
				if(( (Hour-2)<=DISP_LINEE)&&((Hour+2)>=DISP_LINEE) )
				{
					if(((Hour-1)==DISP_LINEE)||((Hour+1)==DISP_LINEE))
					{
						P2=0XFF;
						Send_data_A(0XBF);
						OEA=0;
					}
					else if(((Hour-2)==DISP_LINEE)||((Hour+2)==DISP_LINEE))
					{
						P2=0XFF;
						Send_data_A(0XDF);
						OEA=0;
					}	
				}
			   	if(Hour==DISP_LINEE)//||(DISP_LINEE==i)||(DISP_LINEE==j
			    {
			        
			        P2=0X80 ;
					Send_data_A(0X00);
					OEA=0;
			
			
			    }    
			    //��ʾָ��"��"
				if(( (Cent-2)<=DISP_LINEE)&&((Cent+2)>=DISP_LINEE) )
				{
					if(((Cent-1)==DISP_LINEE)||((Cent+1)==DISP_LINEE))
					{
						Send_data_A(0XFF);
						Send_data_B(0XFB);
						P2=0XFF;
						OEA=OEB=0;
					}	
					else if(((Cent-2)==DISP_LINEE)||((Cent+2)==DISP_LINEE))
					{
						Send_data_A(0XFF);
						Send_data_B(0XFD);
						P2=0XFF;
						OEA=OEB=0;
					}
					
				}
				if(Cent==DISP_LINEE)
			    {
			        //Send_data_B(0X00);
					Send_data_A(0X00);
					Send_data_B(0XF0);
					P2=0X80;
					OEA=OEB=0;
			       	
			    }
				//��ʾָ��"��"
				if(( (Sec-2)<=DISP_LINEE)&&((Sec+2)>=DISP_LINEE) )
				{
					if(((Sec-1)==DISP_LINEE)||((Sec+1)==DISP_LINEE))
					{
						Send_data_B(0XBF);
						Send_data_A(0XFF);
						P2=0XFF;
						OEA=OEB=0;
					}
					else if(((Sec-2)==DISP_LINEE)||((Sec+2)==DISP_LINEE))
					{
						Send_data_B(0XDF);
						Send_data_A(0XFF);
						P2=0XFF;
						OEA=OEB=0;
					}
						
				}
			    if(Sec==DISP_LINEE)
			    {
			        Send_data_B(0X00);
					Send_data_A(0X00);
					P2=0X80;
					OEA=OEB=0;
			       
			    }
				//DISP_LINEE=DISP_LINEE+1;
		
			}
			else if(ucMode==5)//11��ͼƬ��ʾ
				{
					   
					date1=byte_read(OffsetAdder*720+0x3A02+DISP_LINE*4);
					date2=byte_read(OffsetAdder*720+0x3A03+DISP_LINE*4);
					date3=byte_read(OffsetAdder*720+0x3A04+DISP_LINE*4);
					date4=byte_read(OffsetAdder*720+0x3A05+DISP_LINE*4);	
					dis_picture(date3,date4,date1,date2);
					//	DISP_LINE=DISP_LINE+1;
				}
				else if(ucMode==6)//����
				{
						//DISP_LINE=DISP_LINE+2;
//						date1=two_heart[DISP_LINE+OffsetAdder*180][0];
//						date2=two_heart[DISP_LINE+OffsetAdder*180][1];
//						date3=two_heart[DISP_LINE+OffsetAdder*180][2];
//						date4=two_heart[DISP_LINE+OffsetAdder*180][3];
//						dis_picture(date1,date2,date3,date4);
						//DISP_LINE=DISP_LINE-2;
					date1=byte_read(OffsetAdder*720+0x5202+DISP_LINE*4);
					date2=byte_read(OffsetAdder*720+0x5203+DISP_LINE*4);
					date3=byte_read(OffsetAdder*720+0x5204+DISP_LINE*4);
					date4=byte_read(OffsetAdder*720+0x5205+DISP_LINE*4);	
					dis_picture(date1,date2,date3,date4);
				}
//				else if(ucMode==7)//����
//				{
//						//DISP_LINE=DISP_LINE+2;
//						date1=hudie[DISP_LINE+OffsetAdder*180][0];
//						date2=hudie[DISP_LINE+OffsetAdder*180][1];
//						date3=hudie[DISP_LINE+OffsetAdder*180][2];
//						date4=hudie[DISP_LINE+OffsetAdder*180][3];
//						dis_picture(date1,date2,date3,date4);
//						//DISP_LINE=DISP_LINE-2;
//				}
		}		
	}
	else 	
	{
			OEA=OEB=OEC=1;
			P2=0XFF;
			LED=0;

	}
}

/*********�ж��ӳ���**********/
void int0() interrupt 0	//ʹ���ⲿ�ж�0
{
	if((ucMode==0x01)||(ucMode==0x02))
	{
		BIT_timeout=1;
	}
	else
	{		
		if(Auto==1)
		{
			D+=(DISP_LINE-178);   //����ֵ
	   		Pt=600+D; 
		}      //�õ���ʱ��T0�ĳ���ֵ
		TH0=-Pt/256;
		TL0=-Pt%256;   //���ö�ʱ��T0�ĳ���ֵ
		DISP_LINE=0;   //���������㣬�����¼���
		DISP_LINEE=128;	
		switch (ucMode)
		{
			case 0x06:
					if(++Row>=2)
					{
					   Row=0;
						OffsetAdder=OffsetAdder+1;
					   if(OffsetAdder>uiFontNumber_D)
						  OffsetAdder=0;
					}
				break;
			case 0x05:
				if(++Row>=100)
				{
				   Row=0;
				   if(AutoSwitch==1)
				   {
				   		OffsetAdder=OffsetAdder+1;
				   		if(OffsetAdder>uiFontNumber_P)
					 	OffsetAdder=0;
					}
				}	 
				break;
			case 0x03:
				du1302();//��ȡʱ��
				Sec=Sec/16*10+Sec%16 ;
        	    Cent=Cent/16*10+Cent%16 ;
        		Hour=Hour/16*10+Hour%16 ;
				if(Hour>11)
				{
					Hour=Hour-12;	
				}
			//	Hour=12-Hour;
				Sec=Sec*3;//���붨λ="��"*3
				Hour=(Hour*15)+(Cent/4);//ʱ�붨λ="ʱ"*15+"��"/4
				Cent=Cent*3;//���붨λ="��"*3	
				break;
			case 0x04:
				du1302();//��ȡʱ��
				Sec=Sec/16*10+Sec%16 ;
        	    Cent=Cent/16*10+Cent%16 ;
        		Hour=Hour/16*10+Hour%16 ;
				if(Hour>12)
				{
					Hour=Hour-12;	
				}
				break;
			default:
				break;
		}
		
	}		
}
/********************************/

/***************************************/
void OS_ALLRun(void)
{	
		if( new_code ) //�к��ⰴ��
		{
			//Send_data(key_code);
			new_code=0;
			switch( key_code ) //���ݲ�ͬ�İ���ִֵ�в�ͬ�Ķ���
			{
				
				case 0x44:   //��2�е�һ��
					Auto=~Auto;
					if(Auto==0)
					{
						write_1302Data(DISP_TIME_adder_L,Pt);//д��DS1302 RAM�б���
						write_1302Data(DISP_TIME_adder_H,Pt>>8);//д��DS1302 RAM�б���
						write_1302Data(Auto_adder,1);//д��DS1302 RAM�б���	
					}

				break;
				case 0x07://�����е�һ��
				
				 if((ucMode==3)||(ucMode==4)||(ucMode==5))
				 {				 	
					Pt++;
					write_1302Data(DISP_TIME_adder_L,Pt);//д��DS1302 RAM�б���
					write_1302Data(DISP_TIME_adder_H,Pt>>8);//д��DS1302 RAM�б���

				 }
				 else
				 {
				 	DelayTimeCount++;
				 }
				break;
	
				case 0x09:
				
				 if((ucMode==3)||(ucMode==4)||(ucMode==5))
				 {
				 	
					Pt--;
					write_1302Data(DISP_TIME_adder_L,Pt);//д��DS1302 RAM�б���
					write_1302Data(DISP_TIME_adder_H,Pt>>8);//д��DS1302 RAM�б���
				
				 }
				 else
				 {
				 	if(DelayTimeCount>0)
					{
						DelayTimeCount--;
						
					}
				 }
					
				break;
			   /*********************************/
				case 0x0C:
					ucMode=0x01;//ƽ����ʾ��ģʽ
					CR=0;
					TR0=0;
					P2=0XFF;
					OEA=1;
				break;

				case 0x18:
					TR0=0;
					CR=0;
					ucMode=0x02;//������ģʽ
					P2=0XFF;
				break;

				case 0x5E:
			
					//Pt=DISP_TIME_SET=R1302(DISP_TIME_adder+1);//��ȡ������ʾʱ��

					ucMode=0x03;//ָ��ʱ��ģʽ
					TR0=1;
			 		//CR=1;				 
					
				break;
				case 0x08:
					ucMode=0x04;//Բ��ʱ��ģʽ
					TR0=1;
			 		//CR=1;
					
				break;
				case 0x1C:
//					DISP_TIME_SET=R1302(DISP_TIME_adder+1);//��ȡ������ʾʱ��
//					if((DISP_TIME_SET>200)||(DISP_TIME_SET<50)) //��ֵֹ����	��С
//					{
//						DISP_TIME_SET=80;	
//					}
					ucMode=0x05;//ͼƬ��ʾģʽ
					OffsetAdder=0;//ƫ�Ƶ�ַΪ0
					TR0=1;
			 		CR=0;
				break;
				/********************************************************/
				case 0x5A:
//					DISP_TIME_SET=R1302(DISP_TIME_adder+1);//��ȡ������ʾʱ��
//					if((DISP_TIME_SET>200)||(DISP_TIME_SET<50)) //��ֵֹ����	��С
//					{
//						DISP_TIME_SET=80;	
//					}
					
					OffsetAdder=0;//ƫ�Ƶ�ַΪ0
					TR0=1;
			 		CR=0;
					ucMode=0x06;//�򵥶�����ʾģʽ
				break;
					/********************************************************/
				case 0x42:
					OffsetAdder=0;//ƫ�Ƶ�ַΪ0
					TR0=1;
			 		CR=0;
					ucMode=0x07;//�򵥶�����ʾģʽ
				break;
				/*********************************/
				case 0x40:	 //��ʱ��
				    if(ucMode==5)
					{
						if(OffsetAdder<uiFontNumber_P)//���8��ͼ
						OffsetAdder=OffsetAdder+1;
					}
					else if(ucMode==2)
					Set(id,1);
				break;

				case 0x19: //��ʱ��
					 if(ucMode==5)
					{
						if(OffsetAdder>0)//8��ͼ
							OffsetAdder=OffsetAdder-1;
						
					}
					else if(ucMode==2)
					Set(id,0); 
				break;
				
				case 0x15://��ʱ�л�
						if(ucMode==5)
						{
							AutoSwitch=~AutoSwitch;
						}
						else
						{
							id++;						
							//CCAPM0 = 0x49; //��PCA0�ж�
							//CCAPM1 = 0x00; //��PCA1�ж�
							CR=1;//����PCA����
	   						if(id>4)
							{
	    						id=0;
								CR=0;//�ر�PCA����
							//	CCAPM0 = 0x00;//��PCA0�ж�
							}
						}
				break;
					case 0x4A://ʱ�ӳ�ʼ��
						Set1302(starts_time);    //��ʼ�� 
						W1302(0x8e,0x00); //��������,WP=0,д����                
						W1302(0x90,0xa5); //��䵶����  һ�������ܴ���һ��2K�� 
//						write_1302Data(DISP_TIME_adder,130);
				break;

				default: break;
			}
		}
	if((ucMode==3)||(ucMode==4)||(ucMode==5)||(ucMode==6)||(ucMode==7))
	{
		display_pic();
	}
	else if(BIT_timeout)//��ʼ��
 	{			  
		BIT_timeout=0;
		Scan_bit=1;
		//DelayTime=TimeCount/(ucNumRows+60);	
		//TimeCount=0;	//��ʱ���ڼ�������
		switch (ucMode)
		{
			case 0x01://ƽ����ʾ��ģʽ
				//uiCountFontNumber++; 	
					P2=0XFF;
				Send_data_A(0xFF);				           
            	if( ++uiCountFontNumber >uiFontNumber) //uiFontNumber
	            {
	                
					uiCountFontNumber = 0;
					
	            }            
	            for( uiicount = uiCountFontNumber;uiicount<ucNumRows+uiCountFontNumber;uiicount++ )
	            {                               
	                				
					//Send_data_C(zimo_num1[uiicount*2]);//��ȡ���������Ļ����
	                //Send_data_B(zimo_num1[uiicount*2+1]);
					Send_data_C(byte_read(2+uiicount*2));	//��ȡ�ڲ�EEPROM��Ļ���� ������2��ַ�� ����Ҫ����2
					Send_data_B(byte_read(2+uiicount*2+1));
					
					OEB=OEC=0;
					delay(2);
					OEB=OEC=1;
	               if(BIT_timeout)
				   {
				   	  
					  break;
				   }
				}
				break;
			case 0x02:	//����ʱ��ģʽ
				du1302();
				read_temp();
				display();
				break;
			/*********************/
		
			default: break;
		}
		   
	}

//	if(Scan_bit==0)	//�������Թ������⣨����ⲻ���� ��ת����ֻ����ˮ������	 ��ˮ�ƿ��Լ��ƺ��ӵ��Ƿ�������
//	{
//			OEA=OEB=OEC=0;				
//			for(k=0;k<8;k++)
//			{				
//				ES=0;
//				Send_data_A(~liushui[k]);
//				P3=0X0F;
//				Send_data_B(~liushui[k]);
//				Send_data_C(~liushui[k]);
//				ES=1;
//				P2=~0x80>>k;			
//			    delay_200ms();

//			}				
//		
//	}
}
/*********************************************************/
void delay_200ms(void)
{
    unsigned char a,b,c;
    for(c=164;c>0;c--)
        for(b=212;b>0;b--)
            for(a=25;a>0;a--);
}
/*********************************************************************************/
/*************************************************************************************
************************************************************************************
***********************                                     ***************************
***********************    http://59tiaoba.taobao.com       ***************************
***********************                                     ***************************
**************************�����д��Fucp ******************************
**********************************************************************************/