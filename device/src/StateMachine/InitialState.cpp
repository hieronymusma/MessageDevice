#include <StateMachine/States.h>
#include <Controller/Controller.h>
#include <ESP8266WiFi.h>
#include <Arduino.h>

void InitialState::onEnter(Controller &controller)
{
    controller.lcd.dotAnimation(F("Connecting"));
    controller.matrix.slidingAnimation(3);
}

State &InitialState::callback(Controller &controller)
{
    if (WiFi.status() != wl_status_t::WL_CONNECTED)
        return *this;
    CheckState::the().backgroundLightsForOneCallback = true;
    return CheckState::the();
}

State &InitialState::buttonPressCheck(Controller &controller)
{
    return *this;
}

void InitialState::onExit(Controller &controller)
{
    controller.lcd.clear();
    controller.matrix.clear();
}