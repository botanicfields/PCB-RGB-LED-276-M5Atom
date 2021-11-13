// Copyright 2021 BotanicFields, Inc.
// BF-025 RGB LED Clock 276 for M5Atom
// Demonstration: Noise to check Perlin noise and color palette

#define FASTLED_ESP32_I2S true
//#define FASTLED_ALLOW_INTERRUPTS 0

#include <M5Atom.h>
#include "BF_RGB_LED_276.h"
#include "BF_DemoNoise.h"

const int loop_ms = 20;          // 20ms
const int num_of_repeat = 1500;  // 20ms * 3000 = 30s
static int last_ms = 0;

void DemoNoise()
{
  Serial.println("[DemoNoise]start");
  int repeat_remain = num_of_repeat;
  last_ms = millis();

  while (repeat_remain > 0) {

    // circle
    for(int y = 0; y < leds1_num_of_y; ++y)
      for(int x = 0; x < leds1_num_of_x; ++x) {
        foreground_color = ColorFromPalette(palette_color, inoise8(ScaleXY(x), ScaleXY(y), ScaleZ()));
        PutDotLeds1(x, y);
      }

    // rectangle
    for(int y = leds1_num_of_y; y < leds1_num_of_y + leds2_num_of_y; ++y)
      for(int x = 0; x < leds2_num_of_x; ++x) {
        foreground_color = ColorFromPalette(palette_color, inoise8(ScaleXY(x), ScaleXY(y), ScaleZ()));
        PutDotLeds2(x, y - leds1_num_of_y);
      }

    // check button
    M5.update();
    int button_check = CheckButton();
    if (button_check == 2000 || button_check == 1000) {  // exit or go next
      Serial.println("[DemoNoise]break");
      repeat_remain = 1;
    }
    else if (button_check != 0) {
      Serial.println("[DemoNoise]repeat extended");
      repeat_remain = num_of_repeat;
    }

    FastLED.show();

    delay(loop_ms - (millis() - last_ms));
    --repeat_remain;
    last_ms = millis();
  }

  Serial.println("[DemoNoise]end");
}

// make x, y for inoise8()
//   0xHHLL format HH: integral part, LL: fractional part
//   hh: leds2_num_of_y * n, LL: (1 / leds2_num_of_y) * m
//
//     x = 0x000       0x100       0x200
// y = 0x000 + - - - - - + - - - - - + - - - -
//           | . . . . . | . . . . . | . . . .
//           | . . . . . | . . . . . | . . . .
//           | . . . . . | . . . . . | . . . .
//           | . . . . . | . . . . . | . . . .
//           | . . . . . | . . . . . | . . . .
//     0x100 + - - - - - + - - - - - + - - - -
int ScaleXY(int xy)
{
  if (scale_factor >= 0)
    return xy * 256 / leds2_num_of_y * scale_factor;
  else
    return xy * 256 / leds2_num_of_y / - scale_factor;
}

// make z for inoise8()
//   0xHHLL format HH: integral part, LL: fractional part
//   HH: sec, LL: msec .. ms * 256 / 1000
int ScaleZ()
{
  if (period_factor >= 0)
    return last_ms * 256 / 1000 * period_factor;
  else
    return last_ms * 256 / 1000 / - period_factor;
}
