int led_pin = 8;    //led is attached to pin 8
int button_pin = 5; //button is attached to pin 5


// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(led_pin, OUTPUT); //set the pin that controls the led as Output
  pinMode(button_pin, INPUT); //set the pin that read the status of the button  as Input
}


// the loop function runs over and over again forever
void loop() {
  //read the status of the button and save it into a variable called buttonState
  int buttonState = digitalRead(button_pin);
  digitalWrite (led_pin, buttonState); //turn on or off the led_pin depending on the value of buttonState
}
