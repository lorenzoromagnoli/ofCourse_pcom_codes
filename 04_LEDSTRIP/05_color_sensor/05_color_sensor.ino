#include <Wire.h>
#include "Adafruit_TCS34725.h"

/* Example code for the Adafruit TCS34725 breakout library */

/* Connect SCL    to analog 5
   Connect SDA    to analog 4
   Connect VDD    to 3.3V DC
   Connect GROUND to common ground */

/* Initialise with default values (int time = 2.4ms, gain = 1x) */
// Adafruit_TCS34725 tcs = Adafruit_TCS34725();

/* Initialise with specific int time and gain values */
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

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



void setup(void) {
  Serial.begin(9600);

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }

  pixels.begin(); // This initializes the NeoPixel library.

  // Now we're ready to get readings!
}

void loop(void) {
  uint16_t r, g, b, c;

  tcs.getRawData(&r, &g, &b, &c);

  float red, green, blue;
  int sum;

  red = r;
  green = g;
  blue = b;
  sum = c;

  red = red / sum;
  green = green / sum;
  blue = blue / sum;

  red = red * 256;
  green = green * 256;
  blue = blue * 256;

  Serial.print ("red: ");
  Serial.print (red);
  Serial.print (" green: ");
  Serial.print (red);
  Serial.print (" blue: ");
  Serial.println(blue);

  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color((int)red, (int)green, (int)blue));
  }
  pixels.show();
}

