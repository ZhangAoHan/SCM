
#include "task.h"
bit new_code;
/*�ṹ��*/      /* ����һ�ν������յ������ֽ�����*/
static struct IR_data    //������յ����ݽṹ
{
    unsigned char addr1;     // ��ַ1(�ͻ���1)
    unsigned char addr2;     // ��ַ2(�ͻ���2)
    unsigned char data1;     // ����1(������)
    unsigned char data2;     // ����2(�����뷴��)
} IR_DATA;
#define GTime 53                
#define CTime 114               
#define D0MinTime 4  
#define D0MaxTime 9  
#define D1MinTime 11  
#define D1MaxTime 16             
#define TimeOut_cnt 250 
/*ȫ�ֹ�������*/
 unsigned char T0_CNT;                // ��ʱ������ֵ
 unsigned char T0_CNT_bk;           // ��������
 bit TimeOut;                     // ��ʱ��־
 bit Guide;                           // ��������Ч
 bit Continuous;                      // ��_����
 unsigned char xdata IR_Time[33]; // ����ÿ�����½���֮���ʱ����
uchar key_code;
/*********************************************************************************************
/*Timer1�ж��ӳ���*/
void TR1_Service(void) interrupt 3 using 2
{
    //static unsigned char  T;
  //  T++;
  //  if(T>1)
  //  {
      //  T=0;
        T0_CNT ++;
  //  }
    if(T0_CNT > TimeOut_cnt)
    {
        TimeOut = 1;       // ��ʱ��־
    }
}
/***********************************************************************/
/*������ĳ���*/
void Decode(void)
{
    unsigned char i=0x00,j,k;
    static unsigned char *p;  // ָ��ṹ��IR_DATA.XX��ָ��
    EX1 = 0;   // ���ⲿ�ж�1
    /*/////////////////////////���н��봦��////////////////////////*/
    p = &IR_DATA.addr1;
    for(k=0; k<4; k++)
    {
        for(j=0; j<8; j++)
        {
            if((IR_Time[i]>D0MinTime) & (IR_Time[i]<D0MaxTime))
            {
                *p >>= 1;           // ����1λ��
                *p &= 0x7f;         // ��0111 1111��0. ���ݡ�0�� 0.56ms�͵�ƽ+0.56ms�ߵ�ƽ
            }
            else if((IR_Time[i]>D1MinTime) & (IR_Time[i]<D1MaxTime))
            {
                *p >>= 1;                // ����1λ��
                *p |= 0x80;              // ��1000 0000��1. ���ݡ�1�� 0.56ms�͵�ƽ+1.69ms�ߵ�ƽ
            }
            i ++;
        }
        p ++;
    }
    if(IR_DATA.data2+IR_DATA.data1==0XFF)
    {
        key_code=IR_DATA.data1;
		new_code=1;
    }
    else
    {
        key_code=0XFF;   /**�Ǳ���ң���������ݴ���**/
    };
    /*/////////////////////////���봦�����////////////////////////*/
    EX1 = 1;   // ���¿����ⲿ�ж�1
} 
void serviceINT0(void) interrupt 2 using 1  //{////�ⲿ�ж�1���жϺ��������ں����߶�����
{
    static unsigned char m=0;
	TR1=1;
	
    T0_CNT_bk = T0_CNT;     // ����ʱ�����ֵ����ǰһ���½��ص����½��ص�ʱ����
    T0_CNT = 0x00;          // ���ʱ�����ֵ
    if(TimeOut)             // �����ʱ
    {
        //  TL0 = TIMER0_COUNT;     // ��ʼ����ʱ��0       ��0x1f��31��
        TimeOut = 0;        // �����ʱ��־
        m = 0;              // ��λ����λ
        T0_CNT = 0x00;      // ���ʱ�����ֵ
        Guide = 0;          // ���������־
        Continuous = 0;     // �����_����־
    }
    else       // ��������ʱ��58.5ms��76.5ms
    {
        if(Guide | Continuous)          // �����������Ч
        {
            IR_Time[m++] = T0_CNT_bk;       // ����ʱ����
            if(m == 32)   // ���չ�32���ݺ�
            {
                m = 0;
                Guide = 0;    // ���������־
				 //new_code=1;
				TR1=0;
                /*���н������*/
                Decode();     // ����
					
            }
        }
        if(T0_CNT_bk > GTime)   // ���ʱ����>������ʱ��
        {
            Guide = 1;          // ʹ��������־
            m = 0;
        };
        if(T0_CNT_bk > CTime)    // ���ʱ����>��_����ʱ��
        {
            Continuous = 1;      // ʹ����_����־
            m = 0;
        }
    }//end of ��ʱ
}
/*********************************************************************************/
/*************************************************************************************
************************************************************************************
***********************                                     ***************************
***********************    http://59tiaoba.taobao.com       ***************************
***********************                                     ***************************
************************************�����д��Fucp****************************************
**********************************************************************************/