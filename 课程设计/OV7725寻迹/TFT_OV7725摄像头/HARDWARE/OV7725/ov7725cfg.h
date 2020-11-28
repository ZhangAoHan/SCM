#ifndef _OV7725CFG_H
#define _OV7725CFG_H
#include "ov7725.h"	
//////////////////////////////////////////////////////////////////////////////////
//ALIENTEK战舰STM32开发板
//OV7725 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2017/11/1
//版本：V1.0		    							    							  
//////////////////////////////////////////////////////////////////////////////////
                                                                            //初始值
/* OV7725寄存器宏定义 */
#define GAIN      0x00      //自动增益控制-增益控制增益设置              00
#define BLUE      0x01   //AWB–蓝色通道增益设置                            80
#define RED       0x02                                                       80
#define GREEN     0x03  											//	00
#define BAVG      0x05   //U/B 平均水平基于芯片输出格式自动更新
#define GAVG      0x06   //y/gb 平均水平基于芯片输出格式自动更新
#define RAVG      0x07   //V/R 平均水平基于芯片输出格式自动更新
#define AECH      0x08    //曝光值
#define COM2      0x09    //第4位  睡眠模式   1-0位  输出驱动能力 （00-11  1-4）
#define PID       0x0A
#define VER       0x0B
#define COM3      0x0C   //第7位：垂直反正图像   第6位：水平镜像   第5位：在RGB输出模式下交换B / R输出序列  第4位：MSB/LSB交换输出   第0位：传感器色带测试图案输出启用
#define COM4      0x0D   //7-6位：锁相环频率控制   第5-4位：窗口设置（00：满屏）
#define COM5      0x0E  //第7位：自动帧率控制开/关选择(夜间模式)  第6位：自动帧率控制速度选择 第5-4：自动帧速率最大速率控制（00：全速） 第3-2位：自动帧率主动点控制（00：不允许）  第0位“最大步长控制（0：AEC增加步骤有限制  1：对AEC增加步骤没有限制）
#define COM6      0x0F  //第0位：格式化时自动窗口设置开/关选择变化
#define AEC       0x10   //曝光值
#define CLKRC     0x11   //时钟设置  第6位：直接使用外部时钟(没有时钟预缩放可用)
#define COM7      0x12  //第7位：SCCB 寄存器复位（将所有寄存器设为默认值）  第6位：输出格式（0：VGA  1:QVGA）第5位：bt. 656协议开/关选择  第3-2位：RGB输出设置（01:565）  第1-0位：数据输出格式选择（10：RGB）
#define COM8      0x13  //7：启用快速自动增益控制   6：步长限制（0：步长限于垂直空白  1：无限步长）  5：过滤器开/关  4：启用带值以下的AEC   3：精细自动控制开关控制  2-0：AGC AWB AEC使能 
#define COM9      0x14   //7：基于直方图或平均值的AEC / AGC选择   6-4：自动增益上限  2-1：丢弃损坏帧的VSYNC/HREF输出
#define COM10     0x15   // 7：输出负数据   6：HREF对同步码更改  5：输出选项（0：自由运行  1：在水平空白期间，PCLK不会切换） 4-3：PCLK HREF反相  2：数据记录方式（0：PCLK上升沿记录  1“下降沿记录）   0：输出数据范围选择（0：满量程）
#define REG16     0x16
#define HSTART    0x17
#define HSIZE     0x18
#define VSTRT     0x19
#define VSIZE     0x1A
#define PSHFT     0x1B
#define MIDH      0x1C
#define MIDL      0x1D
#define LAEC      0x1F
#define COM11     0x20
#define BDBase    0x22
#define BDMStep   0x23
#define AEW       0x24
#define AEB       0x25
#define VPT       0x26
#define REG28     0x28
#define HOutSize  0x29
#define EXHCH     0x2A
#define EXHCL     0x2B
#define VOutSize  0x2C
#define ADVFL     0x2D     //垂直同步中插入虚拟行的LSB ( 1位等于1行)
#define ADVFH     0x2E    //垂直同步插入虚拟行的MSB
#define YAVE      0x2F
#define LumHTh    0x30
#define LumLTh    0x31
#define HREF      0x32
#define DM_LNL    0x33
#define DM_LNH    0x34
#define ADoff_B   0x35
#define ADoff_R   0x36
#define ADoff_Gb  0x37
#define ADoff_Gr  0x38
#define Off_B     0x39
#define Off_R     0x3A
#define Off_Gb    0x3B
#define Off_Gr    0x3C
#define COM12     0x3D
#define COM13     0x3E
#define COM14     0x3F
#define COM16     0x41
#define TGT_B     0x42
#define TGT_R     0x43
#define TGT_Gb    0x44
#define TGT_Gr    0x45
#define LC_CTR    0x46
#define LC_XC     0x47
#define LC_YC     0x48
#define LC_COEF   0x49
#define LC_RADI   0x4A
#define LC_COEFB  0x4B 
#define LC_COEFR  0x4C
#define FixGain   0x4D
#define AREF1     0x4F
#define AREF6     0x54
#define UFix      0x60   //u通道固定值输出
#define VFix      0x61   //v通道固定值输出
#define AWBb_blk  0x62
#define AWB_Ctrl0 0x63
#define DSP_Ctrl1 0x64
#define DSP_Ctrl2 0x65
#define DSP_Ctrl3 0x66
#define DSP_Ctrl4 0x67
#define AWB_bias  0x68
#define AWBCtrl1  0x69
#define AWBCtrl2  0x6A
#define AWBCtrl3  0x6B
#define AWBCtrl4  0x6C
#define AWBCtrl5  0x6D
#define AWBCtrl6  0x6E
#define AWBCtrl7  0x6F
#define AWBCtrl8  0x70
#define AWBCtrl9  0x71
#define AWBCtrl10 0x72
#define AWBCtrl11 0x73
#define AWBCtrl12 0x74
#define AWBCtrl13 0x75
#define AWBCtrl14 0x76
#define AWBCtrl15 0x77
#define AWBCtrl16 0x78
#define AWBCtrl17 0x79
#define AWBCtrl18 0x7A
#define AWBCtrl19 0x7B
#define AWBCtrl20 0x7C
#define AWBCtrl21 0x7D 
#define GAM1      0x7E
#define GAM2      0x7F
#define GAM3      0x80
#define GAM4      0x81
#define GAM5      0x82
#define GAM6      0x83
#define GAM7      0x84
#define GAM8      0x85
#define GAM9      0x86
#define GAM10     0x87
#define GAM11     0x88
#define GAM12     0x89
#define GAM13     0x8A
#define GAM14     0x8B
#define GAM15     0x8C
#define SLOP      0x8D
#define DNSTh     0x8E
#define EDGE0     0x8F
#define EDGE1     0x90
#define DNSOff    0x91
#define EDGE2     0x92
#define EDGE3     0x93
#define MTX1      0x94
#define MTX2      0x95
#define MTX3      0x96
#define MTX4      0x97
#define MTX5      0x98
#define MTX6      0x99
#define MTX_Ctrl  0x9A
#define BRIGHT    0x9B
#define CNST      0x9C
#define UVADJ0    0x9E
#define UVADJ1    0x9F
#define SCAL0     0xA0
#define SCAL1     0xA1
#define SCAL2     0xA2
#define SDE       0xA6   //特效设置    6：负片   5：灰度图像    2：对比度/亮度 启用   1：饱和度使能   0：色度使能
#define USAT      0xA7
#define VSAT      0xA8
#define HUECOS    0xA9
#define HUESIN    0xAA
#define SIGN      0xAB
#define DSPAuto   0xAC

