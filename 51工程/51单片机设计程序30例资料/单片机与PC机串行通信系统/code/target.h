/****************************************************************************************
* �ļ����ƣ�Target.h
* ˵�������ļ�Ϊ����ͷ�ļ�
* ���ܣ�����ʹ�õĺ���˵��
* �޸ģ���
* �汾��1.0.0
* ���ߣ�YuanDong
* ʱ�䣺2009.5.30
*****************************************************************************************/
#ifndef TARGET_H
#define TARGET_H
#include "Include.h"
#ifndef TARGET_GLOBAL
     #define TARGET_EXT extern
#else
    #define TARGET_EXT
#endif
TARGET_EXT void  usart0_initial(void);             //ʹ�ö�ʱ��1,���ʼ����usart0��ʼ����
TARGET_EXT void  send_char(uchar txd);           //���ڷ���һ���ַ�
TARGET_EXT uchar get_char(void);                 //���ڽ���һ���ַ�
TARGET_EXT void  send_str(uchar *str,uchar len);    //���ڷ���һ���ַ���
#endif
