#include <M5Stack.h>
#include "SD.h"
#include "MPU6050test.h"

SPIClass SPI2;

unsigned long currentTime=0;
unsigned long prevTime=0;
unsigned long prevTime1s=0;
unsigned long cnt=0;
unsigned long cnt_interval=0;
unsigned long flag=0;
uint32_t counter = 0;
short int time_interval = 10;
short int first_flag = 1;
short int csv_num = 1;


File file;
#include <Wire.h>





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
  sensor2.begin();
  sensor1.begin();

  Serial.begin(115200);
  Serial.println("*** started");
  
}

void loop() {

  
  
  M5.update();
  //  send start address
  if(flag==1) {
    // sensor1.read();
    // sensor2.read();
    if(first_flag==1){
        M5.Lcd.fillScreen(BLACK);
        first_flag=0;
        prevTime=millis();
        
      }
    currentTime=millis();
  
  

    cnt_interval++;
  
      
    if(currentTime-prevTime>=time_interval) {
        sensor1.read();
        sensor2.read();
        prevTime+=time_interval;




        // file.println((String)currentTime+"," +(String)prevTime + "," + (String)tempax1 + "," + (String)tempay1 + "," + (String)tempaz1
        // + "," + (String)tempgx1 + "," + (String)tempgy1 + "," + (String)tempgz1 + "," + (String)temptemp1
        // + "," + (String)tempax2 + "," + (String)tempay2 + "," + (String)tempaz2
        // + "," + (String)tempgx2 + "," + (String)tempgy2 + "," + (String)tempgz2 + "," + (String)temptemp2);
        // // file.println((String)currentTime+"," +(String)prevTime);
        file.println((String)currentTime+"," +(String)prevTime + "," + (String)sensor1.ax + "," + (String)sensor1.ay + "," + (String)sensor1.az
        + "," + (String)sensor1.gx + "," + (String)sensor1.gy + "," + (String)sensor1.gz + "," + (String)sensor1.Temp
        + "," + (String)sensor2.ax + "," + (String)sensor2.ay + "," + (String)sensor2.az
        + "," + (String)sensor2.gx + "," + (String)sensor2.gy + "," + (String)sensor2.gz + "," + (String)sensor2.Temp);
        cnt++;
        cnt_interval = 0;
        M5.Lcd.setCursor(0, 0,2);
        M5.Lcd.setTextColor(WHITE, BLACK);
//         M5.Lcd.printf("acc1x: %d\r\n ",sensor1.ax);
//         M5.Lcd.printf("acc1y: %d\r\n ",sensor1.ay);
//         M5.Lcd.printf("acc1z: %d\r\n ",sensor1.az);
//         M5.Lcd.printf("gyro1x %d\r\n ",sensor1.gx);
//         M5.Lcd.printf("gyro1y: %d\r\n ",sensor1.gy); 
//         M5.Lcd.printf("gyro1z: %d\r\n ",sensor1.gz); 
//         M5.Lcd.printf("acc2x: %d\r\n ",sensor2.ax);
//         M5.Lcd.printf("acc2y: %d\r\n ",sensor2.ay);
//         M5.Lcd.printf("acc2z: %d\r\n ",sensor2.az);
//         M5.Lcd.printf("gyro2x: %d\r\n ",sensor2.gx);
//         M5.Lcd.printf("gyro2y: %d\r\n ",sensor2.gy);
//         M5.Lcd.printf("gyro2z: %d\r\n ",sensor2.gz);
              // Serial.print("  "); Serial.print(sensor1.ax);
              // Serial.println("");

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
        M5.Lcd.printf("test%d\r\n",csv_num);
        csv_num++;
        first_flag=1;
      }
    }

}
