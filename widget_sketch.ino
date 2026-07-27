#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <ArduinoJson.h>

MCUFRIEND_kbv tft;

String inputBuffer = "";

void setup() {
  Serial.begin(9600);
  uint16_t ID = tft.readID(); // auto-detects the driver chip
  tft.begin(ID);
  tft.setRotation(1);
  tft.fillScreen(0x0000); // black
  tft.setTextColor(0xFFFF); // white
  tft.setTextSize(2);
}

void loop() {
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {
      parseAndDisplay(inputBuffer);
      inputBuffer = "";
    } else {
      inputBuffer += c;
    }
  }
}

void parseAndDisplay(String jsonStr) {
  StaticJsonDocument<256> doc;
  if (deserializeJson(doc, jsonStr)) return;

  const char* title = doc["title"];
  const char* artist = doc["artist"];
  long progess = doc["progress_ms"];

  tft.fillScreen(0x0000);
  tft.setCursor(10, 20);
  tft.println(title);
  tft.setCursor(10, 50);
  tft.println(artist);
  tft.setCursor(10, 70);
  tft.println(progess);
}