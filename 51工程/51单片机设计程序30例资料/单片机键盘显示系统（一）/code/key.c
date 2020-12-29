#define KEY_GLOBAL 1
#include "key.h"
static uchar keyValueTemp;       //当前键值寄存,keyScanValue=keyLineScan*keyRowScan
static uchar keyValueOld;        //上次扫描的键值 
static uchar keyIsUp;            //按键是否松开变量  
static uint  stillTimes;         //键按下保持次数
static uint  stillTimesMax;
static void  write_line(uchar n); //输出n后四位到行端口
static void  write_row(uchar n);  //输出n后四位到列端口
static void  write_line_row(uchar line,uchar row); //line和row的后四位分别代表四行四列的键值
static uchar read_line();		  //读取行值到返回变量的后四位
static uchar read_row();  		  //读取列值到返回变量的后四位
static uchar get_data_1_count(uchar number);   //计算变量number中位为1的数量
static uchar get_key(uchar lineV,uchar rowV);  //根据按下的行列键,返回1~16键值
/********************************************************
*函数名称：keyDelay_us(uint us)
*函数功能：毫秒级延时函数
*函数入口：延时循环周期数us
*函数出口：无
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
*函数名称：init_key(void)
*函数功能：键盘扫描变量初始化
*函数入口：无
*函数出口：无
**********************************************************/
void key_init(void)
{
  keyIsUp=1;                   //按键初始默认松开
  write_line_row(0x00,0x0f);   //键盘行列值初始为00001111  
  keyValueTemp=0x00;
  keyValueOld=0x00;  
}
/*************************************************************
*函数名称：get_key_value(void)
*函数功能：获得键值
*函数入口：无
*函数出口：返回1~16键值
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
*函数名称：write_line(uchar n)
*函数功能：输出n后四位到行端口
*函数入口：n
*函数出口：无
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
*函数名称：write_row(uchar n)
*函数功能：输出n后四位到列端口
*函数入口：n
*函数出口：无
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
*函数名称：read_line(void)
*函数功能：读取键盘行值
*函数入口：无
*函数出口：返回键盘行值
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
*函数名称：read_row(void)
*函数功能：读取键盘列值
*函数入口：无
*函数出口：返回键盘列值
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
*函数名称：write_line_row(uchar lineWrite,uchar rowWrite)
*函数功能：写数据lineWrite和rowWrite后四位到行列
*函数入口：lineWrite,rowWrite
*函数出口：无
*********************************************************/
void write_line_row(uchar lineWrite,uchar rowWrite)
{
   write_line(lineWrite);
   write_row(rowWrite); 
}
/********************************************************
*函数名称：get_data_1_count(uchar number)
*函数功能：计算变量number中为1的位数
*函数入口：number
*函数出口：无
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
*函数名称：uchar get_key(uchar lineV,uchar rowV)
*函数功能：根据行值lineV和列值rowV计算键值1~16
*函数入口：按下键盘的行值lineV和列值rowV
*函数出口：返回键值1~16
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