/*
 * code to precisely control the robot movement, 
 * back and forward so that it advances by a specified 
 * amount of "ticks" counted using the wheel encoders.
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


void setup() {
  pinMode(leftEncoderPin, INPUT);
  pinMode(rightEncoderPin, INPUT);

  Serial.begin(9600);
  setRobotSpeed(100, 90);
  moveForward();
}

void loop() {
  moveXTicks (20, forward);
  delay(2000);
  moveXTicks (20, backward );
  delay(2000);
}

void moveXTicks(int ticks, boolean direction) {
  //reset the tick count
  leftTickCount = 0;
  rightTickCount = 0;

  //select the movement direction
  if (direction == forward) {
    moveForward();
  } else {
    moveBackward();
  }

  //until the tick count reaches the desired values keep on counting
  while (leftTickCount < ticks && rightTickCount < ticks) {
    tickCount();
  }
  //then stop the robot
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

