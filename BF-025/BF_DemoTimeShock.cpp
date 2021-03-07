// Copyright 2021 BotanicFields, Inc.
// BF-025 RGB LED Clock 276 for M5Atom
// Demonstration: A tribute to "Quiz Time Shock" a famous TV show in Japan

#include "BF_DemoTimeShock.h"

const int loop_ms = 20;  // 20ms

int timer_select = 3;  // 180sec .. see SelectTimer()
int timer_ms     = 0;  // initialized by SelectTimer()

void DemoTimeShock()
{
  Serial.println("[DemoTimeShock]start");

  bool count_down = true;
  bool mode_quiz  = false;
  bool correct_answer[12] = { false, false, false, false, false, false, 
                              false, false, false, false, false, false, };
  SelectTimer(timer_select);
  int remain_ms = timer_ms;
  int last_ms = millis();

  while (remain_ms > 0) {

    // background of pie-chart
    foreground_color = ColorFromPalette(palette_color, HUE_RED, 16);
    for (int i = 0; i < 60; ++i)
      PutDotLeds1(i, 0);
    foreground_color = ColorFromPalette(palette_color, HUE_RED, 64);
    for (int i = 0; i < 60; i += 5)
      PutDotLeds1(i, 0);
    foreground_color = ColorFromPalette(palette_color, HUE_AQUA, 255);
    for (int i = 0; i < 60; ++i) {
      PutDotLeds1(i, 1);
      PutDotLeds1(i, 2);
    }

    // pie-chart
    foreground_color = ColorFromPalette(palette_color, HUE_AQUA, 16);
    for (int i = 1; i < 60 - remain_ms / 1000 % 60; ++i) {
        PutDotLeds1(i, 1);
        PutDotLeds1(i, 2);
    }
    //correct answer automatic
    if (!mode_quiz) {
      foreground_color = ColorFromPalette(palette_color, HUE_RED, 255);
      if ((remain_ms + 3000) / 1000 % 60 > 3)  
        for (int i = 0; i < 12 - (remain_ms + 3000) / 5000 % 12; ++i) {
          PutDotLeds1(i * 5 + 1, 0);
          PutDotLeds1(i * 5 + 2, 0);
          PutDotLeds1(i * 5 + 3, 0);
          PutDotLeds1(i * 5 + 4, 0);
        }
    }
        
    // time_remaining
    background_color = ColorFromPalette(palette_color, HUE_BLUE, 16);
    ClearLeds2();
    foreground_color = ColorFromPalette(palette_color, HUE_AQUA, 128);
    PutFont( 0, remain_ms / 60000 % 10);
    PutDotLeds2(4, 0);  PutDotLeds2(4, 1);
    PutFont( 6, remain_ms / 10000 %  6);
    PutFont(10, remain_ms /  1000 % 10);
    PutDotLeds2(14, 0);  PutDotLeds2(14, 1);
    PutDotLeds2(15, 0);  PutDotLeds2(15, 1);

    // correct answer
    if (mode_quiz) {
      foreground_color = ColorFromPalette(palette_color, HUE_RED, 255);
      for (int i = 0; i < 12; ++i)
        if (correct_answer[i]) {
          PutDotLeds1(i * 5 + 1, 0);
          PutDotLeds1(i * 5 + 2, 0);
          PutDotLeds1(i * 5 + 3, 0);
          PutDotLeds1(i * 5 + 4, 0);
        }
      
      // prize money
      int score = 0;
      for (int i = 0; i < 12; ++i)
        if (correct_answer[i])
          ++score;
      background_color = ColorFromPalette(palette_color, HUE_RED, 16);
      foreground_color = ColorFromPalette(palette_color, HUE_AQUA, 128);
      PutPattern(pattern_yen);
      switch (score) {
      case  1: PutFont(12, 1);               break;  //     1,000 Yen  
      case  2: PutFont(12, 2);               break;  //     2,000 Yen
      case  3: PutFont(12, 3);               break;  //     3,000 Yen
      case  4: PutFont(12, 4);               break;  //     4,000 Yen
      case  5: PutFont(12, 5);               break;  //     5,000 Yen
      case  6: PutFont( 8, 1);  PutZero(1);  break;  //    10,000 Yen
      case  7: PutFont( 8, 2);  PutZero(1);  break;  //    20,000 Yen
      case  8: PutFont( 8, 3);  PutZero(1);  break;  //    30,000 Yen
      case  9: PutFont( 8, 4);  PutZero(1);  break;  //    40,000 Yen
      case 10: PutFont( 8, 5);  PutZero(1);  break;  //    50,000 Yen
      case 11: PutFont( 4, 1);  PutZero(2);  break;  //   100,000 Yen
      case 12: ClearLeds2();  PutFont( 0, 1);  PutZero(3);  break;  // 1,000,000 Yen
      default: break;
      }
    }

    M5.update();
    int button_check = DemoTimeShockCheckButton();

    if (button_check == 2000) {  // exit
      Serial.println("[DemoTimeShock]exit");
      return;
    }
    if (button_check == 1000) {  // set timer
      Serial.println("[DemoTimeShock]stop and reset timer");
      mode_quiz  = false;
      count_down = false;
      remain_ms = timer_ms;
    }
    if (button_check == -1) {
      if (count_down) {
        Serial.println("[DemoTimeShock]enter quiz mode, get prize money");

        // enter quiz mode
        if (!mode_quiz) {
          for (int i = 0; i < 12; ++i)
            correct_answer[i] = false;
          mode_quiz = true;
        }
        correct_answer[11 - remain_ms / 5000 % 12] = true;
      }
      else {
        Serial.println("[DemoTimeShock]reset quiz mode, start counting down");
        count_down = true;
        mode_quiz  = false;
      }
    }
    
    FastLED.show();

    delay(loop_ms - (millis() - last_ms));
    last_ms = millis();

    if (count_down) {
      remain_ms -= loop_ms;
      if (remain_ms / 1000 % 60 == 0) {
        mode_quiz = false;
      }
    }
  }

  Serial.println("[DemoTimeShock]end");
  return;
}

