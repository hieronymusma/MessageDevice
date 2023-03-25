#include <StateMachine/States.h>
#include <Controller/Controller.h>

void ShowPreviousMessageTransitionState::onEnter(Controller &controller)
{
}

State &ShowPreviousMessageTransitionState::callback(Controller &controller)
{
    return ShowPreviousMessageState::the();
}

State &ShowPreviousMessageTransitionState::buttonPressCheck(Controller &controller)
{
    return *this;
}

void ShowPreviousMessageTransitionState::onExit(Controller &controller)
{
}
