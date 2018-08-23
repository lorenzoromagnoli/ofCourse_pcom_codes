/*
 * In this Sketch we will count how many claps we detect in a specific interval of time.  
 * depending on how many claps are detected we will turn on one, two or three leds.
 */

int sensorPin = A0;

//connect 3 leds to pins 11,12,13
int led1Pin = 13; 
int led2Pin = 12;
int led3Pin = 11;

int maxPeak = 0;
int minPeak = 0;

int readingWindow = 20;
long lastOpenWindowTime = 0;
int loudness = 0;

bool soundHIGH;
bool lastSoundHIGH;

int clapCount = 0;

int clapCountInterval = 2000; //for how long I'll keep on listening for claps?
long lastClapIntervalStarted = 0; //when did I hear the first clap of the sequence?

boolean recording; //am I listening for detecting new claps?

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  long currentTime = millis();

  int soundValue = analogRead(sensorPin);
  //  Serial.print(soundValue);
  //  Serial.print(",");
  //  Serial.println(loudness);

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

  if (loudness > 200) {
    soundHIGH = true;
  } else {
    soundHIGH = false;
  }

  if (currentTime - lastClapIntervalStarted < clapCountInterval) { //I'm inside the interval counting for the claps
    if (soundHIGH && !lastSoundHIGH) { //if now the sound is high and before it was not
      clapCount++;
      Serial.println("clap");
    }
  } else { //if the time has expired and I'm not waiting to count new claps
    if (recording) {  //if I was recording... it means that the window just closed.
      Serial.println("time over");
      Serial.print("clap Count=");
      Serial.print (clapCount);

      switch (clapCount) { //depending on how many claps are detected turn on the appropriate amount of led
        case (1):
          digitalWrite(led1Pin, HIGH);
          digitalWrite(led2Pin, LOW);
          digitalWrite(led3Pin, LOW);
          break;
        case (2):
          digitalWrite(led1Pin, HIGH);
          digitalWrite(led2Pin, HIGH);
          digitalWrite(led3Pin, LOW);
          break;
        case (3):
          digitalWrite(led1Pin, HIGH);
          digitalWrite(led2Pin, HIGH);
          digitalWrite(led3Pin, HIGH);
          break;
        case (4):
          digitalWrite(led1Pin, LOW);
          digitalWrite(led2Pin, LOW);
          digitalWrite(led3Pin, LOW);
          break;
      }

    }
    recording = false; //reset the recording variable to false and wait for a new clap.

    if (soundHIGH && !lastSoundHIGH) { //if I'm not recording but I detect a clap
      clapCount = 1; 
      recording = true; 
      lastClapIntervalStarted = currentTime; //reset the timer and restart waiting for new claps in the next 2seconds. 
      Serial.println("here I start coundting for claps");
    }
  }

  lastSoundHIGH = soundHIGH;



}
