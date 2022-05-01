/*
PROJECT NAME: Meteo Hub 2.0
AUTHOR: @Tizfaver
START DATE: 15/04/2022
FINISH DATE: 01/05/2022
You can do what you want with my code
*/

#include "LowPower.h"
//#include <avr/sleep.h>
//#include <avr/power.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BME280.h>
#include "RF24.h"

byte addresses[][6] = {"0"};

RF24 myRadio (7, 8);
Adafruit_BME280 bme;

struct package{
  //int8_t n = 0; //number of the package, remember to uncomment the esp32 side
  float t;
  float p;
  float h;
};
typedef struct package Package;
Package data;

//------------------------------------------

void setup(){
  //Serial.begin(115200);
  beginM();
  pinMode(9, OUTPUT);

  digitalWrite(9, HIGH);
  delay(50);
  digitalWrite(9, LOW);
  delay(50);
  digitalWrite(9, HIGH);
  delay(50);
  digitalWrite(9, LOW);
  delay(50);
  digitalWrite(9, HIGH);
  delay(50);
  digitalWrite(9, LOW);
  
  delay(5000);
}

void loop(){
  myRadio.powerDown();
  SleepA();
  myRadio.powerUp();
  beginM();

  //digitalWrite(9, HIGH);
  data.t = bme.readTemperature();
  data.p = bme.readPressure() / 100.0F;
  data.h = bme.readHumidity();
  delay(100);
  //digitalWrite(9, LOW);
  myRadio.write(&data, sizeof(data));
}

void SleepA(){
  for(int i = 0; i < 8; i++){
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  }
}

void beginM(){
  bme.begin(0x76);
  myRadio.begin();
  myRadio.setChannel(115);
  myRadio.setPALevel(RF24_PA_MIN);
  myRadio.setDataRate(RF24_250KBPS);
  myRadio.openWritingPipe(addresses[0]);  
}
