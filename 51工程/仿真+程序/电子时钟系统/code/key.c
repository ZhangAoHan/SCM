#define KEY_GLOBAL  1
#include "Key.h"

uchar keyValueBuff;             // 读取键值的缓冲区 
uchar keyValueOld;              // 前一次的键值 
uchar keyValueTemp;
uint  stillTimes;               // 键按下保持次数 
uint  stillTimesMax;

uchar get_data_1_count(uchar number);
void read_all_key(uchar *buff);
					   
/********************************************************************************************
* 函数名称：init_key(void)
* 功    能：键盘驱动初始化
* 入口参数：无
* 出口参数：无
*********************************************************************************************/
void init_key(void)
{
    keyValueBuff = 0x00;
    keyValueOld = 0x00;
    keyValueTemp = 0x00;
    stillTimes = 0;
    stillTimesMax = FIRST_TIMES;
}
void read_all_key(uchar *buff)
{
   if(IN_PRESS_SECOND == KEY_FORCE_VALUE)
	 READ_KEY(1,KEY_SECOND,*buff);
   else
     READ_KEY(0,KEY_SECOND,*buff);

   if(IN_PRESS_MINUTE == KEY_FORCE_VALUE)
     READ_KEY(1,KEY_MINUTE,*buff);
   else
     READ_KEY(0,KEY_MINUTE,*buff);

   if(IN_PRESS_HOUR == KEY_FORCE_VALUE)
     READ_KEY(1,KEY_HOUR,*buff);
   else
     READ_KEY(0,KEY_HOUR,*buff);

   if(IN_PRESS_ALARM == KEY_FORCE_VALUE)
     READ_KEY(1,KEY_ALARM,*buff);
   else
     READ_KEY(0,KEY_ALARM,*buff);
     
}							
/********************************************************************************************
* 函数名称：uchar get_key_value(void)
* 功    能：获取键盘的键值
* 入口参数：无
* 出口参数：键盘的键值编码（keyValueTemp）
*********************************************************************************************/
uchar get_key_value(void)
{
    keyValueBuff = 0x00;
    read_all_key(&keyValueBuff);
    keyValueTemp = keyValueBuff;
    delay_us(KEY_DELAY_TIME);
    read_all_key(&keyValueBuff);

    /* 两次读到的键盘值相同 则为有效键盘值 */
    if( keyValueTemp == keyValueBuff )
    {

        if(keyValueTemp == 0)
        {
            keyValueOld = 0;
            stillTimes = 0;
            stillTimesMax = FIRST_TIMES;
            return 0;
        }
        else if(keyValueOld != keyValueTemp)
        {
            stillTimes = 0;
            keyValueOld = keyValueTemp;

            #if CAN_MORE_PRESS
                return keyValueTemp;
            #else
                if( 1 == get_data_1_count(keyValueTemp) )
                {
                    return keyValueTemp;
                }
                else
                {
                    return 0;
                }
            #endif
        }
        else if(keyValueOld == keyValueTemp)
        {
            #if CAN_MORE_PRESS == 0
                if( 1 != get_data_1_count(keyValueTemp) )
                {
                    stillTimes = 0;
                    return 0;
                }
            #endif

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
                stillTimes = 0;
                return 0;
            #endif
        }
    }
    else
    {
        stillTimes = 0;
        return 0;
    }
    return 0;
}
   
/********************************************************************************************
* 函数名称：uchar get_data_1_count(uchar number)
* 功    能：判断同时按下的键的数目
* 入口参数：键值（uchar number）
* 出口参数：同时按下的键的数目
*********************************************************************************************/
uchar get_data_1_count(uchar number)
{
    register uchar i,j = 0;
    for(i = 0; i < 8; i ++)
    {
        if( (number&_BV(i)) )
        {
            j ++;
        }
    }
    return j;
}	
	 
/********************************************************************************************
* 函数名称：delay_us(uint us)
* 功    能：延时一段时间
* 入口参数：us
* 出口参数：无
*********************************************************************************************/
void delay_us(uint us)
{
   uchar delayi;
   while(--us)
   {
	 for(delayi = 0;delayi < 10;delayi++);
   } 
}		
/********************************************************************************************
* 函数名称：delay(uint us)
* 功    能：延时1ms
* 入口参数：us
* 出口参数：无
*********************************************************************************************/													  
void delay(uint us)                                          //1ms
{
   uchar delayi;
   while(--us)
   {
	 for(delayi = 0;delayi < 124;delayi++);
   }
}
