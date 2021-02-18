// Copyright 2021 BotanicFields, Inc.
// BF-025 RGB LED Clock 276 for M5Atom
// Demonstration: Digital & analog clock

#include "BF_DemoClock.h"
#include <WiFi.h>
#include <Ticker.h>

const int loop_ms      =   20;  // loop delay
const int ticker_ms    =  100;  // update interval of date, time
const int hhmm_stay_ms = 5000;  // duration of hour and minute display
const int crawl_ms     =  100;  // crawling speed of time, date

// test samples of flow string
const String s2x3x = " !\"#$%&'()*+,-./0123456789:;<=>?";
const String s4x5x = "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_";
const String s6x7x = "`abcdefghijklmnopqrstuvwxyz{|}~\x7f";
const String sample1 = "A QUICK FOX JUMPED OVER THE LAZY BROWN DOG.";
const String sample2 = "An old saying tells us that if you want something done well, you should do it yourself.";

// timer interrupt to update date and time
Ticker tk;
static bool ticker_invoked = false;

void TickerHandle()
{
  ticker_invoked = true;
}

// main of demo clock
void DemoClock()
{
  Serial.println("[DemoClock]start");
  tk.attach_ms(ticker_ms, TickerHandle);

  int demo_code     = 0;
  int crawl_length  = 0;
  int crawl_offset  = 0;

  bool complete = false;
  int last_ms = millis();

  while (!complete) {

    // update tv(time value)
    gettimeofday(&tv, NULL);
    int tv_msec = tv.tv_sec * 1000 + tv.tv_usec / 1000;

    // update td(time of day)
    if (ticker_invoked) {  // for every 100ms
      ticker_invoked = false;
      if (tv_msec % 1000 < ticker_ms) {  // every 0..99ms once in a second
        while (!getLocalTime(&td)) {
          Serial.print("[DemoClock]Waiting to obtain time ");
          delay(100);
        }
      // Serial.printf("[DemoClock]last_ms=%d, tv_msec=%d ", last_ms, tv_msec);
      // Serial.println(&td, "%A %B %d %Y %H:%M:%S");
      }
    }

    // background of circle clock
    //   HUE_AQUA, HUE_YELLOW are color names at the palette: RainbowsColor_p
    for (int i = 0; i < leds1_num_of_x; ++i) {
        leds[i] = ColorFromPalette(palette_color, tv_msec / 1000, 24);
        leds[i + leds1_num_of_x    ] = leds[i];
        leds[i + leds1_num_of_x * 2] = leds[i];
    }

    for (int i = 0; i < leds1_num_of_x; i += 5) {
      leds[i] = ColorFromPalette(palette_color, HUE_YELLOW, 64);
      leds[i + leds1_num_of_x    ] = leds[i];
      leds[i + leds1_num_of_x * 2] = leds[i];
    }

    // foreground of circle clock
    //   HUE_BLUE, HUE_GREEN, HUE_RED are color names at the palette: RainbowsColor_p
    int hsv_v = 255;
    for (int i = 0; i < 20; ++i) {
      leds[(td.tm_sec + 60 - i) % 60] = ColorFromPalette(palette_color, HUE_BLUE, hsv_v);
      hsv_v = hsv_v * 7 / 8;
    }
    hsv_v = 255;
    for (int i = 0; i < 15; ++i) {
      leds[(td.tm_min + 60 - i) % 60 + 60] = ColorFromPalette(palette_color, HUE_GREEN, hsv_v);
      hsv_v = hsv_v * 5 / 6;
    }
    hsv_v = 255;
    for (int i = 0; i < 10; ++i) { 
      leds[(td.tm_hour * 5 + td.tm_min / 12 + 60 - i) % 60 + 120] = ColorFromPalette(palette_color, HUE_RED, hsv_v);
      hsv_v = hsv_v * 3 / 4;
    }

    // background of digital clock
    for (int i = head_of_leds2; i < num_of_leds; ++i)
      leds[i] = ColorFromPalette(palette_color, tv_msec / 1000, 24);

    // foreground of digital clock
    switch (demo_code) {
      case 0: foreground_color = ColorFromPalette(palette_color, HUE_AQUA);  crawl_length = CrawlTimeDate(last_ms, crawl_offset);  break; 
      case 1: foreground_color = CRGB::DarkRed;     crawl_length = CrawlTimeDate(last_ms, crawl_offset);  break;
      case 2: foreground_color = CRGB::DarkGreen;   crawl_length = CrawlTimeDate(last_ms, crawl_offset);  break;
      case 3: foreground_color = CRGB::DarkBlue;    crawl_length = CrawlTimeDate(last_ms, crawl_offset);  break;
      case 4: foreground_color = CRGB::Crimson;     crawl_length = FlowString(crawl_offset, s2x3x);       break;
      case 5: foreground_color = CRGB::FireBrick;   crawl_length = FlowString(crawl_offset, s4x5x);       break;
      case 6: foreground_color = CRGB::DarkOrchid;  crawl_length = FlowString(crawl_offset, s6x7x);       break;
      case 7: foreground_color = CRGB::Coral;       crawl_length = FlowString(crawl_offset, sample1);     break;
      case 8: foreground_color = CRGB::Amethyst;    crawl_length = FlowString(crawl_offset, sample2);     break;
      case 9:                                       crawl_length = Invader(crawl_offset);                 break;
      default:
        demo_code = 0;
        break;
    }

    // crawl
    if (last_ms % crawl_ms < loop_ms) {  // crawl timing
      if(++crawl_offset > crawl_length + 10) 
        crawl_offset = 0;
    }

    // check button
    M5.update();
    int button_check = CheckButton();
    if (button_check == 2000) {  // exit
      Serial.println("[DemoClock]break");
      complete = true;
    }
    else if (button_check == 1000) {  // go next
      Serial.printf("[DemoClock]demo_code = %d\n", ++demo_code);
      crawl_offset = 0;
    }

    FastLED.show();

    delay(loop_ms - (millis() - last_ms));
    last_ms = millis();
  }
  tk.detach();
}

