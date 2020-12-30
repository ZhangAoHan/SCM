#include <GravityTDS.h>

#include <OneWire.h>
#include <EEPROM.h>
#include "GravityTDS.h"
#include <MsTimer2.h>               //定时器库的 头文件 

#define TdsSensorPin A1
GravityTDS gravityTds;

int DS18S20_Pin = 2;
OneWire ds(DS18S20_Pin); 
float temperature = 25,tdsValue = 0;


#define SensorPin A2            //pH meter Analog output to Arduino Analog Input 0
#define Offset 0.00            //deviation compensate
//#define LED 13
#define samplingInterval 20
#define printInterval 800
#define ArrayLenth  40    //times of collection
int pHArray[ArrayLenth];   //Store the average value of the sensor feedback
int pHArrayIndex=0;    
double avergearray(int* arr, int number);
float getTemp();
int set1=0;
void flash()                        //中断处理函数，改变灯的状态
{            
  
  
          delay(100);
         Serial.print("D");
     Serial.println(tdsValue,3);
  delay(100);

     // delay(50);
     //
     //
}


void setup() {
  Serial.begin(9600);
 // pinMode(LED,OUTPUT);  
     gravityTds.setPin(TdsSensorPin);
    gravityTds.setAref(5.0);  //reference voltage on ADC, default 5.0V on Arduino UNO
    gravityTds.setAdcRange(1024);  //1024 for 10bit ADC;4096 for 12bit ADC
    gravityTds.begin();  //initialization
    //Serial.println("pH meter experiment!");  
     MsTimer2::set(500, flash);        // 中断设置函数，每 500ms 进入一次中断
  MsTimer2::start();                //开始计时
}

void loop() {
    static unsigned long samplingTime = millis();
  static unsigned long printTime = millis();
  static float pHValue,voltage;
  
  float temperature = getTemp();
 // Serial.println(temperature);  //输出温度数据
    gravityTds.setTemperature(temperature);  // set the temperature and execute temperature compensation
   gravityTds.update();  //sample and calculate 
    tdsValue = gravityTds.getTdsValue();  // then get the value
    //Serial.println(tdsValue);
    //Serial.println("ppm");
  //delay(1000); 

  if(millis()-samplingTime > samplingInterval)
  {
      pHArray[pHArrayIndex++]=analogRead(SensorPin);
      if(pHArrayIndex==ArrayLenth)pHArrayIndex=0;
     voltage = avergearray(pHArray, ArrayLenth)*5.0/1024;
      pHValue = 3.5*voltage+Offset;
      samplingTime=millis();
 }
 if(millis() - printTime > printInterval)   //Every 800 milliseconds, print a numerical, convert the state of the LED indicator
  {
    Serial.print("P");
    Serial.print(voltage);
    Serial.println(pHValue);
    delay(50);
       //Serial.print("T");
   //  Serial.println(temperature,2); 
    printTime=millis();
 
  }

 
    
}
float getTemp(){
  //returns the temperature from one DS18S20 in DEG Celsius

  byte data[12];
  byte addr[8];

  if ( !ds.search(addr)) {
      //no more sensors on chain, reset search
      ds.reset_search();
      return -1000;
  }

  if ( OneWire::crc8( addr, 7) != addr[7]) {
     // Serial.println("CRC is not valid!");
      return -1000;
  }

  if ( addr[0] != 0x10 && addr[0] != 0x28) {
     // Serial.print("Device is not recognized");
      return -1000;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1); // start conversion, with parasite power on at the end

  byte present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE); // Read Scratchpad

  
  for (int i = 0; i < 9; i++) { // we need 9 bytes
    data[i] = ds.read();
  }
  
  ds.reset_search();
  
  byte MSB = data[1];
  byte LSB = data[0];

  float tempRead = ((MSB << 8) | LSB); //using two's compliment
  float TemperatureSum = tempRead / 16;
  
  return TemperatureSum;
  
}
double avergearray(int* arr, int number){
  int i;
  int max,min;
  double avg;
  long amount=0;
  if(number<=0){
    //Serial.println("Error number for the array to avraging!/n");
    return 0;
  }
  if(number<5){   //less than 5, calculated directly statistics
    for(i=0;i<number;i++){
      amount+=arr[i];
    }
    avg = amount/number;
    return avg;
  }else{
    if(arr[0]<arr[1]){
      min = arr[0];max=arr[1];
    }
    else{
      min=arr[1];max=arr[0];
    }
    for(i=2;i<number;i++){
      if(arr[i]<min){
        amount+=min;        //arr<min
        min=arr[i];
      }else {
        if(arr[i]>max){
          amount+=max;    //arr>max
          max=arr[i];
        }else{
          amount+=arr[i]; //min<=arr<=max
        }
      }//if
    }//for
    avg = (double)amount/(number-2);
  }//if
  return avg;
}


