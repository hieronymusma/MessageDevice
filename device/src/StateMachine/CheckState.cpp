#include <StateMachine/States.h>
#include <Controller/Controller.h>
#include <Arduino.h>

void CheckState::onEnter(Controller &controller) {}

State &CheckState::callback(Controller &controller)
{
    if (skipOneCallback)
    {
        skipOneCallback = false;
        backgroundLightsForOneCallback = false;
        controller.lcd.clear();
        return *this;
    }

    controller.lcd.dotAnimation(F("Checking for new messages"), backgroundLightsForOneCallback);

    // Do it only once
    backgroundLightsForOneCallback = false;

    bool result = controller.http.tryReceiveLastMessage();
    controller.lcd.clear();

    const Message *lastMessage = controller.http.getLastMessage();

    if (result && lastMessage && !lastMessage->ack)
        return NotifyState::the();

    if (!result)
    {
        ErrorState::the().errorMessage = F(ERR_MSG("Could not retrieve new messages."));
        return ErrorState::the();
    }

    return *this;
}

State &CheckState::buttonPressCheck(Controller &controller)
{
    // Skip direct check after we manually dive into messages
    CheckState::the().skipOneCallback = true;

    // Show random message
    if (controller.flashButtonPressed)
        return ShowRandomMessageState::the();

    if (controller.acknowledgeButtonPressed) {
        ShowPreviousMessageState::the().skipCount = 0;
        return ShowPreviousMessageState::the();
    }

    return *this;
}

void CheckState::onExit(Controller &controller)
{
    controller.lcd.clear();
    controller.matrix.clear();
}