#include <StateMachine/States.h>
#include <Controller/Controller.h>

void ShowPreviousMessageState::onEnter(Controller &controller) {}

State &ShowPreviousMessageState::callback(Controller &controller)
{
    // Callback is executed only once.
    // Executing code here instead of onEnter to have the chance to return an ErrorState

    controller.lcd.dotAnimation(F("Loading previous message"));
    bool result = controller.http.tryReceivePreviousMessage(skipCount);
    controller.lcd.clear(false);

    const Message *previousMessage = controller.http.getPreviousMessage();

    if (!result || !previousMessage)
    {
        ErrorState::the().errorMessage = F(ERR_MSG("Could not retrieve previous message."));
        return ErrorState::the();
    }

    controller.lcd.print(previousMessage->content);
    controller.matrix.draw(previousMessage->leds);

    return *this;
}

State &ShowPreviousMessageState::buttonPressCheck(Controller &controller)
{
    if (controller.acknowledgeButtonPressed && controller.flashButtonPressed)
        return CheckState::the();

    if (controller.flashButtonPressed)
        skipCount++;

    if (controller.acknowledgeButtonPressed && skipCount == 0)
        return CheckState::the();

    if (controller.acknowledgeButtonPressed)
        skipCount--;

    return ShowPreviousMessageTransitionState::the();
}

void ShowPreviousMessageState::onExit(Controller &controller)
{
    controller.lcd.clear();
    controller.matrix.clear();
}