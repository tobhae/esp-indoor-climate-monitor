#include <time.h>

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <esp_sleep.h>
#include <Wire.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#include "config.h"
#include "debug.h"
#include "ota.h"
#include "wifi.h"
#include "buffer.h"
#include "influx.h"
#include "sensor.h"
#include "ntp.h"

void setup() {
  init_hardware();
  build_influxdb_url();

  if(!connect_wifi()) {
    enter_deep_sleep();
  }

  if(!sync_time()) {
    enter_deep_sleep();
  }

  if(should_check_for_update) {
    check_for_update();
  }

  ClimateData data = read_climate();

  char payload[PAYLOAD_SIZE];

  if (!build_influx_payload(payload, sizeof(payload), data)) {
    enter_deep_sleep();
  }

  if (!flush_buffer()) {
    buffer_push(payload);
    enter_deep_sleep();
  }

  if (!post_influxdb(payload, strlen(payload))) {
    buffer_push(payload);
  } 

  enter_deep_sleep();

}

void loop() {
  /* Function unused. Execution cycle occurs entirely in setup() and enters deep sleep when finished. */
}

void enter_deep_sleep() {
  DEBUG_PRINTLN("Shutting down WiFi and entering deep sleep.");

  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);

  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * 1000000ULL);
  esp_deep_sleep_start();
}