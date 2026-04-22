#include "USB.h"
#include "USBHIDKeyboard.h"

// BOOT button on ESP32-S3 is GPIO 0
const int buttonPin = 0;
USBHIDKeyboard Keyboard;

void setup() {
  // BOOT connect to GND when pressed
  pinMode(buttonPin, INPUT_PULLUP);

  Keyboard.begin();
  USB.begin();
}

void loop() {
  // Check if BOOT pressed
  if (digitalRead(buttonPin) == LOW) {

    delay(50);

    if (digitalRead(buttonPin) == LOW) {
      // Send string of key to Machine
      Keyboard.print("Hello from ESP32-S3 HID!");

      // Press Enter
      // Keyboard.press(KEY_RETURN);
      Keyboard.releaseAll();

      // Wait until unpressed
      while (digitalRead(buttonPin) == LOW) {
        delay(10);
      }
    }
  }
}
