
#include "task.h"
bit flag;
uchar id;
uchar Tem=32;
/*********��ʱ�ӳ���**********/
void delay1(void)//18.432M 180us
{
	uchar a,b;
     for(b=115;b>0;b--)
        for(a=5;a>0;a--);
}
/*********************************************/
void OE_open(void)
{
	OEB=OEC=0;	
}
void OE_close(void)
{
	OEB=OEC=1;	
}
/**********************************************************/
void display(void)	
{	
	uchar i; 
/******************��ʾʱ��������**************************/
/**************************************************/   	 
	if((flag==1)&&(id==1))    //ʵ�ֵ�ʱ ����˸λ ������ͬ�� 
	{
		for(i=0;i<8;i++) 	  //������16��LEDʵ��ʱ����ʾ������ͬ��
		{	 
			OE_close(); //�ر���ʾ	//ʱ��ʮλ����ʾ������Ľ�Ͼ�ʵ������˸��
				 
			delay1();	 	
		}	 
	
	  //if(BIT_timeout)return;
		for(i=0;i<8;i++) 
		{ 
			OE_close(); //�ر���ʾ		//ʱ�ĸ�λ����ʾ	 	
			delay1();	 	
		}
	
		 //if(BIT_timeout)return;
	}
	else
	{
		for(i=0;i<8;i++) 			//������8��LEDʵ��ʱ����ʾ
		{	 
			Send_data_C(tab[Hour/16][i*2]);		//ʱ��ʮλ
			Send_data_B(tab[Hour/16][i*2+1]);
			Send_data_A(_8X8Number[tvalue/100][i]); //��ʾ�¶�ʮλ
			//Send_data_A(_8X8Number[Tem%10][i]); //��ʾ�¶ȸ�λ
			//595�½�������
			
			OE_open();//����ʾ
			OEA=0;		 	 
			delay1();	 	
		}
		OE_close(); //�ر���ʾ
		OEA=1;	 
	   //if(BIT_timeout)return;
		for(i=0;i<8;i++) 
		{ 
			Send_data_C(tab[Hour%16][i*2]);	//ʱ��	��λ
			Send_data_B(tab[Hour%16][i*2+1]);
			Send_data_A(_8X8Number[tvalue%100/10][i]); //��ʾ�¶ȸ�λ	
			
			//595�½�������
			
			OE_open();//����ʾ
			OEA=0;		 
			delay1();	 	
		}	
		OE_close(); //�ر���ʾ
		OEA=1;
		//if(BIT_timeout)return;
	}
/***********************************************************/	
	
	for(i=0;i<8;i++) 
	{ 
		Send_data_C(tab[10][i*2]);			//��ʾ����
		Send_data_B(tab[10][i*2+1]);
		Send_data_A(_8X8Number[12][i]); //��ʾС����
		OEA=0;
		OE_open();//����ʾ	 
		delay1();	 
	}
	OE_close(); //�ر���ʾ
	OEA=1;
	//if(BIT_timeout)
	//return;
/**************************************************/ 
	if((flag==1)&&(id==2))      
	{
		for(i=0;i<8;i++) 
		{ 
			OE_close(); //�ر���ʾ		 //�ֵ�ʮλ����ʾ	
			delay1();
		}
		
		if(BIT_timeout)return;
		for(i=0;i<8;i++) 
		{ 
			OE_close(); //�ر���ʾ		//�ֵĸ�λ����ʾ								 	 
			delay1();	 
		}
	
		//if(BIT_timeout)return;
	}
	else
	{	
		for(i=0;i<8;i++) 
		{ 
			Send_data_C(tab[Cent/16][i*2]);		//�ֵ� ʮλ
			Send_data_B(tab[Cent/16][i*2+1]);
			//Send_data_A(_8X8Number[11][i]); //��ʾ.
			Send_data_A(_8X8Number[tvalue%10][i]); //��ʾ�¶�С��λ
			
			//
			//595�½�������
			
			OE_open();//����ʾ
			OEA=0;
			delay1();	 	
		}
		OE_close(); //�ر���ʾ
		OEA=1;
		//if(BIT_timeout)return;
		for(i=0;i<8;i++) 
		{ 
			Send_data_C(tab[Cent%16][i*2]);		 //�ֵĸ�λ
			Send_data_B(tab[Cent%16][i*2+1]);
			Send_data_A(_8X8Number[11][i]); //��ʾ.//
			
			
			OE_open();//����ʾ
			OEA=0;						 	
			delay1();	 
		}
		OE_close(); //�ر���ʾ
		OEA=1;
		//if(BIT_timeout)return;

	}
	for(i=0;i<8;i++) 		 //��ʾ���� 
	{ 
		Send_data_C(tab[10][i*2]);
		Send_data_B(tab[10][i*2+1]);
		//Send_data_A(_8X8Number[12][i]); //��ʾm
		Send_data_A(_8X8Number[10][i]); //��ʾC
		//595�½�������
		
		OE_open();//����ʾ
		OEA=0;		
		delay1();	 
	}
	OE_close(); //�ر���ʾ
	OEA=1;
	//if(BIT_timeout)return;
	for(i=0;i<8;i++) 
	{ 
		Send_data_C(tab[Sec/16][i*2]);	   //���ʮλ
		Send_data_B(tab[Sec/16][i*2+1]);
		
		//595�½�������
		
		OE_open();//����ʾ	
		delay1();	 	 
	}
	OE_close(); //�ر���ʾ
   //if(BIT_timeout)return;
	for(i=0;i<8;i++) 
	{ 
		Send_data_C(tab[Sec%16][i*2]);		 //���	��λ
		Send_data_B(tab[Sec%16][i*2+1]);
		
		//595�½�������
		
		OE_open();//����ʾ 
		delay1();	 	 
	}
	OE_close(); //�ر���ʾ
	//OEA=1;
	//if(BIT_timeout)return;
	/*********************��ʾ��������***************************/
	delay1();	 //������ʱ�������� ��������ʱ����������
		delay1();
			delay1();
				delay1();
					delay1();
						delay1();
							delay1();
								delay1();
			delay1();
				delay1();
					delay1();
						delay1();
							delay1();
								delay1();
				delay1();
				delay1();
					delay1();
						delay1();
							delay1();
								delay1();
									delay1();
										delay1();
											delay1();
	/****************************************************/
/****************************************************/
	for(i=7;i>0;i--) 
	{ 
		Send_data_C(tab1[11][i*2]);					//���ַ�
		Send_data_B(tab1[11][i*2+1]);
			
		//595�½�������
		
		OE_open();//����ʾ		 
		delay1();	 	 
	}
	OE_close(); //�ر���ʾ
	//if(BIT_timeout)return;
	if((flag==1)&&(id==4)) 
	{
		for(i=8;i>0;i--) 
		{ 
			OE_close(); //�ر���ʾ		//���ڸ�λ����ʾ	 
			delay1();	 
		}
		  if(BIT_timeout)return;
		for(i=8;i>0;i--) 
		{ 
			OE_close(); //�ر���ʾ		//����ʮλ����ʾ
			delay1();		 
		}
		if(BIT_timeout)return;
	}
	else
	{
		for(i=8;i>0;i--) 
		{ 
			Send_data_C(tab1[Day%16][i*2]);				//���ڸ�λ
			Send_data_B(tab1[Day%16][i*2+1]);	
			
			//595�½�������
			
			OE_open();//����ʾ
			delay1();	 
		}
		OE_close(); //�ر���ʾ
		for(i=8;i>0;i--) 
		{ 
			Send_data_C(tab1[Day/16][i*2]);				 //����ʮλ
			Send_data_B(tab1[Day/16][i*2+1]);
				
			//595�½�������
			
			OE_open();//����ʾ
			delay1();	 
		}	
	}
OE_close(); //�ر���ʾ
	if(BIT_timeout)return;
/******************************************/

/************************************************************/
	for(i=8;i>0;i--)  
	{ 
		Send_data_C(tab1[10][i*2]);				   //���ַ�
		Send_data_B(tab1[10][i*2+1]);	
		
		//595�½�������
		
		OE_open();//����ʾ
		delay1();	 
	}
	OE_close(); //�ر���ʾ
	if(BIT_timeout)return;
    if((flag==1)&&(id==3))      
	{
		for(i=8;i>0;i--) 
		{   
			OE_close(); //�ر���ʾ		   //�µĸ�λ����ʾ	 
			delay1();	 
		}
	
	   if(BIT_timeout)return;
		for(i=8;i>0;i--)
		{ 
			OE_close(); //�ر���ʾ			 //�µ�ʮλ����ʾ	
			delay1();	 	 
		}
		if(BIT_timeout)return;
	}
	else
	{	
		for(i=8;i>0;i--) 
		{ 
			Send_data_C(tab1[Month%16][i*2]);		   //�µ� ��λ
			Send_data_B(tab1[Month%16][i*2+1]);
			
			//595�½�������
			
			OE_open();//����ʾ			
			delay1();	 	 
		}
		OE_close(); //�ر���ʾ
		if(BIT_timeout)return;	
		for(i=8;i>0;i--) 
		{ 
			Send_data_C(tab1[Month/16][i*2]);			 //�µ�	 ʮλ
			Send_data_B(tab1[Month/16][i*2+1]);
			
			//595�½�������
			
			OE_open();//����ʾ
			delay1();		 
		}
		
	}
		OE_close(); //�ر���ʾ
		//OEA=1;
	    //if(BIT_timeout)return;
/***********************************/


/******************��ʾ��������******************************/
	
//	if((flag==1)&&(id==5))
//	{
//	for(i=8;i>0;i--)
//	{ 
//		OE_close(); //�ر���ʾ	   //����ֵ����ʾ
//		delay1();	 
//	}
//	if(BIT_timeout)return;
//	} 
//	else
//	{
//		for(i=8;i>0;i--) 
//		{ 
//			Send_data_C(tab1[Week][i*2]);	   //����ֵ
//			Send_data_B(tab1[Week][i*2+1]);
//				
//			//595�½�������
//			
//			OE_open();//����ʾ	 
//			delay1();	 
//		}		
//	}
//	OE_close(); //�ر���ʾ
//	if(BIT_timeout)return;
}
/*********************************************************************************/
/*************************************************************************************
************************************************************************************
***********************                                     ***************************
***********************    http://59tiaoba.taobao.com       ***************************
***********************                                     ***************************
*******************************�����д��Fucp***************************************
**********************************************************************************/