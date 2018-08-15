// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

#include "DHT.h"

#define DHTPIN 2     // what digital pin we're connected to

#define DHTTYPE DHT11   // DHT 11

int redLedPin = 8;
int blueLedPin = 9;

// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(redLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);

  Serial.begin(9600);
  Serial.println("DHTxx test!");
  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float t = dht.readTemperature();
  // Read temperature as Celsius (the default)

  // Check if any reads failed and exit early (to try again).
  if ( isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println("°C ");

  if (t > 25) { // if the temperature is higher than 25 degrees turn on the led red
    digitalWrite(redLedPin, HIGH);
    digitalWrite(blueLedPin, LOW);

  } else { //else turn on the blue led
    digitalWrite(blueLedPin, HIGH);
    digitalWrite(redLedPin, LOW);
  }
}
