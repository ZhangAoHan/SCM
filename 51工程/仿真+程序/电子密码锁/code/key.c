#define KEY_GLOBAL 1
#include "key.h"
static uchar keyValueTemp;      //当前键值,keyScanValue=keyLineScan*keyRowScan
static uchar keyValueOld;       //前次键盘值寄存变量  
static uchar keyIsUp;           //判断键是否按下键  
uint  stillTimes;               //键按下保持次数
uint  stillTimesMax;
static void  write_line(uchar n);
static void  write_row(uchar n);
static void  write_line_row(uchar line,uchar row); //line,row均用到最后四位
static uchar read_line(void);
static uchar read_row(void);  
static uchar get_data_1_count(uchar number);
static uchar get_key(uchar lineV,uchar rowV);

void key_init(void)
{
  keyIsUp=1;  //初始默认键盘的键都是松开的
  write_line_row(0x00,0x0f);
  keyValueTemp=0x00;
  keyValueOld=0x00;  
}
void keyDelay(uint us)
{
  uchar i;
  while(us--)
  {
    for(i=0;i<100;i++);
  }
}  
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
void  write_line_row(uchar lineWrite,uchar rowWrite)
{
    write_line(lineWrite);
    write_row(rowWrite); 
}
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
uchar get_key_value(void)
{
  uchar lineValue,lineValueTemp;
  uchar rowValue;
  write_line_row(0x00,0x0f);
  keyDelay(10);
  lineValue=read_line();
  keyDelay(10);
  lineValueTemp=read_line();
  if(lineValue==lineValueTemp) //比较两次扫描的键盘是否一样
  {
     if((lineValue&0x0f)==0x00) //判断是否有键按下
     {
        stillTimes=0x00;
	    keyIsUp=1;              //键是否松开
        stillTimesMax = FIRST_TIMES;
        return 0x00;
     }
     else
     {
        if(1==get_data_1_count(lineValue))  //判断是否是一个键按下
         {
           write_line_row(0x0f,0x00);
           keyDelay(10);
           rowValue=read_row();
           if(1==get_data_1_count(rowValue))
           {
              keyValueTemp=get_key(lineValue,rowValue);  
              if(keyValueTemp!=keyValueOld)
              {
                   keyValueOld=keyValueTemp;
				   keyIsUp=0;             //有键按下
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
             else	//列扫描结束处 
             {
                stillTimes=0x00;
                return 0x00;
             }
          }    //结束一行键盘的扫描
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