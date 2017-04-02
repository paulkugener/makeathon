#include "Arduino.h"
#include <SoftwareSerial.h>

SoftwareSerial lcd = SoftwareSerial(0,2);

// Take a look at the different commands!
// If we send commands to the display we use .write()
// If we send a String to display we use .print() and/or .println()
// More information on commands:
// https://learn.adafruit.com/usb-plus-serial-backpack/command-reference

void setup() {
  lcd.begin(9600);  
  
  // set the size of the display if it isn't 16x2 (you only have to do this once)
  lcd.write(0xFE);
  lcd.write(0xD1);
  lcd.write(16);  // 16 columns
  lcd.write(2);   // 2 rows
  delay(10);       
  // we suggest putting delays after each command to make sure the data 
  // is sent and the LCD is updated.

  // set the contrast, 200 is a good place to start, adjust as desired
  lcd.write(0xFE);
  lcd.write(0x50);
  lcd.write(200);
  delay(10);       
  
  // set the brightness - we'll max it (255 is max brightness)
  lcd.write(0xFE);
  lcd.write(0x99);
  lcd.write(255);
  delay(10);       
  
  // turn off cursors
  lcd.write(0xFE);
  lcd.write(0x4B);
  lcd.write(0xFE);
  lcd.write(0x54);
  
  // clear screen
  clearScreen();
  
  // go 'home'
  goHome();

  lcd.print("Hello ");
  lcd.println("World!");
  lcd.print("2nd-line");
  
  delay(5000);
}

void loop() {
  int numberArray[] = {1, 10, 25, 44};
  int x = numberArray[(int)random(0,4)];

  updateDisplay(x);
  delay(5000);
}

void updateDisplay(int x){
  if (x < 5){
    setBackgroundWhite();
    clearScreen();
    goHome();
    lcd.println("x value is");
    lcd.print(String(x));
  } 
  else if (x < 15) {
    setBackgroundGreen();
    clearScreen();
    goHome();
    lcd.println("x value is");
    lcd.print(String(x));
  }
  else if (x < 30) {
    setBackgroundBlue();
    clearScreen();
    goHome();
    lcd.println("x value is");
    lcd.print(String(x));
  }
  else if (x < 50) {
    setBackgroundRed();
    clearScreen();
    goHome();
    lcd.println("x value is");
    lcd.print(String(x));
  }

  delay(50);
}

void clearScreen(){
  // clear screen
  lcd.write(0xFE);
  lcd.write(0x58);
  delay(10);   // we suggest putting delays after each command
}

void goHome(){
  // go 'home' ~> first char in first line
  lcd.write(0xFE);
  lcd.write(0x48);
  delay(10);   // we suggest putting delays after each command
}

void setBackgroundRed() {
  //0xFE 0xD0 0xFF 0x0 0x0
  lcd.write(0xFE);
  lcd.write(0xD0);
  lcd.write(0xFF);
  lcd.write((uint8_t)0);
  lcd.write((uint8_t)0);
  delay(10);
}

void setBackgroundGreen() {
  //0xFE 0xD0 0x0 0xFF 0x0
  lcd.write(0xFE);
  lcd.write(0xD0);
  lcd.write((uint8_t)0);
  lcd.write(0xFF);
  lcd.write((uint8_t)0);
  delay(10);
}

void setBackgroundBlue() {
  //0xFE 0xD0 0x0 0x0 0xFF
  lcd.write(0xFE);
  lcd.write(0xD0);
  lcd.write((uint8_t)0);
  lcd.write((uint8_t)0);
  lcd.write(0xFF);
  delay(10);
}

void setBackgroundWhite() {
  //0xFE 0xD0 0xFF 0xFF 0xFF
  lcd.write(0xFE);
  lcd.write(0xD0);
  lcd.write(0xFF);
  lcd.write(0xFF);
  lcd.write(0xFF);
  delay(10);
}

