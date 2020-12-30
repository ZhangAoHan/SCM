//MISO -> D12  
// * MOSI ->D11  
// * SCK ->D13

 //* CE ->D8
 //* CSN ->D7

#include "SPI.h"      //24L01库文件
#include "Mirf.h"
#include "nRF24L01.h"
#include "MirfHardwareSpiDriver.h"

int temp;
int otemp;
int aaa;
int aaaa;
int bbb;
int bbbb;

void setup(){
 // Serial.begin(9600);
  Mirf.spi = &MirfHardwareSpi;  //加载24L01  SPI
  Mirf.init();                 //开始
  //Mirf.setRADDR((byte *)"clie1");
   Mirf.setTADDR((byte *)"serv1");//发送到"接收地址"
  Mirf.payload = sizeof(int);  //发送类型（整数）
   Mirf.config();  //发送通道??
}
void loop(){
  aaa=analogRead(A4);  //读取 X 向电平(0至1024)
  bbb= -analogRead(A5);//读取 X 向电平(0至-1024)
   if (aaa !=aaaa)   //如果当前 X 向电平以之前电平不一样则发送
   {
     //temp= aaa;
      Mirf.send((byte *)&aaa); //发送X向电平
     aaaa=aaa;                 //保存当前电平
     while(Mirf.isSending()){  //等待或继续发送??
  }
    }
if (bbb !=bbbb)
{
 /// temp= bbb;
   Mirf.send((byte *)&bbb);
  bbbb=bbb;
  while(Mirf.isSending()){
  }
}
/*
if(temp !=otemp)
{
 Mirf.send((byte *)&temp);
 otemp=temp;
}
*/
 
 delay(10);// 等待0.1秒
}  
