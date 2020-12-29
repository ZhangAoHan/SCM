/**************************************************************************************
                                TLC2543驱动程序
功能:12位AD采样芯片驱动.
说明:芯片开始时第一次采样数据无效
     芯片采样口起始编号为:0
	 采样速度：11.0592MHz AVR16L －0s优化模式  (25us)
作者:wayne
时间:2007-11-01
版本:0.1.0
//----------------------------------------------------------
移植:系统从GCC上移植到IAR上.
作者:wayne
时间:2007-11-01
版本:0.1.0
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
