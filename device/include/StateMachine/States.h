#pragma once

#include <StateMachine/State.h>
#include <TaskSchedulerDeclarationsWithSettings.h>
#include <Arduino.h>

class Controller;

#define CREATE_STATE(NAME, INTERVALL, ITERATIONS, ...) \
class NAME : public State \
{ \
public:\
    void onEnter(Controller &); \
    State &callback(Controller &); \
    State &buttonPressCheck(Controller &); \
    void onExit(Controller &); \
    unsigned long callbackIntervall() { return INTERVALL; } \
    long callbackIterations() { return ITERATIONS; } \
    const __FlashStringHelper* name() { return F(""#NAME""); }; \
    __VA_ARGS__ \
    static NAME &the() { \
        static NAME singleton; \
        return singleton; \
    }; \
\
private: \
    NAME() {} \
    NAME(const NAME &); \
    NAME &operator=(const NAME &); \
}

CREATE_STATE(InitialState, 500 * TASK_MILLISECOND, TASK_FOREVER);
CREATE_STATE(NotifyState, 0, TASK_ONCE);
CREATE_STATE(CheckState, 10 * TASK_SECOND, TASK_FOREVER, bool backgroundLightsForOneCallback{false}; bool skipOneCallback{false};);
CREATE_STATE(ErrorState, 20 * TASK_SECOND, TASK_FOREVER, const __FlashStringHelper* errorMessage{0}; bool firstCall{false};);
CREATE_STATE(ShowLastMessageState, 0, TASK_ONCE);
CREATE_STATE(ShowRandomMessageState, 0, TASK_ONCE);
CREATE_STATE(ShowRandomMessageTransitionState, 0, TASK_ONCE);
CREATE_STATE(ShowPreviousMessageState, 0, TASK_ONCE, uint32_t skipCount{1};);
CREATE_STATE(ShowPreviousMessageTransitionState, 0, TASK_ONCE); // This state is used to when page in the previous messages

#define ERR_MSG(MSG) "ERROR: Either wait or press a key\n" MSG

#undef CREATE_STATE