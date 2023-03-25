#pragma once

#include <StateMachine/State.h>
#include <StateMachine/States.h>

class Controller;

class StateMachine
{
public:
    StateMachine(Controller &);
    void executeCallback();
    void executeButtonPressCheck();

private:
    Controller &controller;
    State* currentState{&InitialState::the()};
    void setNewState(State &);
};