// crawl of digital clock
int CrawlTimeDate(int last_ms, int crawl_offset)
{
  static bool during_stay   = false;
  static int  stay_start_ms = 0;
  static int  stay_offset   = 0;
  
  if (crawl_offset == 0) {
    during_stay = true;
    stay_start_ms = last_ms;
  }
  if (during_stay & last_ms - stay_start_ms > hhmm_stay_ms) {
    during_stay = false;
    stay_offset = crawl_offset;
  }
  if (during_stay)
    return PutTimeDate(0);
  else
    return PutTimeDate(crawl_offset - stay_offset) + stay_offset;
}

// digital clock foreground
int PutTimeDate(int x_offset)
{
  int x = - x_offset;  // x position to put font, etc.

  // hour
  PutFont(x, td.tm_hour / 10);  x += 4;
  PutFont(x, td.tm_hour % 10);  x += 3;

  // colon slow
  if (tv.tv_sec % 2 == 1) {
    PutDotLeds2(x, 1);
    PutDotLeds2(x, 4);
  }
  x += 2;
  
  // minute
  PutFont(x, td.tm_min / 10);  x += 4;
  PutFont(x, td.tm_min % 10);  x += 3;

  // colon fast
  if (tv.tv_usec >= 500000) {  //  >= 0.5sec
    PutDotLeds2(x, 1);
    PutDotLeds2(x, 4);
  }
  x += 2;

  // second
  PutFont(x, td.tm_sec / 10);  x += 4;
  PutFont(x, td.tm_sec % 10);  x += 3;

  // dot
  PutDotLeds2(x, 5);  x += 2;

  // 100 milli-second
  PutFont(x, tv.tv_usec / 100000);  x += 8;

  // day of week
  const uint16_t pattern_wday[][6] = {
    { 0x6000, 0x94B8, 0x44A4, 0x24A4, 0x94A4, 0x63A5, },  //  Sun.
    { 0x8800, 0xD998, 0xAA54, 0x8A54, 0x8A54, 0x8995, },  //  Mon.
    { 0xF800, 0x2498, 0x24A4, 0x24A8, 0x24B0, 0x239D, },  //  Tue.
    { 0x8804, 0x898C, 0xAA54, 0xAA94, 0xAB14, 0x51CD, },  //  Wed.
    { 0xFA00, 0x2200, 0x2394, 0x2254, 0x2254, 0x224D, },  //  Thu.
    { 0x7808, 0x4240, 0x4298, 0x7308, 0x4208, 0x421D, },  //  Fri.
    { 0x6010, 0x933C, 0x4090, 0x2390, 0x9490, 0x634D, },  //  Sat.
  };
  for (int j = 0; j < leds2_num_of_y; ++j)
    for (int i = 0; i < leds2_num_of_x; ++i)
      if ((pattern_wday[td.tm_wday][j] & 0x8000 >> i) != 0)
        PutDotLeds2(x + i, j);
  x += 17;

  // year
  PutFont(x, (td.tm_year + 1900) / 1000      );  x += 4;
  PutFont(x, (td.tm_year + 1900) % 1000 / 100);  x += 4;
  PutFont(x, (td.tm_year + 1900) %  100 /  10);  x += 4;
  PutFont(x, (td.tm_year + 1900) %   10      );  x += 4;

  // slash
  PutDotLeds2(x, 4);  x += 1;
  PutDotLeds2(x, 3);  x += 1;
  PutDotLeds2(x, 2);  x += 1;
  PutDotLeds2(x, 1);  x += 2;

  // month
  PutFont(x, (td.tm_mon + 1) / 10);  x += 4;
  PutFont(x, (td.tm_mon + 1) % 10);  x += 4;

  // slash
  PutDotLeds2(x, 4);  x += 1;
  PutDotLeds2(x, 3);  x += 1;
  PutDotLeds2(x, 2);  x += 1;
  PutDotLeds2(x, 1);  x += 2;

  // day
  PutFont(x, td.tm_mday / 10);  x += 4;
  PutFont(x, td.tm_mday % 10);  x += 4;

  return x + x_offset;  // x position of time-date ends
}

