/*
 * Example code for controlling two DC motors using a TB6612FNG motor Driver
 */

const int motorADir1 = 10; //AIN1
const int motorADir2 = 9; //AIN2

const int motorBDir1 = 7; //BIN1
const int motorBDir2 = 6; //BIN2

const int standByPin = 8; //STBY

const int motorASpeed = 11; //PWMA
const int motorBSpeed = 5; //PWMB

void setup() {
  pinMode(motorADir1, OUTPUT);
  pinMode(motorADir2, OUTPUT);
  pinMode(motorBDir1, OUTPUT);
  pinMode(motorBDir2, OUTPUT);
  pinMode(standByPin, OUTPUT);
  pinMode(motorASpeed, OUTPUT);
  pinMode(motorASpeed, OUTPUT);
}

void loop() {
  digitalWrite(standByPin,HIGH);
  
  analogWrite(motorASpeed,255);
  digitalWrite(motorADir1,LOW);
  digitalWrite(motorADir2,HIGH);

  analogWrite(motorBSpeed,255);
  digitalWrite(motorBDir1,LOW);
  digitalWrite(motorBDir2,HIGH);
}
