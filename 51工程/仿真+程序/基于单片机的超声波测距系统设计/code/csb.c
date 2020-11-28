/*****************************************************
* 文件名称：CSB.c							   
* 功能：超声波测距
* 当前版本：1.0
* 作者：YuanDong
* 完成日期：2009年7月18日
******************************************************/
#include <reg52.h>
#include "intrins.h"
#include "12864LCDdriver.h"
#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long int
#define V=173
sbit CSOut=P1^7;
sbit Start=P1^4;

ulong TIME;
uchar DISTANCE;
uchar code discode[11]={'0','1','2','3','4','5','6','7','8','9',' '};
ulong data disnum[5];
bit data ReceiveOK=0;
bit data TOut;
bit data FLAG;
 
/*********************************************************
* 函数名称：void delay2(uchar x)
* 功    能：延时函数
* 入口参数：无
* 出口参数：无
*********************************************************/
void delay2(uchar x)
{
 uchar a,b;
 for(a=0;a<x;a++)
  for(b=0;b<255;b++);
}
 
/*********************************************************
* 函数名称：void init(void)
* 功    能：初始化
* 入口参数：无
* 出口参数：无
*********************************************************/
void init(void)
{
 lcd_init();//LCD初始化，开机调用一次
 TMOD=0x01;//T0定时器方式1
 IT0=0;//INT0负边沿触发
 IP=0x01;//INT0高优先级
 EA=1;//开总中断
}
  
/*********************************************************
* 函数名称：
* 功    能：超声波发射函数
* 入口参数：无
* 出口参数：无
*********************************************************/
void CCOut(void)
{
 TR0=1;
//40KHz
 CSOut=0;//1
 _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
 _nop_();_nop_();
 CSOut=1;//2
 _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
 _nop_();
 CSOut=0;//3
 _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
 _nop_();_nop_();
 CSOut=1;//4
 _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
 _nop_();
 CSOut=0;//5
 _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
 _nop_();_nop_();
 CSOut=1;//6
 _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
 _nop_();
 CSOut=0;//7
 _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
 _nop_();_nop_();
 CSOut=1;//8
 _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
 _nop_();
 CSOut=0;//9
 _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
 _nop_();_nop_();
 CSOut=1;//10
 _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
 _nop_();
 CSOut=0;//11
 _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
 _nop_();_nop_();
 CSOut=1;//12
}
  
/*********************************************************
* 函数名称：void DataProcess(void)
* 功    能：数据处理函数
* 入口参数：无
* 出口参数：无
*********************************************************/
void DataProcess(void)
{
  ulong time=0;
  TIME=TH0;
  TIME=(TIME<<8)|TL0;
  TIME*=173;//距离
  TIME=TIME/10000;//单位:CM
  disnum[0]=(uchar)TIME%10;        //个位
  disnum[4]=TIME/10;
  disnum[1]=(uchar)disnum[4]%10;//十位
  disnum[4]=disnum[4]/10;
  disnum[2]=(uchar)disnum[4]%10;//百位
  disnum[4]=disnum[4]/10;
  disnum[3]=(uchar)disnum[4]%10;//千位
}
/*********************************************************
* 函数名称：void TimeOut(void) interrupt 1
* 功    能：超时处理函数 T0
* 入口参数：无
* 出口参数：无
*********************************************************/
void TimeOut(void) interrupt 1
{
 TR0=0;
 ET0=0;
 EX0=0;
 ReceiveOK=0;
 TOut=1;
}
	 
/*********************************************************
* 函数名称：void Receive(void) interrupt 0
* 功    能：超声波接收处理函数
* 入口参数：无
* 出口参数：无
*********************************************************/
void Receive(void) interrupt 2
{
 TR0=0;
 EX0=0;
 ET0=0;
 ReceiveOK=1; //设定接收成功标志
 TOut=0;      //清除超时标志
}
   
/*********************************************************
* 函数名称：void LCDDisplay(void)
* 功    能：测量结果显示函数
* 入口参数：无
* 出口参数：无
*********************************************************/
void LCDDisplay(void)
{
 lcd_home();
 lcd_writestr(0,0,"  超声波测距仪  ");
 lcd_writestr(1,0,"＊＊＊＊＊＊＊＊");
 lcd_writestr(2,0,"当前被测距离为：");
 lcd_writestr(3,0,"        厘米    ");
 lcd_writechar(discode[disnum[3]],discode[disnum[2]],discode[disnum[1]],discode[disnum[0]]);
}

/*********************************************************
* 函数名称：void ErrorDisplay(void)
* 功    能：出错提示函数
* 入口参数：无
* 出口参数：无
*********************************************************/
void ErrorDisplay(void)
{
 lcd_home();
 lcd_writestr(0,0,"  超声波测距仪  ");
 lcd_writestr(1,0,"＊＊＊＊＊＊＊＊");
 lcd_writestr(2,0,"未收到回波信号，");
 lcd_writestr(3,0,"请缩短测量距离！");
}
	 
/*********************************************************
* 函数名称：void ReadyDis(void)
* 功    能：预备好提示函数
* 入口参数：无
* 出口参数：无
*********************************************************/
void ReadyDis(void)
{
 lcd_home();
 lcd_writestr(0,0,"  超声波测距仪  ");
 lcd_writestr(1,0,"＊＊＊＊＊＊＊＊");
 lcd_writestr(2,0,"    已准备好    ");
 lcd_writestr(3,0,"    等待测量    ");
}
	
/*********************************************************
* 函数名称：void main(void)
* 功    能：主函数
* 入口参数：无
* 出口参数：无
*********************************************************/
void main(void)
{
  uchar ct;
  init();         //初始化
  ReadyDis();
  while(1)
  {
    if(Start==0)
    {
      delay2(50);
      if(Start==0) FLAG=1;
    } 
 
    if(FLAG==1)   //启动测量一次
    {
      TH0=0x00;
      TL0=0x00;
      TIME=0x00;
      ET0=1;
      CCOut();
      ct=100;
      while(--ct);
      EX0=1;
      while(TOut==0)
      {
        if(ReceiveOK==1)    //接收成功
        {
           DataProcess();   //数据处理
           LCDDisplay();    //LCD显示
           ReceiveOK=0;     //清除接收成功标志
           goto aa;
        }
      }
      if(TOut==1)
      {
        TOut=0;
        ErrorDisplay(); //超时,错误提示
      }
  aa: FLAG=0;            //清除定时标志,等待下一次测量
    }
  }
}
 
