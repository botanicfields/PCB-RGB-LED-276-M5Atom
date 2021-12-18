// Copyright 2021 BotanicFields, Inc.
// BF-025 RGB LED Clock 276 for M5Atom
// Demonstration: Digital & analog clock

#pragma once

void TickerHandle();
void DemoClock();
int  CrawlTimeDate(unsigned int last_ms, int crawl_offset);
int  PutTimeDate(int x_offset);
int  FlowString(int x, const String s);
int  Invader(int x);
void InvaderSub(int x, int kind);
