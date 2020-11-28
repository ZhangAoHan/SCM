#include "delay.h"
#include "sys.h"

#include "usart.h"	 
#include "ov7670.h"
#include "exti.h"
#include "motor.h"

MOTOR GmLeft = {MOTOR_STOP,MOTOR_GOAHEAD,0,0,0};//定义并初始化左电机状态
MOTOR GmRight = {MOTOR_STOP,MOTOR_GOAHEAD,0,0,0};//定义并初始化右电机状态
u8 ov_sta;
					
int main(void)
 {	 
	
	delay_init();	    	 //延时函数初始化	  
	uart_init(9600);	 	//串口初始化为9600
	Motor_Init();	    	 //包含定时器中断初始化

	while(OV7670_Init())//初始化OV7670
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
	
		/*关闭定时器中断*/
		/*之前考虑到，timer是否会对对fifo这个过程有影响 所以加上开关中断*/
		/*后来发现开关中断没影响*/
//		NVIC_DisableIRQ(TIM3_IRQn);			//读取fifo不被打断
//		NVIC_DisableIRQ(TIM2_IRQn);			//读取fifo不被打断
//		NVIC_DisableIRQ(EXTI15_10_IRQn); 	//避免再次写fifo

		flag = camera_refresh();

		/*开启定时器中断*/ 
//		NVIC_EnableIRQ(TIM2_IRQn);
//	    NVIC_EnableIRQ(TIM3_IRQn);
//	    NVIC_EnableIRQ(EXTI15_10_IRQn);

		//printf("%d ",flag);
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








