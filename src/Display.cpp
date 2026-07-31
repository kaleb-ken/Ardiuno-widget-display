#include <Arduino.h> 
#include "Display.h"
#include <MCUFRIEND_kbv.h>

MCUFRIEND_kbv tft;

#define PURPLE 0xf00f
#define BLACK 0x0000

void Display::Begin()
{
    uint16_t ID = tft.readID();
    tft.begin(ID);
    tft.setRotation(1); // adjust to your orientation
    tft.fillScreen(BLACK);
}

void Display::DrawTitle(const String& title)
{
    tft.fillRect(0,0,320,320,PURPLE);
    tft.setCursor(10,10);
    tft.print(title);
}