#pragma once

#include "utils/types.hpp"

/**
 * @class HumiditySensor
 * @brief A class for interfacing with a humidity sensor.
 *
 * This class provides methods to read humidity data from a sensor and execute
 * reading operations.
 */
class HumiditySensor {
 public:
  /**
   * @brief Constructor for the HumiditySensor class.
   *
   * @param IO The input/output (IO) pin connected to the humidity sensor.
   */
  HumiditySensor(byte IO);

 private:
  /**
   * @brief Private member variable to store the IO pin connected to the
   * humidity sensor.
   */
  byte io_pin;

  /**
   * @brief Private member variable to store the humidity sensor's value.
   */
  uint16_t value;

 private:
  /**
   * @brief Private method to read the humidity sensor's value.
   */
  void readValue();

 public:
  /**
   * @brief Get the last-read value from the humidity sensor.
   *
   * @return The humidity sensor's value as a 16-bit unsigned integer.
   */
  uint16_t getValue();

  /**
   * @brief Execute a reading operation to update the humidity sensor's value.
   */
  void executeReadValue();
};

/**
 * @namespace humuditySendorTasks
 * @brief A namespace containing functions related to humidity sensor tasks.
 */
namespace humiditySensorTasks {
/**
 * @brief Task function for reading data from a humidity sensor.
 *
 * This function is intended to be run as a task and is responsible for reading
 * data from a humidity sensor.
 *
 * @param p A pointer (void*) that can be used to pass any necessary parameters.
 */
void taskReadData(void* p);
}  // namespace humiditySensorTasks
