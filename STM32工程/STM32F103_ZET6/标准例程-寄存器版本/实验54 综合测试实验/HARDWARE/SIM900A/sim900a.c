#include "sim900a.h" 
#include "delay.h"	
#include "led.h"     
#include "w25qxx.h"  
#include "malloc.h"
#include "string.h"    
#include "text.h"		
#include "usart3.h" 
#include "ff.h" 
#include "ucos_ii.h" 

//////////////////////////////////////////////////////////////////////////////////	   
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������V3
//SIM900A ��ʼ�� 
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/3/5
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved
//********************************************************************************
//�޸�˵��
//��
////////////////////////////////////////////////////////////////////////////////// 	

__sim900dev sim900dev;	//sim900������

//sim900a���������,�����յ���Ӧ��
//str:�ڴ���Ӧ����
//����ֵ:0,û�еõ��ڴ���Ӧ����
//    ����,�ڴ�Ӧ������λ��(str��λ��)
u8* sim900a_check_cmd(u8 *str)
{
	char *strx=0;
	if(USART3_RX_STA&0X8000)		//���յ�һ��������
	{ 
		USART3_RX_BUF[USART3_RX_STA&0X7FFF]=0;//��ӽ�����
		strx=strstr((const char*)USART3_RX_BUF,(const char*)str);
	} 
	return (u8*)strx;
}
//��sim900a��������
//cmd:���͵������ַ���(����Ҫ��ӻس���),��cmd<0XFF��ʱ��,��������(���緢��0X1A),���ڵ�ʱ�����ַ���.
//ack:�ڴ���Ӧ����,���Ϊ��,���ʾ����Ҫ�ȴ�Ӧ��
//waittime:�ȴ�ʱ��(��λ:10ms)
//����ֵ:0,���ͳɹ�(�õ����ڴ���Ӧ����)
//       1,�յ���Ԥ�ڽ��
//       2,û�յ��κλظ�
u8 sim900a_send_cmd(u8 *cmd,u8 *ack,u16 waittime)
{
	u8 res=0;  
	USART3_RX_STA=0;
	sim900dev.cmdon=1;//����ָ��ȴ�״̬
	if((u32)cmd<=0XFF)
	{   
		while((USART3->SR&0X40)==0);//�ȴ���һ�����ݷ������  
		USART3->DR=(u32)cmd;
	}else u3_printf("%s\r\n",cmd);//��������
	if(ack&&waittime)		//��Ҫ�ȴ�Ӧ��
	{
		while(--waittime)	//�ȴ�����ʱ
		{
			delay_ms(10);
			if(USART3_RX_STA&0X8000)//�Ƿ���յ��ڴ���Ӧ����
			{
				if(sim900a_check_cmd(ack))res=0;//�յ��ڴ��Ľ����
				else res=1;//�����ڴ��Ľ��
				break; 
			} 
		}
		if(waittime==0)res=2; 
	}
	return res;
}
//�������ʱ����,��sim900a_send_cmd�ɶ�ʹ��/�����sim900a_send_cmd�����.
void sim900a_cmd_over(void)
{
	USART3_RX_STA=0;
	sim900dev.cmdon=0;//�˳�ָ��ȴ�״̬
}
//��1���ַ�ת��Ϊ16��������
//chr:�ַ�,0~9/A~F/a~F
//����ֵ:chr��Ӧ��16������ֵ
u8 sim900a_chr2hex(u8 chr)
{
	if(chr>='0'&&chr<='9')return chr-'0';
	if(chr>='A'&&chr<='F')return (chr-'A'+10);
	if(chr>='a'&&chr<='f')return (chr-'a'+10); 
	return 0;
}
//��1��16��������ת��Ϊ�ַ�
//hex:16��������,0~15;
//����ֵ:�ַ�
u8 sim900a_hex2chr(u8 hex)
{
	if(hex<=9)return hex+'0';
	if(hex>=10&&hex<=15)return (hex-10+'A'); 
	return '0';
}
//unicode gbk ת������
//src:�����ַ���
//dst:���(uni2gbkʱΪgbk����,gbk2uniʱ,Ϊunicode�ַ���)
//mode:0,unicode��gbkת��;
//     1,gbk��unicodeת��;
void sim900a_unigbk_exchange(u8 *src,u8 *dst,u8 mode)
{
    OS_CPU_SR cpu_sr=0;
	u16 temp; 
	u8 buf[2];
	OS_ENTER_CRITICAL();//�����ٽ���(�޷����жϴ��)  
	if(mode)//gbk 2 unicode
	{
		while(*src!=0)
		{
			if(*src<0X81)	//�Ǻ���
			{
				temp=(u16)ff_convert((WCHAR)*src,1);
				src++;
			}else 			//����,ռ2���ֽ�
			{
				buf[1]=*src++;
				buf[0]=*src++;    
				temp=(u16)ff_convert((WCHAR)*(u16*)buf,1); 
			}
			*dst++=sim900a_hex2chr((temp>>12)&0X0F);
			*dst++=sim900a_hex2chr((temp>>8)&0X0F);
			*dst++=sim900a_hex2chr((temp>>4)&0X0F);
			*dst++=sim900a_hex2chr(temp&0X0F);
		}
	}else	//unicode 2 gbk
	{ 
		while(*src!=0)
		{
			buf[1]=sim900a_chr2hex(*src++)*16;
			buf[1]+=sim900a_chr2hex(*src++);
			buf[0]=sim900a_chr2hex(*src++)*16;
			buf[0]+=sim900a_chr2hex(*src++);
 			temp=(u16)ff_convert((WCHAR)*(u16*)buf,0);
			if(temp<0X80){*dst=temp;dst++;}
			else {*(u16*)dst=swap16(temp);dst+=2;}
		} 
	}
	*dst=0;//��ӽ�����
	OS_EXIT_CRITICAL();	//�˳��ٽ���(���Ա��жϴ��)	
} 

