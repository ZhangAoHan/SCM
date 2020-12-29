#include "sin_dds.h"

uchar i,j;
uint counter,step;

/**************��ʱ��0��ʼ��**********************************/
void Init_Timer0(void)
{
   TMOD = (TMOD & 0XF0) | 0X01; 	//��ʱ��0����ʽ1
   TH0 = 0xff;						//��ʱ����ֵ
   TL0 = 0xff; 
   TR0 =1; 							//������ʱ��0
   ET0 =1;							//����ʱ��0�ж�
}

/*************************������*********************************/
main()
{
   Init_Timer0();				    //��ʱ��0��ʼ��
   step=2;							//��ֵ����������ʼ��
   EA = 1;							//CPU���ж�
 	while(1)						
	{
		if(key_up == 0) if(step<4096) step++;	 //��ֵ����������1������Ƶ�ʱ�� �����Ҳ����ڱ�С
		if(key_dw == 0) if(step>1) step--;		 //��ֵ����������1������Ƶ�ʱ�� �����Ҳ����ڱ��
		while((!key_up)||(!key_dw));			     //����һ��������ȥ�������Ҳ�����ʼ�ձ��ֲ���
 	}
}
/******************ϵͳOS��ʱ�жϷ���***************************/
void OS_Timer0(void) interrupt 1 using 2
{													   
   TH0 = 0xff;									  //��װ��ʱ����ֵ
   TL0 = 0xff; 									  
   counter = counter + step;					  //counter��step�Ĳ�������
   dac1=type[(unsigned int)counter>>8];			  //��counter����(256/step)��ʱ��dac1�Ĳ���ֵ�仯һ��
}
