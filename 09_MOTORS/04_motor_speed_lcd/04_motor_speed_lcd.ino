int motorPin = 3;
int potPin = A0;

#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

LiquidCrystal_PCF8574 lcd(0x27);

void setup() {
  // put your setup code here, to run once:
  pinMode(motorPin, OUTPUT);

  lcd.begin(16, 2);
  lcd.setBacklight(255);

}

void loop() {
  // put your main code here, to run repeatedly:
  int potValue = analogRead(potPin);

  int motorSpeed = map(potValue, 0, 1024, 0, 255);

  lcd.home();
  lcd.clear();
  lcd.print("motor speed: ");
  lcd.print(motorSpeed);

  analogWrite(motorPin, motorSpeed );

  delay(10);
}
