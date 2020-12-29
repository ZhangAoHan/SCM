#ifndef SENSOR_H
#define SENSOR_H
#include "Include.h"
#ifndef SENSOR_GLOBAL
  #define SENSOR_EXT extern
#else
  #define SENSOR_EXT
#endif
/***************************DS18B20�ܽ�����*******************************/
sbit dq = P2 ^ 1; 
SENSOR_EXT void Sensor_Delay(uchar count);          //��ʱ����
SENSOR_EXT uchar Sensor_Read_Byte(void);            //��DS18B20��һ���ֽ�
SENSOR_EXT void Sensor_Write_Byte(uchar temp) ;     //��DS18B20дһ���ֽ�
SENSOR_EXT uchar Sensor_Initial(void);              //DS18B20��ʼ��
SENSOR_EXT void Sensor_Fresh(uchar * temperature ); //��ȡ����ʾ�¶�
#endif
