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

void setup() {

	display.begin(SSD1306_SWITCHCAPVCC);

	//pinMode(BUTTON, INPUT_PULLUP);           // set pin to input

	display.setTextColor(WHITE);
	display.setTextSize(1);
	display.setTextWrap(false);
	display.setFont(&FreeSans24pt7b);

	pincode.setDialSpeed(20);
}

void loop() {

	randomSeed(analogRead(A0));

        // SHA-256 Hash of "1234" (0x01, 0x02, 0x03, 0x04)
	byte pinHash[32] = { 0x9f, 0x64, 0xa7, 0x47, 0xe1, 0xb9, 0x7f, 0x13, 0x1f, 0xab,
			0xb6, 0xb4, 0x47, 0x29, 0x6c, 0x9b, 0x6f, 0x02, 0x01, 0xe7, 0x9f,
			0xb3, 0xc5, 0x35, 0x6e, 0x6c, 0x77, 0xe8, 0x9b, 0x6a, 0x80, 0x6a };

	boolean ok = pincode.requestPinHash(pinHash);

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