// button on the M5Atom
int DemoTimeShockCheckButton()
{
  if      (M5.Btn.pressedFor(3000)) PutPattern(pattern_null);  // cancel and nullify 
  else if (M5.Btn.pressedFor(2000)) PutPattern(pattern_exit);  // exit
  else if (M5.Btn.pressedFor(1000)) PutPattern(pattern_time);  // set timer

  if (M5.Btn.wasReleasefor(3000)) {
    Serial.println("[DemoTimeShockCheckButton]button >3s: button cancelled, nullify");
    return 3000;
  }
  if (M5.Btn.wasReleasefor(2000)) {
    Serial.println("[DemoTimeShockCheckButton]button >2s: exit");
    return 2000;
  } 
  if (M5.Btn.wasReleasefor(1000)) {
    Serial.println("[DemoTimeShockCheckButton]button >1s: set timer");
    ++timer_select;
    SelectTimer(timer_select);
    return 1000;
  } 
  if (M5.Btn.wasReleased()) {
    Serial.println("[DemoTimeShockCheckButton]button: start, correct answer");
    return -1;
  }
  return 0;
}

// select time for set timer
void SelectTimer(int &timer_select)
{
  switch (timer_select) {
  case  1: timer_ms =  60000;  break;  // 1 min
  case  2: timer_ms = 120000;  break;  // 2 min
  case  3: timer_ms = 180000;  break;  // 3 min
  case  4: timer_ms = 240000;  break;  // 4 min
  default: timer_ms = 300000;          // 5 min
    timer_select = 0;
    break;
  }
  Serial.printf("[SelectTimer]timer_ms: (%d) %d\n", timer_select, timer_ms);
}

// put zero
void PutZero(int num_of_digit)
{
  for (int i = num_of_digit; i > 0; --i)
    PutFont(16 - 4 * i, 0);
}
