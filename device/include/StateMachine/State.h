#pragma once

#include <Arduino.h>

class Controller;

class State {
public:
    virtual void onEnter(Controller &controller) { };
    virtual State& callback(Controller &controller) { return *this; };
    virtual State& buttonPressCheck(Controller &controller) { return *this; };
    virtual void onExit(Controller &controller) { };
    virtual unsigned long callbackIntervall() = 0;
    virtual long callbackIterations() = 0;
    virtual const __FlashStringHelper* name() = 0;
    virtual ~State() {}
};