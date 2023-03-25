#include <StateMachine/States.h>
#include <Controller/Controller.h>

void ShowRandomMessageState::onEnter(Controller &controller) { }

State &ShowRandomMessageState::callback(Controller &controller)
{
    // Callback is executed only once.
    // Executing code here instead of onEnter to have the chance to return an ErrorState

    controller.lcd.dotAnimation(F("Loading random message"));
    bool result = controller.http.tryReceiveRandomMessage();
    controller.lcd.clear(false);

    const Message* randomMessage = controller.http.getRandomMessage();

    if(!result || !randomMessage) {
        ErrorState::the().errorMessage = F(ERR_MSG("Could not retrieve random message."));
        return ErrorState::the();
    }

    controller.lcd.print(randomMessage->content);
    controller.matrix.draw(randomMessage->leds);

    return *this;
}

State &ShowRandomMessageState::buttonPressCheck(Controller &controller)
{
    if (controller.acknowledgeButtonPressed)
        return CheckState::the();

    if (controller.flashButtonPressed)
        return ShowRandomMessageTransitionState::the();

    return *this;
}

void ShowRandomMessageState::onExit(Controller &controller)
{
    controller.lcd.clear();
    controller.matrix.clear();
}