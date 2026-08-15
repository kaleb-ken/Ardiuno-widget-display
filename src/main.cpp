#include <Arduino.h>
#include "ScreenText.h"
#include "Tamagotchi.h"
#include "Global.h"
#include <SD.h>
#include <SPI.h>

MCUFRIEND_kbv tft;
ScreenText display;
Tamagotchi Terry;

void setup() {
   Serial.begin(9600);
  while (!Serial);
  Serial.print("Initializing SD card...");
  if (!SD.begin(10)) {
    Serial.println("failed!");
    return;
  }
  Serial.println("done.");
  display.SetUp();
  display.DrawTitle("Terry");
  Terry.SetUp();
}

void loop() {

  
}
