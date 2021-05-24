// Copyright 2021 BotanicFields, Inc.
// routines for Wi-Fi
#ifndef INCLUDED_BF_WIFI_H
#define INCLUDED_BF_WIFI_H

#include <WiFi.h>
#include <WiFiManager.h>  // https://github.com/tzapu/WiFiManager

void WifiBegin();
void WifiProcess();
void ConfigModeCallback(WiFiManager *wm);
void PrintWiFiStatus(const char* header, wl_status_t wl_status);

#endif  // INCLUDED_BF_WIFI_H
