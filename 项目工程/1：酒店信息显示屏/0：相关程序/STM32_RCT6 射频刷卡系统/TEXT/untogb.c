#include "untogb.h"
#include "flash.h"
#include "usart.h"
#include "fontupd.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//Mini STM32������
//UNICODE TO GBK ����ת������ ��������		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/5/23 
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////	 
 		

//��UNICODE��ת��ΪGBK��
//unicode:UNICODE��
//����ֵ:GBK��				 
u16 UnicodeToGBK(u16 unicode)//�ö��ֲ����㷨
{
   	u32 offset;
	u8 temp[2];
	u16 res;
	if(unicode<=0X9FA5)offset=unicode-0X4E00;
	else if(unicode>0X9FA5)//�Ǳ�����
	{
		if(unicode<0XFF01||unicode>0XFF61)return 0;//û�ж�Ӧ����
		offset=unicode-0XFF01+0X9FA6-0X4E00;    
	}  
	SPI_Flash_Read(temp,offset*2+UNI2GBKADDR,2);//�õ�GBK��   
	res=temp[0];
	res<<=8;
	res+=temp[1];						 
	return res ; //�����ҵ��ı���
}						 							  
//��pbuf�ڵ�unicode��תΪgbk��.
//pbuf:unicode��洢��,ͬʱҲ��gbk��������.����С��80���ֽ�.
//����ת��unit code-> GBK
//����ԭ��@HYW
//CHECK:09/10/30
void UniToGB(u8 *pbuf)
{   					  
	unsigned int  code;
	unsigned char i,m=0; 
	for(i=0;i<80;i++)//�80���ַ�
	{	  
		code= pbuf[i*2+1]*256+pbuf[i*2]; 
		if((code==0)||(code==0xffff))break;
		if((code&0xff00)==0)//��ĸ
		{
			if((code>=0x20)&&(code<=0x7e))
			{
				pbuf[m++]=(unsigned char)code;              
			}else pbuf[m++]='?';//�޷�ʶ����ã����� 
			continue;
		}
		if(code>=0X4E00)//�Ǻ���
		{   								    
			code=UnicodeToGBK(code);//��unicodeת��Ϊgb2312 	   
			pbuf[m++]=code>>8;	 
			pbuf[m++]=(u8)code; 
		}else pbuf[m++]='?';//�޷�ʶ����ã�����  
	}    
	pbuf[m]='\0';//��ӽ�������  			      
}
