/*
 * Pincode.cpp
 *
 *  Created on: 23.01.2018
 *      Author: Martin Plaas
 */

#include <Pincode.h>

Pincode::Pincode(Adafruit_SSD1306 *the_display, Encoder *the_enc,
		int the_button) {
	this->display = the_display;
	this->myEnc = the_enc;
	this->button = the_button;

	//pinMode(button, INPUT_PULLUP);           // set pin to input

	display->setTextColor(WHITE);
	display->setFont(&FreeSans24pt7b);
}


void Pincode::reqPin(byte pin[]) {

	long newPosition = myEnc->read() / 2;
	long value;
	long lastValue = -1;
	byte pinPos = 0;
	byte number;
	randNumber = random(10) * 100 - (((newPosition % 1000) * dialSpeed) % 100);

	while (true) {

		newPosition = (myEnc->read() / 2) % 1000;
		if (newPosition < 0) {
			newPosition = (1000 + newPosition);
		}
		value = ((newPosition * dialSpeed) + randNumber) % 1000;

		if (lastValue != value) {
			lastValue = value;

			display->clearDisplay();

			draw3Nums(32 * pinPos + 2, 48, 40, 8, value);
			drawRects(pinPos);

			display->display();
		}

		if (digitalRead(button) == LOW) {
			while (digitalRead(button) == LOW) {
			}
			number = (value + 50) / 100;
			pin[pinPos] = number;
			if (pinPos == 3) {
				return;
			} else {
				pinPos++;
			}

			randNumber = random(10) * 100
					- ((newPosition * dialSpeed) % 100);
			int old_value = value;
			value = ((newPosition * dialSpeed) + randNumber) % 1000;
			int step = (old_value - value) / 32;
			for (int i = 0; i < 32; i++) {
				display->clearDisplay();
				draw3Nums(32 * (pinPos - 1) + 2 + i, 48, 40, 8, (old_value - i * step) % 1000);
				drawRects(pinPos - 1);

				display->display();
			}
			drawRects(pinPos);
			display->display();
		}

	}
}



boolean Pincode::requestPinHash(byte hash[]) {

	byte pin[4];
	byte hashResult[32];

	reqPin(pin);

	SHA256 sha256;
	sha256.reset();
	sha256.update(pin, 4);
	sha256.finalize(hashResult, 32);

	for (int i = 0; i < 32; i++) {
		if (hashResult[i] != hash[i]) {
			return false;
		}
	}
	return true;

}


void Pincode::drawRects(int filled) {
	display->drawRoundRect(0, 12, 30, 42, 4, WHITE);
	display->drawRoundRect(32, 12, 30, 42, 4, WHITE);
	display->drawRoundRect(64, 12, 30, 42, 4, WHITE);
	display->drawRoundRect(96, 12, 30, 42, 4, WHITE);

#ifdef FILL_RECTANGLE
	//if (type == FILL_RECTANGLE) {

		if (filled >= 1) {
			display->fillRoundRect(2, 14, 26, 38, 3, WHITE);
		}
		if (filled >= 2) {
			display->fillRoundRect(34, 14, 26, 38, 3, WHITE);
		}
		if (filled == 3) {
			display->fillRoundRect(66, 14, 26, 38, 3, WHITE);
		}

#else
	//} else if (type == FILL_CIRCLE) {
		if (filled >= 1) {
			display->fillCircle(15, 32, 4, WHITE);
		}
		if (filled >= 2) {
			display->fillCircle(47, 32, 4, WHITE);
		}
		if (filled == 3) {
			display->fillCircle(79, 32, 4, WHITE);
		}
#endif
	//}
	display->drawLine(0, 11, 128, 11, BLACK);
	display->drawLine(0, 10, 128, 10, BLACK);
	display->drawLine(0, 54, 128, 54, BLACK);
	display->drawLine(0, 55, 128, 55, BLACK);
}

/*
 x,y = bottom-left corner of number
 height = height of box containing number incl. padding
 padding = height - character-height

 ___________
 |           |    Padding
 |     #     |
 |  #  #     |
 |     #     |
 |     #     |
 |     #     |
 |___#####___|


 */
void Pincode::draw3Nums(int x, int y, int height, int padding, int value) {
	value = (value + padding * 100 / height) % 1000;
	int num = value / 100;
	int pos = ((value % 100)) * height / 100;
	y = y - padding;
	display->setCursor(x, y + pos);
	display->print(num);
	display->setCursor(x, y + pos + height);
	if (num - 1 == -1) {
		display->print(9);
	} else {
		display->print((num - 1) % 10);
	}
	display->setCursor(x, y + pos - height);
	display->print((num + 1) % 10);
}

void Pincode::setRandomSeed(int seed) {
	randomSeed(seed);
}

void Pincode::setDialSpeed(float speed) {
	this->dialSpeed = speed;
}
