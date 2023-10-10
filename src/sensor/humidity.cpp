#include <Arduino.h>

#include "humidity.hpp"

HumiditySensor::HumiditySensor(byte IO_pin) : io_pin(IO_pin), value(0) {}

void HumiditySensor::readValue() {
  this->value = analogRead(this->io_pin);
}

uint16_t HumiditySensor::getValue() {
  return this->value;
}

void HumiditySensor::executeReadValue() {
  for (; true; delay(100)) {
    this->readValue();
  }
}

namespace humiditySensorTasks {
void taskReadData(void* p) {
  HumiditySensor* sensor = (HumiditySensor*)p;
  sensor->executeReadValue();
}
}  // namespace humiditySensorTasks