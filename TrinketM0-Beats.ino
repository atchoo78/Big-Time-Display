#include <MIDIUSB.h>
#include <MIDIUSB_Defs.h>

#include <frequencyToNote.h>
#include <pitchToFrequency.h>
#include <pitchToNote.h>
#include "Colors.h"
#include <Adafruit_GFX.h>
#include <Adafruit_DotStar.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define PIN 0
#define NUMPIXELS 1
#define DATAPIN   7
#define CLOCKPIN   8


Adafruit_NeoMatrix lc = Adafruit_NeoMatrix(32, 8, PIN,
                                           NEO_MATRIX_BOTTOM + NEO_MATRIX_RIGHT + NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
                                           NEO_GRB + NEO_KHZ800);
Adafruit_DotStar dotstar = Adafruit_DotStar(
  NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BGR);

const uint16_t colors[] = {

  lc.Color(pink.r, pink.g, pink.b), lc.Color(blue.r, blue.g, blue.b), lc.Color(yellow.r, yellow.g, yellow.b)
};

String beatCounter;
String barCounter;
midiEventPacket_t rx;
void displayPosition();
void noteOn(byte channel, byte pitch, byte velocity);
void sysexReceived(byte data, unsigned length);
boolean dots;

int x = lc.width();
int16_t xPos0 = x - 32;
int16_t dot1 = x - 21;
int16_t xPos1 = x - 26;
int16_t xPos2 = x - 20;
int16_t dot2 = x - 15;
int16_t xPos3 = x - 14;
int16_t xPos4 = x - 8;
int16_t xPos5 = x - 2;

void setup() {

  lc.begin();
  lc.setTextWrap(true);
  lc.setBrightness(32);
  lc.setTextColor(colors[1]);
  dots = false;
  dotstar.begin(); 
  dotstar.setPixelColor(0, 0x0000FF); 
  dotstar.setBrightness(200);
  dotstar.show();
}

void loop() {
  rx = MidiUSB.read();
  displayPosition();
}

void displayPosition() {
  if (rx.byte1 >> 4 == 0x0B) {    
  if (dots) {
    lc.drawPixel(dot1, 6, 50);
    lc.drawPixel(dot2, 6, 50);
  }
  if (rx.byte2 >= 0x40 && rx.byte2 <= 0x41) {
    lc.fillRect(xPos5, 0, 5, 8, 0);
    if ((rx.byte3 & 0x10) == 0) {
      beatCounter = 1;
    }  else {
      beatCounter = rx.byte3 & 0x0F;
    }
      lc.setCursor(xPos5, 0);
      lc.print(beatCounter);
      lc.show();
  }
  if (rx.byte2 >= 0x42 && rx.byte2 <= 0x43) {
    lc.fillRect(xPos4, 0, 5, 8, 0);
    if ((rx.byte3 & 0x10) == 0) {
      beatCounter = 1;
    }  else {
      beatCounter = rx.byte3 & 0x0F;
    }
      lc.setCursor(xPos4, 0);
      lc.print(beatCounter);
      lc.show();
  }
  if (rx.byte2 >= 0x43 && rx.byte2 <= 0x44) {
      lc.fillRect(xPos3, 0, 6, 8, 0);
    if ((rx.byte3 & 0x10) == 0) {
      beatCounter = " ";
    } else {
      beatCounter = rx.byte3 & 0x0F;
    }
      lc.setCursor(xPos3, 0);
      lc.print(beatCounter);
      lc.show();
  }
  if (rx.byte2 >= 0x45 && rx.byte2 <= 0x46) {
      lc.fillRect(xPos2, 0, 6, 8, 0);
    if ((rx.byte3 & 0x10) == 0) {
      beatCounter = " ";
    } else {
      beatCounter = rx.byte3 & 0x0F;
    }
      lc.setCursor(xPos2, 0);
      lc.print(beatCounter);
      lc.show();
  }
  if (rx.byte2 >= 0x46 && rx.byte2 <= 0x47) {
      lc.fillRect(xPos1, 0, 6, 8, 0);
    if ((rx.byte3 & 0x10) == 0) {
      beatCounter = " ";
    } else {
      beatCounter = rx.byte3 & 0x0F;
    }
      lc.setCursor(xPos1, 0);
      lc.print(beatCounter);
      lc.show();
  }
  if (rx.byte2 >= 0x48 && rx.byte2 <= 0x49) {  // position display message
      lc.fillRect(xPos0, 0, 6, 8, 0);
    if ((rx.byte3 & 0x10) == 0) {
      barCounter = " ";
    } else {
      barCounter = rx.byte3 & 0x0F;
    }
      lc.setCursor(xPos0, 0);
      lc.print(barCounter);
      lc.show();
  }
  }
}

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = { 0x09, 0x90 | channel, pitch, velocity };
  MidiUSB.sendMIDI(noteOn);
}
