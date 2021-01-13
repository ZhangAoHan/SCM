#ifndef __sbit_H__
#define __sbit_H__


#include <NEW_8051.H>
#include <intrins.h>

sbit STRA=P4^3;	 //����
sbit OEA=P3^4;  //595ʹ��
sbit SDAA =P3^0;	 //����
sbit SCKA=P3^1;  //ʱ��

sbit STRB=P1^5;	 //����
sbit OEB=P1^4;  //595ʹ��
sbit SDAB=P1^6;	//����
sbit SCKB=P1^7;	//ʱ��

sbit STRC=P1^1;	 //����
sbit OEC=P1^0;  //595ʹ��
sbit SDAC=P1^2;	//����
sbit SCKC=P1^3;	//ʱ��


sbit T_CLK=P3^5;		    //DS1302��������
sbit T_IO =P3^6;
sbit T_RST=P3^7;
sbit LED=P0^3;	//����ȦLED����
#define Auto_adder 0XC8//�����ֶ� �Զ����� ��־
#define DISP_TIME_adder_L 0XC2	//��ʾģ�����ʱ�ӵ���ʱ��
#define DISP_TIME_adder_H 0XC4
extern void Round_table(uchar DISP_LINEE,uchar HourE,uchar CentE,uchar SecE );
extern void Send_data_A(unsigned char temp);	  /*�Ӵ��ڷ�������*/
extern void Send_data_B(unsigned char temp);	  /*��������*/
extern void Send_data_C(unsigned char temp);
extern void dis_picture(uchar temp_one,uchar temp_two,uchar temp_three,uchar temp_four);
extern void Send_data(unsigned char d);
extern uchar byte_read(uint);
extern void sector_erase(uint);
extern void byte_program(uint, uchar);
extern bit Scan_bit;
extern void   RTInputByte(uchar);         //* ���� 1Byte */
extern uchar  RTOutputByte(void);         //* ��� 1Byte */
extern void   W1302(uchar, uchar);        // ��DS1302д��һ���ֽ�
extern uchar  R1302(uchar);               // ��DS1302����һ���ֽ�
extern void   Set1302(uchar *pClock);
extern void   du1302();                   // ��ʱ��  
extern void   DelayMs(void);              // ��ʱ
extern void   Set(uchar,uchar );          // ��������
extern uchar starts_time[7];
extern void  write_1302Data (uchar  ucAddr,uchar  Value);
extern uint uiFontNumber;//��Ļ����
extern uchar uiFontNumber_P;
extern uchar uiFontNumber_D;
extern void Auto_Set1302(uchar *pClock);
extern uint Pt;
extern bit Auto;
#endif