#include <M5Stack.h>
#include "utility/MPU9250.h"

MPU9250 IMU;

void drawGrid(){
  M5.Lcd.drawLine(41,120,279,120,CYAN);
  M5.Lcd.drawLine(160,1,160,239,CYAN);
  M5.Lcd.drawCircle(160,120,119,CYAN);
  M5.Lcd.drawCircle(160,120,60,CYAN);
}

void drawSpot(int ax, int ay){
  int x,y;
  x = map(constrain(ax,-300,300),-300,300,40,280);
  y = map(constrain(ay,-300,300),-300,300,240,0);
  M5.Lcd.fillScreen(BLACK);
  drawGrid();
  M5.Lcd.fillCircle(x,y,7,WHITE);

}
void setup() {
  // put your setup code here, to run once:
  M5.begin();
  Wire.begin();
  IMU.initMPU9250();


}

void loop() {
  // put your main code here, to run repeatedly:
  float ax,ay;
  while(! (IMU.readByte(MPU9250_ADDRESS,INT_STATUS) & 0x01));

  IMU.readAccelData(IMU.accelCount);
  IMU.getAres();

  ax = (float)IMU.accelCount[0]*IMU.aRes;
  ay = (float)IMU.accelCount[1]*IMU.aRes;
  drawSpot((int)(ax*1000),(int)(ay*1000));
  delay(100);

}
