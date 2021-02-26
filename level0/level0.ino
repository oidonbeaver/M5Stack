#include <M5Stack.h>
#include "utility/MPU9250.h"

#define MULTISAMPLE 20

MPU9250 IMU;

void readAccelMulti(float *accel,int multi){
  float ax, ay, az;
  ax=ay=az=0;
  for(int i=0; i<multi; i++){
   while(!(IMU.readByte(MPU9250_ADDRESS,INT_STATUS) & 0x01)) ;
   IMU.readAccelData(IMU.accelCount);
   IMU.getAres();
   ax += (float)IMU.accelCount[0];
   ay += (float)IMU.accelCount[1];
   az += (float)IMU.accelCount[2];

  }
  accel[0] = ax/multi;
  accel[1] = ay/multi;
  accel[2] = az/multi;
}

void drawGrid(){
  M5.Lcd.drawLine(41,120,279,120,CYAN);
  M5.Lcd.drawLine(160,1,160,239,CYAN);
  M5.Lcd.drawCircle(160,120,119,CYAN);
  M5.Lcd.drawCircle(160,120,60,CYAN);
}

int oldx = 0;
int oldy = 0;

void drawSpot(int ax, int ay){
  int x,y;
  x = map(constrain(ax,-300,300),-300,300,40,280);
  y = map(constrain(ay,-300,300),-300,300,240,0);
  M5.Lcd.fillCircle(oldx,oldy,7,BLACK);
  drawGrid();
  M5.Lcd.fillCircle(x,y,7,WHITE);
  oldx=x;
  oldy=y;

}

float offset[3];
#define MOVINGAVG 10
float movingavgx[MOVINGAVG],movingavgy[MOVINGAVG];
int _indx = 0;


void setup() {
  // put your setup code here, to run once:
  M5.begin();
  Wire.begin();
  IMU.initMPU9250();
  // IMU.calibrateMPU9250(IMU.gyroBias,IMU.accelBias);
  readAccelMulti(offset,MULTISAMPLE);

  for (int i = 0; i<MOVINGAVG;i++){
    movingavgx[i]=offset[0];
    movingavgy[i]=offset[1];
  }


}

void loop() {
  // put your main code here, to run repeatedly:
  float ax,ay;
  float accel[3];
  M5.update();
  readAccelMulti(accel,MULTISAMPLE);

  movingavgx[_indx] = accel[0];
  movingavgy[_indx] = accel[1];
  _indx = (_indx + 1)%MOVINGAVG;
  ax=ay=0;
  for (int i =0; i< MOVINGAVG; i++){
    ax += movingavgx[i];
    ay += movingavgy[i];
  }
  ax /= MOVINGAVG;
  ay /= MOVINGAVG;

  if(M5.BtnA.wasPressed()){
    offset[0]=ax;
    offset[1]=ay;
  }

  
  drawSpot((int)((ax-offset[0])*1000),(int)((ay-offset[1])*1000));
  // drawSpot((int)((ax)*1000),(int)((ay)*1000));


  delay(100);

}
