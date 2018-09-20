#include <Servo.h>

int servoPin = 3;
int potPin = A0;

Servo myServo;

void setup() {
  // put your setup code here, to run once:
  myServo.attach(servoPin);
}

void loop() {
  // put your main code here, to run repeatedly:
  int potValue = analogRead(potPin);
  potValue = map(potValue, 0, 1024, 0, 180);
  myServo.write(potValue);
}
