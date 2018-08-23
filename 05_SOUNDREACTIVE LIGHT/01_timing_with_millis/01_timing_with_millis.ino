/*
 In this sketch we use a potentiometer to change 
 the blinking speed of a led.

 The blink is done without using any delay() 
 which would have block the continuos execution of the program
*/

int potPin=A0; //the potentiometer pin
int ledPin=13; //the led pin

int delayTime= 1000; //initial delay time for the blinking speed

long lastBlinkTime=0; //when did I iverted the state of the led last time
bool ledState=false; // a variable to store the status of the led

void setup() {
  
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  
  delayTime= analogRead(potPin); //read the value from the potentiometer and update the delayTime variable 
  delayTime= map(delayTime, 0, 1024, 0, 2000); //map the delay between 0s and 2s
  
  long timePassed=millis(); //get how much time has passed from the beginning of the program

  Serial.println(timePassed-lastBlinkTime); //print how much time has passed from the last time I changed the status of the led
  
  if(timePassed-lastBlinkTime>delayTime){ //if the interval is bigger that the delaytime value...
    ledState=!ledState; //invert the status of ledstate
    lastBlinkTime=timePassed; //update the lastBlinkTime value
    Serial.println("blink");
  }

  digitalWrite(ledPin, ledState); //set the led to ON or OFF depending on the value of ledstate variable


}
