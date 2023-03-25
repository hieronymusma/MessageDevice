#include <DiagnosticsTask.h>

DiagnosticsTask::DiagnosticsTask(Scheduler &scheduler) : Task(10 * TASK_SECOND, TASK_FOREVER, &scheduler, true) {}

bool DiagnosticsTask::Callback()
{
    Serial.printf_P(PSTR("Diagnostics:\n\nHeap:\nFree heap: %d\nHeap Fragmentation: %d\nMax free blocksize: %d\n\n"), ESP.getFreeHeap(), ESP.getHeapFragmentation(), ESP.getMaxFreeBlockSize());
    Serial.printf_P(PSTR("WiFi: "));
    Serial.print(getWifiStatusAsText(WiFi.status()));
    Serial.printf_P(PSTR("\n\n"));
    printUptime();
    return true;
}

void DiagnosticsTask::printUptime() {
    unsigned long millisecs = millis();
    int systemUpTimeSec = (millisecs / (1000)) % 60;
    int systemUpTimeMn = (millisecs / (1000 * 60)) % 60;
    int systemUpTimeHr = (millisecs / (1000 * 60 * 60)) % 24;
    int systemUpTimeDy = (millisecs / (1000 * 60 * 60 * 24)) % 365;
    Serial.printf_P(PSTR("UPTIME: %02d Days %02d h %02d min %02d sec\n\n"), systemUpTimeDy, systemUpTimeHr, systemUpTimeMn, systemUpTimeSec);
}

const __FlashStringHelper *DiagnosticsTask::getWifiStatusAsText(wl_status_t status)
{
    switch (status)
    {
    case wl_status_t::WL_CONNECT_FAILED:
        return F("WL_CONNECT_FAILED");
    case wl_status_t::WL_CONNECTED:
        return F("WL_CONNECTED");
    case wl_status_t::WL_CONNECTION_LOST:
        return F("WL_CONNECTION_LOST");
    case wl_status_t::WL_DISCONNECTED:
        return F("WL_DISCONNECTED");
    case wl_status_t::WL_IDLE_STATUS:
        return F("WL_IDLE_STATUS");
    case wl_status_t::WL_NO_SHIELD:
        return F("WL_NO_SHIELD");
    case wl_status_t::WL_NO_SSID_AVAIL:
        return F("WL_NO_SSID_AVAIL");
    case wl_status_t::WL_SCAN_COMPLETED:
        return F("WL_SCAN_COMPLETED");
    case wl_status_t::WL_WRONG_PASSWORD:
        return F("WL_WRONG_PASSWORD");
    }
    return F("");
}