#include "LCD.hpp"

#include <LiquidCrystal_I2C.h>
#include "../sensor/humidity.hpp"

LCDManager::LCDManager() {
  this->lcd_obj = new LiquidCrystal_I2C(0x27, 20, 4);
  this->lcd_obj->init();
  this->lcd_obj->clear();
}

LCDManager::~LCDManager() {
  if (this->lcd_obj == NULL) {
    return;
  }
  delete this->lcd_obj;
  this->lcd_obj = NULL;
}

LiquidCrystal_I2C* LCDManager::screenLCD() {
  return this->lcd_obj;
}

void LCDManager::Light(bool state) {
  state ? this->lcd_obj->backlight() : this->lcd_obj->noBacklight();
}

void LCDManager::printData(uint16_t data) {
  this->lcd_obj->setCursor(0, 0);
  this->lcd_obj->printf("raw: %4u (%.2f)", data, data / 4096.0);

  this->lcd_obj->setCursor(0, 1);
  this->lcd_obj->printf("voltage: %.1fv", data / 4096.0 * 3.3);
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