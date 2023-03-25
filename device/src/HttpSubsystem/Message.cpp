#include <HttpSubsystem/Message.h>

Message::Message(JsonDocument &doc)
{
    id = doc["id"];
    content = doc["content"].as<String>();
    ack = doc["ack"].as<bool>();
    JsonArray jsonLeds = doc["leds"];
    for (int idx = 0; idx < 64; idx++)
    {
        leds[idx] = jsonLeds[idx].as<bool>();
    }
}

Message::Message() {}