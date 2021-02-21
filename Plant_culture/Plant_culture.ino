/*Please install the < Adafruit BMP280 Library > （https://github.com/adafruit/Adafruit_BMP280_Library）
 * from the library manager before use. 
 *This code will display the temperature, humidity and air pressure information on the screen*/

#include <M5Stack.h>
#include <Wire.h>

//env2
#include "Adafruit_Sensor.h"
#include <Adafruit_BMP280.h>
#include "SHT3X.h"
SHT3X sht30;
Adafruit_BMP280 bme;

float tmp = 0.0;
float hum = 0.0;
float pressure = 0.0;

//clock
#define TFT_GREY 0x5AEB
#define HEATER_PIN 1
#define LIGHT_PIN 16
int tmp_flg =0;

uint32_t targetTime = 0;                    // for next 1 second timeout

static uint8_t conv2d(const char* p); // Forward declaration needed for IDE 1.6.x

uint8_t hh = conv2d(__TIME__), mm = conv2d(__TIME__ + 3), ss = conv2d(__TIME__ + 6); // Get H, M, S from compile time

byte omm = 99, oss = 99;
byte xcolon = 0, xsecs = 0;
unsigned int colour = 0;

uint16_t analogRead_value = 0;
uint16_t digitalRead_value = 0;


void setup() {
  pinMode(HEATER_PIN, OUTPUT);
  pinMode(LIGHT_PIN, OUTPUT);
  M5.begin();
  M5.Power.begin();

    //disable the speak noise
  dacWrite(25, 0);
  Wire.begin();
  M5.Lcd.setBrightness(10);
  M5.Lcd.setTextSize(3);
  // Serial.println(F("ENV Unit(SHT30 and BMP280) test..."));

  while (!bme.begin(0x76)){  
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    M5.Lcd.println("Could not find a valid BMP280 sensor, check wiring!");
  }
  M5.Lcd.clear(WHITE);
  // M5.Lcd.println("ENV Unit test...");

  targetTime = millis() + 1000;

}


void loop() {
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.setTextColor(BLACK, WHITE);
  M5.Lcd.setTextSize(5);


  if (targetTime < millis()) {
    // Set next update for 1 second later
    targetTime = millis() + 1000;

    // Adjust the time values by adding 1 second
    ss++;              // Advance second
    if (ss == 60) {    // Check for roll-over
      ss = 0;          // Reset seconds to zero
      omm = mm;        // Save last minute time for display update
      mm++;            // Advance minute
      if (mm > 59) {   // Check for roll-over
        mm = 0;
        hh++;          // Advance hour
        if (hh > 23) { // Check for 24hr roll-over (could roll-over on 13)
          hh = 0;      // 0 for 24 hour clock, set to 1 for 12 hour clock
        }
      }
    }
  }


  if(hh>6 && hh <20){
    digitalWrite(LIGHT_PIN,HIGH);
    M5.Lcd.setTextColor(PINK, WHITE);
  }else{
    digitalWrite(LIGHT_PIN,LOW);
    M5.Lcd.setTextColor(BLACK, WHITE);
  }
  M5.Lcd.printf("%02d:%02d:%02d\n",hh,mm,ss);

  
  pressure = bme.readPressure();
  if(sht30.get()==0){
    tmp = sht30.cTemp;
    hum = sht30.humidity;
  }
  Serial.printf("Temperatura: %2.2f*C  Humedad: %0.2f%%  Pressure: %0.2fPa\r\n", tmp, hum, pressure);

  M5.Lcd.setTextSize(3);

  
  if(tmp<25){
    digitalWrite(HEATER_PIN,HIGH);
    M5.Lcd.setTextColor(RED, WHITE);
    tmp_flg=1;
  }else if(tmp>30){
    digitalWrite(HEATER_PIN,LOW);
    M5.Lcd.setTextColor(BLACK, WHITE);
    tmp_flg=0;
  }else{
    if(tmp_flg==1){
      M5.Lcd.setTextColor(RED, WHITE);
      digitalWrite(HEATER_PIN,HIGH);
    }else{
      M5.Lcd.setTextColor(BLACK, WHITE);
      digitalWrite(HEATER_PIN,LOW);
    }
  }
  M5.Lcd.printf("Temp: %2.1fC  \r\n", tmp);



  M5.Lcd.setTextColor(BLACK, WHITE);
  M5.Lcd.printf("Humi: %2.0f%%  \r\n", hum);
  M5.Lcd.printf("Pressure:%2.0fPa\r\n", pressure);
  analogRead_value = analogRead(36);


  M5.Lcd.printf("Light: %d  \r\n", analogRead_value);

  delay(100);

}




// Function to extract numbers from compile time string
static uint8_t conv2d(const char* p) {
  uint8_t v = 0;
  if ('0' <= *p && *p <= '9')
    v = *p - '0';
  return 10 * v + *++p - '0';
}
