#include <StateMachine/States.h>
#include <Controller/Controller.h>
#include <HttpSubsystem/Message.h>
#include <Arduino.h>

void ShowLastMessageState::onEnter(Controller &controller)
{
}

State &ShowLastMessageState::callback(Controller &controller)
{
    const Message* message = controller.http.getLastMessage();
    if (!message) {
        ErrorState::the().errorMessage = F(ERR_MSG("Could not show last message."));
        return ErrorState::the();
    }
    controller.lcd.print(message->content);
    controller.matrix.draw(message->leds);
    return *this;
}

State &ShowLastMessageState::buttonPressCheck(Controller &controller)
{
    // Acknowledge on any button press
    controller.matrix.clear();
    controller.lcd.dotAnimation(F("Wait until message is acknowledged..."));
    bool result = controller.http.acknowledgeLastMessage();
    if (!result) {
        ErrorState::the().errorMessage = F(ERR_MSG("Could not acknowledge message..."));
        return ErrorState::the();
    }
    CheckState::the().backgroundLightsForOneCallback = true;
    return CheckState::the();
}

void ShowLastMessageState::onExit(Controller &controller)
{
    controller.lcd.clear(false);
    controller.matrix.clear();
}