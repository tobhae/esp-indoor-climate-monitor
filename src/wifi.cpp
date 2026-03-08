#include "wifi.h"

#include <Arduino.h>
#include <WiFi.h>

#include "config.h"
#include "debug.h"

bool connect_wifi() {
  /* Attempts to connect to configured WiFi network */
  #if USE_STATIC_IP
  WiFi.config(
    IPAddress (WIFI_STATIC_IP),
    IPAddress (WIFI_DNS),
    IPAddress (WIFI_GATEWAY),
    IPAddress (WIFI_SUBNET));
  #endif

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  unsigned long start = millis();
  const unsigned long timeout = 15000;

  while (WiFi.status() != WL_CONNECTED && millis() - start < timeout) {
    delay(500);
  }

  if (WiFi.status() == WL_CONNECTED) {
    DEBUG_PRINT("Connected to WiFi with IP: ");
    DEBUG_PRINTLN(WiFi.localIP());
    return true;
  }

  DEBUG_PRINTLN("WiFi connection failed.");
  return false;
}