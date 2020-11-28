#define CLOCK_GLOBAL
#include "clock.h"
/********************************************************************************************
* 函数名称：Clock_Write_Byte()
* 功    能：向时钟DS1302写入一个字节
* 入口参数：temp
* 出口参数：无
*********************************************************************************************/
void Clock_Write_Byte(uchar temp)
{
    uchar i;
    ACC=temp;
    for(i=8; i>0; i--)
    {
        clock_io = ACC0;           	//相当于汇编中的 RRC
        clock_sclk = 1;
        clock_sclk = 0;
        ACC = ACC >> 1; 
    } 
}
/********************************************************************************************
* 函数名称：Clock_Read_Byte()
* 功    能：从时钟DS1302读取一个字节
* 入口参数：无
* 出口参数：ACC
*********************************************************************************************/
uchar Clock_Read_Byte(void)
{
	uchar i;
    for(i=8; i>0; i--)
    {
        ACC = ACC >>1;         			//相当于汇编中的 RRC 
        ACC7= clock_io;
		clock_sclk = 1;
        clock_sclk = 0;
	} 
    return(ACC);
}
/********************************************************************************************
* 函数名称：Clock_Write_Time()
* 功    能：向时钟DS1302写入一个时间
* 入口参数：时间地址  
* 出口参数：无
*********************************************************************************************/
void Clock_Write_Time(uchar address, uchar temp)
{
	clock_sclk=0;
	clock_rst=0;
	clock_rst=1;
	Clock_Write_Byte(address);
	Clock_Write_Byte(temp);
	clock_rst=0;
	clock_sclk=1;
}
/********************************************************************************************
* 函数名称：Clock_Read_Time()
* 功    能：从时钟DS1302读出一个时间
* 入口参数：时间地址  
* 出口参数：时间数据
*********************************************************************************************/
uchar Clock_Read_Time(uchar address)
{
	uchar temp=0;
	clock_sclk=0;
	clock_rst=0;
	clock_rst=1;
	Clock_Write_Byte( address|0x01 );
	temp=Clock_Read_Byte();
	clock_rst=0;
	clock_sclk=1;
	return(temp);
}

/********************************************************************************************
* 函数名称：Clock_Initial()
* 功    能：时钟初始化
* 入口参数：时间地址   时间数据
* 出口参数：
*********************************************************************************************/
void Clock_Initial(uchar *clock_time )
{
    Clock_Write_Time(0x8e,0x00);                //WP=0 写操作
    Clock_Write_Time( second_address, * clock_time );   //秒
    clock_time ++;
    Clock_Write_Time( minute_address, * clock_time );    //分
    clock_time ++;
    Clock_Write_Time( hour_address, * clock_time );     //时
    clock_time ++;
    Clock_Write_Time( day_address, * clock_time );      //日
    clock_time ++;
    Clock_Write_Time( month_address, * clock_time);   //月
	clock_time ++;
    Clock_Write_Time( year_address, * clock_time );    //年

    Clock_Write_Time( 0x8e,0x80);              //WP=1 写保护	
}

/********************************************************************************************
* 函数名称：Clock_Fresh( uchar * clock_time )
* 功    能：从时钟DS1302读出时间
* 入口参数：时间地址  
* 出口参数：时间数据
*********************************************************************************************/
void Clock_Fresh(uchar * clock_time )
{
	* clock_time = Clock_Read_Time( second_address );  //读秒
	clock_time ++;
	* clock_time = Clock_Read_Time( minute_address ); //读分
	clock_time ++;
	* clock_time = Clock_Read_Time( hour_address ); //读时
    clock_time ++;
    * clock_time = Clock_Read_Time( day_address ); //读日	
	clock_time ++;
    * clock_time = Clock_Read_Time( month_address ); //读月
	clock_time ++;
	*clock_time  = Clock_Read_Time( year_address ); //读年	
}
