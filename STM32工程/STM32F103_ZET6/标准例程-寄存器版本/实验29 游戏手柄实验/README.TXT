实验器材:
	战舰STM32F103开发板V3版本
	
实验目的:
	学习FC游戏手柄的使用.
	
硬件资源:
	1,DS0(连接在PB5)
	2,串口1(波特率:115200,PA9/PA10连接在板载USB转串口芯片CH340上面)
	3,ALIENTEK 2.8/3.5/4.3/7寸TFTLCD模块(通过FSMC驱动,FSMC_NE4接LCD片选/A10接RS) 
	4,9针FC游戏手柄(CLK接PD3,DAT接PB10,LAT接PB11). 
	
实验现象:
	本实验主程序不停的扫描FC手柄的输入，一旦检测到有效输入，那么就将该输入值在TFTLCD模块上面显
	示，同时显示对应的符号（比如：Left/Right之类的）。
	 
注意事项:
	1,4.3寸和7寸屏需要比较大电流,USB供电可能不足,请用外部电源适配器(推荐外接12V 1A电源).
	2,本例程在LCD_Init函数里面(在ILI93xx.c),用到了printf,如果不初始化串口1,将导致液晶无法显示!!
	3,P8需要将跳线帽连接为:PB10接COM3_RX,PB11接COM3_TX
	4,K1需要将开关打到JOYPAD位置


			正点原子@ALIENTEK 
			广州市星翼电子科技有限公司
			电话：020-38271790
			传真：020-36773971
			购买：http://eboard.taobao.com
			公司网站：www.alientek.com
			技术论坛：www.openedv.com



































