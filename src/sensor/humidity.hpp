#pragma once

#include "utils/types.hpp"

class HumiditySensor {
 public:
  HumiditySensor(byte IO);

 private:
  byte __IO_pin;
  uint16_t __value;

 private:
  void __readValue();

 public:
  uint16_t getValue();
  void executeReadValue();
};

namespace humuditySendorTasks {
void taskReadData(void* p);
}