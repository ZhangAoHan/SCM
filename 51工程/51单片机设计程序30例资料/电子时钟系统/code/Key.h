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

    #define CAN_MORE_PRESS  0           // �Ƿ�����������: ����Ϊ1;������Ϊ0 
    #define CAN_REPEAT      1           // �Ƿ������ظ�����: ����Ϊ1;������Ϊ0 
    #define REPEAT_MODE     1           // �ظ�ģʽ: �ȳ����Ϊ1;��ͬ���Ϊ0 
    #define FIRST_TIMES     200         // �ظ�����ʱ,��һ�μ��ʱ�� 
    #define OTHER_TIMES     25          // �ڶ��κ���ʱ��(����ظ�ģʽΪ0ʱ��ֵ��Ч) 
    #define KEY_DELAY_TIME  20          // ����ɨ��ʱ������XXXus 
	#define KEY_FORCE_VALUE 0           //������Ч��ƽ��1Ϊ�ߵ�ƽ��0Ϊ�͵�ƽ 

	#define IN_PRESS_SECOND      P1_0   //�����ü��˿� 
    #define IN_PRESS_MINUTE      P1_1   //�����ü��˿� 
    #define IN_PRESS_HOUR        P1_2   //ʱ���ü��˿� 
    #define IN_PRESS_ALARM       P1_3	//�������ü��˿� 

    /* ������ӳ��  ע����ǰ�ṹ����󰴼���Ϊ:8; ��2�����е���Ӧλ����ʶ*/
	enum  KEY_VALUE{KEY_SECOND = 0x01,KEY_MINUTE = 0x02, KEY_HOUR = 0x04, KEY_ALARM = 0x08,KEY_NULL = 0x00};
//------------------------------------------------------------------------------------
    KEY_EXT void    init_key(void);
    KEY_EXT uchar   get_key_value(void);
	KEY_EXT void delay_us(uint us);
	KEY_EXT void delay(uint us);
#endif
