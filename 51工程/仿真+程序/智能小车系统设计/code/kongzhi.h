/*******************************************************************************
* �ļ����ƣ�kongzhi.h                          
* ˵�������ļ�Ϊ����ͷ�ļ�С��������������
* ���ܣ�1.�������˿ڶ��� 
        2.kongzhi.c���õ��ĺ���˵��
* �޸ģ� ��
* �汾��1.0.0
* ���ߣ�YuanDong 
* ʱ�䣺2009.7.14 
*******************************************************************************/

#ifndef kongzhi_H
#define kongzhi_H 1

  #ifndef kongzhi_GLOBAL
    #define kongzhi_EXT  extern
  #else 
    #define kongzhi_EXT 
  #endif
   	
  #define    uchar unsigned char
  #define    uint  unsigned int	
  			
  sfr	     WDT_CONTR = 0xe1;	         //���忴�Ź���ַ
  #define    zhang_ai  P3_2
  #define	 stop_1	P1_5   	             //Ŀ��վ��1
  #define	 stop_2	P1_6	             //Ŀ��վ��2
  #define	 stop_3	P1_7	             //Ŀ��վ��3	 
  #define    timer_data  (256 - 200)     //��ʱ��Ԥ��ֵ��12Mʱ��ʱ����ʱ0.2ms
  #define	 spy		P0               //����Ѱ�����ӿ�				 
  #define    key     P2   		        					 
  #define    PWM_T   100			      //����PWM������TΪ10ms
  sbit	     PWM  = P1^0;				  //PWM�������	
  sbit	     DR   = P1^1;				      //�������	
  sbit	     ENA  = P1^2;				  //PWM�����ʹ�ܿ���
  sbit       PWM2 = P1^3;				  //PWM2������� 
  sbit	     DR2  = P1^4;				  //����2����
  
  kongzhi_EXT  void	bizhang();
  kongzhi_EXT  void  stop();
  kongzhi_EXT  void  xunji();  
  kongzhi_EXT  void  timer_init();
  kongzhi_EXT  void delay();
  kongzhi_EXT  void jieshou();
  kongzhi_EXT  uchar dulie();
  kongzhi_EXT  uchar key_board();
  kongzhi_EXT  void keyboard();

#endif