#define KEY_GLOBAL  1
#include "Key.h"

uchar keyValueBuff;             //读取键值的缓冲区
uchar keyValueOld;              //前一次的键值 
uchar keyValueTemp;
uint  stillTimes;               //键按下保持次数 
uint  stillTimesMax;

uchar get_data_1_count(uchar number);
void read_all_key(uchar *buff);
/*******************************************************************************************
*函数名称：key_init(void)
*函数功能：初始化按键扫描
*函数入口：无
*函数出口：无
*******************************************************************************************/
void init_key(void)
{
    keyValueBuff = 0x00;
    keyValueOld = 0x00;
    keyValueTemp = 0x00;
    stillTimes = 0;
    stillTimesMax = FIRST_TIMES;
}
/*******************************************************************************************
*函数名称：read_all_key(uchar *buff)
*函数功能：扫描按键下的键，将按下的键的位置存入变量buff
*函数入口：buff
*函数出口：无
*******************************************************************************************/
void read_all_key(uchar *buff)
{
   if(IN_PRESS_ONE==KEY_FORCE_VALUE)  //检测按下的键,并相应的置位或清零相应位
	 READ_KEY(1,KEY_ONE,*buff);
   else
     READ_KEY(0,KEY_ONE,*buff);

   if(IN_PRESS_TWO==KEY_FORCE_VALUE)
     READ_KEY(1,KEY_TWO,*buff);
   else
     READ_KEY(0,KEY_TWO,*buff);

   if(IN_PRESS_THREE==KEY_FORCE_VALUE)
     READ_KEY(1,KEY_THREE,*buff);
   else
     READ_KEY(0,KEY_THREE,*buff);

   if(IN_PRESS_FOUR==KEY_FORCE_VALUE)
     READ_KEY(1,KEY_FOUR,*buff);
   else
     READ_KEY(0,KEY_FOUR,*buff);
     
}
/*******************************************************************************************
*函数名称：get_key_value(void)
*函数功能：读取键值
*函数入口：无
*函数出口：返回按下的有效键值
*******************************************************************************************/
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
/*******************************************************************************************
*函数名称：get_data_1_count(uchar number)
*函数功能：计算uchar类型变量中1的数量，用于检测是否多键按下
*函数入口：number,需要检测1数量的变量
*函数出口：返回变量bumber中1的数量
*******************************************************************************************/
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
/*******************************************************************************************
*函数名称：delay_us(uint us)
*函数功能：毫秒级延时
*函数入口：延时计数变量us
*函数出口：无
*******************************************************************************************/
void delay_us(uint us)
{
   uchar delayi;
   while(--us)
   {
	 for(delayi=0;delayi<10;delayi++);
   } 
}															  
