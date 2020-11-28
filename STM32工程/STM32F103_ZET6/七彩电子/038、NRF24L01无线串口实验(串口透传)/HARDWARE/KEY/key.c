
/*  key.c  */


#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"

/***********************************************************************/
//�˳����������߲ʹ���̫��M3��STM32F103�����弰���ּ��ݵ�STM32ϵͳ��
//ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;��
/***********************************************************************/


u8 Key_Sta[4]={0};//������״̬


//������ʼ������
void Key_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(KEY0_RCC_CLK|KEY1_RCC_CLK|KEY2_RCC_CLK|KEY3_RCC_CLK,ENABLE);//ʹ��PORTA,PORTEʱ��

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;//KEY0-KEY2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIOE2,3,4

	//��ʼ�� WK_UP-->GPIOA.0	  ��������
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0���ó����룬Ĭ������	  
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.0

}


//������������������
//���ذ���ֵ
//0��û���κΰ�������
//1��KEY0����
//2��KEY1����
//3��KEY2���� 
//4��KEY3���� WK_UP
//ע��˺���֧�ֶఴ��ͬʱ���¼��,
//��ͬʱ����ʱ����Ӧ���ȼ�,KEY0>KEY1>KEY2>KEY3!!
//mode  ����,��㴫��һ��ֵ��OK
//
u8 Key_Scan(u8 mode)
{
	//key0
	if(Key_Sta[0]==0){
		if(KEY0_HARD_STA){
			delay_ms(10);
			if(KEY0_HARD_STA){
				Key_Sta[0]=1;
				return KEY0_PRES;
			}
		}
	}
	else{
		if(!(KEY0_HARD_STA)){
			Key_Sta[0]=0;
		}
	}
//KEY1
	if(Key_Sta[1]==0){
		if(KEY1_HARD_STA){
			delay_ms(10);
			if(KEY1_HARD_STA){
				Key_Sta[1]=1;
				return KEY1_PRES;
			}
		}
	}
	else{
		if(!(KEY1_HARD_STA)){
			Key_Sta[1]=0;
		}
	}	
	//Key2
	if(Key_Sta[2]==0){
		if(KEY2_HARD_STA){
			delay_ms(10);
			if(KEY2_HARD_STA){
				Key_Sta[2]=1;
				return KEY2_PRES;
			}
		}
	}
	else{
		if(!(KEY2_HARD_STA)){
			Key_Sta[2]=0;
		}
	}	
	
	//KEY3
	if(Key_Sta[3]==0){
		if(KEY3_HARD_STA){
			delay_ms(10);
			if(KEY3_HARD_STA){
				Key_Sta[3]=1;
				return WKUP_PRES;
			}
		}
	}
	else{
		if(!(KEY3_HARD_STA)){
			Key_Sta[3]=0;
		}
	}	
	
 	return 0;// �ް�������
}

//��ȡ�����ĵ�ǰ״̬
u8 Key_GetSta(u8 key){
	if(key<=3){
		return Key_Sta[key];
	}
	return 0;
}























