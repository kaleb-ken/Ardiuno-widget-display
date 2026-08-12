#include <Arduino.h> 
#include <SD.h>
#include <SPI.h>
#include "Display.h"
#include <MCUFRIEND_kbv.h>

MCUFRIEND_kbv tft;
                        

uint16_t read16(SDLib::File &f);
uint32_t read32(SDLib::File &f);

#define PURPLE 0xf00f
#define BLACK 0x0000
#define SD_CS 10 

// Screen is orientated landscape
int SCREEN_W, SCREEN_H;

void Display::SetUp()
{
    uint16_t ID = tft.readID();
    tft.begin(ID);
    tft.setRotation(1); // adjust to your orientation
    tft.fillScreen(BLACK);

    Serial.begin(9600);
    
    // Screen is orientated landscape
    SCREEN_W = tft.width();
    SCREEN_H = tft.height();

    // Initialize the SD card reader hardware
    if (!SD.begin(SD_CS)) {
        tft.print("SD initialization failed!");
        while (1); // Halt program execution if missing/broken
    }


}

void Display::DrawTitle(const String& title)
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

void Display::Clear()
{
    tft.fillScreen(BLACK);
}

void Display::DrawImage(int x, int y, const char *FileName)
{
   SDLib::File bmpFile = SD.open(FileName);
  if (!bmpFile) {
    Serial.println("Image File Not Found!");
    return;
  }

  if (read16(bmpFile) != 0x4D42) { // Verify 'BM' signature
    Serial.println("Not a valid BMP file!");
    bmpFile.close();
    return;
  }

  read32(bmpFile); // Skip file size
  read32(bmpFile); // Skip creator bytes
  uint32_t bmpImageoffset = read32(bmpFile); 
  read32(bmpFile); // Skip header size
  int bmpWidth = read32(bmpFile);
  int bmpHeight = read32(bmpFile);

  if (read16(bmpFile) == 1 && read16(bmpFile) == 24 && read32(bmpFile) == 0) {
    uint32_t rowSize = (bmpWidth * 3 + 3) & ~3;
    int w = bmpWidth;
    int h = bmpHeight;

    if ((x + w - 1) >= tft.width())  w = tft.width()  - x;
    if ((y + h - 1) >= tft.height()) h = tft.height() - y;

    // Open parallel data stream window on the shield
    tft.setAddrWindow(x, y, x + w - 1, y + h - 1);

    uint8_t sdbuffer[3 * 20]; 
    uint8_t buffidx = sizeof(sdbuffer);
    bool firstPixel = true; // Tracks address indexing initialization

    for (int row = 0; row < h; row++) {
      uint32_t pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
      if (bmpFile.position() != pos) {
        bmpFile.seek(pos);
        buffidx = sizeof(sdbuffer);
      }

      for (int col = 0; col < w; col++) {
        if (buffidx >= sizeof(sdbuffer)) {
          bmpFile.read(sdbuffer, sizeof(sdbuffer));
          buffidx = 0;
        }
        uint8_t b = sdbuffer[buffidx++];
        uint8_t g = sdbuffer[buffidx++];
        uint8_t r = sdbuffer[buffidx++];
        
        // Fix: Convert to RGB565 and push via array pointer
        uint16_t pixelColor = tft.color565(r, g, b);
        tft.pushColors(&pixelColor, 1, firstPixel); 
        firstPixel = false; // Subroutine addresses remain locked inside the window bounds
      }
    }
  }
  bmpFile.close();
}

uint16_t read16(SDLib::File &f) {
  uint16_t result;
  f.read((uint8_t *)&result, sizeof(result));
  return result;
}

uint32_t read32(SDLib::File &f) {
  uint32_t result;
  f.read((uint8_t *)&result, sizeof(result));
  return result;
}