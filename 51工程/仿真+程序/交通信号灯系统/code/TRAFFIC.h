#include	<reg52.h>
#ifndef TRAFFIC_H
#define TRAFFIC_H  1
   #ifndef TRAFFIC_GLOBAL  
            #define TRAFFIC_EXT extern
   #else	
            #define TRAFFIC_EXT		  
   #endif	
#define	uchar	unsigned char
#define	uint	unsigned int
/*****�������λ**********************/
sbit    Time_Show_LED2=P2^5;    //Time_Show_LED2����λ
sbit    Time_Show_LED1=P2^4;    //Time_Show_LED1����λ
sbit	EW_LED2=P2^3;	        //EW_LED2����λ
sbit	EW_LED1=P2^2;	        //EW_LED1����λ
sbit	SN_LED2=P2^1;	        //SN_LED2����λ
sbit	SN_LED1=P2^0;	        //SN_LED1����λ
sbit    SN_Yellow=P1^6;         //SN�Ƶ�
sbit    EW_Yellow=P1^2;         //EW�Ƶ�
sbit    EW_Red=P1^3;            //EW���
sbit    SN_Red=P1^7;            //SN���
sbit    QZ_SN_LED=P3^0;         //SN����ǿ��ֱ��ָʾ��
sbit    QZ_EW_LED=P3^1;         //EW����ǿ��ֱ��ָʾ��	
sbit    Add_Button=P3^4;        //ʱ���
sbit    Reduces_Button=P3^5;    //ʱ��� 
sbit    QZ_EW_Btton=P3^6;       //EW����ǿ��ֱ�а���
sbit    QZ_SN_Btton=P3^7;       //SN����ǿ��ֱ�а��� 
bit     Flag_SN_Yellow;         //SN�ƵƱ�־λ
bit     Flag_EW_Yellow;         //EW�ƵƱ�־λ
bit     QZ_EW;
bit     QZ_SN;
char	Time_EW;                //�������򵹼�ʱ��Ԫ
char	Time_SN;                //�ϱ����򵹼�ʱ��Ԫ
uchar EW=60,SN=40,EWL=19,SNL=19; //�����ʼ����ֵ������ģʽ
uchar EW1=60,SN1=40,EWL1=19,SNL1=19;
                                //���ڴ���޸�ֵ�ı���
uchar code table[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
                                //1~~~~9��ѡ��
uchar code LIGHT[8]={0X28,0X48,0X18,0X48,0X82,0X84,0X81,0X84};
                                //��ͨ�źŵƿ��ƴ���
TRAFFIC_EXT void Delay(uchar );
TRAFFIC_EXT	void Display(void);
#endif