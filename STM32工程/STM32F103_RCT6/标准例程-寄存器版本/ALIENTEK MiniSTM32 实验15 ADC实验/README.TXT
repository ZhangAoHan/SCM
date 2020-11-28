实验器材:
	MiniSTM32F103开发板V3版本
	
实验目的:
	学习STM32内部ADC的使用
	
硬件资源:
	1,DS0(连接在PA8) 
	2,串口1(波特率:9600,PA9/PA10连接在板载USB转串口芯片CH340上面)
	3,ALIENTEK 2.8/3.5/4.3/7寸TFTLCD模块(通过GPIO驱动,连接关系见lcd.h) 
	4,ADC(STM32内部ADC1,通道1,即:ADC1_CH1)
	
实验现象:
	本实验通过STM32内部ADC1读取通道1（PA1）上面的电压，在LCD模块上面显示ADC转换值以及换算成电压后
	的电压值。
	
注意事项:  
	1,4.3寸和7寸屏需要比较大电流,USB供电可能不足,请用外部电源供电(5V电源，接VOUT2即可).
	2,本例程在LCD_Init函数里面(在ILI93xx.c),用到了printf,如果不初始化串口1,将导致液晶无法显示!! 
	3,LCD模块在开发板的LCD接口上面，必须靠右插
	4,STM32F103RCT6的参考电压恒为VDDA（即3.3V）
	5,ADC的最大输入电压是3.3V,请不要超过这个值.
	   

					正点原子@ALIENTEK
					2014-3-09
					广州市星翼电子科技有限公司
					电话：020-38271790
					传真：020-36773971
					购买：http://shop62103354.taobao.com
					http://shop62057469.taobao.com
					公司网站：www.alientek.com
					技术论坛：www.openedv.com