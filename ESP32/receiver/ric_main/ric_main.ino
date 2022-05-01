/*
PROJECT NAME: Meteo Hub 2.0
AUTHOR: @Tizfaver
START DATE: 16/04/2022
FINISH DATE: --/--/--
You can do what you want with my code
*/

#include <SPI.h>  
#include "RF24.h" 
#include "RTClib.h"
#include <Adafruit_SSD1306.h>
#include <splash.h>

//RTC_DS1307 rtc;
RF24 myRadio (7, 8);
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

struct package{
  int n = 0;
  float t = 0.00, p = 0.00, h = 0.00;
};

byte addresses[][6] = {"0"}; 

typedef struct package Package;
Package data;

void setup(){
  Serial.begin(115200);
  delay(1000);

  //rtc.begin();
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  //rtc.adjust(DateTime(2022, 4, 17, 12, 19, 30));

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  myRadio.begin();
  myRadio.setChannel(115);
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate(RF24_250KBPS);
  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Pronto!");
  display.display();
}

void loop(){
  //int v = analogRead(A0); //pin LM35
  //String tInterna = String(((float)(5000.0d/1024.0d)*(float)v) / 10.0d);
  //DateTime now = rtc.now();

  if (myRadio.available()){
    while (myRadio.available()){
      myRadio.read( &data, sizeof(data) );
    }
    //Serial.print(String(data.t) + "|" + String(data.p) + "|" + String(data.h) + "|" + tInterna + "|" + String(now.hour(), DEC) + "|" + String(now.minute(), DEC) + "|" + String(now.second(), DEC) + "|"); //send to esp32
    Serial.println(String(data.t) + "|" + String(data.p) + "|" + String(data.h));
    display.setCursor(0,0);
    display.clearDisplay();
    display.display();
    delay(100);
    display.println("OK Signal, now data:");
    display.println(String(data.t) + " C");
    display.println(String(data.p) + " hPa");
    display.println(String(data.h) + " %");
    display.display();
    //delay(1000);

  }
  //Serial.println(String(now.hour(), DEC) + "|" + String(now.minute(), DEC) + "|" + String(now.second(), DEC) + "|");
  //Serial.println(tInterna);
  //delay(2000);
}
