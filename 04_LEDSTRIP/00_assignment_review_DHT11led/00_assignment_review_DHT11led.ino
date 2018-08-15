#include <SimpleDHT.h>

int redLedPin = 6;
int blueLedPin = 5;

int pinDHT11 = 3;
SimpleDHT11 dht11;

void setup() {
  Serial.begin(115200);

  pinMode(redLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);

}

void loop() {
  // start working...
  Serial.println("=================================");
  Serial.println("Sample DHT11...");

  // read without samples.
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(pinDHT11, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.println(err); delay(1000);
    return;
  }

  Serial.print("Sample OK: ");
  Serial.print((int)temperature); Serial.print(" *C, ");
  Serial.print((int)humidity); Serial.println(" H");


  if ((int)temperature > 29) {
    digitalWrite(redLedPin, HIGH);
    digitalWrite(blueLedPin, LOW);

  } else {
    digitalWrite(redLedPin, LOW);
    digitalWrite(blueLedPin, HIGH);
  }

  // DHT11 sampling rate is 1HZ.
  delay(1500);
}
