int led_pin = 8;    //led is attached to pin 8
int button_pin = 5; //button is attached to pin 5

int buttonState = 0;
int oldButtonState = 0;

boolean ledState = false;

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(led_pin, OUTPUT); //set the pin that controls the led as Output
  pinMode(button_pin, INPUT); //set the pin that read the status of the button  as Input
}

// the loop function runs over and over again forever
void loop() {

  //read the status of the button and save it into a variable
  buttonState = digitalRead(button_pin);

 
  if (oldButtonState == LOW && buttonState == HIGH) {   //if the value I read is High, but in the previous loop was low it means the button was pushed.
    ledState = !ledState; //invert the value of the ledstate variable: if it was true, make it false and vice versa
  }
  
  digitalWrite (led_pin, ledState); //turn on or off the ledpin depending on the value of ledState

  oldButtonState = buttonState; // update the value of oldButtonState for the next loop cycle. 
  delay(100);
}
