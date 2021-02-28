#include <M5Stack.h>
#include "SD.h"
#include "MPU6050test.h"

SPIClass SPI2;

unsigned long currentTime;
unsigned long prevTime=0;
unsigned long prevTime1s=0;
unsigned long cnt=0;
unsigned long flag=0;
uint32_t counter = 0;

File file;
#include <Wire.h>




short int prevX = 0;
short int prevY = 0;
short int prevZ = 0;
short int prevgX = 0;
short int prevgY = 0;
short int prevgZ = 0;

MPU6050sensor sensor1(0x68);
MPU6050sensor sensor2(0x69);


void setup() {
  M5.begin();
  // M5.IMU.Init();
  M5.Lcd.setRotation(3);

  SPI2.begin(0, 36, 26, -1); // SPI初期化
  if(!SD.begin(-1, SPI2)) { // SDカード初期化
    M5.Lcd.println("Card Mount Failed");
    return;
  }
  dacWrite(25, 0);
  //  serial for debugging
  
  //  i2c as a master
  Wire.begin();
  //  wake it up
  sensor2.read();
  sensor1.read();
}

void loop() {
  M5.update();
  //  send start address
  if(flag==1) {
    sensor2.read();
    currentTime=millis();
      //  debug monitor
      // if(sensor2.ax!=prevX || sensor2.ay!=prevY || sensor2.az!=prevZ||sensor2.gx!=prevgX || sensor2.gy!=prevgY || sensor2.gz!=prevgZ) {
      //    if(pitch!=prepitch || roll!=preroll || yaw!=preyaw) {
      if(currentTime-prevTime>=5) {
        prevX=sensor2.ax;
        prevY=sensor2.ay;
        prevZ=sensor2.az;
        prevgX=sensor2.gx;
        prevgY=sensor2.gy;
        prevgZ=sensor2.gz;
        file.println((String)currentTime + "," + (String)prevX + "," + (String)prevY + "," + (String)prevZ
        + "," + (String)prevgX + "," + (String)prevgY + "," + (String)prevgZ);
        cnt++;
        
        M5.Lcd.setCursor(0, 0);
            // M5.Lcd.printf("%d\n",ax);
            // M5.Lcd.printf("%d\n",ay);
            // M5.Lcd.printf("%d\n",az);
        //      M5.Lcd.printf("%2.2f\n",ax);
        //      M5.Lcd.printf("%2.2f\n",ay);
        //      M5.Lcd.printf("%2.2f\n",az);
        prevTime=currentTime;
      }
    
      // currentTime=millis();
      if(currentTime-prevTime1s>=1000) {
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(0, 0, 4);
        M5.Lcd.println(cnt);
        cnt=0;
        prevTime1s=currentTime;
      }
    }

    if(M5.BtnA.wasPressed()) {
      flag = (flag+1)%2;
      if(flag==1) {
        file = SD.open("/test1.csv", FILE_WRITE);
      }
      if(flag==0) {
        file.close();
        M5.Lcd.println("STOP");
      }
    }

}

