/*
A simple piano keyboard which uses kapacitive keys. 
The piano has 3 modalities,
Mode 0 = the piano automatically plays a melody in loop
Mode 1 = the piano only shows trough light the notes to be played to reproduce the melody
Mode 2 = free mode, the user can play the piano autonomosly
*/

#include "pitches.h"

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN            13
#define NUMPIXELS      8
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#include <Wire.h>
#include "Adafruit_MPR121.h"

// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 cap = Adafruit_MPR121();

// notes in the melody:
/*
   Mary had a little lamb
   E D C D E E E
   Little lamb, little lamb
   D D D E G G
   Mary had a little lamb
   E D C D E E E
   Its fleece was white as snow
   E D D E D C
*/

int melody[] = {
  NOTE_E4, NOTE_D4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_E4, NOTE_E4,
  NOTE_D4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_G4, NOTE_G4,
  NOTE_E4, NOTE_D4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_E4, NOTE_E4,
  NOTE_E4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_D4, NOTE_C4,
  0, 0
};

int keysToLightUp[] = {
  5, 4, 3, 4, 5, 5, 5,
  4, 4, 4, 3, 7, 7,
  5, 4, 3, 4, 5, 5, 5,
  5, 4, 4, 5, 4, 3,
  -1, -1
};

int scale[] = {
  NOTE_C4,
  NOTE_D4,
  NOTE_E4,
  NOTE_F4,
  NOTE_G4,
  NOTE_A4,
  NOTE_B4,
  NOTE_C5
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 4, 4, 4, 4, 4, 2,
  4, 4, 2, 4, 4, 2,
  4, 4, 4, 4, 4, 4, 2,
  4, 4, 2, 4, 4, 2,
  1, 1
};

int numberOfNotes = 28;

int OctaveDuration = 2000; //bar duration
int currentNotePlaying = 0;
int timeToWait = OctaveDuration / noteDurations[currentNotePlaying]; //set the fist interval as the first duration

long lastNoteStarted = 0;

int pauseBetweenNotes = 20;

//0 = the piano automatically plays a melody in loop
//1 = the piano only shows trough light the notes to be played
//2 = free mode, the user can play the piano autonomosly
int playmode = 1;

uint16_t currtouched = 0;

void setup() {

  Serial.begin(9600);
  pixels.begin();


  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }


  lastNoteStarted = millis();
}

void loop() {

  if (playmode == 0 || playmode == 1) { // if I have a melody to reproduce

    if (melody[currentNotePlaying] != 0) { // if the currentNote is not a pause

      if (playmode == 0) { // if I need to also reproduce the sound
        tone(8, melody[currentNotePlaying]); //reproduce the note
      }

      int brightness = map (millis() - lastNoteStarted, 0, timeToWait, 255, 0); //calculate the brightness of the key depending on how long the note should last
      pixels.setPixelColor(keysToLightUp[currentNotePlaying], pixels.Color(brightness, brightness, brightness)); //light up the key
      pixels.show();
    }

    if (millis() - lastNoteStarted > timeToWait) { //if it is time to pass to the next note

      if (playmode == 0) { //first of all stop playing the note you were playing before, only if in mode 0
        noTone(8);
      }

      for (int i = 0; i < NUMPIXELS; i++) { //turn off all the led
        pixels.setPixelColor(i, pixels.Color(0, 0, 0));
      }
      pixels.show();

      delay(pauseBetweenNotes);

      //update the index that tell us which note we should play
      if (currentNotePlaying < numberOfNotes - 1) {
        currentNotePlaying++;
      } else {
        currentNotePlaying = 0;
      }

      //update the timer
      timeToWait = ( OctaveDuration / noteDurations[currentNotePlaying] ) - pauseBetweenNotes;
      lastNoteStarted = millis();
    }

  }


  if (playmode == 1 || playmode == 2) {
    currtouched = cap.touched();

    for (int i = 0; i < 12; i++) { // I go trough the bitarray
      bool key = bitRead(currtouched, i); //get the value of each single bit
      if (key != 0) { // if the value is not 0 play the note
        tone(8, scale[i]);
        
        if (playmode == 2) { //only if I'm not in the trainer mode light up the key
          pixels.setPixelColor(i, pixels.Color(255, 255, 255));
        }
      } else {
        if (playmode == 2) {//only if I'm not in the trainer mode turn off the keys when released
          pixels.setPixelColor(i, pixels.Color(0, 0, 0));
        }

      }
      Serial.print(bitRead(currtouched, i));
    }
    pixels.show();
    Serial.println();
    if (currtouched == 0) { // if the array is made of all 0's stop making any noise
      noTone(8);
    }
  }

}
