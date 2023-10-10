#include <Arduino.h>

#include "humidity.hpp"

HumiditySensor::HumiditySensor(byte IO_pin) : __IO_pin(IO_pin), __value(0) {}

void HumiditySensor::__readValue() {
  this->__value = analogRead(this->__IO_pin);
}

uint16_t HumiditySensor::getValue() {
  return this->__value;
}

void HumiditySensor::executeReadValue() {
  for (; true; delay(100)) {
    this->__readValue();
  }
}

namespace humuditySendorTasks {
void taskReadData(void* p) {
  HumiditySensor* sensor = (HumiditySensor*)p;
  sensor->executeReadValue();
}
}  // namespace humuditySendorTasks