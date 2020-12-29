 /*************************************************************************/
#define uchar unsigned char
#define uint unsigned int
code uchar ershi1_code[24]={ 
0x05,0x14,0x03,0x18,
0x05,0x14,0x04,0x13,
0x05,0x14,0x05,0x15,
0x06,0x16,0x07,0x16,
0x07,0x16,0x08,0x17,
0x07,0x16,0x06,0x15,}


code uchar ershi2_code[]={}
/**************************************************************************
* 名称: void ershi( uchar * clock_time )
* 功能: 输入BCD的阳历数据， 输出BCD阴历数据( 1901 - 2099 )
* 入口参数: c_flag:阳历的世纪标志  clock_time: 时钟地址
* 出口参数: 无
* 说明: c_flag = 0 :21世纪 c_flag = 1 :19世纪 
*****************************************************************************/
void  Ershi( uchar * clock_time )
{
  // bit flag_month, flag_year;
   uchar year, month, day, month_point; //定义 年 月 天
   uchar temp1, temp2, temp3;
  // uint calendar_address; //定义农历地址
  // uint day_number;
  // uchar clock_moon[3]; //定义阴历


   clock_time += 3; //指向日
   day = ( * clock_time >> 4 ) * 10 + ( *clock_time & 0x0f ); //BCD转换十进制
   clock_time ++; //指向月
   month = ( * clock_time >> 4 ) * 10 + ( * clock_time & 0x0f ); //BCD转换十进制
   clock_time ++; //指向年
   year = ( * clock_time >> 4 ) * 10 + ( * clock_time & 0x0f ); //BCD转换十进制 

   temp1=ershi1_code[(month-1)*2+1]      //找出本月第二个节气的最小日
   //temp2=(month-1)/4;
   temp2=ershi2_code[year*3+(month-1)/4];     //找出本月的节气对应的字节
   temp3=(month-1)%4;
   temp2=temp2<<(temp3*2+1)&0x80;
   temp1=temp1+temp2>>7;                // 计算出本月第二个节气的日期
   if(day>=temp1)
    {temp1=month*2-1;}
	else 
	  {
	       temp1=ershi1_code[(month-1)*2];	//找出本月第一个节气的最小日
		    temp2=ershi2_code[year*3+(month-1)/4];     //找出本月的节气对应的字节
           temp3=(month-1)%4;
           temp2=temp2<<(temp3*2)&0x80;
           temp1=temp1+temp2>>7; 
		   if(day>=temp1)
		     temp1=month*2-2;
			temp1=month*2-3;
		 }
LCD_ERSHI(temp1);
}
