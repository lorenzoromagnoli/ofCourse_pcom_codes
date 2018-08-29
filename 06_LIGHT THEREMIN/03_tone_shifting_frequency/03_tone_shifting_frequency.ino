/*
 * connect a potentiometer to pin A0 
 * to control the frequency of the sound produced 
 * using the tone function
 */

int buzzerPin=8; 
int potPin=A0;

void setup() {
  // put your setup code here, to run once:
  
  pinMode(buzzerPin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  int freq=analogread(A0);
  freq =map (freq,0,1024,20,20000); //map the value read from the potentiometer into the audible range
  
  tone (buzzerPin,freq); 
}
