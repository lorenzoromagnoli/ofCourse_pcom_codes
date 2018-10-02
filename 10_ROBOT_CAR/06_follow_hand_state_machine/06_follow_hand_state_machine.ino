/*
   Example code of how to structure an arduino sketch
   following state machine principles.
   A robot on two wheels will look for an obstacle
   (an hand) by spinning around (state 0).
   When it finds a hand it will either move backward
   (state 2) or forward (state 1) to keep
   the distance from it.
*/

const int motorASpeed = 11; //pwmA
const int motorBSpeed = 5;  //pwmB

const int motorAdir1 = 10;  //Ain1
const int motorAdir2 = 9;   //Ain2

const int motorBdir1 = 7;   //Bin1
const int motorBdir2 = 6;   //Bin2

const int standBy = 8;      //stby


#include <NewPing.h>

#define TRIGGER_PIN  2  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     3  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

long lastUpdate = 0;
long updateFrequency = 50;

boolean foundObstacles = false;
boolean turnDirection = 0; //true=right, false=left

int state = 0;

int distance;

void setup() {
  // put your setup code here, to run once:
  pinMode(motorASpeed, OUTPUT);
  pinMode(motorBSpeed, OUTPUT);
  pinMode(motorAdir1, OUTPUT);
  pinMode(motorAdir2, OUTPUT);
  pinMode(motorBdir1, OUTPUT);
  pinMode(motorBdir2, OUTPUT);
  pinMode(standBy, OUTPUT);

  Serial.begin(9600);

  setRobotSpeed(100);
}

void loop() {

  if (millis() - lastUpdate > updateFrequency) {
    distance = sonar.ping_cm();
    runStateMachine();
    lastUpdate = millis();
  }
}

void runStateMachine() {
  switch (state) {
    case 0: //we look for a hand
      if (distance < 15) {
        state = 2;
      } else if (distance > 15 && distance < 30) {
        state = 1;
      } else {
        if (turnDirection == 1) {
          turnRight();
        } else {
          turnLeft();
        }
      }
      break;

    case 1: //we move forward
      moveForward();
      if (distance < 15) {
        state = 2;
      } else if (distance > 30) {
        state = 0;
      }

      break;

    case 2: //move backward
      moveBackward();

      if (distance > 15 && distance < 30) {
        state = 1;
      } else if (distance > 30) {
        state = 0;
      }

      break;
  }
}

boolean handFound() {
  int distance = sonar.ping_cm();
  if (distance < 10) {
    return true;
  } else {
    return false;
  }
}

void setRobotSpeed(int speed) {
  analogWrite(motorASpeed, speed);
  analogWrite(motorBSpeed, speed);
}

void moveForward() {
  digitalWrite(standBy, HIGH);
  digitalWrite(motorAdir1, LOW);
  digitalWrite(motorAdir2, HIGH);
  digitalWrite(motorBdir1, HIGH);
  digitalWrite(motorBdir2, LOW);
}

void moveBackward() {
  digitalWrite(standBy, HIGH);
  digitalWrite(motorAdir1, HIGH);
  digitalWrite(motorAdir2, LOW);
  digitalWrite(motorBdir1, LOW);
  digitalWrite(motorBdir2, HIGH);
}

void turnRight() {
  digitalWrite(standBy, HIGH);
  digitalWrite(motorAdir1, LOW);
  digitalWrite(motorAdir2, HIGH);
  digitalWrite(motorBdir1, LOW);
  digitalWrite(motorBdir2, HIGH);
}

void turnLeft() {
  digitalWrite(standBy, HIGH);
  digitalWrite(motorAdir1, HIGH);
  digitalWrite(motorAdir2, LOW);
  digitalWrite(motorBdir1, HIGH);
  digitalWrite(motorBdir2, LOW);
}

void stopRobot() {
  digitalWrite(standBy, LOW);
  digitalWrite(motorAdir1, HIGH);
  digitalWrite(motorAdir2, HIGH);
  digitalWrite(motorBdir1, HIGH);
  digitalWrite(motorBdir2, HIGH);

}

