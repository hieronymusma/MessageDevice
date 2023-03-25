#include <StateMachine/StateMachine.h>
#include <Controller/Controller.h>
#include <Arduino.h>

StateMachine::StateMachine(Controller &controller) : controller{controller}
{
    currentState->onEnter(controller);
    controller.callbackTask.setInterval(currentState->callbackIntervall());
    controller.callbackTask.setIterations(currentState->callbackIterations());
    controller.callbackTask.enableDelayed();
}

void StateMachine::executeCallback()
{
    State &newState = currentState->callback(controller);
    // Reset delay such that a long executed task run after it's delay again
    controller.callbackTask.delay();
    setNewState(newState);
}

void StateMachine::executeButtonPressCheck()
{
    if (!controller.acknowledgeButtonPressed && !controller.flashButtonPressed)
        return;
    State &newState = currentState->buttonPressCheck(controller);
    setNewState(newState);
}

void StateMachine::setNewState(State &newState)
{
    if (currentState == &newState)
        return;

    Serial.print(F("Transition from "));
    Serial.print(currentState->name());
    Serial.print(F(" to "));
    Serial.print(newState.name());
    Serial.println();

    controller.callbackTask.disable();
    currentState->onExit(controller);

    controller.resetButtonPresses();

    currentState = &newState;
    currentState->onEnter(controller);

    controller.callbackTask.setInterval(currentState->callbackIntervall());
    controller.callbackTask.setIterations(currentState->callbackIterations());
    controller.callbackTask.enable();
}