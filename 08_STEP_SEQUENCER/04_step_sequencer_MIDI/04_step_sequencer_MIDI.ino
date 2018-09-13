#include <MIDI.h>

/*
 * This code demonstrate how to build a simple Midi step sequencer
 * which sends data via the Serial Port. 
 * 
 * The Serial Data are interpreted by hairless midi serial and sent to a 
 * virtual midi instrument running on the computer. 
 */
struct MySettings : public midi::DefaultSettings{
      static const long BaudRate = 115200;
};

MIDI_CREATE_CUSTOM_INSTANCE(HardwareSerial, Serial, MIDI, MySettings);


int buttonPins[] = {13, 12, 11, 10};
int potPins[] = {A0, A1, A2, A3};
int ledPins[] = {7, 6, 5, 4};
int tempoPin = A4;

int buttonsState[] = {0, 0, 0, 0};
int oldButtonState[] = {0, 0, 0, 0};
boolean notesToPlay[] = {0, 0, 0, 0};

int frequencies[] = {0, 0, 0, 0};
int minFrequency = 33;
int maxFrequncy = 300;

int stepDuration = 500;
int minStepDuration = 20;
int maxStepDuration = 1000;

int nSteps = 4;

long lastNotePlayedTime;
int currentStep=0; 


int lastNoteSent=0;

void setup() {
  // put your setup code here, to run once:

  for (int i = 0; i < nSteps; i++) {
    pinMode(buttonPins[i], INPUT);
    pinMode(ledPins[i], OUTPUT);
  }

  //Serial.begin(9600);
  MIDI.begin(1);

  lastNotePlayedTime=millis();  
}

void loop() {
  readButtons();
  readPotentimeters();

  //printSequencerValues();

  if (millis()-lastNotePlayedTime>stepDuration){
    currentStep++;
    //noTone(8);
    MIDI.sendNoteOff(lastNoteSent,0,1);
    if(currentStep==nSteps){
      currentStep=0;
    }
    makeSound();

    lastNotePlayedTime=millis();
  }

  lightUpLed();
}

void makeSound(){
  for(int i=0; i<nSteps; i++){
    if (currentStep ==i && notesToPlay[i]){
      //tone(8,frequencies[i]);
      MIDI.sendNoteOn(frequencies[i],127,1);
      lastNoteSent=frequencies[i];
    }
  }
}

void lightUpLed(){
  for(int i=0; i<nSteps; i++){
    if (currentStep ==i && notesToPlay[i]){
      digitalWrite(ledPins[i], HIGH); 
    }else{
      digitalWrite(ledPins[i], LOW); 
    }
  }
}

void readPotentimeters() {
  for (int i = 0; i < nSteps; i++) {
    int potValue = analogRead(potPins[i]);
    frequencies[i] = map (potValue, 0, 1024, minFrequency, maxFrequncy);
  }

  stepDuration = analogRead(tempoPin);
  stepDuration = map(stepDuration, 0, 1024, minStepDuration, maxStepDuration);
}

void readButtons() {
  for (int i = 0; i < nSteps; i++) {
    buttonsState[i] = digitalRead(buttonPins[i]);
    if (buttonsState[i] && !oldButtonState[i]) {
      notesToPlay[i] = !notesToPlay[i];
    }
    oldButtonState[i] = buttonsState[i];
  }
}

void printSequencerValues() {
  for (int i = 0; i < nSteps; i++) {
    Serial.print (notesToPlay[i]);
    Serial.print('\t');
  }
  for (int i = 0; i < nSteps; i++) {
    Serial.print (frequencies[i]);
    Serial.print('\t');
  }
  Serial.print(stepDuration);
  Serial.println();
}

