#include <M5Stack.h>
#include "utility/MPU9250.h"

MPU9250 IMU;

void setup(){
    M5.begin();
    Wire.begin();
    IMU.initMPU9250();
    // IMU.calibrateMPU9250(IMU.gyroBias,IMU.accelBias);
    M5.Lcd.setTextSize(2);



}

void loop(){
    if (IMU.readByte(MPU9250_ADDRESS,INT_STATUS) & 0x01){
        IMU.readAccelData(IMU.accelCount);
        IMU.getAres();
        IMU.ax=(float)IMU.accelCount[0]*IMU.aRes;
        IMU.ay=(float)IMU.accelCount[1]*IMU.aRes;
        IMU.az=(float)IMU.accelCount[2]*IMU.aRes;
        M5.Lcd.clear();
        M5.Lcd.setCursor(0,0);
        M5.Lcd.print("MPU9250 acceleration");
        M5.Lcd.setCursor(0,32);
        M5.Lcd.printf("X: %7.2f mG\n", 1000*IMU.ax);
        M5.Lcd.printf("Y: %7.2f mG\n", 1000*IMU.ay);
        M5.Lcd.printf("Z: %7.2f mG\n", 1000*IMU.az);
    }
    delay(500);

}


// void setup()
// {
//   M5.begin();
//   Wire.begin();

//   IMU.initMPU9250();
//   // IMU.calibrateMPU9250(IMU.gyroBias,IMU.accelBias);
//   IMU.getGres();
  
// }

// void loop()
// {
//   if (IMU.readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01)
//   {
//     IMU.readAccelData(IMU.accelCount);
//     IMU.getAres();
//     IMU.ax = (float)IMU.accelCount[0] * IMU.aRes;
//     IMU.ay = (float)IMU.accelCount[1] * IMU.aRes;
//     IMU.az=(float)IMU.accelCount[2]*IMU.aRes;

//     M5.Lcd.clear();
//     M5.Lcd.setCursor(0,0);
//     M5.Lcd.print("MPU9250 acceleration");
//     M5.Lcd.setCursor(0,32);
//     M5.Lcd.printf("X: %7.2f mG\n", 1000*IMU.ax);
//     M5.Lcd.printf("Y: %7.2f mG\n", 1000*IMU.ay);
//     M5.Lcd.printf("Z: %7.2f mG\n", 1000*IMU.az);

//   }
//   delay(200);
// }