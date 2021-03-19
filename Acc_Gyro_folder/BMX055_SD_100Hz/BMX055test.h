#include <Wire.h>
#define AC_ADDRop 0x19
#define GY_ADDRop 0x69
#define MG_ADDRop 0x13
#define AC_ADDRsh 0x18
#define GY_ADDRsh 0x68
#define MG_ADDRsh 0x10

// #define AX  0x3B
// #define AY  0x3D
// #define AZ  0x3F
// #define TP  0x41    //  data not used
// #define GX  0x43
// #define GY  0x45
// #define GZ  0x47


class BMX055sensor{
    public:
        BMX055sensor(uint8_t _AC_add,uint8_t _GY_add,uint8_t _MG_add );
        // void read();
        void read_acc();
        void read_gyro();
        void read_mg();
        void begin();
        // short int getAccelx(){ return ax; };
        // short int getAccely(){ return ay; };
        // short int getAccelz(){ return az; };
        // short int getGyrox(){ return gx; };
        // short int getGyroy(){ return gy; };
        // short int getGyroz(){ return gz; };
        // short int getTemp();
    // private:
        int ax, ay, az;
        int Temp;
        int gx, gy, gz;
        int mx, my, mz;
        uint8_t AC_add,GY_add,MG_add;
                


};