// flow string
//  string:               A quick fox jumped over the lazy brown dog. 
// leds2: ::::::::::::::::
//        ^x_start - (leds2_num_of_x = 16)                           ^x_end = (string length) * (font_pixel = 6)
//                        <-x->::::::::::::::::
//                             ^during flow: (font_pixel = 6) * i - x
int FlowString(int x, const String s)
{  
  PutString(leds2_num_of_x - x, s);
  return s.length() * font_pixel_x + leds2_num_of_x;
}

// invader           form 0    0    1    1
//                        L    R    L    R       
//   kind = 0:Crab       0x10 0x11 0x12 0x13
//          1:Octopus    0x14 0x15 0x16 0x17
//          2:Squid      0x18 0x19 0x1A 0x1B
//          3:UFO        0x1C 0x1D 0x1E 0x1F
int Invader(int x)
{
  int x_pos = x / 2;
  if      (x_pos <  32) { foreground_color = CRGB::ForestGreen;  InvaderSub(-16 + x_pos % 32, 0); }
  else if (x_pos <  64) { foreground_color = CRGB::LimeGreen;    InvaderSub( 16 - x_pos % 32, 0); }
  else if (x_pos <  96) { foreground_color = CRGB::DarkCyan;     InvaderSub(-16 + x_pos % 32, 1); }
  else if (x_pos < 128) { foreground_color = CRGB::Cyan;         InvaderSub( 16 - x_pos % 32, 1); }
  else if (x_pos < 160) { foreground_color = CRGB::Olive;        InvaderSub(-16 + x_pos % 32, 2); }
  else if (x_pos < 192) { foreground_color = CRGB::Yellow;       InvaderSub( 16 - x_pos % 32, 2); }
  else if (x_pos < 224) { foreground_color = CRGB::DarkMagenta;  InvaderSub(-16 + x_pos % 32, 3); }
  else if (x_pos < 256) { foreground_color = CRGB::Magenta;      InvaderSub( 16 - x_pos % 32, 3); }
  return 512;
}

void InvaderSub(int x, int kind)
{
   int form = (x + leds2_num_of_x) % 2;
   PutFont(x               , 0x10 + kind * 4 + form * 2    );  // L
   PutFont(x + font_pixel_x, 0x10 + kind * 4 + form * 2 + 1);  // R
}
