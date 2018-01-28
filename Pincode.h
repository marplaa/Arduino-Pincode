/*
 * Copyright (C) 2018  Martin Plaas <martin.plaas@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PINCODE_H
#define PINCODE_H

#include <Arduino.h>
#include <Encoder.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans24pt7b.h>

#include <Crypto.h>
#include <SHA256.h>
#include <string.h>


class Pincode {
public:
	Pincode(Adafruit_SSD1306 *display, Encoder *the_enc, int the_button);
	void reqPin(byte pin[]);

	boolean requestPinHash(byte hash[]);
//	void setRandomSeed(int seed);
	void setDialSpeed(float speed);

private:
	Adafruit_SSD1306 *display;
	Encoder *myEnc;
	byte dialSpeed = 20;

	int randNumber = 0;//= int(random(10)) * 100 - ((analogRead(A0) * dialSpeed) % 100);
	int xpos0 = 96;
	int ypos0 = 40;
	const int FILL_RECTANGLE = 0;
	const int FILL_CIRCLE = 1;
	//int symbol = FILL_CIRCLE;
	int button;
	void drawRects(int filled);
	void draw3Nums(int x, int y, int height, int padding, int value);
};

#endif
