// Copyright 2021 BotanicFields, Inc.
// BF-025 RGB LED Clock 276 for M5Atom
// Demonstration: Cylon for lamp test, referred to the sample program of FastLED

#define FASTLED_ESP32_I2S true
//#define FASTLED_ALLOW_INTERRUPTS 0

#include <M5Atom.h>
#include "BF_RGB_LED_276.h"
#include "BF_DemoCylon.h"

const int loop_ms = 20;  // 20ms
static int last_ms = 0;

const int fade_rate = 250;  // 250 of 255

const int num_of_repeat  = 3;
static int repeat_remain = 0;

void DemoCylon()
{
  Serial.println("[DemoCylon]start");
  repeat_remain = num_of_repeat;
  last_ms = millis();

  while (repeat_remain > 0) {

    // forward
    for (int j = 0; j < num_of_leds; ++j)
      if(DemoCylonSub(j) != 0)
        return;

    // backward
    for (int j = num_of_leds - 1; j >= 0; --j)
      if(DemoCylonSub(j) != 0)
        return;

    --repeat_remain;
  }
  Serial.println("[DemoCylon]end");
  return;
}

int DemoCylonSub(int dot_head)
{
  // fade all
  for (int i = 0; i < num_of_leds; ++i)
    leds[i].nscale8(fade_rate);

  // head dot
  static int hue = 0;
  leds[dot_head] = ColorFromPalette(palette_color, hue++, 255);

  M5.update();
  int button_check = CheckButton();
  if (button_check == 2000 || button_check == 1000) {  // exit or go next
    Serial.println("[DemoCylon]break");
    return 1;
  }
  else if (button_check != 0) {
    Serial.println("[DemoCylon]repeat extended");
    repeat_remain = num_of_repeat;
  }

  FastLED.show();

  delay(loop_ms - (millis() - last_ms));
  last_ms = millis();
  return 0;
}
