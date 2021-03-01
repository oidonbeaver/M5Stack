#define M5STACK_MPU6886 
#include <M5Stack.h>
#include "SD.h"

SPIClass SPI2;

unsigned long currentTime;
unsigned long prevTime=0;
unsigned long cnt=0;
unsigned long flag=0;

float accX = 0.0f;
float accY = 0.0f;
float accZ = 0.0f;
float prevX = 0.0f;
float prevY = 0.0f;
float prevZ = 0.0f;

File file;

void setup() {
  M5.begin();
  M5.IMU.Init();
  M5.Lcd.setRotation(3);

  SPI2.begin(0, 36, 26, -1); // SPI初期化
  if(!SD.begin(-1, SPI2)) { // SDカード初期化
    M5.Lcd.println("Card Mount Failed");
    return;
  }
}

void loop() {
  M5.update();

  if(flag==1) {
    M5.IMU.getAccelData(&accX, &accY, &accZ);
    if(accX!=prevX || accY!=prevY || accZ!=prevZ) {
      file.println((String)millis() + "," + (String)accX + "," + (String)accY + "," + (String)accZ);
      cnt++;
      prevX=accX;
      prevY=accY;
      prevZ=accZ;
    }
  
    currentTime=millis();
    if(currentTime-prevTime>=1000) {
      M5.Lcd.fillScreen(BLACK);
      M5.Lcd.setCursor(0, 0, 4);
      M5.Lcd.println(cnt);
      cnt=0;
      prevTime=currentTime;
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
