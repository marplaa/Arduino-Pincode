#ifndef PINCODE_H
#define PINCODE_H

#include <Arduino.h>
#include <Encoder.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans24pt7b.h>
#include <Fonts/FreeSans12pt7b.h>

#include <Crypto.h>
#include <SHA256.h>
#include <string.h>

class Pincode {
public:
	void Pincode(Adafruit_SSD1306 *display);
	void reqPin(byte pin[]);
	boolean requestPinHash(byte hash[]);

private:
	void drawRects(int filled, int type);
	void draw3Nums(int x, int y, int height, int padding, int value);
};

#endif
