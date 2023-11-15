#include "LCD.hpp"

#include "../sensor/humidity.hpp"
#include "../utils/types.hpp"
#include <LiquidCrystal_I2C.h>

LCDManager::LCDManager(byte address) {
  this->lcd_obj = new LiquidCrystal_I2C(address, 16, 4);
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

LiquidCrystal_I2C *LCDManager::screenLCD() { return this->lcd_obj; }

void LCDManager::Light(bool state) {
  state ? this->lcd_obj->backlight() : this->lcd_obj->noBacklight();
}

float UA(float t);

float UR(uint16_t f);

void LCDManager::printData(uint16_t data, float temp) {
  this->lcd_obj->setCursor(0, 0);
  this->lcd_obj->printf("b3-n5 INPE");
  this->lcd_obj->setCursor(0, 1);
  this->lcd_obj->printf("RAW (Hz): %5u", data);
  this->lcd_obj->setCursor(0, 2);
  this->lcd_obj->printf("UR (%.2f C):", temp);
  this->lcd_obj->setCursor(0, 3);
  this->lcd_obj->printf("%.2f", UR(data)/UA(temp));
}

namespace lcdTasks {
void taskPrintOnLCD(void *p) {
  taskPrintOnLCDParam_t *params = (taskPrintOnLCDParam_t *)p;
  HumiditySensor *sensor = params->humiditySensor;
  LCDManager *lcd_manager = params->lcdManager;

  lcd_manager->Light(true);

  for (; true; vTaskDelay(pdMS_TO_TICKS(500))) {
    uint16_t data = sensor->value();
    lcd_manager->printData(data, sensor->t);
  }
}
} // namespace lcdTasks
