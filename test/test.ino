/*
    Description: Read the analog quantity and digital quantity returned by the EARTH unit, and convert the analog quantity into 12-bit data and display it on the screen.
*/
#include <M5Stack.h>

void setup() {
  M5.begin();
  M5.Power.begin();
  //disable the speak noise
  dacWrite(25, 0);

  M5.Lcd.setTextColor(YELLOW);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(65, 50);
  M5.Lcd.printf("UNIT_EARTH EXAMPLE\n");
  pinMode(26, INPUT);
  // pinMode(2, INPUT);
  // pinMode(5, INPUT);
  pinMode(1, INPUT);
  pinMode(3, INPUT);

}

uint16_t analogRead_value = 0;
uint16_t a1=0,a2 = 0,a26 = 0;
float soil_mois=0;
void loop() {
  // put your main code here, to run repeatedly:

 

  // analogRead_value = analogRead(36);
  // // digitalRead_value = digitalRead(26);
  // digitalRead_value = analogRead(26);

  


  M5.Lcd.setTextColor(YELLOW,BLACK);
  M5.Lcd.setCursor(0, 0);


  
  a1 = analogRead(35);

  M5.Lcd.printf("%d\n", analogRead_value);
  M5.Lcd.printf("a1 %d\n", a1);

// analogRead_value = analogRead(5);
// soil_mois=(4095-analogRead_value)/analogRead_value*100;
//   M5.Lcd.printf("soil_mois %3.2f\n", soil_mois);

  delay(100);
}
// analogread OK 2,26,25,35,36
// NG 5,1,3,23,19