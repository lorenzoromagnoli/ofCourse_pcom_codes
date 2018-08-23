/*
 * display the measurement of loudness of the 7 bands to 7 neopixels led
 */

// MSGEQ7
#include "MSGEQ7.h"
#define pinAnalog A2
#define pinReset 3
#define pinStrobe 4
#define MSGEQ7_INTERVAL ReadsPerSecond(50)
#define MSGEQ7_SMOOTH 191 // Range: 0-255

CMSGEQ7<MSGEQ7_SMOOTH, pinReset, pinStrobe, pinAnalog> MSGEQ7;

// Choose a PWM pin!
#define pinLed 11


#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      7

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


int bandsValues[7]; //create an array to store the values we get from the msgeq7 module

void setup() {
  // This will set the IC ready for reading
  MSGEQ7.begin();

  // led setup
  pinMode(pinLed, OUTPUT);

  pixels.begin();

  Serial.begin(9600);

}

void loop() {
  // Analyze without delay every interval
  bool newReading = MSGEQ7.read(MSGEQ7_INTERVAL);


  // Led output
  if (newReading) {

    //read the value for each band and store the data to the array.
    bandsValues[0]=MSGEQ7.get(MSGEQ7_0);
    bandsValues[1]=MSGEQ7.get(MSGEQ7_1);
    bandsValues[2]=MSGEQ7.get(MSGEQ7_2);
    bandsValues[3]=MSGEQ7.get(MSGEQ7_3);
    bandsValues[4]=MSGEQ7.get(MSGEQ7_4);
    bandsValues[5]=MSGEQ7.get(MSGEQ7_5);
    bandsValues[6]=MSGEQ7.get(MSGEQ7_6);
  
    printBandValues();

    for (int i=0; i<NUMPIXELS; i++){
        //set each pixel with one value from the array.
        pixels.setPixelColor(i, pixels.Color(bandsValues[i],0,0));
    }
    
    pixels.show();

  }
}

void printBandValues(){
  for (int i=0; i<7; i++){
    Serial.print(bandsValues[i]);
    Serial.print("-");
  }
  Serial.println();
}

