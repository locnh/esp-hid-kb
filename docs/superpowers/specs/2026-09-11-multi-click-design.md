# Design: Multi-click String Dispatch

**Date:** 2026-09-11  
**Status:** Approved

## Overview

Add support for distinguishing single / double / triple clicks on the BOOT button (GPIO 0) of the ESP32-S3. Each click type sends a different HID keyboard string.

## Requirements

- Single click → send `string1`
- Double click → send `string2`
- Triple click → send `string3`
- Click timeout window is configurable via `CLICK_TIMEOUT_MS` constant (default 500ms)
- Debounce remains at 50ms as per current implementation

## Approach

**Click counter + timeout (Approach A)**

Count the number of button releases within `CLICK_TIMEOUT_MS`. Once no new click is detected within that window, dispatch based on the click count.

## Variables

| Variable | Type | Purpose |
|----------|------|---------|
| `CLICK_TIMEOUT_MS` | `const unsigned long` | Configurable timeout window (default 500ms) |
| `clickCount` | `int` | Number of clicks accumulated in the current window |
| `lastReleaseTime` | `unsigned long` | Timestamp of the last button release (`millis()`) |
| `lastButtonState` | `bool` | Previous button state, used to detect rising edge |

## Strings

```cpp
const char* string1 = "Hello from ESP32-S3 HID!";  // single click
const char* string2 = "String 2 - double click";    // double click
const char* string3 = "String 3 - triple click";    // triple click
```

String contents can be changed freely to suit the intended use case.

## Logic Flow

```
loop():
  read buttonPin

  if button just released (HIGH, previously LOW):
    debounce 50ms
    increment clickCount
    update lastReleaseTime = millis()

  if clickCount > 0 and (millis() - lastReleaseTime) >= CLICK_TIMEOUT_MS:
    switch clickCount:
      1 → Keyboard.print(string1)
      2 → Keyboard.print(string2)
      3 → Keyboard.print(string3)
    Keyboard.releaseAll()
    reset clickCount = 0
```

## Trade-offs

- Single click is delayed by `CLICK_TIMEOUT_MS` (500ms) before sending — unavoidable with any multi-click scheme on a hardware button.
- Triple-click on a physical button is harder than on a mouse/touchpad; a 500ms window is comfortable enough.

## Out of Scope

- 4+ click levels (unreliable with mechanical buttons)
- Press-and-hold behavior
- Multiple buttons
