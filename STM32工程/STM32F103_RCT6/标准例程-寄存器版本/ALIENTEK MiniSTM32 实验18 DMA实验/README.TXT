实验器材:
	MiniSTM32F103开发板V3版本
	
实验目的:
	学习STM32 DMA功能的使用
	
硬件资源:
	1,DS0(连接在PA8) 
	2,串口1(波特率:9600,PA9/PA10连接在板载USB转串口芯片CH340上面)
	3,ALIENTEK 2.8/3.5/4.3/7寸TFTLCD模块(通过GPIO驱动,连接关系见lcd.h) 
	4,按键KEY0(PC5) 
	5,DMA(DMA1通道4) 
	
实验现象:
	本实验通过按键KEY0控制串口1以DMA方式发送数据，按下KEY0，就开始DMA传送，同时在LCD上面显示传送进度。
	打开串口调试助手，可以收到DMA发送的内容。
	
注意事项:  
	1,4.3寸和7寸屏需要比较大电流,USB供电可能不足,请用外部电源供电(5V电源，接VOUT2即可).
	2,本例程在LCD_Init函数里面(在ILI93xx.c),用到了printf,如果不初始化串口1,将导致液晶无法显示!! 
	3,LCD模块在开发板的LCD接口上面，必须靠右插
	4,电脑端串口调试助手波特率必须是9600.
	5,请使用XCOM/SSCOM串口调试助手,其他串口助手可能控制DTR/RTS导致MCU复位/程序不运行 
	6,请用USB线连接在USB_232,找到USB转串口后测试本例程.
	7,PA9/PA10必须通过跳线帽连接在RXD/TXD上.
	 

					正点原子@ALIENTEK
					2014-3-09
					广州市星翼电子科技有限公司
					电话：020-38271790
					传真：020-36773971
					购买：http://shop62103354.taobao.com
					http://shop62057469.taobao.com
					公司网站：www.alientek.com
					技术论坛：www.openedv.com
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					