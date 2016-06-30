/*
 * Example Implementation of a custom display class using Adafruit_FramebufferDisplay
 */

#ifndef Adafruit_myDisplay_h
#define Adafruit_myDisplay_h

#include "Adafruit_FramebufferDisplay.h"

class Adafruit_myDisplay : public Adafruit_FramebufferDisplayH {
 public:
  Adafruit_myDisplay(void);
  void display(void);
};

Adafruit_myDisplay::Adafruit_myDisplay(void) : Adafruit_FramebufferDisplayH(8,8) {
  // use this to initialize your display
  // let's assume this one is 8x8 horizontal ...
}

void Adafruit_myDisplay::display() {
  // use this to write to your display
  for(uint16_t i; i<bufferSize; i++) {
    uint8_t data = buffer[i];
    // writeByteToDisplay(data) ...
  }
}

#endif
