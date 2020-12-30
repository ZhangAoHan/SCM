#include <NRF24L01.h>

/*********************************************************************
**   SPI-compatible                                                 **
**   CE - to digital pin 13                                          **
**   CSN - to digital pin 7  (SS pin)                               **
**   SCK - to digital pin 12 (SCK pin)                              **
**   MOSI - to digital pin 11 (MOSI pin)                            **
**   MISO - to digital pin 6 (MISO pin)                            **
**   IRQ - to digital pin 5 (MISO pin)                             **
*********************************************************************/
#define TX_ADR_WIDTH    5   // 5 unsigned chars TX(RX) address width
#define TX_PLOAD_WIDTH  11  // 32 unsigned chars TX payload
unsigned char RX_ADDRESS[TX_ADR_WIDTH]  = {'L','O','V','E','!'};
unsigned char TX_ADDRESS[TX_ADR_WIDTH]  = {'L','O','V','E','!'};
unsigned char rx_buf[TX_PLOAD_WIDTH] = {0};
unsigned char tx_buf[TX_PLOAD_WIDTH] = {0};
unsigned char channel = 33;
void setup()
{
    Serial.begin(9600);
    NRF_Init();                        // Initialize IO     
    //NRF_SetRxMode();
     NRF_SeTxMode();
  //  Serial.println("RX_Mode start...");
}
 
void loop()
{
  NRF_Send('D');
    //NRF_SetRxMode();
   // if(NRF_Receive(rx_buf))
  //  {
     //   Serial.print("RX = ");
      //  for(int i = 0; i < 11; i++)
       // {
        //    Serial.print(rx_buf[i]);
       //     Serial.print(",");
      //  }
       // Serial.println();
        //for(int i = 0; i < 11; i++)
          //  rx_buf[i] =0;
        //NRF_SeTxMode();
       // NRF_Send((byte *)"OK123456789");
       //unsigned char sta5=SPI_Write_Buf(WR_TX_PLOAD,(byte *)"OK123456789",TX_PLOAD_WIDTH);
       //Serial.print("RX = ");
       //Serial.println(sta5,HEX);
    }
    delay(500);
}
 
