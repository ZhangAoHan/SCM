/*  main.c  */

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "w25qxx.h"
#include "string.h"
#include "ff.h"
#include "sdio_sdcard.h"
#include "beep.h"




/***********************************************************************/
//此程序适用于七彩光子太极M3—STM32F103开发板及部分兼容的STM32系统，
//只供学习使用，未经作者许可，不得用于其它任何用途！
/***********************************************************************/
 
 
 
 




//FatFs变量定义
FATFS fs; 
FIL fsrc;


const char f_path[]={"test.txt"};
const char test_txt[]={"太极M3-STM32F103开发板SD卡FATFS配套实验程序！\r\n此内容是通过FATFS写入的!\r\n"};
u8 test_buf[200];
u32 count=0;
u16 i=0;




int main(void)
{
	u8 t=0,r=0;
	delay_init();	    //延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	LED_Init();
	//Beep_Init();
	USART1_Init(115200);//串口1初始化
	
	//延时1秒
	delay_ms(1000);
	
	printf("太极M3-STM32F103开发板SD卡FATFS实验开始 !\r\n");
	delay_ms(1000);
	
	Start:
	//开始初始化SD卡
	while( SD_OK != SD_Init() ){
		delay_ms(30);
		t++;
		if(t%10==0){
			//BEEP_TOGGLE();
			LED_TOGGLE(LED1);
		}
		if(t>30){
			t=0;
			printf("SD 卡初始化失败 !\r\n");
		}
	}
	//BEEP_OFF();
	printf("\r\nSD 卡初始化成功 !\r\n");
	printf("SD卡容量: %dM\r\n",(u32)SDCardInfo.CardCapacity/1024/1024);
	
	delay_ms(1000);
	
	//开始初始化文件系统
	while(FR_OK != f_mount(&fs,"0:",1)){
		delay_ms(30);
		t++;
		if(t%10==0){
			//BEEP_TOGGLE();
			LED_TOGGLE(LED1);
		}
		if(t>30){
			t=0;
			printf("FatFs 挂载失败 !\r\n");
		}
	}
	//BEEP_OFF();
	printf("\r\nFatFs 挂载成功 !\r\n");
	
	delay_ms(1000);
	
	//开始创建文件
	r=f_open(&fsrc,f_path,FA_CREATE_ALWAYS|FA_READ|FA_WRITE);
	if(FR_OK != r){
		printf("\r\n创建文件失败 !\r\n");
		goto Start;
	}
	printf("\r\n创建文件成功 !\r\n");
	
	delay_ms(1000);
	
	//开始写入数据
	r=f_write(&fsrc,test_txt,strlen((const char*)test_txt),&count);
	//写入数据完毕，关闭文件
	f_close(&fsrc);
	if(FR_OK != r){
		printf("文件写入失败 !\r\n");
		goto Start;
	}
	printf("FATFS写入%d个字节 !\r\n",count);
	
	delay_ms(1000);
	
	//重新打开文件，准备读取数据
	r=f_open(&fsrc,f_path,FA_READ|FA_WRITE);
	if(FR_OK != r){
		printf("重新打开文件失败 !\r\n");
		goto Start;
	}
	printf("\r\n重新文件成功 !\r\n");
	
	delay_ms(1000);
	
	//开始读取数据
	r=f_read(&fsrc,test_buf,strlen((const char*)test_txt),&count);//	
	f_close(&fsrc);
	if(FR_OK != r){
		printf("读取文件失败 !\r\n");
		goto Start;
	}
	printf("\r\n读取文件成功 !读取到如下%d字节数据：\r\n\r\n%s",count,test_buf);

	delay_ms(1000);
	//测试完成
	printf("\r\n\r\n测试完成 !\r\n");
	while(1)
	{
		delay_ms(500);
		LED_TOGGLE(LED0);
	}
}




