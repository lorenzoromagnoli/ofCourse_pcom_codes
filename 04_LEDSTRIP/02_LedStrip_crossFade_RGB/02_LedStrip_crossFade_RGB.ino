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

int redPod = A0;
int greenPot = A1;
int bluePot = A2;


void setup() {
  // put your setup code here, to run once:
  pixels.begin(); // This initializes the NeoPixel library.

}

void loop() {
  // put your main code here, to run repeatedly:

  int redColor = analogRead(A0);
  int greenColor = analogRead(A1);
  int blueColor = analogRead(A2);

  redColor = redColor / 4;
  greenColor = greenColor / 4;
  blueColor = blueColor / 4;

   for(int i=0;i<NUMPIXELS;i++){
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(redColor,greenColor,blueColor)); // Moderately bright green color.
  }

    pixels.show(); // This sends the updated pixel color to the hardware.



}
