#ifndef  include_H
#define  include_H 1
  #include "kongzhi.h"
  #include "keyboard.h"
  #include "pwmout.h"
   			 
  #define    key     P2   							
  #define    PWM_T   100			      //����PWM������TΪ10ms 

  #define    uchar unsigned char
  #define    uint  unsigned int
  uchar      PWM_t,PWM_t0;                //PWM_tΪ������(0~100)ʱ��Ϊ0~10ms
  uchar      flag;		//flagΪС��״̬��־,0:ֹͣ,1:ǰ��,2:����
  uchar      flag2;		//flag2ΪС��״̬�ָ��Ĵ���,��С�������ϰ���ֹͣ,�ȵ��ϰ����ų�֮��,С����ֹ֮ͣǰ��״̬�ͼĴ���flag2��
  uchar      flag3;		//flag3ΪС������ֹͣ��ʱ��־,��ʼ��Ϊ0,�ȴ��ϰ��ų�֮��ֵΪ1,��ʼ��ʱ,����֮��ָ�ֹͣǰ���н�״̬
  uchar      flag4;     //--flag4Ϊ���Ź���λ��״̬�ָ��Ĵ���
  uchar      kind = 0;	//������������ 



#endif