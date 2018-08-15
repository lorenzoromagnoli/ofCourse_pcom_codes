int ledPin=11;
int potPin=A0;

void setup(){
  // put your setup here, to run once:
  pinMode(potPin, INPUT);
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);
}

void loop(){
  //put your main code here, to run repeatedly;

  int sensorValue=analogRead(potPin);

  int mappedSensorValue=map(sensorValue,160, 520, 0,255);

  mappedSensorValue=constrain(mappedSensorValue,0,255);

  Serial.print("sensor: ");
  Serial.print(sensorValue);
  Serial.print("mapped value "); 
  Serial.println(mappedSensorValue);

  analogWrite(ledPin, mappedSensorValue);
  
}

