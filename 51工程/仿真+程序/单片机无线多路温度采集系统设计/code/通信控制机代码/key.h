/***********************************************************************
*�ļ����ƣ�key.h
*˵�������ļ�Ϊ����ɨ����������ͷ�ļ�
*���ܣ�1.�˿ڶ���
       2.������������
*�޸ģ���
*�汾��V1.0.0
*���ߣ�YuanDong
*ʱ�䣺2009.07.03
*************************************************************************/
#include "Include.h"
#ifndef KEY_H
    #define KEY_H 1
    #ifndef KEY_GLOBAL
        #define KEY_EXT  extern
    #else
        #define KEY_EXT
    #endif
    #define READ_KEY(x,name,b)       ((x) ? (b |= name):(b &= ~name) )
/*--------------------------------�û�������------------------------------------------*/
    #define CAN_MORE_PRESS  0             // �Ƿ�����������: ����Ϊ1;������Ϊ0 
    #define CAN_REPEAT      1              // �Ƿ������ظ�����: ����Ϊ1;������Ϊ0 
    #define REPEAT_MODE     1              // �ظ�ģʽ: �ȳ����Ϊ1;��ͬ���Ϊ0 
    #define FIRST_TIMES     200              // �ظ�����ʱ,��һ�μ��ʱ�� 
    #define OTHER_TIMES     25              // �ڶ��κ���ʱ��(����ظ�ģʽΪ0ʱ��ֵ��Ч) 
    #define KEY_DELAY_TIME  20             // ����ɨ��ʱ������XXXus 
 #define KEY_FORCE_VALUE 0              //������Ч��ƽ��1Ϊ�ߵ�ƽ��0Ϊ�͵�ƽ 
#define IN_PRESS_SECOND        P1_4     //�����ü��˿� 
    #define IN_PRESS_MINUTE        P1_5     //�����ü��˿� 
    #define IN_PRESS_HOUR          P1_6     //ʱ���ü��˿� 
    #define IN_PRESS_ALARM        P1_7	   //�������ü��˿� 
    #define IN_PRESS_UP             P1_4     //�����ü��˿� 
    #define IN_PRESS_DOWN         P1_5     //�����ü��˿� 
    #define IN_PRESS_START         P1_6      //ʱ���ü��˿� 
    #define IN_PRESS_STOP       P1_7	//�������ü��˿�  

    /* ������ӳ��  ע����ǰ�ṹ����󰴼���Ϊ:8; ��2�����е���Ӧλ����ʶ*/
	enum  KEY_VALUE{KEY_UP = 0x01,KEY_DOWN  = 0x02, KEY_START = 0x04, KEY_STOP = 0x08,KEY_NULL = 0x00};
//------------------------------------------------------------------------------------
    KEY_EXT void    init_key(void);
    KEY_EXT uchar   get_key_value(void);
KEY_EXT void delay_us(uint us);
KEY_EXT void delay(uint us);
#endif
