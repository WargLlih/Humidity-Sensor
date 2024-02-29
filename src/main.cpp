#include <Arduino.h>

#include "lcd/LCD.hpp"
#include "sensor/humidity.hpp"

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 17
#define DHTTYPE DHT22

// Tasks ID
TaskHandle_t task1;
TaskHandle_t task2;
TaskHandle_t task3;

float UR(uint32_t f) {
  float ur = -0.3236888671696293*f/1000 + 163.5348810653951;
  if (ur > 100) {
    ur = 100;
  }
  if (ur <= 0) {
    ur = 0;
  }
  return ur;
}

void mydht(void* p) {
  HumiditySensor* sensor_h = (HumiditySensor*)p;
  DHT_Unified* dht = new DHT_Unified(DHTPIN, DHTTYPE);
  dht->begin();
  sensor_t sensor;

  float temperature_dht;
  float air_humidity_dht;

  for (; true; vTaskDelay(pdMS_TO_TICKS(1000))) {
    sensors_event_t event;
    dht->temperature().getEvent(&event);
    if (isnan(event.temperature)) {
      Serial.println(F("Error reading temperature!"));
    } else {
      temperature_dht = event.temperature;
      sensor_h->t = temperature_dht;
    }
    // Get humidity event and print its value.
    dht->humidity().getEvent(&event);
    if (isnan(event.relative_humidity)) {
      Serial.println(F("Error reading humidity!"));
    } else {
      air_humidity_dht = event.relative_humidity;
    }

    Serial.printf(
        "{\"temperature_dht\": %.2f,"
        "\"air_humidity_dht\": %.2f, "
        "\"air_humidity_inpe_hz\": %.3f}\n",
        temperature_dht, 
        air_humidity_dht, 
        sensor_h->value() / 1000.0);
  }
}

void setup() {
  Serial.begin(115200);
  HumiditySensor* sensor = new HumiditySensor();
  LCDManager* lcd_manager = new LCDManager(0x27);

  //__________________________________________________________________________
  lcdTasks::taskPrintOnLCDParam_t* p1 = NULL;
  p1 = (lcdTasks::taskPrintOnLCDParam_t*)malloc(
      sizeof(lcdTasks::taskPrintOnLCDParam_t));

  if (p1 == NULL) {
    Serial.println("Error on malloc");
    return;
  }

  p1->humiditySensor = sensor;
  p1->lcdManager = lcd_manager;

  xTaskCreatePinnedToCore(lcdTasks::taskPrintOnLCD, "Task-Print-On-LCD",
                          configMINIMAL_STACK_SIZE + 2048, p1, 1, &task1,
                          APP_CPU_NUM);

  //__________________________________________________________________________
  xTaskCreatePinnedToCore(
      humiditySensorTasks::taskReadData, "Task-Read-Sensor-Data",
      configMINIMAL_STACK_SIZE + 2048, sensor, 1, &task2, PRO_CPU_NUM);

  //__________________________________________________________________________
  // xTaskCreatePinnedToCore(mydht, "Task-Read-Sensor-DHT22",
  //                         configMINIMAL_STACK_SIZE + 4000, sensor, 2, &task3,
  //                         APP_CPU_NUM);
}

void loop() {}
