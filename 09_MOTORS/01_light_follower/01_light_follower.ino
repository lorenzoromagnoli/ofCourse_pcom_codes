#include <Servo.h>

int ServoPin = 3;
int sensorAPin = A0;
int sensorBPin = A1;

Servo lightFollower;

int servoPosition = 0;

void setup() {
  // put your setup code here, to run once:

  lightFollower.attach(ServoPin);

  Serial.begin(9600);

}

void loop() {

  int sensorAValue = analogRead(sensorAPin);
  int sensorBValue = analogRead(sensorBPin);

  Serial.print(sensorAValue);
  Serial.print("\t");
  Serial.println(sensorBValue);

  if (sensorAValue < sensorBValue) {
    servoPosition++;
  } else {
    servoPosition--;
  }

  if (servoPosition>180){
    servoPosition=180;
  }
  if (servoPosition<0){
    servoPosition=0;
  }

  lightFollower.write(servoPosition);

}
