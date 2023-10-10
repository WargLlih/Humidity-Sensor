#include <LiquidCrystal_I2C.h>

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
