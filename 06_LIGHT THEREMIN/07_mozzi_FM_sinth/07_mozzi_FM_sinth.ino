/*  Example demonstrating how to build a simple FM sinthezizer using mozzi library
 *  A potentiometer connected to A0 changes the frequency of the modulator wave.
*/

//#include <ADC.h>  // Teensy 3.0/3.1 uncomment this line and install http://github.com/pedvide/ADC
#include <MozziGuts.h>
#include <Oscil.h> // oscillator template
#include <tables/sin2048_int8.h> // sine table for oscillator

// use: Oscil <table_size, update_rate> oscilName (wavetable), look in .h file of table #included above
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aCarrier(SIN2048_DATA);
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aModulator(SIN2048_DATA);

int modulationIntensity=300;

// use #define for CONTROL_RATE, not a constant
#define CONTROL_RATE 64 // powers of 2 please

int potPin=A0;

void setup(){
  startMozzi(CONTROL_RATE); // set a control rate of 64 (powers of 2 please)
  aCarrier.setFreq(440); // set the frequency
  aModulator.setFreq(1000);
}


void updateControl(){
  // put changing controls in here
  int freq=mozziAnalogRead(potPin);
  freq=map (freq, 0,1024,20,20000);
  aModulator.setFreq(freq);
}


int updateAudio(){
  long modulation= aModulator.next()*modulationIntensity;
  return aCarrier.phMod(modulation); // return an int signal centred around 0
}


void loop(){
  audioHook(); // required here
}



