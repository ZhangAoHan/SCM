/*
	控制函数
*/

#include "control.h"	
#include "text.h"	 
#include "lcd.h"
#include "fdc2214.h"
u8 sca;        //报错标准量  0有错误  1正常
void FDC2214read(void)
{
	u8 i;
	//FDC2214read函数用到了一阶滤波  每次都要先给fre2_last赋值
	FDC2214_GetChannelData(FDC2214_Channel_1, &date2);
	fre2 = FDC2214_CalculateFrequency(FDC2214_Channel_1, date2); 
	fre2_last=fre2;	
	
	for(i=0;i<30;i++)
	{
        FDC2214_GetChannelData(FDC2214_Channel_1, &date2);
	    fre2 = FDC2214_CalculateFrequency(FDC2214_Channel_1, date2);    
	//算术平均滤波
		result2	=result2+fre2;
		i++;
	}
	fre2=result2/30;
	fre2=result2/30*0.8+fre2_last*0.2;
	fre2_last=fre2;
	result2=0;
}


//猜拳界面  训练函数
void C_control(void)
{
	u8 i;
	switch(mode_selsct)
	{
		case 1:
			{
				for(i=0;i<10;i++)   //延时  减小按键手势对波动的影响
				{
					FDC2214read();
					fre2_init_min=fre2_init_max=fre2;   //赋初值
				}
				POINT_COLOR=RED;    //红色显示  表示开始训练
				Show_Str(11,180,48,24,"石头",24,0);
				while(ch2_wave<1200)
				{
					Scan_sjb();     //学习阈值		
					POINT_COLOR=BLACK;
					LCD_ShowxNum(96,94,fre2,8,16,0);	
					LCD_ShowxNum(60,184,ch2_middle,8,16,0);	   //显示阈值
					LCD_ShowxNum(130,184,ch2_wave,5,16,0);    //显示波动范围
				}
				sy2=ch2_middle;
				sb2=ch2_wave;
				ch2_middle=0;
				ch2_wave=0;
				POINT_COLOR=BLUE;    //蓝色显示  表示训练完成
				Show_Str(11,180,48,24,"石头",24,0);
				mode_selsct=0;
			} break;
		case 2:
			{
				for(i=0;i<10;i++)   //延时  减小按键手势对波动的影响
					{
						FDC2214read();
						fre2_init_min=fre2_init_max=fre2;   //赋初值
					}
				POINT_COLOR=RED;
				Show_Str(11,210,48,24,"剪刀",24,0);
				FDC2214read();
				fre2_init_min=fre2_init_max=fre2;   //赋初值
				while(ch2_wave<300)
					{
						Scan_sjb();     //学习阈值		
						POINT_COLOR=BLACK;
						LCD_ShowxNum(96,94,fre2,8,16,0);	
						LCD_ShowxNum(60,214,ch2_middle,8,16,0);	   //显示阈值
						LCD_ShowxNum(130,214,ch2_wave,5,16,0);    //显示波动范围
					}
				jy2=ch2_middle;
				jb2=ch2_wave;
				ch2_middle=0;
				ch2_wave=0;
				POINT_COLOR=BLUE;  
				Show_Str(11,210,48,24,"剪刀",24,0);
				mode_selsct=0;
			} break;
		case 3:
			{
				for(i=0;i<10;i++)   //延时  减小按键手势对波动的影响
					{
						FDC2214read();
						fre2_init_min=fre2_init_max=fre2;   //赋初值
					}
				POINT_COLOR=RED;
				Show_Str(11,240,48,24,"布",24,0);
				FDC2214read();
				fre2_init_min=fre2_init_max=fre2;   //赋初值
				while(ch2_wave<700)
					{
						Scan_sjb();     //学习阈值		
						POINT_COLOR=BLACK;
						LCD_ShowxNum(96,94,fre2,8,16,0);	
						LCD_ShowxNum(60,244,ch2_middle,8,16,0);	   //显示阈值
						LCD_ShowxNum(130,244,ch2_wave,5,16,0);    //显示波动范围
					}
				by2=ch2_middle;
				bb2=ch2_wave;
				ch2_middle=0;
				ch2_wave=0;
				POINT_COLOR=BLUE;  
				Show_Str(11,240,48,24,"布",24,0);
				mode_selsct=0;
			} break;
	}
	//显示测的值  ，使系统具有存储功能
		POINT_COLOR=BLACK;
		LCD_ShowxNum(60,184,sy2,8,16,0);	   //显示阈值
		LCD_ShowxNum(130,184,sb2,5,16,0);    //显示波动范围
		LCD_ShowxNum(60,214,jy2,8,16,0);	   //显示阈值
		LCD_ShowxNum(130,214,jb2,5,16,0);    //显示波动范围
		LCD_ShowxNum(60,244,by2,8,16,0);	   //显示阈值
		LCD_ShowxNum(130,244,bb2,5,16,0);    //显示波动范围
			//显示通道的返回值
		POINT_COLOR=BLACK;
		LCD_ShowxNum(96,94,fre2,8,16,0);	
}

