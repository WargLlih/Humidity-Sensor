#pragma once

#include "utils/types.hpp"

class HumiditySensor {
 public:
  HumiditySensor(byte IO);

 private:
  byte __IO_pin;

 public:
  uint16_t ReadValue();
};