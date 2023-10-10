#include "LCD.hpp"

#include <LiquidCrystal_I2C.h>
#include "../sensor/humidity.hpp"

LCDManager::LCDManager() {
  this->__lcd = new LiquidCrystal_I2C(0x27, 20, 4);
  this->__lcd->init();
  this->__lcd->clear();
}

LCDManager::~LCDManager() {
  if (this->__lcd == NULL) {
    return;
  }
  delete this->__lcd;
  this->__lcd = NULL;
}

LiquidCrystal_I2C* LCDManager::screenLCD() {
  return this->__lcd;
}

void LCDManager::Light(bool state) {
  state ? this->__lcd->backlight() : this->__lcd->noBacklight();
}

void LCDManager::printData(uint16_t data) {
  this->__lcd->setCursor(0, 0);
  this->__lcd->printf("raw: %4u (%.2f)", data, data / 4096.0);

  this->__lcd->setCursor(0, 1);
  this->__lcd->printf("voltage: %.1fv", data / 4096.0 * 3.3);
}

namespace lcdTasks {
void taskPrintOnLCD(void* p) {
  taskPrintOnLCDParam_t* params = (taskPrintOnLCDParam_t*)p;
  HumiditySensor* sensor = params->humiditySensor;
  LCDManager* lcd_manager = params->lcdManager;

  lcd_manager->Light(true);

  for (; true; vTaskDelay(pdMS_TO_TICKS(100))) {
    uint16_t data = sensor->getValue();
    lcd_manager->printData(data);
  }
}
}  // namespace lcdTasks