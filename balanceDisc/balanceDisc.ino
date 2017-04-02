// libaries
#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define MPU 0x68  // I2C address of the MPU-6050
#define LCDADD 0x3f // I2C address of the lcd-display

LiquidCrystal_I2C lcd(LCDADD, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

// variables
double AcX,AcY,AcZ;
int pitch, roll;

// SETUP
void setup() {
  init_MPU(); // Init MPU6050
  init_LCD(); // Init display
  delay(5000);
}


// LOOP
void loop() {
  FunctionsMPU(); // get the values for the axis AcX, AcY, AcZ

  roll = FunctionsPitchRoll(AcX, AcY, AcZ);   // calculate the roll-value
  pitch = FunctionsPitchRoll(AcY, AcX, AcZ);  // calculate the pitch-value

  writeOutput(roll, pitch);

  delay(500);
}


// Init MPU6050
void init_MPU() {
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  delay(1000);
}

void init_LCD() {
  lcd.begin(16,2); // Init 16x2 LCD-Display
  lcd.backlight(); // backlight on

//-------- Write characters on the display ------------------
// NOTE: Cursor Position: (CHAR, LINE) start at 0
  lcd.setCursor(0,0); //Start at character 0 on line 0
  lcd.print("  Balance-Disc");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("   Have fun :)");
}

// function to calculate the angles for pitch and roll
double FunctionsPitchRoll(double A, double B, double C) {
  double dataA, dataB, value;
  dataA = A;
  dataB = (B*B) + (C*C);
  dataB = sqrt(dataB);

  value = atan2(dataA, dataB);
  value = value * 180 / PI;

  return (int)value;
}

// function to get the values for the axis X, Y, Z from MPU6050
void FunctionsMPU() {
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,6,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
}


// function to organize the output to the LCD-Display
void writeOutput(int xAng, int yAng) {
  String line1 = "x = " + String(xAng) + ", y = " + String(yAng);

  lcd.clear();
  lcd.setCursor(0,0); //Start at character 0 on line 0
  lcd.print(line1);
  lcd.setCursor(0,1);
  if (xAng > 20 || yAng > 20 || xAng < -20 || yAng < -20) {
    lcd.print(" X X DANGER X X");
  }
  else if (xAng > 10 || yAng > 10 || xAng < -10 || yAng < -10) {
    lcd.print("   Take care!");
  }
  else {
    lcd.print("   Keep going");
  }

}
