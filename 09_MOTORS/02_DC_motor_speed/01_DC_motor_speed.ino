int motorPin = 3;
int potPin = A0;

#include <Wire.h>

void setup() {
  // put your setup code here, to run once:
  pinMode(motorPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int potValue = analogRead(potPin);
  int motorSpeed = map(potValue, 0, 1024, 0, 255);
  analogWrite(motorPin, motorSpeed );
  delay(10);
}
