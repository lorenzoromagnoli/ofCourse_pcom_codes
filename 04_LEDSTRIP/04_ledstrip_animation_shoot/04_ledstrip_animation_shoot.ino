#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN            3

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      10

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);



void setup() {
  // put your setup code here, to run once:
  pixels.begin(); // This initializes the NeoPixel library.

}

void loop() {
  // put your main code here, to run repeatedly:
  shootingAnimation();
  fade((int)random(2, 20));

}


void shootingAnimation() {
  for (int i = 0; i < NUMPIXELS; i++) { //which led to turn on
    for (int j = 0; j < NUMPIXELS; j++) { //scan trough the led and set the values
      if (i == j) {
        pixels.setPixelColor(j, pixels.Color(255, 255, 255));
      } else {
        pixels.setPixelColor(j, pixels.Color(0, 0, 0));
      }
    }
    pixels.show();
    delay(20);
  }
}


void fade(int time) {
  for (int i = 0; i < 255; i++) {
    for (int j = 0; j < NUMPIXELS; j++) {
      // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
      pixels.setPixelColor(j, pixels.Color(i, i, i)); // Moderately bright green color.
    }
    pixels.show();
    delay(time);
  }

  for (int i = 255; i > 0; i--) {
    for (int j = 0; j < NUMPIXELS; j++) {
      // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
      pixels.setPixelColor(j, pixels.Color(i, i, i)); // Moderately bright green color.
    }
    pixels.show();
    delay(time);
  }
}
