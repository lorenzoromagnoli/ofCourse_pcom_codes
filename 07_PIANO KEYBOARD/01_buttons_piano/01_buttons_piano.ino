/**
	*  example of a simple piano keyboard made with 3 buttons connected to digital pins 2,3,4
**/

#include "pitches.h"

int btn1 = 4;
int btn2 = 2;
int btn3 = 3;

int buzzerPin = 8;

void setup() {
  // put your setup code here, to run once:
  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);
  pinMode(btn3, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (digitalRead(btn1)) {
    tone(buzzerPin, NOTE_A4);
  } else {
    noTone(buzzerPin);
  }

  if (digitalRead(btn2)) {
    tone(buzzerPin, NOTE_B4);
  } else {
    noTone(buzzerPin);
  }

  if (digitalRead(btn3)) {
    tone(buzzerPin, NOTE_C3);
  } else {
    noTone(buzzerPin);
  }

}
