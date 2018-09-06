/**
	*  simple example on how to use the capacitive sensor library to create a touch sensor
**/

#include <CapacitiveSensor.h>
#include "notes.h"


CapacitiveSensor sensor1 = CapacitiveSensor(4, 2);


void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  long cap1 = sensor1.capacitiveSensor(30); //do the average of 30 consecutive readings to smooth the readings
  Serial.println(cap1);

}
