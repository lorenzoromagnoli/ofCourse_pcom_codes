const int motorASpeed = 11; //pwmA
const int motorBSpeed = 5;  //pwmB

const int motorAdir1 = 10;  //Ain1
const int motorAdir2 = 9;   //Ain2

const int motorBdir1 = 7;   //Bin1
const int motorBdir2 = 6;   //Bin2

const int standBy = 8;      //stby


void setRobotSpeed(int speedA, int speedB) {
  analogWrite(motorASpeed, speedA);
  analogWrite(motorBSpeed, speedB);
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
