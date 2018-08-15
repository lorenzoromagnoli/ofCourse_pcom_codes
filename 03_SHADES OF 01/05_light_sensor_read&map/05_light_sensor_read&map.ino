int ledPin=11;
int potPin=A0;

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  pinMode(11, OUTPUT);

  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  int sensorValue=analogRead(potPin);

  int mappedSensorValue=map(sensorValue, 150, 600, 0, 255);

  if (mappedSensorValue<0){
    mappedSensorValue=0;
  }
  
  if (mappedSensorValue>255){
    mappedSensorValue=255;
  }

  Serial.print( "sensorValue: ");
  Serial.print(sensorValue);
  Serial.print( " mappedValue: ");
  Serial.println(mappedSensorValue);

  analogWrite(ledPin, mappedSensorValue);
  
}
