#include <M5Stack.h>gg
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
    float theta = atan2(IMU.ax, -IMU.ay);

    IMU.readGyroData(IMU.gyroCount);
    IMU.gz = (float)IMU.gyroCount[2] * IMU.gRes;

    int px, py;

    if (fabs(hx * tan(-theta)) < hy)
    {
      px = hx * sgn(cos(-theta));
      py = px * tan(-theta);
    }
    else
    {
      py = hy * sgn(sin(-theta));
      px = py / tan(-theta);
    }

    int col1, col2;
    if (px * qy - py * qx > 0)
    {
      col1 = col_bottom;
      col2 = col_top;
    }
    else
    {
      col1 = col_top;
      col2 = col_bottom;
    }

    triangle(0, 0, qx, qy, px, py, col1);
    triangle(0, 0, -qx, -qy, -px, -py, col2);

    if (qx != px && qy != py)
    {
      int cx = hx * sgn(qx);
      int cy = hy * sgn(qy);

      triangle(cx, cy, qx, qy, px, py, col1);
      triangle(-cx, -cy, -qx, -qy, -px, -py, col2);
    }

    qx = px;
    qy = py;
  }
}
