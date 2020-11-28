/*     iwdg.c    */


#include "iwdg.h"


/*************************** �ļ�˵�� *******************************/
//����:�߲ʹ���
//�˳����������߲ʹ���̫��M3��STM32F103�����弰���ּ��ݵ�STM32ϵͳ��
//�Ա�����"�߲ʹ��� ̫��M3 STM32������"���򳬸��Լ۱ȿ�������ȡ��������
//ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;��
/********************************************************************/ 



/*
����:��ʼ���������Ź�
prer:��Ƶ��:0~7(ֻ�е�3λ��Ч!)��Ƶ����=4*2^prer.�����ֵֻ����256!
rlr :��װ�ؼĴ���ֵ:��11λ��Ч.
˵��:ʱ�����(���):Tout=((4*2^prer)*rlr)/40 (ms).
*/
void IWDG_Init(u8 prer,u16 rlr) 
{	
 	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);  //ʹ�ܶԼĴ���IWDG_PR��IWDG_RLR��д����
	IWDG_SetPrescaler(prer);  //����IWDGԤ��Ƶֵ:����IWDGԤ��ƵֵΪ64
	IWDG_SetReload(rlr);  //����IWDG��װ��ֵ
	IWDG_ReloadCounter();  //����IWDG��װ�ؼĴ�����ֵ��װ��IWDG������
	IWDG_Enable();  //ʹ��IWDG
}
//
void IWDG_Init_10ms(void){
	IWDG_Init(IWDG_Prescaler_4,100);
}
//
void IWDG_Init_50ms(void){
	IWDG_Init(IWDG_Prescaler_4,500);
}
//
void IWDG_Init_200ms(void){
	IWDG_Init(IWDG_Prescaler_4,2000);
}
//
void IWDG_Init_500ms(void){
	IWDG_Init(IWDG_Prescaler_8,2500);
}
//
void IWDG_Init_1s(void){
	IWDG_Init(IWDG_Prescaler_64,625);
}
//
void IWDG_Init_2s(void){
	IWDG_Init(IWDG_Prescaler_64,1250);
}
//
void IWDG_Init_4s(void){
	IWDG_Init(IWDG_Prescaler_64,2500);
}
//
void IWDG_Init_8s(void){
	IWDG_Init(IWDG_Prescaler_128,2500);
}
//
void IWDG_Init_16s(void){
	IWDG_Init(IWDG_Prescaler_256,2500);
}

//ι�������Ź�
void IWDG_Feed(void)
{   
 	IWDG_ReloadCounter();//reload										   
}


