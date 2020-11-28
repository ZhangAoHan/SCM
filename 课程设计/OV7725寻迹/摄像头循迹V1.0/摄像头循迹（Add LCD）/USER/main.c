#include "led.h"
#include "delay.h"
#include "sys.h"

#include "lcd.h"
#include "usart.h"	 
#include "ov7670.h"
#include "exti.h"
#include "motor.h"

u8 ov_sta;	//在exit.c里面定义
MOTOR GmLeft = {MOTOR_STOP,MOTOR_GOAHEAD,0,0,0};//定义并初始化左电机状态
MOTOR GmRight = {MOTOR_STOP,MOTOR_GOAHEAD,0,0,0};//定义并初始化右电机状态							 

u16 Array[60] ={
	 /*采集像素点矩阵【（46,150），（49,154）】 320列*/
	14870,14871,14872,14873,14874,
	15190,15191,15192,15193,15194,
	15510,15511,15512,15513,15514,
	15830,15831,15832,15833,15834,
	 /*采集像素点矩阵【（100,10），（104,13）】 320列*/
	32010,32011,32012,32013,			 
	32330,32331,32332,32333,
	32650,32651,32652,32653,
	32970,32971,32972,32973,
	33290,33291,33292,33293,
	/*采集像素点矩阵【（165,150），（168,154）】 320列  */
	52950,52951,52952,52953,52954,		 
	53270,53271,53272,53273,53274,
	53590,53591,53592,53593,53594,
	53910,53911,53912,53913,53914,

};
//更新LCD显示
u8 camera_refresh(void)
{
	u32 j;
	u8 k = 0;
 	u16 color;


	u8 whitepoint = 0;
	u8 leftblackpoint  = 0;
	u8 rightblackpoint = 0;
	u8 JudgeFlag = 0;
	
		 
	if(ov_sta==2)
	{
		LCD_Scan_Dir(U2D_L2R);		//从上到下,从左到右 
		LCD_SetCursor(0x00,0x0000);	//设置光标位置 
		LCD_WriteRAM_Prepare();     //开始写入GRAM	
		OV7670_RRST=0;				//开始复位读指针 
		OV7670_RCK=0;
		OV7670_RCK=1;
		OV7670_RCK=0;
		OV7670_RRST=1;				//复位读指针结束 
		OV7670_RCK=1; 

	
	for(j=0;j<76800;j++)
		{	
			GPIOB->CRL=0X88888888;
			OV7670_RCK=0;
			color=GPIOB->IDR&0x00FF;	//读数据
			OV7670_RCK=1; 
			color<<=8;  
			OV7670_RCK=0;
			color|=GPIOB->IDR&0x00FF;	//读数据
			OV7670_RCK=1; 
			GPIOB->CRL=0X33333333;	
			LCD_WR_DATA(color); 


//			EXTI_ClearITPendingBit(EXTI_Line15);



			if(j == Array[k]&&(k<=60))//init(k) = 0									  -=
			{
				if(k < 20)
				{
					   
					 if(!(color&0x8000))  //检测底片  黑，如果bit15为0，则黑点
						leftblackpoint++;
						
				}
				else if(k < 40)
				{
					if(color&0x8000)
					whitepoint++;		//测得白点
					
				}
				else if(k < 60)
				{
						if(!(color&0x8000))  //检测底片  黑，如果bit15为0，则黑点
						rightblackpoint++;
					
				}														   	 
			k++;
			}   
	   	}						 
				
		ov_sta=0;					//开始下一次采集
//		LCD_Scan_Dir(DFT_SCAN_DIR);	//恢复默认扫描方向 
		k=0;
		if(whitepoint<=13)	    //中间端未检测到白色则停止
	{
		JudgeFlag = 0;// stop
	}
		else 
	{

		if((whitepoint>13)&&(leftblackpoint>13)&&(rightblackpoint>13))//如果左端块黑色  中端块白色 右端块黑色 则前进
		{
			JudgeFlag = 1;
		}
	
		if(leftblackpoint <= 13 && rightblackpoint >13)	//左端白色 右端黑色 则向往右
		{
			JudgeFlag = 2;  //rihgt
		}

		if(leftblackpoint > 13 && rightblackpoint <= 13)	//右端白色 左端黑色 则向往左
		{
			JudgeFlag = 3;  //left
		}
    }	


	} 

  	


	return JudgeFlag;
}		
 int main(void)
 {	 
	
	delay_init();	    	 //延时函数初始化	  
	uart_init(9600);	 	//串口初始化为9600
 	LED_Init();			     //LED端口初始化
	LCD_Init();	
	Motor_Init();
		    
 	POINT_COLOR=RED;//设置字体为红色 

	LCD_ShowString(60,110,200,16,16,"OV7670 Init...");  
	 
	while(OV7670_Init())//初始化OV7670
	{
		LCD_ShowString(60,230,200,16,16,"OV7670 Error!!");
		delay_ms(200);
	    LCD_Fill(60,230,239,246,WHITE);
		delay_ms(200);
	}
 	LCD_ShowString(60,110,200,16,16,"OV7670 Init OK");
	delay_ms(1500);	 	   										  
	EXTI15_Init();

	OV7670_Special_Effects(1);
	OV7670_Light_Mode(2);

	ov_sta=0;	  
  	OV7670_CS=0;
							 	 
 	while(1)
	{	
		u8 flag ;
		flag = camera_refresh();
		/*LED0 red \ LED1 green */
		switch(flag)
		{
			case 0:Motor_Stop();break;    						//0 stop
			case 1:Motor_GOStraight();delay_ms(500);break;	 	//每一TIMER（20ms），走20step，
			case 2:Motor_GORight();delay_ms(500);break;			//2 往右 左步进电机转动							   LED1= 1
			case 3:Motor_GOLeft();delay_ms(500);break;			//3 往左 右步进电机转动
			default:break; 
		}
	}
}