void S_control(void)
{
	u8 i;
	POINT_COLOR=RED;        //红色字体
	Show_Str(11,90,84,24,"通道2：",24,0);
	switch(mode_selsct)
	{
		case 1:
			{
				for(i=0;i<10;i++)   //延时  减小按键手势对波动的影响
					{
						FDC2214read();
						fre2_init_min=fre2_init_max=fre2;   //赋初值
					}
				POINT_COLOR=RED;
				Show_Str(11,150,60,24,"测1",24,0);
				FDC2214read();
				fre2_init_min=fre2_init_max=fre2;   //赋初值
				while(ch2_wave<300)
					{
						Scan_sjb();     //学习阈值		
						POINT_COLOR=BLACK;
						LCD_ShowxNum(96,94,fre2,8,16,0);	
						LCD_ShowxNum(60,154,ch2_middle,8,16,0);	   //显示阈值
						LCD_ShowxNum(130,154,ch2_wave,5,16,0);    //显示波动范围
					}
				y1=ch2_middle;
				b1=ch2_wave;
				ch2_middle=0;
				ch2_wave=0;
				POINT_COLOR=BLUE;  
				Show_Str(11,150,48,24,"测1",24,0);
				mode_selsct=0;
			} break;
		case 2:
		{
			for(i=0;i<10;i++)   //延时  减小按键手势对波动的影响
				{
					FDC2214read();
					fre2_init_min=fre2_init_max=fre2;   //赋初值
				}
			POINT_COLOR=RED;
			Show_Str(11,180,48,24,"测2",24,0);
			FDC2214read();
			fre2_init_min=fre2_init_max=fre2;   //赋初值
			while(ch2_wave<350)
				{
					Scan_sjb();     //学习阈值		
					POINT_COLOR=BLACK;
					LCD_ShowxNum(96,94,fre2,8,16,0);	
					LCD_ShowxNum(60,184,ch2_middle,8,16,0);	   //显示阈值
					LCD_ShowxNum(130,184,ch2_wave,5,16,0);    //显示波动范围
				}
			y2=ch2_middle;
			b2=ch2_wave;
			ch2_middle=0;
			ch2_wave=0;
			POINT_COLOR=BLUE;  
			Show_Str(11,180,48,24,"测2",24,0);
			mode_selsct=0;
		} break;
		case 3:
		{
			for(i=0;i<10;i++)   //延时  减小按键手势对波动的影响
				{
					FDC2214read();
					fre2_init_min=fre2_init_max=fre2;   //赋初值
				}
			POINT_COLOR=RED;
			Show_Str(11,210,48,24,"测3",24,0);
			FDC2214read();
			fre2_init_min=fre2_init_max=fre2;   //赋初值
			while(ch2_wave<400)
				{
					Scan_sjb();     //学习阈值		
					POINT_COLOR=BLACK;
					LCD_ShowxNum(96,94,fre2,8,16,0);	
					LCD_ShowxNum(60,214,ch2_middle,8,16,0);	   //显示阈值
					LCD_ShowxNum(130,214,ch2_wave,5,16,0);    //显示波动范围
				}
			y3=ch2_middle;
			b3=ch2_wave;
			ch2_middle=0;
			ch2_wave=0;
			POINT_COLOR=BLUE;  
			Show_Str(11,210,48,24,"测3",24,0);
			mode_selsct=0;
		} break;
		case 4:
		{
			for(i=0;i<10;i++)   //延时  减小按键手势对波动的影响
				{
					FDC2214read();
					fre2_init_min=fre2_init_max=fre2;   //赋初值
				}
			POINT_COLOR=RED;
			Show_Str(11,240,48,24,"测4",24,0);
			FDC2214read();
			fre2_init_min=fre2_init_max=fre2;   //赋初值
			while(ch2_wave<450)
				{
					Scan_sjb();     //学习阈值		
					POINT_COLOR=BLACK;
					LCD_ShowxNum(96,94,fre2,8,16,0);	
					LCD_ShowxNum(60,244,ch2_middle,8,16,0);	   //显示阈值
					LCD_ShowxNum(130,244,ch2_wave,5,16,0);    //显示波动范围
				}
			y4=ch2_middle;
			b4=ch2_wave;
			ch2_middle=0;
			ch2_wave=0;
			POINT_COLOR=BLUE;  
			Show_Str(11,240,48,24,"测4",24,0);
			mode_selsct=0;
		} break;
		case 5:
		{
			for(i=0;i<10;i++)   //延时  减小按键手势对波动的影响
				{
					FDC2214read();
					fre2_init_min=fre2_init_max=fre2;   //赋初值
				}
			POINT_COLOR=RED;
			Show_Str(11,270,48,24,"测5",24,0);
			FDC2214read();
			fre2_init_min=fre2_init_max=fre2;   //赋初值
			while(ch2_wave<500)
				{
					Scan_sjb();     //学习阈值		
					POINT_COLOR=BLACK;
					LCD_ShowxNum(96,94,fre2,8,16,0);	
					LCD_ShowxNum(60,274,ch2_middle,8,16,0);	   //显示阈值
					LCD_ShowxNum(130,274,ch2_wave,5,16,0);    //显示波动范围
				}
			y5=ch2_middle;
			b5=ch2_wave;
			ch2_middle=0;
			ch2_wave=0;
			POINT_COLOR=BLUE;  
			Show_Str(11,270,48,24,"测5",24,0);
			mode_selsct=0;	
		} break;
		
	}
	//显示测的值  ，使系统具有存储功能
			POINT_COLOR=BLACK;
			LCD_ShowxNum(60,154,y1,8,16,0);	   //显示阈值
			LCD_ShowxNum(130,154,b1,5,16,0);    //显示波动范围
			LCD_ShowxNum(60,184,y2,8,16,0);	   //显示阈值
			LCD_ShowxNum(130,184,b2,5,16,0);    //显示波动范围
			LCD_ShowxNum(60,214,y3,8,16,0);	   //显示阈值
			LCD_ShowxNum(130,214,b3,5,16,0);    //显示波动范围
			LCD_ShowxNum(60,244,y4,8,16,0);	   //显示阈值
			LCD_ShowxNum(130,244,b4,5,16,0);    //显示波动范围
			LCD_ShowxNum(60,274,y5,8,16,0);	   //显示阈值
			LCD_ShowxNum(130,274,b5,5,16,0);    //显示波动范围
			POINT_COLOR=BLACK;
			LCD_ShowxNum(96,94,fre2,8,16,0);	
}
  //训练函数
