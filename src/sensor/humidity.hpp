#pragma once
#include "utils/types.hpp"
#include <ADS1X15.h>
#include <cstdint>

#define SENSOR_PIN_IN_ADS1115 0
/**
 * @class HumiditySensor
 * @brief A class for interfacing with a humidity sensor via ADS1115.
 *
 * This class provides methods to read humidity data from a sensor and execute
 * reading operations.
 */
class HumiditySensor {
public:
  /**
   * @brief Constructor for the HumiditySensor class.
   *
   * @param address The i2c address from ADS1115
   * connected to the humidity sensor.
   */
  HumiditySensor(byte address);

private:
  /**
   * @brief Private member variable to store the i2c address from ADS1115
   * connected to the humidity sensor.
   */
  byte i2c_address;

  /**
   * @brief Private member variable to store the humidity sensor's value.
   */
  uint16_t value;

  /**
   * @brief Private member variable to store the ADS1115 instance.
   */
  ADS1115 *ads_module;

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
void taskReadData(void *p);
} // namespace humiditySensorTasks
