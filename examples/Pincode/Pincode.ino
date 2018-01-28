#include <Pincode.h>
#include <Adafruit_SSD1306.h>
#include <Encoder.h>

#define OLED_DC     3
#define OLED_CS     2
#define OLED_RESET  4

#define BUTTON      6
#define ENCODER_1   20
#define ENCODER_2   21

Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);
Encoder myEnc(ENCODER_1, ENCODER_2);
Pincode pincode(&display, &myEnc, BUTTON);

byte pin[] = {1, 2, 3, 4};

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC);
  pinMode(BUTTON, INPUT_PULLUP);
}

void loop() {
  byte inputPin[4];
  boolean ok = true;

  // (Optional) A floating A0 as input for the RNG
  randomSeed(analogRead(A0));

  // let the user enter the pin
  pincode.reqPin(inputPin);

  // Check if pins match
  for (int i = 0; i < 4; i++) {
    if (inputPin[i] != pin[i]) {
      ok = false;
      break;
    }
  }

  // Print "OK" if the pin is correct or "NO" otherwise
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
