#include <Wire.h>

#define MPU6050_ADDR68 0x68
#define MPU6050_ADDR69 0x69
#define MPU6050_AX  0x3B
#define MPU6050_AY  0x3D
#define MPU6050_AZ  0x3F
#define MPU6050_TP  0x41    //  data not used
#define MPU6050_GX  0x43
#define MPU6050_GY  0x45
#define MPU6050_GZ  0x47


class MPU6050sensor{
    public:
        MPU6050sensor(uint8_t _address=0x69);
        void read();
        void begin();
        short int getAccelx(){ return ax; };
        short int getAccely(){ return ay; };
        short int getAccelz(){ return az; };
        short int getGyrox(){ return gx; };
        short int getGyroy(){ return gy; };
        short int getGyroz(){ return gz; };
        // short int getTemp();
    // private:
        short int ax, ay, az;
        short int Temp;
        short int gx, gy, gz;
        uint8_t address;
                


};
