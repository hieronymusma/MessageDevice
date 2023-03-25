#include <StateMachine/States.h>
#include <Controller/Controller.h>

void ShowRandomMessageTransitionState::onEnter(Controller &controller)
{
}

State &ShowRandomMessageTransitionState::callback(Controller &controller)
{
    return ShowRandomMessageState::the();
}

State &ShowRandomMessageTransitionState::buttonPressCheck(Controller &controller)
{
    return *this;
}

void ShowRandomMessageTransitionState::onExit(Controller &controller)
{
}
