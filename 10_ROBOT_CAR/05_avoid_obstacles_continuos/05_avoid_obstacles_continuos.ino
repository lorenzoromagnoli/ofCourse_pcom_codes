/*
 * example code of a robot capable of avoiding obstacles. 
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
    int distanceFromObstacles = sonar.ping_cm();
    
    Serial.println(distanceFromObstacles);
    
    if (foundObstacles) {
      if (distanceFromObstacles > 10) {
        foundObstacles = false;
      }
      if (turnDirection == 1) {
        turnRight();
      } else if (turnDirection == 0) {
        turnLeft();
      }

    } else {
      moveForward();
      if (distanceFromObstacles < 10) {
        foundObstacles = true;
        if (random(10) > 5) {
          turnDirection = 1;
        } else {
          turnDirection = 0;
        }
      }
    }

    lastUpdate = millis();
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
  digitalWrite(motorAdir1, LOW);
  digitalWrite(motorAdir2, HIGH);
  digitalWrite(motorBdir1, LOW);
  digitalWrite(motorBdir2, HIGH);
}

void turnLeft() {
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

