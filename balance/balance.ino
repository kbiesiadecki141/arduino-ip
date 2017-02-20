/* fill me in later but 2/20/17 */

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
  Serial.println("Orientation Sensor Raw Data Test"); Serial.println("");

  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  servo.attach(9);
  delay(1000);
  
  bno.setExtCrystalUse(true);

  Serial.println("Calibration status values: 0=uncalibrated, 3=fully calibrated");
}

void loop(void)
{
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);

  potVal = analogRead(PIN_POT);
  potVal = map(potVal, 0, 1023, 0, 180);
  
  // Maps yaw to servo position.
  yaw = euler.z();
  pos = map(yaw, 90, -90, potVal, 180);
  servo.write(pos);

  // Display yaw.
  Serial.print(" Z: ");
  Serial.print(yaw);
  Serial.print("\t\t");
  Serial.print(" Pos: ");
  Serial.print(pos);
  Serial.print("\n");


  delay(BNO055_SAMPLERATE_DELAY_MS);
}
