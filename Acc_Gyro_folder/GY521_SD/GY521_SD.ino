

#include <M5Stack.h>
#include "SD.h"

#include <Wire.h>



SPIClass SPI2;

unsigned long currentTime;
unsigned long prevTime=0;
unsigned long cnt=0;
unsigned long flag=0;


File file;

#include "GY521.h"

GY521 sensor(0x69);

uint32_t counter = 0;



float prevX = 0;
float prevY = 0;
float prevZ = 0;
//float prepitch = 0;
//float preroll = 0;
//float preyaw = 0;


void setup() {
  // M5の設定
  M5.begin();
  // M5.IMU.Init();
  M5.Lcd.setRotation(3);

  SPI2.begin(0, 36, 26, -1); // SPI初期化
  if(!SD.begin(-1, SPI2)) { // SDカード初期化
    M5.Lcd.println("Card Mount Failed");
    return;
  }
  dacWrite(25, 0);

// シリアル通信の設定　後で消す
Serial.begin(115200);
  Serial.println(__FILE__);

  Wire.begin();

  delay(100);
  while (sensor.wakeup() == false)
  {
    Serial.print(millis());
    Serial.println("\tCould not connect to GY521");
    delay(1000);
  }
  sensor.setAccelSensitivity(0);  // 8g
  sensor.setGyroSensitivity(0);   // 500 degrees/s

  sensor.setThrottle();
  Serial.println("start...");
  
  // set callibration values from calibration sketch.
  sensor.axe = 0;
  sensor.aye = 0;
  sensor.aze = 0;
  sensor.gxe = 0;
  sensor.gye = 0;
  sensor.gze = 0;

}

void loop() {
  M5.update();
  


  if(flag==1) {
    sensor.read();
    float ax = sensor.getAccelX();
    float ay = sensor.getAccelY();
    float az = sensor.getAccelZ();
//    float pitch = sensor.getPitch();
//    float roll  = sensor.getRoll();
//    float yaw   = sensor.getYaw();
    if(ax!=prevX || ay!=prevY || az!=prevZ) {
    // if(1==1) {
//    if(pitch!=prepitch || roll!=preroll || yaw!=preyaw) {
      file.println((String)millis() + "," + (String)ax + "," + (String)ay + "," + (String)az);
      cnt++;
      prevX=ax;
      prevY=ay;
      prevZ=az;
      M5.Lcd.setCursor(0, 0);
//      M5.Lcd.printf("%2.2f\n",ax);
//      M5.Lcd.printf("%2.2f\n",ay);
//      M5.Lcd.printf("%2.2f\n",az);
//      M5.Lcd.printf("%2.2f\n",ax);
//      M5.Lcd.printf("%2.2f\n",ay);
//      M5.Lcd.printf("%2.2f\n",az);

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
