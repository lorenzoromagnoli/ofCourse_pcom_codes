/*
   with this sketch we will see how to recognise a loud sound
   like a clap or a knock on a table.
*/

int sensorPin = A0;

//connect 3 leds to pins 11,12,13
int led1Pin = 13;
int led2Pin = 12;
int led3Pin = 11;

//maximum and minimum peaks detected in the timewindow
int maxPeak = 0;
int minPeak = 0;

int readingWindow = 20;
long lastOpenWindowTime = 0;
int loudness = 0;

// how many claps have I detected since the start of the program
int clapCount=0; 

bool soundHIGH; //is the current sound above a specific range?
bool lastSoundHIGH; //was it above the range the last time I measured?

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);

}

void loop() {

  long currentTime = millis();

  int soundValue = analogRead(sensorPin);

  if (soundValue > maxPeak) {
    maxPeak = soundValue;
  }
  if (soundValue < minPeak) {
    minPeak = soundValue;
  }

  if (currentTime - lastOpenWindowTime > readingWindow) {
    //here I reset my window and to the other calculations;

    loudness = maxPeak + minPeak;

    maxPeak = soundValue;
    minPeak = soundValue;
    lastOpenWindowTime = currentTime;
  }

  if (loudness > 200) { //determin if the sound is lower a certain range
    soundHIGH = true;
  } else {
    soundHIGH = false;
  }

  if (soundHIGH && !lastSoundHIGH) { //if now the sound is high and before it was not, that means we measured a clap
    clapCount++; // increment the counter
    Serial.println(clapCount);
  }

  lastSoundHIGH = soundHIGH;


}
