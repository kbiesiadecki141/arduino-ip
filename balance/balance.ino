//*********************************************************************************
//*                                                                               *
//*  Katelyn Biesiadecki                                                          *
//*  February 20th, 2017                                                          *
//*                                                                               *
//*  Balance                                                                      *
//*                                                                               *
//*  This sketch uses an IMU to determine the current yaw of the sensor and set   *
//*  a servo to a position so that it always points straight up.                  *
//*                                                                               *
//*  Inspiration for this project from the following videos...                    *
//*  Bender is gyroscopically stable: https://www.youtube.com/watch?v=xl-0AePt0e0 *
//*  Star Trek: https://www.youtube.com/watch?v=-t7oF6tNAJI                       *
//*                                                                               *
//*********************************************************************************

#include <Wire.h>
#include <Servo.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

#define BNO055_SAMPLERATE_DELAY_MS (15)

Adafruit_BNO055 bno = Adafruit_BNO055();
Servo servo;
int yaw = 0;
int potVal = 0;
int pos = 0;
int PIN_POT = 0;

void setup(void)
{
  Serial.begin(9600);
  Serial.println("Orientation Sensor Raw Data"); 
  Serial.println("");

  // Initialize the sensor.
  if(!bno.begin())
  {
    // There was a problem detecting the BNO055.
    Serial.print("Ooops, no BNO055 detected... Check your wiring or I2C ADDR!");
    while(1);
  }

  servo.attach(9);
  delay(1000);
  
  bno.setExtCrystalUse(true);
}

void loop(void)
{
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);

  // Reads potentiometer to determine offset for servo.
  potVal = analogRead(PIN_POT);
  potVal = map(potVal, 0, 1023, 0, 180);
  
  // Maps yaw to servo position inversely.
  yaw = euler.z();
  pos = map(yaw, 90, -90, potVal, 180);
  servo.write(pos);

  // Display yaw.
  Serial.print(" Z: ");
  Serial.print(yaw);
  Serial.print("\t\t");

  // Display pos.
  Serial.print(" Pos: ");
  Serial.print(pos);
  Serial.print("\n");

  // Delay 15 ms.
  delay(BNO055_SAMPLERATE_DELAY_MS);
}
