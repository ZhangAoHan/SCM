#define LCD_GLOBAL
#include "lcd.h"
#include "character.h"
/********************************************************************************************
* �������ƣ�Delay()
* ��    �ܣ��ӳ�ʱ��=a*1ms
* ��ڲ�����
* ���ڲ�������
*********************************************************************************************/
void Delay(uint a)
{
   uchar  i;
   while(a--)
   for(i=0;i<125;i++);
}
/********************************************************************************************
* �������ƣ�Lcd_Display_On()
* ��    �ܣ�LCD��ʾ��
* ��ڲ�������
* ���ڲ�������
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
* �������ƣ�Lcd_Display_Off()
* ��    �ܣ�LCD��ʾ��
* ��ڲ�������
* ���ڲ�������
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
* �������ƣ�Lcd_Set_X(uchar x)
* ��    �ܣ�LCD����X����
* ��ڲ�����x 
* ���ڲ�������
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
* �������ƣ�Lcd_Set_Y(uchar y)
* ��    �ܣ�LCD����Y����
* ��ڲ�����y
* ���ڲ�������
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
* �������ƣ�Lcd_Set_X_Y(uchar x, uchar y )
* ��    �ܣ�LCD����x y����
* ��ڲ�����x y
* ���ڲ�������
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
* �������ƣ�Lcd_Write_Command()
* ��    �ܣ�дָ�����
* ��ڲ�������
* ���ڲ�������
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
* �������ƣ�Lcd_Write_Byte()
* ��    �ܣ�д����
* ��ڲ�������
* ���ڲ�������
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
*����:Lcd_Character_16X8( bit bit_flag, uchar x, uchar y, uchar code *point )
*����:��ʾ16X8�ַ�(��ĸ)         
*��ڲ���:
*���ڲ���:
*˵��:bit_flag = 1 ������ʾ  bit_flag = 0 �ڰ׷�����ʾ 
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
* ���ƣ�Lcd_Character_16X16( bit bit_flag, uchar x, uchar y, uchar code *point )
* ���ܣ���ʾ16*16�ַ������֣�       
* ��ڲ�����x y data
* ���ڲ�������
*˵��:bit_flag = 1 ������ʾ bit_flag = 0 �ڰ׷�����ʾ
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
* ���ƣ�Lcd_Clear(void)
* ���ܣ�����        
* ��ڲ�������
* ���ڲ�������
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
* �������ƣ�Lcd_Initial()
* ��    �ܣ���ʼ��LCD
* ��ڲ�������
* ���ڲ�������
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
* ���ƣ�Lcd_Time(uchar * clock_time )
* ���ܣ���ʾʱ��       
* ��ڲ�������
* ���ڲ�������                 
* ˵��    : ʱ������ BCD ����ʽ
****************************************************************************/
void Lcd_Time(uchar * clock_time )	                //��ʾ"hourʱmin��sec��"  
{
   uchar i=0;                                     
   i= * clock_time >> 4;
   Lcd_Character_16X8( 1, 2, 80, letter_logo[i]);    //��ʾ   sec�ĸ�λ
   i= * clock_time & 0x0f;
   Lcd_Character_16X8( 1, 2, 88, letter_logo[i]);    //��ʾ   sec�ĵ�λ
   Lcd_Character_16X16( 1, 2, 96 , time_logo[2]);    //��ʾ   ��

   clock_time ++;
   i= *  clock_time >> 4;
   Lcd_Character_16X8( 1, 2, 48, letter_logo[i]);    //��ʾ   min�ĸ�λ
   i= * clock_time & 0x0f;
   Lcd_Character_16X8( 1, 2, 56, letter_logo[i]);    //��ʾ   min�ĵ�λ
   Lcd_Character_16X16( 1, 2, 64 , time_logo[1]);    //��ʾ   ��

   clock_time ++;
   i= * clock_time >> 4;
   Lcd_Character_16X8( 1, 2, 16 , letter_logo[i]);    //��ʾ   hour�ĸ�λ
   i= * clock_time & 0x0f;
   Lcd_Character_16X8( 1, 2, 24 , letter_logo[i]);    //��ʾ   hour�ĵ�λ
   Lcd_Character_16X16( 1, 2, 32 , time_logo[0]);     //��ʾ   ��         
}
/****************************************************************************
* ���ƣ�Lcd_Data(uchar * clock_time )
* ���ܣ���ʾ����       
* ��ڲ�������
* ���ڲ�������                 
* ˵��    : ʱ������ BCD ����ʽ
****************************************************************************/
void Lcd_Data(uchar * clock_time )
{
   uchar i=0;
   clock_time += 3;

   //��ʾ   "year �� month �� day ��"                                                  
   i= * clock_time >> 4;
   Lcd_Character_16X8( 1, 0, 80, letter_logo[i]);  //��ʾ   day�ĸ�λ
   i= * clock_time & 0x0f;
   Lcd_Character_16X8( 1, 0, 88, letter_logo[i]);  //��ʾ   day�ĵ�λ  
   Lcd_Character_16X16( 1, 0, 96, data_logo[2]); //��ʾ   ��
   
   clock_time ++;
   i= * clock_time >> 4 ;
   Lcd_Character_16X8( 1, 0, 48, letter_logo[i]);  //��ʾ   month�ĸ�λ
   i= * clock_time & 0x0f;
   Lcd_Character_16X8( 1, 0, 56, letter_logo[i]); //��ʾ   month�ĵ�λ
   Lcd_Character_16X16( 1, 0, 64, data_logo[1]);   //��ʾ   ��
   
   clock_time ++ ;   
   i= * clock_time >>  4;
   Lcd_Character_16X8( 1, 0, 16 , letter_logo[i]); //��ʾ   year�ĸ�λ
   i= * clock_time & 0x0f;
   Lcd_Character_16X8( 1, 0, 24 , letter_logo[i]); //��ʾ   year�ĵ�λ
   Lcd_Character_16X16( 1, 0, 32, data_logo[0]);   //��ʾ   ��
}
/****************************************************************************
* ���ƣ�Lcd_Week(uchar week)
* ���ܣ���ʾ����      
* ��ڲ�������
* ���ڲ�������                 
****************************************************************************/
void Lcd_Week( uchar week )
{  
   Lcd_Character_16X16( 1, 6, 16,  week_logo[7] ); //��
   Lcd_Character_16X16( 1, 6, 32, week_logo[8] ); //��
   Lcd_Character_16X16( 1, 6, 48, week_logo[  week & 0x0f ] );
}
/******************************************************************************
* ��������: Lcd_Clock( uchar *clock_time )
* ����: ��ʾʱ��
* ��ڲ���: ʱ�ӵ�ַ
* ���ڲ���: ��
********************************************************************************/
void Lcd_Clock( uchar * clock_time )
{
   Lcd_Data( clock_time ); //��ʾ����
   Lcd_Time( clock_time ); //��ʾʱ��
}
/******************************************************************************
* ����: void Lcd_Lunar_Calendar( uchar * lunch_calendar )
* ����: ��ʾũ��
* ��ڲ���: ũ��ָ��
* ���ڲ���: ��
*******************************************************************************/
void Lcd_Lunar_Calendar( uchar * lunar_canlendar )
{
   uchar i;
   //ũ��
   Lcd_Character_16X16( 1, 4, 16, lunar_calendar_logo[0] );
   Lcd_Character_16X16( 1, 4, 32, lunar_calendar_logo[1] );
   //year-mongth-day
   i= * lunar_canlendar >>  4;
   Lcd_Character_16X8( 1, 4, 96, letter_logo[i] ); //ũ����ĸ�λ
   i= * lunar_canlendar & 0x0f;
   Lcd_Character_16X8( 1, 4, 104, letter_logo[i] ); //ũ����ĵ�λ
   Lcd_Character_16X8( 1, 4, 88, letter_logo[11] ); //-

   lunar_canlendar ++;
   i= * lunar_canlendar >>  4;
   Lcd_Character_16X8( 1, 4, 72, letter_logo[i] ); //ũ���µĸ�λ
   i= * lunar_canlendar & 0x0f;
   Lcd_Character_16X8( 1, 4, 80, letter_logo[i] ); //ũ���µĵ�λ
   Lcd_Character_16X8( 1, 4, 64, letter_logo[11] ); //-

   lunar_canlendar ++;
   i= * lunar_canlendar >>  4;
   Lcd_Character_16X8( 1, 4, 48, letter_logo[i] ); //ũ����ĸ�λ
   i= * lunar_canlendar & 0x0f;
   Lcd_Character_16X8( 1, 4, 56, letter_logo[i] ); //ũ����ĵ�λ
   
}
/*******************************************************************************
* ����: Lcd_Temperature( uchar * temperture )
* ����: ��ʾ�¶�
* ��ڲ���: �¶�
* ���ڲ���: ��
*********************************************************************************/
void Lcd_Temperture( uchar * temperature )
{
   uchar temp;
   switch( * temperature & 0x0f )                    //��� ��ȷ�� 0.1  ��C
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
   Lcd_Character_16X8( 1, 6, 96, temperture_logo[1] );    //   �� 
   Lcd_Character_16X8( 1, 6, 88, letter_logo[temp] );  //  С��λ
   Lcd_Character_16X8( 1, 6, 80,  temperture_logo[0] );     //  .
   temp = ( * temperature ) >> 4;
   temperature ++;
   temp |= ( * temperature ) << 4;
   Lcd_Character_16X8( 1, 6, 72, letter_logo[ temp % 10 ] ); //��λ
   Lcd_Character_16X8( 1, 6, 64, letter_logo[ temp /10 ] );  //ʮλ


   
   if( temp >= 30 )
      Lcd_Character_16X16( 1, 6, 112, sensor_inducator_logo[0] );  //����30����ʾͼ��
   else
   {
      if( temp < 20 )
	     Lcd_Character_16X16( 1, 6, 112, sensor_inducator_logo[2] );  //С��20����ʾͼ��
	  else 
	     Lcd_Character_16X16( 1, 6, 112, sensor_inducator_logo[1] );  //����20��С��30����ʾͼ��
   }
}

