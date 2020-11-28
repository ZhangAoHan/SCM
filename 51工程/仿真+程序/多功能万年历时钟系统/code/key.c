#define KEY_GLOBAL 1
#include "key.h"
uchar keyValueBuff;  //��ǰ��ֵ������
uchar keyValueOld;	 //�ϴμ�ֵ��ȡ
uchar keyValueTemp;
/*****************************************
*�������ƣ�key_delay_us(uint us)
*�������ܣ����뼶��ʱ����
*������ڣ�us,��ʱ������
*�������ڣ���
*****************************************/
void key_delay_us(uint us)
{
   uchar delayi;
   while(--us)
   {
	 for(delayi=0;delayi<10;delayi++);
   } 
}
/****************************************
*�������ƣ�key_init(void)
*�������ܣ���ʼ������ɨ��������
*������ڣ���
*�������ڣ���
****************************************/
void key_init(void)
{
  keyValueBuff=0x00;
  keyValueOld=0x00;
  keyValueTemp=0x00;
}
/********************************************
*�������ƣ�read_all_key(uchar *buff)
*�������ܣ�ʵʱ��ȡ����ֵ
*������ڣ�buff,ָ���ֵ��ȡ����
*�������ڣ���
********************************************/
void read_all_key(uchar *buff)
{
   READ_KEY(IN_PRESS_UP==KEY_FORCE_VALUE,KEY_UP,*buff);
   READ_KEY(IN_PRESS_DOWN==KEY_FORCE_VALUE,KEY_DOWN,*buff);
   READ_KEY(IN_PRESS_CLEAR==KEY_FORCE_VALUE,KEY_CLEAR,*buff);
   READ_KEY(IN_PRESS_FUNC==KEY_FORCE_VALUE,KEY_FUNC,*buff);    
}
/********************************************************************************************
* �������ƣ�Key_Idle()
* ��    �ܣ������ɿ�
* ��ڲ�������
* ���ڲ�������
*********************************************************************************************/
void Key_Idle(void)
{
   uchar temp;
   while (temp!=KEY_NULL)
   {  
      read_all_key(&temp);
   }
}
/********************************************************************************************
* �������ƣ�Key_Scan()
* ��    �ܣ�����ɨ��
* ��ڲ�������
* ���ڲ�������ֵ
*********************************************************************************************/
uchar Key_Scan(void)
{
   keyValueBuff=0x00;
   read_all_key(&keyValueBuff);
   keyValueTemp=keyValueBuff;
   key_delay_us(10);
   read_all_key(&keyValueBuff);
   if(keyValueBuff==keyValueTemp)
   {
     switch(keyValueBuff)
	 {
	   case KEY_UP:    return KEY_UP;
	   case KEY_DOWN:  return KEY_DOWN;
	   case KEY_CLEAR: return KEY_CLEAR;
	   case KEY_FUNC:  return KEY_FUNC;
	   default:        return KEY_NULL;
	 }
   }
}


