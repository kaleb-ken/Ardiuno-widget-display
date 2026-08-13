#include <Arduino.h>
#include "ScreenText.h"
#include "Tamagotchi.h"
#include "Global.h"
#include <SD.h>
#include <SPI.h>

MCUFRIEND_kbv tft;
ScreenText display;
Tamagotchi bob;

void setup() {
   Serial.begin(9600);
  while (!Serial);
  Serial.print("Initializing SD card...");
  if (!SD.begin(10)) {
    Serial.println("failed!");
    return;
  }
  Serial.println("done.");
  // display.SetUp();
  // display.DrawTitle("Bob");
  // bob.SetUp();
  // Serial.println("poooo");
}

void loop() {

  
}
