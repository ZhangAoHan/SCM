实验器材:
	MiniSTM32F103开发板V3版本
	
实验目的:
	学习单色OLED显示屏的使用
	
硬件资源:
	1,DS0(连接在PA8) 
	2,ALIENTEK 0.96寸OLED模块(连接IO说明,见oled.h文件) 
	
实验现象:
	本实验利用开发板的LCD接口(靠左插)连接ALIENTEK OLED模块，实现OLED模块的显示，下
	载成功后，通过把OLED模块插入开发板的LCD接口(靠左插)，按下复位键之后，就可以看到
	OLED模块不停的显示ASCII码和码值。
	
注意事项:
	1,开发板的OLED和LCD共用一个接口，插OLED模块的时候，靠左插即可.
	2,例程默认用的8080方式驱动OLED模块,所以OLED模块的BS0,BS1都需要接VCC(默认接的VCC).
	 

					正点原子@ALIENTEK
					2014-3-07
					广州市星翼电子科技有限公司
					电话：020-38271790
					传真：020-36773971
					购买：http://shop62103354.taobao.com
					http://shop62057469.taobao.com
					公司网站：www.alientek.com
					技术论坛：www.openedv.com