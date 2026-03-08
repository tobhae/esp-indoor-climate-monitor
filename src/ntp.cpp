#include "ntp.h"

#include <Arduino.h>
#include <time.h>

#include "config.h"
#include "debug.h"

/* TODO: Consider changing if (now < 10000) to if (now < 1700000000) */

bool sync_time() {
  /* Synchronizes system time using NTP */
  configTime(0, 0, NTP_SERVER);

  const unsigned long timeout = 10000;
  unsigned long start = millis();

  time_t now = time(nullptr);

  while(now < 100000 && millis() - start < timeout) {
    delay(200);
    now = time(nullptr);
  }

  if (now < 10000) {
    DEBUG_PRINTLN("NTP synchronization failed.");
    return false;
  }

  DEBUG_BLOCK({
    /* Debugging prints */
    struct tm timeinfo;
    gmtime_r(&now, &timeinfo); // UTC
    char timeString [32];
    strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", &timeinfo);

    Serial.print("NTP: ");
    Serial.println(now);

    Serial.print("UTC: ");
    Serial.println(timeString);

    Serial.println("Time synchronized.");
  });

  return true;
}