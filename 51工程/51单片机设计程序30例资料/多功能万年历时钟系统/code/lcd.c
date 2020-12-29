#define LCD_GLOBAL
#include "lcd.h"
#include "character.h"
/********************************************************************************************
* 函数名称：Delay()
* 功    能：延迟时间=a*1ms
* 入口参数：
* 出口参数：无
*********************************************************************************************/
void Delay(uint a)
{
   uchar  i;
   while(a--)
   for(i=0;i<125;i++);
}
/********************************************************************************************
* 函数名称：Lcd_Display_On()
* 功    能：LCD显示开
* 入口参数：无
* 出口参数：无
*********************************************************************************************/
void Lcd_Display_On()
{  
   port=0x3f;
   rs=0;
   rw=0;
   e=1;
   e=0;  
}
/********************************************************************************************
* 函数名称：Lcd_Display_Off()
* 功    能：LCD显示关
* 入口参数：无
* 出口参数：无
*********************************************************************************************/
void Lcd_Display_Off()
{  
   port=0x3e;
   rs=0;
   rw=0;
   e=1;
   e=0;  
}
/********************************************************************************************
* 函数名称：Lcd_Set_X(uchar x)
* 功    能：LCD设置X坐标
* 入口参数：x 
* 出口参数：无
*********************************************************************************************/
void Lcd_Set_X(uchar x)
{  
   port=0xb8|x;
   rs=0;
   rw=0;
   e=1;
   e=0;  
}
/********************************************************************************************
* 函数名称：Lcd_Set_Y(uchar y)
* 功    能：LCD设置Y坐标
* 入口参数：y
* 出口参数：无
*********************************************************************************************/
void Lcd_Set_Y(uchar y)
{  
   port=0x40|y;
   rs=0;
   rw=0;
   e=1;
   e=0;  
}
/********************************************************************************************
* 函数名称：Lcd_Set_X_Y(uchar x, uchar y )
* 功    能：LCD设置x y坐标
* 入口参数：x y
* 出口参数：无
*********************************************************************************************/
void Lcd_Set_X_Y(uchar x, uchar y)
{  
   
   if( y<64 )
      { cs1=1; cs2=0; Lcd_Set_Y( y ); }
   else
      { cs1=0; cs2=1; Lcd_Set_Y( y-64 );  }
    Lcd_Set_X( x);
}
/********************************************************************************************
* 函数名称：Lcd_Write_Command()
* 功    能：写指令代码
* 入口参数：无
* 出口参数：无
*********************************************************************************************/
void Lcd_Write_Command(uchar temp)
{  
   port=temp;
   rs=0;
   rw=0;
   e=1;
   e=0;  
}
/********************************************************************************************
* 函数名称：Lcd_Write_Byte()
* 功    能：写数据
* 入口参数：无
* 出口参数：无
*********************************************************************************************/
void Lcd_Write_Byte(uchar temp)
{  
   port=temp;
   rs=1;
   rw=0;
   e=1;
   e=0;  
}
/****************************************************************************
*名称:Lcd_Character_16X8( bit bit_flag, uchar x, uchar y, uchar code *point )
*功能:显示16X8字符(字母)         
*入口参数:
*出口参数:
*说明:bit_flag = 1 正常显示  bit_flag = 0 黑白反相显示 
****************************************************************************/
void Lcd_Character_16X8( bit bit_flag, uchar x, uchar y, uchar code *point )
{
   uchar i , j,temp;
   temp=y;
   if( bit_flag )
   {   
      for( i=0; i<2; i++ )
      {
         x+=i;
	     y=temp;
         for( j=0;j<8;j++ )
         {
            Lcd_Set_X_Y( x, y ); y++;
            Lcd_Write_Byte( point[ i*8 + j] );  
         } 
      }
   }
   else
   {
      for( i = 0; i < 2; i++ )
      {
         x += i;
         y = temp;
         for( j = 0; j < 8; j++ )
         {
            Lcd_Set_X_Y( x, y ); y++;
            Lcd_Write_Byte( ~point[ i * 8 + j ] );
         }
      }
   }
}
/****************************************************************************
* 名称：Lcd_Character_16X16( bit bit_flag, uchar x, uchar y, uchar code *point )
* 功能：显示16*16字符（汉字）       
* 入口参数：x y data
* 出口参数：无
*说明:bit_flag = 1 正常显示 bit_flag = 0 黑白反相显示
****************************************************************************/
void Lcd_Character_16X16( bit bit_flag, uchar x, uchar y, uchar code *point )
{
   uchar i,j,temp ;
   temp=y;
   if( bit_flag )
   {
      for( i=0; i<2; i++ )
      {
         x+=i;
	     y=temp;
         for( j=0;j<16;j++ )
         {
            Lcd_Set_X_Y( x, y ); y++;
            Lcd_Write_Byte( point[ i*16 + j] );  
         } 
      }
   }
   else
   {
      for( i = 0; i<2; i++ )
      {
         x += i;
         y = temp;
         for( j = 0; j < 16; j++ )
         {
            Lcd_Set_X_Y( x, y ); y++;
            Lcd_Write_Byte( ~ point[ i * 16 + j ] );
         }
      }
   }
}
/****************************************************************************
* 名称：Lcd_Clear(void)
* 功能：清屏        
* 入口参数：无
* 出口参数：无
****************************************************************************/
void Lcd_Clear()
{
   uchar i,j;
   cs1=1;cs2=1;
   for(i=0;i<8;i++)
   {
      Lcd_Set_X( i );
      Lcd_Set_Y( 0 );
      for(j=0;j<64;j++)
         Lcd_Write_Byte(0x00);
   }
}
/*******************************************************************************************
* 函数名称：Lcd_Initial()
* 功    能：初始化LCD
* 入口参数：无
* 出口参数：无
*********************************************************************************************/
void Lcd_Initial()
{  
   Lcd_Display_Off();
   Lcd_Write_Command(0xb8);     //Page_Add
   Lcd_Write_Command(0x40);     //Col_Add
   Lcd_Write_Command(0xc0);     //Start_Line
   Lcd_Display_On();
   Lcd_Clear();
}

