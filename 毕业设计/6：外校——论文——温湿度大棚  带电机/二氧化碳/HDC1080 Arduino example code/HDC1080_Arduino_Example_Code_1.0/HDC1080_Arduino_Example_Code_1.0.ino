/*
 * HDC1080_Arduino_Example.ino
 * Created: July 21st 2017
 * This sketch is released AS-IS into the public domain, no guarantee or warranty is given.
 * This Code is not supported by Texas Instruments.
 * 
 * Description: This sketch configures the HDC1080 and Arduino Uno to read and display the 
 * local temperature and humidty to a standard 1602 LCD display. Please see the associated
 * schematic for setup information. 
 * 
 * Copyright (C) 2017 Texas Instruments Incorporated - http://www.ti.com/ 
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/

#include <Wire.h>
#include <LiquidCrystal.h>

//Declare           RS, E,  D4, D5, D6, D7
LiquidCrystal lcd(  3,  5,  6,  9,  10, 11);

void setup() {
   //Initialize I2C Communication
  Wire.begin();
  
  //Initialize the LCD Display
  lcd.begin(16, 2);
  //Print temperature label
  lcd.setCursor(0,0);
  lcd.write("TEMP(C): ");
  
  //Print Humidity label
  lcd.setCursor(0,1);
  lcd.write("%RH : ");
  
  //Configure HDC1080
  Wire.beginTransmission(0x40);
  Wire.write(0x02);
  Wire.write(0x90);
  Wire.write(0x00);
  Wire.endTransmission();

  //Delay for Startup of HDC1080
  delay(20);
}

void loop() 
{
  double temperature;
  double humidity;

  humidity = readSensor(&temperature);

  //Print the current temperature to the right of the label
  lcd.setCursor(9,0);
  lcd.print(temperature);

  //Print the current humidity to the right of the label
  lcd.setCursor(6,1);
  lcd.print(humidity);

  //Wait 1 second for the next reading
  delay(1000);
  
}

double readSensor(double* temperature)
{
  //holds 2 bytes of data from I2C Line
  uint8_t Byte[4];

  //holds the total contents of the temp register
  uint16_t temp;

  //holds the total contents of the humidity register
  uint16_t humidity;
  
  //Point to device 0x40 (Address for HDC1080)
  Wire.beginTransmission(0x40);
  //Point to register 0x00 (Temperature Register)
  Wire.write(0x00);
  //Relinquish master control of I2C line
  //pointing to the temp register triggers a conversion
  Wire.endTransmission();
  
  //delay to allow for sufficient conversion time
  delay(20);
  
  //Request four bytes from registers
  Wire.requestFrom(0x40, 4);

  delay(1);
  
  //If the 4 bytes were returned sucessfully
  if (4 <= Wire.available())
  {
    //take reading
    //Byte[0] holds upper byte of temp reading
    Byte[0] = Wire.read();
    //Byte[1] holds lower byte of temp reading
    Byte[1] = Wire.read();
    
    //Byte[3] holds upper byte of humidity reading
    Byte[3] = Wire.read();
    //Byte[4] holds lower byte of humidity reading
    Byte[4] = Wire.read();

    //Combine the two bytes to make one 16 bit int
    temp = (((unsigned int)Byte[0] <<8 | Byte[1]));

    //Temp(C) = reading/(2^16)*165(C) - 40(C)
    *temperature = (double)(temp)/(65536)*165-40;

   //Combine the two bytes to make one 16 bit int
    humidity = (((unsigned int)Byte[3] <<8 | Byte[4]));

    //Humidity(%) = reading/(2^16)*100%
    return (double)(humidity)/(65536)*100;
  }
}


