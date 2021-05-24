// Copyright 2021 BotanicFields, Inc.
// routines for NTP and RTCx(PCf8563)

#ifndef INCLUDED_BF_RTCXNTP_H
#define INCLUDED_BF_RTCXNTP_H

#include <sys/time.h>  // for struct timeval
#include <sntp.h>      // for sntp_sync_status, https://github.com/espressif/arduino-esp32 1.0.6-

void SetTimeFromRtcx();
void NtpBegin();
void PrintSntpStatus(const char* header, sntp_sync_status_t sntp_sync_status);
void SntpTimeSyncNotificationCallback(struct timeval *tv);

#endif  // INCLUDED_BF_RTCXNTP_H