/****************************************************************************
* 名称：Lcd_Time(uchar * clock_time )
* 功能：显示时间       
* 入口参数：无
* 出口参数：无                 
* 说明    : 时间数组 BCD 码形式
****************************************************************************/
void Lcd_Time(uchar * clock_time )	                //显示"hour时min分sec秒"  
{
   uchar i=0;                                     
   i= * clock_time >> 4;
   Lcd_Character_16X8( 1, 2, 80, letter_logo[i]);    //显示   sec的高位
   i= * clock_time & 0x0f;
   Lcd_Character_16X8( 1, 2, 88, letter_logo[i]);    //显示   sec的低位
   Lcd_Character_16X16( 1, 2, 96 , time_logo[2]);    //显示   秒

   clock_time ++;
   i= *  clock_time >> 4;
   Lcd_Character_16X8( 1, 2, 48, letter_logo[i]);    //显示   min的高位
   i= * clock_time & 0x0f;
   Lcd_Character_16X8( 1, 2, 56, letter_logo[i]);    //显示   min的低位
   Lcd_Character_16X16( 1, 2, 64 , time_logo[1]);    //显示   分

   clock_time ++;
   i= * clock_time >> 4;
   Lcd_Character_16X8( 1, 2, 16 , letter_logo[i]);    //显示   hour的高位
   i= * clock_time & 0x0f;
   Lcd_Character_16X8( 1, 2, 24 , letter_logo[i]);    //显示   hour的低位
   Lcd_Character_16X16( 1, 2, 32 , time_logo[0]);     //显示   分         
}
/****************************************************************************
* 名称：Lcd_Data(uchar * clock_time )
* 功能：显示日期       
* 入口参数：无
* 出口参数：无                 
* 说明    : 时间数组 BCD 码形式
****************************************************************************/
void Lcd_Data(uchar * clock_time )
{
   uchar i=0;
   clock_time += 3;

   //显示   "year 年 month 月 day 日"                                                  
   i= * clock_time >> 4;
   Lcd_Character_16X8( 1, 0, 80, letter_logo[i]);  //显示   day的高位
   i= * clock_time & 0x0f;
   Lcd_Character_16X8( 1, 0, 88, letter_logo[i]);  //显示   day的低位  
   Lcd_Character_16X16( 1, 0, 96, data_logo[2]); //显示   日
   
   clock_time ++;
   i= * clock_time >> 4 ;
   Lcd_Character_16X8( 1, 0, 48, letter_logo[i]);  //显示   month的高位
   i= * clock_time & 0x0f;
   Lcd_Character_16X8( 1, 0, 56, letter_logo[i]); //显示   month的低位
   Lcd_Character_16X16( 1, 0, 64, data_logo[1]);   //显示   月
   
   clock_time ++ ;   
   i= * clock_time >>  4;
   Lcd_Character_16X8( 1, 0, 16 , letter_logo[i]); //显示   year的高位
   i= * clock_time & 0x0f;
   Lcd_Character_16X8( 1, 0, 24 , letter_logo[i]); //显示   year的低位
   Lcd_Character_16X16( 1, 0, 32, data_logo[0]);   //显示   年
}
/****************************************************************************
* 名称：Lcd_Week(uchar week)
* 功能：显示星期      
* 入口参数：无
* 出口参数：无                 
****************************************************************************/
void Lcd_Week( uchar week )
{  
   Lcd_Character_16X16( 1, 6, 16,  week_logo[7] ); //星
   Lcd_Character_16X16( 1, 6, 32, week_logo[8] ); //期
   Lcd_Character_16X16( 1, 6, 48, week_logo[  week & 0x0f ] );
}
/******************************************************************************
* 函数名称: Lcd_Clock( uchar *clock_time )
* 功能: 显示时钟
* 入口参数: 时钟地址
* 出口参数: 无
********************************************************************************/
void Lcd_Clock( uchar * clock_time )
{
   Lcd_Data( clock_time ); //显示日期
   Lcd_Time( clock_time ); //显示时间
}
/******************************************************************************
* 名称: void Lcd_Lunar_Calendar( uchar * lunch_calendar )
* 功能: 显示农历
* 入口参数: 农力指针
* 出口参数: 无
*******************************************************************************/
void Lcd_Lunar_Calendar( uchar * lunar_canlendar )
{
   uchar i;
   //农历
   Lcd_Character_16X16( 1, 4, 16, lunar_calendar_logo[0] );
   Lcd_Character_16X16( 1, 4, 32, lunar_calendar_logo[1] );
   //year-mongth-day
   i= * lunar_canlendar >>  4;
   Lcd_Character_16X8( 1, 4, 96, letter_logo[i] ); //农历天的高位
   i= * lunar_canlendar & 0x0f;
   Lcd_Character_16X8( 1, 4, 104, letter_logo[i] ); //农历天的低位
   Lcd_Character_16X8( 1, 4, 88, letter_logo[11] ); //-

   lunar_canlendar ++;
   i= * lunar_canlendar >>  4;
   Lcd_Character_16X8( 1, 4, 72, letter_logo[i] ); //农历月的高位
   i= * lunar_canlendar & 0x0f;
   Lcd_Character_16X8( 1, 4, 80, letter_logo[i] ); //农历月的低位
   Lcd_Character_16X8( 1, 4, 64, letter_logo[11] ); //-

   lunar_canlendar ++;
   i= * lunar_canlendar >>  4;
   Lcd_Character_16X8( 1, 4, 48, letter_logo[i] ); //农历年的高位
   i= * lunar_canlendar & 0x0f;
   Lcd_Character_16X8( 1, 4, 56, letter_logo[i] ); //农历年的地位
   
}
/*******************************************************************************
* 名称: Lcd_Temperature( uchar * temperture )
* 功能: 显示温度
* 入口参数: 温度
* 出口参数: 无
*********************************************************************************/
void Lcd_Temperture( uchar * temperature )
{
   uchar temp;
   switch( * temperature & 0x0f )                    //查表 精确到 0.1  °C
   {
      case 0x00: temp = 0; break;
      case 0x01: temp = 0; break;
      case 0x02: temp = 1; break;
      case 0x03: temp = 2; break;
      case 0x04: temp = 2; break;
      case 0x05: temp = 3; break;
      case 0x06: temp = 4; break;
      case 0x07: temp = 4; break;
      case 0x08: temp = 5; break;
      case 0x09: temp = 6; break;
      case 0x0a: temp = 6; break;
      case 0x0b: temp = 7; break;
      case 0x0c: temp = 8; break;
      case 0x0d: temp = 8; break;
      case 0x0e: temp = 9; break;
      case 0x0f: temp = 9; break;
      default:  break;
   } 
   Lcd_Character_16X8( 1, 6, 104, temperture_logo[2] );    //   C 
   Lcd_Character_16X8( 1, 6, 96, temperture_logo[1] );    //   ° 
   Lcd_Character_16X8( 1, 6, 88, letter_logo[temp] );  //  小数位
   Lcd_Character_16X8( 1, 6, 80,  temperture_logo[0] );     //  .
   temp = ( * temperature ) >> 4;
   temperature ++;
   temp |= ( * temperature ) << 4;
   Lcd_Character_16X8( 1, 6, 72, letter_logo[ temp % 10 ] ); //个位
   Lcd_Character_16X8( 1, 6, 64, letter_logo[ temp /10 ] );  //十位


   
   if( temp >= 30 )
      Lcd_Character_16X16( 1, 6, 112, sensor_inducator_logo[0] );  //大雨30度显示图形
   else
   {
      if( temp < 20 )
	     Lcd_Character_16X16( 1, 6, 112, sensor_inducator_logo[2] );  //小于20度显示图形
	  else 
	     Lcd_Character_16X16( 1, 6, 112, sensor_inducator_logo[1] );  //大于20度小于30度显示图形
   }
}

