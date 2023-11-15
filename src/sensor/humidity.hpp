#pragma once
#include "../utils/types.hpp"

#define DIGITAL_PIN 16

class HumiditySensor {
public:
  HumiditySensor();

private:
  uint16_t _value;

public:
  float t;
  void execute();
  uint16_t value();
};

namespace humiditySensorTasks {
void taskReadData(void *p);
} // namespace humiditySensorTasks
