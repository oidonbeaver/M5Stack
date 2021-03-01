#include "MPU6050test.h"

MPU6050sensor::MPU6050sensor(uint8_t _address)
{
  address= _address;
}


void MPU6050sensor::read()
{
    Wire.beginTransmission(address);
    Wire.write(MPU6050_AX);
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



void MPU6050sensor::begin()
{
  Wire.beginTransmission(address);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission();
}
