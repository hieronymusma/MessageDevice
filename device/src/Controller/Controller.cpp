#include <Controller/Controller.h>
#include <Arduino.h>

Controller::Controller(Scheduler &basePriorityScheduler, volatile bool &flashButtonPressed, volatile bool &acknowledgeButtonPressed) : flashButtonPressed{flashButtonPressed}, acknowledgeButtonPressed{acknowledgeButtonPressed}, buttonTask{basePriorityScheduler, *this}, callbackTask{basePriorityScheduler, *this}, matrix{basePriorityScheduler}, lcd{basePriorityScheduler}, diagnostics{basePriorityScheduler}, stateMachine{*this} {}

void Controller::resetButtonPresses()
{
    acknowledgeButtonPressed = false;
    flashButtonPressed = false;
}

IRAM_ATTR void Controller::interruptOccurred()
{
    buttonTask.delay();
}