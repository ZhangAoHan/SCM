#include "Include.h"
#ifndef KEY_H
    #define KEY_H 1

    #ifndef KEY_GLOBAL
        #define KEY_EXT  extern
    #else
        #define KEY_EXT
    #endif

    #define READ_KEY(x,name,b)       ((x)?(b|=name):(b&=~name) )
//--------------------------------�û�������------------------------------------------

    #define CAN_MORE_PRESS  0           //�Ƿ�����������: ����Ϊ1;������Ϊ0 
    #define CAN_REPEAT      1           //�Ƿ������ظ�����: ����Ϊ1;������Ϊ0 
    #define REPEAT_MODE     1           //�ظ�ģʽ: �ȳ����Ϊ1;��ͬ���Ϊ0 
    #define FIRST_TIMES     200         //�ظ�����ʱ,��һ�μ��ʱ�� 
    #define OTHER_TIMES     25          //�ڶ��κ���ʱ��(����ظ�ģʽΪ0ʱ��ֵ��Ч) 
    #define KEY_DELAY_TIME  20          //����ɨ��ʱ������XXXus
	#define KEY_FORCE_VALUE 0           //������Ч��ƽ��1Ϊ�ߵ�ƽ��0Ϊ�͵�ƽ 

	#define IN_PRESS_ONE        P1_0    //1���ü��˿� 
    #define IN_PRESS_TWO        P1_1    //2���ü��˿� 
    #define IN_PRESS_THREE      P1_2    //3���ü��˿� 
    #define IN_PRESS_FOUR       P1_3    //4���ü��˿� 
	#define IN_PRESS_FIVE       P1_4    //5���ü��˿� 
    #define IN_PRESS_SIX        P1_5    //6���ü��˿� 
    #define IN_PRESS_SEVEN      P1_6    //7���ü��˿�
    /* ������ӳ��  ע����ǰ�ṹ����󰴼���Ϊ:8; ��2�����е���Ӧλ����ʶ*/
	enum  KEY_VALUE{KEY_ONE= 0x01,KEY_TWO= 0x02,KEY_THREE=0x04,KEY_FOUR=0x08,KEY_FIVE=0x10,KEY_SIX=0x20,KEY_SEVEN=0x40,KEY_NULL = 0x00};
//------------------------------------------------------------------------------------
    KEY_EXT void  key_init(void);      //����ɨ���ʼ��
    KEY_EXT uchar get_key_value(void); //��ȡ��Ч��ֵ����
	KEY_EXT void  delay_us(uint us);   //us����ʱ����
#endif
