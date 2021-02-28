//
//    FILE: GY521_pitch_roll_yaw.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo PRY
//    DATE: 2020-08-06
#include <M5Stack.h>
#include "SD.h"

#include "GY521.h"

GY521 sensor(0x68);

uint32_t counter = 0;

void setup()
{
  M5.begin();
  dacWrite(25, 0);
  
  Serial.begin(115200);
  Serial.println(__FILE__);

  Wire.begin();

  delay(100);
  while (sensor.wakeup() == false)
  {
    Serial.print(millis());
    Serial.println("\tCould not connect to GY521");
    delay(1000);
  }
  sensor.setAccelSensitivity(2);  // 8g
  sensor.setGyroSensitivity(1);   // 500 degrees/s

  sensor.setThrottle();
  Serial.println("start...");
  
  // set callibration values from calibration sketch.
  sensor.axe = 0;
  sensor.aye = 0;
  sensor.aze = 0;
  sensor.gxe = 0;
  sensor.gye = 0;
  sensor.gze = 0;
}

void loop()
{
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.setTextColor(BLACK, WHITE);
  M5.Lcd.setTextSize(3);
  sensor.read();
  float pitch = sensor.getPitch();
  float roll  = sensor.getRoll();
  float yaw   = sensor.getYaw();

  if (counter % 10 == 0)
  {
    Serial.println("\nCNT\tPITCH\tROLL\tYAW");
  }

//  M5.Lcd.printf("%d\n",counter);

  M5.Lcd.printf("%2.2f\n",pitch);

  M5.Lcd.printf("%2.2f\n",roll);

  M5.Lcd.printf("%2.2f\n",yaw);


  counter++;
}

// -- END OF FILE --
