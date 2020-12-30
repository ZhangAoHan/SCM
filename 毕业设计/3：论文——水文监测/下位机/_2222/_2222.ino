#include "SPI.h"      //24L01库文件
#include "Mirf.h"
#include "nRF24L01.h"
#include "MirfHardwareSpiDriver.h"
unsigned char tx_buf[33] = {0};
void setup() {
   Mirf.spi = &MirfHardwareSpi;  //加载24L01  SPI
  Mirf.init();                 //开始
   Mirf.setTADDR((byte *)"serv1");//发送到"接收地址"
  Mirf.payload = sizeof(int);  //发送类型（整数）
   Mirf.config();  //发送通道??
}

void loop() {
  // put your main code here, to run repeatedly:
  rx_buf[0]='D';
  for(int i = 0; i < 33; i++)
  {
  NRF_Send(rx_buf[i]);
    }

}
