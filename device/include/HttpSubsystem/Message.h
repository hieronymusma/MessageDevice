#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>

struct Message {
    u64 id = 0;
    String content;
    bool leds[64] = { 0 };
    bool ack = false;

    Message();
    Message(JsonDocument&);
};