#include<reg51.h>
#include<absacc.h>

#ifndef  sin_dds_H
  #define  sin_dds_H 1
  #define uchar unsigned char 
  #define uint	unsigned int
  #define dac1 XBYTE[0xdfff]	// X ��0832һ�������ַ
  sbit key_up = P3^2;
  sbit key_dw = P3^3;

unsigned char code type[256]={	 //
0x80,0x83,0x86,0x89,0x8c,0x8f,0x92,0x95,0x98,0x9c,0x9f,0xa2,0xa5,0xa8,0xab,0xae,0xb0,0xb3,0xb6,0xb9,
0xbc,0xbf,0xc1,0xc4,0xc7,0xc9,0xcc,0xce,0xd1,0xd3,0xd5,0xd8,0xda,0xdc,0xde,0xe0,0xe2,0xe4,0xe6,0xe8,
0xea,0xec,0xed,0xef,0xf0,0xf2,0xf3,0xf4,0xf6,0xf7,0xf8,0xf9,0xfa,0xfb,0xfc,0xfc,0xfd,0xfe,0xfe,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xfe,0xfd,0xfc,0xfc,0xfb,0xfa,0xf9,0xf8,0xf7,
0xf6,0xf5,0xf3,0xf2,0xf0,0xef,0xed,0xec,0xea,0xe8,0xe6,0xe4,0xe3,0xe1,0xde,0xdc,0xda,0xd8,0xd6,0xd3,
0xd1,0xce,0xcc,0xc9,0xc7,0xc4,0xc1,0xbf,0xbc,0xb9,0xb6,0xb4,0xb1,0xae,0xab,0xa8,0xa5,0xa2,0x9f,0x9c,
0x99,0x96,0x92,0x8f,0x8c,0x89,0x86,0x83,0x80,0x7d,0x79,0x76,0x73,0x70,0x6d,0x6a,0x67,0x64,0x61,0x5e,
0x5b,0x58,0x55,0x52,0x4f,0x4c,0x49,0x46,0x43,0x41,0x3e,0x3b,0x39,0x36,0x33,0x31,0x2e,0x2c,0x2a,0x27,
0x25,0x23,0x21,0x1f,0x1d,0x1b,0x19,0x17,0x15,0x14,0x12,0x10,0xf,0xd,0xc,0xb,0x9,0x8,0x7,0x6,0x5,0x4,
0x3,0x3,0x2,0x1,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x1,0x2,0x3,0x3,0x4,0x5,0x6,0x7,
0x8,0x9,0xa,0xc,0xd,0xe,0x10,0x12,0x13,0x15,0x17,0x18,0x1a,0x1c,0x1e,0x20,0x23,0x25,0x27,0x29,0x2c,
0x2e,0x30,0x33,0x35,0x38,0x3b,0x3d,0x40,0x43,0x46,0x48,0x4b,0x4e,0x51,0x54,0x57,0x5a,0x5d,0x60,0x63,
0x66,0x69,0x6c,0x6f,0x73,0x76,0x79,0x7c};


#endif