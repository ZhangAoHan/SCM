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
* ����: get_moon_day(uchar month_p,uint table_addr)
* ����: ��ȡ���ݱ���ũ���Ĵ��»�С�� ��������·���1, С�·���0
* ��ڲ���:
* ���ڲ���:
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
* ����: void Calendar_Convert( uchar * clock_time )
* ����: ����BCD���������ݣ� ���BCD��������( 1901 - 2099 )
* ��ڲ���: c_flag:���������ͱ�־  clock_time: ʱ�ӵ�ַ
* ���ڲ���: ��
* ˵��: c_flag = 0 :21���� c_flag = 1 :19���� 
*****************************************************************************/
void Calendar_Convert( uchar c_flag, uchar * clock_time )
{
   bit flag_month, flag_year;
   uchar year, month, day, month_point; //���� �� �� ��
   uchar temp1, temp2, temp3;
   uint calendar_address; //����ũ����ַ
   uint day_number;
   uchar clock_moon[3]; //��������
   clock_time += 3; //ָ����
   day = ( * clock_time >> 4 ) * 10 + ( *clock_time & 0x0f ); //BCDת��ʮ����
   clock_time ++; //ָ����
   month = ( * clock_time >> 4 ) * 10 + ( * clock_time & 0x0f ); //BCDת��ʮ����
   clock_time ++; //ָ����
   year = ( * clock_time >> 4 ) * 10 + ( * clock_time & 0x0f ); //BCDת��ʮ���� 
   calendar_address =  year  * 3;
   //����(���³�һ)���ڵ������·�
   temp1 = year_code[ calendar_address + 2 ] & 0x60; //Bit6~~Bit5:�������ڵ������·�
   temp1 >>= 5 ;
   //����(���³�һ)���ڵ���������
   temp2 = year_code[ calendar_address + 2 ] & 0x1f; //Bit4~~Bit0:�������ڵ���������
   //���㴺��(���³�һ)�뵱��Ԫ��{ 1��1��(����) }������������ֻ����������1�� �� 2��
   if( temp1 == 1 )
      temp3 = temp2 - 1;
   else
      temp3 = temp2 + 31 - 1;
   //�����������뵱��Ԫ��{ 1��1��(����) }������
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
	} //���������������뵱��Ԫ��{ 1��1��(����) }������       
   //�ж������� �ڴ���(���³�һ) ֮ǰ ���� ֮��
   if( day_number >= temp3 ) //�����ڴ���֮�� ���� ���ڵ���
   {
      day_number -= temp3;
      month = 1;
      month_point = 1; // month_point Ϊ�·�ָ���������ڴ���ǰ���Ǵ���
	  flag_month = get_moon_day( month_point, calendar_address ); //���������µĴ�С  ���·���1  С�·���0
	  flag_year = 0;
	  if( flag_month )
	     temp1 = 30; //����30��
	  else
 	     temp1 = 29; //С��29��
      //�������ڵ��·�
	  temp2 = year_code[ calendar_address ] & 0xf0;
	  temp2 >>= 4; //��ȡ����λ  ������0 ��ʾû������

	  while( day_number >= temp1 )
	  {
	     day_number -= temp1;
         month_point ++;
         if( month == temp2 ) //����� ����
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
   else //�����ڴ���֮ǰʹ�����´����������
   {
      temp3 -= day_number;
      if( year == 0 )
         { year = 99; c_flag = 1; }
      else
         year -= 1;
      calendar_address -= 0x03;
      month = 12;
      temp2 = year_code[ calendar_address] & 0xf0;
      temp2 >>= 4; //��ȡ��4λ
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
   //HEX->BCD ,���������,������ת��ΪBCD����
   temp1 = year / 10;
   temp1 <<= 4;
   clock_moon[2] = temp1 | ( year % 10 );
 
   temp1 = month / 10;
   temp1 <<= 4;
   clock_moon[1] = temp1 | ( month % 10 );
 
   temp1 = day / 10;
   temp1 <<= 4;
   clock_moon[0] = temp1 | ( day % 10 );
   Lcd_Lunar_Calendar( clock_moon );	//ת���������ʾLCD.H�е���ʾ����
}

/********************************************************************************
* ����: void Week_convert( uchar * clock_time )
* ����: ����BCD�������ݣ����BCD����
* ��ڲ���: 
* ���ڲ���:
* ˵��: �㷨: �� ���� + ��� + �������� + ��У�� ) / 7 �������������� ����������ֲ��� 3 �·�����֮�� Ҫ��һ�� ��
********************************************************************************/
void Week_Convert( bit c, uchar * clock_time )
{
   uchar year, month, day; //���� �� �� ��
   uchar temp;

   clock_time += 3; //ָ����
   day = ( * clock_time >> 4 ) * 10 + ( *clock_time & 0x0f ); //BCDת��ʮ����
   clock_time ++; //ָ����
   month = ( * clock_time >> 4 ) * 10 + ( * clock_time & 0x0f );
   clock_time ++; //ָ����
   year = ( * clock_time >> 4 ) * 10 + ( * clock_time & 0x0f ); 

   if( c == 0 ) //���Ϊ21����,�������100
      year += 100;
   temp = year / 4; //����������ֻ��1900��֮���
   temp = year + temp;
   temp = temp % 0x07; //Ϊ��ʡ��Դ,�Ƚ���һ��ȡ��,����������0xff,����ʹ����������
   temp = temp + day + table_week[ month - 1 ];
   if( ( year % 4  == 0 ) && ( month <3  ) )
      temp -=1;
   Lcd_Week( temp % 7 );
}
/**************************************************************************
* ����: void ershi( uchar * clock_time )
* ����: ����BCD���������ݣ� ���BCD��������( 2000 - 2099 )
* ��ڲ���:clock_time: ʱ�ӵ�ַ
* ���ڲ���: ��
*****************************************************************************/
void  Ershi( uchar * clock_time )
{
   uchar year, month, day, month_point; //���� �� �� ��
   uchar temp1, temp2, temp3,temp4;
   clock_time += 3; //ָ����
   day = ( * clock_time >> 4 ) * 10 + ( *clock_time & 0x0f ); //BCDת��ʮ����
   clock_time ++; //ָ����
   month = ( * clock_time >> 4 ) * 10 + ( * clock_time & 0x0f ); //BCDת��ʮ����
   clock_time ++; //ָ����
   year = ( * clock_time >> 4 ) * 10 + ( * clock_time & 0x0f ); //BCDת��ʮ���� 
   temp1=ershi1_code[(month-1)*2];     //�ҳ����µ�һ����������С��
   temp2=ershi1_code[(month-1)*2+1];	  //�ҳ����µڶ�����������С��
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