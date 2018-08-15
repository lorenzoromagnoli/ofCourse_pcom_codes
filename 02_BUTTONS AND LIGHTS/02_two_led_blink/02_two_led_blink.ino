int led1_pin=9; 
int led2_pin=10;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 9 as an output.
  pinMode(led1_pin, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(led1_pin, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(led2_pin, LOW);   // turn the LED off by making the voltage LOW

  delay(500);                       // wait for half a second
  
  digitalWrite(led1_pin, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(led2_pin, HIGH);   // turn the LED on (HIGH is the voltage level)

  delay(1000);                       // wait for half a second
}