void Scan_sjb(void)  
{
	FDC2214read();
	if(fre2<fre2_init_min) fre2_init_min=fre2;
	if(fre2>fre2_init_max) fre2_init_max=fre2;
	ch2_middle=(fre2_init_min+fre2_init_max)/2;
	ch2_wave=((ch2_middle-fre2_init_min)+(fre2_init_max-ch2_middle))/2;
			
}
//反馈函数
void C_Feedback(void)
{
	Scan(0);
	if(sca)                     //如果正常
	{
		if(fre2>sy2&&(fre2-sy2)<(sb2*1.5))   Show_Str(11,30,48,24,"石头",24,0);   //检测到石头

		else if(fre2<sy2&&(sy2-fre2)<(sb2*1.5))   Show_Str(11,30,48,24,"石头",24,0);  //检测到石头

		
		else if(fre2>jy2&&(fre2-jy2)<(jb2*1.5))  Show_Str(11,30,48,24,"剪刀",24,0);   //检测到剪刀

		else if(fre2<jy2&&(jy2-fre2)<(jb2*1.5))  Show_Str(11,30,48,24,"剪刀",24,0);     //检测到剪刀

		else if(fre2>by2&&(fre2-by2)<(bb2*1.5))  Show_Str(11,30,48,24,"  布",24,0);     //检测到布

		else if(fre2<by2&&(by2-fre2)<(bb2*1.5)) Show_Str(11,30,48,24,"  布",24,0);     //检测到布

		else Show_Str(1,30,240,24,"            ",24,0); 
		sca=0;                        
	}

}
void S_Feedback(void)
{
	Scan(1);
	if(sca)
	{
		if(fre2>y1&&(fre2-y1)<(b1*1.5))   Show_Str(11,30,48,24,"1",24,0);   

		else if(fre2<y1&&(y1-fre2)<(b1*1.5))   Show_Str(11,30,48,24,"1",24,0);  
		
		else if(fre2>y2&&(fre2-y2)<(b2*1.5))   Show_Str(11,30,48,24,"2",24,0);   

		else if(fre2<y2&&(y2-fre2)<(b2*1.5))   Show_Str(11,30,48,24,"2",24,0);  

		else if(fre2>y3&&(fre2-y3)<(b3*1.5))   Show_Str(11,30,48,24,"3",24,0);  

		else if(fre2<y3&&(y3-fre2)<(b3*1.5))   Show_Str(11,30,48,24,"3",24,0);
		
		else if(fre2>y4&&(fre2-y4)<(b4*1.5))   Show_Str(11,30,48,24,"4",24,0);  

		else if(fre2<y4&&(y4-fre2)<(b4*1.5))   Show_Str(11,30,48,24,"4",24,0); 
		
		else if(fre2>y5&&(fre2-y5)<(b5*1.5))   Show_Str(11,30,48,24,"5",24,0);  

		else if(fre2<y5&&(y5-fre2)<(b5*1.5))   Show_Str(11,30,48,24,"5",24,0); 	

		else Show_Str(11,30,240,24,"0",24,0); 
		sca=0;
	}

}

