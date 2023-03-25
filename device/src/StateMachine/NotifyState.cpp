#include <StateMachine/States.h>
#include <Controller/Controller.h>

void NotifyState::onEnter(Controller &controller)
{
    controller.matrix.pulsatingAnimation(3);
}

State &NotifyState::callback(Controller &controller)
{
    return *this;
}

State &NotifyState::buttonPressCheck(Controller &controller)
{
    // When we arrive here, we know that at least one button was pressed
    return ShowLastMessageState::the();
}

void NotifyState::onExit(Controller &controller)
{
    controller.matrix.clear();
    controller.lcd.clear();
}