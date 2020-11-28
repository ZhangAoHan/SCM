#define KEY_GLOBAL  1
#include "Key.h"

uchar keyValueBuff;             // 读取键值的缓冲区 
uchar keyValueOld;              //前一次的键值 
uchar keyValueTemp;
uint  stillTimes;               //键按下保持次数 
uint  stillTimesMax;

uchar get_data_1_count(uchar number);
void read_all_key(uchar *buff);

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
   READ_KEY(IN_PRESS_ONE==KEY_FORCE_VALUE,KEY_ONE,*buff);
   READ_KEY(IN_PRESS_TWO==KEY_FORCE_VALUE,KEY_TWO,*buff);
   READ_KEY(IN_PRESS_THREE==KEY_FORCE_VALUE,KEY_THREE,*buff);
   READ_KEY(IN_PRESS_FOUR==KEY_FORCE_VALUE,KEY_FOUR,*buff);
   READ_KEY(IN_PRESS_FIVE==KEY_FORCE_VALUE,KEY_FIVE,*buff);
   READ_KEY(IN_PRESS_SIX==KEY_FORCE_VALUE,KEY_SIX,*buff);
   READ_KEY(IN_PRESS_SEVEN==KEY_FORCE_VALUE,KEY_SEVEN,*buff);
   READ_KEY(IN_PRESS_EIGHT==KEY_FORCE_VALUE,KEY_EIGHT,*buff);
     
}
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
void delay_us(uint us)
{
   uchar delayi;
   while(--us)
   {
	 for(delayi=0;delayi<10;delayi++);
   } 
}															  
void delay(uint us)                                      //1ms
{
   uchar delayi;
   while(--us)
   {
	 for(delayi=0;delayi<124;delayi++);
   }
}
