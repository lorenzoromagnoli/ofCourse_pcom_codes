 /*
this code demonstrate how to interpret incoming characters 
received via the serial port and control the robot car.
*/

#include <Servo.h>

int leftEncoderPin = 2;
int rightEncoderPin = 3;

int leftTickCount = 0;
int rightTickCount = 0;

int lastLeftEncoderState;
int leftEncoderState;
int lastRightEncoderState;
int rightEncoderState;

const int servoPin = 12;
int servoUp = 90;
int servoDown = 0;
Servo myServo;

const boolean forward = true;
const boolean backward = false;
const boolean right = true;
const boolean left = false;

const int wheelDiameter = 67;
int wheelCircumference = wheelDiameter * 3.14;
int ticksXRevolution = 20;
int tickMovement = wheelCircumference / ticksXRevolution;

const int distanceBetweenWheels = 129;
int fullRobotCircumference = distanceBetweenWheels * 3.14;
int nTicksForFullRevolution = fullRobotCircumference / tickMovement;
int angularTickRotation = 360 / nTicksForFullRevolution;

//distance between the tip of the pen and the wheel axis
int penOffset = 80;


void setup() {
  pinMode(leftEncoderPin, INPUT);
  pinMode(rightEncoderPin, INPUT);

  Serial.begin(9600);
  setRobotSpeed(100, 90);
  myServo.attach(servoPin);
}


void loop() {
  if (Serial.available() > 0) {
    char c = (char)Serial.read();
    Serial.println(c);

    switch (c) {
      case 'f':
        moveForward();
        break;
      case 'b':
        moveBackward();
        break;
      case 'r':
        turnRight();
        break;
      case 'l':
        turnLeft();
        break;
      case 'p':
        stopRobot();
    }
  }
}


void moveServoUp() {
  myServo.write(servoUp);
}
void moveServoDown() {
  myServo.write(servoDown);
}

void moveBymm(int mm, boolean direction) {
  int ticks = mm / tickMovement;
  moveXTicks(ticks, direction);
}

void rotateByAngle(int angle, boolean direction) {
  int ticks = angle / angularTickRotation;
  Serial.println(ticks);
  rotateXTicks(ticks, direction);
}

void rotateXTicks(int ticks, boolean direction) {
  leftTickCount = 0;
  rightTickCount = 0;

  if (direction == right) {
    turnRight();
  } else {
    turnLeft();
  }

  while (leftTickCount < ticks && rightTickCount < ticks) {
    tickCount();
  }
  stopRobot();
}

void moveXTicks(int ticks, boolean direction) {
  leftTickCount = 0;
  rightTickCount = 0;

  if (direction == forward) {
    moveForward();
  } else {
    moveBackward();
  }

  while (leftTickCount < ticks && rightTickCount < ticks) {
    tickCount();
  }

  stopRobot();
}


void tickCount() {
  leftEncoderState = digitalRead(leftEncoderPin);
  rightEncoderState = digitalRead(rightEncoderPin);

  if (leftEncoderState && !lastLeftEncoderState ) {
    leftTickCount++;
  }

  if (rightEncoderState && !lastRightEncoderState ) {
    rightTickCount++;
  }

  lastLeftEncoderState = leftEncoderState;
  lastRightEncoderState = rightEncoderState;

  Serial.print(leftTickCount);
  Serial.print('\t');
  Serial.println(rightTickCount);

}

