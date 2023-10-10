#pragma once

#include <LiquidCrystal_I2C.h>
#include "../sensor/humidity.hpp"

class LCDManager {
 public:
  LCDManager();
  ~LCDManager();

 public:
  LiquidCrystal_I2C* __lcd;

 public:
  LiquidCrystal_I2C* screenLCD();
  void printData(uint16_t data);
  void Light(bool state);
};

namespace lcdTasks {
// taskPrintOnLCD parameter
typedef struct {
  HumiditySensor* humiditySensor;
  LCDManager* lcdManager;
} taskPrintOnLCDParam_t;

void taskPrintOnLCD(void* p);
}  // namespace lcdTasks