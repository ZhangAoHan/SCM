#include "spblcd.h"
#include "spb.h"
#include "dma.h"
#include "lcd.h"
#include "delay.h"
#include "malloc.h"
#include "usart.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//SPBLCD ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/7/20
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	


u16 *sramlcdbuf;							//SRAM LCD BUFFER,����ͼƬ�Դ��� 

//��ָ��λ�û���.
//x,y:����
//color:��ɫ.
void slcd_draw_point(u16 x,u16 y,u16 color)
{	 
	sramlcdbuf[y+x*spbdev.spbheight+spbdev.frame*spbdev.spbheight*spbdev.spbwidth]=color;
}
//��ȡָ��λ�õ����ɫֵ
//x,y:����
//����ֵ:��ɫ
u16 slcd_read_point(u16 x,u16 y)
{
	return sramlcdbuf[y+x*spbdev.spbheight+spbdev.frame*spbdev.spbheight*spbdev.spbwidth];
} 
//�����ɫ
//x,y:��ʼ����
//width��height����Ⱥ͸߶�
//*color����ɫ����
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
//SRAM --> LCD_RAM dma����
//16λ,�ⲿSRAM���䵽LCD_RAM. 
void slcd_dma_init(void)
{  
	RCC->AHBENR|=1<<1;						//����DMA2ʱ��    		 
	DMA2_Channel5->CPAR=0;					//�ݲ�����
	DMA2_Channel5->CMAR=(u32)&LCD->LCD_RAM;	//Ŀ���ַΪLCD_RAM
 	DMA2_Channel5->CNDTR=0;    				//DMA2,����������
	DMA2_Channel5->CCR=0X00000000;			//��λ

 	DMA2_Channel5->CCR|=0<<4;  				//�������
	DMA2_Channel5->CCR|=0<<5;  				//��ͨģʽ
	DMA2_Channel5->CCR|=1<<6; 				//�����ַ����ģʽ
	DMA2_Channel5->CCR|=0<<7; 				//�洢��������ģʽ
	DMA2_Channel5->CCR|=1<<8; 				//�������ݿ��Ϊ16λ
	DMA2_Channel5->CCR|=1<<10; 				//�洢�����ݿ��16λ
	DMA2_Channel5->CCR|=1<<12; 				//�е����ȼ�
	DMA2_Channel5->CCR|=1<<14; 				//�洢�����洢��ģʽ(����Ҫ�ⲿ����)	 
} 

//����һ��SPI��LCD��DMA�Ĵ���
//x:��ʼ�����ַ���(0~480)
void slcd_dma_enable(u32 x)
{	  
	u32 lcdsize=spbdev.spbwidth*spbdev.spbheight;
	u32 dmatransfered=0;
	while(lcdsize)
	{     	  
		DMA2_Channel5->CCR&=~(1<<0); 		//�ر�DMA����
		//while(DMA2_Stream0->CR&0X01);		//�ȴ�DMA2_Stream0������ 
		DMA2->IFCR|=1<<17;					//����ϴεĴ�����ɱ�� 
		if(lcdsize>SLCD_DMA_MAX_TRANS)
		{
			lcdsize-=SLCD_DMA_MAX_TRANS;
			DMA2_Channel5->CNDTR=SLCD_DMA_MAX_TRANS;	//���ô��䳤��
		}else
		{
			DMA2_Channel5->CNDTR=lcdsize;				//���ô��䳤��
			lcdsize=0;
		}	
		DMA2_Channel5->CPAR=(u32)(sramlcdbuf+x*spbdev.spbheight+dmatransfered);	//DMA2,�ı�洢����ַ
		dmatransfered+=SLCD_DMA_MAX_TRANS;		
		DMA2_Channel5->CCR|=1<<0;   		//����DMA����
		while((DMA2->ISR&(1<<17))==0);		//�ȴ�
	} 
	DMA2_Channel5->CCR&=~(1<<0); 			//�ر�DMA���� 
}
//��ʾһ֡,������һ��spi��lcd����ʾ.
//x:����ƫ����
void slcd_frame_show(u32 x)
{  
	LCD_Scan_Dir(U2D_L2R);		//����ɨ�跽��  
	if(lcddev.id==0X9341||lcddev.id==0X5310||lcddev.id==0X5510||lcddev.id==0X6804)
	{
		LCD_Set_Window(spbdev.stabarheight,0,spbdev.spbheight,spbdev.spbwidth);
		LCD_SetCursor(spbdev.stabarheight,0);//���ù��λ�� 
	}else
	{
		LCD_Set_Window(0,spbdev.stabarheight,spbdev.spbwidth,spbdev.spbheight);
		if(lcddev.id!=0X1963)LCD_SetCursor(0,spbdev.stabarheight);//���ù��λ�� 		
	}
	LCD_WriteRAM_Prepare();     //��ʼд��GRAM	
	slcd_dma_enable(x);
	LCD_Scan_Dir(DFT_SCAN_DIR);	//�ָ�Ĭ�Ϸ���
	LCD_Set_Window(0,0,lcddev.width,lcddev.height);//�ָ�Ĭ�ϴ��ڴ�С
}
 





