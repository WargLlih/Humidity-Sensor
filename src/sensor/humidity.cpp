#include "humidity.hpp"
#include <Arduino.h>

HumiditySensor::HumiditySensor() {
  pinMode(DIGITAL_PIN, INPUT_PULLUP);
}

void HumiditySensor::execute() {
  unsigned long t0 = millis();
  uint32_t cont = 0;
  uint8_t old_value = HIGH;
  uint8_t current_value = HIGH;

  for (; true;) {
    current_value = (uint8_t)digitalRead(DIGITAL_PIN);

    if (current_value != old_value) {
      old_value = current_value;
      cont++;
    }

    if (millis() - t0 > 1000) {
      vTaskDelay(1);
      t0 = millis();
      this->_value = cont;
      cont = 0;
    }
  }
}

uint32_t HumiditySensor::value() {
  return this->_value;
}

namespace humiditySensorTasks {
void taskReadData(void* p) {
  HumiditySensor* sensor = (HumiditySensor*)p;
  sensor->execute();
}
}  // namespace humiditySensorTasks
