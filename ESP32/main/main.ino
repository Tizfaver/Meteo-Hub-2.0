#include "helpfull.h"
#include <SPI.h>
#include "RF24.h"

#define CE_PIN  22
#define CSN_PIN 21

struct package{
  //int n = 0;
  float t = 0.00, p = 0.00, h = 0.00;
} __attribute__((packed, aligned(1)));
byte addresses[][6] = {"0"}; 

typedef struct package Package;
Package data;

RF24 myRadio(12, 5);

void setup() {
  Serial.begin(115200);
/*
  tft.begin(0x6814);
  tft.setRotation(1);
  tft.fillScreen(BLUE);
  tft.setCursor(85, 110);
*/
  myRadio.begin();
  myRadio.setChannel(115);
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate(RF24_250KBPS);
  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();
  
  tft.setTextColor(WHITE);
  tft.fillRect(30, 200, 50, 50, RED);
}

void loop() {
   if (myRadio.available() ){
    
      myRadio.read( &data, sizeof(data) );
    
      //Serial.println("giro");
      Serial.println(String(data.t) + " C");
      Serial.println(String(data.p) + " hPa");
      Serial.println(String(data.h) + " %");
   }  
}
