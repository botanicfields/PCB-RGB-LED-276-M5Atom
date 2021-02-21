// Copyright 2021 BotanicFields, Inc.
// BF-025 RGB LED Clock 276 for M5Atom
// driver using FastLED 

#include "BF_RGB_LED_276.h"

// parameters of FastLED
const int brightness_bf025  = 64;        // original for BF-025(WS2812C-2020)
const CRGB correction_bf025 = 0xB080FF;  // original for BF-025(WS2812C-2020)

// demonstration control
CRGB foreground_color       = CRGB::SlateGray;
CRGB background_color       = CRGB::Black;
CRGBPalette16 palette_color = RainbowColors_p;
int scale_factor            = 1;
int period_factor           = 1;

// control by a button
int correction_select  = 0;
int temperature_select = 0;
int palette_select     = 0;
int scale_select       = 0;
int period_select      = 0;

// set color correction
//   omitted:
//     TypicalLEDStrip    = TypicalSMD5050
//     TypicalPixelString = Typical8mmPixel
void SelectCorrection(int &correction_select)
{
  switch (correction_select) {
    case  1: FastLED.setCorrection(TypicalSMD5050);    Serial.println("[RGB276]Correction: (1)TypicalSMD5050");    break;
    case  2: FastLED.setCorrection(Typical8mmPixel);   Serial.println("[RGB276]Correction: (2)Typical8mmPixel");   break;
    case  3: FastLED.setCorrection(UncorrectedColor);  Serial.println("[RGB276]Correction: (3)UncorrectedColor");  break;
    default: FastLED.setCorrection(correction_bf025);  Serial.println("[RGB276]Correction: (0)correction_bf025");
      correction_select = 0;
      break;
  }
}

// set color temperature
void SelectTemperature(int &temperature_select)
{
  switch (temperature_select) {
    case  1: FastLED.setTemperature(Candle);                   Serial.println("[RGB276]Temperature: ( 1)Candle");                   break;
    case  2: FastLED.setTemperature(Tungsten40W);              Serial.println("[RGB276]Temperature: ( 2)Tungsten40W");              break;
    case  3: FastLED.setTemperature(Tungsten100W);             Serial.println("[RGB276]Temperature: ( 3)Tungsten100W");             break;
    case  4: FastLED.setTemperature(Halogen);                  Serial.println("[RGB276]Temperature: ( 4)Halogen");                  break;
    case  5: FastLED.setTemperature(CarbonArc);                Serial.println("[RGB276]Temperature: ( 5)CarbonArc");                break;
    case  6: FastLED.setTemperature(HighNoonSun);              Serial.println("[RGB276]Temperature: ( 6)HighNoonSun");              break;
    case  7: FastLED.setTemperature(DirectSunlight);           Serial.println("[RGB276]Temperature: ( 7)DirectSunlight");           break;
    case  8: FastLED.setTemperature(OvercastSky);              Serial.println("[RGB276]Temperature: ( 8)OvercastSky");              break;
    case  9: FastLED.setTemperature(ClearBlueSky);             Serial.println("[RGB276]Temperature: ( 9)ClearBlueSky");             break;
    case 10: FastLED.setTemperature(WarmFluorescent);          Serial.println("[RGB276]Temperature: (10)WarmFluorescent");          break;
    case 11: FastLED.setTemperature(StandardFluorescent);      Serial.println("[RGB276]Temperature: (11)StandardFluorescent");      break;
    case 12: FastLED.setTemperature(CoolWhiteFluorescent);     Serial.println("[RGB276]Temperature: (12)CoolWhiteFluorescent");     break;
    case 13: FastLED.setTemperature(FullSpectrumFluorescent);  Serial.println("[RGB276]Temperature: (13)FullSpectrumFluorescent");  break;
    case 14: FastLED.setTemperature(GrowLightFluorescent);     Serial.println("[RGB276]Temperature: (14)GrowLightFluorescent");     break;
    case 15: FastLED.setTemperature(BlackLightFluorescent);    Serial.println("[RGB276]Temperature: (15)BlackLightFluorescent");    break;
    case 16: FastLED.setTemperature(MercuryVapor);             Serial.println("[RGB276]Temperature: (16)MercuryVapor");             break;
    case 17: FastLED.setTemperature(SodiumVapor);              Serial.println("[RGB276]Temperature: (17)SodiumVapor");              break;
    case 18: FastLED.setTemperature(MetalHalide);              Serial.println("[RGB276]Temperature: (18)MetalHalide");              break;
    case 19: FastLED.setTemperature(HighPressureSodium);       Serial.println("[RGB276]Temperature: (19)HighPressureSodium");       break;
    default: FastLED.setTemperature(UncorrectedTemperature);   Serial.println("[RGB276]Temperature: ( 0)UncorrectedTemperature");
      temperature_select = 0;
      break;
  }
}

