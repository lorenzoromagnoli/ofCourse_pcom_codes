/*
   INITIALIZE COMPONENTS AND LIBRARIES
*/

//ledstrip
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#define ledStripPin 6
#define NUMPIXELS 7

Adafruit_NeoPixel strip = Adafruit_NeoPixel(7, ledStripPin, NEO_GRB + NEO_KHZ800);

// MSGEQ7
#include "MSGEQ7.h"
#define pinAnalog A2
#define pinReset 3
#define pinStrobe 4
#define MSGEQ7_INTERVAL ReadsPerSecond(50)
#define MSGEQ7_SMOOTH 191 // Range: 0-255

CMSGEQ7<MSGEQ7_SMOOTH, pinReset, pinStrobe, pinAnalog> MSGEQ7;

//Color Sensor
#include <Wire.h>
#include "Adafruit_TCS34725.h"

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_154MS, TCS34725_GAIN_1X);

//a variable to hold the amount of base measured by the MSGEQ7 module
uint8_t soundBase = 0;

#define modePin 12 //the value of this pin determin the lamp modality



void setup() {
  // put your setup code here, to run once:

  MSGEQ7.begin();

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  pinMode(modePin, INPUT);


  Serial.begin(9600);

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }
}

void loop() {

  if (digitalRead(modePin)) { //I'm in sound reactive mode
    Serial.println("sound mode");
    readSoundBaseFromMSGEQ7();
   Serial.println(soundBase);

   int brightness = map (soundBase,0,255,0,NUMPIXELS*255);
   
   for(int i=0;i<NUMPIXELS;i++){
    if(brightness>255){
      strip.setPixelColor(i, strip.Color(255,255,255));
      brightness-=255;
    }else{
      strip.setPixelColor(i, strip.Color(brightness,brightness,brightness));
      brightness=0;
    }
   }
   strip.show();

  } else { //I'm in chamaleon mode
    Serial.println("chamaleon mode");
    readColorAndMapItToLedStrip();
  }

}


void readSoundBaseFromMSGEQ7() {
  bool newReading = MSGEQ7.read(MSGEQ7_INTERVAL);
  if (newReading) {
    // Read bass frequency
    soundBase = MSGEQ7.get(MSGEQ7_BASS);
  }
}

void readColorAndMapItToLedStrip() {
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
    strip.setPixelColor(i, strip.Color((int)red, (int)green, (int)blue));
  }
  strip.show();
}


