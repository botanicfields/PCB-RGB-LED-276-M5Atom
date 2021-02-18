// Copyright 2021 BotanicFields, Inc.
// BF-025 RGB LED Clock 276 for M5Atom
// Demonstration: HUE-ring
//   shows the FastLED Rainbow hue chart of yellow enhanced
//   to check color correction, temperature 
 
#include "BF_DemoHueRing.h"

const int loop_ms = 20;          // 20ms
const int num_of_repeat = 1000;  // 20ms * 1000 = 20s

void DemoHueRing()
{
  Serial.println("[DemoHueRing]start");
  int repeat_remain = num_of_repeat;
  int last_ms = millis();

  while (repeat_remain > 0) {

    // hue rings 
    for (int i = 0; i < 60; ++i) {
      int hue = 256.0 * i / 60.0 + 0.5;
//      leds[i] = CHSV(hue, 255, 255);  // to check hue directly
      leds[i] = ColorFromPalette(palette_color, hue, 255);
      leds[ 60 + i] = leds[i];
      leds[120 + i] = leds[i];
    }

    // count down
    PutInt(repeat_remain * loop_ms / 1000);

    // check button
    M5.update();
    int button_check = CheckButton();
    if (button_check == 2000 || button_check == 1000) {  // exit or go next
      Serial.println("[DemoHueRing]break");
      repeat_remain = 1;
    }
    else if (button_check != 0) {
      Serial.println("[DemoHueRing]repeat extended");
      repeat_remain = num_of_repeat;
    }

    FastLED.show();

    delay(loop_ms - (millis() - last_ms));
    --repeat_remain;
    last_ms = millis();
  }

  Serial.println("[DemoHueRing]end");
}