// set color palette
//   omitted:
//     RainbowStripesColors_p = RainbowStripeColors_p
void SelectPalette(int &palette_select)
{
  switch (palette_select) {
    case  1: palette_color = CloudColors_p;          Serial.println("[RGB276]palette: (1)CloudColors_p");          break;
    case  2: palette_color = LavaColors_p;           Serial.println("[RGB276]palette: (2)LavaColors_p");           break;
    case  3: palette_color = OceanColors_p;          Serial.println("[RGB276]palette: (3)OceanColors_p");          break;
    case  4: palette_color = ForestColors_p;         Serial.println("[RGB276]palette: (4)ForestColors_p");         break;
    case  5: palette_color = RainbowStripeColors_p;  Serial.println("[RGB276]palette: (5)RainbowStripeColors_p");  break;
    case  6: palette_color = PartyColors_p;          Serial.println("[RGB276]palette: (6)PartyColors_p");          break;
    case  7: palette_color = HeatColors_p;           Serial.println("[RGB276]palette: (7)HeatColors_p");           break;
    default: palette_color = RainbowColors_p;        Serial.println("[RGB276]palette: (0)RainbowColors_p");
      palette_select = 0;
      break;
  }
}

// set scale factor for noise
void SelectScale(int &scale_select)
{
  switch (scale_select) {
    case  1: scale_factor =  2;  break;
    case  2: scale_factor =  5;  break;
    case  3: scale_factor = -2;  break;
    case  4: scale_factor = -5;  break;
    default: scale_factor =  1;
      scale_select = 0;
      break;
  }
  Serial.printf("[RGB276]scale: (%d) %d\n", scale_select, scale_factor);
}

// set period factor for noise
void SelectPeriod(int &period_select)
{
  switch (period_select) {
    case  1: period_factor =   2;  break;
    case  2: period_factor =  10;  break;
    case  3: period_factor =  -2;  break;
    case  4: period_factor = -10;  break;
    default: period_factor =   1;
      period_select = 0;
      break;
  }
  Serial.printf("[RGB276]period: (%d) %d\n", period_select, period_factor);
}

// reset to default
void ResetParameters()
{
  FastLED.setBrightness(brightness_bf025);
//  FastLED.setDither(DISABLE_DITHER);  // uncomment to prevent flicker
  foreground_color = CRGB::SlateGray;
  background_color = CRGB::Black;
  correction_select = 0;
  SelectCorrection(correction_select);
  temperature_select = 0;
  SelectTemperature(temperature_select);
  period_select = 0;
  SelectPeriod(period_select);
  scale_select = 0;
  SelectScale(scale_select);
  palette_select = 0;
  SelectPalette(palette_select);
}

// connection of RGB LEDs
//  M5Atom --> leds1[60][3] --> leds2[16][6]

// circle: leds1[0..60][0..2] --> leds[0..179]
//      0   1   2  ..  58  59
//     ..  ..  ..  ..  ..  ..
// 0:   0   1   2  ..  58  59
// 1:  60  61  62  .. 118 119
// 2: 120 121 122  .. 178 179
const int leds1_num_of_x = 60;
const int leds1_num_of_y =  3;

// rectangle: leds2[0..15][0..5] --> leds[180..275]
//      0   1   2  ..  14  15
//     ..  ..  ..  ..  ..  ..
// 0: 180 191 192  .. 264 275
// 1: 181 190 193  .. 265 274
// ..  ..  ..  ..  ..  ..  ..
// 4: 184 187 196  .. 268 271
// 5: 185 186 197  .. 269 270
const int leds2_num_of_x = 16;
const int leds2_num_of_y =  6;
const int head_of_leds2 = leds1_num_of_x * leds1_num_of_y;

