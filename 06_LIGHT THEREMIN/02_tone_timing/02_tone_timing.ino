int buzzerPin=8; 

void setup() {
  // put your setup code here, to run once:
  
  pinMode(buzzerPin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  tone (buzzerPin,420,500); //start producing a sound at 420HZ
  delay(1000);
}
