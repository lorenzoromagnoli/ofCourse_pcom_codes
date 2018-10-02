/*
 * example code to control the all the possible robot movements 
 * forward/backward turn left/right
 */

const int motorASpeed = 11; //pwmA
const int motorBSpeed = 5;  //pwmB

const int motorAdir1 = 10;  //Ain1
const int motorAdir2 = 9;   //Ain2

const int motorBdir1 = 7;   //Bin1
const int motorBdir2 = 6;   //Bin2

const int standBy = 8;      //stby


void setup() {
  // put your setup code here, to run once:
  pinMode(motorASpeed, OUTPUT);
  pinMode(motorBSpeed, OUTPUT);
  pinMode(motorAdir1, OUTPUT);
  pinMode(motorAdir2, OUTPUT);
  pinMode(motorBdir1, OUTPUT);
  pinMode(motorBdir2, OUTPUT);
  pinMode(standBy, OUTPUT);
}

void loop() {
  setRobotSpeed(100);
  moveForward();
  delay(1000);
  stopRobot();
  delay(1000);
  moveBackward();
  delay(2000);
  turnRight();
  delay(2000);
  turnLeft();
  delay(2000);
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