// for fastLED
const int pin_to_leds = 22;  // assigned to GPIO22
const int num_of_leds = leds1_num_of_x * leds1_num_of_y + leds2_num_of_x * leds2_num_of_y; 
CRGB leds[num_of_leds];

// font for leds2 
//   0x00-0x0f: 4*6 font(actually 3*6)
//     0x00..0x0F: 0..9, A..F
//   0x10-0x7F: 6*6 font(actually 5*6)
//     0x10..0X1F: invaders
//     0x20..0x7F: ASCII characters
const int font_pixel_x = 6;
const int font_pixel_y = 6;
const uint8_t font[][font_pixel_y] = {
  { 0x60, 0xA0, 0xA0, 0xA0, 0xA0, 0xC0, },  // 0x00 0
  { 0x40, 0xC0, 0x40, 0x40, 0x40, 0x40, },  // 0x01 1
  { 0xC0, 0x20, 0x20, 0x40, 0x80, 0xE0, },  // 0x02 2
  { 0xC0, 0x20, 0x40, 0x20, 0x20, 0xC0, },  // 0x03 3
  { 0x20, 0xA0, 0xA0, 0xE0, 0x20, 0x20, },  // 0x04 4
  { 0xE0, 0x80, 0xC0, 0x20, 0x20, 0xC0, },  // 0x05 5
  { 0x60, 0x80, 0xC0, 0xA0, 0xA0, 0x40, },  // 0x06 6
  { 0xE0, 0x20, 0x20, 0x40, 0x80, 0x80, },  // 0x07 7
  { 0x60, 0xA0, 0x40, 0xA0, 0xA0, 0xC0, },  // 0x08 8
  { 0x40, 0xA0, 0xA0, 0x60, 0x20, 0xC0, },  // 0x09 9
  { 0x40, 0xA0, 0xA0, 0xE0, 0xA0, 0xA0, },  // 0x0A A
  { 0xC0, 0xA0, 0xC0, 0xA0, 0xA0, 0xC0, },  // 0x0B B
  { 0x60, 0x80, 0x80, 0x80, 0x80, 0x60, },  // 0x0C C
  { 0xC0, 0xA0, 0xA0, 0xA0, 0xA0, 0xC0, },  // 0x0D D
  { 0xE0, 0x80, 0xE0, 0x80, 0x80, 0xE0, },  // 0x0E E
  { 0xE0, 0x80, 0xE0, 0x80, 0x80, 0x80, },  // 0x0F F
  { 0x60, 0x3C, 0x6C, 0xFC, 0x90, 0x18, },  // 0x10 Crab1L
  { 0x30, 0xE0, 0xB0, 0xF8, 0x48, 0xC0, },  // 0x11 Crab1R
  { 0x20, 0xBC, 0xEC, 0x7C, 0x10, 0x30, },  // 0x12 Crab2L
  { 0x20, 0xE8, 0xB8, 0xF0, 0x40, 0x60, },  // 0x13 Crab2R
  { 0x3C, 0x7C, 0x6C, 0x7C, 0x24, 0xC8, },  // 0x14 Octopus1L
  { 0xE0, 0xF0, 0xB0, 0xF0, 0x20, 0x98, },  // 0x15 Octopus1R
  { 0x3C, 0x7C, 0x6C, 0x7C, 0x24, 0x14, },  // 0x16 Octopus2L
  { 0xE0, 0xF0, 0xB0, 0xF0, 0x20, 0x40, },  // 0x17 Octopus2R
  { 0x04, 0x1C, 0x74, 0xFC, 0x24, 0x10, },  // 0x18 Squid1L
  { 0x00, 0xC0, 0x70, 0xF8, 0x20, 0x40, },  // 0x19 Squid1R
  { 0x04, 0x1C, 0x74, 0xFC, 0x24, 0xC0, },  // 0x1A Squid2L
  { 0x00, 0xC0, 0x70, 0xF8, 0x20, 0x18, },  // 0x1B Squid2R
  { 0x1C, 0x7C, 0xCC, 0xFC, 0x38, 0x00, },  // 0x1C UFO1L
  { 0xE0, 0xF8, 0x3C, 0xFC, 0x70, 0x00, },  // 0x1D UFO1R
  { 0x1C, 0x7C, 0xF0, 0xFC, 0x38, 0x00, },  // 0x1E UFO2L
  { 0xE0, 0xF8, 0xCC, 0xFC, 0x70, 0x00, },  // 0x1F UFO2R
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, },  // 0x20 space
  { 0x20, 0x20, 0x20, 0x00, 0x20, 0x00, },  // 0x21 !
  { 0x50, 0x50, 0x00, 0x00, 0x00, 0x00, },  // 0x22 "
  { 0x50, 0xF8, 0x50, 0xF8, 0x50, 0x00, },  // 0x23 #
  { 0x78, 0xA0, 0x70, 0x28, 0xF0, 0x00, },  // 0x24 $
  { 0xC8, 0xD0, 0x20, 0x58, 0x98, 0x00, },  // 0x25 %
  { 0x40, 0xA0, 0x48, 0x90, 0x68, 0x00, },  // 0x26 &
  { 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, },  // 0x27 '
  { 0x10, 0x20, 0x20, 0x20, 0x10, 0x00, },  // 0x28 (
  { 0x40, 0x20, 0x20, 0x20, 0x40, 0x00, },  // 0x29 )
  { 0xA8, 0x70, 0x20, 0x70, 0xA8, 0x00, },  // 0x2A *
  { 0x20, 0x20, 0xF8, 0x20, 0x20, 0x00, },  // 0x2B +
  { 0x00, 0x00, 0x00, 0x00, 0x40, 0x80, },  // 0x2C ,
  { 0x00, 0x00, 0xF8, 0x00, 0x00, 0x00, },  // 0x2D -
  { 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, },  // 0x2E .
  { 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, },  // 0x2F /
  { 0x70, 0x98, 0xA8, 0xC8, 0x70, 0x00, },  // 0x30 0
  { 0x20, 0x60, 0x20, 0x20, 0x70, 0x00, },  // 0x31 1
  { 0xF0, 0x08, 0x70, 0x80, 0xF8, 0x00, },  // 0x32 2
  { 0xF0, 0x08, 0x70, 0x08, 0xF0, 0x00, },  // 0x33 3
  { 0x30, 0x50, 0x90, 0xF8, 0x10, 0x00, },  // 0x34 4
  { 0xF8, 0x80, 0xF0, 0x08, 0xF0, 0x00, },  // 0x35 5
  { 0x70, 0x80, 0xF0, 0x88, 0x70, 0x00, },  // 0x36 6
  { 0xF8, 0x08, 0x10, 0x20, 0x20, 0x00, },  // 0x37 7
  { 0x70, 0x88, 0x70, 0x88, 0x70, 0x00, },  // 0x38 8
  { 0x70, 0x88, 0x78, 0x08, 0x70, 0x00, },  // 0x39 9
  { 0x00, 0x20, 0x00, 0x20, 0x00, 0x00, },  // 0x3A :
  { 0x00, 0x20, 0x00, 0x20, 0x40, 0x00, },  // 0x3B ;
  { 0x10, 0x20, 0x40, 0x20, 0x10, 0x00, },  // 0x3C <
  { 0x00, 0xF8, 0x00, 0xF8, 0x00, 0x00, },  // 0x3D =
  { 0x40, 0x20, 0x10, 0x20, 0x40, 0x00, },  // 0x3E >
  { 0x70, 0x88, 0x30, 0x00, 0x20, 0x00, },  // 0x3F ?
  { 0x70, 0x88, 0xB8, 0xA8, 0xB8, 0x00, },  // 0x40 @
  { 0x20, 0x50, 0x88, 0xF8, 0x88, 0x00, },  // 0x41 A
  { 0xF0, 0x48, 0x70, 0x48, 0xF0, 0x00, },  // 0x42 B
  { 0x78, 0x80, 0x80, 0x80, 0x78, 0x00, },  // 0x43 C
  { 0xF0, 0x48, 0x48, 0x48, 0xF0, 0x00, },  // 0x44 D
  { 0xF8, 0x80, 0xF0, 0x80, 0xF8, 0x00, },  // 0x45 E
  { 0xF8, 0x80, 0xF0, 0x80, 0x80, 0x00, },  // 0x46 F
  { 0x78, 0x80, 0xB8, 0x88, 0x78, 0x00, },  // 0x47 G
  { 0x88, 0x88, 0xF8, 0x88, 0x88, 0x00, },  // 0x48 H
  { 0x70, 0x20, 0x20, 0x20, 0x70, 0x00, },  // 0x49 I
  { 0x38, 0x10, 0x10, 0x10, 0xE0, 0x00, },  // 0x4A J
  { 0x88, 0x90, 0xE0, 0x90, 0x88, 0x00, },  // 0x4B K
  { 0x80, 0x80, 0x80, 0x80, 0xF8, 0x00, },  // 0x4C L
  { 0x88, 0xD8, 0xA8, 0x88, 0x88, 0x00, },  // 0x4D M
  { 0x88, 0xC8, 0xA8, 0x98, 0x88, 0x00, },  // 0x4E N
  { 0xF0, 0x88, 0x88, 0x88, 0x78, 0x00, },  // 0x4F O
  { 0xF0, 0x88, 0xF0, 0x80, 0x80, 0x00, },  // 0x50 P
  { 0x70, 0x88, 0x88, 0xA8, 0x70, 0x08, },  // 0x51 Q
  { 0xF0, 0x88, 0xF0, 0xA0, 0x98, 0x00, },  // 0x52 R
  { 0x78, 0x80, 0x70, 0x08, 0xF0, 0x00, },  // 0x53 S
  { 0xF8, 0x20, 0x20, 0x20, 0x20, 0x00, },  // 0x54 T
  { 0x88, 0x88, 0x88, 0x88, 0x70, 0x00, },  // 0x55 U
  { 0x88, 0x88, 0x88, 0x50, 0x20, 0x00, },  // 0x56 V
  { 0x88, 0xA8, 0xA8, 0xA8, 0x50, 0x00, },  // 0x57 W
  { 0x88, 0x50, 0x20, 0x50, 0x88, 0x00, },  // 0x58 X
  { 0x88, 0x50, 0x20, 0x20, 0x20, 0x00, },  // 0x59 Y
  { 0xF8, 0x10, 0x20, 0x40, 0xF8, 0x00, },  // 0x5A Z
  { 0x30, 0x20, 0x20, 0x20, 0x30, 0x00, },  // 0x5B [
  { 0x88, 0x50, 0x20, 0xF8, 0x20, 0x00, },  // 0x5C yen
  { 0x60, 0x20, 0x20, 0x20, 0x60, 0x00, },  // 0x5D ]
  { 0x20, 0x50, 0x00, 0x00, 0x00, 0x00, },  // 0x5E ^
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, },  // 0x5F _
  { 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, },  // 0x60 `
  { 0x00, 0x70, 0x90, 0x90, 0x68, 0x00, },  // 0x61 a
  { 0x80, 0xF0, 0x88, 0x88, 0xF0, 0x00, },  // 0x62 b
  { 0x00, 0x78, 0x80, 0x80, 0x78, 0x00, },  // 0x63 c
  { 0x08, 0x78, 0x88, 0x88, 0x78, 0x00, },  // 0x64 d
  { 0x00, 0x60, 0x90, 0xA0, 0x78, 0x00, },  // 0x65 e
  { 0x38, 0x40, 0xF0, 0x40, 0x40, 0x00, },  // 0x66 f
  { 0x00, 0x78, 0x88, 0x78, 0x08, 0xF0, },  // 0x67 g
  { 0x80, 0xF0, 0x88, 0x88, 0x88, 0x00, },  // 0x68 h
  { 0x20, 0x00, 0x60, 0x20, 0x20, 0x00, },  // 0x69 i
  { 0x10, 0x00, 0x30, 0x10, 0x10, 0xE0, },  // 0x6A j
  { 0x80, 0x88, 0x90, 0xE0, 0x98, 0x00, },  // 0x6B k
  { 0x60, 0x20, 0x20, 0x20, 0x20, 0x00, },  // 0x6C l
  { 0x00, 0xF0, 0xA8, 0xA8, 0xA8, 0x00, },  // 0x6D m
  { 0x00, 0xF0, 0x88, 0x88, 0x88, 0x00, },  // 0x6E n
  { 0x00, 0xF0, 0x88, 0x88, 0x78, 0x00, },  // 0x6F o
  { 0x00, 0xF0, 0x88, 0x88, 0xF0, 0x80, },  // 0x70 p
  { 0x00, 0x78, 0x88, 0x88, 0x78, 0x08, },  // 0x71 q
  { 0x00, 0x98, 0xA0, 0xC0, 0x80, 0x00, },  // 0x72 r
  { 0x00, 0x38, 0x20, 0x10, 0xF0, 0x00, },  // 0x73 s
  { 0x40, 0xF8, 0x40, 0x40, 0x38, 0x00, },  // 0x74 t
  { 0x00, 0x88, 0x88, 0x88, 0x78, 0x00, },  // 0x75 u
  { 0x00, 0x88, 0x88, 0x50, 0x20, 0x00, },  // 0x76 v
  { 0x00, 0xA8, 0xA8, 0xA8, 0x78, 0x00, },  // 0x77 w
  { 0x00, 0xD8, 0x20, 0x20, 0xD8, 0x00, },  // 0x78 x
  { 0x00, 0x88, 0x88, 0x78, 0x08, 0xF0, },  // 0x79 y
  { 0x00, 0xF0, 0x20, 0x40, 0xF8, 0x00, },  // 0x7A z
  { 0x30, 0x20, 0x60, 0x20, 0x30, 0x00, },  // 0x7B {
  { 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, },  // 0x7C |
  { 0x60, 0x20, 0x30, 0x20, 0x60, 0x00, },  // 0x7D }
  { 0x68, 0x90, 0x00, 0x00, 0x00, 0x00, },  // 0x7E ~
  { 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, },  // 0x7F DEL
};

