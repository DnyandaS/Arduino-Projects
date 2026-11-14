#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "cat_oled_bitmap.h"

Adafruit_SSD1306 display(128, 64, &Wire, -1);

const int BUTTON_PIN = 2;
const int BUZZER_PIN = 8;

bool wasPressed = false;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loop() {
  bool isPressed = (digitalRead(BUTTON_PIN) == LOW);

  if (isPressed && !wasPressed) {
    tone(BUZZER_PIN, 300, 100);
  }
  wasPressed = isPressed;

  display.clearDisplay();

  if (isPressed) {
    display.drawBitmap(0, 0, cat_hit, 128, 64, WHITE);
  } else {
    display.drawBitmap(0, 0, cat_idle, 128, 64, WHITE);
  }

  display.display();
}