/********************************************************************************************
* �������ƣ�Key_Set_Clock( uchar * clock_time )
* ��    �ܣ������趨ʱ��
* ��ڲ�����clock_time[6]ָ��
* ���ڲ�������
*********************************************************************************************/
void Key_Set_Clock( uchar * clock_time )
{
   uchar *i; 
   i = clock_time ;
   clock_time ++ ;   //ָ���
   Lcd_Set_Clock( 2, i );  //��Ļ��ʾ����ʱ�� 
   Key_Idle();
   while(1)
   {
      uchar minute;
      minute = ( ( * clock_time >>4 ) * 10 ) + ( ( * clock_time ) & 0x0f );                                //BCD ת HEX
      switch( Key_Scan() )   //������  
      {	  	  	  	  
         case KEY_UP:   
		 { 
		   minute ++;   
		   if(minute==60)
		      minute=0;
           (*clock_time)=minute/10<<4; 
		   (*clock_time)=(*clock_time)|( minute%10); //HEX ת BCD 
			Lcd_Set_Clock( 2, i );  //��Ļ��ʾ����ʱ�� 
 		    Key_Idle();
			break;
         }                  
         case KEY_DOWN: 
		 { 
		   if(minute==0)  
			 minute=60;  
		   minute --; 
           (*clock_time)=minute/10<<4; 
		   (*clock_time)=(*clock_time)|(minute%10);  //HEX ת BCD  
           Lcd_Set_Clock( 2, i );  //��Ļ��ʾ����ʱ��
           Key_Idle();
		   break;
         }                    
        case  KEY_FUNC:  //����ʱ
         {
			clock_time ++;   //ָ��ʱ
            Lcd_Set_Clock(3,i);   //��Ļ��ʾ����ʱ�� 
			Key_Idle();
            while(1)
            {
			   uchar hour;
               hour=((*clock_time>>4)*10)+((*clock_time)&0x0f);                                //BCD ת HEX
               switch( Key_Scan())
               {
                  case  KEY_UP:  
				   {
					  hour ++;
					  if(hour==24) 
						hour = 0; 
					 (*clock_time)=hour/10 <<4 ; 
					 (*clock_time)=(*clock_time)|(hour%10);   //HEX ת BCD 
                     Lcd_Set_Clock( 3, i );   //��Ļ��ʾ����ʱ�� 
					 Key_Idle();
					 break;
				   } 
                  case  KEY_DOWN:  
				  {
					 if(hour == 0) 
						hour = 24;
					 hour --; 
					 if( hour == 0) 
						hour =23;
					 (*clock_time)=hour/10 <<4 ; 
					 (*clock_time)=(*clock_time)|(hour%10); //HEX ת BCD 
					 Lcd_Set_Clock( 3, i );   //��Ļ��ʾ����ʱ�� 
					 Key_Idle();
					 break;
				  }			      
                 case KEY_FUNC:    //������
  				 {
                    clock_time ++;   //ָ����
                    Lcd_Set_Clock( 4, i );   //��Ļ��ʾ����ʱ�� 
					Key_Idle();
					while(1)
					{
					  uchar day;
					  day = ( (*clock_time >>4)*10 ) + ( (*clock_time)&0x0f );                                //BCD ת HEX
					  switch(Key_Scan())
					  {
						 case KEY_UP:
   						 { 
							day ++;
							if(day==32)
							  day=1; 
							(*clock_time)=day/10 <<4 ;  
							(*clock_time)=(*clock_time)|(day%10);                         //HEX ת BCD 
							Lcd_Set_Clock( 4, i );   //��Ļ��ʾ����ʱ�� 
							Key_Idle();
							break;
						 }						    
                        case KEY_DOWN: 
						 { 
							if(day == 0)
							  day= 31;
							day --; 
							if(day == 0) 
							  day=31; 
							(*clock_time) = day/10 <<4 ;     
							(*clock_time) = (*clock_time) | (day%10);                         //HEX ת BCD ;
							Lcd_Set_Clock( 4, i );   //��Ļ��ʾ����ʱ�� 
							Key_Idle();
							break;
						}													     
		               case KEY_FUNC:    //������
					   {
                         clock_time ++;   //ָ����
						 Lcd_Set_Clock( 5, i );   //��Ļ��ʾ����ʱ�� 
						 Key_Idle();
						 while(1)
						 {
						   uchar month;
						   month = ( ( * clock_time >>4)*10 ) + ( ( * clock_time ) & 0x0f );                                //BCD ת HEX
                           switch(Key_Scan())
						   {
                              case KEY_UP: 
							   {  
								  month ++; 
								  if(month == 13)
									month= 1;
								  (*clock_time)=month/10<<4; 
								  (*clock_time)=(*clock_time)|(month%10);                         //HEX ת BCD 
								   Lcd_Set_Clock( 5, i );   //��Ļ��ʾ����ʱ�� 
							       Key_Idle();
								   break;
							  }										   
                              case KEY_DOWN:
							   {  
								  if(month==0)
									 month = 12; 
								  month --; 
								  if(month==0) 
									month = 12; 
								  (*clock_time)=month/10 <<4; 
								  (*clock_time)=(*clock_time)|(month%10);                         //HEX ת BCD 
								  Lcd_Set_Clock( 5, i );   //��Ļ��ʾ����ʱ�� 
							      Key_Idle();
								  break;
							  }                                                 
							 case KEY_FUNC:    //������
							 {
								clock_time ++;   //ָ����
								Lcd_Set_Clock( 6, i );   //��Ļ��ʾ����ʱ�� 
							    Key_Idle();
						        while(1)
							    {
								  uchar year;
							      year=((*clock_time>>4)*10)+((*clock_time)&0x0f);                                //BCD ת HEX
                                  switch( Key_Scan() )
								  {
								     case KEY_UP: 
							         {   
										  year ++; 
										  if(year == 100)
											 year= 0; 
										  (*clock_time)=year/10<<4;
								          (*clock_time)=(*clock_time)|(year%10); //HEX ת BCD 
								          Lcd_Set_Clock( 6, i );   //��Ļ��ʾ����ʱ�� 
							              Key_Idle();
									      break;
						             }
                                     case KEY_DOWN:
								     {  
									   if(year==0) 
										  year=100; 
									   year--; 
									   if(year==0) 
										  year=100;
									   (*clock_time)=year/10<<4;
								       (*clock_time)=(*clock_time)|(year%10); //HEX ת BCD 
									    Lcd_Set_Clock( 6, i );   //��Ļ��ʾ����ʱ�� 
							            Key_Idle();
								        break;
								     }
					                 case KEY_FUNC: 
								      {   
										 goto loop; 
									     break;
								      } 
							       }																				   
						         }
					          }
		                    } 
	                      }
	                    }             
                     }
                   }
                 }
               }
            }         
          }
      }
   }
   loop:  Key_Idle(); 
}
/***************************************************************************************
* ����: Key_Set_Alarm( uchar *  alarm_time )
* ����: ���ӵ���
* ��ڲ���: ���ӵ�ַ
* ���ڲ���:
****************************************************************************************/
void Key_Set_Alarm( uchar * alarm_time )
{
   Lcd_Alarm( 1, alarm_time );
   Key_Idle();
   while( 1 )
   {
      switch( Key_Scan() )
	  {
	     case KEY_UP:
		 {   
		   (*alarm_time)++;
		   if(*alarm_time==60)
		      *alarm_time = 0;
		   Lcd_Alarm( 1, alarm_time );
		   Key_Idle();
		   break;
		 }			  
	    case KEY_DOWN:
	     {
		    if(*alarm_time==0) 
			  *alarm_time=60; 
		    (*alarm_time)--;
	        Lcd_Alarm(1,alarm_time);
            Key_Idle();
			break;
	     }				
		case KEY_CLEAR:
		 {
			Lcd_Clear();
			goto loop;
			break;
		 }				
		case KEY_FUNC:
		 {
			alarm_time ++;
		    Lcd_Alarm( 2, alarm_time - 1 );
		    Key_Idle();
            while( 1 )
			{
			  switch( Key_Scan() )
			  {
				case KEY_UP:
				{
				  (*alarm_time) ++; 
				  if(*alarm_time==24) 
				    *alarm_time=0;
				  Lcd_Alarm( 2,alarm_time-1);
				  Key_Idle();
				  break;
			    }			     
		        case KEY_DOWN:
			    {
				   if(*alarm_time==0) 
				      *alarm_time=24;
				   (*alarm_time)--;
		           Lcd_Alarm( 2, alarm_time - 1 );
				   Key_Idle();
				   break;
			    }                     
		 	    case KEY_CLEAR:
				 {
				    Lcd_Clear();
	                goto loop;
					break;
				 }
			    case KEY_FUNC:
				 {
					Lcd_Clear();
					goto loop;
					break;
			     }

			   }
			}
		  break;
		}
	  }
   }
   loop: Key_Idle();
}
/****************************************************************************************
* ����: Key_Function( uchar * clock_time ) 
* ����: ϵͳ���ܵ���
* ��ڲ���: ʱ�ӳ���
* ���ڲ���: ��
*****************************************************************************************/
void Key_Function( uchar * clock_time, uchar * alarm_time )
{
   uchar temp = 2;
   Lcd_Clear();
   Lcd_Function( temp );
   Key_Idle();
   while( 1 )
   {
     switch( Key_Scan() )
     {
       case KEY_UP:
       {
         temp ++;
         if( temp > 2 )
           temp = 2;
         Lcd_Function( temp );
         Key_Idle();
		 break;
       }                 
      case KEY_DOWN:
      {
         temp --;
        if( temp == 0 )
           temp = 1;
        Lcd_Function( temp );
        Key_Idle();
		break;
      }                
     case KEY_CLEAR:
      {
		 Lcd_Clear();
         goto loop;
		 break;
      }               
     case KEY_FUNC:
     {
        if( temp == 2 )
        {
          Lcd_Clear();
          Key_Set_Clock( clock_time );
          Clock_Initial( clock_time );
          Lcd_Clear();
          goto loop;
        }
       if( temp == 1 )
        {
          Lcd_Clear();
          Key_Set_Alarm( alarm_time );
          Lcd_Clear();
	      goto loop;
        }
	   break;
     }
                            
   }
 }
  loop: Key_Idle();
}