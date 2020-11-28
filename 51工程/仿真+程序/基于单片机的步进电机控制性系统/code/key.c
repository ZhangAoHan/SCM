#define KEY_GLOBAL  1
#include "Key.h"
static uchar keyValueBuff;             //��ȡ��ֵ�Ļ����� 
static uchar keyValueOld;              //ǰһ�εļ�ֵ 
static uchar keyValueTemp;			   //��ֵ�м佻������ 
static uint  stillTimes;               //�����±��ִ���
static uint  stillTimesMax;

static uchar get_data_1_count(uchar number);
static void read_all_key(uchar *buff);
/**********************************************************
*�������ƣ�keyDelay(uint us)
*�������ܣ����뼶��ʱ
*������ڣ���ʱ��������us
*�������ڣ���
***********************************************************/
void keyDelay(uint us)
{
   uchar delayi;
   while(--us)
   {
	 for(delayi=0;delayi<10;delayi++);
   } 
}															  
/*******************************************
*�������ƣ�key_init(void)
*�������ܣ���ʼ������ɨ��
*������ڣ���
*�������ڣ���
*******************************************/
void key_init(void)
{
    keyValueBuff = 0x00;
    keyValueOld = 0x00;
    keyValueTemp = 0x00;
    stillTimes = 0;
    stillTimesMax = FIRST_TIMES;
}
/******************************************************
*�������ƣ�read_all_key(uchar *buff)
*�������ܣ�ɨ�谴���µļ��������µļ���λ�ô������buff
*������ڣ�buff
*�������ڣ���
*******************************************************/
void read_all_key(uchar *buff)
{
   if(IN_PRESS_FRONT==KEY_FORCE_VALUE)   //��ⰴ�µļ�
	 READ_KEY(1,KEY_FRONT,*buff);
   else
     READ_KEY(0,KEY_FRONT,*buff);

   if(IN_PRESS_QUEEN==KEY_FORCE_VALUE)	 //��ⰴ�µļ�
     READ_KEY(1,KEY_QUEEN,*buff);
   else
     READ_KEY(0,KEY_QUEEN,*buff);
   
   if(IN_PRESS_ADD==KEY_FORCE_VALUE)	//��ⰴ�µļ�
     READ_KEY(1,KEY_ADD,*buff);
   else
     READ_KEY(0,KEY_ADD,*buff);
  
   if(IN_PRESS_REDUCE==KEY_FORCE_VALUE)	//��ⰴ�µļ�
     READ_KEY(1,KEY_REDUCE,*buff);
   else
     READ_KEY(0,KEY_REDUCE,*buff);
  
   if(IN_PRESS_STOP==KEY_FORCE_VALUE)  //��ⰴ�µļ�
     READ_KEY(1,KEY_STOP,*buff);
   else
     READ_KEY(0,KEY_STOP,*buff);
}
/******************************************************
*�������ƣ�get_key_value(void)
*�������ܣ���ȡ��ֵ
*������ڣ���
*�������ڣ����ذ��µ���Ч��ֵ
*******************************************************/
uchar get_key_value(void)
{
    keyValueBuff = 0x00;
    read_all_key(&keyValueBuff);
    keyValueTemp = keyValueBuff;
    keyDelay(KEY_DELAY_TIME);
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
/**********************************************************
*�������ƣ�get_data_1_count(uchar number)
*�������ܣ�����uchar���ͱ�����1�����������ڼ���Ƿ�������
*������ڣ�number,��Ҫ���1�����ı���
*�������ڣ����ر���bumber��1������
***********************************************************/
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
