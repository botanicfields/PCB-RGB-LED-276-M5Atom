// Copyright 2021 BotanicFields, Inc.
// BF-025 RGB LED Clock 276 for M5Atom
// Demonstrations 

#include "BF-025.h"
#include <WiFi.h>
#include <WiFiManager.h>  // https://github.com/tzapu/WiFiManager
#include "BF_DemoClock.h"
#include "BF_DemoCylon.h"
#include "BF_DemoHueRing.h"
#include "BF_DemoNoise.h"

// initialize WiFiManager
WiFiManager wm;

// for M5Atom
const bool serial_enable   = true;
const bool serial_disable  = false;  // not used
const bool i2c_enable      = true;
const bool i2c_disable     = false;  // not used
const bool display_enable  = true;   // not used
const bool display_disable = false;

// for NTP and time
const int   gmt_offset = 3600 * 9;  // JST-9
const int   daylight   = 3600 * 0;  // No daylight time
const char* ntp_server = "pool.ntp.org";
struct tm      td;  // time of day .. year, month, day, hour, minute, second
struct timeval tv;  // time value .. second. micro-second

void setup()
{
  M5.begin(serial_enable, i2c_enable, display_disable);
  delay(3000);  // initialize delay for M5Atom

  // initialize FastLED
  InitFastLed();
  LampTest();

  ShowPattern(pattern_wifi, 100);  // delay = 100ms

  // connect Wifi
  // wm.resetSettings();  // for testing
  if (!wm.autoConnect())
    Serial.println("Failed to connect");
  else
    Serial.println("connected...yeey :)");

  ShowPattern(pattern_ntp, 100);  // delay = 100ms 

  // start NTP
  configTime(gmt_offset, daylight, ntp_server);
  while (!getLocalTime(&td)) {
    Serial.println("Waiting to obtain time");
    delay(100);
  }
  Serial.println(&td, "%A %B %d %Y %H:%M:%S");
}

void loop()
{ 
  ResetParameters();
  DemoClock();
  ResetParameters();
  DemoCylon();
  ResetParameters();
  DemoHueRing();
  ResetParameters();
  DemoNoise();
}
