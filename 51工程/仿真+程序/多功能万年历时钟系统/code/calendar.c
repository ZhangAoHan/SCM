#define CALENDAR_GLOBAL
#include "calendar.h"
#include "character.h"
code uchar ershi1_code[24]={ 
0x05,0x14,0x03,0x18,
0x05,0x14,0x04,0x13,
0x05,0x14,0x05,0x15,
0x06,0x16,0x07,0x16,
0x07,0x16,0x08,0x17,
0x07,0x16,0x06,0x15,};
uchar code ershi2_code[]={
0xf1,0x49,0x42,	 //00
0x23,0x9d,0x43,	 //01
0x3f,0xef,0xc3,	 //02
0xbf,0xff,0xff,  //03
0xf1,0x49,0x42,  //04
0x23,0x4d,0x43,  //05
0x00,0x00,0x00,  //07
0xf5,0x49,0x02,  //08
0x21,0x4d,0x43,  //09
0x3f,0x6d,0xc3,  //10
0xbf,0xff,0xdf,  //11
0xf1,0x09,0x02,  //12
0x21,0x49,0x43,  //13
0x3f,0x6d,0xc3,  //14
0xbf,0xff,0xd7,  //15
0xb0,0x09,0x02,  //16
0x01,0x49,0x43,  //17
0x37,0x6d,0xc3,  //18
0x3f,0xef,0xdb,  //19
0xb0,0x00,0x02,  //20
};
/********************************************************************************
* 名称: get_moon_day(uchar month_p,uint table_addr)
* 功能: 读取数据表中农历的大月或小月 ，如果大月返回1, 小月返回0
* 入口参数:
* 出口参数:
*********************************************************************************/
bit get_moon_day( uchar month_p,uint calendar_address )
{
    uchar temp;
    switch(month_p)
	{
        case 1: 
		 { 
		  temp = year_code[calendar_address] & 0x08; 
		  if(temp==0) 
		    return(0);
		  else 
		    return(1); 
	     }
        case 2: 
		 { 
		   temp = year_code[calendar_address] & 0x04; 
		   if(temp==0) 
		     return(0); 
		   else 
		     return(1); 
	     }
        case 3: 
		 { 
		   temp = year_code[calendar_address] & 0x02; 
		   if(temp==0) 
		     return(0); 
		   else 
		     return(1); 
	     }
        case 4: 
		 { 
		   temp = year_code[calendar_address] & 0x01; 
		   if(temp==0)
		     return(0);
	       else 
		     return(1); 
	     }
        case 5:
		 { 
		   temp = year_code[calendar_address + 1] & 0x80; 
		   if(temp==0) 
		     return(0);
		   else 
		     return(1); 
		 }
        case 6: 
		 { 
		   temp = year_code[calendar_address + 1] & 0x40;
		   if(temp==0) 
		     return(0); 
		   else 
		     return(1);
		 }
        case 7: 
		 { 
		   temp = year_code[calendar_address + 1] & 0x20;
		   if(temp==0) 
		     return(0); 
		   else 
		     return(1); 
		 }
        case 8: 
		 { 
		   temp = year_code[calendar_address + 1] & 0x10;
		   if(temp==0) 
		     return(0);
		   else 
		     return(1); 
		 }
        case 9: 
		 {
		   temp = year_code[calendar_address + 1] & 0x08; 
		   if(temp==0)
		     return(0); 
		   else 
		     return(1); 
		 }
        case 10: 
		 { 
		   temp = year_code[calendar_address + 1] & 0x04;
		   if(temp==0) 
		     return(0); 
		   else 
		     return(1);
		 }
        case 11: 
		 {
		   temp = year_code[calendar_address + 1] & 0x02;
		   if(temp==0) 
		     return(0); 
		   else 
		     return(1); 
		 }
        case 12: 
		 { 
		   temp = year_code[calendar_address + 1] & 0x01;
		     if(temp==0) 
			    return(0); 
		     else 
			    return(1); 
		 }
        case 13: 
		 { 
		    temp = year_code[calendar_address + 2] & 0x80; 
			if(temp==0) 
			  return(0);
		    else 
			  return(1); 
		 } 
		default:
		  break;
    }
}
/**************************************************************************
* 名称: void Calendar_Convert( uchar * clock_time )
* 功能: 输入BCD的阳历数据， 输出BCD阴历数据( 1901 - 2099 )
* 入口参数: c_flag:阳历的世纪标志  clock_time: 时钟地址
* 出口参数: 无
* 说明: c_flag = 0 :21世纪 c_flag = 1 :19世纪 
*****************************************************************************/
void Calendar_Convert( uchar c_flag, uchar * clock_time )
{
   bit flag_month, flag_year;
   uchar year, month, day, month_point; //定义 年 月 天
   uchar temp1, temp2, temp3;
   uint calendar_address; //定义农历地址
   uint day_number;
   uchar clock_moon[3]; //定义阴历
   clock_time += 3; //指向日
   day = ( * clock_time >> 4 ) * 10 + ( *clock_time & 0x0f ); //BCD转换十进制
   clock_time ++; //指向月
   month = ( * clock_time >> 4 ) * 10 + ( * clock_time & 0x0f ); //BCD转换十进制
   clock_time ++; //指向年
   year = ( * clock_time >> 4 ) * 10 + ( * clock_time & 0x0f ); //BCD转换十进制 
   calendar_address =  year  * 3;
   //春节(正月初一)所在的阳历月份
   temp1 = year_code[ calendar_address + 2 ] & 0x60; //Bit6~~Bit5:春节所在的阳历月份
   temp1 >>= 5 ;
   //春节(正月初一)所在的阳历日期
   temp2 = year_code[ calendar_address + 2 ] & 0x1f; //Bit4~~Bit0:春节所在的阳历日期
   //计算春节(正月初一)离当年元旦{ 1月1日(阳历) }的天数；春节只会在阳历的1月 或 2月
   if( temp1 == 1 )
      temp3 = temp2 - 1;
   else
      temp3 = temp2 + 31 - 1;
   //计算阳历日离当年元旦{ 1月1日(阳历) }的天数
   switch (month)
   {
      case 1:{day_number=day;}break;
	  case 2:{day_number=31+day;}break;
	  case 3:{if(year%4==0)
	             {day_number=60+day;}
				 else day_number=59+day;
			   }
			   break;
	  case 5:{if(year%4==0)
	             {day_number=121+day;}
				 else day_number=120+day;
			   }
			   break;
	  case 6:{if(year%4==0)
	             {day_number=152+day;}
				 else day_number=151+day;
			   }
			   break;
	  case 7:{if(year%4==0)
	             {day_number=182+day;}
				 else day_number=181+day;
			   }
			   break;
	  case 8:{if(year%4==0)
	             {day_number=213+day;}
				 else day_number=212+day;
			   }
			   break;
	  case 9:{if(year%4==0)
	             {day_number=244+day;}
				 else day_number=243+day;
			   }
			   break;
	  case 10:{if(year%4==0)
	             {day_number=274+day;}
				 else day_number=273+day;
			   }
			   break;
	  case 11:{if(year%4==0)
	             {day_number=305+day;}
				 else day_number=304+day;
			   }
			   break;
	  case 12:{if(year%4==0)
	             {day_number=335+day;}
				 else day_number=334+day;
			   }
			   break;
	  break;
	} //结束计算阳历日离当年元旦{ 1月1日(阳历) }的天数       
   //判断阳历日 在春节(正月初一) 之前 还是 之后
   if( day_number >= temp3 ) //阳历在春节之后 或者 春节当日
   {
      day_number -= temp3;
      month = 1;
      month_point = 1; // month_point 为月份指向，阳历日在春季前就是春季
	  flag_month = get_moon_day( month_point, calendar_address ); //检查该阴历月的大小  大月返回1  小月返回0
	  flag_year = 0;
	  if( flag_month )
	     temp1 = 30; //大月30天
	  else
 	     temp1 = 29; //小月29天
      //闰月所在的月分
	  temp2 = year_code[ calendar_address ] & 0xf0;
	  temp2 >>= 4; //提取高四位  假如是0 表示没有闰月

	  while( day_number >= temp1 )
	  {
	     day_number -= temp1;
         month_point ++;
         if( month == temp2 ) //如果是 闰月
         {
            flag_year = ~ flag_year; 
            if( flag_year == 0 ) 
               month +=1;
         }
         else
            month ++ ;
         flag_month = get_moon_day( month_point, calendar_address );
         if( flag_month )
            temp1 = 30;
         else
            temp1 = 29;
       }
       day = day_number ;
   }
   else //阳历在春节之前使用以下代码进行运算
   {
      temp3 -= day_number;
      if( year == 0 )
         { year = 99; c_flag = 1; }
      else
         year -= 1;
      calendar_address -= 0x03;
      month = 12;
      temp2 = year_code[ calendar_address] & 0xf0;
      temp2 >>= 4; //提取高4位
      if( temp2 == 0 )
         month_point = 12;
      else
         month_point = 13;
      flag_year = 0;
      flag_month = get_moon_day( month_point, calendar_address );
      if( flag_month )
         temp1 = 30;
      else
         temp1 = 29;
      while( temp3 > temp1 )
      {
         temp3 -= temp1;
         month_point --;
         if( flag_year == 0 )
         month -=1;
         if( month == temp2 )
         flag_year = ~ flag_year;
         flag_month = get_moon_day( month_point, calendar_address );
         if( flag_month )
            temp1 = 30;
         else
            temp1 = 29;
         
      }
      //day = temp1 - day_number + 1;
	  day=temp1-temp3;	  
	     }
   //HEX->BCD ,运算结束后,把数据转换为BCD数据
   temp1 = year / 10;
   temp1 <<= 4;
   clock_moon[2] = temp1 | ( year % 10 );
 
   temp1 = month / 10;
   temp1 <<= 4;
   clock_moon[1] = temp1 | ( month % 10 );
 
   temp1 = day / 10;
   temp1 <<= 4;
   clock_moon[0] = temp1 | ( day % 10 );
   Lcd_Lunar_Calendar( clock_moon );	//转换后调用显示LCD.H中的显示程序
}

