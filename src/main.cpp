#include <Arduino.h>
#include "ScreenText.h"
#include "Tamagotchi.h"
#include "Global.h"

MCUFRIEND_kbv tft;
ScreenText display;
Tamagotchi bob;

void setup() {
  display.SetUp();
  display.DrawTitle("Bob");
  bob.SetUp();
  Serial.println("poooo");
}

void loop() {

  
}
