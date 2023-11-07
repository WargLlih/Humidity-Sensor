#include "humidity.hpp"
#include <ADS1X15.h>
#include <Arduino.h>

ADS1115* ADS_M = NULL;

HumiditySensor::HumiditySensor() {
  // ADS_M = new ADS1115(0x48);
  // if (!ADS_M->begin()) {
  //   Serial.println("Error on being ADS1115");
  // }
  // ADS_M->setGain(0);

  // this->_value = 0;

  pinMode(DIGITAL_PIN, INPUT_PULLUP);
}

// 5v
// min 2k
// max 60k
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
      t0 = millis();
      this->_value = cont;
      cont = 0;
      vTaskDelay(1);
    }
  }
}

uint16_t HumiditySensor::value() {
  return this->_value;
}

namespace humiditySensorTasks {
void taskReadData(void* p) {
  HumiditySensor* sensor = (HumiditySensor*)p;
  sensor->execute();
}
}  // namespace humiditySensorTasks
