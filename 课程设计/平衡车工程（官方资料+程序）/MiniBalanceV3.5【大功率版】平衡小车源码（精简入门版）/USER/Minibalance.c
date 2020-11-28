#include "sys.h"
  /**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
**************************************************************************/
int Encoder_Left,Encoder_Right;             //左右编码器的脉冲计数
int Moto1,Moto2;                            //电机PWM变量 应是Motor的 向Moto致敬	
float Angle_Balance,Gyro_Balance;           //平衡倾角 平衡陀螺仪 转向陀螺仪
int main(void)
{ 
	Stm32_Clock_Init(9);            //=====系统时钟设置
	delay_init(72);                 //=====延时初始化
//	JTAG_Set(JTAG_SWD_DISABLE);     //=====关闭JTAG接口
//	JTAG_Set(SWD_ENABLE); 	//=====打开SWD接口 可以利用主板的SWD接口调试
	JTAG_Set(JTAG_SWD_ENABLE);
	LED_Init();                     //=====初始化与 LED 连接的硬件接口
	OLED_Init();                    //=====OLED初始化
	uart_init(72,128000);           //=====初始化串口1
  MiniBalance_PWM_Init(7199,0);   //=====初始化PWM 10KHZ，用于驱动电机 如需初始化电调接口 改为MiniBalance_PWM_Init(9999,35) 200HZ
	Encoder_Init_TIM2();            //=====编码器接口
	Encoder_Init_TIM4();            //=====初始化编码器2 
	IIC_Init();                     //=====模拟IIC初始化
  MPU6050_initialize();           //=====MPU6050初始化	
  DMP_Init();                     //=====初始化DMP     
	EXTI_Init();                    //=====MPU6050 5ms定时中断初始化
	while(1)
		{     
					oled_show();            //===显示屏打开
				  printf("平衡 倾角  %f \r\n左轮编码器%d \r\n右轮编码器%d \r\n",Angle_Balance,Encoder_Left,Encoder_Right);//向串口调试助手发送数据
		} 
}
