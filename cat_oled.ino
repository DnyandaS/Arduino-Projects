#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "cat_oled_bitmap.h"

Adafruit_SSD1306 display(128, 64, &Wire, -1);

const int BUTTON_PIN = 2;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loop() {
  display.clearDisplay();

  if (digitalRead(BUTTON_PIN) == LOW) {
    display.drawBitmap(0, 0, cat_hit, 128, 64, WHITE);
  } else {
    display.drawBitmap(0, 0, cat_idle, 128, 64, WHITE);
  }

  display.display();
}