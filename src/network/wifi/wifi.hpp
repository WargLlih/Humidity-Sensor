#pragma once

#include <Arduino.h>
#include "../../utils/types.hpp"

#define MAX_SSID_LEN 32
#define MAX_PASS_LEN 32

class WifiManager {
 private:
  static WifiManager* __instance;
  char __ssid[MAX_SSID_LEN];
  char __password[MAX_PASS_LEN];

 public:
  /**
   * @brief getter for __ssid.
   * @return string_t wifi ssid 
   */
  string_t ssid();


  string_t password();

  void setSSID(const string_t ssid, uint8_t size);

  void setPassword(const string_t password, uint8_t size);

  static WifiManager* getInstance();

  void runAccessPoint();

  // Getter for password
};