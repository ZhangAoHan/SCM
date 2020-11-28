#include "sys.h" 
//#include "timer.h"
#include "olcd.h"
//#include "motor.h"
	u8 res;
	
void Bluetooth(void);	
int main(void)
{		
//	u16 led0pwmval=0;    
//	u8 dir=1;
//		u8 t;

//	u8 len;	
//	u16 times=0;  
	Stm32_Clock_Init(9);	//系统时钟设置
	delay_init(72);	  		//延时初始化
	uart_init(72,9600); 	//串口初始化为9600


//	IIC_Init();                  //6050_iic初始化	
//	DMP_Init();                  //6050_DMP初始化
//	MPU6050_initialize();        //6050_初始化
//	iIC_Init(); 

//	Timer_init(7199,0);   //不分频，pwm频率为72M/7200=10K hz  ，pwm计数总数为7200，定时器3内部输出比较寄存器装载值与900比较
//    MOTO_PWM_init();
//	Mortor_init();
	
		OLED_Init();			//初始化OLED  
		OLED_Clear() ; 
  	while(1)
	{
//		Read_DMP();
//		Bluetooth();
//		Motor_PWM(6900,6900) ;      //PWM极限为6900.（值越大，越慢）

		OLED_ShowCHinese(0,0,0);//中
		OLED_ShowCHinese(18,0,1);//景
		OLED_ShowCHinese(36,0,2);//园
		OLED_ShowCHinese(54,0,3);//电
		OLED_ShowCHinese(72,0,4);//子
		OLED_ShowCHinese(90,0,5);//科
		OLED_ShowCHinese(108,0,6);//技
				delay_ms(8000);
	}	 
} 


void Bluetooth()
{
	switch(res)
	{
		case 0x00:  led=0;   break;
		case 0x01:  led=1;   break;
	}
}






