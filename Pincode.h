#ifndef PINCODE_H
#define PINCODE_H

#include <Arduino.h>
#include <Encoder.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans24pt7b.h>
#include <Fonts/FreeSans12pt7b.h>


#include <Crypto.h>
#include <SHA256.h>
#include <string.h>


class Pincode {
public:
	Pincode(Adafruit_SSD1306 *display, Encoder *the_enc, int the_button);
	void reqPin(byte pin[]);

	boolean requestPinHash(byte hash[]);
	void setRandomSeed(int seed);
	void setDialSpeed(float speed);

private:
	Adafruit_SSD1306 *display;
	Encoder *myEnc;
	float dialSpeed = 25;

	int randNumber = 0;//= int(random(10)) * 100 - ((analogRead(A0) * dialSpeed) % 100);
	int xpos0 = 96;
	int ypos0 = 40;
	const int FILL_RECTANGLE = 0;
	const int FILL_CIRCLE = 1;
	int symbol = FILL_CIRCLE;
	int button;
	void drawRects(int filled);
	void draw3Nums(int x, int y, int height, int padding, int value);
};

#endif
