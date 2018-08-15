int redPin = 6;
int greenPin = 5;
int bluePin = 3;

int redPod = A0;
int greenPot = A1;
int bluePot = A2;


void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  int redColor = analogRead(A0);
  int greenColor = analogRead(A1);
  int blueColor = analogRead(A2);

  redColor = redColor / 4;
  greenColor = greenColor / 4;
  blueColor = blueColor / 4;

  analogWrite(redPin, redColor);
  analogWrite(greenPin, greenColor);
  analogWrite(bluePin, blueColor);


}
