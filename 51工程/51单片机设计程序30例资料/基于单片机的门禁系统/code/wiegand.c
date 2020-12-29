/*******************************************************************************
* 文件名称：Wiegand.c	                        
* 说明：本文件为韦根卡读卡程序。
* 功能：实现对韦根卡的识别
* 修改：无
* 版本：1.0.0
* 作者：YuanDong
* 时间：2009.7.20
*******************************************************************************/	
#include <51reg.h>
#include <string.h>
#include <stdio.h>      /*标准输入输出定义*/

				
sbit DATA0=P3^2;   //数据线0
sbit DATA1=P3^3;   //数据线1

/*定义韦根卡的一个结构体*/
struct wiegand_dev
{
	char wiegand[26];			     // 定义Weigand  26Bits 数据
  unsigned char  state;  
	int global_var;			         // 全局计数器 计数组长度

  
};static struct wiegand_dev *rf_card;


/*****************************************************************************************
*函数名称：initial(void)
*函数功能：中断初始化
*入口函数：无
*出口函数：无
*****************************************************************************************/
void initial(void) 
{ 
  EA=0;   //关CPU中断

  IT0=0;  //Wiegand-Data0	低电平触发中断
  EX0=1;  //外部中断0允许 
  
  IT1=0;  //Wiegand-Data1 低电平触发中断
  EX1=1;  //外部中断1允许 
 
  EA=1;  //开CPU中断
} 
/*****************************************************************************************
*函数名称：Wiegand_Data0( )
*函数功能：韦根卡数据0中断处理
*入口函数：无
*出口函数：无
*****************************************************************************************/
void Wiegand_Data0( ) interrupt 0 using 2  //中断0处理函数,使用第二组寄存器
{
	EX0=0;         //关中断0
	udelay(5);
	
	if(DATA0 == 0)  //如果INT0为低，标示0线中断
	{
		wiegand[rf_card->global_var] = '0';      //往数组里填0
		global_var = rf_card->global_var + 1;
	}	
	
	udelay(500);   //延时1500uS（去掉中断后的处理时间）
	
	EX0=1;         //开中断0

  udelay(2500);  //延时2500uS(max值，去掉前期处理时间)

}
/*****************************************************************************************
*函数名称：Wiegand_Data1( )
*函数功能：韦根卡数据1中断处理
*入口函数：无
*出口函数：无
*****************************************************************************************/
void  Wiegand_Data1( ) interrupt 2 using 1  //中断1处理函数,使用第一组寄存器
{
	EX1=0;         //关中断1			
	udelay(5);
	
	if(DATA1 == 0)
	{
		rf_card->wiegand[rf_card->global_var] = '1';
		rf_card->global_var = rf_card->global_var + 1;
	}	
	udelay(500);
	EX1=1;         //开中断0
  
}
/*****************************************************************************************
*函数名称：udelay(uint num)
*函数功能：延时函数 延时num  us
*入口函数：num
*出口函数：无
*****************************************************************************************/
void udelay(uint num)
{
  num=num/5;		
  while(--num);	
}
/*****************************************************************************************
*函数名称：main( )
*函数功能：主函数
*入口函数：无
*出口函数：无
*****************************************************************************************/
void main()
(
   whlie(1)
   {
   initial(void);
   rf_card->global=0;
   
   //等待中断
   }
)
