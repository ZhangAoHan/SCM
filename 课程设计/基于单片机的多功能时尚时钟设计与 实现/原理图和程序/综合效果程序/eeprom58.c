#include "NEW_8051.H"
#include "task.h"	
#include <intrins.h>  
typedef unsigned char  INT8U;
typedef unsigned int   INT16U;

/*
sfr IAP_DATA    = 0xC2;
sfr IAP_ADDRH   = 0xC3;
sfr IAP_ADDRL   = 0xC4;
sfr IAP_CMD     = 0xC5;
sfr IAP_TRIG    = 0xC6;
sfr IAP_CONTR   = 0xC7;
*/

//����Flash �����ȴ�ʱ�估����IAP/ISP/EEPROM �����ĳ���
//#define ENABLE_ISP 0x80 //ϵͳ����ʱ��<30MHz ʱ����IAP_CONTR �Ĵ������ô�ֵ
//#define ENABLE_ISP 0x81 //ϵͳ����ʱ��<24MHz ʱ����IAP_CONTR �Ĵ������ô�ֵ
#define ENABLE_ISP 0x82 //ϵͳ����ʱ��<20MHz ʱ����IAP_CONTR �Ĵ������ô�ֵ
//#define ENABLE_ISP 0x83 //ϵͳ����ʱ��<12MHz ʱ����IAP_CONTR �Ĵ������ô�ֵ
//#define ENABLE_ISP 0x84 //ϵͳ����ʱ��<6MHz ʱ����IAP_CONTR �Ĵ������ô�ֵ
//#define ENABLE_ISP 0x85 //ϵͳ����ʱ��<3MHz ʱ����IAP_CONTR �Ĵ������ô�ֵ
//#define ENABLE_ISP 0x86 //ϵͳ����ʱ��<2MHz ʱ����IAP_CONTR �Ĵ������ô�ֵ
//#define ENABLE_ISP 0x87 //ϵͳ����ʱ��<1MHz ʱ����IAP_CONTR �Ĵ������ô�ֵ

void IAP_Disable();

union union_temp16
{
    INT16U un_temp16;
    INT8U  un_temp8[2];
}my_unTemp16;

//��һ�ֽڣ�����ǰ���IAP ���ܣ����:DPTR = �ֽڵ�ַ������:A = �����ֽ�
INT8U byte_read(INT16U add)
{
    IAP_DATA = 0x00;
    IAP_CONTR = ENABLE_ISP;         //��IAP ����, ����Flash �����ȴ�ʱ��
    IAP_CMD = 0x01;                 //IAP/ISP/EEPROM �ֽڶ�����

    my_unTemp16.un_temp16 = add;
    IAP_ADDRH = my_unTemp16.un_temp8[0];    //����Ŀ�굥Ԫ��ַ�ĸ�8 λ��ַ
    IAP_ADDRL = my_unTemp16.un_temp8[1];    //����Ŀ�굥Ԫ��ַ�ĵ�8 λ��ַ

    //EA = 0;
    IAP_TRIG = 0x5A;   //���� 5Ah,����A5h ��ISP/IAP �����Ĵ���,ÿ�ζ������
    IAP_TRIG = 0xA5;   //����A5h ��ISP/IAP ����������������
    _nop_();
    //EA = 1;
    IAP_Disable();  //�ر�IAP ����, ����ص����⹦�ܼĴ���,ʹCPU ���ڰ�ȫ״̬,
                    //һ��������IAP �������֮����ر�IAP ����,����Ҫÿ�ζ���
    return (IAP_DATA);
}

//�ֽڱ�̣�����ǰ���IAP ���ܣ����:DPTR = �ֽڵ�ַ, A= �����ֽڵ�����
void byte_program(INT16U add, INT8U ch)
{
    IAP_CONTR = ENABLE_ISP;         //�� IAP ����, ����Flash �����ȴ�ʱ��
    IAP_CMD = 0x02;                 //IAP/ISP/EEPROM �ֽڱ������

    my_unTemp16.un_temp16 = add;
    IAP_ADDRH = my_unTemp16.un_temp8[0];    //����Ŀ�굥Ԫ��ַ�ĸ�8 λ��ַ
    IAP_ADDRL = my_unTemp16.un_temp8[1];    //����Ŀ�굥Ԫ��ַ�ĵ�8 λ��ַ

    IAP_DATA = ch;                  //Ҫ��̵��������ͽ�IAP_DATA �Ĵ���
    //EA = 0;
    IAP_TRIG = 0x5A;   //���� 5Ah,����A5h ��ISP/IAP �����Ĵ���,ÿ�ζ������
    IAP_TRIG = 0xA5;   //����A5h ��ISP/IAP ����������������
    _nop_();
    //EA = 1;
    IAP_Disable();  //�ر�IAP ����, ����ص����⹦�ܼĴ���,ʹCPU ���ڰ�ȫ״̬,
                    //һ��������IAP �������֮����ر�IAP ����,����Ҫÿ�ζ���
}

//��������, ���:DPTR = ������ַ
void sector_erase(INT16U add)
{
    IAP_CONTR = ENABLE_ISP;         //��IAP ����, ����Flash �����ȴ�ʱ��
    IAP_CMD = 0x03;                 //IAP/ISP/EEPROM ������������

    my_unTemp16.un_temp16 = add;
    IAP_ADDRH = my_unTemp16.un_temp8[0];    //����Ŀ�굥Ԫ��ַ�ĸ�8 λ��ַ
    IAP_ADDRL = my_unTemp16.un_temp8[1];    //����Ŀ�굥Ԫ��ַ�ĵ�8 λ��ַ

    //EA = 0;
    IAP_TRIG = 0x5A;   //���� 5Ah,����A5h ��ISP/IAP �����Ĵ���,ÿ�ζ������
    IAP_TRIG = 0xA5;   //����A5h ��ISP/IAP ����������������
    _nop_();
    //EA = 1;
    IAP_Disable();  //�ر�IAP ����, ����ص����⹦�ܼĴ���,ʹCPU ���ڰ�ȫ״̬,
                    //һ��������IAP �������֮����ر�IAP ����,����Ҫÿ�ζ���
}

void IAP_Disable()
{
    //�ر�IAP ����, ����ص����⹦�ܼĴ���,ʹCPU ���ڰ�ȫ״̬,
    //һ��������IAP �������֮����ر�IAP ����,����Ҫÿ�ζ���
    IAP_CONTR = 0;      //�ر�IAP ����
    IAP_CMD   = 0;      //������Ĵ���,ʹ����Ĵ���������,�˾�ɲ���
    IAP_TRIG  = 0;      //��������Ĵ���,ʹ������Ĵ����޴���,�˾�ɲ���
    IAP_ADDRH = 0;
    IAP_ADDRL = 0;
}