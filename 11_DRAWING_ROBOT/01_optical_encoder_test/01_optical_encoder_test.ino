/*
 * Example code to test the optical encoder installed 
 * on the robot wheel
 */

// encoder connections
int leftEncoderPin = 2;
int rightEncoderPin = 3;

// variables to store the encoders count
int leftTickCount = 0;
int rightTickCount = 0;

//variables used to detect only the encoder transition moment from 0 to 1
int lastLeftEncoderState;
int leftEncoderState;
int lastRightEncoderState;
int rightEncoderState;

void setup() {
  pinMode(leftEncoderPin, INPUT);
  pinMode(rightEncoderPin, INPUT);

  Serial.begin(9600);
  setRobotSpeed(100);
  moveForward();
}

void loop() {

  // digital read the value from the encoder
  leftEncoderState = digitalRead(leftEncoderPin);
  rightEncoderState = digitalRead(rightEncoderPin);

  // if I detect a change in state update the tick counts
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