// pattern for leds2
const uint16_t pattern_null[] = { 0x881B, 0xCA49, 0xAA49, 0x9A49, 0x8A49, 0x89C9, };  //  Null
const uint16_t pattern_exit[] = { 0xE012, 0x8887, 0xE532, 0x8212, 0x8512, 0xE891, };  //  Exit
const uint16_t pattern_next[] = { 0x9002, 0xD257, 0xB552, 0x9722, 0x9452, 0x9351, };  //  Next
const uint16_t pattern_corr[] = { 0x6000, 0x8655, 0x8966, 0x8944, 0x8944, 0x6644, };  //  Corr
const uint16_t pattern_temp[] = { 0xE000, 0x49A6, 0x5555, 0x5D55, 0x5156, 0x4D54, };  //  Temp
const uint16_t pattern_pale[] = { 0xE060, 0x9626, 0x9129, 0xE72F, 0x8928, 0x86A7, };  //  Pale
const uint16_t pattern_scal[] = { 0x6003, 0x9331, 0x4409, 0x2439, 0x9449, 0x6335, };  //  Scal
const uint16_t pattern_peri[] = { 0xE001, 0x9328, 0x94B3, 0xE7A1, 0x8421, 0x83A1, };  //  Peri
const uint16_t pattern_btn[]  = { 0xE200, 0x9760, 0xE250, 0x9250, 0x9250, 0xE150, };  //  Btn
const uint16_t pattern_wifi[] = { 0x8AD0, 0x8880, 0xAA90, 0xAAD0, 0xAA90, 0x5295, };  //  Wifi..
const uint16_t pattern_ntp[]  = { 0x8BB0, 0xC928, 0xA928, 0x9930, 0x8920, 0x8925, };  //  NTP..