/********************************************************************************
* 名称: void Week_convert( uchar * clock_time )
* 功能: 输入BCD阳历数据；输出BCD星期
* 入口参数: 
* 出口参数:
* 说明: 算法: （ 日期 + 年份 + 所过闰年 + 月校正 ) / 7 的余数就是星期 如果是闰年又不到 3 月份上述之和 要减一天 再
********************************************************************************/
void Week_Convert( bit c, uchar * clock_time )
{
   uchar year, month, day; //定义 年 月 天
   uchar temp;

   clock_time += 3; //指向日
   day = ( * clock_time >> 4 ) * 10 + ( *clock_time & 0x0f ); //BCD转换十进制
   clock_time ++; //指向月
   month = ( * clock_time >> 4 ) * 10 + ( * clock_time & 0x0f );
   clock_time ++; //指向年
   year = ( * clock_time >> 4 ) * 10 + ( * clock_time & 0x0f ); 

   if( c == 0 ) //如果为21世纪,年份数加100
      year += 100;
   temp = year / 4; //所过闰年数只算1900年之后的
   temp = year + temp;
   temp = temp % 0x07; //为节省资源,先进行一次取余,避免数大于0xff,避免使用整型数据
   temp = temp + day + table_week[ month - 1 ];
   if( ( year % 4  == 0 ) && ( month <3  ) )
      temp -=1;
   Lcd_Week( temp % 7 );
}
/**************************************************************************
* 名称: void ershi( uchar * clock_time )
* 功能: 输入BCD的阳历数据， 输出BCD阴历数据( 2000 - 2099 )
* 入口参数:clock_time: 时钟地址
* 出口参数: 无
*****************************************************************************/
void  Ershi( uchar * clock_time )
{
   uchar year, month, day, month_point; //定义 年 月 天
   uchar temp1, temp2, temp3,temp4;
   clock_time += 3; //指向日
   day = ( * clock_time >> 4 ) * 10 + ( *clock_time & 0x0f ); //BCD转换十进制
   clock_time ++; //指向月
   month = ( * clock_time >> 4 ) * 10 + ( * clock_time & 0x0f ); //BCD转换十进制
   clock_time ++; //指向年
   year = ( * clock_time >> 4 ) * 10 + ( * clock_time & 0x0f ); //BCD转换十进制 
   temp1=ershi1_code[(month-1)*2];     //找出本月第一个节气的最小日
   temp2=ershi1_code[(month-1)*2+1];	  //找出本月第二个节气的最小日
	switch(month)
	  {
	    case 1: {if (ershi2_code[year*3]&0x80)  temp1++; if(ershi2_code[year*3]&0x40) temp2++;}  break;
		case 2: {if (ershi2_code[year*3]&0x20)  temp1++; if(temp3&0x10) temp2++;}  break	;
		case 3: {if(ershi2_code[year*3]&0x08)  temp1++;  if(ershi2_code[year*3]&0x04)  temp2++;} break;
		case 4: {if(ershi2_code[year*3]&0x02) temp1++; if(ershi2_code[year*3]&0x01)  temp2++;} break;
		case 5: {if (ershi2_code[year*3+1]&0x80)  temp1++; if(ershi2_code[year*3+1]&0x40) temp2++;}  break;
		case 6: {if (ershi2_code[year*3+1]&	0x20)  temp1++; if(ershi2_code[year*3+1]&0x10) temp2++;}  break	;
		case 7: {if(ershi2_code[year*3+1]&0x08)  temp1++;  if(ershi2_code[year*3+1]&0x04)  temp2++;} break;
		case 8: {if(ershi2_code[year*3+1]&0x02) temp1++; if(ershi2_code[year*3+1]&0x01)  temp2++;} break;
		case 9: {if (ershi2_code[year*3+2]&0x80)  temp1++; if(ershi2_code[year*3+2]&0x40) temp2++;}  break;
		case 10: {if (ershi2_code[year*3+2]&	0x20)  temp1++; if(ershi2_code[year*3+2]&0x10) temp2++;}  break	;
		case 11: {if(ershi2_code[year*3+2]&0x08)  temp1++;  if(ershi2_code[year*3+2]&0x04)  temp2++;} break;
		case 12: {if(ershi2_code[year*3+2]&0x02) temp1++; if(ershi2_code[year*3+2]&0x01)  temp2++;} break;
		 }
	if(day<temp1) { temp4=month*2-2;if(temp4==0) temp4=24;}
	if(temp1<=day&&day<temp2) temp4=month*2-1;
	if(day>=temp2)  temp4=month*2;
    LCD_ERSHI(temp4);
}