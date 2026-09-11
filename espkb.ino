#include "USB.h"
#include "USBHIDKeyboard.h"

// BOOT button on ESP32-S3 is GPIO 0
const int buttonPin = 0;

// Configurable click timeout window (ms)
const unsigned long CLICK_TIMEOUT_MS = 500;

// Strings sent for each click type
const char* string1 = "Hello from ESP32-S3 HID!";  // single click
const char* string2 = "String 2 - double click";    // double click
const char* string3 = "String 3 - triple click";    // triple click

USBHIDKeyboard Keyboard;

// Click tracking state
int clickCount = 0;
unsigned long lastReleaseTime = 0;
bool lastButtonState = HIGH;  // HIGH = not pressed (INPUT_PULLUP)

void setup() {
  // BOOT connects to GND when pressed
  pinMode(buttonPin, INPUT_PULLUP);

  Keyboard.begin();
  USB.begin();
}

void loop() {
  bool currentState = digitalRead(buttonPin);

  // Detect rising edge: button just released (LOW -> HIGH)
  if (lastButtonState == LOW && currentState == HIGH) {
    delay(50);  // debounce
    if (digitalRead(buttonPin) == HIGH) {
      clickCount++;
      lastReleaseTime = millis();
    }
  }

  lastButtonState = currentState;

  // Dispatch after timeout window with no new clicks
  if (clickCount > 0 && (millis() - lastReleaseTime) >= CLICK_TIMEOUT_MS) {
    switch (clickCount) {
      case 1:
        Keyboard.print(string1);
        break;
      case 2:
        Keyboard.print(string2);
        break;
      case 3:
        Keyboard.print(string3);
        break;
      default:
        // More than 3 clicks: ignore
        break;
    }
    Keyboard.releaseAll();
    clickCount = 0;
  }
}
