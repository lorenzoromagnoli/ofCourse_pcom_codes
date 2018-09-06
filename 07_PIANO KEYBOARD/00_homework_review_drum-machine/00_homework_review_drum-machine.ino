/*  
 *   exemple of a simple drum machine which uses FM modulation for sound synthesis
 *   and EAD for the generation of the beat
*/

//#include <ADC.h>  // Teensy 3.0/3.1 uncomment this line and install http://github.com/pedvide/ADC
#include <MozziGuts.h>
#include <Oscil.h> // oscillator template
#include <tables/sin2048_int8.h> // sine table for oscillator
#include <Ead.h> // exponential attack decay to shape the soundwave with an enevlope to create a beat
#include <EventDelay.h> // this piece of the mozzi library help us dealing with timing

// use: Oscil <table_size, update_rate> oscilName (wavetable), look in .h file of table #included above
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aCarrier(SIN2048_DATA);
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aModulator(SIN2048_DATA);

int modulationIntensity = 300;

// use #define for CONTROL_RATE, not a constant
#define CONTROL_RATE 64 // powers of 2 please

EventDelay kDelay; // for triggering envelope start - mozzi alternative to using millis()
Ead kEnvelope(CONTROL_RATE); // resolution will be CONTROL_RATE

int gain; //in the control we are going to chage the value of the gain reading it from the kEnvelope

//connections
int potPin1 = A0;
int potPin2 = A3;

int ldr1 = A1;
int ldr2 = A2;

int minCarrierFreq = 22;
int maxCarrierFreq = 100;

int minModulationFreq = 10;
int maxModulationFreq = 1000;

int minModulationIntensity = 0;
int maxModulationIntensity = 800;

void setup() {
  startMozzi(CONTROL_RATE); // set a control rate of 64 (powers of 2 please)
  aCarrier.setFreq(98); // set the frequency
  aModulator.setFreq(1000);

  Serial.begin(9600);

  kDelay.start(1000); // start a timer which will go off in 1000ms

}


void updateControl() {
  // put changing controls in here


  int carrierFreq = mozziAnalogRead(potPin1);
  carrierFreq = map(carrierFreq, 0, 1024, minCarrierFreq, maxCarrierFreq);
  aCarrier.setFreq(carrierFreq);


  int modulationFreq = mozziAnalogRead(ldr1);
  modulationFreq = map(modulationFreq, 0, 1024,maxModulationFreq, minModulationFreq );
  aModulator.setFreq(modulationFreq);

  modulationIntensity = mozziAnalogRead(ldr2);
  modulationIntensity = map(modulationIntensity, 0, 1024, minModulationIntensity, maxModulationIntensity);


  int tempo = mozziAnalogRead(potPin2);
  tempo = map(tempo, 0, 1024, 100, 500);

  if (kDelay.ready()) { //when the timer goes off
    // set random parameters
    unsigned int duration = 100; //duration of the note
    unsigned int attack = 10; // duratio of the attack
    unsigned int decay = duration - attack; //duration of the decay
    kEnvelope.start(attack, decay); //restart generating a new envelop waveform 
    kDelay.start(tempo); //reset the timer with the new tempo
  }
  gain = (int) kEnvelope.next(); //always get the data from the envelop waveworfm
}


int updateAudio() {
  long modulation = aModulator.next() * modulationIntensity;
  long FM = (aCarrier.phMod(modulation));
  return (FM * gain) >> 8; // return an int signal centred around 0
}


void loop() {
  audioHook(); // required here
}



