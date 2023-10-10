#include <Arduino.h>

#include "humidity.hpp"

HumiditySensor::HumiditySensor(byte IO_pin) : __IO_pin(IO_pin) {
    pinMode(this->__IO_pin, INPUT);
}

uint16_t HumiditySensor::ReadValue() {
    return analogRead(this->__IO_pin);
}
