#include <Arduino.h>

#include "HardwareSerial.h"
#include "humidity.hpp"
#include <ADS1X15.h>

HumiditySensor::HumiditySensor(byte address) : i2c_address(address), value(0) {
  this->ads_module = new ADS1115(this->i2c_address);
  if (!this->ads_module->begin()) {
    Serial.println("Error on being ADS1115");
  }
  this->ads_module->setGain(0);
}

void HumiditySensor::readValue() {
  this->value = this->ads_module->readADC(SENSOR_PIN_IN_ADS1115);
}

uint16_t HumiditySensor::getValue() { return this->value; }

void HumiditySensor::executeReadValue() {
  for (; true; delay(100)) {
    this->readValue();
  }
}

namespace humiditySensorTasks {
void taskReadData(void *p) {
  HumiditySensor *sensor = (HumiditySensor *)p;
  sensor->executeReadValue();
}
} // namespace humiditySensorTasks
