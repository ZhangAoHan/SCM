#include <Adafruit_ssd1306syp.h>
//#include <MsTimer2.h>               //定时器库的 头文件 
#define SDA_PIN 8
#define SCL_PIN 9
#define SensorPin A2            //pH meter Analog output to Arduino Analog Input 0
#define Offset 0.00            //deviation compensate
#define samplingInterval 20
#define printInterval 800
#define ArrayLenth  40    //times of collection
int pHArray[ArrayLenth];   //Store the average value of the sensor feedback
int pHArrayIndex=0;  
Adafruit_ssd1306syp display(SDA_PIN,SCL_PIN);
double avergearray(int* arr, int number);
static float pHValue,voltage;
void flash()                        //中断处理函数，改变灯的状态
{                        
  //  display.setTextSize(2);
  // display.setCursor(0,20);
 //display.println("PHVa:");
 //  display.setCursor(65,20);
 //display.println(pHValue);
  //  display.setCursor(0,40);
 //display.update();
// display.clear();
}
void setup()
{
  display.initialize();
 //   Serial.begin(9600);  
    display.setTextSize(1);
   display.setCursor(0,20);
 display.println("Date Exception");
  // display.setCursor(65,20);
 //display.println(pHValue);
  //  display.setCursor(0,40);
 //display.update();
 //display.clear();
   //MsTimer2::set(100, flash);        // 中断设置函数，每 500ms 进入一次中断
}
void loop()
{
  static unsigned long samplingTime = millis();
  static unsigned long printTime = millis();
  //static float pHValue,voltage;
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
    Serial.println(pHValue);
   //   MsTimer2::start();                //开始计时
        printTime=millis();
  }

}
double avergearray(int* arr, int number){
  int i;
  int max,min;
  double avg;
  long amount=0;
  if(number<=0){
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

