## Pincode library for rotary encoders

This Arduino library provides a way to ask a user for a 4-digit pincode. The code is entered by turning a rotary encoder. The start point of each digit is randomised, so that there is an additional layer of security e.g. no one can extrapolate the pin by observing the movements of the encoder.

The library is based on the [Adafruit library for SSD1306 displays](https://github.com/adafruit/Adafruit_SSD1306) and the [Encoder library from Paul Stoffregen](https://github.com/PaulStoffregen/Encoder)

The library also supports SHA256 hashing through the [crypto library from Southern Storm Software]( https://github.com/rweather/arduinolibs/tree/master/libraries/Crypto), so that the pin is not stored in plaintext.

For now it only supports a 128x64 pixel SSD1306 OLED display.

A minimal plaintext variant uses approximately 24.500 bytes of flash, so there is not much room for your own code if you use a ATMEGA32 based Arduino e.g. Arduino Uno.
