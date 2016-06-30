/*
 * Variable size 1-Bit Adafruit framebuffer display class
 * which implements a virtual display / framebuffer with
 * either horizontal/row byte arrangement or vertical/
 * column byte arrangement.
 * Can be used for debugging by printing the frambuffer
 * via serial using function "displaySerial()" or for 
 * implementing dedicated display device classes.
 * Therefore you can access the framebuffer via the
 * variable "buffer" which size is "bufferSize".
 * You may also implement the function "display()" for 
 * that. 
 */

#ifndef Adafruit_FramebufferDisplay_h
#define Adafruit_FramebufferDisplay_h

#include "Adafruit_GFX.h"

#ifndef _swap_int16_t
#define _swap_int16_t(a, b) { int16_t t = a; a = b; b = t; }
#endif

class Adafruit_FramebufferDisplayH : public Adafruit_GFX {
 public:
  Adafruit_FramebufferDisplayH(uint16_t width, uint16_t height);  
  void clearDisplay(void);
  void displaySerial();  
  void drawPixel(int16_t x, int16_t y, uint16_t color);
  uint8_t getPixel(int16_t x, int16_t y);
  uint8_t * buffer;
  int16_t _PixelX, _PixelY, _BytesX, _BytesY, bufferSize;    
};

class Adafruit_FramebufferDisplayV : public Adafruit_GFX {
 public:
  Adafruit_FramebufferDisplayV(uint16_t width, uint16_t height);  
  void clearDisplay(void);
  void displaySerial();  
  void drawPixel(int16_t x, int16_t y, uint16_t color);
  uint8_t getPixel(int16_t x, int16_t y);
  uint8_t * buffer;
  int16_t _PixelX, _PixelY, _BytesX, _BytesY, bufferSize;  
};


Adafruit_FramebufferDisplayH::Adafruit_FramebufferDisplayH(uint16_t width, uint16_t height) : Adafruit_GFX(width, height) {
  _PixelX = width;
  _PixelY = height;
  _BytesX = (width+7) >> 3; // ceil(width/8)
  _BytesY = height;
  bufferSize = _BytesX*_BytesY;
  buffer = (uint8_t *) malloc(bufferSize);
  clearDisplay();
}

Adafruit_FramebufferDisplayV::Adafruit_FramebufferDisplayV(uint16_t width, uint16_t height) : Adafruit_GFX(width, height) {
  _PixelX = width;
  _PixelY = height;
  _BytesX = width;
  _BytesY = (height+7) >> 3; // ceil(width/8)
  bufferSize = _BytesX*_BytesY;
  buffer = (uint8_t *) malloc(bufferSize);
  clearDisplay();
}

void Adafruit_FramebufferDisplayH::drawPixel(int16_t x, int16_t y, uint16_t color) {
  switch (getRotation()) {
    case 1:
      _swap_int16_t(x, y);
      x = _PixelX - x - 1;
      break;
    case 2:
      x = _PixelX - x - 1;
      y = _PixelY - y - 1;
      break;
    case 3:
      _swap_int16_t(x, y);
      y = _PixelY - y - 1;
      break;
  }
  if ((y < 0) || (y >= _PixelY)) return;
  if ((x < 0) || (x >= _PixelX)) return;
  uint16_t bpos = y*_BytesX + (x >> 3);
  if (color) {
    buffer[bpos] |= (1 << (x&7));
  } else {
    buffer[bpos] &= ~(1 << (x&7));
  }
}

void Adafruit_FramebufferDisplayV::drawPixel(int16_t x, int16_t y, uint16_t color) {
  switch (getRotation()) {
    case 1:
      _swap_int16_t(x, y);
      x = _PixelX - x - 1;
      break;
    case 2:
      x = _PixelX - x - 1;
      y = _PixelY - y - 1;
      break;
    case 3:
      _swap_int16_t(x, y);
      y = _PixelY - y - 1;
      break;
  }
  if ((y < 0) || (y >= _PixelY)) return;
  if ((x < 0) || (x >= _PixelX)) return;
  uint16_t bpos = (y >> 3)*_BytesX + x;
  if (color) {
    buffer[bpos] |= (1 << (y&7));
  } else {
    buffer[bpos] &= ~(1 << (y&7));
  }
}

uint8_t Adafruit_FramebufferDisplayH::getPixel(int16_t x, int16_t y) {
  if ((y < 0) || (y >= _PixelY)) return 0;
  if ((x < 0) || (x >= _PixelX)) return 0;
  uint16_t bpos = y*_BytesX + (x >> 3);
  uint8_t bitpos = x&7;
  uint8_t val = buffer[bpos] & (1 << bitpos);
  if(val) return 1;
  return 0;
}

uint8_t Adafruit_FramebufferDisplayV::getPixel(int16_t x, int16_t y) {
  if ((y < 0) || (y >= _PixelY)) return 0;
  if ((x < 0) || (x >= _PixelX)) return 0;
  uint16_t bpos = (y >> 3)*_BytesX + x;
  uint8_t bitpos = y&7;
  uint8_t val = buffer[bpos] & (1 << bitpos);
  if(val) return 1;
  return 0;
}

void Adafruit_FramebufferDisplayH::clearDisplay(void) {
  memset(buffer,0x00,bufferSize);
}

void Adafruit_FramebufferDisplayV::clearDisplay(void) {
  memset(buffer,0x00,bufferSize);
}

void Adafruit_FramebufferDisplayH::displaySerial(void) {
  for(uint8_t y = 0; y < _PixelY; y++) { 
    for(uint8_t x = 0; x < _PixelX; x++) {
      if(getPixel(x,y)) {
        Serial.print("#");
      } else {
        Serial.print(".");
      }
    }
    Serial.println(" ");
  }
  Serial.println(" ");
}

void Adafruit_FramebufferDisplayV::displaySerial(void) {
  for(uint8_t y = 0; y < _PixelY; y++) { 
    for(uint8_t x = 0; x < _PixelX; x++) {
      if(getPixel(x,y)) {
        Serial.print("#");
      } else {
        Serial.print(".");
      }
    }
    Serial.println(" ");
  }
  Serial.println(" ");
}

#endif
