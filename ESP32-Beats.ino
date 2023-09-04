#include <BLEMIDI_Transport.h>
#include <Arduino.h>
#include "Colors.h"
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <hardware/BLEMIDI_ESP32_NimBLE.h>
#define buttonPin 0
#define PIN 13 // Pin connected to DATA IN on the Neopixels Matrix

Adafruit_NeoMatrix lc = Adafruit_NeoMatrix(32, 8, PIN,
                                           NEO_MATRIX_BOTTOM + NEO_MATRIX_RIGHT + NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
                                           NEO_GRB + NEO_KHZ800);
const uint16_t colors[] = {

  lc.Color(pink.r, pink.g, pink.b), lc.Color(blue.r, blue.g, blue.b), lc.Color(yellow.r, yellow.g, yellow.b)
};

BLEMIDI_CREATE_INSTANCE("ESP32", MIDI);
unsigned long t0 = millis();
bool isConnected = false;
String beatCounter;
String barCounter;
boolean dots;
int buttonState;  
int lastButtonState = LOW;
int displayMode = HIGH;
int x = lc.width();
int16_t xPos0 = x - 32;
int16_t dot1 = x - 28;
int16_t xPos1 = x - 26;
int16_t xPos2 = x - 20;
int16_t dot2 = x - 15;
int16_t xPos3 = x - 14;
int16_t xPos4 = x - 8;
int16_t xPos5 = x - 2;
void handleControlChange(byte channel, byte number, byte value);

void setup()
{
  pinMode(buttonPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  BLEMIDI.setHandleConnected(OnConnected);
  BLEMIDI.setHandleDisconnected(OnDisconnected);
  lc.begin();
  lc.setTextWrap(true);
  lc.setBrightness(32); // Brightness of the Matrix Display (0-255)
  lc.setTextColor(colors[1]); // Color of the text/numbers
  dots = false; // Set to true to enable dots to separate the numbers according to the MIDI specs
  lc.show();
  MIDI.begin();
  MIDI.setHandleControlChange(displayPosition);
}

void loop()
{
  MIDI.read();
  if (isConnected && (millis() - t0) > 1000)
  {
    t0 = millis();
    readButton();
  }
}

void readButton() {
  int reading = digitalRead(buttonPin);
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) {
        displayMode = !displayMode;
        if (displayMode == 1) {
          MIDI.sendNoteOn(53, 127, 1);
        }
        if (displayMode == 0) {
          MIDI.sendNoteOn(53, 0, 1);
        }
      }
    }
  lastButtonState = reading;
}

void displayPosition(byte channel, byte number, byte value) {
if (number >= 0x40 && number <= 0x41) {
  lc.fillRect(xPos5, 0, 5, 8, 0);
  if ((value & 0x10) == 0) {
    beatCounter = 1;
  } else {
    beatCounter = value & 0x0F;
  }
  lc.setCursor(xPos5, 0);
  lc.print(beatCounter);
  lc.show();
}
if (number >= 0x42 && number <= 0x43) {
  lc.fillRect(xPos4, 0, 5, 8, 0);
  if ((value & 0x10) == 0) {
    beatCounter = 1;
  } else {
    beatCounter = value & 0x0F;
  }
  lc.setCursor(xPos4, 0);
  lc.print(beatCounter);
  lc.show();
}
if (number >= 0x43 && number <= 0x44) {
  lc.fillRect(xPos3, 0, 5, 8, 0);
  if ((value & 0x10) == 0) {
    beatCounter = " ";
  } else {
    beatCounter = value & 0x0F;
  }
  lc.setCursor(xPos3, 0);
  lc.print(beatCounter);
  lc.show();
}
if (number >= 0x45 && number <= 0x46) {
  lc.fillRect(xPos2, 0, 5, 8, 0);
  if ((value & 0x10) == 0) {
    beatCounter = " ";
  } else {
    beatCounter = value & 0x0F;
  }
  lc.setCursor(xPos2, 0);
  lc.print(beatCounter);
  lc.show();
}
if (number >= 0x46 && number <= 0x47) {
  lc.fillRect(xPos1, 0, 5, 8, 0);
  if ((value & 0x10) == 0) {
    beatCounter = " ";
  } else {
    beatCounter = value & 0x0F;
  }
  lc.setCursor(xPos1, 0);
  lc.print(beatCounter);
  lc.show();
}
if (number >= 0x48 && number <= 0x49) {
  lc.fillRect(xPos0, 0, 5, 8, 0);
  if ((value & 0x10) == 0) {
    barCounter = " ";
  } else {
    barCounter = value & 0x0F;
  }
  lc.setCursor(xPos0, 0);
  lc.print(barCounter);
  lc.show();
}
}

void OnConnected() {
  isConnected = true;
  digitalWrite(LED_BUILTIN, HIGH);
}

void OnDisconnected() {
  isConnected = false;
  digitalWrite(LED_BUILTIN, LOW);
}
