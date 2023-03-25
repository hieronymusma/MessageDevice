#include <HttpSubsystem/HttpSubsystem.h>
#include <ESP8266WiFi.h>

HttpSubsystem::HttpSubsystem()
{
    wifiClient.setInsecure();
    httpClient.setAuthorization(API_USER, API_PASSWORD);
}

bool HttpSubsystem::tryReceiveLastMessage()
{
    return getMessageFrom(Endpoints::the().last, lastMessage);
}

bool HttpSubsystem::tryReceivePreviousMessage(uint32_t skip)
{
    return getMessageFrom(Endpoints::the().getPrevious(skip), previousMessage);
}

bool HttpSubsystem::tryReceiveRandomMessage()
{
    return getMessageFrom(Endpoints::the().random, randomMessage);
}

bool HttpSubsystem::getMessageFrom(const String &url, std::optional<Message> &result)
{
    if (WiFi.status() != wl_status_t::WL_CONNECTED)
        return false;

    auto start = millis();

    std::optional<t_http_codes> requesRresult = getRequest(url);

    if (!requesRresult)
        return false;

    t_http_codes returnCode = requesRresult.value();

    auto end = millis();

    auto diff = end - start;

    Serial.printf_P(PSTR("Request time: %lu\n"), diff);

    if (returnCode == HTTP_CODE_NO_CONTENT)
        return true;

    if (returnCode != HTTP_CODE_OK)
        return false;

    DynamicJsonDocument doc(3072); // Calculated by https://arduinojson.org/v6/assistant with a lot of spare space to long strings

    DeserializationError deserializationError = deserializeJson(doc, httpClient.getString());

    httpClient.end();

    if (deserializationError)
    {
        Serial.printf_P(PSTR("Could not deserialize input: %s"), deserializationError.c_str());
        return false;
    }

    result = Message(doc);

    return true;
}

bool HttpSubsystem::acknowledgeLastMessage()
{
    if (!lastMessage.has_value() || lastMessage.value().ack)
        return true;

    String ackEndpoint = Endpoints::the().getAck(lastMessage.value().id);

    std::optional<t_http_codes> result = getRequest(ackEndpoint);

    if (result && result.value() == HTTP_CODE_OK)
        return true;

    return false;
}

std::optional<t_http_codes> HttpSubsystem::getRequest(const String &Url)
{
    httpClient.end();

    Serial.print("Begin request to: ");
    Serial.println(Url);

    bool result = httpClient.begin(wifiClient, Url);

    if (!result)
    {
        Serial.println(F("Could not begin http connection"));
        httpClient.end();
        return {};
    }

    t_http_codes httpResponseCode = static_cast<t_http_codes>(httpClient.GET());

    Serial.printf_P(PSTR("Done: Received http code: %u\n"), httpResponseCode);

    if (httpResponseCode != HTTP_CODE_OK && httpResponseCode != HTTP_CODE_NO_CONTENT)
    {
        Serial.println(F("Got payload:"));
        Serial.print(httpClient.getString());
        httpClient.end();
    }

    return httpResponseCode;
}