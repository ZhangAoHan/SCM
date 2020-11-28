#include "spblcd.h"
#include "spb.h"
#include "dma.h"
#include "lcd.h"
#include "delay.h"
#include "malloc.h"
#include "usart.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//SPBLCD 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/7/20
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	


u16 *sramlcdbuf;							//SRAM LCD BUFFER,背景图片显存区 

//在指定位置画点.
//x,y:坐标
//color:颜色.
void slcd_draw_point(u16 x,u16 y,u16 color)
{	 
	sramlcdbuf[y+x*spbdev.spbheight+spbdev.frame*spbdev.spbheight*spbdev.spbwidth]=color;
}
//读取指定位置点的颜色值
//x,y:坐标
//返回值:颜色
u16 slcd_read_point(u16 x,u16 y)
{
	return sramlcdbuf[y+x*spbdev.spbheight+spbdev.frame*spbdev.spbheight*spbdev.spbwidth];
} 
//填充颜色
//x,y:起始坐标
//width，height：宽度和高度
//*color：颜色数组
void slcd_fill_color(u16 x,u16 y,u16 width,u16 height,u16 *color)
{   
	u16 i,j; 
 	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			slcd_draw_point(x+j,y+i,*color++);
		}	
	}	
} 
//SRAM --> LCD_RAM dma配置
//16位,外部SRAM传输到LCD_RAM. 
void slcd_dma_init(void)
{  
	RCC->AHBENR|=1<<1;						//开启DMA2时钟    		 
	DMA2_Channel5->CPAR=0;					//暂不设置
	DMA2_Channel5->CMAR=(u32)&LCD->LCD_RAM;	//目标地址为LCD_RAM
 	DMA2_Channel5->CNDTR=0;    				//DMA2,传输数据量
	DMA2_Channel5->CCR=0X00000000;			//复位

 	DMA2_Channel5->CCR|=0<<4;  				//从外设读
	DMA2_Channel5->CCR|=0<<5;  				//普通模式
	DMA2_Channel5->CCR|=1<<6; 				//外设地址增量模式
	DMA2_Channel5->CCR|=0<<7; 				//存储器非增量模式
	DMA2_Channel5->CCR|=1<<8; 				//外设数据宽度为16位
	DMA2_Channel5->CCR|=1<<10; 				//存储器数据宽度16位
	DMA2_Channel5->CCR|=1<<12; 				//中等优先级
	DMA2_Channel5->CCR|=1<<14; 				//存储器到存储器模式(不需要外部请求)	 
} 

//开启一次SPI到LCD的DMA的传输
//x:起始传输地址编号(0~480)
void slcd_dma_enable(u32 x)
{	  
	u32 lcdsize=spbdev.spbwidth*spbdev.spbheight;
	u32 dmatransfered=0;
	while(lcdsize)
	{     	  
		DMA2_Channel5->CCR&=~(1<<0); 		//关闭DMA传输
		//while(DMA2_Stream0->CR&0X01);		//等待DMA2_Stream0可配置 
		DMA2->IFCR|=1<<17;					//清除上次的传输完成标记 
		if(lcdsize>SLCD_DMA_MAX_TRANS)
		{
			lcdsize-=SLCD_DMA_MAX_TRANS;
			DMA2_Channel5->CNDTR=SLCD_DMA_MAX_TRANS;	//设置传输长度
		}else
		{
			DMA2_Channel5->CNDTR=lcdsize;				//设置传输长度
			lcdsize=0;
		}	
		DMA2_Channel5->CPAR=(u32)(sramlcdbuf+x*spbdev.spbheight+dmatransfered);	//DMA2,改变存储器地址
		dmatransfered+=SLCD_DMA_MAX_TRANS;		
		DMA2_Channel5->CCR|=1<<0;   		//开启DMA传输
		while((DMA2->ISR&(1<<17))==0);		//等待
	} 
	DMA2_Channel5->CCR&=~(1<<0); 			//关闭DMA传输 
}
//显示一帧,即启动一次spi到lcd的显示.
//x:坐标偏移量
void slcd_frame_show(u32 x)
{  
	LCD_Scan_Dir(U2D_L2R);		//设置扫描方向  
	if(lcddev.id==0X9341||lcddev.id==0X5310||lcddev.id==0X5510||lcddev.id==0X6804)
	{
		LCD_Set_Window(spbdev.stabarheight,0,spbdev.spbheight,spbdev.spbwidth);
		LCD_SetCursor(spbdev.stabarheight,0);//设置光标位置 
	}else
	{
		LCD_Set_Window(0,spbdev.stabarheight,spbdev.spbwidth,spbdev.spbheight);
		if(lcddev.id!=0X1963)LCD_SetCursor(0,spbdev.stabarheight);//设置光标位置 		
	}
	LCD_WriteRAM_Prepare();     //开始写入GRAM	
	slcd_dma_enable(x);
	LCD_Scan_Dir(DFT_SCAN_DIR);	//恢复默认方向
	LCD_Set_Window(0,0,lcddev.width,lcddev.height);//恢复默认窗口大小
}
 





