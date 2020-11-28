                                                                        //
//===========================================================================//

#include "msp430x14x.h"
#include "PIN_DEF.H"
#include "RC522.H"
#include "UART0_Func.c"
#include "ctype.h" 
#include "BoardConfig.h"

unsigned char UID[5],Temp[4]                                       ;
unsigned char RF_Buffer[18]                                        ;
unsigned char Password_Buffer[6]={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}   ; // Mifare One ȱʡ����

char          MBRX[30]                                             ;
char          MBKeyTP[30]                                          ;
char          Event                                                ;
unsigned char DISP_MODE,i                                            ; // �༭�ؼ���ʾģʽ
unsigned char des_on       = 0                                     ; // DES���ܱ�־
void Key_TP_Task(void)                                             ;

//***************************************************************************//
//                                                                           //
//                 ��ʼ����ʱ��: MCLK = XT1��(FLL_FACTOR+1)                  //
//                                                                           //
//***************************************************************************//
void Init_CLK(void)
{
  unsigned int qq;
  WDTCTL     = WDTPW + WDTHOLD                                     ; // �ؿ��Ź�
  BCSCTL1 &= ~XT2OFF;           //��XT2���پ�������  
  do
  {
    IFG1 &= ~OFIFG;           //Clear oscFault flag�������ʧЧ��־
    for(qq=0xff;qq>0;qq--);
  }while((IFG1&OFIFG));       //oscFault flag still set
  
  BCSCTL2 |= SELM_2;          //MCLK=XT2
  //BCSCTL2 |= DIVM_0;        //����MCLK����Ƶ,Ĭ��
  
  BCSCTL2 |= SELS;            //SMCLK=XT2
  //BCSCTL2 |= DIVS_0;        //����SMCLK����Ƶ,Ĭ��
}

void Delay(unsigned int time)
{
  unsigned int i,k                             ;
  for(i=0;i<255;i++)
    for(k=0;k<time;k++)
      _NOP()                                   ;	  
}

void Auto_Reader(void)
{
  while(1)
  {
    if(PcdRequest(0x52,Temp)==MI_OK)
    {
      if(Temp[0]==0x04&&Temp[1]==0x00)  
          PutString("MFOne-S50");
        else if(Temp[0]==0x02&&Temp[1]==0x00)
          PutString("MFOne-S70");
        else if(Temp[0]==0x44&&Temp[1]==0x00)
          PutString("MF-UltraLight");
        else if(Temp[0]==0x08&&Temp[1]==0x00)
          PutString("MF-Pro");
        else if(Temp[0]==0x44&&Temp[1]==0x03)
          PutString("MF Desire");
        else
          PutString("Unknown");
      if(PcdAnticoll(UID)==MI_OK)
      { 
        PutString0("Card Id is:");
        tochar(UID[0]);
        tochar(UID[1]);
        tochar(UID[2]);
        tochar(UID[3]);
        while (!(IFG1 & UTXIFG0));
        TXBUF0 = '\n';                              //���ͻ���ָ��
                        
        RED_LED_ON                                            ;
        Delay(200)                                           ;
        RED_LED_OFF                                           ;
        Delay(200)                                           ;
      }
    }
  else GRE_LED_OFF                                            ;
  } 
}

void Find_Card(void)
{
    if(PcdRequest(0x52,Temp)==MI_OK)
    {
      if(Temp[0]==0x04&&Temp[1]==0x00)  
          PutString("MFOne-S50");
        else if(Temp[0]==0x02&&Temp[1]==0x00)
          PutString("MFOne-S70");
        else if(Temp[0]==0x44&&Temp[1]==0x00)
          PutString("MF-UltraLight");
        else if(Temp[0]==0x08&&Temp[1]==0x00)
          PutString("MF-Pro");
        else if(Temp[0]==0x44&&Temp[1]==0x03)
          PutString("MF Desire");
        else
          PutString("Unknown");
        PutString("SUCCESS!");
    }
    else PutString("Faile!");                                             
}

void Init_Port(void)
{
  P4DIR   =   RF_LPCTL + RF_SS   + RF_SCLK  + RF_DATA_OUT                     ;
  P2DIR |= BIT0+RF_LPCTL + RF_SS   + RF_SCLK  + RF_DATA_OUT;
  P1DIR   =   RF_LPCTL + RF_SS   + RF_SCLK  + RF_DATA_OUT                     ;
}
/*******************************************
�������ƣ�HandleConfigMenu
��    �ܣ�����PC�����ú���
��    ����inputvalue--���յ�������PC�����ַ�
����ֵ  ����
********************************************/
void HandleConfigMenu(uchar inputvalue)
{
    switch(toupper(inputvalue)) 
    {
    case 'A':
              Auto_Reader();
              break;
    case 'F':
              Find_Card();
              break;
    default:
              DisplayConfigMenu();  
    }
}


void main( void )
{
  WDTCTL     = WDTPW + WDTHOLD                                     ; // �ؿ��Ź�
  BoardConfig(0xf0);
  Init_Port();
  InitUART();
  _EINT()                                            ;
  PcdReset();//��λRC522
  PcdAntennaOn();//�������߷��� 
  DisplayConfigMenu();
  while(1)
  {
        Send1Char('>');
        Send1Char('\n');
        i=Get1Char();
        HandleConfigMenu(i);
  }
}