// initialize FastLED
void InitFastLed()
{
  FastLED.addLeds<WS2812, pin_to_leds, GRB>(leds, num_of_leds);
  ResetParameters();
}

// lamp test
void LampTest()
{
  fill_solid(leds, num_of_leds, CRGB::Red);    FastLED.show();  delay(1000);
  fill_solid(leds, num_of_leds, CRGB::Green);  FastLED.show();  delay(1000);
  fill_solid(leds, num_of_leds, CRGB::Blue);   FastLED.show();  delay(1000);
  fill_solid(leds, num_of_leds, CRGB::Olive);  FastLED.show();  delay( 100);
}

// clear rectangle
void ClearLeds2()
{
  for (int i = head_of_leds2; i < num_of_leds; ++i)
    leds[i] = background_color;
}

// put a dot on leds1[x][y]
void PutDotLeds1(int x, int y)
{
  if (x >= 0 && x < leds1_num_of_x && y >= 0 && y < leds1_num_of_y)
    leds[x + leds1_num_of_x * y] = foreground_color;
}

// put a dot on leds2[x][y]
void PutDotLeds2(int x, int y)
{
  if (x >= 0 && x < leds2_num_of_x && y >= 0 && y < leds2_num_of_y)
    if (x % 2 == 0)
      leds[head_of_leds2 + leds2_num_of_y * x + y] = foreground_color;
    else
      leds[head_of_leds2 + leds2_num_of_y * x + leds2_num_of_y - 1 - y] = foreground_color;
}