//初始化寄存器序列及其对应的值
const u8 ov7725_init_reg_tb1[][2]= 
{   
	/*输出窗口设置*/
	{CLKRC,     0x00}, //clock config
	{COM7,      0x06}, //VGA RGB565
	{HSTART,    0x3f}, //水平起始位置
	{HSIZE,     0x50}, //水平尺寸
	{VSTRT,     0x03}, //垂直起始位置
	{VSIZE,     0x78}, //垂直尺寸
	{HREF,      0x00},
	{HOutSize,  0x50}, //输出尺寸
	{VOutSize,  0x78}, //输出尺寸
	
	/*DSP control*/
	{TGT_B,     0x7f},
	{FixGain,   0x09},
	{AWB_Ctrl0, 0xe0},
	{DSP_Ctrl1, 0xff},
	{DSP_Ctrl2, 0x00},
	{DSP_Ctrl3,	0x00},
	{DSP_Ctrl4, 0x00},

	/*AGC AEC AWB*/
	{COM8,		0xf0},
	{COM4,		0xc1}, /*Pll AEC CONFIG*/
	{COM6,		0xc5},
	{COM9,		0x11},
	{BDBase,	0x7F},
	{BDMStep,	0x03},
	{AEW,		0x40},
	{AEB,		0x30},
	{VPT,		0xa1},
	{EXHCL,		0x9e},
	{AWBCtrl3,  0xaa},
	{COM8,		0xff},
	
	/*matrix shapness brightness contrast*/
	{EDGE1,		0x08},
	{DNSOff,	0x01},
	{EDGE2,		0x03},
	{EDGE3,		0x00},
	{MTX1,		0xb0},
	{MTX2,		0x9d},
	{MTX3,		0x13},
	{MTX4,		0x16},
	{MTX5,		0x7b},
	{MTX6,		0x91},
	{MTX_Ctrl,  0x1e},
	{BRIGHT,	0x08},
	{CNST,		0x20},
	{UVADJ0,	0x81},
	{SDE, 		0X06},
	{USAT,		0x65},
	{VSAT,		0x65},
	{HUECOS,	0X80},
	{HUESIN, 	0X80},
	
    /*GAMMA config*/
	{GAM1,		0x0c},
	{GAM2,		0x16},
	{GAM3,		0x2a},
	{GAM4,		0x4e},
	{GAM5,		0x61},
	{GAM6,		0x6f},
	{GAM7,		0x7b},
	{GAM8,		0x86},
	{GAM9,		0x8e},
	{GAM10,		0x97},
	{GAM11,		0xa4},
	{GAM12,		0xaf},
	{GAM13,		0xc5},
	{GAM14,		0xd7},
	{GAM15,		0xe8},
	{SLOP,		0x20},
 
	{COM3,		0x50},/*Horizontal mirror image*/
					  //注：datasheet默认0x10,即改变YUV为UVY格式。但是摄像头不是芯片而是模组时，
					  //要将0X50中的bit4,由1变成0，即设置YUV格式。
	/*night mode auto frame rate control*/ 
	{COM5,		0xf5},	 /*在夜视环境下，自动降低帧率，保证低照度画面质量*/
	//{COM5,		0x31},	/*夜视环境帧率不变*/
	
};

#endif



















