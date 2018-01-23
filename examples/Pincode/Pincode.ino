#include <Pincode.h>
#include <Adafruit_SSD1306.h>
#include <Encoder.h>

#define OLED_DC     5
#define OLED_CS     2
#define OLED_RESET  15

#define BUTTON      4

Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);
Encoder myEnc(20, 21);
Pincode pincode(&display, &myEnc, BUTTON);

byte pin[] = {1, 2, 3, 4};

void setup() {

  display.begin(SSD1306_SWITCHCAPVCC);
  pinMode(BUTTON, INPUT_PULLUP);           // set pin to input
  pincode.setDialSpeed(20);
}

void loop() {
  byte inputPin[4];
  boolean ok = true;
  pincode.setRandomSeed(analogRead(A0));

  pincode.reqPin(inputPin);

  for (int i = 0; i < 4; i++) {
    if (inputPin[i] != pin[i]) {
      ok = false;
      break;
    }
  }

  display.clearDisplay();
  display.setCursor(0, 40);

  if (ok) {
    display.print("OK");
  } else {
    display.print("NO");
  }
  display.display();

  delay(1000);
}
