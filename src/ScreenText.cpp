#include <Arduino.h> 
#include "ScreenText.h"
#include "Global.h"

                        

#define PURPLE 0xf00f
#define BLACK 0x0000

// Screen is orientated landscape
int SCREEN_W, SCREEN_H;

void ScreenText::SetUp()
{
    uint16_t ID = tft.readID();
    tft.begin(ID);
    tft.setRotation(1); // adjust to your orientation
    tft.fillScreen(BLACK);

    Serial.begin(9600);
    
    // Screen is orientated landscape
    SCREEN_W = tft.width();
    SCREEN_H = tft.height();
}

void ScreenText::DrawTitle(const String& title)
{
    int y = 10;
    int padding = 4;
    
    tft.setTextSize(3);
    tft.setTextColor(BLACK);
    
    int16_t x1, y1;
    uint16_t w, h;
    
    tft.getTextBounds(title, 0, 0, &x1, &y1, &w, &h);
    int TextX = (SCREEN_W - w) / 2 - x1;
    int RectX = (SCREEN_W - w) / 2 - padding;

    tft.fillRect(RectX, y - padding, w + padding, h + padding, TFT_WHITE);
    tft.setCursor(TextX, y);
    tft.print(title);
}

void ScreenText::DrawText(int x, int y, const String& text)
{
  tft.setTextSize(2);
  tft.setTextColor(TFT_WHITE);
  tft.setCursor(x, y);
  tft.print(text);
}

void ScreenText::Clear()
{
    tft.fillScreen(BLACK);
}

