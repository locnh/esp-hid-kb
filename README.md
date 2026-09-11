# esp-hid-kb

An ESP32-S3 USB HID keyboard that sends configurable strings when the BOOT button is pressed. Supports single, double, and triple click — each sending a different string.

## Hardware

- **Board:** ESP32-S3 N16R8 (16 MB Flash, 8 MB PSRAM)
- **Button:** BOOT button (GPIO 0, built-in)
- **Connection:** USB-C to host machine

## Software Requirements

- [Arduino IDE](https://www.arduino.cc/en/software) 2.x
- **ESP32 Arduino core** 3.x — install via Arduino IDE Board Manager:
  - Open **File > Preferences**, add the following URL to *Additional boards manager URLs*:
    ```
    https://espressif.github.io/arduino-esp32/package_esp32_index.json
    ```
  - Open **Tools > Board > Boards Manager**, search `esp32`, install **esp32 by Espressif Systems** (3.x)

## Board Configuration (Arduino IDE)

| Setting | Value |
|---------|-------|
| Board | `ESP32S3 Dev Module` |
| USB Mode | `USB-OTG (TinyUSB)` |
| USB CDC On Boot | `Disabled` |
| Flash Size | `16MB (128Mb)` |
| PSRAM | `OPI PSRAM` |
| Partition Scheme | `16M Flash (3MB APP/9.9MB FATFS)` |
| Upload Speed | `921600` |

## Entering Flash Mode

The ESP32-S3 must be in **download mode** before flashing:

1. Hold the **BOOT** button
2. Press and release the **RESET** button (or replug USB while holding BOOT)
3. Release **BOOT**

The device will stay in download mode until flashed or reset.

## Build and Flash

1. Open `espkb.ino` in Arduino IDE
2. Select the correct port under **Tools > Port**
3. Apply the board settings from the table above
4. Click **Upload** (→)

After flashing, press **RESET** to start the sketch. The board will enumerate as a USB HID keyboard.

## Usage

Press the BOOT button on the ESP32-S3:

| Action | Output |
|--------|--------|
| Single click | `Hello from ESP32-S3 HID!` |
| Double click | `String 2 - double click` |
| Triple click | `String 3 - triple click` |

A click window of **500 ms** separates click counts — single click output is delayed by this window.

## Customizing Strings

Edit the three constants near the top of `espkb.ino`:

```cpp
const char* string1 = "Hello from ESP32-S3 HID!";  // single click
const char* string2 = "String 2 - double click";    // double click
const char* string3 = "String 3 - triple click";    // triple click
```

To adjust the click timeout window:

```cpp
const unsigned long CLICK_TIMEOUT_MS = 500;  // milliseconds
```

## License

See [LICENSE](LICENSE).
