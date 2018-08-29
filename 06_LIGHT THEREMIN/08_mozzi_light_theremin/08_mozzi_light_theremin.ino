/*  Example demonstrating how to build a light theremin. 
 *  the light theremin produces sounds depending on the amount
 *  of light that shines on two ldr connected to the circuit. 
 *  
 *  Mozzi Frequency modulation module phMod() is used to syntethize 
 *  the sounds
 *   
 *  One ldr influences the intensity of the modulation, while 
 *  the other ldr influences the modulation frequency;
 *  Lastly one potentiometer control the carrier frequency. 
 *  
 *  
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

int ldr1= A1;
int ldr2= A2;

int minCarrierFreq=40;
int maxCarrierFreq=400;

int minModulationFreq=10;
int maxModulationFreq=700;

int minModulationIntensity=3;
int maxModulationIntensity=800;

void setup(){
  startMozzi(CONTROL_RATE); // set a control rate of 64 (powers of 2 please)
  aCarrier.setFreq(440); // set the frequency
  aModulator.setFreq(1000);
}


void updateControl(){
  // put changing controls in here
  int carrierFreq=mozziAnalogRead(potPin);
  carrierFreq=map (carrierFreq, 0,1024,minCarrierFreq,maxCarrierFreq);
  aCarrier.setFreq(carrierFreq);

  int modulationFreq= mozziAnalogRead(ldr1);
  modulationFreq=map(modulationFreq,0,1024,minModulationFreq,maxModulationFreq);
  aModulator.setFreq(modulationFreq);

  modulationIntensity=mozziAnalogRead(ldr2);
  modulationIntensity=map(modulationIntensity,0,1024,minModulationIntensity,maxModulationIntensity);
}


int updateAudio(){
  long modulation= aModulator.next()*modulationIntensity;
  return aCarrier.phMod(modulation); // return an int signal centred around 0
}


void loop(){
  audioHook(); // required here
}



