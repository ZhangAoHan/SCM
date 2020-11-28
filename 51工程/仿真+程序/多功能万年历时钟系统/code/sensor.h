#ifndef SENSOR_H
#define SENSOR_H
#include "Include.h"
#ifndef SENSOR_GLOBAL
  #define SENSOR_EXT extern
#else
  #define SENSOR_EXT
#endif
/***************************DS18B20管脚配置*******************************/
sbit dq = P2 ^ 1; 
SENSOR_EXT void Sensor_Delay(uchar count);          //延时函数
SENSOR_EXT uchar Sensor_Read_Byte(void);            //从DS18B20读一个字节
SENSOR_EXT void Sensor_Write_Byte(uchar temp) ;     //向DS18B20写一个字节
SENSOR_EXT uchar Sensor_Initial(void);              //DS18B20初始化
SENSOR_EXT void Sensor_Fresh(uchar * temperature ); //读取并显示温度
#endif
