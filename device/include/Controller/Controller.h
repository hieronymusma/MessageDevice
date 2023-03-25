#pragma once

#include <TaskSchedulerDeclarationsWithSettings.h>
#include <Matrix/MatrixSubsystem.h>
#include <LCDSubsystem/LCDSubsystem.h>
#include <DiagnosticsTask.h>
#include <HttpSubsystem/HttpSubsystem.h>
#include <StateMachine/StateMachine.h>
#include <Controller/ButtonTask.h>
#include <Controller/CallbackTask.h>

class Controller
{
    friend ButtonTask;
    friend CallbackTask;
    friend StateMachine;
    friend InitialState;
    friend CheckState;
    friend ShowLastMessageState;
    friend NotifyState;
    friend ErrorState;
    friend ShowRandomMessageState;
    friend ShowPreviousMessageState;
public:
    Controller(Scheduler &basePriorityScheduler, volatile bool &flashButtonPressed, volatile bool &acknowledgeButtonPressed);
    void interruptOccurred();
private:
    volatile bool &flashButtonPressed;
    volatile bool &acknowledgeButtonPressed;
    ButtonTask buttonTask;
    CallbackTask callbackTask;
    MatrixSubsystem matrix;
    LCDSubsystem lcd;
    DiagnosticsTask diagnostics;
    HttpSubsystem http;
    StateMachine stateMachine;

    void resetButtonPresses();
};