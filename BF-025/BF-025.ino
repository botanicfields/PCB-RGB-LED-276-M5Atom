// Copyright 2021 BotanicFields, Inc.
// BF-025 RGB LED Clock 276 for M5Atom
// Demonstrations

#define FASTLED_ESP32_I2S true
#include <M5Atom.h>
#include "BF_Wifi.h"
#include "BF_Pcf8563.h"
#include "BF_RtcxNtp.h"
#include "BF_RGB_LED_276.h"

#include "BF_DemoClock.h"
#include "BF_DemoTimeShock.h"
#include "BF_DemoCylon.h"
#include "BF_DemoHueRing.h"
#include "BF_DemoNoise.h"

void setup()
{
  // button, Serial monitor
  const bool serial_enable(true);
  const bool i2c_enable(true);
  const bool display_enable(true);
  M5.begin(serial_enable, !i2c_enable, !display_enable);

  // FastLED, Lamp test
  InitFastLed();
  LampTest();

  // I2C, RTC
  ShowPattern(pattern_rtc, 100);  // delay = 100ms
  const int wire_scl(21);       // GPIO21
  const int wire_sda(25);       // GPIO25
  const int wire_freq(100000);  // 100kHz
  Wire.begin(wire_sda, wire_scl, wire_freq);
  rtcx.Begin(Wire);
//  rtcx.ClockOutForTrimmer();
  SetTimeFromRtcx();

  // Wi-Fi
  ShowPattern(pattern_wifi, 100);  // delay = 100ms
  WifiBegin();

  // NTP
  ShowPattern(pattern_ntp, 100);  // delay = 100ms
  NtpBegin();
}

void loop()
{
  ResetParameters();
  DemoClock();
  ResetParameters();
  DemoTimeShock();
  ResetParameters();
  DemoCylon();
  ResetParameters();
  DemoHueRing();
  ResetParameters();
  DemoNoise();
}
