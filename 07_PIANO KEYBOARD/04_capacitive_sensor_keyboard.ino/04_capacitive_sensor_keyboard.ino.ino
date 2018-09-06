/**
	*  example of the implementation of multiple capacitive touch buttons
	*  with the capacitive sensor library.
	*  Pin n 4 is always used as senderpin , reciver pins are n 2,6 and 8.
**/
#include <CapacitiveSensor.h>
#include "notes.h"


CapacitiveSensor sensor1 = CapacitiveSensor(4, 2);
CapacitiveSensor sensor2 = CapacitiveSensor(4, 6);
CapacitiveSensor sensor3 = CapacitiveSensor(4, 8);

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  long cap1 = sensor1.capacitiveSensor(60);
  long cap2 = sensor2.capacitiveSensor(60);
  long cap3 = sensor3.capacitiveSensor(60);

  Serial.print(cap1);
  Serial.print(",");
  Serial.print(cap2);
  Serial.print(",");
  Serial.println(cap3);

  if (cap1 > 600) {
    tone(10, NOTE_A4);
  } else if (cap2 > 600) {
    tone(10, NOTE_B4);
  } else if (cap3 > 600) {
    tone(10, NOTE_C3);
  }else{
    noTone(10);
  }

}
