/*****************************************************************************************
*ds18b20.hͷ�ļ�											
*����: ds18b20��������������                                 
*���ߣ�yd                                         
*ʱ�䣺09.07.03                                     
*�汾��1.0                      
*****************************************************************************************/
#ifndef DS18B20_H
#define DS18B20_H
  #include "Include.h"
  #ifndef DS18B20_GLOBAL
    #define DS_EXT extern
  #else 
    #define DS_EXT
  #endif
/************ds18b20�˿ڶ���*****************/
  sbit DQ=P1^0;
  DS_EXT uchar ds18b20_readdata(void);
  DS_EXT void ds18b20_init(void);
  DS_EXT void ds18b20_writecommand(uchar command);
  DS_EXT void temperature_process(uchar,uchar);
  DS_EXT bit match_rom(uchar *rom);
#endif
