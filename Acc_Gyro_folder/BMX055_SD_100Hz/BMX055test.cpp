#include "BMX055test.h"

BMX055sensor::BMX055sensor(uint8_t _AC_add,uint8_t _GY_add,uint8_t _MG_add )
{
  AC_add= _AC_add;
  GY_add= _GY_add;
  MG_add= _MG_add;
}


void BMX055sensor::begin()
{
  Wire.beginTransmission(AC_add);
  Wire.write(0x0F); // Select PMU_Range register
  Wire.write(0x03);   // Range = +/- 2g
  Wire.endTransmission();
  delay(100);


  Wire.beginTransmission(AC_add);
  Wire.write(0x10);  // Select PMU_BW register
  // Wire.write(0x0D);  // Bandwidth = 250 Hz P27
Wire.write(0x08);  // Bandwidth = 7.81 Hz
  Wire.endTransmission();
  delay(100);


  // Wire.beginTransmission(AC_add);
  // Wire.write(0x11);  // Select PMU_LPW register
  // Wire.write(0x00);  // Normal mode, Sleep duration = 0.5ms
  // Wire.endTransmission();
  // delay(100);

  Wire.beginTransmission(GY_add);
  Wire.write(0x0F);  // Select Range register
  Wire.write(0x04);  // Full scale = +/- 125 degree/s
  Wire.endTransmission();
  delay(100);

  // ------//
  Wire.beginTransmission(GY_add);
  Wire.write(0x10);  // Select Bandwidth register
  // Wire.write(0x02);  // ODR = 1000 Hz, filter bandwidth 116Hz P83
Wire.write(0x07);  // ODR = 100 Hz
  Wire.endTransmission();
  delay(100);
 //

//   Wire.beginTransmission(GY_add);
//   Wire.write(0x11);  // Select LPM1 register
//   Wire.write(0x00);  // Normal mode, Sleep duration = 2ms
//   Wire.endTransmission();
//   delay(100);
//  //

  Wire.beginTransmission(MG_add);
  Wire.write(0x4B);  // Select Mag register
  Wire.write(0x83);  // Soft reset 10000011
  Wire.endTransmission();
  delay(100);
  //
  Wire.beginTransmission(MG_add);
  Wire.write(0x4B);  // Select Mag register
  Wire.write(0x01);  // Soft reset
  Wire.endTransmission();
  delay(100);


  Wire.beginTransmission(MG_add);
  Wire.write(0x4C);  // Select Mag register
  // Wire.write(0x07);  // Normal Mode, ODR = 30 Hz P135
  Wire.write(0x38);  // Normal Mode, ODR = 30 Hz 000111000 P135
  Wire.endTransmission();
 //

//  ------//
  Wire.beginTransmission(MG_add); //no pre-decrement operator for type　エラー
  Wire.write(0x4E);  // Select Mag register
  Wire.write(0x84);  // X, Y, Z-Axis enabled
  Wire.endTransmission();
 //

 Wire.beginTransmission(MG_add);
  Wire.write(0x51);  // Select Mag register
  Wire.write(0x04);  // No. of Repetitions for X-Y Axis = 9
  Wire.endTransmission();
 //------------------------------------------------------------//
  Wire.beginTransmission(MG_add);
  Wire.write(0x52);  // Select Mag register
  Wire.write(0x16);  // No. of Repetitions for Z-Axis = 15
  Wire.endTransmission();

}





void BMX055sensor::read_acc()
{
  // Wire.beginTransmission(AC_add);
  int data[6];
  for (int i = 0; i < 6; i++)
  {
    Wire.beginTransmission(AC_add);
    Wire.write((2 + i));// Select data register
    Wire.endTransmission();
    Wire.requestFrom(AC_add, 1);// Request 1 byte of data
    // Read 6 bytes of data
    // xAccl lsb, xAccl msb, yAccl lsb, yAccl msb, zAccl lsb, zAccl msb
    if (Wire.available() == 1)
      data[i] = Wire.read();
  }
  // Convert the data to 12-bits
  ax = ((data[1] * 256) + (data[0] & 0xF0));
 
  ay = ((data[3] * 256) + (data[2] & 0xF0));

  az = ((data[5] * 256) + (data[4] & 0xF0));

  Wire.beginTransmission(AC_add);
  Wire.write(0x08);// データレジスタを選択
  Wire.endTransmission();
  Wire.requestFrom(AC_add, 1);// 1バイトのデータを要求する
  Temp = Wire.read();


}
void BMX055sensor::read_gyro()
{
  int data[6];
  for (int i = 0; i < 6; i++)
  {
    Wire.beginTransmission(GY_add);
    Wire.write((2 + i));    // Select data register
    Wire.endTransmission();
    Wire.requestFrom(GY_add, 1);    // Request 1 byte of data
    // Read 6 bytes of data
    // xGyro lsb, xGyro msb, yGyro lsb, yGyro msb, zGyro lsb, zGyro msb
    if (Wire.available() == 1)
      data[i] = Wire.read();
  }
  // Convert the data
  gx = (data[1] * 256) + data[0];
  
  gy = (data[3] * 256) + data[2];
  
  gz = (data[5] * 256) + data[4];
  
}

void BMX055sensor::read_mg()
{
  int data[8];
  for (int i = 0; i < 8; i++)
  {
    Wire.beginTransmission(MG_add);
    Wire.write((0x42 + i));    // Select data register
    Wire.endTransmission();
    Wire.requestFrom(MG_add, 1);    // Request 1 byte of data
    // Read 6 bytes of data
    // xMag lsb, xMag msb, yMag lsb, yMag msb, zMag lsb, zMag msb
    if (Wire.available() == 1)
      data[i] = Wire.read();
  }
  // Convert the data
  mx = ((data[1] <<8) | (data[0]>>3));

  my = ((data[3] <<8) | (data[2]>>3));

  mz = ((data[5] <<8) | (data[4]>>3));

}


// void BMX055sensor::read()
// {
//     Wire.beginTransmission(address);
//     Wire.write(BMX055_AX);
//     Wire.endTransmission();  
//     //  request 14bytes (int16 x 7)
//     Wire.requestFrom(address, 14);
//     //  get 14bytes
//     ax = Wire.read() << 8;  ax |= Wire.read();
//     ay = Wire.read() << 8;  ay |= Wire.read();
//     az = Wire.read() << 8;  az |= Wire.read();
//     Temp = Wire.read() << 8;  Temp |= Wire.read();
//     gx = Wire.read() << 8; gx |= Wire.read();
//     gy = Wire.read() << 8; gy |= Wire.read();
//     gz = Wire.read() << 8; gz |= Wire.read();


// }
