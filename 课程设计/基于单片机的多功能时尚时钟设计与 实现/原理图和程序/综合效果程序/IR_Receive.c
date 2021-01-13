
#include "task.h"
bit new_code;
/*结构体*/      /* 保存一次解码后接收到的四字节数据*/
static struct IR_data    //红外接收的数据结构
{
    unsigned char addr1;     // 地址1(客户码1)
    unsigned char addr2;     // 地址2(客户码2)
    unsigned char data1;     // 数据1(数据码)
    unsigned char data2;     // 数据2(数据码反码)
} IR_DATA;
#define GTime 53                
#define CTime 114               
#define D0MinTime 4  
#define D0MaxTime 9  
#define D1MinTime 11  
#define D1MaxTime 16             
#define TimeOut_cnt 250 
/*全局公共变量*/
 unsigned char T0_CNT;                // 定时器计数值
 unsigned char T0_CNT_bk;           // 计数备份
 bit TimeOut;                     // 超时标志
 bit Guide;                           // 引导码有效
 bit Continuous;                      // 连_发码
 unsigned char xdata IR_Time[33]; // 保存每两个下降沿之间的时间间隔
uchar key_code;
/*********************************************************************************************
/*Timer1中断子程序*/
void TR1_Service(void) interrupt 3 using 2
{
    //static unsigned char  T;
  //  T++;
  //  if(T>1)
  //  {
      //  T=0;
        T0_CNT ++;
  //  }
    if(T0_CNT > TimeOut_cnt)
    {
        TimeOut = 1;       // 超时标志
    }
}
/***********************************************************************/
/*解码核心程序*/
void Decode(void)
{
    unsigned char i=0x00,j,k;
    static unsigned char *p;  // 指向结构体IR_DATA.XX的指针
    EX1 = 0;   // 关外部中断1
    /*/////////////////////////进行解码处理////////////////////////*/
    p = &IR_DATA.addr1;
    for(k=0; k<4; k++)
    {
        for(j=0; j<8; j++)
        {
            if((IR_Time[i]>D0MinTime) & (IR_Time[i]<D0MaxTime))
            {
                *p >>= 1;           // 右移1位，
                *p &= 0x7f;         // 与0111 1111置0. 数据“0” 0.56ms低电平+0.56ms高电平
            }
            else if((IR_Time[i]>D1MinTime) & (IR_Time[i]<D1MaxTime))
            {
                *p >>= 1;                // 右移1位，
                *p |= 0x80;              // 或1000 0000置1. 数据“1” 0.56ms低电平+1.69ms高电平
            }
            i ++;
        }
        p ++;
    }
    if(IR_DATA.data2+IR_DATA.data1==0XFF)
    {
        key_code=IR_DATA.data1;
		new_code=1;
    }
    else
    {
        key_code=0XFF;   /**非本机遥控器或数据错误**/
    };
    /*/////////////////////////解码处理完毕////////////////////////*/
    EX1 = 1;   // 重新开放外部中断1
} 
void serviceINT0(void) interrupt 2 using 1  //{////外部中断1的中断函数。用于红外线读数。
{
    static unsigned char m=0;
	TR1=1;
	
    T0_CNT_bk = T0_CNT;     // 备份时间计数值，即前一个下降沿到本下降沿的时间间隔
    T0_CNT = 0x00;          // 清空时间计数值
    if(TimeOut)             // 如果超时
    {
        //  TL0 = TIMER0_COUNT;     // 初始化定时器0       －0x1f（31）
        TimeOut = 0;        // 清除超时标志
        m = 0;              // 复位数据位
        T0_CNT = 0x00;      // 清空时间计数值
        Guide = 0;          // 清除引导标志
        Continuous = 0;     // 清除连_发标志
    }
    else       // 正常按键时长58.5ms～76.5ms
    {
        if(Guide | Continuous)          // 如果引导码有效
        {
            IR_Time[m++] = T0_CNT_bk;       // 保存时间间隔
            if(m == 32)   // 接收够32数据后
            {
                m = 0;
                Guide = 0;    // 清除引导标志
				 //new_code=1;
				TR1=0;
                /*进行解码操作*/
                Decode();     // 解码
					
            }
        }
        if(T0_CNT_bk > GTime)   // 如果时间间隔>引导码时长
        {
            Guide = 1;          // 使能引导标志
            m = 0;
        };
        if(T0_CNT_bk > CTime)    // 如果时间间隔>连_发码时长
        {
            Continuous = 1;      // 使能连_发标志
            m = 0;
        }
    }//end of 超时
}
/*********************************************************************************/
/*************************************************************************************
************************************************************************************
***********************                                     ***************************
***********************    http://59tiaoba.taobao.com       ***************************
***********************                                     ***************************
************************************程序编写：Fucp****************************************
**********************************************************************************/