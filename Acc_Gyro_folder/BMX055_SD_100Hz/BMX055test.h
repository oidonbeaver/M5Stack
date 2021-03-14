#include <Wire.h>

#define BMX055_AC_ADDR68 0x18
#define BMX055_GY_ADDR68 0x68
#define BMX055_MG_ADDR68 0x10
#define BMX055_AC_ADDR69 0x19
#define BMX055_GY_ADDR69 0x69
#define BMX055_MG_ADDR69 0x13
#define BMX055_AX  0x3B
#define BMX055_AY  0x3D
#define BMX055_AZ  0x3F
#define BMX055_TP  0x41    //  data not used
#define BMX055_GX  0x43
#define BMX055_GY  0x45
#define BMX055_GZ  0x47


class BMX055sensor{
    public:
        BMX055sensor(uint8_t _address=0x69);
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
