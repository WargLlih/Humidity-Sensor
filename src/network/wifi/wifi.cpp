#include "wifi.hpp"

#include <WiFi.h>

#include "utils/utils.hpp"

WifiManager* WifiManager::__instance = NULL;

char* WifiManager::ssid() {
  return this->__ssid;
}

char* WifiManager::password() {
  return this->__password;
}

void WifiManager::setSSID(const string_t ssid, uint8_t size) {
  if (size < MAX_SSID_LEN) {
    utils::bytecpy(__ssid, ssid, size);
    __ssid[size] = '\0';
    return;
  }
  utils::bytecpy(__ssid, ssid, sizeof(__ssid));
  __ssid[sizeof(__ssid) - 1] = '\0';
}

void WifiManager::setPassword(const string_t password, uint8_t size) {
  if (size < MAX_PASS_LEN) {
    utils::bytecpy(__password, password, size);
    __password[size] = '\0';
    return;
  }
  utils::bytecpy(__password, password, sizeof(__password));
  __password[sizeof(__password) - 1] = '\0';
}

WifiManager* WifiManager::getInstance() {
  if (WifiManager::__instance == NULL) {
    WifiManager::__instance = new WifiManager();
  }
  return WifiManager::__instance;
}

void WifiManager::runAccessPoint() {
  WiFi.mode(WIFI_AP);
  WiFi.softAP(this->__ssid, this->__password);
}