/***************************************************************************
*名称    ：Lcd_Set_Clock( uchar bit_flag, uchar *point )
*功能    ：显示调整的时间
*入口参数：指针
*出口参数：无
*说明    ：
****************************************************************************/
void Lcd_Set_Clock( uchar temp, uchar *point )
{
   bit year_flag = 1;
   bit month_flag = 1;
   bit day_flag = 1;
   bit hour_flag =1;
   bit minute_flag = 1;
   bit second_flag = 1;
   uchar i;
   if( temp == 1 ) //滚动到 second
     second_flag = 0;
   if( temp == 2 ) //滚动到 minute
      minute_flag = 0;
   if( temp == 3 ) //滚动到 hour
      hour_flag = 0;
   if( temp == 4 ) //滚动到 day
      day_flag = 0;
   if( temp == 5 ) //滚动到 month
      month_flag = 0;
   if( temp == 6 ) //滚动到 year
      year_flag = 0;
   //日期
   Lcd_Character_16X16( 1, 2, 0 , data_time_logo[0] );
   Lcd_Character_16X16( 1, 2, 16, data_time_logo[1] );
   point += 5;    //指向年
   //year
   i = *point >> 4;  
   Lcd_Character_16X8( year_flag, 2, 40, letter_logo[i] );
   i = *point & 0x0f;
   Lcd_Character_16X8( year_flag, 2, 48, letter_logo[i] );
   //-
   Lcd_Character_16X8( 1, 2, 56, letter_logo[11] );
   point --;   //指向月
   //month
   i = *point >>4;
   Lcd_Character_16X8( month_flag, 2, 64, letter_logo[i] );
   i = *point & 0x0f;
   Lcd_Character_16X8( month_flag, 2, 72, letter_logo[i] );      
   //-
   Lcd_Character_16X8( 1, 2, 80, letter_logo[11] );
   point --;   //指向日
   //day   
   i = *point >>4;
   Lcd_Character_16X8( day_flag, 2, 88, letter_logo[i] );
   i = *point & 0x0f;
   Lcd_Character_16X8( day_flag, 2, 96, letter_logo[i] );
   //时间
   Lcd_Character_16X16( 1, 4, 0, data_time_logo[2] );
   Lcd_Character_16X16( 1, 4, 16, data_time_logo[3] );
   point -- ; //指向时
   //hour
   i = *point >>4;
   Lcd_Character_16X8( hour_flag, 4, 40, letter_logo[i] );
   i = *point & 0x0f;
   Lcd_Character_16X8( hour_flag, 4, 48, letter_logo[i] );   
   //:
   Lcd_Character_16X8( 1, 4, 56, letter_logo[10] );
   point -- ;  //指向分
   //minnute
   i = *point >>4;
   Lcd_Character_16X8( minute_flag, 4, 64, letter_logo[i] );
   i = *point & 0xff;
   Lcd_Character_16X8( minute_flag, 4, 72, letter_logo[i] );
   //:
   Lcd_Character_16X8( 1, 4, 80, letter_logo[10] );
   point --;   //指向秒
   //second
   i = *point >> 4;
   Lcd_Character_16X8( second_flag, 4, 88, letter_logo[i] );
   i = * point & 0x0f;
   Lcd_Character_16X8( second_flag, 4, 96, letter_logo[i] );
}
/**************************************************************************************
* 名称: Lcd_Function( uchar temp )
* 功能: 滚动显示 时间设置 闹钟设置
* 入口参数: 滚动位置
* 出口参数: 无
**************************************************************************************/
void Lcd_Function( uchar temp )
{
   bit time_flag = 1;
   bit alarm_flag = 1;
   if( temp == 2 ) //滚动到 时间设置
      time_flag = 0;
   if( temp == 1 ) //滚动到 闹钟设置
      alarm_flag = 0;
   //时间设置
   Lcd_Character_16X16( time_flag, 0, 0, function_logo[0] );
   Lcd_Character_16X16( time_flag, 0, 16, function_logo[1] );
   Lcd_Character_16X16( time_flag, 0, 32, function_logo[2] );
   Lcd_Character_16X16( time_flag, 0, 48, function_logo[3] );
   //闹钟设置
   Lcd_Character_16X16( alarm_flag, 2, 0, function_logo[4] );
   Lcd_Character_16X16( alarm_flag, 2, 16, function_logo[5] );
   Lcd_Character_16X16( alarm_flag, 2, 32, function_logo[6] );
   Lcd_Character_16X16( alarm_flag, 2, 48, function_logo[7] );
}
/************************************************************************************
* 名称: Lcd_Alarm( uchar * alarm_time )
* 功能: 闹钟调整画面显示
* 入口参数: 闹钟地址
* 出口参数: 无
************************************************************************************/
void Lcd_Alarm( uchar temp, uchar * alarm_time )
{
   uchar i;
   bit hour_flag = 1;
   bit minute_flag = 1;
   if( temp == 1 )
      minute_flag = 0;
   if( temp == 2 )
      hour_flag = 0;
   Lcd_Character_16X16( 1, 0, 0, alarm_logo[0] ); //显示闹钟标志
   // 小时:分钟
   Lcd_Character_16X16( 1, 0, 16, alarm_logo[1] );
   Lcd_Character_16X16( 1, 0, 32, alarm_logo[2] );
   Lcd_Character_16X8( 1, 0, 48, letter_logo[10] );
   Lcd_Character_16X16( 1, 0, 56, alarm_logo[3] );
   Lcd_Character_16X16( 1, 0, 72, alarm_logo[4] );


   i = ( *  ( alarm_time + 1 ) ) / 10;
   Lcd_Character_16X8( hour_flag, 2, 32, letter_logo[i] ); //显示时的高位 
   i = ( * ( alarm_time + 1 )  ) % 10;
   Lcd_Character_16X8( hour_flag, 2, 40, letter_logo[i] ); //显示时的低位
   Lcd_Character_16X8( 1, 2, 48, letter_logo[10] ); //:

   i = ( *  ( alarm_time ) ) / 10;
   Lcd_Character_16X8( minute_flag, 2, 56, letter_logo[i] ); //显示分的高位 
   i = ( * ( alarm_time  ) ) % 10;
   Lcd_Character_16X8( minute_flag, 2, 64, letter_logo[i] ); //显示分的低位
}
 void LCD_ERSHI( uchar temp )
 {
    switch(temp)
	  {
	    case  1 :{ 
		           Lcd_Character_16X16( 1, 6, 80, ershi_logo[0] );   //小寒
				   Lcd_Character_16X16( 1, 6, 96, ershi_logo[1] );
				   }
				  break;
		case 2:  {
		             Lcd_Character_16X16( 1, 6, 80, ershi_logo[2] ); //大寒 
				     Lcd_Character_16X16( 1, 6, 96, ershi_logo[1] );
				  }
			    	break;
		case 3:  { 
		             Lcd_Character_16X16( 1, 6, 80, ershi_logo[3] );   //立春
				     Lcd_Character_16X16( 1, 6, 96, ershi_logo[4] );
				  }
				    break;
		case 4:  { Lcd_Character_16X16( 1, 6, 80, ershi_logo[5] );     //雨水
				     Lcd_Character_16X16( 1, 6, 96, ershi_logo[6] );
				  }
				    break;
		case 5:   { Lcd_Character_16X16( 1, 6, 80, ershi_logo[7] );  	//惊蛰
				     Lcd_Character_16X16( 1, 6, 96, ershi_logo[8] );
				  }
				    break;
		case 6:  {  Lcd_Character_16X16( 1, 6, 80, ershi_logo[4] );  	//春分
				     Lcd_Character_16X16( 1, 6, 96, ershi_logo[9] );
				  }
				    break;
		case 7: {   Lcd_Character_16X16( 1, 6, 80, ershi_logo[10] );  	 //清明
				     Lcd_Character_16X16( 1, 6, 96, ershi_logo[11] );
				  }
				    break;
		 case 8: {  Lcd_Character_16X16( 1, 6, 80, ershi_logo[12] );  	//谷雨
				     Lcd_Character_16X16( 1, 6, 96, ershi_logo[5] );
				  }
				    break;
		 case 9:  {	  Lcd_Character_16X16( 1, 6, 80, ershi_logo[3] );  //立夏
				     Lcd_Character_16X16( 1, 6, 96, ershi_logo[13] );
				  }
				    break;
		 case 10: { Lcd_Character_16X16( 1, 6, 80, ershi_logo[0] );    //小满
				     Lcd_Character_16X16( 1, 6, 96, ershi_logo[14] );
				  }
				    break;
		 case 11: {	 Lcd_Character_16X16( 1, 6, 80, ershi_logo[15] );  //芒种
				     Lcd_Character_16X16( 1, 6, 96, ershi_logo[16] );
				  }
				    break;
		 case 12: {	 Lcd_Character_16X16( 1, 6, 80, ershi_logo[13] );  //夏至
				     Lcd_Character_16X16( 1, 6, 96, ershi_logo[17] );
				  }
				    break;
		 case 13: {	  Lcd_Character_16X16( 1, 6, 80, ershi_logo[0] );  //小暑
				     Lcd_Character_16X16( 1, 6, 96, ershi_logo[18] );
				  }
				    break;
		 case 14: { Lcd_Character_16X16( 1, 6, 80, ershi_logo[2] );    //大暑
				     Lcd_Character_16X16( 1, 6, 96, ershi_logo[18] );
				  }
				    break;
		 case 15: {	 Lcd_Character_16X16( 1, 6, 80, ershi_logo[3] );   //立秋
				     Lcd_Character_16X16( 1, 6, 96, ershi_logo[19] );
				  }
				    break;
		case 16:  {	  Lcd_Character_16X16( 1, 6, 80, ershi_logo[20] );  //处暑
				     Lcd_Character_16X16( 1, 6, 96, ershi_logo[18] );
				  }
				    break;
		case 17: { Lcd_Character_16X16( 1, 6, 80, ershi_logo[21] );  	//白露

				     Lcd_Character_16X16( 1, 6, 96, ershi_logo[22] );
				  }
				    break;
	   case 18: {  Lcd_Character_16X16( 1, 6, 80, ershi_logo[19] );  	//秋分
				     Lcd_Character_16X16( 1, 6, 96, ershi_logo[9] );
				  }
				    break;
	   case 19: {   Lcd_Character_16X16( 1, 6, 80, ershi_logo[1] );    //寒露
				     Lcd_Character_16X16( 1, 6, 96, ershi_logo[22] );
				  }
				    break;
	   case 20: {  Lcd_Character_16X16( 1, 6, 80, ershi_logo[23] );    //霜降
				     Lcd_Character_16X16( 1, 6, 96, ershi_logo[24] );
				  }
				    break;
	   case 21: {   Lcd_Character_16X16( 1, 6, 80, ershi_logo[3] );  	//立冬
				     Lcd_Character_16X16( 1, 6, 96, ershi_logo[25] );
				  }
				    break;
	   case 22: {   Lcd_Character_16X16( 1, 6, 80, ershi_logo[0] );  	//小雪
				     Lcd_Character_16X16( 1, 6, 96, ershi_logo[26] );
				  }
				    break;
	   case 23: {   Lcd_Character_16X16( 1, 6, 80, ershi_logo[2] );    //大雪
				     Lcd_Character_16X16( 1, 6, 96, ershi_logo[26] );
				  }
				    break;
	   case 24: {   Lcd_Character_16X16( 1, 6, 80, ershi_logo[25] );  	//冬至
				     Lcd_Character_16X16( 1, 6, 96, ershi_logo[17] );
				  }
				    break;
	   default:
		  break;
		 }
}