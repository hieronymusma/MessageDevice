#pragma once

#include <TaskSchedulerDeclarationsWithSettings.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>

class DiagnosticsTask : private Task
{
public:
    DiagnosticsTask(Scheduler &);
    DiagnosticsTask(const DiagnosticsTask&) = delete;
    void operator=(const DiagnosticsTask&) = delete;

private:
    bool Callback();
    const __FlashStringHelper* getWifiStatusAsText(wl_status_t);
    void printUptime();
};