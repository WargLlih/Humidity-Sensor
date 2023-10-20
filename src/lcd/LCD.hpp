#pragma once

#include "../sensor/humidity.hpp"
#include <LiquidCrystal_I2C.h>

/**
 * @class LCDManager
 * @brief A class for managing an LCD display using the LiquidCrystal_I2C
 * library.
 *
 * This class provides methods for initializing, controlling, and displaying
 * data on an LCD screen.
 */
class LCDManager {
public:
  /**
   * @brief Constructor for the LCDManager class.
   *
   * @param address The i2c address from ADS1115
   * connected to the humidity sensor.
   *
   */
  LCDManager(byte address);

  /**
   * @brief Destructor for the LCDManager class.
   */
  ~LCDManager();

private:
  /**
   * @brief Pointer to the LiquidCrystal_I2C object used for controlling the LCD
   * screen.
   */
  LiquidCrystal_I2C *lcd_obj;

public:
  /**
   * @brief Get a pointer to the LiquidCrystal_I2C object used for the LCD
   * screen.
   *
   * @return A pointer to the LiquidCrystal_I2C object.
   */
  LiquidCrystal_I2C *screenLCD();

  /**
   * @brief Print a 16-bit integer value on the LCD screen.
   *
   * @param data The integer value to be displayed on the LCD screen.
   */
  void printData(uint16_t data);

  /**
   * @brief Control the backlight of the LCD screen.
   *
   * @param state If `true`, the backlight is turned on; if `false`, it is
   * turned off.
   */
  void Light(bool state);
};

/**
 * @namespace lcdTasks
 * @brief A namespace containing functions related to LCD tasks.
 */
namespace lcdTasks {
/**
 * @brief Struct representing the parameters for the taskPrintOnLCD function.
 */
typedef struct {
  HumiditySensor *humiditySensor; // Pointer to a humidity sensor object.
  LCDManager *lcdManager;         // Pointer to an LCDManager object.
} taskPrintOnLCDParam_t;

/**
 * @brief Task function for printing humidity data on an LCD screen.
 *
 * This function is intended to be run as a task and prints humidity data on an
 * LCD screen using the provided HumiditySensor and LCDManager objects.
 *
 * @param p A pointer to a taskPrintOnLCDParam_t struct containing the necessary
 * parameters.
 */
void taskPrintOnLCD(void *p);
} // namespace lcdTasks
