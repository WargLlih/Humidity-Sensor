#pragma once

#include <Arduino.h>
#include "../../utils/types.hpp"

/**
 * @brief Maximum length of the Wi-Fi SSID.
 */
#define MAX_SSID_LEN 32

/**
 * @brief Maximum length of the Wi-Fi password.
 */
#define MAX_PASS_LEN 32

/**
 * @class WifiManager
 * @brief A class for managing Wi-Fi configuration and access point setup.
 */
class WifiManager {
 private:
  /**
   * @brief Private constructor to enforce singleton pattern.
   */
  WifiManager();

  /**
   * @brief Private instance variable for the singleton pattern.
   */
  static WifiManager* instance;

  /**
   * @brief Buffer for storing the Wi-Fi SSID.
   */
  char wifi_ssid[MAX_SSID_LEN];

  /**
   * @brief Buffer for storing the Wi-Fi password.
   */
  char wifi_password[MAX_PASS_LEN];

 public:
  /**
   * @brief Getter for the Wi-Fi SSID.
   * @return A string containing the Wi-Fi SSID.
   */
  string_t ssid();

  /**
   * @brief Getter for the Wi-Fi password.
   * @return A string containing the Wi-Fi password.
   */
  string_t password();

  /**
   * @brief Set the Wi-Fi SSID.
   * @param ssid A string containing the Wi-Fi SSID.
   * @param size The size of the provided string (limited to MAX_SSID_LEN).
   */
  void setSSID(const string_t ssid, uint8_t size);

  /**
   * @brief Set the Wi-Fi password.
   * @param password A string containing the Wi-Fi password.
   * @param size The size of the provided string (limited to MAX_PASS_LEN).
   */
  void setPassword(const string_t password, uint8_t size);

  /**
   * @brief Get the singleton instance of the WifiManager class.
   * @return A pointer to the WifiManager instance.
   */
  static WifiManager* getInstance();

  /**
   * @brief Run an access point for Wi-Fi configuration.
   */
  void runAccessPoint();
};
