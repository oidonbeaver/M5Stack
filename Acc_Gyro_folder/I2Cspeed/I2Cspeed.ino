#define M5STACK_MPU6886 

#include <M5Stack.h>

unsigned long currentTime;
unsigned long prevTime=0;
unsigned long cnt=0;

float accX = 0.0f;
float accY = 0.0f;
float accZ = 0.0f;
float prevX = 0.0f;
float prevY = 0.0f;
float prevZ = 0.0f;
void setup() {
  M5.begin();
  M5.Power.begin();
//  M5.IMU.Init();
  M5.IMU.Init();
  Serial.begin(115200);
  dacWrite(25, 0);
}

void loop() {
  M5.IMU.getAccelData(&accX, &accY, &accZ);
  if(accX!=prevX || accY!=prevY || accZ!=prevZ) {
    cnt++;
    prevX=accX;
    prevY=accY;
    prevZ=accZ;
  }

  currentTime=millis();
  if(currentTime-prevTime>=1000) {
    Serial.println(cnt);
    cnt=0;
    prevTime=currentTime;
  }
}
