#define TIMS 65500
#define TIMS1 3036
#define SSIG      1
#define SPEN      1
#define DORD      0
#define MSTR      1
#define CPOL      1
#define CPHA      1
#define SPR1      0
#define SPR0      0
#define SPEED_4   0
#define SPEED_16  1
#define SPEED_64  2
#define SPEED_128 3

#define SPIF      0x80
#define WCOL      0x40

sfr SPSTAT =0xCD;
sfr SPCTL  =0xCE;
sfr SPDAT  =0xCF;

sfr AUXR   =0x8E;
sfr AUXR1  =0XA2;
sfr CLK_DIV=0x97;
sfr P5     =0xC8;

sbit HC595_RCLK=P5^4;