/*
	检测函数
	1：架子摆好后外部新进人员离架子距离大于10cm 影响可以忽略不计   即不需要管环境对空载值的影响
2：报错检测   学习完成之后会进入一个检测环节  如果阈值+波动范围有冲突（报错 或 自动修改）  :
	3：
*/

void Scan(u8 d)
{
	switch(d)      //0 检测猜拳界面     1检测数字识别界面
	{
		case 0:      //猜拳界面主要检测不和拳头   减少检测试剂
		{
			if(by2>sy2&&(by2-sy2)>((bb2+sb2)*1.5))    //测试正常
			{
				Show_Str(110,1,96,24,"测试正常",24,0);	
				sca=1;      
			}
			else
			{
				Show_Str(110,1,96,24,"测试错误",24,0);	
				by2=sy2=bb2=sb2=0;          //测试结果清零  重测
			}
		}break;
		case 1:    //数字识别检测  按顺序检测 减少检测时间
		{
			//检测手指1和2
			if(y1>y2&&(y1-y2)>((b1+b2)*1.5))
			{
				Show_Str(110,1,96,24,"测试正常",24,0);	
				sca=1;  
			}
			else
			{
				Show_Str(110,1,96,24,"测试错误",24,0);	
				y1=y2=b2=b1=0;          //测试结果清零  重测
			}
			//检测手指2和3			
			if(y2>y3&&(y2-y3)>((b2+b3)*1.5))
			{
				Show_Str(110,1,96,24,"测试正常",24,0);	
				sca=1;  
			}
			else
			{
				Show_Str(110,1,96,24,"测试错误",24,0);	
				y3=y2=b2=b3=0;          //测试结果清零  重测				
			}
			//检测手指3和4			
			if(y3>y4&&(y3-y4)>((b3+b4)*1.5))
			{
				Show_Str(110,1,96,24,"测试正常",24,0);	
				sca=1;  
			}
			else
			{
				Show_Str(110,1,96,24,"测试错误",24,0);	
				y3=y4=b4=b3=0;          //测试结果清零  重测				
			}
			//检测手指4和5
			if(y4>y5&&(y4-y5)>((b4+b5)*1.5))
			{
				Show_Str(110,1,96,24,"测试正常",24,0);	
				sca=1;  
			}
			else
			{
				Show_Str(110,1,96,24,"测试错误",24,0);	
				y4=y5=b5=b4=0;          //测试结果清零  重测				
			}			
		}
	}
}
