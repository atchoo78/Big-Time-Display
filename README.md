# Big-Time-Display
Mackie Control Universal (MCU) Time Display on Neopixel Matrix

#### I created 3 different highly customized versions of the same Arduino code. All 3 versions basically does the same thing on different specs and MIDI connections.

Common Arduino Library requirements:
- Adafruit GFX
- Adafruit NeoMatrix
- Adafruit ZeroDMA

## ESP32-Beats.ino
  
Written specifically for ESP32 with Bluetooth (BLE) MIDI connection. Requires the Arduino MIDI & BLE-MIDI libraries, which makes this version run a lot smoother due to callbacks etc.

## SAMD-Beats.ino
  
For SAMD-based boards with an onboard push button and USB connection for MIDI. Requires the MIDI-USB library.

## TrinketM0-Beats.ino
  
Highly customized for the super tiny Adafruit Trinket M0 board with integrated Dotstar(tm). Uses the Arduino USB Stack and USB Midi Connection, utilizing the MIDI-USB library. Preconfigured with 2 separate MIDI ports, which makes it possible to send/receive MIDI even when port 1 is unavailable (when used as a control surface in the DAW, you can't use the port for anything else).

