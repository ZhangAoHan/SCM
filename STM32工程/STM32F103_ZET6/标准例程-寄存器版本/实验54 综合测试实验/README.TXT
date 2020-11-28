实验器材:
	战舰STM32F103开发板V3版本
	
实验目的:
	综合测试实验,测试整个开发板硬件,体验STM32强大的功能.
	
硬件资源:
	1,DS0(连接在PB5),DS1(连接在PE5)
	2,蜂鸣器(连接在PB8) 
	3,按键KEY0(PE4)/KEY1(PE3)/KEY2(PE2)/KEY_UP(PA0,也称之为WK_UP)
	4,外部SRAM(IS62WV51216,通过FSMC驱动,FSMC_NE3接SRAM) 
	5,串口1(波特率:115200,PA9/PA10连接在板载USB转串口芯片CH340上面)
	6,串口3(波特率:115200,PB10/PB11)
	7,ALIENTEK 2.8/3.5/4.3/7寸TFTLCD模块(通过FSMC驱动,FSMC_NE4接LCD片选/A10接RS)
	8,TPAD电容触摸按键(右下角LOGO,即TPAD,连接在PA1)
	9,定时器TIM2~TIM8
	10,RTC(实时时钟)
	11,ADC(读取内部温度传感器)
	12,VS1053(音乐播放/NES游戏/录音机实验)
	13,光敏传感器(连接在PF8)
	14,24C02(IIC连接在PB6/PB7上面) 
	15,W25Q128(SPI FLASH芯片,连接在SPI2上)  
	16,触摸屏(TFTLCD模块自带了,IO状态为:T_PEN(PF10)/T_MOSI(PF9)/T_MISO(PB2)/T_SCK(PB1)/T_CS(PF11)) 
	17,9针FC游戏手柄(CLK接PD3,DAT接PB10,LAT接PB11)
	18,DS18B20传感器一个(接在PG11上). 	
	19,ALIENTEK MPU6050模块一个(连接在PB10(SCL),PB11(SDA),PA15(AD0)上面,INT未用到). 
	20,NRF24L01模块(SPI2(PB13/PB14/PB15)/IRQ(PG6)/CS(PG7)/CE(PG8)). 
	21,ALIENTEK OV7670摄像头模块
	22,USB_SLAVE接口(通过跳线帽将D-/D+连接在PA11/PA12上)
	23,DM9000(通过FSMC驱动,FSMC_NE2接DM9000) 
	24,SD卡,通过SDIO(SDIO_D0~D4(PC8~PC11),SDIO_SCK(PC12),SDIO_CMD(PD2))连接 
	25,HS0038红外接收头
	26,板载咪头(录音/TOM猫)
	27,板载喇叭(播放音乐/NES游戏/TOM猫)
	28,ALIENTEK SIM900/SIM900A GSM模块(电话/短信)
	
		
实验现象:
	本实验功能比较复杂,具体介绍请参考《STM32开发指南》V3版本,第五十九章。 

注意事项:
	1,4.3寸和7寸屏需要比较大电流,USB供电可能不足,请用外部电源适配器(推荐外接12V 1A电源).
	2,本例程在LCD_Init函数里面(在ILI93xx.c),用到了printf,如果不初始化串口1,将导致液晶无法显示!! 
	3,本例程需自备配件(非必须)包括:
		a,SD卡
		b,ALIENTEK OV7670摄像头模块
		c,ALIENTEK MPU6050模块
		d,ALIENTEK GSM/GPRS模块
		e,DS18B20数字温度传感器
		f,NRF24L01无线模块
		g,耳机 
	4,按RESET复位进入开机界面(自检界面)后,迅速按以下按键:
		按住KEY0不放:可以强制进入校准界面,对触摸屏进行校准(仅限电阻屏,对电容屏无效).
		按住KEY1不放:可以强制进入字库更新,更新字库.
		按住KEY2不放:可以强制擦除整个SPI FLASH,方便使用SD卡快速更新系统文件.
        ---提示:按住KEY0~KEY2是要一直按住,并耐心等待.直到进入相应界面/出现提示.
    5,照相机功能,按KEY_UP按键可以进行照相. 
    6,在音乐播放器界面,调节的音量不会自动保存,在设置界面设置好音量,并退回主界面,才会保存.	
	7,P8端口,跳线帽默认连接方式为:PB10(TX)连COM3_RX,PB11(RX)连COM3_TX.
	8,P10端口(多功能端口),默认用跳线帽连接:ADC和TPAD.
	9,P4端口,跳线帽连接方式为:PA9(T)连RXD,PA10(R)连TXD.
	11,P9端口,跳线帽连接方式为:PA11连D-,PA12连D+.
	12,无线传书功能,需要2套开发板才可以测试.
	

			正点原子@ALIENTEK 
			广州市星翼电子科技有限公司
			电话：020-38271790
			传真：020-36773971
			购买：http://eboard.taobao.com
			公司网站：www.alientek.com
			技术论坛：www.openedv.com



































