#pragma once

#include <TaskSchedulerDeclarationsWithSettings.h>
#include <HttpSubsystem/Endpoints.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <HttpSubsystem/Message.h>

class HttpSubsystem
{
public:
    HttpSubsystem();
    const Message *getLastMessage() const { return lastMessage ? std::addressof(*lastMessage) : nullptr; };
    const Message *getPreviousMessage() const { return previousMessage ? std::addressof(*previousMessage) : nullptr; };
    const Message *getRandomMessage() const { return randomMessage ? std::addressof(*randomMessage) : nullptr; };
    bool tryReceiveLastMessage();
    bool tryReceivePreviousMessage(uint32_t skip);
    bool tryReceiveRandomMessage();
    bool acknowledgeLastMessage();

private:
    WiFiClientSecure wifiClient;
    HTTPClient httpClient;
    std::optional<Message> lastMessage{};
    std::optional<Message> previousMessage{};
    std::optional<Message> randomMessage{};
    std::optional<t_http_codes> getRequest(const String &url);
    bool getMessageFrom(const String &url, std::optional<Message> &result);
};