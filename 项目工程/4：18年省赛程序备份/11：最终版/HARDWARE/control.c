/*
	���ƺ���
*/

#include "control.h"	
#include "text.h"	 
#include "lcd.h"
#include "fdc2214.h"
void FDC2214read(void)
{
	u8 i;
	//FDC2214read�����õ���һ���˲�  ÿ�ζ�Ҫ�ȸ�fre2_last��ֵ
	FDC2214_GetChannelData(FDC2214_Channel_2, &date2);
	fre2 = FDC2214_CalculateFrequency(FDC2214_Channel_2, date2); 
	fre2_last=fre2;	
	
	for(i=0;i<30;i++)
	{
        FDC2214_GetChannelData(FDC2214_Channel_2, &date2);
	    fre2 = FDC2214_CalculateFrequency(FDC2214_Channel_2, date2);    
	//����ƽ���˲�
		result2	=result2+fre2;
		i++;
	}
	fre2=result2/30;
	fre2=result2/30*0.8+fre2_last*0.2;
	fre2_last=fre2;
	result2=0;
}


//��ȭ����  ѵ������
void C_control(void)
{
	u8 i;
	switch(mode_selsct)
	{
		case 1:
			{
								POINT_COLOR=RED;    //��ɫ��ʾ  ��ʾ��ʼѵ��
				Show_Str(2,160,48,24,"ʯͷ",24,0);
				for(i=0;i<10;i++)   //��ʱ  ��С�������ƶԲ�����Ӱ��
				{
					FDC2214read();
					fre2_init_min=fre2_init_max=fre2;   //����ֵ
				}

				while(ch2_wave<1200)
				{
					Scan_sjb();     //ѧϰ��ֵ		
					POINT_COLOR=BLACK;
					LCD_ShowxNum(147,114,fre2,8,16,0);	
					LCD_ShowxNum(60,164,ch2_middle,8,16,0);	   //��ʾ��ֵ
					LCD_ShowxNum(154,164,ch2_wave,5,16,0);    //��ʾ������Χ
				}
				sy2=ch2_middle;
				sb2=ch2_wave;
				ch2_middle=0;
				ch2_wave=0;
				POINT_COLOR=BLUE;    //��ɫ��ʾ  ��ʾѵ�����
				Show_Str(2,160,48,24,"ʯͷ",24,0);
				mode_selsct=0;
			} break;
		case 2:
			{
								POINT_COLOR=RED;
				Show_Str(2,190,48,24,"����",24,0);
				for(i=0;i<10;i++)   //��ʱ  ��С�������ƶԲ�����Ӱ��
					{
						FDC2214read();
						fre2_init_min=fre2_init_max=fre2;   //����ֵ
					}

				while(ch2_wave<300)
					{
						Scan_sjb();     //ѧϰ��ֵ		
						POINT_COLOR=BLACK;
						LCD_ShowxNum(147,114,fre2,8,16,0);	
						LCD_ShowxNum(60,194,ch2_middle,8,16,0);	   //��ʾ��ֵ
						LCD_ShowxNum(154,194,ch2_wave,5,16,0);    //��ʾ������Χ
					}
				jy2=ch2_middle;
				jb2=ch2_wave;
				ch2_middle=0;
				ch2_wave=0;
				POINT_COLOR=BLUE;  
				Show_Str(2,190,48,24,"����",24,0);
				mode_selsct=0;
			} break;
		case 3:
			{
								POINT_COLOR=RED;
				Show_Str(2,220,48,24,"��",24,0);
				for(i=0;i<10;i++)   //��ʱ  ��С�������ƶԲ�����Ӱ��
					{
						FDC2214read();
						fre2_init_min=fre2_init_max=fre2;   //����ֵ
					}

				while(ch2_wave<700)
					{
						Scan_sjb();     //ѧϰ��ֵ		
						POINT_COLOR=BLACK;
						LCD_ShowxNum(147,114,fre2,8,16,0);	
						LCD_ShowxNum(60,224,ch2_middle,8,16,0);	   //��ʾ��ֵ
						LCD_ShowxNum(154,224,ch2_wave,5,16,0);    //��ʾ������Χ
					}
				by2=ch2_middle;
				bb2=ch2_wave;
				ch2_middle=0;
				ch2_wave=0;
				POINT_COLOR=BLUE;  
				Show_Str(2,220,48,24,"��",24,0);
				mode_selsct=0;
			} break;
	}
	//��ʾ���ֵ  ��ʹϵͳ���д洢����
		POINT_COLOR=BLACK;
		LCD_ShowxNum(60,164,sy2,8,16,0);	   //��ʾ��ֵ
		LCD_ShowxNum(154,164,sb2,5,16,0);    //��ʾ������Χ
		LCD_ShowxNum(60,194,jy2,8,16,0);	   //��ʾ��ֵ
		LCD_ShowxNum(154,194,jb2,5,16,0);    //��ʾ������Χ
		LCD_ShowxNum(60,224,by2,8,16,0);	   //��ʾ��ֵ
		LCD_ShowxNum(154,224,bb2,5,16,0);    //��ʾ������Χ
			//��ʾͨ���ķ���ֵ
		POINT_COLOR=BLACK;
		LCD_ShowxNum(147,114,fre2,8,16,0);	
}

