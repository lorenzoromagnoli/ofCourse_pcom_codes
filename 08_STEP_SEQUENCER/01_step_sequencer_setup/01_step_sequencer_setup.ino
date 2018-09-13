int buttonPins[] = {13, 12, 11, 10};
int potPins[] = {A0, A1, A2, A3};
int ledPins[] = {7, 6, 5, 4};
int tempoPin = A4;

int buttonsState[] = {0, 0, 0, 0};
int oldButtonState[] = {0, 0, 0, 0};
boolean notesToPlay[] = {0, 0, 0, 0};

int frequencies[] = {0, 0, 0, 0};
int minFrequency = 33;
int maxFrequncy = 300;

int stepDuration = 500;
int minStepDuration = 20;
int maxStepDuration = 1000;

int nSteps = 4;

void setup() {
  // put your setup code here, to run once:

  for (int i = 0; i < nSteps; i++) {
    pinMode(buttonPins[i], INPUT);
    pinMode(ledPins[i], OUTPUT);
  }

  Serial.begin(9600);

}

void loop() {
  readButtons();
  readPotentimeters();

  printSequencerValues();
}

void readPotentimeters() {
  for (int i = 0; i < nSteps; i++) {
    int potValue = analogRead(potPins[i]);
    frequencies[i] = map (potValue, 0, 1024, minFrequency, maxFrequncy);
  }

  stepDuration = analogRead(tempoPin);
  stepDuration = map(stepDuration, 0, 1024, minStepDuration, maxStepDuration);
}

void readButtons() {
  for (int i = 0; i < nSteps; i++) {
    buttonsState[i] = digitalRead(buttonPins[i]);
    if (buttonsState[i] && !oldButtonState[i]) {
      notesToPlay[i] = !notesToPlay[i];
    }
    oldButtonState[i] = buttonsState[i];
  }
}

void printSequencerValues() {
  for (int i = 0; i < nSteps; i++) {
    Serial.print (notesToPlay[i]);
    Serial.print('\t');
  }
  for (int i = 0; i < nSteps; i++) {
    Serial.print (frequencies[i]);
    Serial.print('\t');
  }
  Serial.print(stepDuration);
  Serial.println();
}

