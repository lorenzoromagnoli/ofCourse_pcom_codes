/*
 * Code to precisely control the robot movement.
 * The robot can move back/forward by a specified distance
 * But also you can specify a rotation angle in degree.
 */
 
int leftEncoderPin = 2;
int rightEncoderPin = 3;

int leftTickCount = 0;
int rightTickCount = 0;

int lastLeftEncoderState;
int leftEncoderState;
int lastRightEncoderState;
int rightEncoderState;


const boolean forward = true;
const boolean backward = false;
const boolean right = true;
const boolean left = false;

//some math to calculate by how much the robot moves for 
//each tick counted by the encoder.

const int wheelDiameter = 67;
int wheelCircumference = wheelDiameter * 3.14;
int ticksXRevolution = 20;
int tickMovement = wheelCircumference / ticksXRevolution;

//some math to calculate by how much the robot rotates 
//for each tick counted by the encoders

const int distanceBetweenWheels = 129;
int fullRobotCircumference = distanceBetweenWheels * 3.14;
int nTicksForFullRevolution = fullRobotCircumference / tickMovement;
int angularTickRotation = 360 / nTicksForFullRevolution;


void setup() {
  pinMode(leftEncoderPin, INPUT);
  pinMode(rightEncoderPin, INPUT);

  Serial.begin(9600);
  setRobotSpeed(100, 90);
  moveForward();
}



void loop() {
  moveBymm (100, forward);
  delay(2000);
  rotateByAngle(90, left);
  delay(2000);
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