void S_control(void)
{
	u8 i;
	switch(mode_selsct)
	{
		case 1:
			{
								POINT_COLOR=RED;
				Show_Str(2,162,48,24,"��1",24,0);
				for(i=0;i<10;i++)   //��ʱ  ��С�������ƶԲ�����Ӱ��
					{
						FDC2214read();
						fre2_init_min=fre2_init_max=fre2;   //����ֵ
					}

				while(ch2_wave<300)
					{
						Scan_sjb();     //ѧϰ��ֵ		
						POINT_COLOR=BLACK;
						LCD_ShowxNum(147,114,fre2,8,16,0);	
						LCD_ShowxNum(60,166,ch2_middle,8,16,0);	   //��ʾ��ֵ
						LCD_ShowxNum(154,166,ch2_wave,5,16,0);    //��ʾ������Χ
					}
				y1=ch2_middle;
				b1=ch2_wave;
				ch2_middle=0;
				ch2_wave=0;
				POINT_COLOR=BLUE;  
				Show_Str(2,162,48,24,"��1",24,0);
				mode_selsct=0;
			} break;
		case 2:
		{
						POINT_COLOR=RED;
			Show_Str(2,190,48,24,"��2",24,0);
			for(i=0;i<10;i++)   //��ʱ  ��С�������ƶԲ�����Ӱ��
				{
					FDC2214read();
					fre2_init_min=fre2_init_max=fre2;   //����ֵ
				}

			while(ch2_wave<350)
				{
					Scan_sjb();     //ѧϰ��ֵ		
					POINT_COLOR=BLACK;
					LCD_ShowxNum(147,114,fre2,8,16,0);	
					LCD_ShowxNum(60,194,ch2_middle,8,16,0);	   //��ʾ��ֵ
					LCD_ShowxNum(154,194,ch2_wave,5,16,0);    //��ʾ������Χ
				}
			y2=ch2_middle;
			b2=ch2_wave;
			ch2_middle=0;
			ch2_wave=0;
			POINT_COLOR=BLUE;  
			Show_Str(2,190,48,24,"��2",24,0);
			mode_selsct=0;
		} break;
		case 3:
		{
						POINT_COLOR=RED;
			Show_Str(2,220,48,24,"��3",24,0);
			for(i=0;i<10;i++)   //��ʱ  ��С�������ƶԲ�����Ӱ��
				{
					FDC2214read();
					fre2_init_min=fre2_init_max=fre2;   //����ֵ
				}

			while(ch2_wave<400)
				{
					Scan_sjb();     //ѧϰ��ֵ		
					POINT_COLOR=BLACK;
					LCD_ShowxNum(147,114,fre2,8,16,0);	
					LCD_ShowxNum(60,224,ch2_middle,8,16,0);	   //��ʾ��ֵ
					LCD_ShowxNum(154,224,ch2_wave,5,16,0);    //��ʾ������Χ
				}
			y3=ch2_middle;
			b3=ch2_wave;
			ch2_middle=0;
			ch2_wave=0;
			POINT_COLOR=BLUE;  
			Show_Str(2,220,48,24,"��3",24,0);
			mode_selsct=0;
		} break;
		case 4:
		{
			POINT_COLOR=RED;
			Show_Str(2,250,48,24,"��4",24,0);
			for(i=0;i<10;i++)   //��ʱ  ��С�������ƶԲ�����Ӱ��
				{
					FDC2214read();
					fre2_init_min=fre2_init_max=fre2;   //����ֵ
				}
			while(ch2_wave<450)
				{
					Scan_sjb();     //ѧϰ��ֵ		
					POINT_COLOR=BLACK;
					LCD_ShowxNum(147,114,fre2,8,16,0);	
					LCD_ShowxNum(60,254,ch2_middle,8,16,0);	   //��ʾ��ֵ
					LCD_ShowxNum(154,254,ch2_wave,5,16,0);    //��ʾ������Χ
				}
			y4=ch2_middle;
			b4=ch2_wave;
			ch2_middle=0;
			ch2_wave=0;
			POINT_COLOR=BLUE;  
			Show_Str(2,250,48,24,"��4",24,0);
			mode_selsct=0;
		} break;
		case 5:
		{
			POINT_COLOR=RED;
			Show_Str(2,280,48,24,"��5",24,0);
			for(i=0;i<10;i++)   //��ʱ  ��С�������ƶԲ�����Ӱ��
				{
					FDC2214read();
					fre2_init_min=fre2_init_max=fre2;   //����ֵ
				}
			while(ch2_wave<500)
				{
					Scan_sjb();     //ѧϰ��ֵ		
					POINT_COLOR=BLACK;
					LCD_ShowxNum(147,114,fre2,8,16,0);	
					LCD_ShowxNum(60,284,ch2_middle,8,16,0);	   //��ʾ��ֵ
					LCD_ShowxNum(154,284,ch2_wave,5,16,0);    //��ʾ������Χ
				}
			y5=ch2_middle;
			b5=ch2_wave;
			ch2_middle=0;
			ch2_wave=0;
			POINT_COLOR=BLUE;  
			Show_Str(2,280,48,24,"��5",24,0);
			mode_selsct=0;	
		} break;
		
	}
	//��ʾ���ֵ  ��ʹϵͳ���д洢����
			POINT_COLOR=BLACK;
			LCD_ShowxNum(60,166,y1,8,16,0);	   //��ʾ��ֵ
			LCD_ShowxNum(154,166,b1,5,16,0);    //��ʾ������Χ
			LCD_ShowxNum(60,194,y2,8,16,0);	   //��ʾ��ֵ
			LCD_ShowxNum(154,194,b2,5,16,0);    //��ʾ������Χ
			LCD_ShowxNum(60,224,y3,8,16,0);	   //��ʾ��ֵ
			LCD_ShowxNum(154,224,b3,5,16,0);    //��ʾ������Χ
			LCD_ShowxNum(60,254,y4,8,16,0);	   //��ʾ��ֵ
			LCD_ShowxNum(154,254,b4,5,16,0);    //��ʾ������Χ
			LCD_ShowxNum(60,284,y5,8,16,0);	   //��ʾ��ֵ
			LCD_ShowxNum(154,284,b5,5,16,0);    //��ʾ������Χ
			POINT_COLOR=BLACK;
			LCD_ShowxNum(147,114,fre2,8,16,0);	
}
  //ѵ������
