#include <stdio.h>

unsigned char bitmap[] = //128*40 ͼƬ
{
0xFF,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,
0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,
0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,
0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,
0x03,0x03,0x03,0x03,0x03,0xFF,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0xFC,0x02,0x02,
0xE2,0x12,0x0A,0x4A,0xEA,0x0A,0x0A,0x12,0xE2,0x02,0x02,0x02,0x82,0xC2,0xE2,0xC2,
0x82,0x02,0x02,0x02,0xFC,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0xFF,0x00,
0x00,0x00,0xFF,0x00,0xFF,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x0F,0x00,0x00,0xFF,
0xFF,0xC0,0xE0,0x40,0xE0,0xA0,0x44,0x04,0x90,0xF0,0xE0,0x00,0xC0,0xFC,0xFE,0xFE,
0x27,0x23,0x21,0x61,0x21,0x22,0x3E,0x00,0x00,0x00,0xF8,0xF8,0x9C,0x8C,0x0C,0x0C,
0x0C,0x98,0x00,0x00,0x7C,0xFA,0x63,0xE1,0x80,0x00,0x00,0x00,0x1C,0x00,0x00,0x80,
0x40,0x40,0x40,0xC0,0x80,0x80,0x00,0x00,0x00,0xC0,0xF0,0xFC,0xFE,0xBE,0xBE,0x3E,
0xBE,0xBC,0x1C,0x40,0x00,0xFF,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x7F,0x80,0x90,
0xAB,0x94,0x88,0x88,0x8B,0x88,0x88,0x94,0xAB,0x90,0x80,0x81,0x81,0x8F,0x8F,0x8F,
0x81,0x81,0x80,0x80,0x7F,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x3F,0x00,
0x00,0x00,0x03,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0x00,0x00,0xFB,
0xFF,0xFF,0xFF,0xF1,0xF2,0xF2,0xE4,0xFE,0xFD,0xFF,0xFF,0xFC,0xFF,0xFF,0xFF,0xF7,
0xC4,0x08,0x08,0x00,0x00,0x88,0xFC,0xFF,0xFC,0xF2,0xC7,0xFF,0x61,0xE1,0xC4,0xC0,
0x41,0xC1,0xF0,0xF8,0xF8,0xE7,0x8F,0x8F,0xCD,0x8C,0xC4,0xE0,0xF8,0x68,0x07,0x00,
0x08,0x08,0x00,0xF8,0x08,0xFF,0xE0,0xE0,0xF0,0xFF,0xFF,0xFF,0xFF,0xF9,0xDC,0x54,
0xC1,0xE1,0xC8,0x80,0x80,0xFF,0x00,0x00,0x00,0x03,0xC0,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,
0xE0,0x00,0x00,0x00,0xF8,0x00,0x00,0x00,0xFC,0x00,0x00,0x00,0xFF,0x00,0x00,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x7F,0x7F,0x7F,
0xFF,0x7C,0xF8,0xF8,0xF8,0xFF,0xFF,0xFF,0xFF,0x3F,0x7F,0xFF,0xFF,0xFC,0xF8,0xF9,
0xFF,0x7F,0x3F,0x3F,0x7F,0x7F,0x7B,0x7B,0xF9,0xF9,0xF8,0x38,0xB8,0x78,0x78,0x78,
0x78,0xFC,0xFC,0xFE,0x7F,0x7F,0x3F,0x3F,0x3F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0xFF,0x00,0x00,
0x00,0xFF,0x00,0x00,0xF0,0x00,0x00,0x00,0x00,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0xE0,0x00,0x00,0xFC,0x00,0x00,0xFF,0x00,
0xFF,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0xFF,0x00,0x00,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF1,0xE0,0xEE,0xDF,0xDF,0xFF,0xEE,
0xC5,0xF4,0xF5,0xF0,0xFF,0xFF,0xFF,0xDF,0xCF,0xE7,0xF8,0xF8,0xF1,0xE7,0xCF,0xFF,
0xFF,0xC0,0xFF,0xFF,0xFF,0xFF,0x9F,0x80,0xFF,0xFF,0xF6,0xF1,0xE4,0xD3,0xD5,0xC6,
0xD6,0xD1,0xFF,0x97,0x90,0xD5,0xF0,0xF0,0xF0,0xD0,0xD7,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0xFF,0x00,0x00,
0x00,0xFF,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0xFF,0x00,0x00,
0x00,0xFF,0x00,0x00,0xFF,0x00,0x00,0x00,0xFF,0x00,0x00,0xFF,0x00,0x00,0xFF,0x00,
0xFF,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0xFF,0x00,0x00,0xFF
};

void main()
{
  FILE *fp;

  fp = fopen("c:\\2764.bin","wb");

  fwrite(bitmap,1,128*64,fp);

  fclose(fp);
}