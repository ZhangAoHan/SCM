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

//定义Flash 操作等待时间及允许IAP/ISP/EEPROM 操作的常数
//#define ENABLE_ISP 0x80 //系统工作时钟<30MHz 时，对IAP_CONTR 寄存器设置此值
//#define ENABLE_ISP 0x81 //系统工作时钟<24MHz 时，对IAP_CONTR 寄存器设置此值
#define ENABLE_ISP 0x82 //系统工作时钟<20MHz 时，对IAP_CONTR 寄存器设置此值
//#define ENABLE_ISP 0x83 //系统工作时钟<12MHz 时，对IAP_CONTR 寄存器设置此值
//#define ENABLE_ISP 0x84 //系统工作时钟<6MHz 时，对IAP_CONTR 寄存器设置此值
//#define ENABLE_ISP 0x85 //系统工作时钟<3MHz 时，对IAP_CONTR 寄存器设置此值
//#define ENABLE_ISP 0x86 //系统工作时钟<2MHz 时，对IAP_CONTR 寄存器设置此值
//#define ENABLE_ISP 0x87 //系统工作时钟<1MHz 时，对IAP_CONTR 寄存器设置此值

void IAP_Disable();

union union_temp16
{
    INT16U un_temp16;
    INT8U  un_temp8[2];
}my_unTemp16;

//读一字节，调用前需打开IAP 功能，入口:DPTR = 字节地址，返回:A = 读出字节
INT8U byte_read(INT16U add)
{
    IAP_DATA = 0x00;
    IAP_CONTR = ENABLE_ISP;         //打开IAP 功能, 设置Flash 操作等待时间
    IAP_CMD = 0x01;                 //IAP/ISP/EEPROM 字节读命令

    my_unTemp16.un_temp16 = add;
    IAP_ADDRH = my_unTemp16.un_temp8[0];    //设置目标单元地址的高8 位地址
    IAP_ADDRL = my_unTemp16.un_temp8[1];    //设置目标单元地址的低8 位地址

    //EA = 0;
    IAP_TRIG = 0x5A;   //先送 5Ah,再送A5h 到ISP/IAP 触发寄存器,每次都需如此
    IAP_TRIG = 0xA5;   //送完A5h 后，ISP/IAP 命令立即被触发起动
    _nop_();
    //EA = 1;
    IAP_Disable();  //关闭IAP 功能, 清相关的特殊功能寄存器,使CPU 处于安全状态,
                    //一次连续的IAP 操作完成之后建议关闭IAP 功能,不需要每次都关
    return (IAP_DATA);
}

//字节编程，调用前需打开IAP 功能，入口:DPTR = 字节地址, A= 须编程字节的数据
void byte_program(INT16U add, INT8U ch)
{
    IAP_CONTR = ENABLE_ISP;         //打开 IAP 功能, 设置Flash 操作等待时间
    IAP_CMD = 0x02;                 //IAP/ISP/EEPROM 字节编程命令

    my_unTemp16.un_temp16 = add;
    IAP_ADDRH = my_unTemp16.un_temp8[0];    //设置目标单元地址的高8 位地址
    IAP_ADDRL = my_unTemp16.un_temp8[1];    //设置目标单元地址的低8 位地址

    IAP_DATA = ch;                  //要编程的数据先送进IAP_DATA 寄存器
    //EA = 0;
    IAP_TRIG = 0x5A;   //先送 5Ah,再送A5h 到ISP/IAP 触发寄存器,每次都需如此
    IAP_TRIG = 0xA5;   //送完A5h 后，ISP/IAP 命令立即被触发起动
    _nop_();
    //EA = 1;
    IAP_Disable();  //关闭IAP 功能, 清相关的特殊功能寄存器,使CPU 处于安全状态,
                    //一次连续的IAP 操作完成之后建议关闭IAP 功能,不需要每次都关
}

//擦除扇区, 入口:DPTR = 扇区地址
void sector_erase(INT16U add)
{
    IAP_CONTR = ENABLE_ISP;         //打开IAP 功能, 设置Flash 操作等待时间
    IAP_CMD = 0x03;                 //IAP/ISP/EEPROM 扇区擦除命令

    my_unTemp16.un_temp16 = add;
    IAP_ADDRH = my_unTemp16.un_temp8[0];    //设置目标单元地址的高8 位地址
    IAP_ADDRL = my_unTemp16.un_temp8[1];    //设置目标单元地址的低8 位地址

    //EA = 0;
    IAP_TRIG = 0x5A;   //先送 5Ah,再送A5h 到ISP/IAP 触发寄存器,每次都需如此
    IAP_TRIG = 0xA5;   //送完A5h 后，ISP/IAP 命令立即被触发起动
    _nop_();
    //EA = 1;
    IAP_Disable();  //关闭IAP 功能, 清相关的特殊功能寄存器,使CPU 处于安全状态,
                    //一次连续的IAP 操作完成之后建议关闭IAP 功能,不需要每次都关
}

void IAP_Disable()
{
    //关闭IAP 功能, 清相关的特殊功能寄存器,使CPU 处于安全状态,
    //一次连续的IAP 操作完成之后建议关闭IAP 功能,不需要每次都关
    IAP_CONTR = 0;      //关闭IAP 功能
    IAP_CMD   = 0;      //清命令寄存器,使命令寄存器无命令,此句可不用
    IAP_TRIG  = 0;      //清命令触发寄存器,使命令触发寄存器无触发,此句可不用
    IAP_ADDRH = 0;
    IAP_ADDRL = 0;
}