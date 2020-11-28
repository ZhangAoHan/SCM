实验器材:
	战舰STM32F103开发板V3版本
	
实验目的:
	学习彩色TFTLCD显示屏的使用
	
硬件资源:
	1,DS0(连接在PB5)
	2,串口1(波特率:115200,PA9/PA10连接在板载USB转串口芯片CH340上面)
	3,ALIENTEK 2.8/3.5/4.3/7寸TFTLCD模块(通过FSMC驱动,FSMC_NE4接LCD片选/A10接RS) 
	
实验现象:
	本实验利用战舰STM32开发板连接ALIENTEK TFTLCD模块(除CPLD版本7寸屏模块外,其余所有ALIENTEK的
	LCD模块都可以支持)，实现TFTLCD模块的显示，下载成功后，通过把LCD模块插入TFTLCD模块接口，按
	下复位之后，就可以看到LCD模块不停的显示一些信息并不断切换底色。同时该实验会显示LCD驱动器的
	ID，并且会在串口打印（按复位一次，打印一次）。
	
注意事项:
	1,4.3寸和7寸屏需要比较大电流,USB供电可能不足,请用外部电源适配器(推荐外接12V 1A电源).
	2,本例程在LCD_Init函数里面(在ILI93xx.c),用到了printf,如果不初始化串口1,将导致液晶无法显示!!


			正点原子@ALIENTEK 
			广州市星翼电子科技有限公司
			电话：020-38271790
			传真：020-36773971
			购买：http://eboard.taobao.com
			公司网站：www.alientek.com
			技术论坛：www.openedv.com



































