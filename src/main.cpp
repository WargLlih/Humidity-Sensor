#include <Arduino.h>

#include "lcd/LCD.hpp"
#include "sensor/humidity.hpp"

// Tasks ID
TaskHandle_t task1;
TaskHandle_t task2;

void setup() {
  Serial.begin(115200);
  HumiditySensor* sensor = new HumiditySensor(33);
  LCDManager* lcd_manager = new LCDManager();

  // __________________________________________________________________________
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
                          configMINIMAL_STACK_SIZE + 2024, p1, 1, &task1,
                          APP_CPU_NUM);

  // __________________________________________________________________________
  xTaskCreatePinnedToCore(
      humiditySensorTasks::taskReadData, "Task-Read-Sensor-Data",
      configMINIMAL_STACK_SIZE + 2024, sensor, 1, &task2, APP_CPU_NUM);
}

void loop() {}