/***************************************************************************
*����    ��Lcd_Set_Clock( uchar bit_flag, uchar *point )
*����    ����ʾ������ʱ��
*��ڲ�����ָ��
*���ڲ�������
*˵��    ��
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
   if( temp == 1 ) //������ second
     second_flag = 0;
   if( temp == 2 ) //������ minute
      minute_flag = 0;
   if( temp == 3 ) //������ hour
      hour_flag = 0;
   if( temp == 4 ) //������ day
      day_flag = 0;
   if( temp == 5 ) //������ month
      month_flag = 0;
   if( temp == 6 ) //������ year
      year_flag = 0;
   //����
   Lcd_Character_16X16( 1, 2, 0 , data_time_logo[0] );
   Lcd_Character_16X16( 1, 2, 16, data_time_logo[1] );
   point += 5;    //ָ����
   //year
   i = *point >> 4;  
   Lcd_Character_16X8( year_flag, 2, 40, letter_logo[i] );
   i = *point & 0x0f;
   Lcd_Character_16X8( year_flag, 2, 48, letter_logo[i] );
   //-
   Lcd_Character_16X8( 1, 2, 56, letter_logo[11] );
   point --;   //ָ����
   //month
   i = *point >>4;
   Lcd_Character_16X8( month_flag, 2, 64, letter_logo[i] );
   i = *point & 0x0f;
   Lcd_Character_16X8( month_flag, 2, 72, letter_logo[i] );      
   //-
   Lcd_Character_16X8( 1, 2, 80, letter_logo[11] );
   point --;   //ָ����
   //day   
   i = *point >>4;
   Lcd_Character_16X8( day_flag, 2, 88, letter_logo[i] );
   i = *point & 0x0f;
   Lcd_Character_16X8( day_flag, 2, 96, letter_logo[i] );
   //ʱ��
   Lcd_Character_16X16( 1, 4, 0, data_time_logo[2] );
   Lcd_Character_16X16( 1, 4, 16, data_time_logo[3] );
   point -- ; //ָ��ʱ
   //hour
   i = *point >>4;
   Lcd_Character_16X8( hour_flag, 4, 40, letter_logo[i] );
   i = *point & 0x0f;
   Lcd_Character_16X8( hour_flag, 4, 48, letter_logo[i] );   
   //:
   Lcd_Character_16X8( 1, 4, 56, letter_logo[10] );
   point -- ;  //ָ���
   //minnute
   i = *point >>4;
   Lcd_Character_16X8( minute_flag, 4, 64, letter_logo[i] );
   i = *point & 0xff;
   Lcd_Character_16X8( minute_flag, 4, 72, letter_logo[i] );
   //:
   Lcd_Character_16X8( 1, 4, 80, letter_logo[10] );
   point --;   //ָ����
   //second
   i = *point >> 4;
   Lcd_Character_16X8( second_flag, 4, 88, letter_logo[i] );
   i = * point & 0x0f;
   Lcd_Character_16X8( second_flag, 4, 96, letter_logo[i] );
}
/**************************************************************************************
* ����: Lcd_Function( uchar temp )
* ����: ������ʾ ʱ������ ��������
* ��ڲ���: ����λ��
* ���ڲ���: ��
**************************************************************************************/
void Lcd_Function( uchar temp )
{
   bit time_flag = 1;
   bit alarm_flag = 1;
   if( temp == 2 ) //������ ʱ������
      time_flag = 0;
   if( temp == 1 ) //������ ��������
      alarm_flag = 0;
   //ʱ������
   Lcd_Character_16X16( time_flag, 0, 0, function_logo[0] );
   Lcd_Character_16X16( time_flag, 0, 16, function_logo[1] );
   Lcd_Character_16X16( time_flag, 0, 32, function_logo[2] );
   Lcd_Character_16X16( time_flag, 0, 48, function_logo[3] );
   //��������
   Lcd_Character_16X16( alarm_flag, 2, 0, function_logo[4] );
   Lcd_Character_16X16( alarm_flag, 2, 16, function_logo[5] );
   Lcd_Character_16X16( alarm_flag, 2, 32, function_logo[6] );
   Lcd_Character_16X16( alarm_flag, 2, 48, function_logo[7] );
}
/************************************************************************************
* ����: Lcd_Alarm( uchar * alarm_time )
* ����: ���ӵ���������ʾ
* ��ڲ���: ���ӵ�ַ
* ���ڲ���: ��
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
   Lcd_Character_16X16( 1, 0, 0, alarm_logo[0] ); //��ʾ���ӱ�־
   // Сʱ:����
   Lcd_Character_16X16( 1, 0, 16, alarm_logo[1] );
   Lcd_Character_16X16( 1, 0, 32, alarm_logo[2] );
   Lcd_Character_16X8( 1, 0, 48, letter_logo[10] );
   Lcd_Character_16X16( 1, 0, 56, alarm_logo[3] );
   Lcd_Character_16X16( 1, 0, 72, alarm_logo[4] );


   i = ( *  ( alarm_time + 1 ) ) / 10;
   Lcd_Character_16X8( hour_flag, 2, 32, letter_logo[i] ); //��ʾʱ�ĸ�λ 
   i = ( * ( alarm_time + 1 )  ) % 10;
   Lcd_Character_16X8( hour_flag, 2, 40, letter_logo[i] ); //��ʾʱ�ĵ�λ
   Lcd_Character_16X8( 1, 2, 48, letter_logo[10] ); //:

   i = ( *  ( alarm_time ) ) / 10;
   Lcd_Character_16X8( minute_flag, 2, 56, letter_logo[i] ); //��ʾ�ֵĸ�λ 
   i = ( * ( alarm_time  ) ) % 10;
   Lcd_Character_16X8( minute_flag, 2, 64, letter_logo[i] ); //��ʾ�ֵĵ�λ
}
 void LCD_ERSHI( uchar temp )
 {
    switch(temp)
	  {
	    case  1 :{ 
		           Lcd_Character_16X16( 1, 6, 80, ershi_logo[0] );   //С��
				   Lcd_Character_16X16( 1, 6, 96, ershi_logo[1] );
				   }
				  break;
		case 2:  {
		             Lcd_Character_16X16( 1, 6, 80, ershi_logo[2] ); //�� 
				     Lcd_Character_16X16( 1, 6, 96, ershi_logo[1] );
				  }
			    	break;
		case 3:  { 
		             Lcd_Character_16X16( 1, 6, 80, ershi_logo[3] );   //����
				     Lcd_Character_16X16( 1, 6, 96, ershi_logo[4] );
				  }
				    break;
		case 4:  { Lcd_Character_16X16( 1, 6, 80, ershi_logo[5] );     //��ˮ
				     Lcd_Character_16X16( 1, 6, 96, ershi_logo[6] );
				  }
				    break;
		case 5:   { Lcd_Character_16X16( 1, 6, 80, ershi_logo[7] );  	//����
				     Lcd_Character_16X16( 1, 6, 96, ershi_logo[8] );
				  }
				    break;
		case 6:  {  Lcd_Character_16X16( 1, 6, 80, ershi_logo[4] );  	//����
				     Lcd_Character_16X16( 1, 6, 96, ershi_logo[9] );
				  }
				    break;
		case 7: {   Lcd_Character_16X16( 1, 6, 80, ershi_logo[10] );  	 //����
				     Lcd_Character_16X16( 1, 6, 96, ershi_logo[11] );
				  }
				    break;
		 case 8: {  Lcd_Character_16X16( 1, 6, 80, ershi_logo[12] );  	//����
				     Lcd_Character_16X16( 1, 6, 96, ershi_logo[5] );
				  }
				    break;
		 case 9:  {	  Lcd_Character_16X16( 1, 6, 80, ershi_logo[3] );  //����
				     Lcd_Character_16X16( 1, 6, 96, ershi_logo[13] );
				  }
				    break;
		 case 10: { Lcd_Character_16X16( 1, 6, 80, ershi_logo[0] );    //С��
				     Lcd_Character_16X16( 1, 6, 96, ershi_logo[14] );
				  }
				    break;
		 case 11: {	 Lcd_Character_16X16( 1, 6, 80, ershi_logo[15] );  //â��
				     Lcd_Character_16X16( 1, 6, 96, ershi_logo[16] );
				  }
				    break;
		 case 12: {	 Lcd_Character_16X16( 1, 6, 80, ershi_logo[13] );  //����
				     Lcd_Character_16X16( 1, 6, 96, ershi_logo[17] );
				  }
				    break;
		 case 13: {	  Lcd_Character_16X16( 1, 6, 80, ershi_logo[0] );  //С��
				     Lcd_Character_16X16( 1, 6, 96, ershi_logo[18] );
				  }
				    break;
		 case 14: { Lcd_Character_16X16( 1, 6, 80, ershi_logo[2] );    //����
				     Lcd_Character_16X16( 1, 6, 96, ershi_logo[18] );
				  }
				    break;
		 case 15: {	 Lcd_Character_16X16( 1, 6, 80, ershi_logo[3] );   //����
				     Lcd_Character_16X16( 1, 6, 96, ershi_logo[19] );
				  }
				    break;
		case 16:  {	  Lcd_Character_16X16( 1, 6, 80, ershi_logo[20] );  //����
				     Lcd_Character_16X16( 1, 6, 96, ershi_logo[18] );
				  }
				    break;
		case 17: { Lcd_Character_16X16( 1, 6, 80, ershi_logo[21] );  	//��¶

				     Lcd_Character_16X16( 1, 6, 96, ershi_logo[22] );
				  }
				    break;
	   case 18: {  Lcd_Character_16X16( 1, 6, 80, ershi_logo[19] );  	//���
				     Lcd_Character_16X16( 1, 6, 96, ershi_logo[9] );
				  }
				    break;
	   case 19: {   Lcd_Character_16X16( 1, 6, 80, ershi_logo[1] );    //��¶
				     Lcd_Character_16X16( 1, 6, 96, ershi_logo[22] );
				  }
				    break;
	   case 20: {  Lcd_Character_16X16( 1, 6, 80, ershi_logo[23] );    //˪��
				     Lcd_Character_16X16( 1, 6, 96, ershi_logo[24] );
				  }
				    break;
	   case 21: {   Lcd_Character_16X16( 1, 6, 80, ershi_logo[3] );  	//����
				     Lcd_Character_16X16( 1, 6, 96, ershi_logo[25] );
				  }
				    break;
	   case 22: {   Lcd_Character_16X16( 1, 6, 80, ershi_logo[0] );  	//Сѩ
				     Lcd_Character_16X16( 1, 6, 96, ershi_logo[26] );
				  }
				    break;
	   case 23: {   Lcd_Character_16X16( 1, 6, 80, ershi_logo[2] );    //��ѩ
				     Lcd_Character_16X16( 1, 6, 96, ershi_logo[26] );
				  }
				    break;
	   case 24: {   Lcd_Character_16X16( 1, 6, 80, ershi_logo[25] );  	//����
				     Lcd_Character_16X16( 1, 6, 96, ershi_logo[17] );
				  }
				    break;
	   default:
		  break;
		 }
}