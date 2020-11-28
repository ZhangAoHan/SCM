#include "led.h"
#include "delay.h"
#include "sys.h"

#include "lcd.h"
#include "usart.h"	 
#include "ov7670.h"
#include "exti.h"
#include "motor.h"

u8 ov_sta;	//��exit.c���涨��
MOTOR GmLeft = {MOTOR_STOP,MOTOR_GOAHEAD,0,0,0};//���岢��ʼ������״̬
MOTOR GmRight = {MOTOR_STOP,MOTOR_GOAHEAD,0,0,0};//���岢��ʼ���ҵ��״̬							 

u16 Array[60] ={
	 /*�ɼ����ص���󡾣�46,150������49,154���� 320��*/
	14870,14871,14872,14873,14874,
	15190,15191,15192,15193,15194,
	15510,15511,15512,15513,15514,
	15830,15831,15832,15833,15834,
	 /*�ɼ����ص���󡾣�100,10������104,13���� 320��*/
	32010,32011,32012,32013,			 
	32330,32331,32332,32333,
	32650,32651,32652,32653,
	32970,32971,32972,32973,
	33290,33291,33292,33293,
	/*�ɼ����ص���󡾣�165,150������168,154���� 320��  */
	52950,52951,52952,52953,52954,		 
	53270,53271,53272,53273,53274,
	53590,53591,53592,53593,53594,
	53910,53911,53912,53913,53914,

};
//����LCD��ʾ
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
		LCD_Scan_Dir(U2D_L2R);		//���ϵ���,������ 
		LCD_SetCursor(0x00,0x0000);	//���ù��λ�� 
		LCD_WriteRAM_Prepare();     //��ʼд��GRAM	
		OV7670_RRST=0;				//��ʼ��λ��ָ�� 
		OV7670_RCK=0;
		OV7670_RCK=1;
		OV7670_RCK=0;
		OV7670_RRST=1;				//��λ��ָ����� 
		OV7670_RCK=1; 

	
	for(j=0;j<76800;j++)
		{	
			GPIOB->CRL=0X88888888;
			OV7670_RCK=0;
			color=GPIOB->IDR&0x00FF;	//������
			OV7670_RCK=1; 
			color<<=8;  
			OV7670_RCK=0;
			color|=GPIOB->IDR&0x00FF;	//������
			OV7670_RCK=1; 
			GPIOB->CRL=0X33333333;	
			LCD_WR_DATA(color); 


//			EXTI_ClearITPendingBit(EXTI_Line15);



			if(j == Array[k]&&(k<=60))//init(k) = 0									  -=
			{
				if(k < 20)
				{
					   
					 if(!(color&0x8000))  //����Ƭ  �ڣ����bit15Ϊ0����ڵ�
						leftblackpoint++;
						
				}
				else if(k < 40)
				{
					if(color&0x8000)
					whitepoint++;		//��ð׵�
					
				}
				else if(k < 60)
				{
						if(!(color&0x8000))  //����Ƭ  �ڣ����bit15Ϊ0����ڵ�
						rightblackpoint++;
					
				}														   	 
			k++;
			}   
	   	}						 
				
		ov_sta=0;					//��ʼ��һ�βɼ�
//		LCD_Scan_Dir(DFT_SCAN_DIR);	//�ָ�Ĭ��ɨ�跽�� 
		k=0;
		if(whitepoint<=13)	    //�м��δ��⵽��ɫ��ֹͣ
	{
		JudgeFlag = 0;// stop
	}
		else 
	{

		if((whitepoint>13)&&(leftblackpoint>13)&&(rightblackpoint>13))//�����˿��ɫ  �ж˿��ɫ �Ҷ˿��ɫ ��ǰ��
		{
			JudgeFlag = 1;
		}
	
		if(leftblackpoint <= 13 && rightblackpoint >13)	//��˰�ɫ �Ҷ˺�ɫ ��������
		{
			JudgeFlag = 2;  //rihgt
		}

		if(leftblackpoint > 13 && rightblackpoint <= 13)	//�Ҷ˰�ɫ ��˺�ɫ ��������
		{
			JudgeFlag = 3;  //left
		}
    }	


	} 

  	


	return JudgeFlag;
}		
 int main(void)
 {	 
	
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
 	LED_Init();			     //LED�˿ڳ�ʼ��
	LCD_Init();	
	Motor_Init();
		    
 	POINT_COLOR=RED;//��������Ϊ��ɫ 

	LCD_ShowString(60,110,200,16,16,"OV7670 Init...");  
	 
	while(OV7670_Init())//��ʼ��OV7670
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
			case 1:Motor_GOStraight();delay_ms(500);break;	 	//ÿһTIMER��20ms������20step��
			case 2:Motor_GORight();delay_ms(500);break;			//2 ���� �󲽽����ת��							   LED1= 1
			case 3:Motor_GOLeft();delay_ms(500);break;			//3 ���� �Ҳ������ת��
			default:break; 
		}
	}
}








