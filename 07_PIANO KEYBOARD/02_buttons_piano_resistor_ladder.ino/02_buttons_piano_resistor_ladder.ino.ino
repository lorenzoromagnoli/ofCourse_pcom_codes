/**
	*  example of a simple piano keyboard made with 3 buttons connected in series using a resistive ladder
**/

#include "pitches.h"

int buzzerPin = 8; //buzzer or speaker connected to pin 8

int buttonsPin = A0;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  int sensorValue = analogRead(A0);
  Serial.println(sensorValue);

  if (sensorValue > 1000) {
    tone(8, NOTE_A4);
  } else if (sensorValue > 900) {
    tone(8, NOTE_B4);
  } else if (sensorValue > 500) {
    tone(8, NOTE_C3);
  } else {
    noTone(8);
  }

}
