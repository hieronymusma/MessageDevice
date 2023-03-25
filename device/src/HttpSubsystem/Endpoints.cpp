#include <HttpSubsystem/Endpoints.h>

#define BASEURL "https://" DOMAIN "/api/messages/" DEVICE_ID "/"
#define LAST BASEURL "last"
#define RANDOM BASEURL "random"

Endpoints::Endpoints() : baseUrl(F(BASEURL)), last(LAST), random(RANDOM) { }

const Endpoints& Endpoints::the() {
    static Endpoints singleton;
    return singleton;
}

String Endpoints::getPrevious(uint32_t count) const {
    String previous;

    previous.reserve(baseUrl.length() + 20);

    previous += baseUrl;
    previous += F("previous/");
    previous += count;

    return previous;
}

String Endpoints::getAck(uint32_t messageId) const {
    String ack;

    ack.reserve(baseUrl.length() + 20);

    ack += baseUrl;
    ack += messageId;
    ack += "/ack";

    return ack;
}