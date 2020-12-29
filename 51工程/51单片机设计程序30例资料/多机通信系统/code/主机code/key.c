#define KEY_GLOBAL  1
#include "Key.h"

uchar keyValueBuff;                   //��ȡ��ֵ�Ļ�����
uchar keyValueOld;                    //ǰһ�εļ�ֵ
uchar keyValueTemp;
uint  stillTimes;                     //�����±��ִ���
uint  stillTimesMax;

uchar get_data_1_count(uchar number); //����number��λ��Ϊ1��λ��
void read_all_key(uchar *buff);
/************************************************
*�������ƣ�void init_key(void)
*�������ܣ�����������ʼ��
*������ڣ���
*�������ڣ���
************************************************/
void init_key(void)
{
    keyValueBuff = 0x00;
    keyValueOld = 0x00;
    keyValueTemp = 0x00;
    stillTimes = 0;
    stillTimesMax = FIRST_TIMES;
}
/***********************************************
*�������ƣ�read_all_key(uchar *buff)
*�������ܣ�ɨ�谴��������λbuffָ����ָ��ı���
����Ӧλ
*������ڣ�ָ��buff
*�������ڣ���
***********************************************/
void read_all_key(uchar *buff)
{
   if(IN_PRESS_ONE==KEY_FORCE_VALUE)
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

   if(IN_PRESS_FIVE==KEY_FORCE_VALUE)
     READ_KEY(1,KEY_FIVE,*buff);
   else
     READ_KEY(0,KEY_FIVE,*buff);
     
}
/**************************************************
*�������ƣ�get_key_value(void)
*�������ܣ���ü�ֵ
*������ڣ���
*�������ڣ����ؼ�ֵ
**************************************************/
uchar get_key_value(void)
{
    keyValueBuff = 0x00;
    read_all_key(&keyValueBuff);
    keyValueTemp = keyValueBuff;
    delay_us(KEY_DELAY_TIME);
    read_all_key(&keyValueBuff);

    /* ���ζ����ļ���ֵ��ͬ ��Ϊ��Ч����ֵ */
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
/***************************************************
*�������ƣ�get_data_1_count(uchar number)
*�������ܣ��������number��λΪ1��λ��
*������ڣ�number
*�������ڣ���
***************************************************/
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
/**************************************************
*�������ƣ�delay_us(uint us)
*�������ܣ����뼶��ʱ����
*������ڣ�us
*�������ڣ���
**************************************************/
void delay_us(uint us)
{
   uchar delayi;
   while(--us)
   {
	 for(delayi=0;delayi<10;delayi++);
   } 
}															  