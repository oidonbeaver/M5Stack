#include "BMX055test.h"

BMX055sensor::BMX055sensor(uint8_t _AC_add,uint8_t _GY_add,uint8_t _MG_add )
{
  AC_add= _AC_add;
  GY_add= _GY_add;
  MG_add= _MG_add;
}


void BMX055sensor::read()
{
    Wire.beginTransmission(address);
    Wire.write(BMX055_AX);
    Wire.endTransmission();  
    //  request 14bytes (int16 x 7)
    Wire.requestFrom(address, 14);
    //  get 14bytes
    ax = Wire.read() << 8;  ax |= Wire.read();
    ay = Wire.read() << 8;  ay |= Wire.read();
    az = Wire.read() << 8;  az |= Wire.read();
    Temp = Wire.read() << 8;  Temp |= Wire.read();
    gx = Wire.read() << 8; gx |= Wire.read();
    gy = Wire.read() << 8; gy |= Wire.read();
    gz = Wire.read() << 8; gz |= Wire.read();


}



void BMX055sensor::begin()
{
  Wire.beginTransmission(address);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission();
}
