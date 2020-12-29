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
/*****定义控制位**********************/
sbit    Time_Show_LED2=P2^5;    //Time_Show_LED2控制位
sbit    Time_Show_LED1=P2^4;    //Time_Show_LED1控制位
sbit	EW_LED2=P2^3;	        //EW_LED2控制位
sbit	EW_LED1=P2^2;	        //EW_LED1控制位
sbit	SN_LED2=P2^1;	        //SN_LED2控制位
sbit	SN_LED1=P2^0;	        //SN_LED1控制位
sbit    SN_Yellow=P1^6;         //SN黄灯
sbit    EW_Yellow=P1^2;         //EW黄灯
sbit    EW_Red=P1^3;            //EW红灯
sbit    SN_Red=P1^7;            //SN红灯
sbit    QZ_SN_LED=P3^0;         //SN方向强制直行指示灯
sbit    QZ_EW_LED=P3^1;         //EW方向强制直行指示灯	
sbit    Add_Button=P3^4;        //时间加
sbit    Reduces_Button=P3^5;    //时间减 
sbit    QZ_EW_Btton=P3^6;       //EW方向强制直行按键
sbit    QZ_SN_Btton=P3^7;       //SN方向强制直行按键 
bit     Flag_SN_Yellow;         //SN黄灯标志位
bit     Flag_EW_Yellow;         //EW黄灯标志位
bit     QZ_EW;
bit     QZ_SN;
char	Time_EW;                //东西方向倒计时单元
char	Time_SN;                //南北方向倒计时单元
uchar EW=60,SN=40,EWL=19,SNL=19; //程序初始化赋值，正常模式
uchar EW1=60,SN1=40,EWL1=19,SNL1=19;
                                //用于存放修改值的变量
uchar code table[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
                                //1~~~~9段选码
uchar code LIGHT[8]={0X28,0X48,0X18,0X48,0X82,0X84,0X81,0X84};
                                //交通信号灯控制代码
TRAFFIC_EXT void Delay(uchar );
TRAFFIC_EXT	void Display(void);
#endif