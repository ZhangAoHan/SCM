/**************************************************************************************
                                TLC2543��������
����:12λAD����оƬ����.
˵��:оƬ��ʼʱ��һ�β���������Ч
     оƬ��������ʼ���Ϊ:0
	 �����ٶȣ�11.0592MHz AVR16L ��0s�Ż�ģʽ  (25us)
����:wayne
ʱ��:2007-11-01
�汾:0.1.0
//----------------------------------------------------------
��ֲ:ϵͳ��GCC����ֲ��IAR��.
����:wayne
ʱ��:2007-11-01
�汾:0.1.0
**************************************************************************************/

#ifndef TLC2543_H
    #define TLC2543_H

    #include "Include.h"

    #define TLC2543_SET     1
    #define TLC2543_CLR     0

    #define TLC2543_Cs(x)   (x?(P1_5=1):(P1_5=0))
    #define TLC2543Di(x)    (x?(P1_4=1):(P1_4=0))
    #define TLC2543Clk(x)   (x?(P1_6=1):(P1_6=0))
    #define TLC2543GetDo()  P1_3
    #define TLC2543GetEoc() P1_7

    #ifdef TLC2543_GLOBAL
	    #define TLC2543_EXT
    #else
	    #define TLC2543_EXT extern
    #endif
    
    #define  nop()  _nop_()

    TLC2543_EXT uint read_TLC2543(uchar channel);
	TLC2543_EXT void _delay_us(uint us);
#endif
