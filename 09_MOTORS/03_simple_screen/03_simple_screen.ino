#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

LiquidCrystal_PCF8574 lcd(0x27);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup(){
  lcd.begin(16, 2); // initialize the lcd
} 

void loop(){
    lcd.setBacklight(255);
    lcd.home(); 
    lcd.print("Hello LCD");
} 
