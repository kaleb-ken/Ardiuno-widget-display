#include <Arduino.h>
#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>

MCUFRIEND_kbv tft;

#define WHITE 0xFFFF
#define BLACK 0x0000
#define PURPLE 0xFFF0

int circle_radius = 10;


void setup() {
  // put your setup code here, to run once:
  uint16_t ID = tft.readID();
  tft.begin(ID);
  tft.setRotation(1); // adjust to your orientation
  tft.fillScreen(BLACK);

  tft.setCursor(10, 10);
  tft.setTextSize(3);
  tft.setTextColor(PURPLE);
  tft.print("No monster means kms");
  
  for (int i = 0; i < 10; i++){
    tft.drawCircle(175, 130, circle_radius, WHITE);
    circle_radius += 5;
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
