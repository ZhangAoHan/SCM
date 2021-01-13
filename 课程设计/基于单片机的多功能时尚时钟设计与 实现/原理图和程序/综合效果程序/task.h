#ifndef __task_H__
#define __task_H__

#include "sbit.h"

#define EN_OS_INT0
#define EN_OS_TIMER0
#define EN_OS_INT1
#define EN_OS_TIMER1
#define EN_OS_SERIAL
//#define EN_OS_UART2
#define EN_OS_PCA0
#define LINE_ADJ_adder 0XC0     //��ʾģ�����ʱ���м�����У��ֵ
#define ucNumAdder 0XC6//������Ļ����

#define DEC2BCD(X) ((X/10)<<4 | (X%10))               //���ڽ�ʮ����ת��BCD��ĺ�
#define BCD2DEC(X) (((X&0xF0)>>4)*10 + (X&0x0F))      //���ڽ�BCD��ת��ʮ���Ƶĺ�
//#define EN_OS_PCA1 


/************task.c****************************/
extern void delay(unsigned char n);
extern bit BIT_timeout;
extern data uint i;
extern data uint uiAddressCount;
extern  uchar BuffCount;
extern data uint uiBaseAddress;
/************zimo.c*************************/
extern uchar code picture[][4];
extern uchar code zimo_num1[];
extern const uchar code tab[11][16];
extern const uchar code tab1[12][16];
extern const uchar code _8X8Number[13][8];
extern uint uiFontNumber;
extern const uchar code shuzi[11][8];
/**************zimo_donghua.c*****************************/
extern uchar code two_heart[][4];
extern uchar code hudie[][4];
/***********IR_Receive.c**************************/
extern bit new_code;
extern uchar key_code;
extern void Ircordpro(void);//������ֵ������
/*************ShowTime.c**************************************/
extern uchar id;
extern void display(void);
extern bit flag;
/***************DS1302.c****************************************/
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
extern uchar Sec;
extern uchar Cent;
extern uchar Hour;
extern uchar Year;
extern uchar Day;
extern uchar Week;
extern uchar Month;
extern void Auto_Set1302(uchar *pClock);
/******************eeprom.c**********************/
extern uchar byte_read(uint);
extern void sector_erase(uint);
extern void byte_program(uint, uchar);
/*********************uart.c*********************/
extern uchar ucTimeOut;
extern uchar ucControlCode;
extern uchar ucLength;
extern bit uart_rBIT;
extern uchar ReceVeryfy;
extern data uint uiAddressCount;
extern uchar ReceState;
extern uchar ucDataBuff[220];
extern uchar ucUdateTime;
extern uchar ReceCount;
extern void Send_data(unsigned char d);	
/*********************DS18B20.c*********************/
extern uint tvalue;//�¶�ֵ
extern read_temp();/*��ȡ�¶�ֵ��ת��*/
#endif
/************************************************/