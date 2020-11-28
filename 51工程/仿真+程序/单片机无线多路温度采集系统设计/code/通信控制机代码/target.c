/*************************************************************************************
*文件名称：target.c
*说明：本文件为继电器和蜂鸣器驱动函数文件
*功能：驱动函数实例化
*修改：无
*版本：V1.0.0
*作者：YuanDong
*时间：2009.07.03
************************************************************************************/
#define  TARGET_GLOBAL  1
#include"target.h"
void relay_Init(void)
{
	 relayPort = 0;
}
void buzzer_Init(void)
{
	 buzzerPort = 0;
}
void relay_Command(bit status)
{
	relarPort = status;
}
void buzzer_Command(bit status)
{
	buzzerPort = status;
}
