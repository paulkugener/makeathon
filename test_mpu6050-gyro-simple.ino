// Test code for roll and pitch with MPU6050
// source: http://www.giuseppecaccavale.it/arduino/roll-pitch-e-yaw-con-mpu6050-arduino/


#include <SPI.h>
#include <Wire.h>

#define MPU 0x68  // I2C address of the MPU-6050

double AcX,AcY,AcZ;
int pitch, roll;


void setup(){
  Serial.begin(9600);
  init_MPU(); // Init MPU6050
}


void loop()
{
  FunctionsMPU(); // get the values for the axis AcX, AcY, AcZ
    
  roll = FunctionsPitchRoll(AcX, AcY, AcZ);   // calculate the roll-value
  pitch = FunctionsPitchRoll(AcY, AcX, AcZ);  // calculate the pitch-value

  writeOutput(roll, pitch);

  delay(500);
}


// Init MPU6050
void init_MPU(){
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  delay(1000);
}


// function to calculate the angles for pitch and roll
double FunctionsPitchRoll(double A, double B, double C){
  double dataA, dataB, value;
  dataA = A;
  dataB = (B*B) + (C*C);
  dataB = sqrt(dataB);
  
  value = atan2(dataA, dataB);
  value = value * 180 / PI;
  
  return (int)value;
}


// function to get the values for the axis X, Y, Z from MPU6050
void FunctionsMPU(){
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,6,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
}


// function to organize the output to the 'serial monitor'
void writeOutput(int xAng, int yAng) {
  String xString = String(xAng);
  String yString = String(yAng);
  
  Serial.print("x = " + xString + ", y = " + yString);
  Serial.println();
  
  // we could add more stuff here
}
