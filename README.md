# Big-Time-Display
Initially based on Arduino code by [i2make](https://github.com/i2make/MTC_SPP_Reader).

Mackie Control Universal (MCU) Time Display on Neopixels RGB Matrix display

#### I created 3 different versions of the same Arduino base code. All 3 versions basically does the same thing, but is customized to run on different commonly used boards with different MIDI connections etc.

Common Arduino Library requirements:
- [Adafruit GFX](https://github.com/adafruit/Adafruit-GFX-Library)
- [Adafruit NeoMatrix](https://github.com/adafruit/Adafruit_NeoMatrix)

## ESP32-Beats.ino
  
Written specifically for ESP32 with Bluetooth (BLE) MIDI connection. Requires the Arduino MIDI & BLE-MIDI libraries, which makes this version run a lot smoother due to callbacks etc.
The "Boot" button is mapped to toggle between Beats/SMPTE.

## SAMD-Beats.ino
  
For SAMD-based boards with an onboard push button and USB connection for MIDI. Requires the MIDI-USB library.

## TrinketM0-Beats.ino
  
Highly customized for the super tiny [Adafruit Trinket M0 board](https://www.adafruit.com/product/3500) with integrated Dotstar™. Uses the Arduino USB Stack and USB Midi Connection, utilizing the [MIDI-USB library](https://www.arduino.cc/reference/en/libraries/usb-midi/). Preconfigured with 2 separate MIDI ports/instances, which makes it possible to send/receive MIDI even when port 1 is unavailable[^1]

[^1]: When used as a control surface in the DAW, most DAWs hijacks the first available MIDI port provided by the device.

