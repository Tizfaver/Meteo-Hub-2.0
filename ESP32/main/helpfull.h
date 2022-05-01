//--------------------------------------------------------------------
/*
display:
LCD_D1 --> D13
LCD_D0 --> D12
LCD_D7 --> D14
LCD_D6 --> D27
LCD_D5 --> RX2
LCD_D4 --> TX2
LCD_D3 --> D25
LCD_D2 --> D26
LCD_RD --> D2
LCD_WR --> D4
LCD_RS --> D15
LCD_CS --> D33
LCD_RST --> D32

nrf24l01:
CE --> D12
SCK --> D18
MISO --> D19
CSN --> D5
MOSI --> D23
*/


#define LCD_CS 33 // Chip Select ESP32 GPIO33
#define LCD_RS 15 // LCD_RS = Register Select or LCD_CD = Command/Data
#define LCD_WR 4 // LCD Write goes to ESP32 GPIO4
#define LCD_RD 2 // LCD Read goes to ESP32 GPIO2
#define LCD_RESET 32 // ESP32 GPIO32

//--------------------------------------------------------------------
//needed librarys
#include <MCUFRIEND_kbv.h>
#include "Adafruit_GFX.h"
#include "TouchScreen.h"
#include <HardwareSerial.h>

MCUFRIEND_kbv tft; //create the object 'tft' to interract with the lib

//--------------------------------------------------------------------

//declaration for the serial com from the arduino nano
#define RXD2 34 //pins for receive datas from arduino
#define TXD2 35

//--------------------------------------------------------------------

//Assign human-readable names to some common 16-bit color values
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

//--------------------------------------------------------------------

//helpfull comands to remind for the code:
/*tft.setTextColor(YELLOW, BLACK);
tft.println("readPixel() reads as BGR");
printmsg(msglin, "INVERT DISPLAY ");
tft.fillScreen(BLACK);
tft.setTextColor(GREEN);
tft.setCursor(0, 0);
tft.setTextSize(1);
tft.drawRect(cx - i2, cy - i2, i, i, color);
tft.fillRect(cx - i2, cy - i2, i, i, color1);
tft.fillCircle(x, y, radius, color);*/

//--------------------------------------------------------------------

const int XP=27,XM=15,YP=4,YM=14; //320x480 ID=0x6814
