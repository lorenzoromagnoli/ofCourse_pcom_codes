/*
 * Example code to adjust the speed of each wheel so that 
 * they speed at a similar rate. 
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

  /*
   * this function allows you to set the speed of the motor
   * for each wheel. I've tried several values until I found
   * a couple that seems to let the two wheel spin at the same 
   * speed. 
   * 
   * Just open the serial port and check that the tick count values
   * are growing at the same rate. If not adjust the two values. 
   * 
   * TODO: It's probably easier if you calculate the rpm (revolution per seconds) 
   * at which each wheel is turning.
   */
  setRobotSpeed(100,90);
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
