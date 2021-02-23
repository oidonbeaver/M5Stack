#include <M5Stack.h>
#include <math.h>
#include "utility/MPU9250.h"

MPU9250 IMU;

const int col_top = TFT_RED, col_bottom = TFT_BLACK;

const float hx = 160, hy = 120;
int qx = hx, qy = 0;

const float d = atan2(hy, hx);

template <typename T>
int sgn(T val)
{
  return (T(0) < val) - (val < T(0));
}

void triangle(int x1, int y1, int x2, int y2, int x3, int y3, int color)
{
  M5.Lcd.fillTriangle(hx + x1, hy + y1, hx + x2, hy + y2, hx + x3, hy + y3, color);
}

void setup()
{
  M5.begin();
  Wire.begin();

  IMU.initMPU9250();
  IMU.getAres();
  IMU.getGres();
  M5.Lcd.fillRect(0, hy, 2 * hx, 2 * hy, col_bottom);
}

void loop()
{
  if (IMU.readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01)
  {
    IMU.readAccelData(IMU.accelCount);
    IMU.ax = (float)IMU.accelCount[0] * IMU.aRes;
    IMU.ay = (float)IMU.accelCount[1] * IMU.aRes;
    IMU.az=(float)IMU.accelCount[2]*IMU.aRes;


    M5.Lcd.setCursor(0,0);
    M5.Lcd.print("MPU9250 acceleration");
    M5.Lcd.setCursor(0,32);
    M5.Lcd.printf("X: %7.2f mG\n", 1000*IMU.ax);
    M5.Lcd.printf("Y: %7.2f mG\n", 1000*IMU.ay);
    M5.Lcd.printf("Z: %7.2f mG\n", 1000*IMU.az);

  }
  delay(500);
}
