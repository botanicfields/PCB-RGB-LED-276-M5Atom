// Copyright 2021 BotanicFields, Inc.
// BF-025 RGB LED Clock 276 for M5Atom
// driver using FastLED

#pragma once

extern const int brightness_default;
extern const CRGB correction_default;

extern CRGB foreground_color;
extern CRGB background_color;
extern CRGBPalette16 palette_color;
extern int scale_factor;
extern int period_factor;

extern int correction_select;
extern int temperature_select;
extern int palette_select;
extern int scale_select;
extern int period_select;

void SelectTemperature(int &temperature_select);
void SelectPalette(int &palette_select);
void SelectScale(int &scale_select);
void SelectPeriod(int &period_select);
void ResetParameters();

extern const int leds1_num_of_x;
extern const int leds1_num_of_y;

extern const int leds2_num_of_x;
extern const int leds2_num_of_y;
extern const int head_of_leds2;

extern const int pin_to_leds;
extern const int num_of_leds;
extern CRGB leds[];

extern const int font_pixel_x;
extern const int font_pixel_y;

extern const uint16_t pattern_null[];
extern const uint16_t pattern_exit[];
extern const uint16_t pattern_next[];
extern const uint16_t pattern_corr[];
extern const uint16_t pattern_temp[];
extern const uint16_t pattern_pale[];
extern const uint16_t pattern_scal[];
extern const uint16_t pattern_peri[];
extern const uint16_t pattern_btn[];
extern const uint16_t pattern_rtc[];
extern const uint16_t pattern_wifi[];
extern const uint16_t pattern_ntp[];
extern const uint16_t pattern_time[];
extern const uint16_t pattern_stop[];
extern const uint16_t pattern_yen[];

void InitFastLed();
void LampTest();
void ClearLeds1();
void ClearLeds2();
void PutDotLeds1(int x, int y);
void PutDotLeds2(int x, int y);
void PutFont(int x, char c);
void PutString(int x, const String s);
void PutInt(int n);
void PutPattern(const uint16_t pattern[]);
void PutButton(char c);
void ShowPattern(const uint16_t pattern[], int delay_ms = 1000);

int CheckButton();
