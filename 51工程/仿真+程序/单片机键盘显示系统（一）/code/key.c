#define KEY_GLOBAL 1
#include "key.h"
static uchar keyValueTemp;       //��ǰ��ֵ�Ĵ�,keyScanValue=keyLineScan*keyRowScan
static uchar keyValueOld;        //�ϴ�ɨ��ļ�ֵ 
static uchar keyIsUp;            //�����Ƿ��ɿ�����  
static uint  stillTimes;         //�����±��ִ���
static uint  stillTimesMax;
static void  write_line(uchar n); //���n����λ���ж˿�
static void  write_row(uchar n);  //���n����λ���ж˿�
static void  write_line_row(uchar line,uchar row); //line��row�ĺ���λ�ֱ�����������еļ�ֵ
static uchar read_line();		  //��ȡ��ֵ�����ر����ĺ���λ
static uchar read_row();  		  //��ȡ��ֵ�����ر����ĺ���λ
static uchar get_data_1_count(uchar number);   //�������number��λΪ1������
static uchar get_key(uchar lineV,uchar rowV);  //���ݰ��µ����м�,����1~16��ֵ
/********************************************************
*�������ƣ�keyDelay_us(uint us)
*�������ܣ����뼶��ʱ����
*������ڣ���ʱѭ��������us
*�������ڣ���
********************************************************/
void  keyDelay_us(uint us)
{
  uchar delayi;
  while(--us)
  {
	for(delayi=0;delayi<10;delayi++);
  } 
}
/**********************************************************
*�������ƣ�init_key(void)
*�������ܣ�����ɨ�������ʼ��
*������ڣ���
*�������ڣ���
**********************************************************/
void key_init(void)
{
  keyIsUp=1;                   //������ʼĬ���ɿ�
  write_line_row(0x00,0x0f);   //��������ֵ��ʼΪ00001111  
  keyValueTemp=0x00;
  keyValueOld=0x00;  
}
/*************************************************************
*�������ƣ�get_key_value(void)
*�������ܣ���ü�ֵ
*������ڣ���
*�������ڣ�����1~16��ֵ
**************************************************************/
uchar get_key_value(void)
{
   uchar lineValue,lineValueTemp;
   uchar rowValue;
   write_line_row(0x00,0x0f);
   keyDelay_us(10);
   lineValue=read_line();
   keyDelay_us(10);
   lineValueTemp=read_line();
   if(lineValue==lineValueTemp) /*throw off twitter*/
   {
      if((lineValue&0x0f)==0x00) /*no key press*/
      {
          stillTimes=0x00;
		  keyIsUp=1;              /*the key is up*/
          stillTimesMax = FIRST_TIMES;
          return 0x00;
      }
      else
      {
         if(1==get_data_1_count(lineValue))  /*one line key press*/
         {
             write_line_row(0x0f,0x00);
             keyDelay_us(10);
             rowValue=read_row();
             if(1==get_data_1_count(rowValue))
             {
               keyValueTemp=get_key(lineValue,rowValue);  
               if(keyValueTemp!=keyValueOld)
                {
                    keyValueOld=keyValueTemp;

					keyIsUp=0;    /*the key is down*/

                    return keyValueTemp;
                }
                else if(keyValueTemp==keyValueOld)
                     {
                         #if CAN_REPEAT
                             stillTimes ++;
                             if(stillTimes > stillTimesMax)
                              {
                                stillTimes = 0;
                                #if REPEAT_MODE
                                  if(FIRST_TIMES == stillTimesMax)
                                  {
                                    stillTimesMax = OTHER_TIMES;
                                  }
                                #endif

                                  return keyValueTemp;
                              }
                          #else
							 if(keyIsUp==1)
						      {
								 stillTimes=0;
							     keyIsUp=0;
							     return keyValueTemp;
							  }
							  else
							  {
								 stillTimes = 0;
                                 return 0;
						      }
                                
                         #endif
                     }
             }
             else	/*end one row key press*/ 
             {
                stillTimes=0x00;
                return 0x00;
             }
         }    /*end one line key press*/
         else
         {
             stillTimes=0x00;
             return 0x00;      
         }
             
      }
        
    }
    else
    {
      stillTimes=0x00;
      return 0x00;
    }   
}
/*******************************************
*�������ƣ�write_line(uchar n)
*�������ܣ����n����λ���ж˿�
*������ڣ�n
*�������ڣ���
********************************************/
void write_line(uchar n)
{
   if(n&0x01)
     key_line_L1=1;
   else
     key_line_L1=0;

   if(n&0x02)
     key_line_L2=1;
   else 
     key_line_L2=0;

   if(n&0x04)
     key_line_L3=1;
   else
     key_line_L3=0;

   if(n&0x08)
     key_line_L4=1;
   else
     key_line_L4=0;
}
/*******************************************
*�������ƣ�write_row(uchar n)
*�������ܣ����n����λ���ж˿�
*������ڣ�n
*�������ڣ���
********************************************/
void write_row(uchar n)
{
   if(n&0x01)
     key_row_R1=1;
   else
     key_row_R1=0;

   if(n&0x02)
     key_row_R2=1;
   else 
     key_row_R2=0;

   if(n&0x04)
     key_row_R3=1;
   else
     key_row_R3=0;

   if(n&0x08)
     key_row_R4=1;
   else
     key_row_R4=0;
}
/*********************************************
*�������ƣ�read_line(void)
*�������ܣ���ȡ������ֵ
*������ڣ���
*�������ڣ����ؼ�����ֵ
*********************************************/
uchar read_line(void)
{    
   uchar lineBuff;   
   lineBuff=0x00;                    
   if(key_line_L1)
	 lineBuff|=0x01;
   else
	 lineBuff&=0xfe;

   if(key_line_L2)
	 lineBuff|=0x02;
   else
	 lineBuff&=0xfd;

   if(key_line_L3)
	 lineBuff|=0x04;
   else
	 lineBuff&=0xfb;

   if(key_line_L4)
	 lineBuff|=0x08;
   else
	 lineBuff&=0xf7;
    
   return lineBuff;
}
/*******************************************
*�������ƣ�read_row(void)
*�������ܣ���ȡ������ֵ
*������ڣ���
*�������ڣ����ؼ�����ֵ
*******************************************/
uchar read_row(void)
{ 
  uchar rowBuff;
  rowBuff=0x00;
  if(key_row_R1)
	 rowBuff|=0x01;
  else
	 rowBuff&=0xfe;

  if(key_row_R2)
	 rowBuff|=0x02;
  else
	 rowBuff&=0xfd;

  if(key_row_R3)
	 rowBuff|=0x04;
  else
	 rowBuff&=0xfb;

  if(key_row_R4)
	 rowBuff|=0x08;
  else
	 rowBuff&=0xf7;

  return rowBuff;
       
}
/********************************************************
*�������ƣ�write_line_row(uchar lineWrite,uchar rowWrite)
*�������ܣ�д����lineWrite��rowWrite����λ������
*������ڣ�lineWrite,rowWrite
*�������ڣ���
*********************************************************/
void write_line_row(uchar lineWrite,uchar rowWrite)
{
   write_line(lineWrite);
   write_row(rowWrite); 
}
/********************************************************
*�������ƣ�get_data_1_count(uchar number)
*�������ܣ��������number��Ϊ1��λ��
*������ڣ�number
*�������ڣ���
*********************************************************/
uchar get_data_1_count(uchar number)
{
   uchar i,j = 0;
   for(i = 0; i < 8; i ++)
   {
      if(number&0x01)
      {
         j ++;
      }
	  number=number>>1;
   }
    return j;
}
/************************************************************
*�������ƣ�uchar get_key(uchar lineV,uchar rowV)
*�������ܣ�������ֵlineV����ֵrowV�����ֵ1~16
*������ڣ����¼��̵���ֵlineV����ֵrowV
*�������ڣ����ؼ�ֵ1~16
************************************************************/
uchar get_key(uchar lineV,uchar rowV)
{
   uchar keyTemp;
   uchar l,r;
   for(l=0;l<4;l++)
    {
	   if(GET_BIT(lineV,l))
	    {
		 l++;
		 break;  
		}        
    }
    for(r=0;r<4;r++)
    {						
	    if(GET_BIT(rowV,r))
		{
		  r++;
		  break;
		}
    }  

    switch(l)
    {
        case 1:
         {
           keyTemp=r;
           break;
         }
        case 2:
         {
           keyTemp=r+4;
           break;
         }
        case 3:
         {
           keyTemp=r+8;
           break;
         }
        case 4:  
         {
           keyTemp=r+12;
           break;
         }
        default:
		{
		   keyTemp=0;
           break; 
		}
		   
    }
 return keyTemp;
}