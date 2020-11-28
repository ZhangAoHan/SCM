#include "sys.h"

	u8 res;         //蓝牙接收变量
	
void Bluetooth(void);
void Olcd_Display(void);
void Speed(void); 
 int main(void)
 {	
	 //系统初始化
	Stm32_Clock_Init(9);	//系统时钟设置
	delay_init(72);	  		//延时初始化
	uart_init(72,9600); 	//串口初始化为9600	
	 
	 //OLCD初始化
	OLED_Init();			//初始化OLED  
	OLED_Clear() ;   //清屏
	 
	   //6050初始化
	 	//IIC_Init();                  //6050_iic初始化	
     //	DMP_Init();                  //6050_DMP初始化
     	//MPU6050_initialize();        //6050_初始化
	 
	 //电机pwm初始化
		Timer_init(7199,0);   //不分频，pwm频率为72M/7200=10K hz  ，pwm计数总数为7200，定时器3内部输出比较寄存器装载值与900比较
		MOTO_PWM_init();
     	Mortor_init();
		TIM2_init(65535);     //不分频，72M/65536=900us读一次速度
		TIM4_init(65535);
	 
	 
	while(1)
	{
//	Read_DMP();                  //读6050的值
	Motor_PWM(5500,5500) ;      //PWM极限为6900.（值越大，越慢）
	Speed();
//    Olcd_Display();
	}
 }
 
void Bluetooth()          //蓝牙接收函数
{
	switch(res)
	{
		case 0x00:  led=0;   break;
		case 0x01:  led=1;   break;
	}
}
void Olcd_Display()
{
	//128*64  x=0-127  y=0-7(每个y占8横)   
		OLED_Clear();                                //清屏（如果不清屏，则显示内容会相互覆盖）
		OLED_ShowCHinese(0,0,14);                 //显示汉字函数 张（参数：x,y,C）X和Y，汉字的坐标（每个汉字占16*16,横x纵y），C：汉字点阵序号
	    OLED_ShowCHinese(16,2,15);  //奥
	    OLED_ShowCHinese(32,4,16);  //涵
		delay_ms(3000);
		OLED_Clear() ; 
		OLED_ShowString(6,3,"0.96' OLED TEST",SIZE);    //显示字符串函数  参数（x,y,"字符串",s）  x,y为字符串起始坐标（横x纵y，每个字符占8*16（s=16）或6*8（s=SIZE=8））
		delay_ms(3000);
		OLED_Clear() ; 
		OLED_ShowNum(0,2,100,3,16);//显示数字  参数（x,y,num,len,size）  len为数字的有效位数（由len来将数字精确分解）  mun为数字，
		delay_ms(3000);
		OLED_Clear() ; 
	   OLED_ShowChar(48,6,'1',16);//显示ASCII字符	参数（x,y,‘字符’,size）  注意：字符用单引号，字符串用双引号   
		delay_ms(3000);
//		OLED_DrawBMP(0,0,128,8,BMP1);  //图片显示(图片显示慎用，生成的字表较大，会占用较多空间，FLASH空间8K以下慎用)
//		delay_ms(3000);
}
void Speed_Show(u16 left,u16 right,u16 tms)
{
	OLED_Clear(); 
	OLED_ShowString(0,0,"Left",16);
	OLED_ShowChar(32,0,':',16);
	OLED_ShowNum(40,0,left,8,16);
	OLED_ShowString(0,2,"RIGHT",16);
	OLED_ShowChar(40,2,':',16);
	OLED_ShowNum(48,2,right,8,16);
	delay_ms(tms);
}
void Speed()              //测速并显示
{
	u16 s_left,s_right;
	s_left=Read_val(2);
	s_right=Read_val(4);
	Speed_Show(s_left,s_right,100);
}





