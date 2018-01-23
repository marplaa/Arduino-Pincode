/*
 * Pincode.cpp
 *
 *  Created on: 23.01.2018
 *      Author: Martin Plaas
 */

#include <Pincode.h>

float dialSpeed = 25;

int randNumber ;//= int(random(10)) * 100 - ((analogRead(A0) * dialSpeed) % 100);
int xpos0 = 96;
int ypos0 = 40;


#define OLED_DC     5
#define OLED_CS     2
#define OLED_RESET  15
#define BUTTON      4
Adafruit_SSD1306 display;
Encoder myEnc(20, 21);

const int FILL_RECTANGLE = 0;
const int FILL_CIRCLE = 1;


void Pincode(Adafruit_SSD1306 *display) {
	  display->clearDisplay();

	  pinMode(BUTTON, INPUT_PULLUP);           // set pin to input

	  randomSeed(analogRead(A0));

	  display->setTextColor(WHITE);
	  display->setTextSize(1);
	  display->setTextWrap(false);
	  display->setFont(&FreeSans24pt7b);
}


void reqPin(byte pin[]) {

  //int analog = analogRead(A0);
  //long oldPosition = -999;
  long newPosition = myEnc.read()/2;
  //int avg = runningAverage(newPosition);
  float value ;//= ((newPosition) + randNumber) % 1000;
  long lastValue = -1;
  byte pinPos = 0;
  byte number;
  randNumber = int(random(10)) * 100 - (int((newPosition % 1000) * dialSpeed) % 100);

  while (true) {

    //analog = analogRead(A0);
    //avg = runningAverage(analog);
    newPosition = (myEnc.read()/2) % 1000;
    if (newPosition < 0) {
      newPosition = (1000 + newPosition);
    }
    value = int((newPosition * dialSpeed) + randNumber) % 1000;


    if (lastValue != value) {
      Serial.print("Value: ");
      Serial.println(value);
      Serial.print("Pos: ");
      Serial.println(newPosition);
      lastValue = value;
      display.clearDisplay();
      draw3Nums((int)(32 * pinPos + 2), (int)48, (int)40, (int)8, (int)value);
      drawRects((int)pinPos, FILL_CIRCLE);

      //  display.setCursor(0, 40);
      //  display.print(value);

      display.display();
    }
    //delay(10);

    if (digitalRead(BUTTON) == LOW) {
      while (digitalRead(BUTTON) == LOW) {
      }
      number = (value + 50) / 100;
      pin[pinPos] = number;
      if (pinPos == 3) {
        return;
      } else {
        pinPos++;
      }

      randNumber = int(random(10)) * 100  - (int(newPosition * dialSpeed) % 100);
      int old_value = value;
      value = int(((newPosition * dialSpeed) + randNumber)) % 1000;
      int step = (old_value - value) / 32;
      for (int i = 0; i < 32; i++) {
        display.clearDisplay();
        draw3Nums(32 * (pinPos - 1) + 2 + i, 48, 40, 8,
                  (old_value - i * step) % 1000);
        drawRects(pinPos - 1, FILL_CIRCLE);

        display.display();
        //delay(5);

      }
    }

  }
}

boolean requestPinHash(byte hash[]) {

  byte pin[4];
  byte hashResult[32];

  reqPin(pin);

  //display.clearDisplay();
  //display.setFont();
  //display.setTextWrap(true);
  //display.setCursor(0, 0);

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

  char hashStr[33];


  for (int i = 0; i < 32; i++) {
    hashStr[i] = hashResult[i];
  }
  hashStr[32] = '\0';

  //QRcode qrcode (&display);
  //qrcode.init();
  // create qrcode
  //qrcode.create(hashStr);
  //display.display();

  //display.setTextWrap(false);
  //display.setFont(&FreeSans24pt7b);
}

void drawRects(int filled, int type) {
  display.drawRoundRect(0, 12, 30, 42, 4, WHITE);
  display.drawRoundRect(32, 12, 30, 42, 4, WHITE);
  display.drawRoundRect(64, 12, 30, 42, 4, WHITE);
  display.drawRoundRect(96, 12, 30, 42, 4, WHITE);

  if (type == FILL_RECTANGLE) {

    if (filled >= 1) {
      display.fillRoundRect(2, 14, 26, 38, 3, WHITE);
    }
    if (filled >= 2) {
      display.fillRoundRect(34, 14, 26, 38, 3, WHITE);
    }
    if (filled == 3) {
      display.fillRoundRect(66, 14, 26, 38, 3, WHITE);
    }
  } else if (type == FILL_CIRCLE) {
    if (filled >= 1) {
      display.fillCircle(15, 32, 4, WHITE);
    }
    if (filled >= 2) {
      display.fillCircle(47, 32, 4, WHITE);
    }
    if (filled == 3) {
      display.fillCircle(79, 32, 4, WHITE);
    }

  }
  display.drawLine(0, 11, 128, 11, BLACK);
  display.drawLine(0, 10, 128, 10, BLACK);
  display.drawLine(0, 54, 128, 54, BLACK);
  display.drawLine(0, 55, 128, 55, BLACK);
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
void draw3Nums(int x, int y, int height, int padding, int value) {
  value = (value + padding * 100 / height) % 1000;
  int num = value / 100;
  int pos = ((value % 100)) * height / 100;
  y = y - padding;
  display.setCursor(x, y + pos);
  display.print(num);
  display.setCursor(x, y + pos + height);
  if (num - 1 == -1) {
    display.print(9);
  } else {
    display.print((num - 1) % 10);
  }
  display.setCursor(x, y + pos - height);
  display.print((num + 1) % 10);

}

