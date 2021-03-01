#include <M5Stack.h>
#include "SD.h"
#include "MPU6050test.h"

SPIClass SPI2;

unsigned long currentTime=0;
unsigned long prevTime=0;
unsigned long prevTime1s=0;
unsigned long cnt=0;
unsigned long flag=0;
uint32_t counter = 0;
short int time_interval = 10;
short int first_flag = 1;
short int csv_num = 1;


File file;
#include <Wire.h>




//short int prevX = 0;
//short int prevY = 0;
//short int prevZ = 0;
//short int prevgX = 0;
//short int prevgY = 0;
//short int prevgZ = 0;

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
    sensor1.read();
    if(first_flag==1){
        M5.Lcd.fillScreen(BLACK);
        first_flag=0;
        prevTime=millis();
        
      }
    currentTime=millis();
      
      if(currentTime-prevTime>=time_interval) {

        prevTime+=time_interval;
        // file.println((String)currentTime + "," + (String)sensor1.ax + "," + (String)sensor1.ay + "," + (String)sensor1.az
        // + "," + (String)sensor1.gx + "," + (String)sensor1.gy + "," + (String)sensor1.gz + "," + (String)sensor1.Temp);
        file.println((String)currentTime+"," +(String)prevTime);
        cnt++;
        
        M5.Lcd.setCursor(0, 0,4);
        M5.Lcd.setTextColor(WHITE, BLACK);
             M5.Lcd.printf("%d\r\n",sensor1.ax);
             M5.Lcd.printf("%d\r\n",sensor1.ay);
             M5.Lcd.printf("%d\r\n",sensor1.az);
             M5.Lcd.printf("%d\r\n",sensor1.gx);
             M5.Lcd.printf("%d\r\n",sensor1.gy);
             M5.Lcd.printf("%d\r\n",sensor1.gz);

        // prevTime+=time_interval;
      }
    
      // currentTime=millis();
      if(currentTime-prevTime1s>=1000) {
        // M5.Lcd.fillScreen(BLACK);
//        M5.Lcd.setCursor(0, 0, 4);
        M5.Lcd.printf("%d\r\n",cnt);
        cnt=0;
        prevTime1s=currentTime;
      }
    }

    if(M5.BtnA.wasPressed()) {
      flag = (flag+1)%2;
      if(flag==1) {
        file = SD.open("/test"+(String)csv_num+".csv", FILE_WRITE);
      }
      if(flag==0) {
        file.close();
        M5.Lcd.printf("STOP\r\n");
        csv_num++;
        first_flag=1;
      }
    }

}
