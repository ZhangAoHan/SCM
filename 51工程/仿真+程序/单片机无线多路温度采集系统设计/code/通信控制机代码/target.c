/*************************************************************************************
*�ļ����ƣ�target.c
*˵�������ļ�Ϊ�̵����ͷ��������������ļ�
*���ܣ���������ʵ����
*�޸ģ���
*�汾��V1.0.0
*���ߣ�YuanDong
*ʱ�䣺2009.07.03
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
