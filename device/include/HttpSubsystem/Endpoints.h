#pragma once

#include <Arduino.h>

class Endpoints {
public:
    const String baseUrl;
    const String last;
    const String random;
    String getPrevious(uint32_t count) const;
    String getAck(uint32_t messageId) const;
    static const Endpoints& the();
private:
    Endpoints();
};