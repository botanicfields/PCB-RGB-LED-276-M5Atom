// Copyright 2021 BotanicFields, Inc.
// BF-025 RGB LED Clock 276 for M5Atom
// Demonstration: A tribute to "Quiz Time Shock" a famous TV show in Japan

#ifndef INCLUDED_BF_DEMOTIMESHOCK_H
#define INCLUDED_BF_DEMOTIMESHOCK_H

#include "BF-025.h"

void DemoTimeShock();
int  DemoTimeShockCheckButton();
void SelectTimer(int &timer_select);
void PutZero(int num_of_digit);

#endif //#ifndef INCLUDED_BF_DEMOTIMESHOCK_H
