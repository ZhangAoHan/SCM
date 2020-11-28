/*  main.c  */

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "ezio.h"
#include "key.h"

#include "LcdApi.h"
#include "LcdBsp.h"
#include "touch.h"




/*************************** �ļ�˵�� *******************************/
//ezio ��Ƭ��IO��������������װ,������������д�߳��Ľṹ��,һ�������㶨
//��Arduinoһ������IO
//�˳����������߲ʹ���̫��M3��STM32F103�����弰���ּ��ݵ�STM32ϵͳ��
//�Ա�����"�߲ʹ��� ̫��M3 STM32������"���򳬸��Լ۱ȿ�������ȡ��������
//ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;��
/********************************************************************/ 





#define COLOR_COUNT 8


u16 CurrentColor=RED;//������ɫ
u16 ColorList[COLOR_COUNT]={BLACK,BLUE,BRED,YELLOW,GBLUE,RED,GREEN,CYAN};//��ɫ����ɫ�б�




//����ɫ��
void Draw_Palette(void){
	u8 i=0;
	//u32 u32_t=0;
	LCD_Fill(5,5,35,35,RED);
	LCD_DrawRectangle(5,5,35,35);
	
	for(i=0;i<COLOR_COUNT;i++){
		LCD_Fill(i*24+40,5,i*24+40+20,25,ColorList[i]);
		//LCD_DrawRectangle(5,5,35,35);
	}
}
//������
void Draw_Canvas(void){
	POINT_COLOR=YELLOW;//��������Ϊ��ɫ
	LCD_DrawRectangle(0,40,240-1,320-1);
	LCD_DrawRectangle(1,41,240-2,320-2);
	POINT_COLOR=BLACK;//��������Ϊ��ɫ
	LCD_DrawRectangle(2,42,240-3,320-3);
}




int main(void)
{
	u8 i=0;
	delay_init();	    //��ʱ������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	USART1_Init(115200);//����1��ʼ��
	
	LCD_Init();    //LCD��ʼ��
	TP_Init();     //��������ʼ��,ע�������õ���24C02���洢У׼����,�����Ҫ24C02������֧��,��ֲ��ʱ��ע��
	
	Draw_Palette();  //����ɫ��
	Draw_Canvas();   //������
	
	while(1)
	{
		//��Ļɨ��
		TP_Scan(0);
		if(tp_dev.sta&TP_PRES_DOWN)			//������������
		{
			if(tp_dev.y<45){   //�ڵ�ɫ������
				if(tp_dev.x>45 && tp_dev.x<(240-2) && tp_dev.y>5 && tp_dev.y<25){//��ɫѡ����,������ˢ��ɫ
					i=(tp_dev.x-45)/24;     //��ȡ��ѡ��ĵ�ɫ����ɫ������
					CurrentColor=ColorList[i];
					LCD_Fill(5,5,35,35,CurrentColor);
					POINT_COLOR=BLACK;
					LCD_DrawRectangle(5,5,35,35);
				}
				else if(tp_dev.x>5 && tp_dev.x<35 && tp_dev.y>5 && tp_dev.y<35){//��ˢ��ɫָʾ��,���������ջ���
					LCD_Fill(3,43,240-4,320-4,WHITE);
				}
			}
			else if(tp_dev.y<315){                                 //��������
				TP_Draw_Big_Point(tp_dev.x,tp_dev.y,CurrentColor);		//��ͼ
			}
		}
		else {
			delay_ms(10);	//û�а������µ�ʱ��
		}
		
		//����ɨ��
		switch(Key_Scan(0)){
			case KEY0_PRES:{//KEY0 ����
				if(Key_GetSta(KEY2)){//����ͬʱ���²���,��סKEY2 �ٰ�KEY0
					
				}
				else{                 //ֻ��KEY0����
					LCD_Clear(WHITE);   //����
					TP_Adjust();         //��ĻУ׼ 
					TP_Save_Adjdata();
					NVIC_SystemReset();  //У׼��� , ����,
				}
				break;
			}
			case KEY1_PRES:{//KEY1 ����
				
				break;
			}
			case KEY2_PRES:{//KEY2 ����
				
				break;
			}
			case WKUP_PRES:{//KEY3 ����
				
				break;
			}
		}
		
	}
}