extern void sms_remind_msg(u8 mode);
extern void phone_incall_task_creat(void);
//�绰����/��⵽���� ���
void sim900a_cmsgin_check(void)
{
	u8 *p1,*p2; 
	u8 num;
	if(sim900dev.cmdon==0&&sim900dev.mode==0)//��ָ��ȴ�״̬,.����/����ģʽ,�ż������
	{
		if(USART3_RX_STA&0X8000)//�յ�������
		{
			if(sim900a_check_cmd("+CLIP:"))//���յ�����?
			{
				p1=sim900a_check_cmd("+CLIP:");
				p1+=8;
				p2=(u8*)strstr((const char *)p1,"\"");
				p2[0]=0;//��ӽ����� 
				strcpy((char*)sim900dev.incallnum,(char*)p1);//��������
				sim900dev.mode=3;			//���������
				phone_incall_task_creat();	//������������
			}
			if(sim900a_check_cmd("+CMGS:"))//���ŷ��ͳɹ�
			{
				sms_remind_msg(1);//��ʾ������Ϣ�ɹ�
			}
			if(sim900a_check_cmd("+CMTI:"))//�յ�����Ϣ
			{
				if(sim900dev.newmsg<SIM900_MAX_NEWMSG)
				{
					p1=(u8*)strstr((const char*)(USART3_RX_BUF),",");   
					p2=(u8*)strstr((const char*)(p1+1),"\r\n");
					if((p2-p1)==2)num=p1[1]-'0';//1λ
					else if((p2-p1)==3)num=(p1[1]-'0')*10+p1[2]-'0';//2λ
					else if((p2-p1)==4)num=(p1[1]-'0')*100+(p1[2]-'0')*10+p1[2]-'0';//3λ 
					sim900dev.newmsgindex[sim900dev.newmsg]=num;
					sim900dev.newmsg++;
				}
				sms_remind_msg(0);//��ʾ�յ�����Ϣ
			}			
			USART3_RX_STA=0;
			printf("rev:%s\r\n",USART3_RX_BUF);	
		}
	}
}
//sim900a״̬���
void sim900a_status_check(void)
{
	u8 *p1; 
	if(sim900dev.cmdon==0&&sim900dev.mode==0&&USART3_RX_STA==0)//��ָ��ȴ�״̬.����/����ģʽ/��û���յ��κ�����,�������ѯ
	{
		if(sim900a_send_cmd("AT+CSQ","OK",25)==0)//��ѯ�ź�����,˳����GSMģ��״̬
		{
			p1=(u8*)strstr((const char*)(USART3_RX_BUF),":"); 
			p1+=2;
			sim900dev.csq=(p1[0]-'0')*10+p1[1]-'0';//�ź�����
			if(sim900dev.csq>30)sim900dev.csq=30;		
			sim900dev.status|=1<<7;	//��ѯGSMģ���Ƿ���λ?
		}else 
		{ 
			sim900dev.csq=0;	
			sim900dev.status=0;	//���²���
		} 
		if((sim900dev.status&0XC0)==0X80)//CPIN״̬,δ��ȡ?
		{ 
			sim900a_send_cmd("ATE0","OK",100);//������(����ر�,����������ݿ����쳣)
			if(sim900a_send_cmd("AT+CPIN?","OK",25)==0)sim900dev.status|=1<<6;//SIM����λ
			else sim900dev.status&=~(1<<6);//SIM������ 
		} 
		if((sim900dev.status&0XE0)==0XC0)//��Ӫ������,δ��ȡ?
		{ 
			if(sim900a_send_cmd("AT+COPS?","OK",25)==0)//��ѯ��Ӫ������
			{ 
				p1=(u8*)strstr((const char*)(USART3_RX_BUF),"MOBILE");//����MOBILE,�����ǲ����й��ƶ�?
				if(p1)sim900dev.status&=~(1<<4); //�й��ƶ� 
				else 
				{
					p1=(u8*)strstr((const char*)(USART3_RX_BUF),"UNICOM");//����UNICOM,�����ǲ����й���ͨ?
					if(p1)sim900dev.status|=1<<4;	//�й���ͨ 
				}
				if(p1)
				{
					sim900dev.status|=1<<5;	//�õ���Ӫ�������� 
					//phone����ͨ������
					sim900a_send_cmd("AT+CLIP=1","OK",100);	//����������ʾ 
					sim900a_send_cmd("AT+COLP=1","OK",100);	//���ñ��к�����ʾ
					//sms����ͨ������
					sim900a_send_cmd("AT+CMGF=1","OK",100);			//�����ı�ģʽ 
					sim900a_send_cmd("AT+CSCS=\"UCS2\"","OK",100);	//����TE�ַ���ΪUCS2 
					sim900a_send_cmd("AT+CSMP=17,0,2,25","OK",100);	//���ö���Ϣ�ı�ģʽ���� 
				}
			}else sim900dev.status&=~(1<<5);	//δ�����Ӫ������
		}
		sim900a_cmd_over();//�������
	}
}























