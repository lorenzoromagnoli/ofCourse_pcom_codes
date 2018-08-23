/*
 Calculate and visualize the loudness of a sound.
 Connect your sound sensor to pin A0 and open the serial plotter. 
 
 In code below we are going to analyze the sound recorded in a interval of 20ms.
 We are going to find the highest and lowest peaks and sum the two values
 to find a instant measure of the loudness of the sound we are listening to.

 a led connected to pin 13 will show loud sounds
 */

int sensorPin=A0;

int readingWindow=20; // the duration of the interval we will analyze

int maxPeak=0; // the minimum value found in the interval
int minPeak=0; // the maximum peak found in the interval

long lastOpenWindowTime=0; //last time in which we opened the reading window

int loudness=0; //the calculated loudness

int ledPin=13;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  long currentTime=millis(); 

  int soundValue=analogRead(sensorPin);
  
  /*I can plot mutiple values to the serial plotter by printing 
  multiple values in the same line separated by comma. */
  
  Serial.print(soundValue);
  Serial.print(",");
  Serial.println(loudness);

  //every time I get a new value from the sensor I check if I find a new max or min peak
  if(soundValue>maxPeak){
    maxPeak=soundValue;
  }
  if (soundValue<minPeak){
    minPeak=soundValue;
  }

  if (currentTime-lastOpenWindowTime>readingWindow){ //here I reset my window and to the other calculations;
   
    loudness=maxPeak+minPeak; //calculate the new level of loudness

    //reset the max and min peak values
    maxPeak=soundValue; 
    minPeak=soundValue;
    lastOpenWindowTime=currentTime;
  }

  //if the loudness is bigger that 200 then turn on the led. 
  if (loudness>200){
   digitalWrite(ledPin, HIGH); 
  }else{
    digitalWrite(ledPin, LOW);
  }

}