void Scan_sjb(void)  
{
	FDC2214read();
	if(fre2<fre2_init_min) fre2_init_min=fre2;
	if(fre2>fre2_init_max) fre2_init_max=fre2;
	ch2_middle=(fre2_init_min+fre2_init_max)/2;
	ch2_wave=((ch2_middle-fre2_init_min)+(fre2_init_max-ch2_middle))/2;
			
}
//��������
void C_Feedback(void)
{
		if(fre2>sy2&&(fre2-sy2)<(sb2*1.5))   Show_Str(170,30,48,24,"ʯͷ",24,0),fj_resut=1;   //��⵽ʯͷ

		else if(fre2<sy2&&(sy2-fre2)<(sb2*1.5))   Show_Str(170,30,48,24,"ʯͷ",24,0),fj_resut=1;  //��⵽ʯͷ

		
		else if(fre2>jy2&&(fre2-jy2)<(jb2*1.5))  Show_Str(170,30,48,24,"����",24,0),fj_resut=2;   //��⵽����

		else if(fre2<jy2&&(jy2-fre2)<(jb2*1.5))  Show_Str(170,30,48,24,"����",24,0),fj_resut=2;     //��⵽����

		else if(fre2>by2&&(fre2-by2)<(bb2*1.5))  Show_Str(170,30,48,24,"  ��",24,0),fj_resut=3;     //��⵽��

		else if(fre2<by2&&(by2-fre2)<(bb2*1.5)) Show_Str(170,30,48,24,"  ��",24,0),fj_resut=3;     //��⵽��

		else Show_Str(170,30,48,24,"    ",24,0);                    
}
void S_Feedback(void)
{
		if(fre2>y1&&(fre2-y1)<(b1*1.5))        Show_Str(170,30,48,24,"1",24,0);   

		else if(fre2<y1&&(y1-fre2)<(b1*1.5))   Show_Str(170,30,48,24,"1",24,0);  
		
		else if(fre2>y2&&(fre2-y2)<(b2*1.5))   Show_Str(170,30,48,24,"2",24,0);   

		else if(fre2<y2&&(y2-fre2)<(b2*1.5))   Show_Str(170,30,48,24,"2",24,0);  

		else if(fre2>y3&&(fre2-y3)<(b3*1.5))   Show_Str(170,30,48,24,"3",24,0);  

		else if(fre2<y3&&(y3-fre2)<(b3*1.5))   Show_Str(170,30,48,24,"3",24,0);
		
		else if(fre2>y4&&(fre2-y4)<(b4*1.5))   Show_Str(170,30,48,24,"4",24,0);  

		else if(fre2<y4&&(y4-fre2)<(b4*1.5))   Show_Str(170,30,48,24,"4",24,0); 
		
		else if(fre2>y5&&(fre2-y5)<(b5*1.5))   Show_Str(170,30,48,24,"5",24,0);  

		else if(fre2<y5&&(y5-fre2)<(b5*1.5))   Show_Str(170,30,48,24,"5",24,0); 	

		else Show_Str(170,30,240,24,"0",24,0); 
}

/*
	��⺯��
	1�����Ӱںú��ⲿ�½���Ա����Ӿ������10cm Ӱ����Ժ��Բ���   ������Ҫ�ܻ����Կ���ֵ��Ӱ��
2��������   ѧϰ���֮������һ����⻷��  �����ֵ+������Χ�г�ͻ������ �� �Զ��޸ģ�  :
	3��
*/
