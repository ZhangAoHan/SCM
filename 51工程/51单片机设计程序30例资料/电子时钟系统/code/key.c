#define KEY_GLOBAL  1
#include "Key.h"

uchar keyValueBuff;             // ��ȡ��ֵ�Ļ����� 
uchar keyValueOld;              // ǰһ�εļ�ֵ 
uchar keyValueTemp;
uint  stillTimes;               // �����±��ִ��� 
uint  stillTimesMax;

uchar get_data_1_count(uchar number);
void read_all_key(uchar *buff);
					   
/********************************************************************************************
* �������ƣ�init_key(void)
* ��    �ܣ�����������ʼ��
* ��ڲ�������
* ���ڲ�������
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
* �������ƣ�uchar get_key_value(void)
* ��    �ܣ���ȡ���̵ļ�ֵ
* ��ڲ�������
* ���ڲ��������̵ļ�ֵ���루keyValueTemp��
*********************************************************************************************/
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
   
/********************************************************************************************
* �������ƣ�uchar get_data_1_count(uchar number)
* ��    �ܣ��ж�ͬʱ���µļ�����Ŀ
* ��ڲ�������ֵ��uchar number��
* ���ڲ�����ͬʱ���µļ�����Ŀ
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
* �������ƣ�delay_us(uint us)
* ��    �ܣ���ʱһ��ʱ��
* ��ڲ�����us
* ���ڲ�������
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
* �������ƣ�delay(uint us)
* ��    �ܣ���ʱ1ms
* ��ڲ�����us
* ���ڲ�������
*********************************************************************************************/													  
void delay(uint us)                                          //1ms
{
   uchar delayi;
   while(--us)
   {
	 for(delayi = 0;delayi < 124;delayi++);
   }
}