// put a font on leds2
void PutFont(int x, char c)
{
  for (int j = 0; j < font_pixel_y; ++j)
    for (int i = 0; i < font_pixel_x; ++i)
      if ((font[c][j] & 0x80 >> i) != 0)
        PutDotLeds2(x + i, j);
}

// put a string on leds2
void PutString(int x, const String s)
{
  for (int i = 0; i < s.length(); ++i)
    PutFont(x + font_pixel_x * i, s[i]);
}

// put 4 digits on leds2
void PutInt(int n)
{
  ClearLeds2();
  PutFont( 1, n / 1000 % 10);
  PutFont( 5, n /  100 % 10);
  PutFont( 9, n /   10 % 10);
  PutFont(13, n        % 10);
}

// put pattern on leds2
void PutPattern(const uint16_t pattern[])
{
  ClearLeds2();
  for (int j = 0; j < leds2_num_of_y; ++j)
    for (int i = 0; i < leds2_num_of_x; ++i)
      if ((pattern[j] & 0x8000 >> i) != 0)
        PutDotLeds2(i, j);
}

// put "Btn" + a digit on leds2
void PutButton(char c)
{
  PutPattern(pattern_btn);
  PutFont(13, c);
}

// show setup status
void ShowPattern(const uint16_t pattern[], int delay_ms)
{
  PutPattern(pattern);
  FastLED.show();
  delay(delay_ms);
}

