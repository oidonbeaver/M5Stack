#include <M5Stack.h>

#include "SD.h"

SPIClass SPI2;

void setup() {
  M5.begin();
  M5.Lcd.setRotation(3);

  SPI2.begin(0, 36, 26, -1); // SPI初期化

  if(!SD.begin(-1, SPI2)) { // SDカード初期化
    M5.Lcd.println("Card Mount Failed");
    return;
  }
  uint8_t cardType = SD.cardType(); // SDカード種別取得
  if (cardType == CARD_NONE) {
    M5.Lcd.println("None SD Card");
    return;
  } else if (cardType == CARD_MMC) {
    M5.Lcd.println("SD Card Type: MMC");
  } else if (cardType == CARD_SD) {
    M5.Lcd.println("SD Card Type: SDSC");
  } else if (cardType == CARD_SDHC) {
    M5.Lcd.println("SD Card Type: SDHC");
  } else {
    M5.Lcd.println("SD Card Type: UNKNOWN");
  }
  uint64_t cardSize = SD.cardSize() / (1024 * 1024); // SDカード容量取得
  M5.Lcd.printf("SD Card Size: %lluMB\n", cardSize);
}

void loop() {
}
