#include <Wire.h>
#include "Adafruit_MPR121.h"
#include "notes.h"

// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 cap = Adafruit_MPR121();

// Keeps track of the last pins touched
uint16_t lasttouched = 0;

int notes[] = {
  NOTE_A4,
  NOTE_B4,
  NOTE_C4,
  NOTE_D4,
  NOTE_E4,
  NOTE_F4,
  NOTE_G4,
  NOTE_A5,
};

uint16_t currtouched = 0;

void setup() {
  while (!Serial);        // needed to keep leonardo/micro from starting too fast!

  Serial.begin(9600);
  Serial.println("Adafruit MPR121 Capacitive Touch sensor test");

  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");
}

void loop() {
  // Get the currently touched pads
  currtouched = cap.touched();

	/*
	 *	currtouched is an array of 16 bits ... something like 0001000010100000
	 *  only the first 12bits are used since the sensr can only sense on 12 different electrodes
	 *  a 1 indicates that the electrode in that position is touched
	 *  a 0 indicates that the electrode in that position is not touched
	*/


  for(int i=0; i<12;i++){ // I go trough the bitarray
    bool key=bitRead(currtouched,i); //get the value of each single bit
    if(key!=0){ // if the value is not 0 play the note
      tone(8,notes[i]);
    }
    Serial.print(bitRead(currtouched,i));
  }

  if(currtouched==0){ // if the array is made of all 0's stop making any noise
    noTone(8);  
  }

  Serial.println();

}