// button on the M5Atom
int CheckButton()
{
  if      (M5.Btn.pressedFor(7000)) PutPattern(pattern_null);  // cancel and nullify 
  else if (M5.Btn.pressedFor(6000)) PutPattern(pattern_peri);  // change period
  else if (M5.Btn.pressedFor(5000)) PutPattern(pattern_scal);  // change scale
  else if (M5.Btn.pressedFor(4000)) PutPattern(pattern_corr);  // change correction
  else if (M5.Btn.pressedFor(3000)) PutPattern(pattern_temp);  // change temperature
  else if (M5.Btn.pressedFor(2000)) PutPattern(pattern_exit);  // exit
  else if (M5.Btn.pressedFor(1000)) PutPattern(pattern_next);  // go next
  else if (M5.Btn.isPressed()     ) PutPattern(pattern_pale);  // change palette

  if      (M5.Btn.wasReleasefor(7000)) {
    Serial.println("[RGB276]button >7s: cancel button, nullify");
    return 7000;
  }
  else if (M5.Btn.wasReleasefor(6000)) {
    Serial.println("[RGB276]button >6s: change period");
    SelectPeriod(++period_select);
    return 6000;
  }
  else if (M5.Btn.wasReleasefor(5000)) {
    Serial.println("[RGB276]button >5s: change scale");
    SelectScale(++scale_select);
    return 5000;
  }
  else if (M5.Btn.wasReleasefor(4000)) {
    Serial.println("[RGB276]button >4s: change correction");
    SelectCorrection(++correction_select);
    return 4000;
  }
  else if (M5.Btn.wasReleasefor(3000)) {
    Serial.println("[RGB276]button >3s: change temperature");
    SelectTemperature(++temperature_select);
    return 3000;
  }
  else if (M5.Btn.wasReleasefor(2000)) {
    Serial.println("[RGB276]button >2s: exit");
    return 2000;
  }
  if      (M5.Btn.wasReleasefor(1000)) {
    Serial.println("[RGB276]button >1s: go next");
    return 1000;
  }
  else if (M5.Btn.wasReleased()) {
    Serial.println("[RGB276]button: change palette");
    SelectPalette(++palette_select);
    return -1;
  }
  return 0;
}
