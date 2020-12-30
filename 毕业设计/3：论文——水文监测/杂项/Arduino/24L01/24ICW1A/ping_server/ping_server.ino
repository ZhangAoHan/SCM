//MISO -> D12  
// * MOSI ->D11  
// * SCK ->D13

 //* CE ->D8
 //* CSN ->D7


#include "Wire.h"   //24L01库文件
#include <LiquidCrystal_I2C.h>;
LiquidCrystal_I2C lcd(0x27,16,2);

#include "SPI.h"  //LCD1602 IIC 库文件
#include "Mirf.h"
#include "nRF24L01.h"
#include "MirfHardwareSpiDriver.h"

int data;
int aaa;
int bbb;

void setup(){   
   lcd.init();  //加载LCD1602 IIC
    lcd.backlight();
    //lcd.setBacklight(120);//设置背光亮度
        delay(20); 
  Mirf.spi = &MirfHardwareSpi;   //加载24L01  SPI
  Mirf.init();
  Mirf.setRADDR((byte *)"serv1");//接收到"接收地址"
  Mirf.payload = sizeof(int);   //接收类型（整数）
 // mirf.channel = ();
 //Mirf.configRegister(EN_AA,0x00);  //Disable auto ack
      Mirf.config(); 
}

void loop(){
 
  if(Mirf.dataReady()){  //如果接收到数据则执行
     
    //do{

      Mirf.getData((byte *)&data); //接收数据
      
      if (data>=1)  //如果大于1为X向
      {
 aaa=data;
      }
         if (data<=-1) //如果小于 -1为Y向
         { 
    bbb=data;
      }
   
   // }while(!Mirf.rxFifoEmpty()); 
    Mirf.rxFifoEmpty(); //清理24L01援存??
  }
     lcd.clear();
      lcd.setCursor(0, 0); 
      lcd.print(aaa);   //显示X向 1至1024
      lcd.setCursor(6, 0);
      lcd.print(0-bbb); //显示Y向,并将负数变为正数 1至1024
  delay(10); 
} 


