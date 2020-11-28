#include "delay.h"
#include "sys.h"

#include "usart.h"	 
#include "ov7670.h"
#include "exti.h"
#include "motor.h"

MOTOR GmLeft = {MOTOR_STOP,MOTOR_GOAHEAD,0,0,0};//���岢��ʼ������״̬
MOTOR GmRight = {MOTOR_STOP,MOTOR_GOAHEAD,0,0,0};//���岢��ʼ���ҵ��״̬
u8 ov_sta;
					
int main(void)
 {	 
	
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
	Motor_Init();	    	 //������ʱ���жϳ�ʼ��

	while(OV7670_Init())//��ʼ��OV7670
	{
		printf("error!\n");
	}

	  										  
	EXTI15_Init();
	
	OV7670_Special_Effects(1);
	OV7670_Light_Mode(2);

	ov_sta=0;	  
  	OV7670_CS=0;
							 	 
 	while(1)
	{	
	volatile	u8 flag ;
	
		/*�رն�ʱ���ж�*/
		/*֮ǰ���ǵ���timer�Ƿ��Զ�fifo���������Ӱ�� ���Լ��Ͽ����ж�*/
		/*�������ֿ����ж�ûӰ��*/
//		NVIC_DisableIRQ(TIM3_IRQn);			//��ȡfifo�������
//		NVIC_DisableIRQ(TIM2_IRQn);			//��ȡfifo�������
//		NVIC_DisableIRQ(EXTI15_10_IRQn); 	//�����ٴ�дfifo

		flag = camera_refresh();

		/*������ʱ���ж�*/ 
//		NVIC_EnableIRQ(TIM2_IRQn);
//	    NVIC_EnableIRQ(TIM3_IRQn);
//	    NVIC_EnableIRQ(EXTI15_10_IRQn);

		//printf("%d ",flag);
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








