#include "untogb.h"
#include "flash.h"
#include "usart.h"
#include "fontupd.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//Mini STM32开发板
//UNICODE TO GBK 内码转换程序 驱动代码		   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2010/5/23 
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////	 
 		

//将UNICODE码转换为GBK码
//unicode:UNICODE码
//返回值:GBK码				 
u16 UnicodeToGBK(u16 unicode)//用二分查找算法
{
   	u32 offset;
	u8 temp[2];
	u16 res;
	if(unicode<=0X9FA5)offset=unicode-0X4E00;
	else if(unicode>0X9FA5)//是标点符号
	{
		if(unicode<0XFF01||unicode>0XFF61)return 0;//没有对应编码
		offset=unicode-0XFF01+0X9FA6-0X4E00;    
	}  
	SPI_Flash_Read(temp,offset*2+UNI2GBKADDR,2);//得到GBK码   
	res=temp[0];
	res<<=8;
	res+=temp[1];						 
	return res ; //返回找到的编码
}						 							  
//将pbuf内的unicode码转为gbk码.
//pbuf:unicode码存储区,同时也是gbk码的输出区.必须小于80个字节.
//代码转换unit code-> GBK
//正点原子@HYW
//CHECK:09/10/30
void UniToGB(u8 *pbuf)
{   					  
	unsigned int  code;
	unsigned char i,m=0; 
	for(i=0;i<80;i++)//最长80个字符
	{	  
		code= pbuf[i*2+1]*256+pbuf[i*2]; 
		if((code==0)||(code==0xffff))break;
		if((code&0xff00)==0)//字母
		{
			if((code>=0x20)&&(code<=0x7e))
			{
				pbuf[m++]=(unsigned char)code;              
			}else pbuf[m++]='?';//无法识别的用？代替 
			continue;
		}
		if(code>=0X4E00)//是汉字
		{   								    
			code=UnicodeToGBK(code);//把unicode转换为gb2312 	   
			pbuf[m++]=code>>8;	 
			pbuf[m++]=(u8)code; 
		}else pbuf[m++]='?';//无法识别的用？代替  
	}    
	pbuf[m]='\0';//添加结束符号  			      
}
