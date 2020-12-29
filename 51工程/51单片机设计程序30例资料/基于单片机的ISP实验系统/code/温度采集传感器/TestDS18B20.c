/*************************************************
*文件名称：温度传感器DS18B20测试函数文件
*名称功能：测试实验系统中DS18B20
*版本：	   V0.0.0
*作者：	   yd
*时间：	   09.07.22
*************************************************/
#include <AT89X51.h>
#include <intrins.h>
#define uchar unsigned char
#define uint  unsigned int
//--------定义温度传感器端口-----------
#define    DQ   P3_4
//-------------------------------------
/*************************************************
*函数名称：delay_50us(uint t)
*函数功能：12M，单循环软件延时50us
*入口参数：t,延时周期数
*出口参数：无
*************************************************/
void delay_50us(uint t)
{

  while( --t );

}
/*************************************************************
*函数名称：delay60us(void)
*函数功能：延时60us
*入口参数：无
*出口参数：无  										
*************************************************************/
void delay60us(void)
{
	uchar i;
	for(i=0;i<20;i++);
}
/*************************************************
*函数名称：ds18b20_reset()
*函数功能：ds18b20 复位
*入口参数：无
*出口参数：返回ds18b20当前数据口状态
*************************************************/
bit  ds18b20_reset( ) 
{
    DQ=0;
	delay_50us(10); 			//延时500us
	DQ=1;
	delay_50us(2);			    // 延时100us
	return(DQ);		 		    //读取数据口状态
}
/*************************************************************
*函数名称：ds18b20_init(void)
*函数功能：ds18b20的初始化
*入口参数：无
*出口参数：无     											
*************************************************************/
void ds18b20_init(void)
{
	while(1)
	{
		if(!ds18b20_reset())  	    //收到ds18b20的应答信号
		{	
			DQ=1;
			delay60us();	 		//延时60us
			break;		
		}
		else
			ds18b20_reset();	 	//否则再发复位信号
	}
}
/*************************************************************
*函数名称：ds18b20_writecommand(uchar command)
*函数功能：向ds18b20写命令
*入口参数：command，命令参数
*出口参数：无     				
*************************************************************/
void ds18b20_writecommand(uchar command)
{	

	uchar   i;
	for(i=0;i<8;i++)
	{
		if((command & 0x01)==0)
		{
			DQ =0;					//写0
			delay60us();			//延时60us
			_nop_();
			_nop_();
			_nop_();
			_nop_();
			_nop_();
			_nop_();
			DQ =1;			   	
			_nop_();
			_nop_();

		}
		else						//写1
		{
		 	DQ =0;
			_nop_();
			_nop_();				//延时2us
			DQ =1;
			delay60us();			//延时60us
			_nop_();
			_nop_();
			_nop_();
			_nop_();
		}
		command=_cror_(command,1); // 右移1位
	 }
}

/*************************************************************
*函数名称：ds18b20_readdata(void)
*函数功能：读ds18b20数据
*入口参数：无
*出口参数：返回读到的数据
*************************************************************/
uchar ds18b20_readdata(void)
{
	uchar readdata;
	uchar i;
	for(i=0;i<8;i++)
	{
		DQ=0;
		_nop_();
		_nop_();
		_nop_();
		DQ=1;		   //释放总线
		if(DQ==0)	   //如果读到的是0
		{
			readdata=readdata&0x7f;
			delay60us();
		}
		else			//读到的是1
		{
			readdata=readdata|0x80;
			delay60us();
		}
		if(i<7)
		
		readdata=_cror_(readdata,1);
	}
	return readdata;
}

void main()
{
  uchar temputreTemp[2];         //当前温度变量寄存数组
  uchar i;
  while(1)
  {
    ds18b20_init();	             //数字温度计初始化 
	ds18b20_writecommand(0xcc);	 //单机模式下，跳过ROM
 	ds18b20_writecommand(0x44);	 //开始转换
	delay_50us(10);              //延时500us
	ds18b20_writecommand(0xcc);	 //跳过ROM
 	ds18b20_writecommand(0xbe);	 //读寄存器
	for(i=0;i<2;i++)
 	{	
 	   temputreTemp[i]=ds18b20_readdata();	//将温度数据的高位和地位存到数组中，temp[0]高位，temp[1]低位	
 	}

  }
  
}