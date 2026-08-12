#include <Arduino.h>
#include "Display.h"

Display display;

void setup() {
  display.SetUp();
  display.DrawTitle("Bob");
  display.DrawImage(100,100,"Bob.bmp");
   Serial.println("poooo");
}

void loop() {

  
}
