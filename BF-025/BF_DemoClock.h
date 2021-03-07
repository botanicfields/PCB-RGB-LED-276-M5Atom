// Copyright 2021 BotanicFields, Inc.
// BF-025 RGB LED Clock 276 for M5Atom
// Demonstration: Digital & analog clock

#ifndef INCLUDED_BF_DEMOCLOCK_H
#define INCLUDED_BF_DEMOCLOCK_H

#include "BF-025.h"

void TickerHandle();
void DemoClock();
int  CrawlTimeDate(int last_ms, int crawl_offset);
int  PutTimeDate(int x_offset);
int  FlowString(int x, const String s);
int  Invader(int x);
void InvaderSub(int x, int kind);

#endif //#ifndef INCLUDED_BF_DEMOCLOCK_H
