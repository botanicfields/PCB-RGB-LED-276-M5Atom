// Copyright 2021 BotanicFields, Inc.
// BF-025 RGB LED Clock 276 for M5Atom
// Demonstrations Noise

#define FASTLED_ESP32_I2S true
#include <M5Atom.h>
#include "BF_RGB_LED_276.h"
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
  ResetParameters();
}

void loop()
{
  DemoNoise();
}
