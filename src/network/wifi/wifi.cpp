#include "wifi.hpp"

#include <WiFi.h>

#include "utils/utils.hpp"

WifiManager* WifiManager::instance = NULL;

char* WifiManager::ssid() {
  return this->wifi_ssid;
}

char* WifiManager::password() {
  return this->wifi_password;
}

void WifiManager::setSSID(const string_t ssid, uint8_t size) {
  if (size < MAX_SSID_LEN) {
    utils::bytecpy(wifi_ssid, ssid, size);
    wifi_ssid[size] = '\0';
    return;
  }
  utils::bytecpy(wifi_ssid, ssid, sizeof(wifi_ssid));
  wifi_ssid[sizeof(wifi_ssid) - 1] = '\0';
}

void WifiManager::setPassword(const string_t password, uint8_t size) {
  if (size < MAX_PASS_LEN) {
    utils::bytecpy(wifi_password, password, size);
    wifi_password[size] = '\0';
    return;
  }
  utils::bytecpy(wifi_password, password, sizeof(wifi_password));
  wifi_password[sizeof(wifi_password) - 1] = '\0';
}

WifiManager* WifiManager::getInstance() {
  if (WifiManager::instance == NULL) {
    WifiManager::instance = new WifiManager();
  }
  return WifiManager::instance;
}

void WifiManager::runAccessPoint() {
  WiFi.mode(WIFI_AP);
  WiFi.softAP(this->wifi_ssid, this->wifi_password);
}
